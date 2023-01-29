// ===================================================================================
// Project:   Rubber Ducky for CH551, CH552 and CH554
// Version:   v1.0
// Year:      2023
// Author:    Stefan Wagner
// Github:    https://github.com/wagiminator
// EasyEDA:   https://easyeda.com/wagiminator
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// Identifies itself as a USB HID keyboard and types a message when the touchkey is
// pressed. It can be used to control the PC via keyboard shortcuts.
//
// References:
// -----------
// - Blinkinlabs: https://github.com/Blinkinlabs/ch554_sdcc
// - Deqing Sun: https://github.com/DeqingSun/ch55xduino
// - Ralph Doncaster: https://github.com/nerdralph/ch554_sdcc
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
//
// Compilation Instructions:
// -------------------------
// - Chip:  CH551, CH552 or CH554
// - Clock: min. 6 MHz internal
// - Adjust the firmware parameters in include/config.h if necessary.
// - Make sure SDCC toolchain and Python3 with PyUSB is installed.
// - Press BOOT button on the board and keep it pressed while connecting it via USB
//   with your PC.
// - Run 'make flash'.
//
// Operating Instructions:
// -----------------------
// - Connect the board via USB to your PC. It should be detected as a HID keyboard.
// - Open a text editor und press the touchkey on the board.


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================

// Libraries
#include <system.h>                       // system functions
#include <touch.h>                        // touchkey functions
#include <neo.h>                          // NeoPixel functions
#include <usb_keyboard.h>                 // USB HID keyboard functions

// Prototypes for used interrupts
void USB_interrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) {
  USB_interrupt();
}

// ===================================================================================
// Main Function
// ===================================================================================
void main(void) {
  // Setup
  NEO_init();                             // init NeoPixel
  CLK_config();                           // configure system clock
  DLY_ms(5);                              // wait for clock to settle
  KBD_init();                             // init USB HID keyboard
  TOUCH_start(PIN_TOUCH);                 // start touchkey
  NEO_writeColor(0, 64, 0);               // set green color for pixel

  // Loop
  while(1) {
    if(TOUCH_pressed(PIN_TOUCH)) {        // touchkey pressed?
      NEO_writeColor(64, 0, 0);           // set red color for pixel
      KBD_print("Hello World!");          // type message
      KBD_type(KBD_KEY_RETURN);           // press return key
      NEO_writeColor(0, 64, 0);           // set green color for pixel
    }
  }
}
