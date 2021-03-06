// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include "common/storage_credential.hpp"
#include "common/storage_uri_builder.hpp"
#include "credentials/credentials.hpp"
#include "http/pipeline.hpp"
#include "protocol/share_rest_client.hpp"
#include "response.hpp"
#include "share_options.hpp"
#include "share_responses.hpp"

#include <memory>
#include <string>

namespace Azure { namespace Storage { namespace Files { namespace Shares {

  class ShareClient;

  class ServiceClient {
  public:
    /**
     * @brief Create from connection string
     * @param connectionString Azure Storage connection string.
     * @param options Optional parameters used to initialize the client.
     * @return ServiceClient
     */
    static ServiceClient CreateFromConnectionString(
        const std::string& connectionString,
        const ServiceClientOptions& options = ServiceClientOptions());

    /**
     * @brief Shared key authentication client.
     * @param serviceUri The service URI this client's request targets.
     * @param credential The shared key credential used to initialize the client.
     * @param options Optional parameters used to initialize the client.
     */
    explicit ServiceClient(
        const std::string& serviceUri,
        std::shared_ptr<SharedKeyCredential> credential,
        const ServiceClientOptions& options = ServiceClientOptions());

    /**
     * @brief Bearer token authentication client.
     * @param serviceUri The service URI this client's request targets.
     * @param credential The token credential used to initialize the client.
     * @param options Optional parameters used to initialize the client.
     */
    explicit ServiceClient(
        const std::string& serviceUri,
        std::shared_ptr<Core::Credentials::TokenCredential> credential,
        const ServiceClientOptions& options = ServiceClientOptions());

    /**
     * @brief Anonymous/SAS/customized pipeline auth.
     * @param serviceUri The service URI this client's request targets.
     * @param options Optional parameters used to initialize the client.
     */
    explicit ServiceClient(
        const std::string& serviceUri,
        const ServiceClientOptions& options = ServiceClientOptions());

    /**
     * @brief Create a ShareClient from current ServiceClient
     * @param shareName The name of the file share.
     * @return ShareClient A share client that can be used to manage a share resource.
     */
    ShareClient GetShareClient(const std::string& shareName) const;

    /**
     * @brief Gets the file share service's primary uri endpoint.
     *
     * @return The file share service's primary uri endpoint.
     */
    std::string GetUri() const { return m_serviceUri.ToString(); }

    /**
     * @brief List the shares from the service.
     * @param options Optional parameters to list the shares.
     * @return Azure::Core::Response<ListSharesSegmentResult> The results containing the shares
     * returned and information used for future list operation on valid result not yet returned.
     */
    Azure::Core::Response<ListSharesSegmentResult> ListSharesSegment(
        const ListSharesOptions& options = ListSharesOptions()) const;

    /**
     * @brief Set the service's properties.
     * @param properties The properties of the service that is to be set.
     * @param options Optional parameters to set the properties of the service.
     * @return Azure::Core::Response<ServiceProperties> The service's properties.
     */
    Azure::Core::Response<SetServicePropertiesInfo> SetProperties(
        StorageServiceProperties properties,
        const SetServicePropertiesOptions& options = SetServicePropertiesOptions()) const;

    /**
     * @brief Get the service's properties.
     * @param options Optional parameters to get the properties of the service.
     * @return Azure::Core::Response<ServiceProperties> The service's properties.
     */
    Azure::Core::Response<StorageServiceProperties> GetProperties(
        const GetServicePropertiesOptions& options = GetServicePropertiesOptions()) const;

  private:
    UriBuilder m_serviceUri;
    std::shared_ptr<Azure::Core::Http::HttpPipeline> m_pipeline;
  };
}}}} // namespace Azure::Storage::Files::Shares
