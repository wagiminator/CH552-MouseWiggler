# Mouse Wiggler based on CH552E
Mouse Wiggler is a tool that simulates movements of the mouse pointer so that no screen saver is activated and the PC or notebook is not put to sleep. Since the board can be used in many ways, it can also become a rubber ducky or a caps blocker with the additional firmware that is included. It is controlled via the touch key at the end of the board and displays its status via an addressable LED (NeoPixel).

![MouseWiggler_pic1.jpg](https://raw.githubusercontent.com/wagiminator/CH552-MouseWiggler/main/documentation/MouseWiggler_pic1.jpg)

# Hardware
## Schematic
![MouseWiggler_wiring.png](https://raw.githubusercontent.com/wagiminator/CH552-MouseWiggler/main/documentation/MouseWiggler_wiring.png)

## CH552E 8-bit USB Device Microcontroller
The CH552E is a low-cost, enhanced E8051 core microcontroller compatible with the MCS51 instruction set. It has an integrated USB 2.0 controller with full-speed data transfer (12 Mbit/s) and supports up to 64 byte data packets with integrated FIFO and direct memory access (DMA). The CH552E has a factory built-in bootloader so firmware can be uploaded directly via USB without the need for an additional programming device.

![MouseWiggler_pic2.jpg](https://raw.githubusercontent.com/wagiminator/CH552-MouseWiggler/main/documentation/MouseWiggler_pic2.jpg)

# Software
## Mouse Wiggler
Mouse Wiggler is a tool that simulates movements of the mouse pointer so that no screen saver is activated and the PC or notebook is not put to sleep. The mouse pointer movements are imperceptibly small, so that you can continue to work normally on your PC even with the function activated.

Connect the board via USB to your PC. It should be detected as a HID mouse. Activate/deactivate the wiggle function by pressing the touchkey. The NeoPixel lights up and changes colors when the function is activated.

## Rubber Ducky
A rubber ducky is a small device that can be plugged into a computer just like a regular USB drive, and once plugged in, it can emulate a keyboard and inject keystrokes that can execute malicious code or exfiltrate data to the attacker. Of course, this version is completely harmless. It identifies itself as a USB HID keyboard and types a message when the touchkey is pressed. It can also be used to control the PC via keyboard shortcuts.

Connect the board via USB to your PC. It should be detected as a HID keyboard. Open a text editor und press the touchkey on the board.

## CAPS bLOCK
Tired of accidentally hitting the CAPS-LOCK key? It doesn't have to be. CAPS bLOCK identifies itself as a USB HID keyboard and constantly monitors the state of CAPS LOCK. It immediately deactivates it if it has been activated.

Connect the board via USB to your PC. It should be detected as a HID keyboard. Activate/deactivate the blocking function by pressing the touchkey. The NeoPixel lights up and changes colors when the function is activated.

## NeoTouch
Control the NeoPixel color by holding the touch key. It can be used as a simple USB light.

## TouchRaw
TouchRaw can be used to calibrate the touchkey. It continuously transmits the touchkey raw sample values via USB-CDC-serial.

Connect the board via USB to your PC. It should be detected as a CDC device. Open a serial monitor or a serial plotter and select the correct serial port (BAUD rate doesn't matter). The touchkey raw sample values are continuously transmitted via CDC. Press and release the touchkey, observe the change in the raw values and use them to determine the threshold values for config.h. Windows users may need to use the [Zadig tool](https://zadig.akeo.ie/) to install the correct CDC driver.

## Compiling and Installing Firmware
### Installing Toolchain for CH55x
Install the [CH55x Software Development Kit for the SDCC compiler](https://github.com/Blinkinlabs/ch554_sdcc). Follow the instructions on the website. In order for the programming tool and the I²C-Bridge software to work, Python3 must be installed on your system. To do this, follow these [instructions](https://www.pythontutorial.net/getting-started/install-python/). In addition [PyUSB](https://github.com/pyusb/pyusb) and [PySerial](https://github.com/pyserial/pyserial/) must be installed. On Linux (Debian-based), all of this can be done with the following commands:

```
sudo apt install sdcc python3 python3-pip
sudo pip install pyusb
sudo pip install pyserial
```

### Installing Drivers for the CH55x Bootloader
On Linux you do not need to install a driver. However, by default Linux will not expose enough permission to upload your code with the USB bootloader. In order to fix this, open a terminal and run the following commands:

```
echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="4348", ATTR{idProduct}=="55e0", MODE="666"' | sudo tee /etc/udev/rules.d/99-ch55x.rules
sudo service udev restart
```

On Windows you will need the [Zadig tool](https://zadig.akeo.ie/) to install the correct driver for both, the CH55x bootloader and the CDC device. Click "Options" and "List All Devices" to select the USB module, then install the libusb-win32 driver.

### Entering CH55x Bootloader Mode
A brand new chip starts automatically in bootloader mode as soon as it is connected to the PC via USB. Once firmware has been uploaded, the bootloader must be started manually for new uploads. To do this, the board must first be disconnected from the USB port and all voltage sources. Now press the BOOT button and keep it pressed while reconnecting the board to the USB port of your PC. The chip now starts again in bootloader mode, the BOOT button can be released and new firmware can be uploaded within the next couple of seconds.

### Compiling and Uploading Firmware
Open a terminal and navigate to the folder with the makefile. Run ```make flash``` to compile and upload the firmware. If you don't want to compile the firmware yourself, you can also upload the precompiled binary. To do this, just run ```python3 ./tools/chprog.py firmware.bin```.

# References, Links and Notes
1. [EasyEDA Design Files](https://oshwlab.com/wagiminator/ch552-usb2oled)
2. [CH552 Datasheet](http://www.wch-ic.com/downloads/CH552DS1_PDF.html)
3. [SDCC Compiler](https://sdcc.sourceforge.net/)
4. [CH55x SDK for SDCC](https://github.com/Blinkinlabs/ch554_sdcc)

![MouseWiggler_pic3.jpg](https://raw.githubusercontent.com/wagiminator/CH552-MouseWiggler/main/documentation/MouseWiggler_pic3.jpg)
![MouseWiggler_pic4.jpg](https://raw.githubusercontent.com/wagiminator/CH552-MouseWiggler/main/documentation/MouseWiggler_pic4.jpg)

# License
![license.png](https://i.creativecommons.org/l/by-sa/3.0/88x31.png)

This work is licensed under Creative Commons Attribution-ShareAlike 3.0 Unported License. 
(http://creativecommons.org/licenses/by-sa/3.0/)
