/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define EE_HANDS

/* Keyboard matrix assignments */
/*
 * NOTE: Matrix pins are COMMENTED OUT here because they are hardware configuration,
 * not keymap configuration. Matrix pins should be defined in keyboard.json (lines 34-35)
 * where they belong as part of the keyboard's hardware definition.
 *
 * Defining matrix pins at the keymap level is incorrect because:
 * - Matrix pins are determined by physical PCB wiring, not by keymap choice
 * - Different keymaps on the same keyboard should never have different matrix pins
 * - Having them here could cause confusion if you create additional keymaps
 *
 * The correct pin assignments are in keyboard.json:
 *   "rows": ["GP27", "GP26", "GP18", "GP20", "GP19", "GP10"]
 *   "cols": ["GP4", "GP5", "GP6", "GP7", "GP8", "GP9"]
 */

// OG
//#define MATRIX_ROW_PINS { GP29, GP28, GP27, GP26, GP22 }

// SparkFun Pro Micro RP2040
//#define MATRIX_ROW_PINS { GP27, GP26, GP22, GP20, GP23, GP21 }

// Adafruit KB2040 - COMMENTED OUT (defined in keyboard.json instead)
//#define MATRIX_ROW_PINS { GP27, GP26, GP18, GP20, GP19, GP10 }


// OG
//#define MATRIX_COL_PINS { GP2, GP3, GP4, GP5, GP6, GP7, GP8, GP9 }

// SparkFun Pro Micro RP2040
// #define MATRIX_COL_PINS { GP4, GP5, GP6, GP7, GP8, GP9 }

// Adafruit KB2040 - COMMENTED OUT (defined in keyboard.json instead)
//#define MATRIX_COL_PINS { GP4, GP5, GP6, GP7, GP8, GP9 }

/* Reset */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
