/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007 Advanced Micro Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <console/console.h>
#include <device/device.h>

static void init(struct device *dev)
{
	printk(BIOS_DEBUG, "MSM800SEV ENTER %s\n", __func__);
	printk(BIOS_DEBUG, "MSM800SEV EXIT %s\n", __func__);
}

static void mainboard_enable(struct device *dev)
{
        dev->ops->init = init;
}

struct chip_operations mainboard_ops = {
        .enable_dev = mainboard_enable,
};
