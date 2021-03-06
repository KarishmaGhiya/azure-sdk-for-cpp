// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#include "blobs/blob_container_client.hpp"

#include "blobs/append_blob_client.hpp"
#include "blobs/block_blob_client.hpp"
#include "blobs/page_blob_client.hpp"
#include "common/common_headers_request_policy.hpp"
#include "common/constants.hpp"
#include "common/shared_key_policy.hpp"
#include "common/storage_common.hpp"
#include "common/storage_version.hpp"
#include "credentials/policy/policies.hpp"
#include "http/curl/curl.hpp"

namespace Azure { namespace Storage { namespace Blobs {

  BlobContainerClient BlobContainerClient::CreateFromConnectionString(
      const std::string& connectionString,
      const std::string& containerName,
      const BlobContainerClientOptions& options)
  {
    auto parsedConnectionString = Details::ParseConnectionString(connectionString);
    auto containerUri = std::move(parsedConnectionString.BlobServiceUri);
    containerUri.AppendPath(containerName, true);

    if (parsedConnectionString.KeyCredential)
    {
      return BlobContainerClient(
          containerUri.ToString(), parsedConnectionString.KeyCredential, options);
    }
    else
    {
      return BlobContainerClient(containerUri.ToString(), options);
    }
  }

  BlobContainerClient::BlobContainerClient(
      const std::string& containerUri,
      std::shared_ptr<SharedKeyCredential> credential,
      const BlobContainerClientOptions& options)
      : BlobContainerClient(containerUri, options)
  {
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> policies;
    policies.emplace_back(std::make_unique<Azure::Core::Http::TelemetryPolicy>(
        Details::c_BlobServicePackageName, BlobServiceVersion));
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

  BlobContainerClient::BlobContainerClient(
      const std::string& containerUri,
      std::shared_ptr<Core::Credentials::TokenCredential> credential,
      const BlobContainerClientOptions& options)
      : BlobContainerClient(containerUri, options)
  {
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> policies;
    policies.emplace_back(std::make_unique<Azure::Core::Http::TelemetryPolicy>(
        Details::c_BlobServicePackageName, BlobServiceVersion));
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
            credential, Details::c_StorageScope));
    policies.emplace_back(std::make_unique<Azure::Core::Http::TransportPolicy>(
        std::make_shared<Azure::Core::Http::CurlTransport>()));
    m_pipeline = std::make_shared<Azure::Core::Http::HttpPipeline>(policies);
  }

