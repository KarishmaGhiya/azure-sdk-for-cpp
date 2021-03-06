// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#include "datalake/path_client.hpp"

#include "common/common_headers_request_policy.hpp"
#include "common/constants.hpp"
#include "common/crypt.hpp"
#include "common/shared_key_policy.hpp"
#include "common/storage_common.hpp"
#include "common/storage_version.hpp"
#include "credentials/policy/policies.hpp"
#include "datalake/datalake_utilities.hpp"
#include "http/curl/curl.hpp"

#include <limits>
#include <utility> //std::pair

namespace Azure { namespace Storage { namespace Files { namespace DataLake {
  namespace {
    Blobs::BlobClientOptions GetBlobClientOptions(const PathClientOptions& options)
    {
      Blobs::BlobClientOptions blobOptions;
      for (const auto& p : options.PerOperationPolicies)
      {
        blobOptions.PerOperationPolicies.emplace_back(p->Clone());
      }
      for (const auto& p : options.PerRetryPolicies)
      {
        blobOptions.PerRetryPolicies.emplace_back(p->Clone());
      }
      return blobOptions;
    }

    LeaseStateType FromBlobLeaseState(Blobs::BlobLeaseState state)
    {
      auto ret = LeaseStateType::Unknown;
      switch (state)
      {
        case Blobs::BlobLeaseState::Available:
          ret = LeaseStateType::Available;
          break;
        case Blobs::BlobLeaseState::Breaking:
          ret = LeaseStateType::Breaking;
          break;
        case Blobs::BlobLeaseState::Broken:
          ret = LeaseStateType::Broken;
          break;
        case Blobs::BlobLeaseState::Expired:
          ret = LeaseStateType::Expired;
          break;
        case Blobs::BlobLeaseState::Leased:
          ret = LeaseStateType::Leased;
          break;
        default:
          ret = LeaseStateType::Unknown;
          break;
      }
      return ret;
    }

    LeaseStatusType FromBlobLeaseStatus(Blobs::BlobLeaseStatus status)
    {
      auto ret = LeaseStatusType::Unknown;
      switch (status)
      {
        case Blobs::BlobLeaseStatus::Locked:
          ret = LeaseStatusType::Locked;
          break;
        case Blobs::BlobLeaseStatus::Unlocked:
          ret = LeaseStatusType::Unlocked;
          break;
        default:
          ret = LeaseStatusType::Unknown;
          break;
      }
      return ret;
    }
  } // namespace

  PathClient PathClient::CreateFromConnectionString(
      const std::string& connectionString,
      const std::string& fileSystemName,
      const std::string& path,
      const PathClientOptions& options)
  {
    auto parsedConnectionString = Azure::Storage::Details::ParseConnectionString(connectionString);
    auto pathUri = std::move(parsedConnectionString.DataLakeServiceUri);
    pathUri.AppendPath(fileSystemName, true);
    pathUri.AppendPath(path, true);

    if (parsedConnectionString.KeyCredential)
    {
      return PathClient(pathUri.ToString(), parsedConnectionString.KeyCredential, options);
    }
    else
    {
      return PathClient(pathUri.ToString(), options);
    }
  }

  PathClient::PathClient(
      const std::string& pathUri,
      std::shared_ptr<SharedKeyCredential> credential,
      const PathClientOptions& options)
      : m_dfsUri(Details::GetDfsUriFromUri(pathUri)),
        m_blobClient(Details::GetBlobUriFromUri(pathUri), credential, GetBlobClientOptions(options))
  {
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> policies;
    policies.emplace_back(std::make_unique<Azure::Core::Http::TelemetryPolicy>(
        Azure::Storage::Details::c_DatalakeServicePackageName, DataLakeServiceVersion));
    for (const auto& p : options.PerOperationPolicies)
    {
      policies.emplace_back(p->Clone());
    }
    policies.emplace_back(
        std::make_unique<Azure::Core::Http::RetryPolicy>(Azure::Core::Http::RetryOptions()));
    for (const auto& p : options.PerRetryPolicies)
    {
      policies.emplace_back(p->Clone());
    }
    policies.emplace_back(std::make_unique<CommonHeadersRequestPolicy>());
    policies.emplace_back(std::make_unique<SharedKeyPolicy>(credential));
    policies.emplace_back(std::make_unique<Azure::Core::Http::TransportPolicy>(
        std::make_shared<Azure::Core::Http::CurlTransport>()));
    m_pipeline = std::make_shared<Azure::Core::Http::HttpPipeline>(policies);
  }

