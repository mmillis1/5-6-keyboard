# Custom Dactyl Split Keyboard - mmillis

This is a custom split keyboard project using two Adafruit KB2040 (RP2040) boards, configured with QMK firmware.

## Hardware Specifications

### Microcontroller
- **Board**: Adafruit KB2040
- **Processor**: RP2040 (dual-core ARM Cortex-M0+)
- **Bootloader**: RP2040 UF2 bootloader with double-tap reset
- **Bootloader LED**: GP17

### Matrix Configuration (Current)
- **Rows per half**: 6 (configured)
- **Columns per half**: 6
- **Total keys**: 62 keys (as defined in layout)
- **Diode direction**: COL2ROW

### Pin Assignments (Adafruit KB2040)

#### Matrix Pins
**Row Pins**: GP27, GP26, GP18, GP20, GP19, GP10
**Column Pins**: GP4, GP5, GP6, GP7, GP8, GP9

#### Split Communication
**TRRS Serial Pin**: GP1 (connects left and right halves)

### Physical Connection
- TRRS cable connects both halves via GP1 pin
- USB cable connects to PRIMARY half (either left or right, determined by EE_HANDS)
- Secondary half gets power and data through TRRS cable

---

## Matrix Configuration Note

This keyboard is wired as a **6x6 matrix** (6 rows × 6 columns per half), even though it may visually appear to have only 5 rows. This is due to practical wiring considerations in the Dactyl design, where the thumb cluster keys are distributed across the matrix in a way that requires 6 row connections.

**Matrix Layout:**
- **Left half**: Rows 0-5, Columns 0-5 (36 positions available)
- **Right half**: Rows 6-11, Columns 0-5 (36 positions available)
- **Total**: 72 positions available, 62 keys used in current layout

---

## Software Setup

### Prerequisites

1. **Install QMK CLI**:
   ```bash
   python3 -m pip install --user qmk
   ```

2. **Verify installation**:
   ```bash
   qmk --version
   ```

3. **Setup QMK** (first time only):
   ```bash
   qmk setup
   ```
   This will clone the QMK firmware repository to `~/qmk_firmware`

### Project Structure

This keyboard uses a standalone structure compatible with QMK CLI:
```
keyboard/
├── keyboard.json          # Main keyboard configuration
├── info.json             # QMK metadata
├── rules.mk              # Build rules
├── keymaps/
│   └── default/
│       ├── config.h      # Keymap-specific config
│       ├── keymap.json   # Your key layout
│       └── rules.mk      # Keymap-specific rules
└── README.md             # This file
```

---

## Building the Firmware

### Compile the Firmware

From the root of this project directory:

```bash
qmk compile -kb handwired/mmillis -km default
```

### Expected Output

If successful, you'll see:
```
Compiling keymap with make handwired/mmillis:default
...
Copying handwired_mmillis_default.uf2 to qmk_firmware folder
```

The compiled firmware file will be:
- **Filename**: `handwired_mmillis_default.uf2`
- **Location**: `~/qmk_firmware/handwired_mmillis_default.uf2`

### Common Build Errors

**Error: "Keyboard handwired/mmillis does not exist"**
- Make sure you're running the command from this project directory
- Or use: `qmk compile -kb /full/path/to/keyboard -km default`

**Error: "Multiple keyboards found"**
- Use the full path to this directory
- QMK might find other keyboards with similar names

---

## Flashing the Firmware

You need to flash **both halves** of the keyboard. The process is identical for each half.

### Step-by-Step Flashing Process

#### 1. Enter Bootloader Mode

**Method 1: Double-Tap Reset (Configured)**
1. Quickly press the RESET button twice
2. The LED on GP17 should indicate bootloader mode
3. The KB2040 will appear as a USB drive named "RPI-RP2"

**Method 2: BOOT + RESET Buttons**
1. Hold down the BOOT button
2. Press and release the RESET button
3. Release the BOOT button
4. The KB2040 will appear as a USB drive named "RPI-RP2"

