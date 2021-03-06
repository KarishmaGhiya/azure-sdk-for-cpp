
// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include "common/storage_error.hpp"
#include "common/xml_wrapper.hpp"
#include "http/http.hpp"
#include "http/pipeline.hpp"
#include "json.hpp"
#include "nullable.hpp"
#include "response.hpp"

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace Azure { namespace Storage { namespace Files { namespace Shares {

  namespace Details {
    constexpr static const char* c_DefaultServiceApiVersion = "2019-12-12";
    constexpr static const char* c_QueryCopyId = "copyid";
    constexpr static const char* c_QueryListSharesInclude = "include";
    constexpr static const char* c_QueryMarker = "marker";
    constexpr static const char* c_QueryMaxResults = "maxresults";
    constexpr static const char* c_QueryPrefix = "prefix";
    constexpr static const char* c_QueryShareSnapshot = "sharesnapshot";
    constexpr static const char* c_QueryTimeout = "timeout";
    constexpr static const char* c_QueryRestype = "restype";
    constexpr static const char* c_QueryComp = "comp";
    constexpr static const char* c_HeaderVersion = "x-ms-version";
    constexpr static const char* c_HeaderRequestId = "x-ms-client-request-id";
    constexpr static const char* c_HeaderContentLength = "content-length";
    constexpr static const char* c_HeaderContentMD5 = "content-md5";
    constexpr static const char* c_HeaderCopyActionAbortConstant = "x-ms-copy-action";
    constexpr static const char* c_HeaderCopySource = "x-ms-copy-source";
    constexpr static const char* c_HeaderFilePermissionCopyMode = "x-ms-file-permission-copy-mode";
    constexpr static const char* c_HeaderIgnoreReadOnly = "x-ms-file-copy-ignore-read-only";
    constexpr static const char* c_HeaderFileAttributes = "x-ms-file-attributes";
    constexpr static const char* c_HeaderFileCreationTime = "x-ms-file-creation-time";
    constexpr static const char* c_HeaderFileLastWriteTime = "x-ms-file-last-write-time";
    constexpr static const char* c_HeaderSetArchiveAttribute = "x-ms-file-copy-set-archive";
    constexpr static const char* c_HeaderDeletedShareName = "x-ms-deleted-share-name";
    constexpr static const char* c_HeaderDeletedShareVersion = "x-ms-deleted-share-version";
    constexpr static const char* c_HeaderDeleteSnapshots = "x-ms-delete-snapshots";
    constexpr static const char* c_HeaderFileCacheControl = "x-ms-cache-control";
    constexpr static const char* c_HeaderFileContentDisposition = "x-ms-content-disposition";
    constexpr static const char* c_HeaderFileContentEncoding = "x-ms-content-encoding";
    constexpr static const char* c_HeaderFileContentLanguage = "x-ms-content-language";
    constexpr static const char* c_HeaderFileContentMD5 = "x-ms-content-md5";
    constexpr static const char* c_HeaderFileContentType = "x-ms-content-type";
    constexpr static const char* c_HeaderFilePermission = "x-ms-file-permission";
    constexpr static const char* c_HeaderFilePermissionKey = "x-ms-file-permission-key";
    constexpr static const char* c_HeaderFileRangeWriteFromUrl = "x-ms-write";
    constexpr static const char* c_HeaderFileRangeWriteFromUrlDefault = "update";
    constexpr static const char* c_HeaderFileTypeConstant = "x-ms-type";
    constexpr static const char* c_HeaderRangeGetContentMD5 = "x-ms-range-get-content-md5";
    constexpr static const char* c_HeaderHandleId = "x-ms-handle-id";
    constexpr static const char* c_HeaderDuration = "x-ms-lease-duration";
    constexpr static const char* c_HeaderLeaseId = "x-ms-lease-id";
    constexpr static const char* c_HeaderMetadata = "x-ms-meta";
    constexpr static const char* c_HeaderProposedLeaseId = "x-ms-proposed-lease-id";
    constexpr static const char* c_HeaderRange = "x-ms-range";
    constexpr static const char* c_HeaderRecursive = "x-ms-recursive";
    constexpr static const char* c_HeaderQuota = "x-ms-share-quota";
    constexpr static const char* c_HeaderSourceContentCrc64 = "x-ms-source-content-crc64";
    constexpr static const char* c_HeaderSourceIfMatchCrc64 = "x-ms-source-if-match-crc64";
    constexpr static const char* c_HeaderSourceIfNoneMatchCrc64 = "x-ms-source-if-none-match-crc64";
    constexpr static const char* c_HeaderSourceRange = "x-ms-source-range";
    constexpr static const char* c_HeaderErrorCode = "x-ms-error-code";
    constexpr static const char* c_HeaderETag = "etag";
    constexpr static const char* c_HeaderLastModified = "last-modified";
    constexpr static const char* c_HeaderDate = "date";
    constexpr static const char* c_HeaderProvisionedIops = "x-ms-share-provisioned-iops";
    constexpr static const char* c_HeaderProvisionedIngressMBps
        = "x-ms-share-provisioned-ingress-mbps";
    constexpr static const char* c_HeaderProvisionedEgressMBps
        = "x-ms-share-provisioned-egress-mbps";
    constexpr static const char* c_HeaderNextAllowedQuotaDowngradeTime
        = "x-ms-share-next-allowed-quota-downgrade-time";
    constexpr static const char* c_HeaderSnapshot = "x-ms-snapshot";
    constexpr static const char* c_HeaderClientRequestId = "x-ms-client-request-id";
    constexpr static const char* c_HeaderIsServerEncrypted = "x-ms-request-server-encrypted";
    constexpr static const char* c_HeaderFileChangeTime = "x-ms-file-change-time";
    constexpr static const char* c_HeaderFileId = "x-ms-file-id";
    constexpr static const char* c_HeaderFileParentId = "x-ms-file-parent-id";
    constexpr static const char* c_HeaderContentType = "content-type";
    constexpr static const char* c_HeaderMarker = "x-ms-marker";
    constexpr static const char* c_HeaderNumberOfHandlesClosed = "x-ms-number-of-handles-closed";
    constexpr static const char* c_HeaderNumberOfHandlesFailedToClose
        = "x-ms-number-of-handles-failed";
    constexpr static const char* c_HeaderFileContentLength = "x-ms-content-length";
    constexpr static const char* c_HeaderContentRange = "content-range";
    constexpr static const char* c_HeaderContentEncoding = "content-encoding";
    constexpr static const char* c_HeaderCacheControl = "cache-control";
    constexpr static const char* c_HeaderContentDisposition = "content-disposition";
    constexpr static const char* c_HeaderContentLanguage = "content-language";
    constexpr static const char* c_HeaderAcceptRanges = "accept-ranges";
    constexpr static const char* c_HeaderCopyCompletionTime = "x-ms-copy-completion-time";
    constexpr static const char* c_HeaderCopyStatusDescription = "x-ms-copy-status-description";
    constexpr static const char* c_HeaderCopyId = "x-ms-copy-id";
    constexpr static const char* c_HeaderCopyProgress = "x-ms-copy-progress";
    constexpr static const char* c_HeaderCopyStatus = "x-ms-copy-status";
    constexpr static const char* c_HeaderLeaseDuration = "x-ms-lease-duration";
    constexpr static const char* c_HeaderLeaseState = "x-ms-lease-state";
    constexpr static const char* c_HeaderLeaseStatus = "x-ms-lease-status";
    constexpr static const char* c_HeaderFileType = "x-ms-type";
    constexpr static const char* c_HeaderAction = "x-ms-lease-action";
    constexpr static const char* c_HeaderFileRangeWrite = "x-ms-write";
    constexpr static const char* c_HeaderFileRangeWriteTypeDefault = "update";
    constexpr static const char* c_HeaderXMsContentCrc64 = "x-ms-content-crc64";
  } // namespace Details

  enum class ListSharesIncludeType
  {
    None = 0,
    Snapshots = 1,
    Metadata = 2,
    Deleted = 4,

  };

  inline ListSharesIncludeType operator|(ListSharesIncludeType lhs, ListSharesIncludeType rhs)
  {
    using type = std::underlying_type_t<ListSharesIncludeType>;
    return static_cast<ListSharesIncludeType>(static_cast<type>(lhs) | static_cast<type>(rhs));
  }

  inline ListSharesIncludeType& operator|=(ListSharesIncludeType& lhs, ListSharesIncludeType rhs)
  {
    lhs = lhs | rhs;
    return lhs;
  }

  inline ListSharesIncludeType operator&(ListSharesIncludeType lhs, ListSharesIncludeType rhs)
  {
    using type = std::underlying_type_t<ListSharesIncludeType>;
    return static_cast<ListSharesIncludeType>(static_cast<type>(lhs) & static_cast<type>(rhs));
  }

  inline ListSharesIncludeType& operator&=(ListSharesIncludeType& lhs, ListSharesIncludeType rhs)
  {
    lhs = lhs & rhs;
    return lhs;
  }
  inline std::string ListSharesIncludeTypeToString(const ListSharesIncludeType& val)
  {
    ListSharesIncludeType value_list[] = {
        ListSharesIncludeType::Snapshots,
        ListSharesIncludeType::Metadata,
        ListSharesIncludeType::Deleted,
    };
    const char* string_list[] = {
        "snapshots",
        "metadata",
        "deleted",
    };
    std::string result;
    for (std::size_t i = 0; i < sizeof(value_list) / sizeof(ListSharesIncludeType); ++i)
    {
      if ((val & value_list[i]) == value_list[i])
      {
        if (!result.empty())
        {
          result += ",";
        }
        result += string_list[i];
      }
    }
    return result;
  }

  struct FileShareHttpHeaders
  {
    std::string CacheControl;
    std::string ContentDisposition;
    std::string ContentEncoding;
    std::string ContentLanguage;
    std::string ContentType;
  };
  // Specifies the option to copy file security descriptor from source file or to set it using the
  // value which is defined by the header value of x-ms-file-permission or x-ms-file-permission-key.
  enum class PermissionCopyModeType
  {
    Source,
    Override,
    Unknown
  };

  inline std::string PermissionCopyModeTypeToString(
      const PermissionCopyModeType& permissionCopyModeType)
  {
    switch (permissionCopyModeType)
    {
      case PermissionCopyModeType::Source:
        return "source";
      case PermissionCopyModeType::Override:
        return "override";
      default:
        return std::string();
    }
  }

  inline PermissionCopyModeType PermissionCopyModeTypeFromString(
      const std::string& permissionCopyModeType)
  {
    if (permissionCopyModeType == "source")
    {
      return PermissionCopyModeType::Source;
    }
    if (permissionCopyModeType == "override")
    {
      return PermissionCopyModeType::Override;
    }
    throw std::runtime_error(
        "Cannot convert " + permissionCopyModeType + " to PermissionCopyModeType");
  }

  // Specifies the option include to delete the base share and all of its snapshots.
  enum class DeleteSnapshotsOptionType
  {
    Include,
    Unknown
  };

  inline std::string DeleteSnapshotsOptionTypeToString(
      const DeleteSnapshotsOptionType& deleteSnapshotsOptionType)
  {
    switch (deleteSnapshotsOptionType)
    {
      case DeleteSnapshotsOptionType::Include:
        return "include";
      default:
        return std::string();
    }
  }

  inline DeleteSnapshotsOptionType DeleteSnapshotsOptionTypeFromString(
      const std::string& deleteSnapshotsOptionType)
  {
    if (deleteSnapshotsOptionType == "include")
    {
      return DeleteSnapshotsOptionType::Include;
    }
    throw std::runtime_error(
        "Cannot convert " + deleteSnapshotsOptionType + " to DeleteSnapshotsOptionType");
  }

  // Only update is supported: - Update: Writes the bytes downloaded from the source url into the
  // specified range.
  enum class FileRangeWriteFromUrlType
  {
    Update,
    Unknown
  };

  inline std::string FileRangeWriteFromUrlTypeToString(
      const FileRangeWriteFromUrlType& fileRangeWriteFromUrlType)
  {
    switch (fileRangeWriteFromUrlType)
    {
      case FileRangeWriteFromUrlType::Update:
        return "update";
      default:
        return std::string();
    }
  }

  inline FileRangeWriteFromUrlType FileRangeWriteFromUrlTypeFromString(
      const std::string& fileRangeWriteFromUrlType)
  {
    if (fileRangeWriteFromUrlType == "update")
    {
      return FileRangeWriteFromUrlType::Update;
    }
    throw std::runtime_error(
        "Cannot convert " + fileRangeWriteFromUrlType + " to FileRangeWriteFromUrlType");
  }

  // An Access policy.
  struct AccessPolicy
  {
    std::string Start; // The date-time the policy is active.
    std::string Expiry; // The date-time the policy expires.
    std::string Permission; // The permissions for the ACL policy.
  };

  // CORS is an HTTP feature that enables a web application running under one domain to access
  // resources in another domain. Web browsers implement a security restriction known as same-origin
  // policy that prevents a web page from calling APIs in a different domain; CORS provides a secure
  // way to allow one domain (the origin domain) to call APIs in another domain.
  struct CorsRule
  {
    std::string AllowedOrigins; // The origin domains that are permitted to make a request against
                                // the storage service via CORS. The origin domain is the domain
                                // from which the request originates. Note that the origin must be
                                // an exact case-sensitive match with the origin that the user age
                                // sends to the service. You can also use the wildcard character '*'
                                // to allow all origin domains to make requests via CORS.
    std::string AllowedMethods; // The methods (HTTP request verbs) that the origin domain may use
                                // for a CORS request. (comma separated)
    std::string AllowedHeaders; // The request headers that the origin domain may specify on the
                                // CORS request.
    std::string ExposedHeaders; // The response headers that may be sent in the response to the CORS
                                // request and exposed by the browser to the request issuer.
    int32_t MaxAgeInSeconds; // The maximum amount time that a browser should cache the preflight
                             // OPTIONS request.
  };

  // A listed directory item.
  struct DirectoryItem
  {
    std::string Name;
  };

  // File properties.
  struct FileProperty
  {
    int64_t
        ContentLength; // Content length of the file. This value may not be up-to-date since an SMB
                       // client may have modified the file locally. The value of Content-Length may
                       // not reflect that fact until the handle is closed or the op-lock is broken.
                       // To retrieve current property values, call Get File Properties.
  };

  // A listed file item.
  struct FileItem
  {
    std::string Name;
    FileProperty Properties;
  };

  // Abstract for entries that can be listed from Directory.
  struct FilesAndDirectoriesListSegment
  {
    std::vector<DirectoryItem> DirectoryItems;
    std::vector<FileItem> FileItems;
  };

  // A listed Azure Storage handle item.
  struct HandleItem
  {
    std::string HandleId; // XSMB service handle ID
    std::string Path; // File or directory name including full path starting from share root
    std::string FileId; // FileId uniquely identifies the file or directory.
    std::string ParentId; // ParentId uniquely identifies the parent directory of the object.
    std::string SessionId; // SMB session ID in context of which the file handle was opened
    std::string ClientIp; // Client IP that opened the handle
    std::string OpenTime; // Time when the session that previously opened the handle has last been
                          // reconnected. (UTC)
    std::string LastReconnectTime; // Time handle was last connected to (UTC)
  };

  // An enumeration of directories and files.
  struct ListFilesAndDirectoriesSegmentResponse
  {
    std::string ServiceEndpoint;
    std::string ShareName;
    std::string ShareSnapshot;
    std::string DirectoryPath;
    std::string Prefix;
    std::string Marker;
    int32_t MaxResults;
    FilesAndDirectoriesListSegment Segment;
    std::string NextMarker;
  };

  // An enumeration of handles.
  struct ListHandlesResponse
  {
    std::vector<HandleItem> HandleList;
    std::string NextMarker;
  };

  // Properties of a share.
  struct ShareProperties
  {
    std::string LastModified;
    std::string Etag;
    int32_t Quota;
    int32_t ProvisionedIops;
    int32_t ProvisionedIngressMBps;
    int32_t ProvisionedEgressMBps;
    std::string NextAllowedQuotaDowngradeTime;
    std::string DeletedTime;
    int32_t RemainingRetentionDays;
  };

  typedef std::map<std::string, std::string> Metadata;

  // A listed Azure Storage share item.
  struct ShareItem
  {
    std::string Name;
    std::string Snapshot;
    bool Deleted;
    std::string Version;
    ShareProperties Properties;
    Metadata ShareMetadata;
  };

  // An enumeration of shares.
  struct ListSharesResponse
  {
    std::string ServiceEndpoint;
    std::string Prefix;
    std::string Marker;
    int32_t MaxResults;
    std::vector<ShareItem> ShareItems;
    std::string NextMarker;
  };

  // The retention policy.
  struct ShareRetentionPolicy
  {
    bool Enabled; // Indicates whether a retention policy is enabled for the File service. If false,
                  // metrics data is retained, and the user is responsible for deleting it.
    int32_t Days; // Indicates the number of days that metrics data should be retained. All data
                  // older than this value will be deleted. Metrics data is deleted on a best-effort
                  // basis after the retention period expires.
  };

  // Storage Analytics metrics for file service.
  struct Metrics
  {
    std::string Version; // The version of Storage Analytics to configure.
    bool Enabled; // Indicates whether metrics are enabled for the File service.
    bool IncludeAPIs; // Indicates whether metrics should generate summary statistics for called API
                      // operations.
    ShareRetentionPolicy RetentionPolicy;
  };

  // An Azure Storage file range.
  struct Range
  {
    int64_t Start; // Start of the range.
    int64_t End; // End of the range.
  };

  // Stats for the share.
  struct ShareStats
  {
    int32_t
        ShareUsageBytes; // The approximate size of the data stored in bytes. Note that this value
                         // may not include all recently created or recently resized files.
  };

  // Signed identifier.
  struct SignedIdentifier
  {
    std::string Id; // A unique id.
    AccessPolicy Policy; // The access policy.
  };

  // Storage service properties.
  struct StorageServiceProperties
  {
    Metrics HourMetrics; // A summary of request statistics grouped by API in hourly aggregates for
                         // files.
    Metrics MinuteMetrics; // A summary of request statistics grouped by API in minute aggregates
                           // for files.
    std::vector<CorsRule> Cors; // The set of CORS rules.
  };

  // A permission (a security descriptor) at the share level.
  struct SharePermission
  {
    std::string Permission; // The permission in the Security Descriptor Definition Language (SDDL).
  };

  // State of the copy operation identified by 'x-ms-copy-id'.
  enum class CopyStatusType
  {
    Pending,
    Success,
    Aborted,
    Failed,
    Unknown
  };

  inline std::string CopyStatusTypeToString(const CopyStatusType& copyStatusType)
  {
    switch (copyStatusType)
    {
      case CopyStatusType::Pending:
        return "pending";
      case CopyStatusType::Success:
        return "success";
      case CopyStatusType::Aborted:
        return "aborted";
      case CopyStatusType::Failed:
        return "failed";
      default:
        return std::string();
    }
  }

  inline CopyStatusType CopyStatusTypeFromString(const std::string& copyStatusType)
  {
    if (copyStatusType == "pending")
    {
      return CopyStatusType::Pending;
    }
    if (copyStatusType == "success")
    {
      return CopyStatusType::Success;
    }
    if (copyStatusType == "aborted")
    {
      return CopyStatusType::Aborted;
    }
    if (copyStatusType == "failed")
    {
      return CopyStatusType::Failed;
    }
    throw std::runtime_error("Cannot convert " + copyStatusType + " to CopyStatusType");
  }

  // When a file is leased, specifies whether the lease is of infinite or fixed duration.
  enum class LeaseDurationType
  {
    Infinite,
    Fixed,
    Unknown
  };

  inline std::string LeaseDurationTypeToString(const LeaseDurationType& leaseDurationType)
  {
    switch (leaseDurationType)
    {
      case LeaseDurationType::Infinite:
        return "infinite";
      case LeaseDurationType::Fixed:
        return "fixed";
      default:
        return std::string();
    }
  }

  inline LeaseDurationType LeaseDurationTypeFromString(const std::string& leaseDurationType)
  {
    if (leaseDurationType == "infinite")
    {
      return LeaseDurationType::Infinite;
    }
    if (leaseDurationType == "fixed")
    {
      return LeaseDurationType::Fixed;
    }
    throw std::runtime_error("Cannot convert " + leaseDurationType + " to LeaseDurationType");
  }

  // Lease state of the file.
  enum class LeaseStateType
  {
    Available,
    Leased,
    Expired,
    Breaking,
    Broken,
    Unknown
  };

  inline std::string LeaseStateTypeToString(const LeaseStateType& leaseStateType)
  {
    switch (leaseStateType)
    {
      case LeaseStateType::Available:
        return "available";
      case LeaseStateType::Leased:
        return "leased";
      case LeaseStateType::Expired:
        return "expired";
      case LeaseStateType::Breaking:
        return "breaking";
      case LeaseStateType::Broken:
        return "broken";
      default:
        return std::string();
    }
  }

  inline LeaseStateType LeaseStateTypeFromString(const std::string& leaseStateType)
  {
    if (leaseStateType == "available")
    {
      return LeaseStateType::Available;
    }
    if (leaseStateType == "leased")
    {
      return LeaseStateType::Leased;
    }
    if (leaseStateType == "expired")
    {
      return LeaseStateType::Expired;
    }
    if (leaseStateType == "breaking")
    {
      return LeaseStateType::Breaking;
    }
    if (leaseStateType == "broken")
    {
      return LeaseStateType::Broken;
    }
    throw std::runtime_error("Cannot convert " + leaseStateType + " to LeaseStateType");
  }

  // The current lease status of the file.
  enum class LeaseStatusType
  {
    Locked,
    Unlocked,
    Unknown
  };

  inline std::string LeaseStatusTypeToString(const LeaseStatusType& leaseStatusType)
  {
    switch (leaseStatusType)
    {
      case LeaseStatusType::Locked:
        return "locked";
      case LeaseStatusType::Unlocked:
        return "unlocked";
      default:
        return std::string();
    }
  }

  inline LeaseStatusType LeaseStatusTypeFromString(const std::string& leaseStatusType)
  {
    if (leaseStatusType == "locked")
    {
      return LeaseStatusType::Locked;
    }
    if (leaseStatusType == "unlocked")
    {
      return LeaseStatusType::Unlocked;
    }
    throw std::runtime_error("Cannot convert " + leaseStatusType + " to LeaseStatusType");
  }

  // Describes what lease action to take.
  enum class LeaseAction
  {
    Acquire,
    Release,
    Change,
    Break,
    Unknown
  };

  inline std::string LeaseActionToString(const LeaseAction& leaseAction)
  {
    switch (leaseAction)
    {
      case LeaseAction::Acquire:
        return "acquire";
      case LeaseAction::Release:
        return "release";
      case LeaseAction::Change:
        return "change";
      case LeaseAction::Break:
        return "break";
      default:
        return std::string();
    }
  }

  inline LeaseAction LeaseActionFromString(const std::string& leaseAction)
  {
    if (leaseAction == "acquire")
    {
      return LeaseAction::Acquire;
    }
    if (leaseAction == "release")
    {
      return LeaseAction::Release;
    }
    if (leaseAction == "change")
    {
      return LeaseAction::Change;
    }
    if (leaseAction == "break")
    {
      return LeaseAction::Break;
    }
    throw std::runtime_error("Cannot convert " + leaseAction + " to LeaseAction");
  }

  // Specify one of the following options: - Update: Writes the bytes specified by the request body
  // into the specified range. The Range and Content-Length headers must match to perform the
  // update. - Clear: Clears the specified range and releases the space used in storage for that
  // range. To clear a range, set the Content-Length header to zero, and set the Range header to a
  // value that indicates the range to clear, up to maximum file size.
  enum class FileRangeWriteType
  {
    Update,
    Clear,
    Unknown
  };

  inline std::string FileRangeWriteTypeToString(const FileRangeWriteType& fileRangeWriteType)
  {
    switch (fileRangeWriteType)
    {
      case FileRangeWriteType::Update:
        return "update";
      case FileRangeWriteType::Clear:
        return "clear";
      default:
        return std::string();
    }
  }

  inline FileRangeWriteType FileRangeWriteTypeFromString(const std::string& fileRangeWriteType)
  {
    if (fileRangeWriteType == "update")
    {
      return FileRangeWriteType::Update;
    }
    if (fileRangeWriteType == "clear")
    {
      return FileRangeWriteType::Clear;
    }
    throw std::runtime_error("Cannot convert " + fileRangeWriteType + " to FileRangeWriteType");
  }

  struct ServiceSetPropertiesResponse
  {
  };

  struct ServiceGetPropertiesResponse
  {
    Metrics HourMetrics;
    Metrics MinuteMetrics;
    std::vector<CorsRule> Cors;
  };

  struct ServiceListSharesSegmentResponse
  {
    std::string ServiceEndpoint;
    std::string Prefix;
    std::string Marker;
    int32_t MaxResults = int32_t();
    std::vector<ShareItem> ShareItems;
    std::string NextMarker;
  };

  struct ShareCreateResponse
  {
    std::string ETag;
    std::string LastModified;
  };

  struct ShareGetPropertiesResponse
  {
    std::string Metadata;
    std::string ETag;
    std::string LastModified;
    int32_t Quota = int32_t();
    int32_t ProvisionedIops = int32_t();
    int32_t ProvisionedIngressMBps = int32_t();
    int32_t ProvisionedEgressMBps = int32_t();
    std::string NextAllowedQuotaDowngradeTime;
  };

  struct ShareDeleteResponse
  {
  };

  struct ShareCreateSnapshotResponse
  {
    std::string Snapshot;
    std::string ETag;
    std::string LastModified;
  };

  struct ShareCreatePermissionResponse
  {
    std::string FilePermissionKey;
  };

  struct ShareGetPermissionResponse
  {
    std::string Permission;
  };

  struct ShareSetQuotaResponse
  {
    std::string ETag;
    std::string LastModified;
  };

  struct ShareSetMetadataResponse
  {
    std::string ETag;
    std::string LastModified;
  };

  struct ShareGetAccessPolicyResponse
  {
    std::vector<SignedIdentifier> SignedIdentifiers;
    std::string ETag;
    std::string LastModified;
  };

  struct ShareSetAccessPolicyResponse
  {
    std::string ETag;
    std::string LastModified;
  };

  struct ShareGetStatisticsResponse
  {
    int32_t ShareUsageBytes = int32_t();
    std::string ETag;
    std::string LastModified;
  };

  struct ShareRestoreResponse
  {
    std::string ETag;
    std::string LastModified;
  };

  struct DirectoryCreateResponse
  {
    std::string ETag;
    std::string LastModified;
    bool IsServerEncrypted = bool();
    std::string FilePermissionKey;
    std::string FileAttributes;
    std::string FileCreationTime;
    std::string FileLastWriteTime;
    std::string FileChangeTime;
    std::string FileId;
    std::string FileParentId;
  };

  struct DirectoryGetPropertiesResponse
  {
    std::string Metadata;
    std::string ETag;
    std::string LastModified;
    bool IsServerEncrypted = bool();
    std::string FileAttributes;
    std::string FileCreationTime;
    std::string FileLastWriteTime;
    std::string FileChangeTime;
    std::string FilePermissionKey;
    std::string FileId;
    std::string FileParentId;
  };

  struct DirectoryDeleteResponse
  {
  };

  struct DirectorySetPropertiesResponse
  {
    std::string ETag;
    std::string LastModified;
    bool IsServerEncrypted = bool();
    std::string FilePermissionKey;
    std::string FileAttributes;
    std::string FileCreationTime;
    std::string FileLastWriteTime;
    std::string FileChangeTime;
    std::string FileId;
    std::string FileParentId;
  };

  struct DirectorySetMetadataResponse
  {
    std::string ETag;
    bool IsServerEncrypted = bool();
  };

  struct DirectoryListFilesAndDirectoriesSegmentResponse
  {
    std::string ServiceEndpoint;
    std::string ShareName;
    std::string ShareSnapshot;
    std::string DirectoryPath;
    std::string Prefix;
    std::string Marker;
    int32_t MaxResults = int32_t();
    FilesAndDirectoriesListSegment Segment;
    std::string NextMarker;
    FileShareHttpHeaders HttpHeaders;
  };

  struct DirectoryListHandlesResponse
  {
    std::vector<HandleItem> HandleList;
    std::string NextMarker;
    FileShareHttpHeaders HttpHeaders;
  };

  struct DirectoryForceCloseHandlesResponse
  {
    std::string marker;
    int32_t numberOfHandlesClosed = int32_t();
    int32_t numberOfHandlesFailedToClose = int32_t();
  };

  struct FileCreateResponse
  {
    std::string ETag;
    std::string LastModified;
    bool IsServerEncrypted = bool();
    std::string FilePermissionKey;
    std::string FileAttributes;
    std::string FileCreationTime;
    std::string FileLastWriteTime;
    std::string FileChangeTime;
    std::string FileId;
    std::string FileParentId;
  };

  struct FileDownloadResponse
  {
    std::unique_ptr<Azure::Core::Http::BodyStream> BodyStream;
    std::string LastModified;
    std::string Metadata;
    int64_t ContentLength = int64_t();
    FileShareHttpHeaders HttpHeaders;
    std::string ContentRange;
    std::string ETag;
    std::string ContentMD5;
    std::string AcceptRanges;
    std::string CopyCompletionTime;
    std::string CopyStatusDescription;
    std::string CopyId;
    std::string CopyProgress;
    std::string CopySource;
    CopyStatusType CopyStatus = CopyStatusType::Unknown;
    std::string FileContentMD5;
    bool IsServerEncrypted = bool();
    std::string FileAttributes;
    std::string FileCreationTime;
    std::string FileLastWriteTime;
    std::string FileChangeTime;
    std::string FilePermissionKey;
    std::string FileId;
    std::string FileParentId;
    LeaseDurationType LeaseDuration = LeaseDurationType::Unknown;
    LeaseStateType LeaseState = LeaseStateType::Unknown;
    LeaseStatusType LeaseStatus = LeaseStatusType::Unknown;
  };

  struct FileGetPropertiesResponse
  {
    std::string LastModified;
    std::string Metadata;
    std::string FileType;
    int64_t ContentLength = int64_t();
    FileShareHttpHeaders HttpHeaders;
    std::string ETag;
    std::string ContentMD5;
    std::string CopyCompletionTime;
    std::string CopyStatusDescription;
    std::string CopyId;
    std::string CopyProgress;
    std::string CopySource;
    CopyStatusType CopyStatus = CopyStatusType::Unknown;
    bool IsServerEncrypted = bool();
    std::string FileAttributes;
    std::string FileCreationTime;
    std::string FileLastWriteTime;
    std::string FileChangeTime;
    std::string FilePermissionKey;
    std::string FileId;
    std::string FileParentId;
    LeaseDurationType LeaseDuration = LeaseDurationType::Unknown;
    LeaseStateType LeaseState = LeaseStateType::Unknown;
    LeaseStatusType LeaseStatus = LeaseStatusType::Unknown;
  };

  struct FileDeleteResponse
  {
  };

  struct FileSetHTTPHeadersResponse
  {
    std::string ETag;
    std::string LastModified;
    bool IsServerEncrypted = bool();
    std::string FilePermissionKey;
    std::string FileAttributes;
    std::string FileCreationTime;
    std::string FileLastWriteTime;
    std::string FileChangeTime;
    std::string FileId;
    std::string FileParentId;
  };

  struct FileSetMetadataResponse
  {
    std::string ETag;
    bool IsServerEncrypted = bool();
  };

  struct FileAcquireLeaseResponse
  {
    std::string ETag;
    std::string LastModified;
    std::string LeaseId;
  };

  struct FileReleaseLeaseResponse
  {
    std::string ETag;
    std::string LastModified;
  };

  struct FileChangeLeaseResponse
  {
    std::string ETag;
    std::string LastModified;
    std::string LeaseId;
  };

  struct FileBreakLeaseResponse
  {
    std::string ETag;
    std::string LastModified;
    std::string LeaseId;
  };

  struct FileUploadRangeResponse
  {
    std::string ETag;
    std::string LastModified;
    std::string ContentMD5;
    bool IsServerEncrypted = bool();
  };

  struct FileUploadRangeFromURLResponse
  {
    std::string ETag;
    std::string LastModified;
    std::string XMsContentCrc64;
    bool IsServerEncrypted = bool();
  };

  struct FileGetRangeListResponse
  {
    std::vector<Range> RangeList;
    std::string LastModified;
    std::string ETag;
    int64_t FileContentLength = int64_t();
  };

  struct FileStartCopyResponse
  {
    std::string ETag;
    std::string LastModified;
    std::string CopyId;
    CopyStatusType CopyStatus = CopyStatusType::Unknown;
  };

  struct FileAbortCopyResponse
  {
  };

  struct FileListHandlesResponse
  {
    std::vector<HandleItem> HandleList;
    std::string NextMarker;
    FileShareHttpHeaders HttpHeaders;
  };

  struct FileForceCloseHandlesResponse
  {
    std::string marker;
    int32_t numberOfHandlesClosed = int32_t();
    int32_t numberOfHandlesFailedToClose = int32_t();
  };

  class ShareRestClient {
  public:
    class Service {
    public:
      struct SetPropertiesOptions
      {
        StorageServiceProperties ServiceProperties; // The StorageService properties.
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<ServiceSetPropertiesResponse> SetProperties(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const SetPropertiesOptions& setPropertiesOptions)
      {

        std::string xml_body;
        {
          XmlWriter writer;
          StorageServicePropertiesToXml(writer, setPropertiesOptions.ServiceProperties);
          writer.Write(XmlNode{XmlNodeType::End});
          xml_body = writer.GetDocument();
        }
        auto body = Azure::Core::Http::MemoryBodyStream(
            reinterpret_cast<const uint8_t*>(xml_body.data()), xml_body.length());
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url, &body);
        request.AddHeader("Content-Length", std::to_string(body.Length()));
        request.AddQueryParameter(Details::c_QueryRestype, "service");
        request.AddQueryParameter(Details::c_QueryComp, "properties");
        if (setPropertiesOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(setPropertiesOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, setPropertiesOptions.ApiVersionParameter);
        return SetPropertiesParseResponse(context, pipeline.Send(context, request));
      }

      struct GetPropertiesOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<ServiceGetPropertiesResponse> GetProperties(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const GetPropertiesOptions& getPropertiesOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddQueryParameter(Details::c_QueryRestype, "service");
        request.AddQueryParameter(Details::c_QueryComp, "properties");
        if (getPropertiesOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(getPropertiesOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, getPropertiesOptions.ApiVersionParameter);
        return GetPropertiesParseResponse(context, pipeline.Send(context, request));
      }

      struct ListSharesSegmentOptions
      {
        Azure::Core::Nullable<std::string> Prefix; // Filters the results to return only entries
                                                   // whose name begins with the specified prefix.
        Azure::Core::Nullable<std::string>
            Marker; // A string value that identifies the portion of the list to be returned with
                    // the next list operation. The operation returns a marker value within the
                    // response body if the list returned was not complete. The marker value may
                    // then be used in a subsequent call to request the next set of list items. The
                    // marker value is opaque to the client.
        Azure::Core::Nullable<int32_t>
            MaxResults; // Specifies the maximum number of entries to return. If the request does
                        // not specify maxresults, or specifies a value greater than 5,000, the
                        // server will return up to 5,000 items.
        Azure::Core::Nullable<ListSharesIncludeType>
            ListSharesInclude; // Include this parameter to specify one or more datasets to include
                               // in the response.
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<ServiceListSharesSegmentResponse> ListSharesSegment(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const ListSharesSegmentOptions& listSharesSegmentOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddQueryParameter(Details::c_QueryComp, "list");
        if (listSharesSegmentOptions.Prefix.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryPrefix, listSharesSegmentOptions.Prefix.GetValue());
        }
        if (listSharesSegmentOptions.Marker.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryMarker, listSharesSegmentOptions.Marker.GetValue());
        }
        if (listSharesSegmentOptions.MaxResults.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryMaxResults,
              std::to_string(listSharesSegmentOptions.MaxResults.GetValue()));
        }
        if (listSharesSegmentOptions.ListSharesInclude.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryListSharesInclude,
              ListSharesIncludeTypeToString(listSharesSegmentOptions.ListSharesInclude.GetValue()));
        }
        if (listSharesSegmentOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(listSharesSegmentOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, listSharesSegmentOptions.ApiVersionParameter);
        return ListSharesSegmentParseResponse(context, pipeline.Send(context, request));
      }

    private:
      static Azure::Core::Response<ServiceSetPropertiesResponse> SetPropertiesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Accepted)
        {
          // Success (Accepted)
          ServiceSetPropertiesResponse result;
          return Azure::Core::Response<ServiceSetPropertiesResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static void ShareRetentionPolicyToXml(XmlWriter& writer, const ShareRetentionPolicy& object)
      {
        writer.Write(XmlNode{XmlNodeType::StartTag, "Enabled"});
        writer.Write(XmlNode{XmlNodeType::Text, nullptr, object.Enabled == 0 ? "false" : "true"});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::StartTag, "Days"});
        writer.Write(XmlNode{XmlNodeType::Text, nullptr, std::to_string(object.Days).data()});
        writer.Write(XmlNode{XmlNodeType::EndTag});
      };

      static void MetricsToXml(XmlWriter& writer, const Metrics& object)
      {
        writer.Write(XmlNode{XmlNodeType::StartTag, "Version"});
        writer.Write(XmlNode{XmlNodeType::Text, nullptr, object.Version.data()});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::StartTag, "Enabled"});
        writer.Write(XmlNode{XmlNodeType::Text, nullptr, object.Enabled == 0 ? "false" : "true"});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::StartTag, "IncludeAPIs"});
        writer.Write(
            XmlNode{XmlNodeType::Text, nullptr, object.IncludeAPIs == 0 ? "false" : "true"});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::StartTag, "RetentionPolicy"});
        ShareRetentionPolicyToXml(writer, object.RetentionPolicy);
        writer.Write(XmlNode{XmlNodeType::EndTag});
      };

      static void CorsRuleToXml(XmlWriter& writer, const CorsRule& object)
      {
        writer.Write(XmlNode{XmlNodeType::StartTag, "CorsRule"});
        writer.Write(XmlNode{XmlNodeType::StartTag, "AllowedOrigins"});
        writer.Write(XmlNode{XmlNodeType::Text, nullptr, object.AllowedOrigins.data()});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::StartTag, "AllowedMethods"});
        writer.Write(XmlNode{XmlNodeType::Text, nullptr, object.AllowedMethods.data()});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::StartTag, "AllowedHeaders"});
        writer.Write(XmlNode{XmlNodeType::Text, nullptr, object.AllowedHeaders.data()});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::StartTag, "ExposedHeaders"});
        writer.Write(XmlNode{XmlNodeType::Text, nullptr, object.ExposedHeaders.data()});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::StartTag, "MaxAgeInSeconds"});
        writer.Write(
            XmlNode{XmlNodeType::Text, nullptr, std::to_string(object.MaxAgeInSeconds).data()});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::EndTag});
      };

      static void StorageServicePropertiesToXml(
          XmlWriter& writer,
          const StorageServiceProperties& object)
      {
        writer.Write(XmlNode{XmlNodeType::StartTag, "StorageServiceProperties"});
        writer.Write(XmlNode{XmlNodeType::StartTag, "HourMetrics"});
        MetricsToXml(writer, object.HourMetrics);
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::StartTag, "MinuteMetrics"});
        MetricsToXml(writer, object.MinuteMetrics);
        writer.Write(XmlNode{XmlNodeType::EndTag});
        if (object.Cors.size() > 0)
        {
          writer.Write(XmlNode{XmlNodeType::StartTag, "Cors"});
          for (const auto& item : object.Cors)
          {
            CorsRuleToXml(writer, item);
          }
          writer.Write(XmlNode{XmlNodeType::EndTag});
        }
        writer.Write(XmlNode{XmlNodeType::EndTag});
      };
      static Azure::Core::Response<ServiceGetPropertiesResponse> GetPropertiesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success.
          const auto& bodyBuffer = response.GetBody();
          auto reader
              = XmlReader(reinterpret_cast<const char*>(bodyBuffer.data()), bodyBuffer.size());
          ServiceGetPropertiesResponse result = bodyBuffer.empty()
              ? ServiceGetPropertiesResponse()
              : ServiceGetPropertiesResponseFromStorageServiceProperties(
                  StorageServicePropertiesFromXml(reader));
          return Azure::Core::Response<ServiceGetPropertiesResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static ShareRetentionPolicy ShareRetentionPolicyFromXml(XmlReader& reader)
      {
        auto result = ShareRetentionPolicy();
        enum class XmlTagName
        {
          c_Unknown,
          c_Enabled,
          c_Days,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "Enabled") == 0)
            {
              path.emplace_back(XmlTagName::c_Enabled);
            }
            else if (std::strcmp(node.Name, "Days") == 0)
            {
              path.emplace_back(XmlTagName::c_Days);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 1 && path[0] == XmlTagName::c_Enabled)
            {
              result.Enabled = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_Days)
            {
              result.Days = std::stoi(node.Value);
            }
          }
        }
        return result;
      }

      static Metrics MetricsFromXml(XmlReader& reader)
      {
        auto result = Metrics();
        enum class XmlTagName
        {
          c_Unknown,
          c_Version,
          c_Enabled,
          c_IncludeAPIs,
          c_RetentionPolicy,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "Version") == 0)
            {
              path.emplace_back(XmlTagName::c_Version);
            }
            else if (std::strcmp(node.Name, "Enabled") == 0)
            {
              path.emplace_back(XmlTagName::c_Enabled);
            }
            else if (std::strcmp(node.Name, "IncludeAPIs") == 0)
            {
              path.emplace_back(XmlTagName::c_IncludeAPIs);
            }
            else if (std::strcmp(node.Name, "RetentionPolicy") == 0)
            {
              path.emplace_back(XmlTagName::c_RetentionPolicy);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }

            if (path.size() == 1 && path[0] == XmlTagName::c_RetentionPolicy)
            {
              result.RetentionPolicy = ShareRetentionPolicyFromXml(reader);
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 1 && path[0] == XmlTagName::c_Version)
            {
              result.Version = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_Enabled)
            {
              result.Enabled = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_IncludeAPIs)
            {
              result.IncludeAPIs = node.Value;
            }
          }
        }
        return result;
      }

      static CorsRule CorsRuleFromXml(XmlReader& reader)
      {
        auto result = CorsRule();
        enum class XmlTagName
        {
          c_Unknown,
          c_AllowedOrigins,
          c_AllowedMethods,
          c_AllowedHeaders,
          c_ExposedHeaders,
          c_MaxAgeInSeconds,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "AllowedOrigins") == 0)
            {
              path.emplace_back(XmlTagName::c_AllowedOrigins);
            }
            else if (std::strcmp(node.Name, "AllowedMethods") == 0)
            {
              path.emplace_back(XmlTagName::c_AllowedMethods);
            }
            else if (std::strcmp(node.Name, "AllowedHeaders") == 0)
            {
              path.emplace_back(XmlTagName::c_AllowedHeaders);
            }
            else if (std::strcmp(node.Name, "ExposedHeaders") == 0)
            {
              path.emplace_back(XmlTagName::c_ExposedHeaders);
            }
            else if (std::strcmp(node.Name, "MaxAgeInSeconds") == 0)
            {
              path.emplace_back(XmlTagName::c_MaxAgeInSeconds);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 1 && path[0] == XmlTagName::c_AllowedOrigins)
            {
              result.AllowedOrigins = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_AllowedMethods)
            {
              result.AllowedMethods = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_AllowedHeaders)
            {
              result.AllowedHeaders = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_ExposedHeaders)
            {
              result.ExposedHeaders = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_MaxAgeInSeconds)
            {
              result.MaxAgeInSeconds = std::stoi(node.Value);
            }
          }
        }
        return result;
      }

      static StorageServiceProperties StorageServicePropertiesFromXml(XmlReader& reader)
      {
        auto result = StorageServiceProperties();
        enum class XmlTagName
        {
          c_Unknown,
          c_StorageServiceProperties,
          c_HourMetrics,
          c_MinuteMetrics,
          c_CorsRule,
          c_Cors,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "StorageServiceProperties") == 0)
            {
              path.emplace_back(XmlTagName::c_StorageServiceProperties);
            }
            else if (std::strcmp(node.Name, "HourMetrics") == 0)
            {
              path.emplace_back(XmlTagName::c_HourMetrics);
            }
            else if (std::strcmp(node.Name, "MinuteMetrics") == 0)
            {
              path.emplace_back(XmlTagName::c_MinuteMetrics);
            }
            else if (std::strcmp(node.Name, "CorsRule") == 0)
            {
              path.emplace_back(XmlTagName::c_CorsRule);
            }
            else if (std::strcmp(node.Name, "Cors") == 0)
            {
              path.emplace_back(XmlTagName::c_Cors);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }

            if (path.size() == 2 && path[0] == XmlTagName::c_StorageServiceProperties
                && path[1] == XmlTagName::c_HourMetrics)
            {
              result.HourMetrics = MetricsFromXml(reader);
              path.pop_back();
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::c_StorageServiceProperties
                && path[1] == XmlTagName::c_MinuteMetrics)
            {
              result.MinuteMetrics = MetricsFromXml(reader);
              path.pop_back();
            }
            else if (
                path.size() == 3 && path[0] == XmlTagName::c_StorageServiceProperties
                && path[1] == XmlTagName::c_Cors && path[2] == XmlTagName::c_CorsRule)
            {
              result.Cors.emplace_back(CorsRuleFromXml(reader));
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
          }
        }
        return result;
      }

      static ServiceGetPropertiesResponse ServiceGetPropertiesResponseFromStorageServiceProperties(
          StorageServiceProperties object)
      {
        ServiceGetPropertiesResponse result;
        result.HourMetrics = std::move(object.HourMetrics);
        result.MinuteMetrics = std::move(object.MinuteMetrics);
        result.Cors = std::move(object.Cors);

        return result;
      }
      static Azure::Core::Response<ServiceListSharesSegmentResponse> ListSharesSegmentParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success.
          const auto& bodyBuffer = response.GetBody();
          auto reader
              = XmlReader(reinterpret_cast<const char*>(bodyBuffer.data()), bodyBuffer.size());
          ServiceListSharesSegmentResponse result = bodyBuffer.empty()
              ? ServiceListSharesSegmentResponse()
              : ServiceListSharesSegmentResponseFromListSharesResponse(
                  ListSharesResponseFromXml(reader));
          return Azure::Core::Response<ServiceListSharesSegmentResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static ShareProperties SharePropertiesFromXml(XmlReader& reader)
      {
        auto result = ShareProperties();
        enum class XmlTagName
        {
          c_Unknown,
          c_LastModified,
          c_Etag,
          c_Quota,
          c_ProvisionedIops,
          c_ProvisionedIngressMBps,
          c_ProvisionedEgressMBps,
          c_NextAllowedQuotaDowngradeTime,
          c_DeletedTime,
          c_RemainingRetentionDays,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "Last-Modified") == 0)
            {
              path.emplace_back(XmlTagName::c_LastModified);
            }
            else if (std::strcmp(node.Name, "Etag") == 0)
            {
              path.emplace_back(XmlTagName::c_Etag);
            }
            else if (std::strcmp(node.Name, "Quota") == 0)
            {
              path.emplace_back(XmlTagName::c_Quota);
            }
            else if (std::strcmp(node.Name, "ProvisionedIops") == 0)
            {
              path.emplace_back(XmlTagName::c_ProvisionedIops);
            }
            else if (std::strcmp(node.Name, "ProvisionedIngressMBps") == 0)
            {
              path.emplace_back(XmlTagName::c_ProvisionedIngressMBps);
            }
            else if (std::strcmp(node.Name, "ProvisionedEgressMBps") == 0)
            {
              path.emplace_back(XmlTagName::c_ProvisionedEgressMBps);
            }
            else if (std::strcmp(node.Name, "NextAllowedQuotaDowngradeTime") == 0)
            {
              path.emplace_back(XmlTagName::c_NextAllowedQuotaDowngradeTime);
            }
            else if (std::strcmp(node.Name, "DeletedTime") == 0)
            {
              path.emplace_back(XmlTagName::c_DeletedTime);
            }
            else if (std::strcmp(node.Name, "RemainingRetentionDays") == 0)
            {
              path.emplace_back(XmlTagName::c_RemainingRetentionDays);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 1 && path[0] == XmlTagName::c_LastModified)
            {
              result.LastModified = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_Etag)
            {
              result.Etag = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_Quota)
            {
              result.Quota = std::stoi(node.Value);
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_ProvisionedIops)
            {
              result.ProvisionedIops = std::stoi(node.Value);
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_ProvisionedIngressMBps)
            {
              result.ProvisionedIngressMBps = std::stoi(node.Value);
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_ProvisionedEgressMBps)
            {
              result.ProvisionedEgressMBps = std::stoi(node.Value);
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_NextAllowedQuotaDowngradeTime)
            {
              result.NextAllowedQuotaDowngradeTime = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_DeletedTime)
            {
              result.DeletedTime = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_RemainingRetentionDays)
            {
              result.RemainingRetentionDays = std::stoi(node.Value);
            }
          }
        }
        return result;
      }

      static std::map<std::string, std::string> MetadataFromXml(XmlReader& reader)
      {
        std::map<std::string, std::string> result;
        int depth = 0;
        std::string key;
        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::StartTag)
          {
            if (depth++ == 0)
            {
              key = node.Name;
            }
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (depth-- == 0)
            {
              break;
            }
          }
          else if (depth == 1 && node.Type == XmlNodeType::Text)
          {
            result.emplace(std::move(key), std::string(node.Value));
          }
        }
        return result;
      }

      static ShareItem ShareItemFromXml(XmlReader& reader)
      {
        auto result = ShareItem();
        enum class XmlTagName
        {
          c_Unknown,
          c_Name,
          c_Snapshot,
          c_Deleted,
          c_Version,
          c_Properties,
          c_Metadata,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "Name") == 0)
            {
              path.emplace_back(XmlTagName::c_Name);
            }
            else if (std::strcmp(node.Name, "Snapshot") == 0)
            {
              path.emplace_back(XmlTagName::c_Snapshot);
            }
            else if (std::strcmp(node.Name, "Deleted") == 0)
            {
              path.emplace_back(XmlTagName::c_Deleted);
            }
            else if (std::strcmp(node.Name, "Version") == 0)
            {
              path.emplace_back(XmlTagName::c_Version);
            }
            else if (std::strcmp(node.Name, "Properties") == 0)
            {
              path.emplace_back(XmlTagName::c_Properties);
            }
            else if (std::strcmp(node.Name, "Metadata") == 0)
            {
              path.emplace_back(XmlTagName::c_Metadata);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }

            if (path.size() == 1 && path[0] == XmlTagName::c_Properties)
            {
              result.Properties = SharePropertiesFromXml(reader);
              path.pop_back();
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_Metadata)
            {
              result.ShareMetadata = MetadataFromXml(reader);
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 1 && path[0] == XmlTagName::c_Name)
            {
              result.Name = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_Snapshot)
            {
              result.Snapshot = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_Deleted)
            {
              result.Deleted = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_Version)
            {
              result.Version = node.Value;
            }
          }
        }
        return result;
      }

      static ListSharesResponse ListSharesResponseFromXml(XmlReader& reader)
      {
        auto result = ListSharesResponse();
        enum class XmlTagName
        {
          c_Unknown,
          c_EnumerationResults,
          c_Prefix,
          c_Marker,
          c_MaxResults,
          c_Shares,
          c_Share,
          c_NextMarker,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "EnumerationResults") == 0)
            {
              path.emplace_back(XmlTagName::c_EnumerationResults);
            }
            else if (std::strcmp(node.Name, "Prefix") == 0)
            {
              path.emplace_back(XmlTagName::c_Prefix);
            }
            else if (std::strcmp(node.Name, "Marker") == 0)
            {
              path.emplace_back(XmlTagName::c_Marker);
            }
            else if (std::strcmp(node.Name, "MaxResults") == 0)
            {
              path.emplace_back(XmlTagName::c_MaxResults);
            }
            else if (std::strcmp(node.Name, "Shares") == 0)
            {
              path.emplace_back(XmlTagName::c_Shares);
            }
            else if (std::strcmp(node.Name, "Share") == 0)
            {
              path.emplace_back(XmlTagName::c_Share);
            }
            else if (std::strcmp(node.Name, "NextMarker") == 0)
            {
              path.emplace_back(XmlTagName::c_NextMarker);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }
            if (path.size() == 3 && path[0] == XmlTagName::c_EnumerationResults
                && path[1] == XmlTagName::c_Shares && path[2] == XmlTagName::c_Share)
            {
              result.ShareItems.emplace_back(ShareItemFromXml(reader));
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 2 && path[0] == XmlTagName::c_EnumerationResults
                && path[1] == XmlTagName::c_Prefix)
            {
              result.Prefix = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::c_EnumerationResults
                && path[1] == XmlTagName::c_Marker)
            {
              result.Marker = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::c_EnumerationResults
                && path[1] == XmlTagName::c_MaxResults)
            {
              result.MaxResults = std::stoi(node.Value);
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::c_EnumerationResults
                && path[1] == XmlTagName::c_NextMarker)
            {
              result.NextMarker = node.Value;
            }
          }
          else if (node.Type == XmlNodeType::Attribute)
          {
            if (path.size() == 1 && path[0] == XmlTagName::c_EnumerationResults
                && (std::strcmp(node.Name, "ServiceEndpoint") == 0))
            {
              result.ServiceEndpoint = node.Value;
            }
          }
        }
        return result;
      }

      static ServiceListSharesSegmentResponse
      ServiceListSharesSegmentResponseFromListSharesResponse(ListSharesResponse object)
      {
        ServiceListSharesSegmentResponse result;
        result.ServiceEndpoint = std::move(object.ServiceEndpoint);
        result.Prefix = std::move(object.Prefix);
        result.Marker = std::move(object.Marker);
        result.MaxResults = object.MaxResults;
        result.ShareItems = std::move(object.ShareItems);
        result.NextMarker = std::move(object.NextMarker);

        return result;
      }
    };

    class Share {
    public:
      struct CreateOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::map<std::string, std::string>
            Metadata; // A name-value pair to associate with a file storage object.
        Azure::Core::Nullable<int32_t>
            ShareQuota; // Specifies the maximum size of the share, in gigabytes.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<ShareCreateResponse> Create(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const CreateOptions& createOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryRestype, "share");
        if (createOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(createOptions.Timeout.GetValue()));
        }
        for (const auto& pair : createOptions.Metadata)
        {
          request.AddHeader(Details::c_HeaderMetadata + pair.first, pair.second);
        }
        if (createOptions.ShareQuota.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderQuota, std::to_string(createOptions.ShareQuota.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, createOptions.ApiVersionParameter);
        return CreateParseResponse(context, pipeline.Send(context, request));
      }

      struct GetPropertiesOptions
      {
        Azure::Core::Nullable<std::string>
            ShareSnapshot; // The snapshot parameter is an opaque DateTime value that, when present,
                           // specifies the share snapshot to query.
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<ShareGetPropertiesResponse> GetProperties(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const GetPropertiesOptions& getPropertiesOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddQueryParameter(Details::c_QueryRestype, "share");
        if (getPropertiesOptions.ShareSnapshot.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryShareSnapshot, getPropertiesOptions.ShareSnapshot.GetValue());
        }
        if (getPropertiesOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(getPropertiesOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, getPropertiesOptions.ApiVersionParameter);
        return GetPropertiesParseResponse(context, pipeline.Send(context, request));
      }

      struct DeleteOptions
      {
        Azure::Core::Nullable<std::string>
            ShareSnapshot; // The snapshot parameter is an opaque DateTime value that, when present,
                           // specifies the share snapshot to query.
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<DeleteSnapshotsOptionType>
            XMsDeleteSnapshots; // Specifies the option include to delete the base share and all of
                                // its snapshots.
      };

      static Azure::Core::Response<ShareDeleteResponse> Delete(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const DeleteOptions& deleteOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Delete, url);
        request.AddQueryParameter(Details::c_QueryRestype, "share");
        if (deleteOptions.ShareSnapshot.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryShareSnapshot, deleteOptions.ShareSnapshot.GetValue());
        }
        if (deleteOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(deleteOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, deleteOptions.ApiVersionParameter);
        if (deleteOptions.XMsDeleteSnapshots.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderDeleteSnapshots,
              DeleteSnapshotsOptionTypeToString(deleteOptions.XMsDeleteSnapshots.GetValue()));
        }
        return DeleteParseResponse(context, pipeline.Send(context, request));
      }

      struct CreateSnapshotOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::map<std::string, std::string>
            Metadata; // A name-value pair to associate with a file storage object.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<ShareCreateSnapshotResponse> CreateSnapshot(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const CreateSnapshotOptions& createSnapshotOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryRestype, "share");
        request.AddQueryParameter(Details::c_QueryComp, "snapshot");
        if (createSnapshotOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(createSnapshotOptions.Timeout.GetValue()));
        }
        for (const auto& pair : createSnapshotOptions.Metadata)
        {
          request.AddHeader(Details::c_HeaderMetadata + pair.first, pair.second);
        }
        request.AddHeader(Details::c_HeaderVersion, createSnapshotOptions.ApiVersionParameter);
        return CreateSnapshotParseResponse(context, pipeline.Send(context, request));
      }

      struct CreatePermissionOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        SharePermission Permission; // A permission (a security descriptor) at the share level.
      };

      static Azure::Core::Response<ShareCreatePermissionResponse> CreatePermission(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const CreatePermissionOptions& createPermissionOptions)
      {

        std::string json_body;
        {
          nlohmann::json json;
          SharePermissionToJson(json, createPermissionOptions.Permission);
          json_body = json.dump();
        }
        auto body = Azure::Core::Http::MemoryBodyStream(
            reinterpret_cast<const uint8_t*>(json_body.data()), json_body.length());
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url, &body);
        request.AddQueryParameter(Details::c_QueryRestype, "share");
        request.AddQueryParameter(Details::c_QueryComp, "filepermission");
        if (createPermissionOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(createPermissionOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, createPermissionOptions.ApiVersionParameter);
        return CreatePermissionParseResponse(context, pipeline.Send(context, request));
      }

      struct GetPermissionOptions
      {
        std::string
            FilePermissionKeyRequired; // Key of the permission to be set for the directory/file.
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<ShareGetPermissionResponse> GetPermission(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const GetPermissionOptions& getPermissionOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddQueryParameter(Details::c_QueryRestype, "share");
        request.AddQueryParameter(Details::c_QueryComp, "filepermission");
        request.AddHeader(
            Details::c_HeaderFilePermissionKey, getPermissionOptions.FilePermissionKeyRequired);
        if (getPermissionOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(getPermissionOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, getPermissionOptions.ApiVersionParameter);
        return GetPermissionParseResponse(context, pipeline.Send(context, request));
      }

      struct SetQuotaOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<int32_t>
            ShareQuota; // Specifies the maximum size of the share, in gigabytes.
      };

      static Azure::Core::Response<ShareSetQuotaResponse> SetQuota(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const SetQuotaOptions& setQuotaOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryRestype, "share");
        request.AddQueryParameter(Details::c_QueryComp, "properties");
        if (setQuotaOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(setQuotaOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, setQuotaOptions.ApiVersionParameter);
        if (setQuotaOptions.ShareQuota.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderQuota, std::to_string(setQuotaOptions.ShareQuota.GetValue()));
        }
        return SetQuotaParseResponse(context, pipeline.Send(context, request));
      }

      struct SetMetadataOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::map<std::string, std::string>
            Metadata; // A name-value pair to associate with a file storage object.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<ShareSetMetadataResponse> SetMetadata(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const SetMetadataOptions& setMetadataOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryRestype, "share");
        request.AddQueryParameter(Details::c_QueryComp, "metadata");
        if (setMetadataOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(setMetadataOptions.Timeout.GetValue()));
        }
        for (const auto& pair : setMetadataOptions.Metadata)
        {
          request.AddHeader(Details::c_HeaderMetadata + pair.first, pair.second);
        }
        request.AddHeader(Details::c_HeaderVersion, setMetadataOptions.ApiVersionParameter);
        return SetMetadataParseResponse(context, pipeline.Send(context, request));
      }

      struct GetAccessPolicyOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<ShareGetAccessPolicyResponse> GetAccessPolicy(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const GetAccessPolicyOptions& getAccessPolicyOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddQueryParameter(Details::c_QueryRestype, "share");
        request.AddQueryParameter(Details::c_QueryComp, "acl");
        if (getAccessPolicyOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(getAccessPolicyOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, getAccessPolicyOptions.ApiVersionParameter);
        return GetAccessPolicyParseResponse(context, pipeline.Send(context, request));
      }

      struct SetAccessPolicyOptions
      {
        std::vector<SignedIdentifier> ShareAcl; // The ACL for the share.
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<ShareSetAccessPolicyResponse> SetAccessPolicy(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const SetAccessPolicyOptions& setAccessPolicyOptions)
      {

        std::string xml_body;
        {
          XmlWriter writer;
          SignedIdentifiersToXml(writer, setAccessPolicyOptions.ShareAcl);
          writer.Write(XmlNode{XmlNodeType::End});
          xml_body = writer.GetDocument();
        }
        auto body = Azure::Core::Http::MemoryBodyStream(
            reinterpret_cast<const uint8_t*>(xml_body.data()), xml_body.length());
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::Put, url, &body);
        request.AddHeader("Content-Length", std::to_string(body.Length()));
        request.AddQueryParameter(Details::c_QueryRestype, "share");
        request.AddQueryParameter(Details::c_QueryComp, "acl");
        if (setAccessPolicyOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(setAccessPolicyOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, setAccessPolicyOptions.ApiVersionParameter);
        return SetAccessPolicyParseResponse(context, pipeline.Send(context, request));
      }

      struct GetStatisticsOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<ShareGetStatisticsResponse> GetStatistics(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const GetStatisticsOptions& getStatisticsOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddQueryParameter(Details::c_QueryRestype, "share");
        request.AddQueryParameter(Details::c_QueryComp, "stats");
        if (getStatisticsOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(getStatisticsOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, getStatisticsOptions.ApiVersionParameter);
        return GetStatisticsParseResponse(context, pipeline.Send(context, request));
      }

      struct RestoreOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                             // limit that is recorded in the analytics logs when storage analytics
                             // logging is enabled.
        Azure::Core::Nullable<std::string>
            DeletedShareName; // Specifies the name of the preivously-deleted share.
        Azure::Core::Nullable<std::string>
            DeletedShareVersion; // Specifies the version of the preivously-deleted share.
      };

      static Azure::Core::Response<ShareRestoreResponse> Restore(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const RestoreOptions& restoreOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryRestype, "share");
        request.AddQueryParameter(Details::c_QueryComp, "undelete");
        if (restoreOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(restoreOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, restoreOptions.ApiVersionParameter);
        if (restoreOptions.ClientRequestId.HasValue())
        {
          request.AddHeader(Details::c_HeaderRequestId, restoreOptions.ClientRequestId.GetValue());
        }
        if (restoreOptions.DeletedShareName.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderDeletedShareName, restoreOptions.DeletedShareName.GetValue());
        }
        if (restoreOptions.DeletedShareVersion.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderDeletedShareVersion, restoreOptions.DeletedShareVersion.GetValue());
        }
        return RestoreParseResponse(context, pipeline.Send(context, request));
      }

    private:
      static Azure::Core::Response<ShareCreateResponse> CreateParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
        {
          // Success, Share created.
          ShareCreateResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          return Azure::Core::Response<ShareCreateResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<ShareGetPropertiesResponse> GetPropertiesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success
          ShareGetPropertiesResponse result;
          result.Metadata = response.GetHeaders().at(Details::c_HeaderMetadata);
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.Quota = std::stoi(response.GetHeaders().at(Details::c_HeaderQuota));
          result.ProvisionedIops
              = std::stoi(response.GetHeaders().at(Details::c_HeaderProvisionedIops));
          result.ProvisionedIngressMBps
              = std::stoi(response.GetHeaders().at(Details::c_HeaderProvisionedIngressMBps));
          result.ProvisionedEgressMBps
              = std::stoi(response.GetHeaders().at(Details::c_HeaderProvisionedEgressMBps));
          result.NextAllowedQuotaDowngradeTime
              = response.GetHeaders().at(Details::c_HeaderNextAllowedQuotaDowngradeTime);
          return Azure::Core::Response<ShareGetPropertiesResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<ShareDeleteResponse> DeleteParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Accepted)
        {
          // Accepted
          ShareDeleteResponse result;
          return Azure::Core::Response<ShareDeleteResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<ShareCreateSnapshotResponse> CreateSnapshotParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
        {
          // Success, Share snapshot created.
          ShareCreateSnapshotResponse result;
          result.Snapshot = response.GetHeaders().at(Details::c_HeaderSnapshot);
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          return Azure::Core::Response<ShareCreateSnapshotResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<ShareCreatePermissionResponse> CreatePermissionParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
        {
          // Success, Share level permission created.
          ShareCreatePermissionResponse result;
          result.FilePermissionKey = response.GetHeaders().at(Details::c_HeaderFilePermissionKey);
          return Azure::Core::Response<ShareCreatePermissionResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static void SharePermissionToJson(nlohmann::json& node, const SharePermission& object)
      {
        node["permission"] = object.Permission;
      }

      static Azure::Core::Response<ShareGetPermissionResponse> GetPermissionParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success
          const auto& bodyBuffer = response.GetBody();
          ShareGetPermissionResponse result = bodyBuffer.empty()
              ? ShareGetPermissionResponse()
              : ShareGetPermissionResponseFromSharePermission(
                  SharePermissionFromJson(nlohmann::json::parse(bodyBuffer)));
          return Azure::Core::Response<ShareGetPermissionResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static SharePermission SharePermissionFromJson(const nlohmann::json& node)
      {
        SharePermission result;
        result.Permission = node["permission"].get<std::string>();
        return result;
      }

      static ShareGetPermissionResponse ShareGetPermissionResponseFromSharePermission(
          SharePermission object)
      {
        ShareGetPermissionResponse result;
        result.Permission = std::move(object.Permission);

        return result;
      }
      static Azure::Core::Response<ShareSetQuotaResponse> SetQuotaParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success
          ShareSetQuotaResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          return Azure::Core::Response<ShareSetQuotaResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<ShareSetMetadataResponse> SetMetadataParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success
          ShareSetMetadataResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          return Azure::Core::Response<ShareSetMetadataResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<ShareGetAccessPolicyResponse> GetAccessPolicyParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success
          const auto& bodyBuffer = response.GetBody();
          auto reader
              = XmlReader(reinterpret_cast<const char*>(bodyBuffer.data()), bodyBuffer.size());
          ShareGetAccessPolicyResponse result = bodyBuffer.empty()
              ? ShareGetAccessPolicyResponse()
              : ShareGetAccessPolicyResponseFromSignedIdentifiers(SignedIdentifiersFromXml(reader));
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          return Azure::Core::Response<ShareGetAccessPolicyResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static AccessPolicy AccessPolicyFromXml(XmlReader& reader)
      {
        auto result = AccessPolicy();
        enum class XmlTagName
        {
          c_Unknown,
          c_Start,
          c_Expiry,
          c_Permission,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "Start") == 0)
            {
              path.emplace_back(XmlTagName::c_Start);
            }
            else if (std::strcmp(node.Name, "Expiry") == 0)
            {
              path.emplace_back(XmlTagName::c_Expiry);
            }
            else if (std::strcmp(node.Name, "Permission") == 0)
            {
              path.emplace_back(XmlTagName::c_Permission);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 1 && path[0] == XmlTagName::c_Start)
            {
              result.Start = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_Expiry)
            {
              result.Expiry = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_Permission)
            {
              result.Permission = node.Value;
            }
          }
        }
        return result;
      }

      static SignedIdentifier SignedIdentifierFromXml(XmlReader& reader)
      {
        auto result = SignedIdentifier();
        enum class XmlTagName
        {
          c_Unknown,
          c_Id,
          c_AccessPolicy,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "Id") == 0)
            {
              path.emplace_back(XmlTagName::c_Id);
            }
            else if (std::strcmp(node.Name, "AccessPolicy") == 0)
            {
              path.emplace_back(XmlTagName::c_AccessPolicy);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }

            if (path.size() == 1 && path[0] == XmlTagName::c_AccessPolicy)
            {
              result.Policy = AccessPolicyFromXml(reader);
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 1 && path[0] == XmlTagName::c_Id)
            {
              result.Id = node.Value;
            }
          }
        }
        return result;
      }

      static std::vector<SignedIdentifier> SignedIdentifiersFromXml(XmlReader& reader)
      {
        auto result = std::vector<SignedIdentifier>();
        enum class XmlTagName
        {
          c_Unknown,
          c_SignedIdentifiers,
          c_SignedIdentifier,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "SignedIdentifiers") == 0)
            {
              path.emplace_back(XmlTagName::c_SignedIdentifiers);
            }
            else if (std::strcmp(node.Name, "SignedIdentifier") == 0)
            {
              path.emplace_back(XmlTagName::c_SignedIdentifier);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }

            if (path.size() == 2 && path[0] == XmlTagName::c_SignedIdentifiers
                && path[1] == XmlTagName::c_SignedIdentifier)
            {
              result.emplace_back(SignedIdentifierFromXml(reader));
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
          }
        }
        return result;
      }

      static ShareGetAccessPolicyResponse ShareGetAccessPolicyResponseFromSignedIdentifiers(
          std::vector<SignedIdentifier> object)
      {
        ShareGetAccessPolicyResponse result;
        result.SignedIdentifiers = std::move(object);

        return result;
      }
      static Azure::Core::Response<ShareSetAccessPolicyResponse> SetAccessPolicyParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success.
          ShareSetAccessPolicyResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          return Azure::Core::Response<ShareSetAccessPolicyResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static void AccessPolicyToXml(XmlWriter& writer, const AccessPolicy& object)
      {
        writer.Write(XmlNode{XmlNodeType::StartTag, "AccessPolicy"});
        writer.Write(XmlNode{XmlNodeType::StartTag, "Start"});
        writer.Write(XmlNode{XmlNodeType::Text, nullptr, object.Start.data()});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::StartTag, "Expiry"});
        writer.Write(XmlNode{XmlNodeType::Text, nullptr, object.Expiry.data()});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::StartTag, "Permission"});
        writer.Write(XmlNode{XmlNodeType::Text, nullptr, object.Permission.data()});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::EndTag});
      };

      static void SignedIdentifierToXml(XmlWriter& writer, const SignedIdentifier& object)
      {
        writer.Write(XmlNode{XmlNodeType::StartTag, "SignedIdentifier"});
        writer.Write(XmlNode{XmlNodeType::StartTag, "Id"});
        writer.Write(XmlNode{XmlNodeType::Text, nullptr, object.Id.data()});
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::StartTag, "AccessPolicy"});
        AccessPolicyToXml(writer, object.Policy);
        writer.Write(XmlNode{XmlNodeType::EndTag});
        writer.Write(XmlNode{XmlNodeType::EndTag});
      };

      static void SignedIdentifiersToXml(
          XmlWriter& writer,
          const std::vector<SignedIdentifier>& object)
      {
        writer.Write(XmlNode{XmlNodeType::StartTag, "SignedIdentifiers"});
        for (const auto& item : object)
        {
          SignedIdentifierToXml(writer, item);
        }
        writer.Write(XmlNode{XmlNodeType::EndTag});
      };
      static Azure::Core::Response<ShareGetStatisticsResponse> GetStatisticsParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success
          const auto& bodyBuffer = response.GetBody();
          auto reader
              = XmlReader(reinterpret_cast<const char*>(bodyBuffer.data()), bodyBuffer.size());
          ShareGetStatisticsResponse result = bodyBuffer.empty()
              ? ShareGetStatisticsResponse()
              : ShareGetStatisticsResponseFromShareStats(ShareStatsFromXml(reader));
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          return Azure::Core::Response<ShareGetStatisticsResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static ShareStats ShareStatsFromXml(XmlReader& reader)
      {
        auto result = ShareStats();
        enum class XmlTagName
        {
          c_Unknown,
          c_ShareStats,
          c_ShareUsageBytes,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "ShareStats") == 0)
            {
              path.emplace_back(XmlTagName::c_ShareStats);
            }
            else if (std::strcmp(node.Name, "ShareUsageBytes") == 0)
            {
              path.emplace_back(XmlTagName::c_ShareUsageBytes);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 2 && path[0] == XmlTagName::c_ShareStats
                && path[1] == XmlTagName::c_ShareUsageBytes)
            {
              result.ShareUsageBytes = std::stoi(node.Value);
            }
          }
        }
        return result;
      }

      static ShareGetStatisticsResponse ShareGetStatisticsResponseFromShareStats(ShareStats object)
      {
        ShareGetStatisticsResponse result;
        result.ShareUsageBytes = object.ShareUsageBytes;

        return result;
      }
      static Azure::Core::Response<ShareRestoreResponse> RestoreParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
        {
          // Created
          ShareRestoreResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          return Azure::Core::Response<ShareRestoreResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }
    };

    class Directory {
    public:
      struct CreateOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::map<std::string, std::string>
            Metadata; // A name-value pair to associate with a file storage object.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            FilePermission; // If specified the permission (security descriptor) shall be set for
                            // the directory/file. This header can be used if Permission size is <=
                            // 8KB, else x-ms-file-permission-key header shall be used. Default
                            // value: Inherit. If SDDL is specified as input, it must have owner,
                            // group and dacl. Note: Only one of the x-ms-file-permission or
                            // x-ms-file-permission-key should be specified.
        Azure::Core::Nullable<std::string>
            FilePermissionKey; // Key of the permission to be set for the directory/file. Note: Only
                               // one of the x-ms-file-permission or x-ms-file-permission-key should
                               // be specified.
        std::string FileAttributes; // If specified, the provided file attributes shall be set.
                                    // Default value: �Archive� for file and �Directory� for
                                    // directory. �None� can also be specified as default.
        std::string FileCreationTime; // Creation time for the file/directory. Default value: Now.
        std::string
            FileLastWriteTime; // Last write time for the file/directory. Default value: Now.
      };

      static Azure::Core::Response<DirectoryCreateResponse> Create(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const CreateOptions& createOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryRestype, "directory");
        if (createOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(createOptions.Timeout.GetValue()));
        }
        for (const auto& pair : createOptions.Metadata)
        {
          request.AddHeader(Details::c_HeaderMetadata + pair.first, pair.second);
        }
        request.AddHeader(Details::c_HeaderVersion, createOptions.ApiVersionParameter);
        if (createOptions.FilePermission.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFilePermission, createOptions.FilePermission.GetValue());
        }
        if (createOptions.FilePermissionKey.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFilePermissionKey, createOptions.FilePermissionKey.GetValue());
        }
        request.AddHeader(Details::c_HeaderFileAttributes, createOptions.FileAttributes);
        request.AddHeader(Details::c_HeaderFileCreationTime, createOptions.FileCreationTime);
        request.AddHeader(Details::c_HeaderFileLastWriteTime, createOptions.FileLastWriteTime);
        return CreateParseResponse(context, pipeline.Send(context, request));
      }

      struct GetPropertiesOptions
      {
        Azure::Core::Nullable<std::string>
            ShareSnapshot; // The snapshot parameter is an opaque DateTime value that, when present,
                           // specifies the share snapshot to query.
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<DirectoryGetPropertiesResponse> GetProperties(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const GetPropertiesOptions& getPropertiesOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddQueryParameter(Details::c_QueryRestype, "directory");
        if (getPropertiesOptions.ShareSnapshot.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryShareSnapshot, getPropertiesOptions.ShareSnapshot.GetValue());
        }
        if (getPropertiesOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(getPropertiesOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, getPropertiesOptions.ApiVersionParameter);
        return GetPropertiesParseResponse(context, pipeline.Send(context, request));
      }

      struct DeleteOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<DirectoryDeleteResponse> Delete(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const DeleteOptions& deleteOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Delete, url);
        request.AddQueryParameter(Details::c_QueryRestype, "directory");
        if (deleteOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(deleteOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, deleteOptions.ApiVersionParameter);
        return DeleteParseResponse(context, pipeline.Send(context, request));
      }

      struct SetPropertiesOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            FilePermission; // If specified the permission (security descriptor) shall be set for
                            // the directory/file. This header can be used if Permission size is <=
                            // 8KB, else x-ms-file-permission-key header shall be used. Default
                            // value: Inherit. If SDDL is specified as input, it must have owner,
                            // group and dacl. Note: Only one of the x-ms-file-permission or
                            // x-ms-file-permission-key should be specified.
        Azure::Core::Nullable<std::string>
            FilePermissionKey; // Key of the permission to be set for the directory/file. Note: Only
                               // one of the x-ms-file-permission or x-ms-file-permission-key should
                               // be specified.
        std::string FileAttributes; // If specified, the provided file attributes shall be set.
                                    // Default value: �Archive� for file and �Directory� for
                                    // directory. �None� can also be specified as default.
        std::string FileCreationTime; // Creation time for the file/directory. Default value: Now.
        std::string
            FileLastWriteTime; // Last write time for the file/directory. Default value: Now.
      };

      static Azure::Core::Response<DirectorySetPropertiesResponse> SetProperties(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const SetPropertiesOptions& setPropertiesOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryRestype, "directory");
        request.AddQueryParameter(Details::c_QueryComp, "properties");
        if (setPropertiesOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(setPropertiesOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, setPropertiesOptions.ApiVersionParameter);
        if (setPropertiesOptions.FilePermission.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFilePermission, setPropertiesOptions.FilePermission.GetValue());
        }
        if (setPropertiesOptions.FilePermissionKey.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFilePermissionKey,
              setPropertiesOptions.FilePermissionKey.GetValue());
        }
        request.AddHeader(Details::c_HeaderFileAttributes, setPropertiesOptions.FileAttributes);
        request.AddHeader(Details::c_HeaderFileCreationTime, setPropertiesOptions.FileCreationTime);
        request.AddHeader(
            Details::c_HeaderFileLastWriteTime, setPropertiesOptions.FileLastWriteTime);
        return SetPropertiesParseResponse(context, pipeline.Send(context, request));
      }

      struct SetMetadataOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::map<std::string, std::string>
            Metadata; // A name-value pair to associate with a file storage object.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<DirectorySetMetadataResponse> SetMetadata(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const SetMetadataOptions& setMetadataOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryRestype, "directory");
        request.AddQueryParameter(Details::c_QueryComp, "metadata");
        if (setMetadataOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(setMetadataOptions.Timeout.GetValue()));
        }
        for (const auto& pair : setMetadataOptions.Metadata)
        {
          request.AddHeader(Details::c_HeaderMetadata + pair.first, pair.second);
        }
        request.AddHeader(Details::c_HeaderVersion, setMetadataOptions.ApiVersionParameter);
        return SetMetadataParseResponse(context, pipeline.Send(context, request));
      }

      struct ListFilesAndDirectoriesSegmentOptions
      {
        Azure::Core::Nullable<std::string> Prefix; // Filters the results to return only entries
                                                   // whose name begins with the specified prefix.
        Azure::Core::Nullable<std::string>
            ShareSnapshot; // The snapshot parameter is an opaque DateTime value that, when present,
                           // specifies the share snapshot to query.
        Azure::Core::Nullable<std::string>
            Marker; // A string value that identifies the portion of the list to be returned with
                    // the next list operation. The operation returns a marker value within the
                    // response body if the list returned was not complete. The marker value may
                    // then be used in a subsequent call to request the next set of list items. The
                    // marker value is opaque to the client.
        Azure::Core::Nullable<int32_t>
            MaxResults; // Specifies the maximum number of entries to return. If the request does
                        // not specify maxresults, or specifies a value greater than 5,000, the
                        // server will return up to 5,000 items.
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<DirectoryListFilesAndDirectoriesSegmentResponse>
      ListFilesAndDirectoriesSegment(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const ListFilesAndDirectoriesSegmentOptions& listFilesAndDirectoriesSegmentOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddQueryParameter(Details::c_QueryRestype, "directory");
        request.AddQueryParameter(Details::c_QueryComp, "list");
        if (listFilesAndDirectoriesSegmentOptions.Prefix.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryPrefix, listFilesAndDirectoriesSegmentOptions.Prefix.GetValue());
        }
        if (listFilesAndDirectoriesSegmentOptions.ShareSnapshot.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryShareSnapshot,
              listFilesAndDirectoriesSegmentOptions.ShareSnapshot.GetValue());
        }
        if (listFilesAndDirectoriesSegmentOptions.Marker.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryMarker, listFilesAndDirectoriesSegmentOptions.Marker.GetValue());
        }
        if (listFilesAndDirectoriesSegmentOptions.MaxResults.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryMaxResults,
              std::to_string(listFilesAndDirectoriesSegmentOptions.MaxResults.GetValue()));
        }
        if (listFilesAndDirectoriesSegmentOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout,
              std::to_string(listFilesAndDirectoriesSegmentOptions.Timeout.GetValue()));
        }
        request.AddHeader(
            Details::c_HeaderVersion, listFilesAndDirectoriesSegmentOptions.ApiVersionParameter);
        return ListFilesAndDirectoriesSegmentParseResponse(
            context, pipeline.Send(context, request));
      }

      struct ListHandlesOptions
      {
        Azure::Core::Nullable<std::string>
            Marker; // A string value that identifies the portion of the list to be returned with
                    // the next list operation. The operation returns a marker value within the
                    // response body if the list returned was not complete. The marker value may
                    // then be used in a subsequent call to request the next set of list items. The
                    // marker value is opaque to the client.
        Azure::Core::Nullable<int32_t>
            MaxResults; // Specifies the maximum number of entries to return. If the request does
                        // not specify maxresults, or specifies a value greater than 5,000, the
                        // server will return up to 5,000 items.
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        Azure::Core::Nullable<std::string>
            ShareSnapshot; // The snapshot parameter is an opaque DateTime value that, when present,
                           // specifies the share snapshot to query.
        Azure::Core::Nullable<bool>
            Recursive; // Specifies operation should apply to the directory specified in the URI,
                       // its files, its subdirectories and their files.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<DirectoryListHandlesResponse> ListHandles(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const ListHandlesOptions& listHandlesOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddQueryParameter(Details::c_QueryComp, "listhandles");
        if (listHandlesOptions.Marker.HasValue())
        {
          request.AddQueryParameter(Details::c_QueryMarker, listHandlesOptions.Marker.GetValue());
        }
        if (listHandlesOptions.MaxResults.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryMaxResults, std::to_string(listHandlesOptions.MaxResults.GetValue()));
        }
        if (listHandlesOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(listHandlesOptions.Timeout.GetValue()));
        }
        if (listHandlesOptions.ShareSnapshot.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryShareSnapshot, listHandlesOptions.ShareSnapshot.GetValue());
        }
        if (listHandlesOptions.Recursive.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderRecursive,
              (listHandlesOptions.Recursive.GetValue() ? "true" : "false"));
        }
        request.AddHeader(Details::c_HeaderVersion, listHandlesOptions.ApiVersionParameter);
        return ListHandlesParseResponse(context, pipeline.Send(context, request));
      }

      struct ForceCloseHandlesOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        Azure::Core::Nullable<std::string>
            Marker; // A string value that identifies the portion of the list to be returned with
                    // the next list operation. The operation returns a marker value within the
                    // response body if the list returned was not complete. The marker value may
                    // then be used in a subsequent call to request the next set of list items. The
                    // marker value is opaque to the client.
        Azure::Core::Nullable<std::string>
            ShareSnapshot; // The snapshot parameter is an opaque DateTime value that, when present,
                           // specifies the share snapshot to query.
        std::string HandleId; // Specifies handle ID opened on the file or directory to be closed.
                              // Asterisk (�*�) is a wildcard that specifies all handles.
        Azure::Core::Nullable<bool>
            Recursive; // Specifies operation should apply to the directory specified in the URI,
                       // its files, its subdirectories and their files.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<DirectoryForceCloseHandlesResponse> ForceCloseHandles(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const ForceCloseHandlesOptions& forceCloseHandlesOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryComp, "forceclosehandles");
        if (forceCloseHandlesOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(forceCloseHandlesOptions.Timeout.GetValue()));
        }
        if (forceCloseHandlesOptions.Marker.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryMarker, forceCloseHandlesOptions.Marker.GetValue());
        }
        if (forceCloseHandlesOptions.ShareSnapshot.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryShareSnapshot, forceCloseHandlesOptions.ShareSnapshot.GetValue());
        }
        request.AddHeader(Details::c_HeaderHandleId, forceCloseHandlesOptions.HandleId);
        if (forceCloseHandlesOptions.Recursive.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderRecursive,
              (forceCloseHandlesOptions.Recursive.GetValue() ? "true" : "false"));
        }
        request.AddHeader(Details::c_HeaderVersion, forceCloseHandlesOptions.ApiVersionParameter);
        return ForceCloseHandlesParseResponse(context, pipeline.Send(context, request));
      }

    private:
      static Azure::Core::Response<DirectoryCreateResponse> CreateParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
        {
          // Success, Directory created.
          DirectoryCreateResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.IsServerEncrypted
              = response.GetHeaders().at(Details::c_HeaderIsServerEncrypted) == "true";
          result.FilePermissionKey = response.GetHeaders().at(Details::c_HeaderFilePermissionKey);
          result.FileAttributes = response.GetHeaders().at(Details::c_HeaderFileAttributes);
          result.FileCreationTime = response.GetHeaders().at(Details::c_HeaderFileCreationTime);
          result.FileLastWriteTime = response.GetHeaders().at(Details::c_HeaderFileLastWriteTime);
          result.FileChangeTime = response.GetHeaders().at(Details::c_HeaderFileChangeTime);
          result.FileId = response.GetHeaders().at(Details::c_HeaderFileId);
          result.FileParentId = response.GetHeaders().at(Details::c_HeaderFileParentId);
          return Azure::Core::Response<DirectoryCreateResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<DirectoryGetPropertiesResponse> GetPropertiesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success.
          DirectoryGetPropertiesResponse result;
          result.Metadata = response.GetHeaders().at(Details::c_HeaderMetadata);
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.IsServerEncrypted
              = response.GetHeaders().at(Details::c_HeaderIsServerEncrypted) == "true";
          result.FileAttributes = response.GetHeaders().at(Details::c_HeaderFileAttributes);
          result.FileCreationTime = response.GetHeaders().at(Details::c_HeaderFileCreationTime);
          result.FileLastWriteTime = response.GetHeaders().at(Details::c_HeaderFileLastWriteTime);
          result.FileChangeTime = response.GetHeaders().at(Details::c_HeaderFileChangeTime);
          result.FilePermissionKey = response.GetHeaders().at(Details::c_HeaderFilePermissionKey);
          result.FileId = response.GetHeaders().at(Details::c_HeaderFileId);
          result.FileParentId = response.GetHeaders().at(Details::c_HeaderFileParentId);
          return Azure::Core::Response<DirectoryGetPropertiesResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<DirectoryDeleteResponse> DeleteParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Accepted)
        {
          // Success (Accepted).
          DirectoryDeleteResponse result;
          return Azure::Core::Response<DirectoryDeleteResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<DirectorySetPropertiesResponse> SetPropertiesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success
          DirectorySetPropertiesResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.IsServerEncrypted
              = response.GetHeaders().at(Details::c_HeaderIsServerEncrypted) == "true";
          result.FilePermissionKey = response.GetHeaders().at(Details::c_HeaderFilePermissionKey);
          result.FileAttributes = response.GetHeaders().at(Details::c_HeaderFileAttributes);
          result.FileCreationTime = response.GetHeaders().at(Details::c_HeaderFileCreationTime);
          result.FileLastWriteTime = response.GetHeaders().at(Details::c_HeaderFileLastWriteTime);
          result.FileChangeTime = response.GetHeaders().at(Details::c_HeaderFileChangeTime);
          result.FileId = response.GetHeaders().at(Details::c_HeaderFileId);
          result.FileParentId = response.GetHeaders().at(Details::c_HeaderFileParentId);
          return Azure::Core::Response<DirectorySetPropertiesResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<DirectorySetMetadataResponse> SetMetadataParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success (OK).
          DirectorySetMetadataResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.IsServerEncrypted
              = response.GetHeaders().at(Details::c_HeaderIsServerEncrypted) == "true";
          return Azure::Core::Response<DirectorySetMetadataResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<DirectoryListFilesAndDirectoriesSegmentResponse>
      ListFilesAndDirectoriesSegmentParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success.
          const auto& bodyBuffer = response.GetBody();
          auto reader
              = XmlReader(reinterpret_cast<const char*>(bodyBuffer.data()), bodyBuffer.size());
          DirectoryListFilesAndDirectoriesSegmentResponse result = bodyBuffer.empty()
              ? DirectoryListFilesAndDirectoriesSegmentResponse()
              : DirectoryListFilesAndDirectoriesSegmentResponseFromListFilesAndDirectoriesSegmentResponse(
                  ListFilesAndDirectoriesSegmentResponseFromXml(reader));
          result.HttpHeaders.ContentType = response.GetHeaders().at(Details::c_HeaderContentType);
          return Azure::Core::Response<DirectoryListFilesAndDirectoriesSegmentResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static DirectoryItem DirectoryItemFromXml(XmlReader& reader)
      {
        auto result = DirectoryItem();
        enum class XmlTagName
        {
          c_Unknown,
          c_Name,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "Name") == 0)
            {
              path.emplace_back(XmlTagName::c_Name);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }
          }
        }
        return result;
      }

      static FileProperty FilePropertyFromXml(XmlReader& reader)
      {
        auto result = FileProperty();
        enum class XmlTagName
        {
          c_Unknown,
          c_ContentLength,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "Content-Length") == 0)
            {
              path.emplace_back(XmlTagName::c_ContentLength);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }
          }
        }
        return result;
      }

      static FileItem FileItemFromXml(XmlReader& reader)
      {
        auto result = FileItem();
        enum class XmlTagName
        {
          c_Unknown,
          c_Name,
          c_Properties,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "Name") == 0)
            {
              path.emplace_back(XmlTagName::c_Name);
            }
            else if (std::strcmp(node.Name, "Properties") == 0)
            {
              path.emplace_back(XmlTagName::c_Properties);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }

            if (path.size() == 1 && path[0] == XmlTagName::c_Properties)
            {
              result.Properties = FilePropertyFromXml(reader);
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 1 && path[0] == XmlTagName::c_Name)
            {
              result.Name = node.Value;
            }
          }
        }
        return result;
      }

      static FilesAndDirectoriesListSegment FilesAndDirectoriesListSegmentFromXml(XmlReader& reader)
      {
        auto result = FilesAndDirectoriesListSegment();
        enum class XmlTagName
        {
          c_Unknown,
          c_Directory,
          c_File,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "Directory") == 0)
            {
              path.emplace_back(XmlTagName::c_Directory);
            }
            else if (std::strcmp(node.Name, "File") == 0)
            {
              path.emplace_back(XmlTagName::c_File);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }
            if (path.size() == 1 && path[0] == XmlTagName::c_Directory)
            {
              result.DirectoryItems.emplace_back(DirectoryItemFromXml(reader));
              path.pop_back();
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_File)
            {
              result.FileItems.emplace_back(FileItemFromXml(reader));
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
          }
        }
        return result;
      }

      static ListFilesAndDirectoriesSegmentResponse ListFilesAndDirectoriesSegmentResponseFromXml(
          XmlReader& reader)
      {
        auto result = ListFilesAndDirectoriesSegmentResponse();
        enum class XmlTagName
        {
          c_Unknown,
          c_EnumerationResults,
          c_Prefix,
          c_Marker,
          c_MaxResults,
          c_Entries,
          c_NextMarker,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "EnumerationResults") == 0)
            {
              path.emplace_back(XmlTagName::c_EnumerationResults);
            }
            else if (std::strcmp(node.Name, "Prefix") == 0)
            {
              path.emplace_back(XmlTagName::c_Prefix);
            }
            else if (std::strcmp(node.Name, "Marker") == 0)
            {
              path.emplace_back(XmlTagName::c_Marker);
            }
            else if (std::strcmp(node.Name, "MaxResults") == 0)
            {
              path.emplace_back(XmlTagName::c_MaxResults);
            }
            else if (std::strcmp(node.Name, "Entries") == 0)
            {
              path.emplace_back(XmlTagName::c_Entries);
            }
            else if (std::strcmp(node.Name, "NextMarker") == 0)
            {
              path.emplace_back(XmlTagName::c_NextMarker);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }

            if (path.size() == 2 && path[0] == XmlTagName::c_EnumerationResults
                && path[1] == XmlTagName::c_Entries)
            {
              result.Segment = FilesAndDirectoriesListSegmentFromXml(reader);
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 2 && path[0] == XmlTagName::c_EnumerationResults
                && path[1] == XmlTagName::c_Prefix)
            {
              result.Prefix = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::c_EnumerationResults
                && path[1] == XmlTagName::c_Marker)
            {
              result.Marker = node.Value;
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::c_EnumerationResults
                && path[1] == XmlTagName::c_MaxResults)
            {
              result.MaxResults = std::stoi(node.Value);
            }
            else if (
                path.size() == 2 && path[0] == XmlTagName::c_EnumerationResults
                && path[1] == XmlTagName::c_NextMarker)
            {
              result.NextMarker = node.Value;
            }
          }
          else if (node.Type == XmlNodeType::Attribute)
          {
            if (path.size() == 1 && path[0] == XmlTagName::c_EnumerationResults
                && (std::strcmp(node.Name, "ServiceEndpoint") == 0))
            {
              result.ServiceEndpoint = node.Value;
            }
            else if (
                path.size() == 1 && path[0] == XmlTagName::c_EnumerationResults
                && (std::strcmp(node.Name, "ShareName") == 0))
            {
              result.ShareName = node.Value;
            }
            else if (
                path.size() == 1 && path[0] == XmlTagName::c_EnumerationResults
                && (std::strcmp(node.Name, "ShareSnapshot") == 0))
            {
              result.ShareSnapshot = node.Value;
            }
            else if (
                path.size() == 1 && path[0] == XmlTagName::c_EnumerationResults
                && (std::strcmp(node.Name, "DirectoryPath") == 0))
            {
              result.DirectoryPath = node.Value;
            }
          }
        }
        return result;
      }

      static DirectoryListFilesAndDirectoriesSegmentResponse
      DirectoryListFilesAndDirectoriesSegmentResponseFromListFilesAndDirectoriesSegmentResponse(
          ListFilesAndDirectoriesSegmentResponse object)
      {
        DirectoryListFilesAndDirectoriesSegmentResponse result;
        result.ServiceEndpoint = std::move(object.ServiceEndpoint);
        result.ShareName = std::move(object.ShareName);
        result.ShareSnapshot = std::move(object.ShareSnapshot);
        result.DirectoryPath = std::move(object.DirectoryPath);
        result.Prefix = std::move(object.Prefix);
        result.Marker = std::move(object.Marker);
        result.MaxResults = object.MaxResults;
        result.Segment = std::move(object.Segment);
        result.NextMarker = std::move(object.NextMarker);

        return result;
      }
      static Azure::Core::Response<DirectoryListHandlesResponse> ListHandlesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success.
          const auto& bodyBuffer = response.GetBody();
          auto reader
              = XmlReader(reinterpret_cast<const char*>(bodyBuffer.data()), bodyBuffer.size());
          DirectoryListHandlesResponse result = bodyBuffer.empty()
              ? DirectoryListHandlesResponse()
              : DirectoryListHandlesResponseFromListHandlesResponse(
                  ListHandlesResponseFromXml(reader));
          result.HttpHeaders.ContentType = response.GetHeaders().at(Details::c_HeaderContentType);
          return Azure::Core::Response<DirectoryListHandlesResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static HandleItem HandleItemFromXml(XmlReader& reader)
      {
        auto result = HandleItem();
        enum class XmlTagName
        {
          c_Unknown,
          c_HandleId,
          c_Path,
          c_FileId,
          c_ParentId,
          c_SessionId,
          c_ClientIp,
          c_OpenTime,
          c_LastReconnectTime,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "HandleId") == 0)
            {
              path.emplace_back(XmlTagName::c_HandleId);
            }
            else if (std::strcmp(node.Name, "Path") == 0)
            {
              path.emplace_back(XmlTagName::c_Path);
            }
            else if (std::strcmp(node.Name, "FileId") == 0)
            {
              path.emplace_back(XmlTagName::c_FileId);
            }
            else if (std::strcmp(node.Name, "ParentId") == 0)
            {
              path.emplace_back(XmlTagName::c_ParentId);
            }
            else if (std::strcmp(node.Name, "SessionId") == 0)
            {
              path.emplace_back(XmlTagName::c_SessionId);
            }
            else if (std::strcmp(node.Name, "ClientIp") == 0)
            {
              path.emplace_back(XmlTagName::c_ClientIp);
            }
            else if (std::strcmp(node.Name, "OpenTime") == 0)
            {
              path.emplace_back(XmlTagName::c_OpenTime);
            }
            else if (std::strcmp(node.Name, "LastReconnectTime") == 0)
            {
              path.emplace_back(XmlTagName::c_LastReconnectTime);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 1 && path[0] == XmlTagName::c_HandleId)
            {
              result.HandleId = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_Path)
            {
              result.Path = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_FileId)
            {
              result.FileId = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_ParentId)
            {
              result.ParentId = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_SessionId)
            {
              result.SessionId = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_ClientIp)
            {
              result.ClientIp = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_OpenTime)
            {
              result.OpenTime = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_LastReconnectTime)
            {
              result.LastReconnectTime = node.Value;
            }
          }
        }
        return result;
      }

      static ListHandlesResponse ListHandlesResponseFromXml(XmlReader& reader)
      {
        auto result = ListHandlesResponse();
        enum class XmlTagName
        {
          c_Unknown,
          c_EnumerationResults,
          c_Entries,
          c_Handle,
          c_NextMarker,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "EnumerationResults") == 0)
            {
              path.emplace_back(XmlTagName::c_EnumerationResults);
            }
            else if (std::strcmp(node.Name, "Entries") == 0)
            {
              path.emplace_back(XmlTagName::c_Entries);
            }
            else if (std::strcmp(node.Name, "Handle") == 0)
            {
              path.emplace_back(XmlTagName::c_Handle);
            }
            else if (std::strcmp(node.Name, "NextMarker") == 0)
            {
              path.emplace_back(XmlTagName::c_NextMarker);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }
            if (path.size() == 3 && path[0] == XmlTagName::c_EnumerationResults
                && path[1] == XmlTagName::c_Entries && path[2] == XmlTagName::c_Handle)
            {
              result.HandleList.emplace_back(HandleItemFromXml(reader));
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 2 && path[0] == XmlTagName::c_EnumerationResults
                && path[1] == XmlTagName::c_NextMarker)
            {
              result.NextMarker = node.Value;
            }
          }
        }
        return result;
      }

      static DirectoryListHandlesResponse DirectoryListHandlesResponseFromListHandlesResponse(
          ListHandlesResponse object)
      {
        DirectoryListHandlesResponse result;
        result.HandleList = std::move(object.HandleList);
        result.NextMarker = std::move(object.NextMarker);

        return result;
      }
      static Azure::Core::Response<DirectoryForceCloseHandlesResponse>
      ForceCloseHandlesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success.
          DirectoryForceCloseHandlesResponse result;
          result.marker = response.GetHeaders().at(Details::c_HeaderMarker);
          result.numberOfHandlesClosed
              = std::stoi(response.GetHeaders().at(Details::c_HeaderNumberOfHandlesClosed));
          result.numberOfHandlesFailedToClose
              = std::stoi(response.GetHeaders().at(Details::c_HeaderNumberOfHandlesFailedToClose));
          return Azure::Core::Response<DirectoryForceCloseHandlesResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }
    };

    class File {
    public:
      struct CreateOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        int64_t XMsContentLength; // Specifies the maximum size for the file, up to 1 TB.
        Azure::Core::Nullable<std::string>
            FileContentType; // Sets the MIME content type of the file. The default type is
                             // 'application/octet-stream'.
        Azure::Core::Nullable<std::string>
            FileContentEncoding; // Specifies which content encodings have been applied to the file.
        Azure::Core::Nullable<std::string>
            FileContentLanguage; // Specifies the natural languages used by this resource.
        Azure::Core::Nullable<std::string>
            FileCacheControl; // Sets the file's cache control. The File service stores this value
                              // but does not use or modify it.
        Azure::Core::Nullable<std::string> FileContentMD5; // Sets the file's MD5 hash.
        Azure::Core::Nullable<std::string>
            FileContentDisposition; // Sets the file's Content-Disposition header.
        std::map<std::string, std::string>
            Metadata; // A name-value pair to associate with a file storage object.
        Azure::Core::Nullable<std::string>
            FilePermission; // If specified the permission (security descriptor) shall be set for
                            // the directory/file. This header can be used if Permission size is <=
                            // 8KB, else x-ms-file-permission-key header shall be used. Default
                            // value: Inherit. If SDDL is specified as input, it must have owner,
                            // group and dacl. Note: Only one of the x-ms-file-permission or
                            // x-ms-file-permission-key should be specified.
        Azure::Core::Nullable<std::string>
            FilePermissionKey; // Key of the permission to be set for the directory/file. Note: Only
                               // one of the x-ms-file-permission or x-ms-file-permission-key should
                               // be specified.
        std::string FileAttributes; // If specified, the provided file attributes shall be set.
                                    // Default value: �Archive� for file and �Directory� for
                                    // directory. �None� can also be specified as default.
        std::string FileCreationTime; // Creation time for the file/directory. Default value: Now.
        std::string
            FileLastWriteTime; // Last write time for the file/directory. Default value: Now.
        Azure::Core::Nullable<std::string>
            LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease is
                             // active and matches this ID.
      };

      static Azure::Core::Response<FileCreateResponse> Create(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const CreateOptions& createOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        if (createOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(createOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, createOptions.ApiVersionParameter);
        request.AddHeader(
            Details::c_HeaderFileContentLength, std::to_string(createOptions.XMsContentLength));
        request.AddHeader(Details::c_HeaderFileTypeConstant, "file");
        if (createOptions.FileContentType.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileContentType, createOptions.FileContentType.GetValue());
        }
        if (createOptions.FileContentEncoding.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileContentEncoding, createOptions.FileContentEncoding.GetValue());
        }
        if (createOptions.FileContentLanguage.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileContentLanguage, createOptions.FileContentLanguage.GetValue());
        }
        if (createOptions.FileCacheControl.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileCacheControl, createOptions.FileCacheControl.GetValue());
        }
        if (createOptions.FileContentMD5.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileContentMD5, createOptions.FileContentMD5.GetValue());
        }
        if (createOptions.FileContentDisposition.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileContentDisposition,
              createOptions.FileContentDisposition.GetValue());
        }
        for (const auto& pair : createOptions.Metadata)
        {
          request.AddHeader(Details::c_HeaderMetadata + pair.first, pair.second);
        }
        if (createOptions.FilePermission.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFilePermission, createOptions.FilePermission.GetValue());
        }
        if (createOptions.FilePermissionKey.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFilePermissionKey, createOptions.FilePermissionKey.GetValue());
        }
        request.AddHeader(Details::c_HeaderFileAttributes, createOptions.FileAttributes);
        request.AddHeader(Details::c_HeaderFileCreationTime, createOptions.FileCreationTime);
        request.AddHeader(Details::c_HeaderFileLastWriteTime, createOptions.FileLastWriteTime);
        if (createOptions.LeaseIdOptional.HasValue())
        {
          request.AddHeader(Details::c_HeaderLeaseId, createOptions.LeaseIdOptional.GetValue());
        }
        return CreateParseResponse(context, pipeline.Send(context, request));
      }

      struct DownloadOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            Range; // Return file data only from the specified byte range.
        Azure::Core::Nullable<bool>
            GetRangeContentMD5; // When this header is set to true and specified together with the
                                // Range header, the service returns the MD5 hash for the range, as
                                // long as the range is less than or equal to 4 MB in size.
        Azure::Core::Nullable<std::string>
            LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease is
                             // active and matches this ID.
      };

      static Azure::Core::Response<FileDownloadResponse> Download(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const DownloadOptions& downloadOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url, true);
        if (downloadOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(downloadOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, downloadOptions.ApiVersionParameter);
        if (downloadOptions.Range.HasValue())
        {
          request.AddHeader(Details::c_HeaderRange, downloadOptions.Range.GetValue());
        }
        if (downloadOptions.GetRangeContentMD5.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderRangeGetContentMD5,
              (downloadOptions.GetRangeContentMD5.GetValue() ? "true" : "false"));
        }
        if (downloadOptions.LeaseIdOptional.HasValue())
        {
          request.AddHeader(Details::c_HeaderLeaseId, downloadOptions.LeaseIdOptional.GetValue());
        }
        return DownloadParseResponse(context, pipeline.Send(context, request));
      }

      struct GetPropertiesOptions
      {
        Azure::Core::Nullable<std::string>
            ShareSnapshot; // The snapshot parameter is an opaque DateTime value that, when present,
                           // specifies the share snapshot to query.
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease is
                             // active and matches this ID.
      };

      static Azure::Core::Response<FileGetPropertiesResponse> GetProperties(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const GetPropertiesOptions& getPropertiesOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Head, url);
        if (getPropertiesOptions.ShareSnapshot.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryShareSnapshot, getPropertiesOptions.ShareSnapshot.GetValue());
        }
        if (getPropertiesOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(getPropertiesOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, getPropertiesOptions.ApiVersionParameter);
        if (getPropertiesOptions.LeaseIdOptional.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderLeaseId, getPropertiesOptions.LeaseIdOptional.GetValue());
        }
        return GetPropertiesParseResponse(context, pipeline.Send(context, request));
      }

      struct DeleteOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease is
                             // active and matches this ID.
      };

      static Azure::Core::Response<FileDeleteResponse> Delete(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const DeleteOptions& deleteOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Delete, url);
        if (deleteOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(deleteOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, deleteOptions.ApiVersionParameter);
        if (deleteOptions.LeaseIdOptional.HasValue())
        {
          request.AddHeader(Details::c_HeaderLeaseId, deleteOptions.LeaseIdOptional.GetValue());
        }
        return DeleteParseResponse(context, pipeline.Send(context, request));
      }

      struct SetHTTPHeadersOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<int64_t>
            XMsContentLength; // Resizes a file to the specified size. If the specified byte value
                              // is less than the current size of the file, then all ranges above
                              // the specified byte value are cleared.
        Azure::Core::Nullable<std::string>
            FileContentType; // Sets the MIME content type of the file. The default type is
                             // 'application/octet-stream'.
        Azure::Core::Nullable<std::string>
            FileContentEncoding; // Specifies which content encodings have been applied to the file.
        Azure::Core::Nullable<std::string>
            FileContentLanguage; // Specifies the natural languages used by this resource.
        Azure::Core::Nullable<std::string>
            FileCacheControl; // Sets the file's cache control. The File service stores this value
                              // but does not use or modify it.
        Azure::Core::Nullable<std::string> FileContentMD5; // Sets the file's MD5 hash.
        Azure::Core::Nullable<std::string>
            FileContentDisposition; // Sets the file's Content-Disposition header.
        Azure::Core::Nullable<std::string>
            FilePermission; // If specified the permission (security descriptor) shall be set for
                            // the directory/file. This header can be used if Permission size is <=
                            // 8KB, else x-ms-file-permission-key header shall be used. Default
                            // value: Inherit. If SDDL is specified as input, it must have owner,
                            // group and dacl. Note: Only one of the x-ms-file-permission or
                            // x-ms-file-permission-key should be specified.
        Azure::Core::Nullable<std::string>
            FilePermissionKey; // Key of the permission to be set for the directory/file. Note: Only
                               // one of the x-ms-file-permission or x-ms-file-permission-key should
                               // be specified.
        std::string FileAttributes; // If specified, the provided file attributes shall be set.
                                    // Default value: �Archive� for file and �Directory� for
                                    // directory. �None� can also be specified as default.
        std::string FileCreationTime; // Creation time for the file/directory. Default value: Now.
        std::string
            FileLastWriteTime; // Last write time for the file/directory. Default value: Now.
        Azure::Core::Nullable<std::string>
            LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease is
                             // active and matches this ID.
      };

      static Azure::Core::Response<FileSetHTTPHeadersResponse> SetHTTPHeaders(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const SetHTTPHeadersOptions& setHTTPHeadersOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryComp, "properties");
        if (setHTTPHeadersOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(setHTTPHeadersOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, setHTTPHeadersOptions.ApiVersionParameter);
        if (setHTTPHeadersOptions.XMsContentLength.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileContentLength,
              std::to_string(setHTTPHeadersOptions.XMsContentLength.GetValue()));
        }
        if (setHTTPHeadersOptions.FileContentType.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileContentType, setHTTPHeadersOptions.FileContentType.GetValue());
        }
        if (setHTTPHeadersOptions.FileContentEncoding.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileContentEncoding,
              setHTTPHeadersOptions.FileContentEncoding.GetValue());
        }
        if (setHTTPHeadersOptions.FileContentLanguage.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileContentLanguage,
              setHTTPHeadersOptions.FileContentLanguage.GetValue());
        }
        if (setHTTPHeadersOptions.FileCacheControl.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileCacheControl, setHTTPHeadersOptions.FileCacheControl.GetValue());
        }
        if (setHTTPHeadersOptions.FileContentMD5.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileContentMD5, setHTTPHeadersOptions.FileContentMD5.GetValue());
        }
        if (setHTTPHeadersOptions.FileContentDisposition.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileContentDisposition,
              setHTTPHeadersOptions.FileContentDisposition.GetValue());
        }
        if (setHTTPHeadersOptions.FilePermission.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFilePermission, setHTTPHeadersOptions.FilePermission.GetValue());
        }
        if (setHTTPHeadersOptions.FilePermissionKey.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFilePermissionKey,
              setHTTPHeadersOptions.FilePermissionKey.GetValue());
        }
        request.AddHeader(Details::c_HeaderFileAttributes, setHTTPHeadersOptions.FileAttributes);
        request.AddHeader(
            Details::c_HeaderFileCreationTime, setHTTPHeadersOptions.FileCreationTime);
        request.AddHeader(
            Details::c_HeaderFileLastWriteTime, setHTTPHeadersOptions.FileLastWriteTime);
        if (setHTTPHeadersOptions.LeaseIdOptional.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderLeaseId, setHTTPHeadersOptions.LeaseIdOptional.GetValue());
        }
        return SetHTTPHeadersParseResponse(context, pipeline.Send(context, request));
      }

      struct SetMetadataOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::map<std::string, std::string>
            Metadata; // A name-value pair to associate with a file storage object.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease is
                             // active and matches this ID.
      };

      static Azure::Core::Response<FileSetMetadataResponse> SetMetadata(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const SetMetadataOptions& setMetadataOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryComp, "metadata");
        if (setMetadataOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(setMetadataOptions.Timeout.GetValue()));
        }
        for (const auto& pair : setMetadataOptions.Metadata)
        {
          request.AddHeader(Details::c_HeaderMetadata + pair.first, pair.second);
        }
        request.AddHeader(Details::c_HeaderVersion, setMetadataOptions.ApiVersionParameter);
        if (setMetadataOptions.LeaseIdOptional.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderLeaseId, setMetadataOptions.LeaseIdOptional.GetValue());
        }
        return SetMetadataParseResponse(context, pipeline.Send(context, request));
      }

      struct AcquireLeaseOptions
      {
        LeaseAction XMsLeaseAction; // Describes what lease action to take.
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        Azure::Core::Nullable<int32_t>
            LeaseDuration; // Specifies the duration of the lease, in seconds, or negative one (-1)
                           // for a lease that never expires. A non-infinite lease can be between 15
                           // and 60 seconds. A lease duration cannot be changed using renew or
                           // change.
        Azure::Core::Nullable<std::string>
            ProposedLeaseIdOptional; // Proposed lease ID, in a GUID string format. The File service
                                     // returns 400 (Invalid request) if the proposed lease ID is
                                     // not in the correct format. See Guid Constructor (String) for
                                     // a list of valid GUID string formats.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                             // limit that is recorded in the analytics logs when storage analytics
                             // logging is enabled.
      };

      static Azure::Core::Response<FileAcquireLeaseResponse> AcquireLease(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const AcquireLeaseOptions& acquireLeaseOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryComp, "lease");
        request.AddHeader(
            Details::c_HeaderAction, LeaseActionToString(acquireLeaseOptions.XMsLeaseAction));
        if (acquireLeaseOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(acquireLeaseOptions.Timeout.GetValue()));
        }
        if (acquireLeaseOptions.LeaseDuration.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderDuration,
              std::to_string(acquireLeaseOptions.LeaseDuration.GetValue()));
        }
        if (acquireLeaseOptions.ProposedLeaseIdOptional.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderProposedLeaseId,
              acquireLeaseOptions.ProposedLeaseIdOptional.GetValue());
        }
        request.AddHeader(Details::c_HeaderVersion, acquireLeaseOptions.ApiVersionParameter);
        if (acquireLeaseOptions.ClientRequestId.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderRequestId, acquireLeaseOptions.ClientRequestId.GetValue());
        }
        return AcquireLeaseParseResponse(context, pipeline.Send(context, request));
      }

      struct ReleaseLeaseOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string LeaseIdRequired; // Specifies the current lease ID on the resource.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                             // limit that is recorded in the analytics logs when storage analytics
                             // logging is enabled.
      };

      static Azure::Core::Response<FileReleaseLeaseResponse> ReleaseLease(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const ReleaseLeaseOptions& releaseLeaseOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryComp, "lease");
        request.AddHeader(Details::c_HeaderAction, "release");
        if (releaseLeaseOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(releaseLeaseOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderLeaseId, releaseLeaseOptions.LeaseIdRequired);
        request.AddHeader(Details::c_HeaderVersion, releaseLeaseOptions.ApiVersionParameter);
        if (releaseLeaseOptions.ClientRequestId.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderRequestId, releaseLeaseOptions.ClientRequestId.GetValue());
        }
        return ReleaseLeaseParseResponse(context, pipeline.Send(context, request));
      }

      struct ChangeLeaseOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string LeaseIdRequired; // Specifies the current lease ID on the resource.
        Azure::Core::Nullable<std::string>
            ProposedLeaseIdOptional; // Proposed lease ID, in a GUID string format. The File service
                                     // returns 400 (Invalid request) if the proposed lease ID is
                                     // not in the correct format. See Guid Constructor (String) for
                                     // a list of valid GUID string formats.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                             // limit that is recorded in the analytics logs when storage analytics
                             // logging is enabled.
      };

      static Azure::Core::Response<FileChangeLeaseResponse> ChangeLease(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const ChangeLeaseOptions& changeLeaseOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryComp, "lease");
        request.AddHeader(Details::c_HeaderAction, "change");
        if (changeLeaseOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(changeLeaseOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderLeaseId, changeLeaseOptions.LeaseIdRequired);
        if (changeLeaseOptions.ProposedLeaseIdOptional.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderProposedLeaseId,
              changeLeaseOptions.ProposedLeaseIdOptional.GetValue());
        }
        request.AddHeader(Details::c_HeaderVersion, changeLeaseOptions.ApiVersionParameter);
        if (changeLeaseOptions.ClientRequestId.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderRequestId, changeLeaseOptions.ClientRequestId.GetValue());
        }
        return ChangeLeaseParseResponse(context, pipeline.Send(context, request));
      }

      struct BreakLeaseOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        Azure::Core::Nullable<std::string>
            LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease is
                             // active and matches this ID.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            ClientRequestId; // Provides a client-generated, opaque value with a 1 KB character
                             // limit that is recorded in the analytics logs when storage analytics
                             // logging is enabled.
      };

      static Azure::Core::Response<FileBreakLeaseResponse> BreakLease(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const BreakLeaseOptions& breakLeaseOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryComp, "lease");
        request.AddHeader(Details::c_HeaderAction, "break");
        if (breakLeaseOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(breakLeaseOptions.Timeout.GetValue()));
        }
        if (breakLeaseOptions.LeaseIdOptional.HasValue())
        {
          request.AddHeader(Details::c_HeaderLeaseId, breakLeaseOptions.LeaseIdOptional.GetValue());
        }
        request.AddHeader(Details::c_HeaderVersion, breakLeaseOptions.ApiVersionParameter);
        if (breakLeaseOptions.ClientRequestId.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderRequestId, breakLeaseOptions.ClientRequestId.GetValue());
        }
        return BreakLeaseParseResponse(context, pipeline.Send(context, request));
      }

      struct UploadRangeOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string
            XMsRange; // Specifies the range of bytes to be written. Both the start and end of the
                      // range must be specified. For an update operation, the range can be up to 4
                      // MB in size. For a clear operation, the range can be up to the value of the
                      // file's full size. The File service accepts only a single byte range for the
                      // Range and 'x-ms-range' headers, and the byte range must be specified in the
                      // following format: bytes=startByte-endByte.
        FileRangeWriteType
            XMsWrite; // Specify one of the following options: - Update: Writes the bytes specified
                      // by the request body into the specified range. The Range and Content-Length
                      // headers must match to perform the update. - Clear: Clears the specified
                      // range and releases the space used in storage for that range. To clear a
                      // range, set the Content-Length header to zero, and set the Range header to a
                      // value that indicates the range to clear, up to maximum file size.
        int64_t ContentLength = int64_t(); // Specifies the number of bytes being transmitted in the
                                           // request body. When the x-ms-write header is set to
                                           // clear, the value of this header must be set to zero.
        Azure::Core::Nullable<std::string>
            ContentMD5; // An MD5 hash of the content. This hash is used to verify the integrity of
                        // the data during transport. When the Content-MD5 header is specified, the
                        // File service compares the hash of the content that has arrived with the
                        // header value that was sent. If the two hashes do not match, the operation
                        // will fail with error code 400 (Bad Request).
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease is
                             // active and matches this ID.
      };

      static Azure::Core::Response<FileUploadRangeResponse> UploadRange(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const UploadRangeOptions& uploadRangeOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryComp, "range");
        if (uploadRangeOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(uploadRangeOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderRange, uploadRangeOptions.XMsRange);
        request.AddHeader(
            Details::c_HeaderFileRangeWrite,
            FileRangeWriteTypeToString(uploadRangeOptions.XMsWrite));
        request.AddHeader(
            Details::c_HeaderContentLength, std::to_string(uploadRangeOptions.ContentLength));
        if (uploadRangeOptions.ContentMD5.HasValue())
        {
          request.AddHeader(Details::c_HeaderContentMD5, uploadRangeOptions.ContentMD5.GetValue());
        }
        request.AddHeader(Details::c_HeaderVersion, uploadRangeOptions.ApiVersionParameter);
        if (uploadRangeOptions.LeaseIdOptional.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderLeaseId, uploadRangeOptions.LeaseIdOptional.GetValue());
        }
        return UploadRangeParseResponse(context, pipeline.Send(context, request));
      }

      struct UploadRangeFromURLOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string TargetRange; // Writes data to the specified byte range in the file.
        std::string
            CopySource; // Specifies the URL of the source file or blob, up to 2 KB in length. To
                        // copy a file to another file within the same storage account, you may use
                        // Shared Key to authenticate the source file. If you are copying a file
                        // from another storage account, or if you are copying a blob from the same
                        // storage account or another storage account, then you must authenticate
                        // the source file or blob using a shared access signature. If the source is
                        // a public blob, no authentication is required to perform the copy
                        // operation. A file in a share snapshot can also be specified as a copy
                        // source.
        Azure::Core::Nullable<std::string>
            SourceRange; // Bytes of source data in the specified range.
        FileRangeWriteFromUrlType
            XMsWrite; // Only update is supported: - Update: Writes the bytes downloaded from the
                      // source url into the specified range.
        int64_t ContentLength = int64_t(); // Specifies the number of bytes being transmitted in the
                                           // request body. When the x-ms-write header is set to
                                           // clear, the value of this header must be set to zero.
        Azure::Core::Nullable<std::string>
            SourceContentCrc64; // Specify the crc64 calculated for the range of bytes that must be
                                // read from the copy source.
        Azure::Core::Nullable<std::string>
            SourceIfMatchCrc64; // Specify the crc64 value to operate only on range with a matching
                                // crc64 checksum.
        Azure::Core::Nullable<std::string>
            SourceIfNoneMatchCrc64; // Specify the crc64 value to operate only on range without a
                                    // matching crc64 checksum.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease is
                             // active and matches this ID.
      };

      static Azure::Core::Response<FileUploadRangeFromURLResponse> UploadRangeFromURL(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const UploadRangeFromURLOptions& uploadRangeFromURLOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryComp, "range");
        if (uploadRangeFromURLOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout,
              std::to_string(uploadRangeFromURLOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderRange, uploadRangeFromURLOptions.TargetRange);
        request.AddHeader(Details::c_HeaderCopySource, uploadRangeFromURLOptions.CopySource);
        if (uploadRangeFromURLOptions.SourceRange.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderSourceRange, uploadRangeFromURLOptions.SourceRange.GetValue());
        }
        request.AddHeader(
            Details::c_HeaderFileRangeWriteFromUrl,
            FileRangeWriteFromUrlTypeToString(uploadRangeFromURLOptions.XMsWrite));
        request.AddHeader(
            Details::c_HeaderContentLength,
            std::to_string(uploadRangeFromURLOptions.ContentLength));
        if (uploadRangeFromURLOptions.SourceContentCrc64.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderSourceContentCrc64,
              uploadRangeFromURLOptions.SourceContentCrc64.GetValue());
        }
        if (uploadRangeFromURLOptions.SourceIfMatchCrc64.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderSourceIfMatchCrc64,
              uploadRangeFromURLOptions.SourceIfMatchCrc64.GetValue());
        }
        if (uploadRangeFromURLOptions.SourceIfNoneMatchCrc64.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderSourceIfNoneMatchCrc64,
              uploadRangeFromURLOptions.SourceIfNoneMatchCrc64.GetValue());
        }
        request.AddHeader(Details::c_HeaderVersion, uploadRangeFromURLOptions.ApiVersionParameter);
        if (uploadRangeFromURLOptions.LeaseIdOptional.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderLeaseId, uploadRangeFromURLOptions.LeaseIdOptional.GetValue());
        }
        return UploadRangeFromURLParseResponse(context, pipeline.Send(context, request));
      }

      struct GetRangeListOptions
      {
        Azure::Core::Nullable<std::string>
            ShareSnapshot; // The snapshot parameter is an opaque DateTime value that, when present,
                           // specifies the share snapshot to query.
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            XMsRange; // Specifies the range of bytes over which to list ranges, inclusively.
        Azure::Core::Nullable<std::string>
            LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease is
                             // active and matches this ID.
      };

      static Azure::Core::Response<FileGetRangeListResponse> GetRangeList(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const GetRangeListOptions& getRangeListOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddQueryParameter(Details::c_QueryComp, "rangelist");
        if (getRangeListOptions.ShareSnapshot.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryShareSnapshot, getRangeListOptions.ShareSnapshot.GetValue());
        }
        if (getRangeListOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(getRangeListOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, getRangeListOptions.ApiVersionParameter);
        if (getRangeListOptions.XMsRange.HasValue())
        {
          request.AddHeader(Details::c_HeaderRange, getRangeListOptions.XMsRange.GetValue());
        }
        if (getRangeListOptions.LeaseIdOptional.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderLeaseId, getRangeListOptions.LeaseIdOptional.GetValue());
        }
        return GetRangeListParseResponse(context, pipeline.Send(context, request));
      }

      struct StartCopyOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        std::map<std::string, std::string>
            Metadata; // A name-value pair to associate with a file storage object.
        std::string
            CopySource; // Specifies the URL of the source file or blob, up to 2 KB in length. To
                        // copy a file to another file within the same storage account, you may use
                        // Shared Key to authenticate the source file. If you are copying a file
                        // from another storage account, or if you are copying a blob from the same
                        // storage account or another storage account, then you must authenticate
                        // the source file or blob using a shared access signature. If the source is
                        // a public blob, no authentication is required to perform the copy
                        // operation. A file in a share snapshot can also be specified as a copy
                        // source.
        Azure::Core::Nullable<std::string>
            FilePermission; // If specified the permission (security descriptor) shall be set for
                            // the directory/file. This header can be used if Permission size is <=
                            // 8KB, else x-ms-file-permission-key header shall be used. Default
                            // value: Inherit. If SDDL is specified as input, it must have owner,
                            // group and dacl. Note: Only one of the x-ms-file-permission or
                            // x-ms-file-permission-key should be specified.
        Azure::Core::Nullable<std::string>
            FilePermissionKey; // Key of the permission to be set for the directory/file. Note: Only
                               // one of the x-ms-file-permission or x-ms-file-permission-key should
                               // be specified.
        Azure::Core::Nullable<PermissionCopyModeType>
            XMsFilePermissionCopyMode; // Specifies the option to copy file security descriptor from
                                       // source file or to set it using the value which is defined
                                       // by the header value of x-ms-file-permission or
                                       // x-ms-file-permission-key.
        Azure::Core::Nullable<bool>
            FileCopyIgnoreReadOnly; // Specifies the option to overwrite the target file if it
                                    // already exists and has read-only attribute set.
        Azure::Core::Nullable<std::string>
            FileCopyFileAttributes; // Specifies either the option to copy file attributes from a
                                    // source file(source) to a target file or a list of attributes
                                    // to set on a target file.
        Azure::Core::Nullable<std::string>
            FileCopyFileCreationTime; // Specifies either the option to copy file creation time from
                                      // a source file(source) to a target file or a time value in
                                      // ISO 8601 format to set as creation time on a target file.
        Azure::Core::Nullable<std::string>
            FileCopyFileLastWriteTime; // Specifies either the option to copy file last write time
                                       // from a source file(source) to a target file or a time
                                       // value in ISO 8601 format to set as last write time on a
                                       // target file.
        Azure::Core::Nullable<bool>
            FileCopySetArchiveAttribute; // Specifies the option to set archive attribute on a
                                         // target file. True means archive attribute will be set on
                                         // a target file despite attribute overrides or a source
                                         // file state.
        Azure::Core::Nullable<std::string>
            LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease is
                             // active and matches this ID.
      };

      static Azure::Core::Response<FileStartCopyResponse> StartCopy(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const StartCopyOptions& startCopyOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        if (startCopyOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(startCopyOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderVersion, startCopyOptions.ApiVersionParameter);
        for (const auto& pair : startCopyOptions.Metadata)
        {
          request.AddHeader(Details::c_HeaderMetadata + pair.first, pair.second);
        }
        request.AddHeader(Details::c_HeaderCopySource, startCopyOptions.CopySource);
        if (startCopyOptions.FilePermission.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFilePermission, startCopyOptions.FilePermission.GetValue());
        }
        if (startCopyOptions.FilePermissionKey.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFilePermissionKey, startCopyOptions.FilePermissionKey.GetValue());
        }
        if (startCopyOptions.XMsFilePermissionCopyMode.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFilePermissionCopyMode,
              PermissionCopyModeTypeToString(
                  startCopyOptions.XMsFilePermissionCopyMode.GetValue()));
        }
        if (startCopyOptions.FileCopyIgnoreReadOnly.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderIgnoreReadOnly,
              (startCopyOptions.FileCopyIgnoreReadOnly.GetValue() ? "true" : "false"));
        }
        if (startCopyOptions.FileCopyFileAttributes.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileAttributes, startCopyOptions.FileCopyFileAttributes.GetValue());
        }
        if (startCopyOptions.FileCopyFileCreationTime.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileCreationTime,
              startCopyOptions.FileCopyFileCreationTime.GetValue());
        }
        if (startCopyOptions.FileCopyFileLastWriteTime.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderFileLastWriteTime,
              startCopyOptions.FileCopyFileLastWriteTime.GetValue());
        }
        if (startCopyOptions.FileCopySetArchiveAttribute.HasValue())
        {
          request.AddHeader(
              Details::c_HeaderSetArchiveAttribute,
              (startCopyOptions.FileCopySetArchiveAttribute.GetValue() ? "true" : "false"));
        }
        if (startCopyOptions.LeaseIdOptional.HasValue())
        {
          request.AddHeader(Details::c_HeaderLeaseId, startCopyOptions.LeaseIdOptional.GetValue());
        }
        return StartCopyParseResponse(context, pipeline.Send(context, request));
      }

      struct AbortCopyOptions
      {
        std::string CopyId; // The copy identifier provided in the x-ms-copy-id header of the
                            // original Copy File operation.
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
        Azure::Core::Nullable<std::string>
            LeaseIdOptional; // If specified, the operation only succeeds if the resource's lease is
                             // active and matches this ID.
      };

      static Azure::Core::Response<FileAbortCopyResponse> AbortCopy(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const AbortCopyOptions& abortCopyOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryComp, "copy");
        request.AddQueryParameter(Details::c_QueryCopyId, abortCopyOptions.CopyId);
        if (abortCopyOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(abortCopyOptions.Timeout.GetValue()));
        }
        request.AddHeader(Details::c_HeaderCopyActionAbortConstant, "abort");
        request.AddHeader(Details::c_HeaderVersion, abortCopyOptions.ApiVersionParameter);
        if (abortCopyOptions.LeaseIdOptional.HasValue())
        {
          request.AddHeader(Details::c_HeaderLeaseId, abortCopyOptions.LeaseIdOptional.GetValue());
        }
        return AbortCopyParseResponse(context, pipeline.Send(context, request));
      }

      struct ListHandlesOptions
      {
        Azure::Core::Nullable<std::string>
            Marker; // A string value that identifies the portion of the list to be returned with
                    // the next list operation. The operation returns a marker value within the
                    // response body if the list returned was not complete. The marker value may
                    // then be used in a subsequent call to request the next set of list items. The
                    // marker value is opaque to the client.
        Azure::Core::Nullable<int32_t>
            MaxResults; // Specifies the maximum number of entries to return. If the request does
                        // not specify maxresults, or specifies a value greater than 5,000, the
                        // server will return up to 5,000 items.
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        Azure::Core::Nullable<std::string>
            ShareSnapshot; // The snapshot parameter is an opaque DateTime value that, when present,
                           // specifies the share snapshot to query.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<FileListHandlesResponse> ListHandles(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const ListHandlesOptions& listHandlesOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Get, url);
        request.AddQueryParameter(Details::c_QueryComp, "listhandles");
        if (listHandlesOptions.Marker.HasValue())
        {
          request.AddQueryParameter(Details::c_QueryMarker, listHandlesOptions.Marker.GetValue());
        }
        if (listHandlesOptions.MaxResults.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryMaxResults, std::to_string(listHandlesOptions.MaxResults.GetValue()));
        }
        if (listHandlesOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(listHandlesOptions.Timeout.GetValue()));
        }
        if (listHandlesOptions.ShareSnapshot.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryShareSnapshot, listHandlesOptions.ShareSnapshot.GetValue());
        }
        request.AddHeader(Details::c_HeaderVersion, listHandlesOptions.ApiVersionParameter);
        return ListHandlesParseResponse(context, pipeline.Send(context, request));
      }

      struct ForceCloseHandlesOptions
      {
        Azure::Core::Nullable<int32_t>
            Timeout; // The timeout parameter is expressed in seconds. For more information, see <a
                     // href="https://docs.microsoft.com/en-us/rest/api/storageservices/Setting-Timeouts-for-File-Service-Operations?redirectedfrom=MSDN">Setting
                     // Timeouts for File Service Operations.</a>
        Azure::Core::Nullable<std::string>
            Marker; // A string value that identifies the portion of the list to be returned with
                    // the next list operation. The operation returns a marker value within the
                    // response body if the list returned was not complete. The marker value may
                    // then be used in a subsequent call to request the next set of list items. The
                    // marker value is opaque to the client.
        Azure::Core::Nullable<std::string>
            ShareSnapshot; // The snapshot parameter is an opaque DateTime value that, when present,
                           // specifies the share snapshot to query.
        std::string HandleId; // Specifies handle ID opened on the file or directory to be closed.
                              // Asterisk (�*�) is a wildcard that specifies all handles.
        std::string ApiVersionParameter
            = Details::c_DefaultServiceApiVersion; // Specifies the version of the operation to use
                                                   // for this request.
      };

      static Azure::Core::Response<FileForceCloseHandlesResponse> ForceCloseHandles(
          std::string url,
          Azure::Core::Http::HttpPipeline& pipeline,
          Azure::Core::Context context,
          const ForceCloseHandlesOptions& forceCloseHandlesOptions)
      {
        Azure::Core::Http::Request request(Azure::Core::Http::HttpMethod::Put, url);
        request.AddHeader(Details::c_HeaderContentLength, "0");
        request.AddQueryParameter(Details::c_QueryComp, "forceclosehandles");
        if (forceCloseHandlesOptions.Timeout.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryTimeout, std::to_string(forceCloseHandlesOptions.Timeout.GetValue()));
        }
        if (forceCloseHandlesOptions.Marker.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryMarker, forceCloseHandlesOptions.Marker.GetValue());
        }
        if (forceCloseHandlesOptions.ShareSnapshot.HasValue())
        {
          request.AddQueryParameter(
              Details::c_QueryShareSnapshot, forceCloseHandlesOptions.ShareSnapshot.GetValue());
        }
        request.AddHeader(Details::c_HeaderHandleId, forceCloseHandlesOptions.HandleId);
        request.AddHeader(Details::c_HeaderVersion, forceCloseHandlesOptions.ApiVersionParameter);
        return ForceCloseHandlesParseResponse(context, pipeline.Send(context, request));
      }

    private:
      static Azure::Core::Response<FileCreateResponse> CreateParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
        {
          // Success, File created.
          FileCreateResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.IsServerEncrypted
              = response.GetHeaders().at(Details::c_HeaderIsServerEncrypted) == "true";
          result.FilePermissionKey = response.GetHeaders().at(Details::c_HeaderFilePermissionKey);
          result.FileAttributes = response.GetHeaders().at(Details::c_HeaderFileAttributes);
          result.FileCreationTime = response.GetHeaders().at(Details::c_HeaderFileCreationTime);
          result.FileLastWriteTime = response.GetHeaders().at(Details::c_HeaderFileLastWriteTime);
          result.FileChangeTime = response.GetHeaders().at(Details::c_HeaderFileChangeTime);
          result.FileId = response.GetHeaders().at(Details::c_HeaderFileId);
          result.FileParentId = response.GetHeaders().at(Details::c_HeaderFileParentId);
          return Azure::Core::Response<FileCreateResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<FileDownloadResponse> DownloadParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Succeeded to read the entire file.
          FileDownloadResponse result;
          result.BodyStream = response.GetBodyStream();
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.Metadata = response.GetHeaders().at(Details::c_HeaderMetadata);
          result.ContentLength
              = std::stoll(response.GetHeaders().at(Details::c_HeaderContentLength));
          result.HttpHeaders.ContentType = response.GetHeaders().at(Details::c_HeaderContentType);
          result.ContentRange = response.GetHeaders().at(Details::c_HeaderContentRange);
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          if (response.GetHeaders().find(Details::c_HeaderContentMD5)
              != response.GetHeaders().end())
          {
            result.ContentMD5 = response.GetHeaders().at(Details::c_HeaderContentMD5);
          }
          result.HttpHeaders.ContentEncoding
              = response.GetHeaders().at(Details::c_HeaderContentEncoding);
          result.HttpHeaders.CacheControl = response.GetHeaders().at(Details::c_HeaderCacheControl);
          result.HttpHeaders.ContentDisposition
              = response.GetHeaders().at(Details::c_HeaderContentDisposition);
          result.HttpHeaders.ContentLanguage
              = response.GetHeaders().at(Details::c_HeaderContentLanguage);
          result.AcceptRanges = response.GetHeaders().at(Details::c_HeaderAcceptRanges);
          result.CopyCompletionTime = response.GetHeaders().at(Details::c_HeaderCopyCompletionTime);
          result.CopyStatusDescription
              = response.GetHeaders().at(Details::c_HeaderCopyStatusDescription);
          result.CopyId = response.GetHeaders().at(Details::c_HeaderCopyId);
          result.CopyProgress = response.GetHeaders().at(Details::c_HeaderCopyProgress);
          result.CopySource = response.GetHeaders().at(Details::c_HeaderCopySource);
          result.CopyStatus
              = CopyStatusTypeFromString(response.GetHeaders().at(Details::c_HeaderCopyStatus));
          result.FileContentMD5 = response.GetHeaders().at(Details::c_HeaderFileContentMD5);
          result.IsServerEncrypted
              = response.GetHeaders().at(Details::c_HeaderIsServerEncrypted) == "true";
          result.FileAttributes = response.GetHeaders().at(Details::c_HeaderFileAttributes);
          result.FileCreationTime = response.GetHeaders().at(Details::c_HeaderFileCreationTime);
          result.FileLastWriteTime = response.GetHeaders().at(Details::c_HeaderFileLastWriteTime);
          result.FileChangeTime = response.GetHeaders().at(Details::c_HeaderFileChangeTime);
          result.FilePermissionKey = response.GetHeaders().at(Details::c_HeaderFilePermissionKey);
          result.FileId = response.GetHeaders().at(Details::c_HeaderFileId);
          result.FileParentId = response.GetHeaders().at(Details::c_HeaderFileParentId);
          result.LeaseDuration = LeaseDurationTypeFromString(
              response.GetHeaders().at(Details::c_HeaderLeaseDuration));
          result.LeaseState
              = LeaseStateTypeFromString(response.GetHeaders().at(Details::c_HeaderLeaseState));
          result.LeaseStatus
              = LeaseStatusTypeFromString(response.GetHeaders().at(Details::c_HeaderLeaseStatus));
          return Azure::Core::Response<FileDownloadResponse>(
              std::move(result), std::move(responsePtr));
        }
        else if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::PartialContent)
        {
          // Succeeded to read a specified range of the file.
          FileDownloadResponse result;
          result.BodyStream = response.GetBodyStream();
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.Metadata = response.GetHeaders().at(Details::c_HeaderMetadata);
          result.ContentLength
              = std::stoll(response.GetHeaders().at(Details::c_HeaderContentLength));
          result.HttpHeaders.ContentType = response.GetHeaders().at(Details::c_HeaderContentType);
          result.ContentRange = response.GetHeaders().at(Details::c_HeaderContentRange);
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          if (response.GetHeaders().find(Details::c_HeaderContentMD5)
              != response.GetHeaders().end())
          {
            result.ContentMD5 = response.GetHeaders().at(Details::c_HeaderContentMD5);
          }
          result.HttpHeaders.ContentEncoding
              = response.GetHeaders().at(Details::c_HeaderContentEncoding);
          result.HttpHeaders.CacheControl = response.GetHeaders().at(Details::c_HeaderCacheControl);
          result.HttpHeaders.ContentDisposition
              = response.GetHeaders().at(Details::c_HeaderContentDisposition);
          result.HttpHeaders.ContentLanguage
              = response.GetHeaders().at(Details::c_HeaderContentLanguage);
          result.AcceptRanges = response.GetHeaders().at(Details::c_HeaderAcceptRanges);
          result.CopyCompletionTime = response.GetHeaders().at(Details::c_HeaderCopyCompletionTime);
          result.CopyStatusDescription
              = response.GetHeaders().at(Details::c_HeaderCopyStatusDescription);
          result.CopyId = response.GetHeaders().at(Details::c_HeaderCopyId);
          result.CopyProgress = response.GetHeaders().at(Details::c_HeaderCopyProgress);
          result.CopySource = response.GetHeaders().at(Details::c_HeaderCopySource);
          result.CopyStatus
              = CopyStatusTypeFromString(response.GetHeaders().at(Details::c_HeaderCopyStatus));
          result.FileContentMD5 = response.GetHeaders().at(Details::c_HeaderFileContentMD5);
          result.IsServerEncrypted
              = response.GetHeaders().at(Details::c_HeaderIsServerEncrypted) == "true";
          result.FileAttributes = response.GetHeaders().at(Details::c_HeaderFileAttributes);
          result.FileCreationTime = response.GetHeaders().at(Details::c_HeaderFileCreationTime);
          result.FileLastWriteTime = response.GetHeaders().at(Details::c_HeaderFileLastWriteTime);
          result.FileChangeTime = response.GetHeaders().at(Details::c_HeaderFileChangeTime);
          result.FilePermissionKey = response.GetHeaders().at(Details::c_HeaderFilePermissionKey);
          result.FileId = response.GetHeaders().at(Details::c_HeaderFileId);
          result.FileParentId = response.GetHeaders().at(Details::c_HeaderFileParentId);
          result.LeaseDuration = LeaseDurationTypeFromString(
              response.GetHeaders().at(Details::c_HeaderLeaseDuration));
          result.LeaseState
              = LeaseStateTypeFromString(response.GetHeaders().at(Details::c_HeaderLeaseState));
          result.LeaseStatus
              = LeaseStatusTypeFromString(response.GetHeaders().at(Details::c_HeaderLeaseStatus));
          return Azure::Core::Response<FileDownloadResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<FileGetPropertiesResponse> GetPropertiesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success.
          FileGetPropertiesResponse result;
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.Metadata = response.GetHeaders().at(Details::c_HeaderMetadata);
          result.FileType = response.GetHeaders().at(Details::c_HeaderFileType);
          result.ContentLength
              = std::stoll(response.GetHeaders().at(Details::c_HeaderContentLength));
          result.HttpHeaders.ContentType = response.GetHeaders().at(Details::c_HeaderContentType);
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          if (response.GetHeaders().find(Details::c_HeaderContentMD5)
              != response.GetHeaders().end())
          {
            result.ContentMD5 = response.GetHeaders().at(Details::c_HeaderContentMD5);
          }
          result.HttpHeaders.ContentEncoding
              = response.GetHeaders().at(Details::c_HeaderContentEncoding);
          result.HttpHeaders.CacheControl = response.GetHeaders().at(Details::c_HeaderCacheControl);
          result.HttpHeaders.ContentDisposition
              = response.GetHeaders().at(Details::c_HeaderContentDisposition);
          result.HttpHeaders.ContentLanguage
              = response.GetHeaders().at(Details::c_HeaderContentLanguage);
          result.CopyCompletionTime = response.GetHeaders().at(Details::c_HeaderCopyCompletionTime);
          result.CopyStatusDescription
              = response.GetHeaders().at(Details::c_HeaderCopyStatusDescription);
          result.CopyId = response.GetHeaders().at(Details::c_HeaderCopyId);
          result.CopyProgress = response.GetHeaders().at(Details::c_HeaderCopyProgress);
          result.CopySource = response.GetHeaders().at(Details::c_HeaderCopySource);
          result.CopyStatus
              = CopyStatusTypeFromString(response.GetHeaders().at(Details::c_HeaderCopyStatus));
          result.IsServerEncrypted
              = response.GetHeaders().at(Details::c_HeaderIsServerEncrypted) == "true";
          result.FileAttributes = response.GetHeaders().at(Details::c_HeaderFileAttributes);
          result.FileCreationTime = response.GetHeaders().at(Details::c_HeaderFileCreationTime);
          result.FileLastWriteTime = response.GetHeaders().at(Details::c_HeaderFileLastWriteTime);
          result.FileChangeTime = response.GetHeaders().at(Details::c_HeaderFileChangeTime);
          result.FilePermissionKey = response.GetHeaders().at(Details::c_HeaderFilePermissionKey);
          result.FileId = response.GetHeaders().at(Details::c_HeaderFileId);
          result.FileParentId = response.GetHeaders().at(Details::c_HeaderFileParentId);
          result.LeaseDuration = LeaseDurationTypeFromString(
              response.GetHeaders().at(Details::c_HeaderLeaseDuration));
          result.LeaseState
              = LeaseStateTypeFromString(response.GetHeaders().at(Details::c_HeaderLeaseState));
          result.LeaseStatus
              = LeaseStatusTypeFromString(response.GetHeaders().at(Details::c_HeaderLeaseStatus));
          return Azure::Core::Response<FileGetPropertiesResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<FileDeleteResponse> DeleteParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Accepted)
        {
          // Success (Accepted).
          FileDeleteResponse result;
          return Azure::Core::Response<FileDeleteResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<FileSetHTTPHeadersResponse> SetHTTPHeadersParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success
          FileSetHTTPHeadersResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.IsServerEncrypted
              = response.GetHeaders().at(Details::c_HeaderIsServerEncrypted) == "true";
          result.FilePermissionKey = response.GetHeaders().at(Details::c_HeaderFilePermissionKey);
          result.FileAttributes = response.GetHeaders().at(Details::c_HeaderFileAttributes);
          result.FileCreationTime = response.GetHeaders().at(Details::c_HeaderFileCreationTime);
          result.FileLastWriteTime = response.GetHeaders().at(Details::c_HeaderFileLastWriteTime);
          result.FileChangeTime = response.GetHeaders().at(Details::c_HeaderFileChangeTime);
          result.FileId = response.GetHeaders().at(Details::c_HeaderFileId);
          result.FileParentId = response.GetHeaders().at(Details::c_HeaderFileParentId);
          return Azure::Core::Response<FileSetHTTPHeadersResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<FileSetMetadataResponse> SetMetadataParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success (OK).
          FileSetMetadataResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.IsServerEncrypted
              = response.GetHeaders().at(Details::c_HeaderIsServerEncrypted) == "true";
          return Azure::Core::Response<FileSetMetadataResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<FileAcquireLeaseResponse> AcquireLeaseParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
        {
          // The Acquire operation completed successfully.
          FileAcquireLeaseResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.LeaseId = response.GetHeaders().at(Details::c_HeaderLeaseId);
          return Azure::Core::Response<FileAcquireLeaseResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<FileReleaseLeaseResponse> ReleaseLeaseParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // The Release operation completed successfully.
          FileReleaseLeaseResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          return Azure::Core::Response<FileReleaseLeaseResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<FileChangeLeaseResponse> ChangeLeaseParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // The Change operation completed successfully.
          FileChangeLeaseResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.LeaseId = response.GetHeaders().at(Details::c_HeaderLeaseId);
          return Azure::Core::Response<FileChangeLeaseResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<FileBreakLeaseResponse> BreakLeaseParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Accepted)
        {
          // The Break operation completed successfully.
          FileBreakLeaseResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.LeaseId = response.GetHeaders().at(Details::c_HeaderLeaseId);
          return Azure::Core::Response<FileBreakLeaseResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<FileUploadRangeResponse> UploadRangeParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
        {
          // Success (Created).
          FileUploadRangeResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          if (response.GetHeaders().find(Details::c_HeaderContentMD5)
              != response.GetHeaders().end())
          {
            result.ContentMD5 = response.GetHeaders().at(Details::c_HeaderContentMD5);
          }
          result.IsServerEncrypted
              = response.GetHeaders().at(Details::c_HeaderIsServerEncrypted) == "true";
          return Azure::Core::Response<FileUploadRangeResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<FileUploadRangeFromURLResponse> UploadRangeFromURLParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Created)
        {
          // Success (Created).
          FileUploadRangeFromURLResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.XMsContentCrc64 = response.GetHeaders().at(Details::c_HeaderXMsContentCrc64);
          result.IsServerEncrypted
              = response.GetHeaders().at(Details::c_HeaderIsServerEncrypted) == "true";
          return Azure::Core::Response<FileUploadRangeFromURLResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<FileGetRangeListResponse> GetRangeListParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success.
          const auto& bodyBuffer = response.GetBody();
          auto reader
              = XmlReader(reinterpret_cast<const char*>(bodyBuffer.data()), bodyBuffer.size());
          FileGetRangeListResponse result = bodyBuffer.empty()
              ? FileGetRangeListResponse()
              : FileGetRangeListResponseFromRangeList(RangeListFromXml(reader));
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.FileContentLength
              = std::stoll(response.GetHeaders().at(Details::c_HeaderFileContentLength));
          return Azure::Core::Response<FileGetRangeListResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Range RangeFromXml(XmlReader& reader)
      {
        auto result = Range();
        enum class XmlTagName
        {
          c_Unknown,
          c_Start,
          c_End,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "Start") == 0)
            {
              path.emplace_back(XmlTagName::c_Start);
            }
            else if (std::strcmp(node.Name, "End") == 0)
            {
              path.emplace_back(XmlTagName::c_End);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 1 && path[0] == XmlTagName::c_Start)
            {
              result.Start = std::stoll(node.Value);
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_End)
            {
              result.End = std::stoll(node.Value);
            }
          }
        }
        return result;
      }

      static std::vector<Range> RangeListFromXml(XmlReader& reader)
      {
        auto result = std::vector<Range>();
        enum class XmlTagName
        {
          c_Unknown,
          c_Ranges,
          c_Range,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "Ranges") == 0)
            {
              path.emplace_back(XmlTagName::c_Ranges);
            }
            else if (std::strcmp(node.Name, "Range") == 0)
            {
              path.emplace_back(XmlTagName::c_Range);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }

            if (path.size() == 2 && path[0] == XmlTagName::c_Ranges
                && path[1] == XmlTagName::c_Range)
            {
              result.emplace_back(RangeFromXml(reader));
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
          }
        }
        return result;
      }

      static FileGetRangeListResponse FileGetRangeListResponseFromRangeList(
          std::vector<Range> object)
      {
        FileGetRangeListResponse result;
        result.RangeList = std::move(object);

        return result;
      }
      static Azure::Core::Response<FileStartCopyResponse> StartCopyParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Accepted)
        {
          // The copy file has been accepted with the specified copy status.
          FileStartCopyResponse result;
          result.ETag = response.GetHeaders().at(Details::c_HeaderETag);
          result.LastModified = response.GetHeaders().at(Details::c_HeaderLastModified);
          result.CopyId = response.GetHeaders().at(Details::c_HeaderCopyId);
          result.CopyStatus
              = CopyStatusTypeFromString(response.GetHeaders().at(Details::c_HeaderCopyStatus));
          return Azure::Core::Response<FileStartCopyResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<FileAbortCopyResponse> AbortCopyParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::NoContent)
        {
          // The delete request was accepted and the file will be deleted.
          FileAbortCopyResponse result;
          return Azure::Core::Response<FileAbortCopyResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static Azure::Core::Response<FileListHandlesResponse> ListHandlesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success.
          const auto& bodyBuffer = response.GetBody();
          auto reader
              = XmlReader(reinterpret_cast<const char*>(bodyBuffer.data()), bodyBuffer.size());
          FileListHandlesResponse result = bodyBuffer.empty()
              ? FileListHandlesResponse()
              : FileListHandlesResponseFromListHandlesResponse(ListHandlesResponseFromXml(reader));
          result.HttpHeaders.ContentType = response.GetHeaders().at(Details::c_HeaderContentType);
          return Azure::Core::Response<FileListHandlesResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }

      static HandleItem HandleItemFromXml(XmlReader& reader)
      {
        auto result = HandleItem();
        enum class XmlTagName
        {
          c_Unknown,
          c_HandleId,
          c_Path,
          c_FileId,
          c_ParentId,
          c_SessionId,
          c_ClientIp,
          c_OpenTime,
          c_LastReconnectTime,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "HandleId") == 0)
            {
              path.emplace_back(XmlTagName::c_HandleId);
            }
            else if (std::strcmp(node.Name, "Path") == 0)
            {
              path.emplace_back(XmlTagName::c_Path);
            }
            else if (std::strcmp(node.Name, "FileId") == 0)
            {
              path.emplace_back(XmlTagName::c_FileId);
            }
            else if (std::strcmp(node.Name, "ParentId") == 0)
            {
              path.emplace_back(XmlTagName::c_ParentId);
            }
            else if (std::strcmp(node.Name, "SessionId") == 0)
            {
              path.emplace_back(XmlTagName::c_SessionId);
            }
            else if (std::strcmp(node.Name, "ClientIp") == 0)
            {
              path.emplace_back(XmlTagName::c_ClientIp);
            }
            else if (std::strcmp(node.Name, "OpenTime") == 0)
            {
              path.emplace_back(XmlTagName::c_OpenTime);
            }
            else if (std::strcmp(node.Name, "LastReconnectTime") == 0)
            {
              path.emplace_back(XmlTagName::c_LastReconnectTime);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 1 && path[0] == XmlTagName::c_HandleId)
            {
              result.HandleId = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_Path)
            {
              result.Path = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_FileId)
            {
              result.FileId = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_ParentId)
            {
              result.ParentId = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_SessionId)
            {
              result.SessionId = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_ClientIp)
            {
              result.ClientIp = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_OpenTime)
            {
              result.OpenTime = node.Value;
            }
            else if (path.size() == 1 && path[0] == XmlTagName::c_LastReconnectTime)
            {
              result.LastReconnectTime = node.Value;
            }
          }
        }
        return result;
      }

      static ListHandlesResponse ListHandlesResponseFromXml(XmlReader& reader)
      {
        auto result = ListHandlesResponse();
        enum class XmlTagName
        {
          c_Unknown,
          c_EnumerationResults,
          c_Entries,
          c_Handle,
          c_NextMarker,
        };
        std::vector<XmlTagName> path;

        while (true)
        {
          auto node = reader.Read();
          if (node.Type == XmlNodeType::End)
          {
            break;
          }
          else if (node.Type == XmlNodeType::EndTag)
          {
            if (path.size() > 0)
            {
              path.pop_back();
            }
            else
            {
              break;
            }
          }
          else if (node.Type == XmlNodeType::StartTag)
          {

            if (std::strcmp(node.Name, "EnumerationResults") == 0)
            {
              path.emplace_back(XmlTagName::c_EnumerationResults);
            }
            else if (std::strcmp(node.Name, "Entries") == 0)
            {
              path.emplace_back(XmlTagName::c_Entries);
            }
            else if (std::strcmp(node.Name, "Handle") == 0)
            {
              path.emplace_back(XmlTagName::c_Handle);
            }
            else if (std::strcmp(node.Name, "NextMarker") == 0)
            {
              path.emplace_back(XmlTagName::c_NextMarker);
            }
            else
            {
              path.emplace_back(XmlTagName::c_Unknown);
            }
            if (path.size() == 3 && path[0] == XmlTagName::c_EnumerationResults
                && path[1] == XmlTagName::c_Entries && path[2] == XmlTagName::c_Handle)
            {
              result.HandleList.emplace_back(HandleItemFromXml(reader));
              path.pop_back();
            }
          }
          else if (node.Type == XmlNodeType::Text)
          {
            if (path.size() == 2 && path[0] == XmlTagName::c_EnumerationResults
                && path[1] == XmlTagName::c_NextMarker)
            {
              result.NextMarker = node.Value;
            }
          }
        }
        return result;
      }

      static FileListHandlesResponse FileListHandlesResponseFromListHandlesResponse(
          ListHandlesResponse object)
      {
        FileListHandlesResponse result;
        result.HandleList = std::move(object.HandleList);
        result.NextMarker = std::move(object.NextMarker);

        return result;
      }
      static Azure::Core::Response<FileForceCloseHandlesResponse> ForceCloseHandlesParseResponse(
          Azure::Core::Context context,
          std::unique_ptr<Azure::Core::Http::RawResponse> responsePtr)
      {
        auto& response = *responsePtr;
        if (response.GetStatusCode() == Azure::Core::Http::HttpStatusCode::Ok)
        {
          // Success.
          FileForceCloseHandlesResponse result;
          result.marker = response.GetHeaders().at(Details::c_HeaderMarker);
          result.numberOfHandlesClosed
              = std::stoi(response.GetHeaders().at(Details::c_HeaderNumberOfHandlesClosed));
          result.numberOfHandlesFailedToClose
              = std::stoi(response.GetHeaders().at(Details::c_HeaderNumberOfHandlesFailedToClose));
          return Azure::Core::Response<FileForceCloseHandlesResponse>(
              std::move(result), std::move(responsePtr));
        }
        else
        {
          throw Azure::Storage::StorageError::CreateFromResponse(context, std::move(responsePtr));
        }
      }
    };

  }; // class ShareRestClient

}}}} // namespace Azure::Storage::Files::Shares
