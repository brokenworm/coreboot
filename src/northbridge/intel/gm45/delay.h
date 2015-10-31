/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2012 secunet Security Networks AG
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

#ifndef __NORTHBRIDGE_INTEL_GM45_DELAY_H__
#define __NORTHBRIDGE_INTEL_GM45_DELAY_H__

#include <delay.h>

void ns100delay(u32);
void udelay_from_reset(u32);

#endif /* __NORTHBRIDGE_INTEL_GM45_DELAY_H__ */
