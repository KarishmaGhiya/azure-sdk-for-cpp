// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include "common/access_conditions.hpp"
#include "protocol/blob_rest_client.hpp"

#include <limits>
#include <string>
#include <utility>

namespace Azure { namespace Storage { namespace Blobs {

  /**
   * @brief Specifies access conditions for a container.
   */
  struct ContainerAccessConditions : public LastModifiedTimeAccessConditions,
                                     public LeaseAccessConditions
  {
  };

  /**
   * @brief Specifies access conditions for a blob.
   */
  struct BlobAccessConditions : public LastModifiedTimeAccessConditions,
                                public ETagAccessConditions,
                                public LeaseAccessConditions
  {
  };

  /**
   * @brief Specifies access conditions for a append blob.
   */
  struct AppendBlobAccessConditions : public BlobAccessConditions
  {
    /**
     * @brief Ensures that the AppendBlock operation succeeds only if the append blob's size
     * is less than or equal to this value.
     */
    Azure::Core::Nullable<int64_t> MaxSize;

    /**
     * @brief Ensures that the AppendBlock operation succeeds only if the append position is equal
     * to this value.
     */
    Azure::Core::Nullable<int64_t> AppendPosition;
  };

  /**
   * @brief Specifies access conditions for a page blob.
   */
  struct PageBlobAccessConditions : public BlobAccessConditions
  {
    /**
     * @brief IfSequenceNumberLessThan ensures that the page blob operation succeeds only if
     * the blob's sequence number is less than a value.
     */
    Azure::Core::Nullable<int64_t> IfSequenceNumberLessThan;

    /**
     * @brief IfSequenceNumberLessThanOrEqual ensures that the page blob operation succeeds
     * only if the blob's sequence number is less than or equal to a value.
     */
    Azure::Core::Nullable<int64_t> IfSequenceNumberLessThanOrEqual;

    /**
     * @brief IfSequenceNumberEqual ensures that the page blob operation succeeds only
     * if the blob's sequence number is equal to a value.
     */
    Azure::Core::Nullable<int64_t> IfSequenceNumberEqual;
  };

  /**
   * @brief Service client options used to initalize BlobServiceClient.
   */
  struct BlobServiceClientOptions
  {
    /**
     * @brief Transport pipeline policies for authentication, additional HTTP headers, etc., that
     * are applied to every request.
     */
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> PerOperationPolicies;

    /**
     * @brief Transport pipeline policies for authentication, additional HTTP headers, etc., that
     * are applied to every retrial.
     */
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> PerRetryPolicies;
  };

  /**
   * @brief Optional parameters for BlobServiceClient::ListBlobContainers.
   */
  struct ListBlobContainersOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Specifies a string that filters the results to return only containers whose
     * name begins with the specified prefix.
     */
    Azure::Core::Nullable<std::string> Prefix;

    /**
     * @brief A string value that identifies the portion of the list of containers to be
     * returned with the next listing operation. The operation returns a non-empty
     * ListContainersSegment.NextMarker value if the listing operation did not return all containers
     * remaining to be listed with the current segment. The NextMarker value can be used as the
     * value for the Marker parameter in a subsequent call to request the next segment of list
     * items.
     */
    Azure::Core::Nullable<std::string> Marker;

    /**
     * @brief Specifies the maximum number of containers to return.
     */
    Azure::Core::Nullable<int32_t> MaxResults;

    /**
     * @brief Specifies that the container's metadata be returned.
     */
    ListBlobContainersIncludeOption Include = ListBlobContainersIncludeOption::None;
  };

  /**
   * @brief Optional parameters for BlobServiceClient::GetUserDelegationKey.
   */
  struct GetUserDelegationKeyOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;
  };

