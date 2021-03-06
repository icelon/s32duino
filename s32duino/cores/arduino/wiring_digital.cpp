/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"
#include "register_helpers.h"

//This is the list of the IOs configured

void pinMode(PinName p, uint32_t ulMode )
{
	switch (ulMode)
	{
	case INPUT:
		setGPIOMODER(p, 0b00);
		setGPIOPUPDR(p, 0b00);
		break;
	case INPUT_PULLUP:
		setGPIOMODER(p, 0b00);
		setGPIOPUPDR(p, 0b01);
		break;
	case INPUT_PULLDOWN:
		setGPIOMODER(p, 0b00);
		setGPIOPUPDR(p, 0b10);
		break;
	case OUTPUT:
		setGPIOMODER(p, 0b01);
		setGPIOPUPDR(p, 0b00);
		break;
	default:
		break;
	}
}

void digitalWrite( PinName p, uint32_t ulVal )
{
	// If the pin is an input, manipulate pullup
	if (getGPIOMODER(p) == 0b00) {
		setGPIOPUPDR(p, !!(ulVal));
	} else {
		if (ulVal)
			STM_PORT(p)->BSRR = STM_GPIO_PIN(p);
		else
			STM_PORT(p)->BRR = STM_GPIO_PIN(p);
	}
}


int digitalRead(PinName p)
{
	uint32_t level = STM_PORT(p)->IDR & STM_GPIO_PIN(p);
	return (level)? HIGH : LOW;
}
