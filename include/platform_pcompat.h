/*
Compatibility header for porting Pebble apps
*/
#ifndef _PLATFORM_PCOMPAT_H_
#include "platform.h"

#define PlatformTypeAplite PlatformTypeArroyo
#define PlatformTypeBasalt PlatformTypeBasin
#define PlatformTypeChalk PlatformTypeChannel
#define PlatformTypeDiorite PlatformTypeDelta
#define PlatformTypeEmery PlatformTypeEstuary

#define PBL_PLATFORM_TYPE_CURRENT BROOK_PLATFORM_TYPE_CURRENT

#define _PLATFORM_PCOMPAT_H_
#endif