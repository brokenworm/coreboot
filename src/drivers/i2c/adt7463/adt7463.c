/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <device/device.h>
#include <console/console.h>
#include <device/smbus.h>

/**
 * Do some S2881-specific HWM initialization for the ADT7463 chip.
 *
 * Should be factored out so that it can be more general.
 *
 * See Analog Devices ADT7463 datasheet, Rev C (2004):
 * http://www.analog.com/en/prod/0,,766_825_ADT7463,00.html
 */
static void adt7463_init(struct device *adt7463)
{
	int result;

	printk(BIOS_DEBUG, "ADT7463 is %s\n", dev_path(adt7463));

	/* Set all fans to 'Fastest Speed Calculated by All 3 Temperature
	 * Channels Controls PWMx'.
	 */
	result = smbus_write_byte(adt7463, 0x5c, 0xc2);
	result = smbus_write_byte(adt7463, 0x5d, 0xc2);
	result = smbus_write_byte(adt7463, 0x5e, 0xc2);

	/* Make sure that our fans never stop when temp. falls below Tmin,
	 * but rather keep going at minimum duty cycle (applies to automatic
	 * fan control mode only).
	 */
	result = smbus_write_byte(adt7463, 0x62, 0xc0);

	/* Set minimum PWM duty cycle to 25%, rather than the default 50%. */
	result = smbus_write_byte(adt7463, 0x64, 0x40);
	result = smbus_write_byte(adt7463, 0x65, 0x40);
	result = smbus_write_byte(adt7463, 0x66, 0x40);

	/* Set Tmin to 55C, rather than the default 90C. Above this temperature
	 * the fans will start blowing harder as temperature increases
	 * (automatic mode only).
	 */
	result = smbus_write_byte(adt7463, 0x67, 0x37);
	result = smbus_write_byte(adt7463, 0x68, 0x37);
	result = smbus_write_byte(adt7463, 0x69, 0x37);

	/* Set THERM limit to 70C, rather than the default 100C.
	 * The fans will kick in at 100% if the sensors reach this temperature,
	 * (only in automatic mode, but supposedly even when hardware is
	 * locked up). This is a failsafe measure.
	 */
	result = smbus_write_byte(adt7463, 0x6a, 0x46);
	result = smbus_write_byte(adt7463, 0x6b, 0x46);
	result = smbus_write_byte(adt7463, 0x6c, 0x46);

	/* Remote temperature 1 offset (LSB == 0.25C). */
	result = smbus_write_byte(adt7463, 0x70, 0x02);

	/* Remote temperature 2 offset (LSB == 0.25C). */
	result = smbus_write_byte(adt7463, 0x72, 0x01);

	/* Set TACH measurements to normal (1/second). */
	result = smbus_write_byte(adt7463, 0x78, 0xf0);

	printk(BIOS_DEBUG, "ADT7463 properly initialized\n");
}

static struct device_operations adt7463_operations = {
	.read_resources = noop_read_resources,
	.set_resources = noop_set_resources,
	.init = adt7463_init,
};

static void enable_dev(struct device *dev)
{
	dev->ops = &adt7463_operations;
}

struct chip_operations drivers_i2c_adt7463_ops = {
	CHIP_NAME("adt7463")
	.enable_dev = enable_dev,
};
