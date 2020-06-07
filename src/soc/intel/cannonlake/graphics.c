/* SPDX-License-Identifier: GPL-2.0-or-later */


#include <device/device.h>
#include <drivers/intel/gma/gma.h>
#include <intelblocks/graphics.h>
#include <types.h>
#include "chip.h"

const struct i915_gpu_controller_info *
intel_igd_get_controller_info(const struct device *device)
{
	struct soc_intel_cannonlake_config *chip = device->chip_info;
	return &chip->gfx;
}
