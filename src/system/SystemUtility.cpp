#include "system/SystemUtility.hpp"

#include <windows.h>
#include <stdio.h>
#include <iphlpapi.h>
#pragma comment(lib, "IPHLPAPI.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x)   HeapFree(GetProcessHeap(), 0, (x))

std::string SystemUtility::getIPAddress()
{
    errno_t error;
    std::string networkIP, networkSubnetMask, networkDefaultGateway;
    PIP_ADAPTER_INFO adapterInformation;
    PIP_ADAPTER_INFO currentAdapterInformation = nullptr;
    DWORD getAdaptersInformationResult = 0;

    ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
    adapterInformation = (IP_ADAPTER_INFO*)MALLOC(sizeof(IP_ADAPTER_INFO));
    if (adapterInformation == nullptr)
        return "";

    if (GetAdaptersInfo(adapterInformation, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
    {
        FREE(adapterInformation);
        adapterInformation = (IP_ADAPTER_INFO*)MALLOC(ulOutBufLen);
        if (adapterInformation == nullptr)
            return "";
    }

    if ((getAdaptersInformationResult = GetAdaptersInfo(adapterInformation, &ulOutBufLen)) == NO_ERROR)
    {
        currentAdapterInformation = adapterInformation;
        while (currentAdapterInformation)
        {
            switch (currentAdapterInformation->Type)
            {
                case MIB_IF_TYPE_OTHER:
                {
                    // printf("Other\n");
                    break;
                }
                case MIB_IF_TYPE_ETHERNET:
                {
                    // printf("Ethernet\n");
                    break;
                }
                case MIB_IF_TYPE_TOKENRING:
                {
                    // printf("Token Ring\n");
                    break;
                }
                case MIB_IF_TYPE_FDDI:
                {
                    // printf("FDDI\n");
                    break;
                }
                case MIB_IF_TYPE_PPP:
                {
                    // printf("PPP\n");
                    break;
                }
                case MIB_IF_TYPE_LOOPBACK:
                {
                    // printf("Lookback\n");
                    break;
                }
                case MIB_IF_TYPE_SLIP:
                {
                    // printf("Slip\n");
                    break;
                }
                default:
                {
                    // printf("Unknown type %ld\n", pAdapter->Type);
                    break;
                }
            }

            networkIP = currentAdapterInformation->IpAddressList.IpAddress.String;
            networkSubnetMask = currentAdapterInformation->IpAddressList.IpMask.String;
            networkDefaultGateway = currentAdapterInformation->GatewayList.IpAddress.String;

            currentAdapterInformation = currentAdapterInformation->Next;
        }
    }
    else
    {
        // printf("GetAdaptersInfo failed with error: %d\n", getAdaptersInformationResult);
    }

    if (adapterInformation)
    {
        FREE(adapterInformation);
    }

    return networkIP;
}
