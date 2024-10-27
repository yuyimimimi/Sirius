/* SPDX-License-Identifier: GPL-2.0 */

#ifndef __ASM_SH_TYPES_H
#define __ASM_SH_TYPES_H
#include <stdio.h>
#include <stdint.h>

/*
 * These aren't exported outside the kernel to avoid name space clashes
 */
#ifndef __ASSEMBLY__

typedef uint16_t insn_size_t;
typedef uint32_t reg_size_t;

#endif /* __ASSEMBLY__ */
#endif /* __ASM_SH_TYPES_H */