  PathClient::PathClient(
      const std::string& pathUri,
      std::shared_ptr<Core::Credentials::TokenCredential> credential,
      const PathClientOptions& options)
      : m_dfsUri(Details::GetDfsUriFromUri(pathUri)),
        m_blobClient(Details::GetBlobUriFromUri(pathUri), credential, GetBlobClientOptions(options))
  {
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> policies;
    policies.emplace_back(std::make_unique<Azure::Core::Http::TelemetryPolicy>(
        Azure::Storage::Details::c_DatalakeServicePackageName, DataLakeServiceVersion));
    for (const auto& p : options.PerOperationPolicies)
    {
      policies.emplace_back(p->Clone());
    }
    policies.emplace_back(
        std::make_unique<Azure::Core::Http::RetryPolicy>(Azure::Core::Http::RetryOptions()));
    for (const auto& p : options.PerRetryPolicies)
    {
      policies.emplace_back(p->Clone());
    }
    policies.emplace_back(std::make_unique<CommonHeadersRequestPolicy>());
    policies.emplace_back(
        std::make_unique<Core::Credentials::Policy::BearerTokenAuthenticationPolicy>(
            credential, Azure::Storage::Details::c_StorageScope));
    policies.emplace_back(std::make_unique<Azure::Core::Http::TransportPolicy>(
        std::make_shared<Azure::Core::Http::CurlTransport>()));
    m_pipeline = std::make_shared<Azure::Core::Http::HttpPipeline>(policies);
  }

  PathClient::PathClient(const std::string& pathUri, const PathClientOptions& options)
      : m_dfsUri(Details::GetDfsUriFromUri(pathUri)),
        m_blobClient(Details::GetBlobUriFromUri(pathUri), GetBlobClientOptions(options))
  {
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> policies;
    policies.emplace_back(std::make_unique<Azure::Core::Http::TelemetryPolicy>(
        Azure::Storage::Details::c_DatalakeServicePackageName, DataLakeServiceVersion));
    for (const auto& p : options.PerOperationPolicies)
    {
      policies.emplace_back(p->Clone());
    }
    policies.emplace_back(
        std::make_unique<Azure::Core::Http::RetryPolicy>(Azure::Core::Http::RetryOptions()));
    for (const auto& p : options.PerRetryPolicies)
    {
      policies.emplace_back(p->Clone());
    }
    policies.emplace_back(std::make_unique<CommonHeadersRequestPolicy>());
    policies.emplace_back(std::make_unique<Azure::Core::Http::TransportPolicy>(
        std::make_shared<Azure::Core::Http::CurlTransport>()));
    m_pipeline = std::make_shared<Azure::Core::Http::HttpPipeline>(policies);
  }

  Azure::Core::Response<PathSetAccessControlInfo> PathClient::SetAccessControl(
      std::vector<Acl> acls,
      const SetAccessControlOptions& options) const
  {
    DataLakeRestClient::Path::SetAccessControlOptions protocolLayerOptions;
    protocolLayerOptions.LeaseIdOptional = options.AccessConditions.LeaseId;
    protocolLayerOptions.Owner = options.Owner;
    protocolLayerOptions.Group = options.Group;
    protocolLayerOptions.Permissions = options.Permissions;
    protocolLayerOptions.Acl = Acl::SerializeAcls(acls);
    protocolLayerOptions.IfMatch = options.AccessConditions.IfMatch;
    protocolLayerOptions.IfNoneMatch = options.AccessConditions.IfNoneMatch;
    protocolLayerOptions.IfModifiedSince = options.AccessConditions.IfModifiedSince;
    protocolLayerOptions.IfUnmodifiedSince = options.AccessConditions.IfUnmodifiedSince;
    return DataLakeRestClient::Path::SetAccessControl(
        m_dfsUri.ToString(), *m_pipeline, options.Context, protocolLayerOptions);
  }

