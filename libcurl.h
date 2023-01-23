#ifndef __LIB_CURL_H__
#define __LIB_CURL_H__

#pragma once

#ifdef _WIN64
#ifdef _DEBUG
#include "G:/dev_libs/curl-7.87.0/builds/libcurl-vc14-x64-debug-dll-ipv6-sspi-schannel/include/curl/curl.h"
#pragma comment(lib, "G:/dev_libs/curl-7.87.0/builds/libcurl-vc14-x64-debug-dll-ipv6-sspi-schannel/lib/libcurl_debug.lib")
#else
#include "G:/dev_libs/curl-7.87.0/builds/libcurl-vc14-x64-release-dll-ipv6-sspi-schannel/include/curl/curl.h"
#pragma comment(lib, "G:/dev_libs/curl-7.87.0/builds/libcurl-vc14-x64-release-dll-ipv6-sspi-schannel/lib/libcurl.lib")
#endif
#else
#ifdef _DEBUG
#include "G:/dev_libs/curl-7.87.0/builds/libcurl-vc14-x86-debug-dll-ipv6-sspi-schannel/include/curl/curl.h"
#pragma comment(lib, "G:/dev_libs/curl-7.87.0/builds/libcurl-vc14-x86-debug-dll-ipv6-sspi-schannel/lib/libcurl_debug.lib")
#else
#include "G:/dev_libs/curl-7.87.0/builds/libcurl-vc14-x86-release-dll-ipv6-sspi-schannel/include/curl/curl.h"
#pragma comment(lib, "G:/dev_libs/curl-7.87.0/builds/libcurl-vc14-x86-release-dll-ipv6-sspi-schannel/lib/libcurl.lib")
#endif
#endif

#endif 