  /**
   * @brief Optional parameters for BlobServiceClient::SetProperties.
   */
  struct SetBlobServicePropertiesOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;
  };

  /**
   * @brief Optional parameters for BlobServiceClient::GetProperties.
   */
  struct GetBlobServicePropertiesOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;
  };

  /**
   * @brief Optional parameters for BlobServiceClient::GetAccountInfo.
   */
  struct GetAccountInfoOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;
  };

  /**
   * @brief Optional parameters for BlobServiceClient::GetStatistics.
   */
  struct GetBlobServiceStatisticsOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;
  };

  /**
   * @brief Container client options used to initalize BlobContainerClient.
   */
  struct BlobContainerClientOptions
  {
    /**
     * @brief Transport pipeline policies for authentication, additional HTTP headers, etc., that
     * are applied to every request.
     */
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> PerOperationPolicies;

    /**
     * @brief Transport pipeline policies for authentication, additional HTTP headers, etc., that
     * are applied to every retrial.
     */
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> PerRetryPolicies;
  };

  /**
   * @brief Optional parameters for BlobContainerClient::Create.
   */
  struct CreateBlobContainerOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Specifies whether data in the container may be accessed publicly and the level
     * of access.
     */
    Azure::Core::Nullable<PublicAccessType> AccessType;

    /**
     * @brief Name-value pairs to associate with the container as metadata.
     */
    std::map<std::string, std::string> Metadata;
  };

  /**
   * @brief Optional parameters for BlobContainerClient::Delete.
   */
  struct DeleteBlobContainerOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    ContainerAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for BlobContainerClient::GetProperties.
   */
  struct GetBlobContainerPropertiesOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    LeaseAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for BlobContainerClient::SetMetadata.
   */
  struct SetBlobContainerMetadataOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    ContainerAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for BlobContainerClient::ListBlobsFlat.
   */
  struct ListBlobsOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Specifies a string that filters the results to return only blobs whose
     * name begins with the specified prefix.
     */
    Azure::Core::Nullable<std::string> Prefix;

    /**
     * @brief A string value that identifies the portion of the list of blobs to be
     * returned with the next listing operation. The operation returns a non-empty
     * BlobsFlatSegment.NextMarker value if the listing operation did not return all blobs
     * remaining to be listed with the current segment. The NextMarker value can be used as the
     * value for the Marker parameter in a subsequent call to request the next segment of list
     * items.
     */
    Azure::Core::Nullable<std::string> Marker;

    /**
     * @brief Specifies the maximum number of blobs to return.
     */
    Azure::Core::Nullable<int32_t> MaxResults;

    /**
     * @brief Specifies one or more datasets to include in the response.
     */
    ListBlobsIncludeItem Include = ListBlobsIncludeItem::None;
  };

  /**
   * @brief Optional parameters for BlobContainerClient::GetAccessPolicy.
   */
  struct GetBlobContainerAccessPolicyOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    LeaseAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for BlobContainerClient::SetAccessPolicy.
   */
  struct SetBlobContainerAccessPolicyOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Specifies whether data in the container may be accessed publicly and the level
     * of access.
     */
    Azure::Core::Nullable<PublicAccessType> AccessType;

    /**
     * @brief Stored access policies that you can use to provide fine grained control over
     * container permissions.
     */
    std::vector<BlobSignedIdentifier> SignedIdentifiers;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    ContainerAccessConditions AccessConditions;
  };

  /**
   * @brief Blob client options used to initalize BlobClient.
   */
  struct BlobClientOptions
  {
    /**
     * @brief Transport pipeline policies for authentication, additional HTTP headers, etc., that
     * are applied to every request.
     */
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> PerOperationPolicies;

    /**
     * @brief Transport pipeline policies for authentication, additional HTTP headers, etc., that
     * are applied to every retrial.
     */
    std::vector<std::unique_ptr<Azure::Core::Http::HttpPolicy>> PerRetryPolicies;
  };

  /**
   * @brief Block blob client options used to initalize BlockBlobClient.
   */
  struct BlockBlobClientOptions : public BlobClientOptions
  {
  };

  /**
   * @brief Append blob client options used to initalize AppendBlobClient.
   */
  struct AppendBlobClientOptions : public BlobClientOptions
  {
  };

  /**
   * @brief Page blob client options used to initalize PageBlobClient.
   */
  struct PageBlobClientOptions : public BlobClientOptions
  {
  };

  /**
   * @brief Optional parameters for BlobClient::GetProperties.
   */
  struct GetBlobPropertiesOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    BlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for BlobClient::SetHttpHeaders.
   */
  struct SetBlobHttpHeadersOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    BlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for BlobClient::SetMetadata.
   */
  struct SetBlobMetadataOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    BlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for BlobClient::SetAccessTier.
   */
  struct SetAccessTierOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @beirf Indicates the priority with which to rehydrate an archived blob. The priority
     * can be set on a blob only once. This header will be ignored on subsequent requests to the
     * same blob.
     */
    Azure::Core::Nullable<Blobs::RehydratePriority> RehydratePriority;
  };

  /**
   * @brief Optional parameters for BlobClient::StartCopyFromUri.
   */
  struct StartCopyFromUriOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Specifies user-defined name-value pairs associated with the blob. If no
     * name-value pairs are specified, the operation will copy the metadata from the source blob or
     * file to the destination blob. If one or more name-value pairs are specified, the destination
     * blob is created with the specified metadata, and metadata is not copied from the source blob
     * or file.
     */
    std::map<std::string, std::string> Metadata;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    BlobAccessConditions AccessConditions;

    /**
     * @brief Optional conditions that the source must meet to perform this operation.
     */
    BlobAccessConditions SourceConditions;

    /**
     * @brief Specifies the tier to be set on the target blob.
     */
    Azure::Core::Nullable<AccessTier> Tier = AccessTier::Unknown;

    /**
     * @beirf Indicates the priority with which to rehydrate an archived blob. The priority
     * can be set on a blob only once. This header will be ignored on subsequent requests to the
     * same blob.
     */
    Azure::Core::Nullable<Blobs::RehydratePriority> RehydratePriority;
  };

  /**
   * @brief Optional parameters for BlobClient::AbortCopyFromUri.
   */
  struct AbortCopyFromUriOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    LeaseAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for BlobClient::Download.
   */
  struct DownloadBlobOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Downloads only the bytes of the blob from this offset.
     */
    Azure::Core::Nullable<int64_t> Offset;

    /**
     * @brief Returns at most this number of bytes of the blob from the offset. Null means
     * download until the end.
     */
    Azure::Core::Nullable<int64_t> Length;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    BlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for BlobClient::DownloadToBuffer.
   */
  struct DownloadBlobToBufferOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Downloads only the bytes of the blob from this offset.
     */
    Azure::Core::Nullable<int64_t> Offset;

    /**
     * @brief Returns at most this number of bytes of the blob from the offset. Null means
     * download until the end.
     */
    Azure::Core::Nullable<int64_t> Length;

    /**
     * @brief The size of the first range request in bytes. Blobs smaller than this limit will be
     * downloaded in a single request. Blobs larger than this limit will continue being downloaded
     * in chunks of size ChunkSize.
     */
    Azure::Core::Nullable<int64_t> InitialChunkSize;

    /**
     * @brief The maximum number of bytes in a single request.
     */
    Azure::Core::Nullable<int64_t> ChunkSize;

    /**
     * @brief The maximum number of threads that may be used in a parallel transfer.
     */
    int Concurrency = 1;
  };

  /**
   * @brief Optional parameters for BlobClient::DownloadToFile.
   */
  using DownloadBlobToFileOptions = DownloadBlobToBufferOptions;

  /**
   * @brief Optional parameters for BlobClient::CreateSnapshot.
   */
  struct CreateSnapshotOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Specifies user-defined name-value pairs associated with the blob. If no
     * name-value pairs are specified, the operation will copy the base blob metadata to the
     * snapshot. If one or more name-value pairs are specified, the snapshot is created with the
     * specified metadata, and metadata is not copied from the base blob.
     */
    std::map<std::string, std::string> Metadata;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    BlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for BlobClient::Delete.
   */
  struct DeleteBlobOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Specifies to delete either the base blob
     * and all of its snapshots, or only the blob's snapshots and not the blob itself. Required if
     * the blob has associated snapshots.
     */
    Azure::Core::Nullable<DeleteSnapshotsOption> DeleteSnapshots;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    BlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for BlobClient::Undelete.
   */
  struct UndeleteBlobOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;
  };

  /**
   * @brief Optional parameters for BlockBlobClient::Upload.
   */
  struct UploadBlockBlobOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief An MD5 hash of the blob content. This hash is used to verify the integrity of
     * the blob during transport. When this header is specified, the storage service checks the hash
     * that has arrived with the one that was sent.
     */
    Azure::Core::Nullable<std::string> ContentMd5;

    /**
     * @brief A CRC64 hash of the blob content. This hash is used to verify the integrity of
     * the blob during transport. When this header is specified, the storage service checks the hash
     * that has arrived with the one that was sent.
     */
    Azure::Core::Nullable<std::string> ContentCrc64;

    /**
     * @brief The standard HTTP header system properties to set.
     */
    BlobHttpHeaders HttpHeaders;

    /**
     * @brief Name-value pairs associated with the blob as metadata.
     */
    std::map<std::string, std::string> Metadata;

    /**
     * @brief Indicates the tier to be set on blob.
     */
    Azure::Core::Nullable<AccessTier> Tier;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    BlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for BlockBlobClient::UploadFromBuffer.
   */
  struct UploadBlobOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief The standard HTTP header system properties to set.
     */
    BlobHttpHeaders HttpHeaders;

    /**
     * @brief Name-value pairs associated with the blob as metadata.
     */
    std::map<std::string, std::string> Metadata;

    /**
     * @brief Indicates the tier to be set on blob.
     */
    Azure::Core::Nullable<AccessTier> Tier;

    /**
     * @brief The maximum number of bytes in a single request.
     */
    Azure::Core::Nullable<int64_t> ChunkSize;

    /**
     * @brief The maximum number of threads that may be used in a parallel transfer.
     */
    int Concurrency = 1;
  };

  /**
   * @brief Optional parameters for BlockBlobClient::StageBlock.
   */
  struct StageBlockOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief An MD5 hash of the blob content. This hash is used to verify the integrity of
     * the blob during transport. When this header is specified, the storage service checks the hash
     * that has arrived with the one that was sent.
     */
    Azure::Core::Nullable<std::string> ContentMd5;

    /**
     * @brief A CRC64 hash of the blob content. This hash is used to verify the integrity of
     * the blob during transport. When this header is specified, the storage service checks the hash
     * that has arrived with the one that was sent.
     */
    Azure::Core::Nullable<std::string> ContentCrc64;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    LeaseAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for BlockBlobClient::StageBlockFromUri.
   */
  struct StageBlockFromUriOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Uploads only the bytes of the source blob from this offset.
     */
    Azure::Core::Nullable<int64_t> SourceOffset;

    /**
     * @brief Uploads this number of bytes of the source blob from the offset. Null means
     * upload until the end.
     */
    Azure::Core::Nullable<int64_t> SourceLength;

    /**
     * @brief An MD5 hash of the blob content. This hash is used to verify the integrity of
     * the blob during transport. When this header is specified, the storage service checks the hash
     * that has arrived with the one that was sent.
     */
    Azure::Core::Nullable<std::string> ContentMd5;

    /**
     * @brief A CRC64 hash of the blob content. This hash is used to verify the integrity of
     * the blob during transport. When this header is specified, the storage service checks the hash
     * that has arrived with the one that was sent.
     */
    Azure::Core::Nullable<std::string> ContentCrc64;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    LeaseAccessConditions AccessConditions;

    /**
     * @brief Optional conditions that the source must meet to perform this operation.
     */
    BlobAccessConditions SourceConditions;
  };

  /**
   * @brief Optional parameters for BlockBlobClient::CommitBlockList.
   */
  struct CommitBlockListOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief The standard HTTP header system properties to set.
     */
    BlobHttpHeaders HttpHeaders;

    /**
     * @brief Name-value pairs associated with the blob as metadata.
     */
    std::map<std::string, std::string> Metadata;

    /**
     * @brief Indicates the tier to be set on blob.
     */
    Azure::Core::Nullable<AccessTier> Tier;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    BlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for BlockBlobClient::GetBlockList.
   */
  struct GetBlockListOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Specifies whether to return the list of committed blocks, the list of uncommitted
     * blocks, or both lists together.
     */
    Azure::Core::Nullable<BlockListTypeOption> ListType;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    LeaseAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for AppendBlobClient::Create.
   */
  struct CreateAppendBlobOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief The standard HTTP header system properties to set.
     */
    BlobHttpHeaders HttpHeaders;

    /**
     * @brief Name-value pairs associated with the blob as metadata.
     */
    std::map<std::string, std::string> Metadata;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    BlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for AppendBlobClient::AppendBlock.
   */
  struct AppendBlockOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief An MD5 hash of the blob content. This hash is used to verify the integrity of
     * the blob during transport. When this header is specified, the storage service checks the hash
     * that has arrived with the one that was sent.
     */
    Azure::Core::Nullable<std::string> ContentMd5;

    /**
     * @brief A CRC64 hash of the blob content. This hash is used to verify the integrity of
     * the blob during transport. When this header is specified, the storage service checks the hash
     * that has arrived with the one that was sent.
     */
    Azure::Core::Nullable<std::string> ContentCrc64;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    AppendBlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for AppendBlobClient::AppendBlockFromUri.
   */
  struct AppendBlockFromUriOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Uploads only the bytes of the source blob from this offset.
     */
    Azure::Core::Nullable<int64_t> SourceOffset;

    /**
     * @brief Uploads this number of bytes of the source blob from the offset. Null means
     * upload until the end.
     */
    Azure::Core::Nullable<int64_t> SourceLength;

    /**
     * @brief An MD5 hash of the blob content. This hash is used to verify the integrity of
     * the blob during transport. When this header is specified, the storage service checks the hash
     * that has arrived with the one that was sent.
     */
    Azure::Core::Nullable<std::string> ContentMd5;

    /**
     * @brief A CRC64 hash of the blob content. This hash is used to verify the integrity of
     * the blob during transport. When this header is specified, the storage service checks the hash
     * that has arrived with the one that was sent.
     */
    Azure::Core::Nullable<std::string> ContentCrc64;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    AppendBlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for PageBlobClient::Create.
   */
  struct CreatePageBlobOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief The sequence number is a user-controlled value that you can use to track requests. The
     * value of the sequence number must be between 0 and 2^63 - 1.
     */
    Azure::Core::Nullable<int64_t> SequenceNumber;

    /**
     * @brief The standard HTTP header system properties to set.
     */
    BlobHttpHeaders HttpHeaders;

    /**
     * @brief Name-value pairs associated with the blob as metadata.
     */
    std::map<std::string, std::string> Metadata;

    /**
     * @brief Indicates the tier to be set on blob.
     */
    Azure::Core::Nullable<AccessTier> Tier;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    BlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for PageBlobClient::UploadPages.
   */
  struct UploadPagesOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief An MD5 hash of the blob content. This hash is used to verify the integrity of
     * the blob during transport. When this header is specified, the storage service checks the hash
     * that has arrived with the one that was sent.
     */
    Azure::Core::Nullable<std::string> ContentMd5;

    /**
     * @brief A CRC64 hash of the blob content. This hash is used to verify the integrity of
     * the blob during transport. When this header is specified, the storage service checks the hash
     * that has arrived with the one that was sent.
     */
    Azure::Core::Nullable<std::string> ContentCrc64;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    PageBlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for PageBlobClient::UploadPagesFromUri.
   */
  struct UploadPagesFromUriOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief An MD5 hash of the blob content. This hash is used to verify the integrity of
     * the blob during transport. When this header is specified, the storage service checks the hash
     * that has arrived with the one that was sent.
     */
    Azure::Core::Nullable<std::string> ContentMd5;

    /**
     * @brief A CRC64 hash of the blob content. This hash is used to verify the integrity of
     * the blob during transport. When this header is specified, the storage service checks the hash
     * that has arrived with the one that was sent.
     */
    Azure::Core::Nullable<std::string> ContentCrc64;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    PageBlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for PageBlobClient::ClearPages.
   */
  struct ClearPagesOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    PageBlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for PageBlobClient::Resize.
   */
  struct ResizePageBlobOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    BlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for PageBlobClient::GetPageRanges.
   */
  struct GetPageRangesOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Specifies that the response will contain only pages that were changed between
     * target blob and previous snapshot. Changed pages include both updated and cleared pages.
     * The target blob may be a snapshot, as long as the snapshot specified by PreviousSnapshot is
     * the older of the two.
     */
    Azure::Core::Nullable<std::string> PreviousSnapshot;

    /**
     * @brief This parameter only works with managed disk storage accounts. Specifies that
     * the response will contain only pages that were changed between target blob and previous
     * snapshot. Changed pages include both updated and cleared pages. The target blob may be a
     * snapshot, as long as the snapshot specified by PreviousSnapshotUrl is the older of the two.
     */
    Azure::Core::Nullable<std::string> PreviousSnapshotUrl;

    /**
     * @brief Optionally specifies the offset of range over which to list ranges. This offset must
     * be a modulus of 512.
     */
    Azure::Core::Nullable<int64_t> Offset;

    /**
     * @brief Optionally specifies the length of range over which to list ranges. The length must be
     * a modulus of 512.
     */
    Azure::Core::Nullable<int64_t> Length;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    BlobAccessConditions AccessConditions;
  };

  /**
   * @brief Optional parameters for PageBlobClient::StartCopyIncremental.
   */
  struct IncrementalCopyPageBlobOptions
  {
    /**
     * @brief Context for cancelling long running operations.
     */
    Azure::Core::Context Context;

    /**
     * @brief Optional conditions that must be met to perform this operation.
     */
    BlobAccessConditions AccessConditions;
  };

}}} // namespace Azure::Storage::Blobs