  Azure::Core::Response<SetPathHttpHeadersInfo> PathClient::SetHttpHeaders(
      DataLakeHttpHeaders httpHeaders,
      const SetPathHttpHeadersOptions& options) const
  {
    Blobs::SetBlobHttpHeadersOptions blobOptions;
    Blobs::BlobHttpHeaders blobHttpHeaders;
    blobOptions.Context = options.Context;
    blobHttpHeaders.CacheControl = httpHeaders.CacheControl;
    blobHttpHeaders.ContentType = httpHeaders.ContentType;
    blobHttpHeaders.ContentDisposition = httpHeaders.ContentDisposition;
    blobHttpHeaders.ContentEncoding = httpHeaders.ContentEncoding;
    blobHttpHeaders.ContentLanguage = httpHeaders.ContentLanguage;
    blobOptions.AccessConditions.IfMatch = options.AccessConditions.IfMatch;
    blobOptions.AccessConditions.IfNoneMatch = options.AccessConditions.IfNoneMatch;
    blobOptions.AccessConditions.IfModifiedSince = options.AccessConditions.IfModifiedSince;
    blobOptions.AccessConditions.IfUnmodifiedSince = options.AccessConditions.IfUnmodifiedSince;
    blobOptions.AccessConditions.LeaseId = options.AccessConditions.LeaseId;
    auto result = m_blobClient.SetHttpHeaders(blobHttpHeaders, blobOptions);
    SetPathHttpHeadersInfo ret;
    ret.ETag = std::move(result->ETag);
    ret.LastModified = std::move(result->LastModified);
    return Azure::Core::Response<SetPathHttpHeadersInfo>(
        std::move(ret), result.ExtractRawResponse());
  }

  Azure::Core::Response<PathInfo> PathClient::Create(
      PathResourceType type,
      const PathCreateOptions& options) const
  {
    DataLakeRestClient::Path::CreateOptions protocolLayerOptions;
    protocolLayerOptions.Resource = type;
    protocolLayerOptions.LeaseIdOptional = options.AccessConditions.LeaseId;
    protocolLayerOptions.CacheControl = options.HttpHeaders.CacheControl;
    protocolLayerOptions.ContentType = options.HttpHeaders.ContentType;
    protocolLayerOptions.ContentDisposition = options.HttpHeaders.ContentDisposition;
    protocolLayerOptions.ContentEncoding = options.HttpHeaders.ContentEncoding;
    protocolLayerOptions.ContentLanguage = options.HttpHeaders.ContentLanguage;
    protocolLayerOptions.IfMatch = options.AccessConditions.IfMatch;
    protocolLayerOptions.IfNoneMatch = options.AccessConditions.IfNoneMatch;
    protocolLayerOptions.IfModifiedSince = options.AccessConditions.IfModifiedSince;
    protocolLayerOptions.IfUnmodifiedSince = options.AccessConditions.IfUnmodifiedSince;
    protocolLayerOptions.Properties = Details::SerializeMetadata(options.Metadata);
    protocolLayerOptions.Umask = options.Umask;
    protocolLayerOptions.Permissions = options.Permissions;
    auto result = DataLakeRestClient::Path::Create(
        m_dfsUri.ToString(), *m_pipeline, options.Context, protocolLayerOptions);
    auto ret = PathInfo();
    ret.ETag = std::move(result->ETag);
    ret.LastModified = std::move(result->LastModified);
    ret.ContentLength = std::move(result->ContentLength);
    return Azure::Core::Response<PathInfo>(std::move(ret), result.ExtractRawResponse());
  }

  Azure::Core::Response<PathDeleteResponse> PathClient::Delete(
      const PathDeleteOptions& options) const
  {
    DataLakeRestClient::Path::DeleteOptions protocolLayerOptions;
    protocolLayerOptions.Continuation = options.Continuation;
    protocolLayerOptions.LeaseIdOptional = options.AccessConditions.LeaseId;
    protocolLayerOptions.IfMatch = options.AccessConditions.IfMatch;
    protocolLayerOptions.IfNoneMatch = options.AccessConditions.IfNoneMatch;
    protocolLayerOptions.IfModifiedSince = options.AccessConditions.IfModifiedSince;
    protocolLayerOptions.IfUnmodifiedSince = options.AccessConditions.IfUnmodifiedSince;
    protocolLayerOptions.RecursiveOptional = options.Recursive;
    return DataLakeRestClient::Path::Delete(
        m_dfsUri.ToString(), *m_pipeline, options.Context, protocolLayerOptions);
  }

