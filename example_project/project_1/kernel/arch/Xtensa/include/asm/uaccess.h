/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * User memory access support for Hexagon
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#ifndef _ASM_UACCESS_H
#define _ASM_UACCESS_H
/*
 * User space memory access functions
 */
/*
 * When a kernel-mode page fault is taken, the faulting instruction
 * address is checked against a table of exception_table_entries.
 * Each entry is a tuple of the address of an instruction that may
 * be authorized to fault, and the address at which execution should
 * be resumed instead of the faulting instruction, so as to effect
 * a workaround.
 */
#include <uapi/drm.h>


/*  Assembly somewhat optimized copy routines  */
unsigned long mmp(void *to, const void *from,
				     unsigned long n);

#define INLINE_COPY_FROM_USER
#define INLINE_COPY_TO_USER

__kernel_size_t __clear_user_hexagon(void *dest, unsigned long count);
#define __clear_user(a, s) __clear_user_hexagon((a), (s))



#endif
