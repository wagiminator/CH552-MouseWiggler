// ===================================================================================
// Project:   CAPS bLOCK for CH551, CH552 and CH554
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
// Tired of accidentally hitting the CAPS-LOCK key? It doesn't have to be. 
// CAPS bLOCK identifies itself as a USB HID keyboard and constantly monitors the
// state of CAPS LOCK. It immediately deactivates it if it has been activated.
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
// - Activate/deactivate the blocking function by pressing the touchkey. The NeoPixel
//   lights up when the function is activated.


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
  // Variables
  __bit activated = 1;                    // function activated flag
  uint8_t cnt = 1;                        // hue cycle counter
  uint8_t hue = 0;                        // hue cycle value

  // Setup
  CLK_config();                           // configure system clock
  DLY_ms(5);                              // wait for clock to settle
  KBD_init();                             // init USB HID keyboard
  NEO_init();                             // init NeoPixel
  WDT_start();                            // start watchdog
  TOUCH_start(PIN_TOUCH);                 // start touchkey

  // Loop
  while(1) {
    WDT_reset();                          // reset watchdog

    if(activated) {                       // blocking function activated?
      if(KBD_CAPS_LOCK_state) {           // CAPS LOCK was pressed?
        KBD_type(KBD_KEY_CAPS_LOCK);      // press CAPS LOCK to deactivate
        DLY_ms(50);                       // wait a bit
      }
      if(!--cnt) {                        // time to cycle hue?
        NEO_writeHue(hue, 0);             // set NeoPixel hue value
        NEO_latch();                      // latch pixel
        if(!hue--) hue = 191;             // cycle hue value
      }
    }

    if(TOUCH_pressed(PIN_TOUCH)) {        // touchkey pressed?
      activated = !activated;             // toggle activated flag
      if(!activated) {                    // blocking function deactivated?
        NEO_writeColor(0, 0, 0);          // turn off NeoPixel
        NEO_latch();                      // latch pixel
      }
      else cnt = 1;                       // activated? set pixel next
    }
  }
}
