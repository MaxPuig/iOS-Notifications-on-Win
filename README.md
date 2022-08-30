# iOS Notifications on Windows using ESP32

This is a simple project to get notifications from an iOS device on a Windows PC using an **ESP32**.

## Requirements

- ESP32 board (Tested with NodeMCU)
- Windows PC
- iOS Device
- Python (Tested with Python 3.10.6)

## Setup
Clone repository: `git clone https://github.com/MaxPuig/iOS-Notifications-on-Win.git`

### Python packages:
- `pip install -r requirements.txt`
    - pyserial>=3.5
    - plyer>=2.0.0
### ESP32 Setup
- Install Arduino IDE
- Install package https://www.github.com/Smartphone-Companions/ESP32-ANCS-Notifications.git
- Upload [./ESP32_Notifications.ino](./ESP32_Notifications.ino) to the ESP32

## Usage

Run [main.py](main.py) for the first time. This will output something similar to this:
```
All ports:
COM1 - BlaBlaBla (COM1)
COM3 - USB-SERIAL CH340 (COM3)
```
In this case, we know that the ESP32 is connected to COM3, in which case we'll edit [main.py](main.py) and change the `name_of_device` variable to `CH340`. This will make the ESP32 connect to the correct port.
> Any string can be used as `name_of_device` as long as it is contained in the name. For example, `USB-SERIAL` would also work instead of `CH340`.

Once [main.py](main.py) has been changed, run it again, and you'll see:

```
All ports:
COM1 - BlaBlaBla (COM1)
COM3 - USB-SERIAL CH340 (COM3)
Chosen port: COM3
```
This means the python script has found the port and is reading its serial output.

**That's it!** The script will now output notifications from the iOS device to the Windows PC.

## Extra details

You will have to have the python file running for it to receive notifications.

I personally don't like having to access the console and manually type the commands to get the python file running, so a solution has been to write a `.bat` file that runs the python file. Double-click on [receive_notifications.bat](receive_notifications.bat) and that's it :)

## Want to run the python file on boot?
 - How to run a batch file each time the computer loads Windows: https://www.computerhope.com/issues/ch000322.htm