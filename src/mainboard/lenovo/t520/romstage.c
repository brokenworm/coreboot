/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2007-2010 coresystems GmbH
 * Copyright (C) 2011 The ChromiumOS Authors.  All rights reserved.
 * Copyright (C) 2014 Vladimir Serbinenko
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

#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <timestamp.h>
#include <arch/byteorder.h>
#include <arch/io.h>
#include <device/pci_def.h>
#include <device/pnp_def.h>
#include <cpu/x86/lapic.h>
#include <pc80/mc146818rtc.h>
#include <arch/acpi.h>
#include <cbmem.h>
#include <console/console.h>
#include <northbridge/intel/sandybridge/sandybridge.h>
#include <northbridge/intel/sandybridge/raminit_native.h>
#include <southbridge/intel/bd82x6x/pch.h>
#include <southbridge/intel/bd82x6x/gpio.h>
#include <arch/cpu.h>
#include <cpu/x86/msr.h>
#include <cbfs.h>

void pch_enable_lpc(void)
{
	/* T520 EC Decode Range Port60/64, Port62/66 */
	/* Enable EC, PS/2 Keyboard/Mouse */
	pci_write_config16(PCH_LPC_DEV, LPC_EN,
			   CNF2_LPC_EN | CNF1_LPC_EN | MC_LPC_EN | KBC_LPC_EN |
			   COMA_LPC_EN);

	pci_write_config32(PCH_LPC_DEV, LPC_GEN1_DEC, 0x7c1601);
	pci_write_config32(PCH_LPC_DEV, LPC_GEN2_DEC, 0xc15e1);
	pci_write_config32(PCH_LPC_DEV, LPC_GEN4_DEC, 0x0c06a1);

	pci_write_config16(PCH_LPC_DEV, LPC_IO_DEC, 0x10);

	pci_write_config32(PCH_LPC_DEV, 0xac,
			   0x80010000);
}

void rcba_config(void)
{
	/* Disable unused devices (board specific) */
	RCBA32(FD) = 0x1ee51fe3;
	RCBA32(BUC) = 0;
}

const struct southbridge_usb_port mainboard_usb_ports[] = {
	{ 1, 1, 0 }, /* P0 left dual conn, OC 0 */
	{ 1, 1, 1 }, /* P1 system onboard USB port (eSATA), (EHCI debug), OC 1 */
	{ 1, 2, -1 }, /* P2: wimax / WLAN */
	{ 1, 1, -1 }, /* P3: WWAN, no OC */
	{ 1, 1, -1 }, /* P4: smartcard, no OC */
	{ 1, 1, -1 }, /* P5: ExpressCard, no OC */
	{ 0, 2, -1 }, /* P6: empty */
	{ 0, 2, -1 }, /* P7: to touch panel, no OC */
	{ 1, 1, 4 }, /* P8: left dual conn, OC4 */
	{ 1, 4, 5 }, /* P9: to system subcard back right, (EHCI debug), OC 5 */
	{ 1, 1, -1 }, /* P10: fingerprint reader, no OC */
	{ 1, 2, -1 }, /* P11: bluetooth, no OC. */
	{ 1, 1, -1 }, /* P12: docking, no OC */
	{ 1, 1, -1 }, /* P13: CAMERA (LCD), no OC */
};

void mainboard_get_spd(spd_raw_data *spd) {
	read_spd (&spd[0], 0x50);
	read_spd (&spd[2], 0x51);
}
