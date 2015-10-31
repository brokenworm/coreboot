/*
 * This file is part of the coreboot project.
 *
 * Copyright 2014 Google Inc.
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

#ifndef __MAINBOARD_GOOGLE_VEYRON_DANGER_BOARD_H
#define __MAINBOARD_GOOGLE_VEYRON_DANGER_BOARD_H

#include <boardid.h>
#include <gpio.h>

#define GPIO_BACKLIGHT	GPIO(7, A, 3)
#define GPIO_RESET	GPIO(0, B, 5)
#define GPIO_LCDC_BL	GPIO(7, A, 7)

void sdmmc_power_off(void);
void sdmmc_power_on(void);
void setup_chromeos_gpios(void);

#endif	/* __MAINBOARD_GOOGLE_VEYRON_DANGER_BOARD_H */
