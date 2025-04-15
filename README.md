# ATtiny2313-Relay-Switch
switching Relays with ATtiny2313, compatible to KMtronic USB Relay Controller.

This code is inspired by the KMtronic One Relay USB Controller board.
The board uses a FT232R USB-UART Interface and a ATtiny2313 to switch a relay with simple USB communication.

The KMtronic commands are:

OFF command: FF 01 00 (HEX) or 255 1 0 (DEC)<br>
ON command: FF 01 01 (HEX) or 255 1 1 (DEC)

So it is easy to decode the protocol:<br>
[HEADER] [CHANNEL] [ON / OFF]

HEADER = 0xFF (255 DEC)<br>
CHANNEL = 0x01 (1 DEC)<br>
ON = 0x1 ( 1 DEC)<br>
OFF = 0x0 ( 0 DEC)<br>

The relay is connected on port PB4, which is Pin 16 of the ATtiny2313, which is Arduino GPIO pin 13.
Older KMtronic boards did not allow to read out the status. So I added this feature to ***KMtronic_emulator.ino***

Up to 8 channels can be addressed with ***KMtronic_emulator_8.ino***

See source code for more details of my protocol implementation.

![image](https://github.com/user-attachments/assets/2e424b96-ad64-40b4-9d2f-38bddf3a9368)
Basic circuit diagram of a USB relay using ATtiny2313 

