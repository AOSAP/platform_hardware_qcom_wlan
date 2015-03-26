/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __WIFI_HAL_GSCAN_COMMAND_H__
#define __WIFI_HAL_GSCAN_COMMAND_H__

#include "common.h"
#include "cpp_bindings.h"
#ifdef __GNUC__
#define PRINTF_FORMAT(a,b) __attribute__ ((format (printf, (a), (b))))
#define STRUCT_PACKED __attribute__ ((packed))
#else
#define PRINTF_FORMAT(a,b)
#define STRUCT_PACKED
#endif
#include "qca-vendor.h"
#include "vendor_definitions.h"
#include "gscan.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef struct{
    u32 status;
    u32 num_channels;
    wifi_channel channels[];
} GScanGetValidChannelsRspParams;

typedef struct{
    u32 status;
    wifi_gscan_capabilities capabilities;
} GScanGetCapabilitiesRspParams;

typedef struct{
    u32 status;
} GScanStartRspParams;

typedef struct{
    u32 status;
} GScanStopRspParams;

typedef struct{
    u32 status;
} GScanSetBssidHotlistRspParams;

typedef struct{
    u32 status;
} GScanResetBssidHotlistRspParams;

typedef struct{
    u8  more_data;
    u32 num_cached_results;
    int lastProcessedScanId; /* Last scan id in gscan cached results block */
    u32 wifiScanResultsStartingIndex; /* For the lastProcessedScanId */
    u32 max;                /* max num of cached results specified by caller */
    wifi_cached_scan_results *cached_results;
} GScanGetCachedResultsRspParams;

typedef struct{
    u32 status;
} GScanSetSignificantChangeRspParams;

typedef struct{
    u32 status;
} GScanResetSignificantChangeRspParams;

typedef struct {
    int max_channels;
    wifi_channel *channels;
    int *number_channels;
} GScan_get_valid_channels_cb_data;

typedef struct{
    u32 status;
} GScanSetSsidHotlistRspParams;

typedef struct{
    u32 status;
} GScanResetSsidHotlistRspParams;

typedef struct{
    u32 status;
} GScanPnoSetlistRspParams;

typedef struct{
    u32 status;
} GScanPnoSetPasspointListRspParams;

typedef struct{
    u32 status;
} GScanPnoResetPasspointListRspParams;

typedef enum{
    eGScanRspParamsInvalid = 0,
    eGScanGetValidChannelsRspParams,
    eGScanGetCapabilitiesRspParams,
    eGScanGetCachedResultsRspParams,
    eGScanStartRspParams,
    eGScanStopRspParams,
    eGScanSetBssidHotlistRspParams,
    eGScanResetBssidHotlistRspParams,
    eGScanSetSignificantChangeRspParams,
    eGScanResetSignificantChangeRspParams,
    eGScanSetSsidHotlistRspParams,
    eGScanResetSsidHotlistRspParams,
    eGScanPnoSetListRspParams,
    eGScanPnoSetPasspointListRspParams,
    eGScanPnoResetPasspointListRspParams,
} eGScanRspRarams;

/* Response and Event Callbacks */
typedef struct {
    /* Various Events Callback */
    void (*get_capabilities)(int status, wifi_gscan_capabilities capabilities);
    void (*start)(int status);
    void (*stop)(int status);
    void (*set_bssid_hotlist)(int status);
    void (*reset_bssid_hotlist)(int status);
    void (*set_significant_change)(int status);
    void (*reset_significant_change)(int status);
    void (*on_hotlist_ap_found)(wifi_request_id id,
        unsigned num_results, wifi_scan_result *results);
    void (*on_hotlist_ap_lost)(wifi_request_id id,
        unsigned num_results, wifi_scan_result *results);
    void (*get_cached_results)(u8 more_data, u32 num_results);
    void (*on_significant_change)(wifi_request_id id,
                unsigned num_results,
                wifi_significant_change_result **results);
    /* Reported when report_threshold is reached in scan cache */
    void (*on_scan_results_available) (wifi_request_id id,
                                    unsigned num_results_available);
    /* Reported when each probe response is received, if report_events
     * enabled in wifi_scan_cmd_params
     */
    void (*on_full_scan_result) (wifi_request_id id, wifi_scan_result *result);
    /* Optional event - indicates progress of scanning statemachine */
    void (*on_scan_event) (wifi_scan_event event, unsigned status);
    void (*set_ssid_hotlist)(int status);
    void (*reset_ssid_hotlist)(int status);
    void (*on_hotlist_ssid_found)(wifi_request_id id,
            unsigned num_results, wifi_scan_result *results);
    void (*on_hotlist_ssid_lost)(wifi_request_id id,
            unsigned num_results, wifi_scan_result *results);
    void (*set_epno_list)(int status);
    void (*on_pno_network_found)(wifi_request_id id,
            unsigned num_results, wifi_scan_result *results);
    void (*set_passpoint_list)(int status);
    void (*reset_passpoint_list)(int status);
    void (*on_passpoint_network_found)(wifi_request_id id,
            unsigned num_matches,
            wifi_passpoint_match_result *results);
} GScanCallbackHandler;

