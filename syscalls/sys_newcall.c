/*  asnux/kernel/compat.c
 *
 *  Kernel compatibililty routines for e.g. 32 bit syscall support
 *  on 64 bit kernels.
 *
 *  Copyright (C) 2002-2003 Stephen Rothwell, IBM Corporation
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#include <linux/linkage.h>
#include <linux/compat.h>
#include <linux/errno.h>
#include <linux/time.h>
#include <linux/signal.h>
#include <linux/sched.h>        /* for MAX_SCHEDULE_TIMEOUT */
#include <linux/syscalls.h>
#include <linux/unistd.h>
#include <linux/security.h>
#include <linux/timex.h>
#include <linux/migrate.h>
#include <linux/posix-timers.h>
#include <linux/times.h>
#include <linux/ptrace.h>
#include <linux/gfp.h>

#include <asm/uaccess.h>


asmlinkage int sys_newcall()
{
   printk("New call");
}
