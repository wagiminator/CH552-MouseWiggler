// ===================================================================================
// User Configurations for CH552E Mouse Wiggler Board
// ===================================================================================

#pragma once

// Pin definitions
#define PIN_TOUCH           P16       // pin connected to touch key
#define PIN_NEO             P17       // pin connected to NeoPixel

// NeoPixel configuration
#define NEO_GRB                       // type of pixel: NEO_GRB or NEO_RGB

// Touchkey configuration
#define TOUCH_TH_LOW        3600      // key pressed threshold
#define TOUCH_TH_HIGH       4000      // key released threshold

// USB device descriptor
#define USB_VENDOR_ID       0x16C0    // VID (shared www.voti.nl)
#define USB_PRODUCT_ID      0x27DB    // PID (shared HID-keyboards)
#define USB_DEVICE_VERSION  0x0100    // v1.0 (BCD-format)

// USB configuration descriptor
#define USB_MAX_POWER_mA    50        // max power in mA 

// USB descriptor strings
#define MANUFACTURER_STR    'w','a','g','i','m','i','n','a','t','o','r'
#define PRODUCT_STR         'R','u','b','b','e','r','D','u','c','k','y'
#define SERIAL_STR          'C','H','5','5','2','E'
#define INTERFACE_STR       'H','I','D','-','K','e','y','b','o','a','r','d'