class GScanCommand: public WifiVendorCommand
{
private:
    GScanStopRspParams                  *mStopGScanRspParams;
    GScanStartRspParams                 *mStartGScanRspParams;
    GScanSetBssidHotlistRspParams       *mSetBssidHotlistRspParams;
    GScanResetBssidHotlistRspParams     *mResetBssidHotlistRspParams;
    GScanSetSignificantChangeRspParams  *mSetSignificantChangeRspParams;
    GScanResetSignificantChangeRspParams*mResetSignificantChangeRspParams;
    GScanSetSsidHotlistRspParams        *mSetSsidHotlistRspParams;
    GScanResetSsidHotlistRspParams      *mResetSsidHotlistRspParams;
    GScanGetCapabilitiesRspParams       *mGetCapabilitiesRspParams;
    GScanGetCachedResultsRspParams      *mGetCachedResultsRspParams;
    GScanPnoSetlistRspParams            *mPnoSetListRspParams;
    GScanPnoSetPasspointListRspParams   *mPnoSetPasspointListRspParams;
    GScanPnoResetPasspointListRspParams *mPnoResetPasspointListRspParams;
    u32                                 mGetCachedResultsNumResults;
    GScanCallbackHandler                mHandler;
    int                                 mRequestId;
    int                                 *mChannels;
    int                                 mMaxChannels;
    int                                 *mNumChannelsPtr;
    bool                                mWaitforRsp;

public:
    GScanCommand(wifi_handle handle, int id, u32 vendor_id, u32 subcmd);
    virtual ~GScanCommand();

    /* This function implements creation of GSCAN specific Request
     * based on  the request type.
     */
    virtual int create();
    virtual int requestEvent();
    virtual int requestResponse();
    virtual int handleResponse(WifiEvent &reply);
    virtual int handleEvent(WifiEvent &event);
    virtual int setCallbackHandler(GScanCallbackHandler nHandler);
    virtual void setMaxChannels(int max_channels);
    virtual void setChannels(int *channels);
    virtual void setNumChannelsPtr(int *num_channels);
    virtual int allocRspParams(eGScanRspRarams cmd);
    virtual void freeRspParams(eGScanRspRarams cmd);
    virtual void getGetCapabilitiesRspParams(
                    wifi_gscan_capabilities *capabilities,
                    u32 *status);
    virtual void getStartGScanRspParams(u32 *status);
    virtual void getStopGScanRspParams(u32 *status);
    virtual void getSetBssidHotlistRspParams(u32 *status);
    virtual void getResetBssidHotlistRspParams(u32 *status);
    virtual void getSetSsidHotlistRspParams(u32 *status);
    virtual void getResetSsidHotlistRspParams(u32 *status);
    virtual void getSetSignificantChangeRspParams(u32 *status);
    virtual void getResetSignificantChangeRspParams(u32 *status);
    virtual wifi_error getGetCachedResultsRspParams(u8 *moreData,
                                                    int *numResults);
    virtual wifi_error copyCachedScanResults(int numResults,
                                             wifi_cached_scan_results *cached_results);
    virtual void getPnoSetListRspParams(u32 *status);
    virtual void getPnoSetPasspointListRspParams(u32 *status);
    virtual void getPnoResetPasspointListRspParams(u32 *status);
    /* Takes wait time in seconds. */
    virtual int timed_wait(u16 wait_time);
    virtual void waitForRsp(bool wait);
    virtual int gscan_get_cached_results(u32 num_results,
                                         wifi_cached_scan_results *results,
                                         u32 starting_index,
                                         struct nlattr **tb_vendor);
    virtual int allocCachedResultsTemp(int max,
                                       wifi_cached_scan_results *results);
};

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