  Azure::Core::Response<PathProperties> PathClient::GetProperties(
      const PathGetPropertiesOptions& options) const
  {
    Blobs::GetBlobPropertiesOptions blobOptions;
    blobOptions.Context = options.Context;
    blobOptions.AccessConditions.IfMatch = options.AccessConditions.IfMatch;
    blobOptions.AccessConditions.IfNoneMatch = options.AccessConditions.IfNoneMatch;
    blobOptions.AccessConditions.IfModifiedSince = options.AccessConditions.IfModifiedSince;
    blobOptions.AccessConditions.IfUnmodifiedSince = options.AccessConditions.IfUnmodifiedSince;
    blobOptions.AccessConditions.LeaseId = options.AccessConditions.LeaseId;
    auto result = m_blobClient.GetProperties(blobOptions);
    PathProperties ret;
    ret.ETag = std::move(result->ETag);
    ret.LastModified = std::move(result->LastModified);
    ret.CreationTime = std::move(result->CreationTime);
    ret.Metadata = std::move(result->Metadata);
    ret.LeaseDuration = std::move(result->LeaseDuration);
    ret.LeaseState = result->LeaseState.HasValue()
        ? FromBlobLeaseState(result->LeaseState.GetValue())
        : ret.LeaseState;
    ret.LeaseStatus = result->LeaseStatus.HasValue()
        ? FromBlobLeaseStatus(result->LeaseStatus.GetValue())
        : ret.LeaseStatus;
    ret.HttpHeaders.CacheControl = std::move(result->HttpHeaders.CacheControl);
    ret.HttpHeaders.ContentDisposition = std::move(result->HttpHeaders.ContentDisposition);
    ret.HttpHeaders.ContentEncoding = std::move(result->HttpHeaders.ContentEncoding);
    ret.HttpHeaders.ContentLanguage = std::move(result->HttpHeaders.ContentLanguage);
    ret.HttpHeaders.ContentType = std::move(result->HttpHeaders.ContentType);
    ret.ServerEncrypted = std::move(result->ServerEncrypted);
    ret.EncryptionKeySha256 = std::move(result->EncryptionKeySha256);
    ret.AccessTierInferred = std::move(result->AccessTierInferred);
    ret.AccessTierChangeTime = std::move(result->AccessTierChangeTime);
    ret.CopyId = std::move(result->CopyId);
    ret.CopySource = std::move(result->CopySource);
    ret.CopyStatus = std::move(result->CopyStatus);
    ret.CopyProgress = std::move(result->CopyProgress);
    ret.CopyCompletionTime = std::move(result->CopyCompletionTime);
    return Azure::Core::Response<PathProperties>(std::move(ret), result.ExtractRawResponse());
  }

  Azure::Core::Response<PathAccessControl> PathClient::GetAccessControls(
      const PathAccessControlOptions& options) const
  {
    DataLakeRestClient::Path::GetPropertiesOptions protocolLayerOptions;
    protocolLayerOptions.Action = PathGetPropertiesAction::GetAccessControl;
    protocolLayerOptions.LeaseIdOptional = options.AccessConditions.LeaseId;
    protocolLayerOptions.IfMatch = options.AccessConditions.IfMatch;
    protocolLayerOptions.IfNoneMatch = options.AccessConditions.IfNoneMatch;
    protocolLayerOptions.IfModifiedSince = options.AccessConditions.IfModifiedSince;
    protocolLayerOptions.IfUnmodifiedSince = options.AccessConditions.IfUnmodifiedSince;
    auto result = DataLakeRestClient::Path::GetProperties(
        m_dfsUri.ToString(), *m_pipeline, options.Context, protocolLayerOptions);
    Azure::Core::Nullable<std::vector<Acl>> acl;
    if (result->ACL.HasValue())
    {
      acl = Acl::DeserializeAcls(result->ACL.GetValue());
    }
    auto ret = PathAccessControl{};
    ret.ETag = std::move(result->ETag);
    ret.LastModified = std::move(result->LastModified);
    if (!acl.HasValue())
    {
      throw std::runtime_error("Got null value returned when getting access control.");
    }
    ret.Acls = std::move(acl.GetValue());
    return Azure::Core::Response<PathAccessControl>(std::move(ret), result.ExtractRawResponse());
  }

  Azure::Core::Response<SetPathMetadataInfo> PathClient::SetMetadata(
      const std::map<std::string, std::string>& metadata,
      const SetPathMetadataOptions& options) const
  {
    Blobs::SetBlobMetadataOptions blobOptions;
    blobOptions.Context = options.Context;
    blobOptions.AccessConditions.IfMatch = options.AccessConditions.IfMatch;
    blobOptions.AccessConditions.IfNoneMatch = options.AccessConditions.IfNoneMatch;
    blobOptions.AccessConditions.IfModifiedSince = options.AccessConditions.IfModifiedSince;
    blobOptions.AccessConditions.IfUnmodifiedSince = options.AccessConditions.IfUnmodifiedSince;
    blobOptions.AccessConditions.LeaseId = options.AccessConditions.LeaseId;
    auto result = m_blobClient.SetMetadata(metadata, blobOptions);
    SetPathMetadataInfo ret;
    ret.ETag = std::move(result->ETag);
    ret.LastModified = std::move(result->LastModified);
    return Azure::Core::Response<SetPathMetadataInfo>(std::move(ret), result.ExtractRawResponse());
  }
}}}} // namespace Azure::Storage::Files::DataLake
