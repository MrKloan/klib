/**
 * Name:    klib
 * Author:  Valentin Fries <contact@fries.io>
 * Version: 1.0.0-SNAPSHOT
 * Date:    29/07/2015
 * 
 * A Linux/Windows utilities library for facilitating the development of pure
 * C applications.
 */
#ifndef KLIB_H
#define	KLIB_H

#ifdef	__cplusplus
extern "C" {
#endif

//OS check & DLL support for Windows
#ifdef WIN32
    #define libimp __declspec(dllimport)
    #define libexp __declspec(dllexport)
#elif defined (linux)
    #define libimp
    #define libexp
#else
    #error "klib is not developped for your current operating system."
#endif

//Standard C headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
	
#ifdef WIN32
	#include <windows.h>
    #include <winsock2.h>
#endif

//klib headers
#include "System/Boolean.h"
#include "System/Timer.h"
#include "System/String.h"
	
#include "Network/Socket.h"
    
#include "Containers/Array.h"
#include "Containers/List.h"
#include "Containers/Map.h"
#include "Containers/Stack.h"
#include "Containers/Queue.h"
#include "Containers/Tree.h"

#ifdef	__cplusplus
}
#endif

#endif	/* KLIB_H */

