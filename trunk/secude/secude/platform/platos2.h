/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssysteme GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2001
 *
 ******************************************/

/*
 * Platform specific header for IBM OS/2, VisualAge C++
 */

#if !defined(SECUDE_CONF_INCLUDE) || !SECUDE_CONF_INCLUDE
#error do not include this file, include <secude/sec_conf.h>
#endif

#include <secude/conf_os2.h> /* This file will go away */

#define SEC_TARGET_OS_OS2 1
#define SEC_TARGET_OS_NAME "OS/2"
#define SEC_TARGET_API_OS2 1
#define SEC_TARGET_CPU_X86 1

#define USE_OWN_GETOPT 1