  BlobContainerClient::BlobContainerClient(
      const std::string& containerUri,
      const BlobContainerClientOptions& options)
      : m_containerUrl(containerUri)
  {
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> policies;
    policies.emplace_back(std::make_unique<Azure::Core::Http::TelemetryPolicy>(
        Details::c_BlobServicePackageName, BlobServiceVersion));
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

  BlobClient BlobContainerClient::GetBlobClient(const std::string& blobName) const
  {
    auto blobUri = m_containerUrl;
    blobUri.AppendPath(blobName);
    return BlobClient(std::move(blobUri), m_pipeline);
  }

  BlockBlobClient BlobContainerClient::GetBlockBlobClient(const std::string& blobName) const
  {
    return GetBlobClient(blobName).GetBlockBlobClient();
  }

  AppendBlobClient BlobContainerClient::GetAppendBlobClient(const std::string& blobName) const
  {
    return GetBlobClient(blobName).GetAppendBlobClient();
  }

  PageBlobClient BlobContainerClient::GetPageBlobClient(const std::string& blobName) const
  {
    return GetBlobClient(blobName).GetPageBlobClient();
  }

  Azure::Core::Response<BlobContainerInfo> BlobContainerClient::Create(
      const CreateBlobContainerOptions& options) const
  {
    BlobRestClient::Container::CreateOptions protocolLayerOptions;
    protocolLayerOptions.AccessType = options.AccessType;
    protocolLayerOptions.Metadata = options.Metadata;
    return BlobRestClient::Container::Create(
        options.Context, *m_pipeline, m_containerUrl.ToString(), protocolLayerOptions);
  }

  Azure::Core::Response<DeleteContainerInfo> BlobContainerClient::Delete(
      const DeleteBlobContainerOptions& options) const
  {
    BlobRestClient::Container::DeleteOptions protocolLayerOptions;
    protocolLayerOptions.LeaseId = options.AccessConditions.LeaseId;
    protocolLayerOptions.IfModifiedSince = options.AccessConditions.IfModifiedSince;
    protocolLayerOptions.IfUnmodifiedSince = options.AccessConditions.IfUnmodifiedSince;
    return BlobRestClient::Container::Delete(
        options.Context, *m_pipeline, m_containerUrl.ToString(), protocolLayerOptions);
  }

  Azure::Core::Response<BlobContainerProperties> BlobContainerClient::GetProperties(
      const GetBlobContainerPropertiesOptions& options) const
  {
    BlobRestClient::Container::GetPropertiesOptions protocolLayerOptions;
    protocolLayerOptions.LeaseId = options.AccessConditions.LeaseId;
    return BlobRestClient::Container::GetProperties(
        options.Context, *m_pipeline, m_containerUrl.ToString(), protocolLayerOptions);
  }

  Azure::Core::Response<BlobContainerInfo> BlobContainerClient::SetMetadata(
      std::map<std::string, std::string> metadata,
      SetBlobContainerMetadataOptions options) const
  {
    BlobRestClient::Container::SetMetadataOptions protocolLayerOptions;
    protocolLayerOptions.Metadata = metadata;
    protocolLayerOptions.LeaseId = options.AccessConditions.LeaseId;
    protocolLayerOptions.IfModifiedSince = options.AccessConditions.IfModifiedSince;
    return BlobRestClient::Container::SetMetadata(
        options.Context, *m_pipeline, m_containerUrl.ToString(), protocolLayerOptions);
  }

  Azure::Core::Response<BlobsFlatSegment> BlobContainerClient::ListBlobsFlat(
      const ListBlobsOptions& options) const
  {
    BlobRestClient::Container::ListBlobsFlatOptions protocolLayerOptions;
    protocolLayerOptions.Prefix = options.Prefix;
    protocolLayerOptions.Marker = options.Marker;
    protocolLayerOptions.MaxResults = options.MaxResults;
    protocolLayerOptions.Include = options.Include;
    return BlobRestClient::Container::ListBlobsFlat(
        options.Context, *m_pipeline, m_containerUrl.ToString(), protocolLayerOptions);
  }

  Azure::Core::Response<BlobsHierarchySegment> BlobContainerClient::ListBlobsByHierarchy(
      const std::string& delimiter,
      const ListBlobsOptions& options) const
  {
    BlobRestClient::Container::ListBlobsByHierarchyOptions protocolLayerOptions;
    protocolLayerOptions.Prefix = options.Prefix;
    protocolLayerOptions.Delimiter = delimiter;
    protocolLayerOptions.Marker = options.Marker;
    protocolLayerOptions.MaxResults = options.MaxResults;
    protocolLayerOptions.Include = options.Include;
    return BlobRestClient::Container::ListBlobsByHierarchy(
        options.Context, *m_pipeline, m_containerUrl.ToString(), protocolLayerOptions);
  }

  Azure::Core::Response<BlobContainerAccessPolicy> BlobContainerClient::GetAccessPolicy(
      const GetBlobContainerAccessPolicyOptions& options) const
  {
    BlobRestClient::Container::GetAccessPolicyOptions protocolLayerOptions;
    protocolLayerOptions.LeaseId = options.AccessConditions.LeaseId;
    return BlobRestClient::Container::GetAccessPolicy(
        options.Context, *m_pipeline, m_containerUrl.ToString(), protocolLayerOptions);
  }

  Azure::Core::Response<BlobContainerInfo> BlobContainerClient::SetAccessPolicy(
      const SetBlobContainerAccessPolicyOptions& options) const
  {
    BlobRestClient::Container::SetAccessPolicyOptions protocolLayerOptions;
    protocolLayerOptions.AccessType = options.AccessType;
    protocolLayerOptions.SignedIdentifiers = options.SignedIdentifiers;
    protocolLayerOptions.LeaseId = options.AccessConditions.LeaseId;
    protocolLayerOptions.IfModifiedSince = options.AccessConditions.IfModifiedSince;
    protocolLayerOptions.IfUnmodifiedSince = options.AccessConditions.IfUnmodifiedSince;
    return BlobRestClient::Container::SetAccessPolicy(
        options.Context, *m_pipeline, m_containerUrl.ToString(), protocolLayerOptions);
  }

}}} // namespace Azure::Storage::Blobs