**Method 3: QK_BOOT Key (After First Flash)**
1. Press the QK_BOOT key in your keymap (top-left key on layer 2)
2. The keyboard will enter bootloader mode

#### 2. Mount the Drive

The KB2040 should appear as a mounted drive:
```bash
# On Linux, it typically mounts to:
/media/$USER/RPI-RP2
# or
/run/media/$USER/RPI-RP2
```

#### 3. Copy the Firmware

Drag and drop (or copy) the `.uf2` file to the RPI-RP2 drive:

```bash
cp ~/qmk_firmware/handwired_mmillis_default.uf2 /media/$USER/RPI-RP2/
```

#### 4. Firmware Flashes Automatically

- The KB2040 will automatically:
  1. Accept the .uf2 file
  2. Flash the firmware
  3. Reboot
  4. Unmount the drive
  5. Start running your keyboard firmware

#### 5. Repeat for Second Half

Repeat steps 1-4 for the other keyboard half.

---

## Handedness Configuration (EE_HANDS)

Your keyboard uses `EE_HANDS` - each half stores its identity (left or right) in EEPROM.

### Setting Handedness

After flashing both halves, you need to tell each half whether it's left or right.

#### Method 1: Using QMK CLI (Recommended)

**For the LEFT half**:
1. Connect the left half via USB
2. Run:
   ```bash
   qmk console
   ```
3. In the console, type:
   ```
   EH_LEFT
   ```
4. The EEPROM will be set to "left hand"

**For the RIGHT half**:
1. Connect the right half via USB
2. Run:
   ```bash
   qmk console
   ```
3. In the console, type:
   ```
   EH_RIGHT
   ```
4. The EEPROM will be set to "right hand"

#### Method 2: Using Handedness Files

Create special UF2 files that set handedness:

**For LEFT half**:
1. Enter bootloader mode
2. Flash `eeprom-lefthand.uf2` (need to create/download this)
3. Then flash your keyboard firmware

**For RIGHT half**:
1. Enter bootloader mode
2. Flash `eeprom-righthand.uf2` (need to create/download this)
3. Then flash your keyboard firmware

You can generate these files with:
```bash
qmk generate-dfu-header -kb handwired/mmillis -km default
```

### How EE_HANDS Works

- Each keyboard half checks its EEPROM on boot
- If EEPROM says "left", it acts as the left half
- If EEPROM says "right", it acts as the right half
- The setting persists across reboots and reflashes
- You only need to set it once per half (unless you erase EEPROM)

### Verifying Handedness

After setting:
1. Connect each half individually via USB
2. Type on the keys
3. Verify the correct keys are registering (left half = left side keys)
4. If reversed, swap the EEPROM settings

---

## Using Your Keyboard

### Normal Operation

1. Connect **both halves** with TRRS cable (IMPORTANT: Do this BEFORE connecting USB)
2. Connect **one half** (primary) to your computer via USB
3. Both halves will work
4. Either half can be the primary (thanks to EE_HANDS)

### Important Warnings

**NEVER hot-plug the TRRS cable while USB is connected!**
- This can short the serial pins
- May damage your KB2040 boards
- Always disconnect USB before plugging/unplugging TRRS

**TRRS Cable Must Use GP1**
- Your configuration uses GP1 for serial communication
- Make sure your TRRS cable is wired correctly
- Typical TRRS: Tip=VCC, Ring1=GND, Ring2=Data(GP1), Sleeve=GND

---

## Layers

Your keymap has 3 layers:

### Layer 0 (Base Layer)
- Standard QWERTY layout
- Modifiers and basic keys
- Access to layers 1 and 2 via layer-tap keys

### Layer 1 (Function Layer)
- F-keys (F1-F12)
- Arrow keys (HJKL or arrow cluster)
- Parentheses ( )
- Curly braces { }

### Layer 2 (System Layer)
- **QK_BOOT** (top-left key): Enter bootloader mode
- Special symbols ($, :, |)
- Brackets [ ]

---

## Troubleshooting

### Keyboard Not Detected

**Check:**
- Is the KB2040 powered? (LED should be on)
- Is USB cable working? (try another cable)
- Try another USB port
- Check if it appears as a USB device: `lsusb | grep RP2040`

