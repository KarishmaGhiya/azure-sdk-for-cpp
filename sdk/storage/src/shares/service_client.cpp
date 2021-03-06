// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#include "shares/service_client.hpp"

#include "common/common_headers_request_policy.hpp"
#include "common/constants.hpp"
#include "common/shared_key_policy.hpp"
#include "common/storage_common.hpp"
#include "common/storage_credential.hpp"
#include "common/storage_version.hpp"
#include "credentials/policy/policies.hpp"
#include "http/curl/curl.hpp"
#include "shares/share_client.hpp"

namespace Azure { namespace Storage { namespace Files { namespace Shares {
  ServiceClient ServiceClient::CreateFromConnectionString(
      const std::string& connectionString,
      const ServiceClientOptions& options)
  {
    auto parsedConnectionString = Azure::Storage::Details::ParseConnectionString(connectionString);
    auto serviceUri = std::move(parsedConnectionString.FileServiceUri);

    if (parsedConnectionString.KeyCredential)
    {
      return ServiceClient(serviceUri.ToString(), parsedConnectionString.KeyCredential, options);
    }
    else
    {
      return ServiceClient(serviceUri.ToString(), options);
    }
  }

  ServiceClient::ServiceClient(
      const std::string& serviceUri,
      std::shared_ptr<SharedKeyCredential> credential,
      const ServiceClientOptions& options)
      : m_serviceUri(serviceUri)
  {
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> policies;
    policies.emplace_back(std::make_unique<Azure::Core::Http::TelemetryPolicy>(
        Azure::Storage::Details::c_FileServicePackageName, FileServiceVersion));
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

  ServiceClient::ServiceClient(
      const std::string& serviceUri,
      std::shared_ptr<Core::Credentials::TokenCredential> credential,
      const ServiceClientOptions& options)
      : m_serviceUri(serviceUri)
  {
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> policies;
    policies.emplace_back(std::make_unique<Azure::Core::Http::TelemetryPolicy>(
        Azure::Storage::Details::c_FileServicePackageName, FileServiceVersion));
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

  ServiceClient::ServiceClient(const std::string& serviceUri, const ServiceClientOptions& options)
      : m_serviceUri(serviceUri)
  {
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> policies;
    policies.emplace_back(std::make_unique<Azure::Core::Http::TelemetryPolicy>(
        Azure::Storage::Details::c_FileServicePackageName, FileServiceVersion));
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

  ShareClient ServiceClient::GetShareClient(const std::string& shareName) const
  {
    auto builder = m_serviceUri;
    builder.AppendPath(shareName, true);
    return ShareClient(builder, m_pipeline);
  }

  Azure::Core::Response<ListSharesSegmentResult> ServiceClient::ListSharesSegment(
      const ListSharesOptions& options) const
  {
    auto protocolLayerOptions = ShareRestClient::Service::ListSharesSegmentOptions();
    protocolLayerOptions.ListSharesInclude = options.ListSharesInclude;
    protocolLayerOptions.Marker = options.Marker;
    protocolLayerOptions.MaxResults = options.MaxResults;
    protocolLayerOptions.Prefix = options.Prefix;
    return ShareRestClient::Service::ListSharesSegment(
        m_serviceUri.ToString(), *m_pipeline, options.Context, protocolLayerOptions);
  }

  Azure::Core::Response<SetServicePropertiesInfo> ServiceClient::SetProperties(
      StorageServiceProperties properties,
      const SetServicePropertiesOptions& options) const
  {
    auto protocolLayerOptions = ShareRestClient::Service::SetPropertiesOptions();
    protocolLayerOptions.ServiceProperties = std::move(properties);
    return ShareRestClient::Service::SetProperties(
        m_serviceUri.ToString(), *m_pipeline, options.Context, protocolLayerOptions);
  }

  Azure::Core::Response<StorageServiceProperties> ServiceClient::GetProperties(
      const GetServicePropertiesOptions& options) const
  {
    auto protocolLayerOptions = ShareRestClient::Service::GetPropertiesOptions();
    auto result = ShareRestClient::Service::GetProperties(
        m_serviceUri.ToString(), *m_pipeline, options.Context, protocolLayerOptions);
    StorageServiceProperties ret;
    ret.Cors = std::move(result->Cors);
    ret.HourMetrics = std::move(result->HourMetrics);
    ret.MinuteMetrics = std::move(result->MinuteMetrics);
    return Azure::Core::Response<StorageServiceProperties>(
        std::move(ret), result.ExtractRawResponse());
  }

}}}} // namespace Azure::Storage::Files::Shares
