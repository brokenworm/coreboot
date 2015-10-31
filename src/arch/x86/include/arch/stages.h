/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2010 coresystems GmbH
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __ARCH_STAGES_H
#define __ARCH_STAGES_H

#include <arch/cpu.h>

void asmlinkage copy_and_run(void);

static inline void stage_exit(void *entry)
{
	__asm__ volatile (
#ifdef __x86_64__
		"jmp  *%%rdi\n"
#else
		"jmp  *%%edi\n"
#endif
		:: "D"(entry)
	);
}
#endif