### Only One Half Works

**Check:**
- Is TRRS cable connected properly?
- Did you connect TRRS **before** USB?
- Is GP1 pin connected on both halves?
- Try swapping which half is connected to USB

### Wrong Keys Register

**Check:**
- Handedness might be reversed (swap EE_HANDS settings)
- Matrix might be 5 rows not 6 (see section above)
- Wiring might not match pin configuration

### Keys Don't Register

**Check:**
- Are diodes installed correctly? (COL2ROW direction)
- Are row/column pins wired correctly?
- Test with QMK's matrix debug mode:
  ```bash
  qmk console
  ```
  Then type `MD` to enable matrix debug

### Compilation Errors

**Check:**
- QMK CLI is installed: `qmk --version`
- You're in the correct directory
- Files haven't been corrupted
- Try: `qmk clean` then recompile

### Serial Communication Issues

**Check:**
- GP1 is not being used by matrix scanning (it shouldn't be)
- TRRS cable has data wire connected to GP1 on both boards
- Cable is not damaged
- Try enabling serial debug in config

---

## Customizing Your Layout

### Edit Keymap

You can edit your keymap in two ways:

#### Option 1: QMK Configurator (GUI)
1. Go to https://config.qmk.fm
2. Click "Import QMK Keymap JSON File"
3. Upload `keymaps/default/keymap.json`
4. Make your changes visually
5. Download the new JSON
6. Replace `keymaps/default/keymap.json`
7. Recompile and flash

#### Option 2: Edit JSON Directly
1. Open `keymaps/default/keymap.json`
2. Modify the key codes in the layers array
3. Reference: https://docs.qmk.fm/keycodes
4. Save and recompile

### Convert to C Keymap

If you want more control:
```bash
qmk json2c keymaps/default/keymap.json > keymaps/default/keymap.c
```

Then edit the `.c` file for advanced features.

---

## Technical Details

### USB Configuration
- **Vendor ID**: 0x444D
- **Product ID**: 0x3536
- **Device Version**: 0.0.2
- **Manufacturer**: mmillis
- **Keyboard Name**: mmillis

### Features Enabled
- Bootmagic (Lite)
- Extrakey (media keys)
- Mousekey
- NKRO (N-Key Rollover)
- RGB Matrix support (hardware dependent)

### Features Disabled
- Audio
- RGB Lighting (underglow)
- Command
- Console (can be enabled for debugging)

### Split Configuration
- **Communication**: Serial (vendor driver - RP2040 PIO-based)
- **Pin**: GP1
- **Handedness**: EE_HANDS (EEPROM stored)
- **Bootmagic**: Matrix [0,0] (top-left key)

---

## Additional Resources

### QMK Documentation
- Main docs: https://docs.qmk.fm
- Configurator: https://config.qmk.fm
- Keycodes reference: https://docs.qmk.fm/keycodes
- Split keyboard guide: https://docs.qmk.fm/features/split_keyboard

### Adafruit KB2040
- Pinout: https://learn.adafruit.com/adafruit-kb2040/pinouts
- RP2040 datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf

### Dactyl Keyboard
- Original design: https://github.com/adereth/dactyl-keyboard
- Dactyl Manuform: https://github.com/abstracthat/dactyl-manuform

---

## Maintenance

### Reflashing Firmware

To update your firmware:
1. Make changes to keymap or config
2. Recompile: `qmk compile -kb handwired/mmillis -km default`
3. Flash both halves with new .uf2 file
4. Handedness is preserved (stored in EEPROM)

### Resetting to Factory

To completely reset a KB2040:
1. Enter bootloader mode
2. Flash `flash_nuke.uf2` from [RP2040 tools](https://github.com/dwelch67/raspberrypi-pico)
3. This erases all firmware and EEPROM
4. Reflash keyboard firmware
5. Re-set handedness with EE_HANDS

---

## License

This keyboard firmware is based on QMK, which is GPL v2 licensed.

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2024 mmillis

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
