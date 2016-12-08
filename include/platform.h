/*
Platform type definitions
*/
#ifndef _PLATFORM_H_

enum PlatformType {
	PlatformTypeUnknown,
	PlatformTypeArroyo,		//144x168 2-color rectangle
	PlatformTypeBasin,		//144x168 64-color rectangle
	PlatformTypeChannel,	//180x180 64-color circular
	PlatformTypeDelta,		//144x168 2-color rectangle
	PlatformTypeEstuary,	//200x228 64-color rectangle
	PlatformTypeFjord		//default platform for brook
}

#define BROOK_PLATFORM_TYPE_CURRENT PlatformTypeFjord

#define _PLATFORM_H_
#endif