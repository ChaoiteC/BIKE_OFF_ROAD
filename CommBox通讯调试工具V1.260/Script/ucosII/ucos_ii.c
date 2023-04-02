/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                          (c) Copyright 1992-2005, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
* File    : uCOS_II.C
* By      : Jean J. Labrosse
* Version : V2.80
*********************************************************************************************************
*/

#define  OS_GLOBALS                           /* Declare GLOBAL variables                              */
#include <..\\script\\ucosii\\ucos_ii.h>


#define  OS_MASTER_FILE                       /* Prevent the following files from including includes.h */
#include <..\\script\\ucosii\\os_core.c>
#include <..\\script\\ucosii\\os_flag.c>
#include <..\\script\\ucosii\\os_mbox.c>
#include <..\\script\\ucosii\\os_mem.c>
#include <..\\script\\ucosii\\os_mutex.c>
#include <..\\script\\ucosii\\os_q.c>
#include <..\\script\\ucosii\\os_sem.c>
#include <..\\script\\ucosii\\os_task.c>
#include <..\\script\\ucosii\\os_time.c>
