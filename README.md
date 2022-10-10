# iOS Notifications on Windows using ESP32

This is a simple project to get notifications from an iOS device on a Windows PC using an **ESP32**.

## Requirements

- ESP32 board (Tested with NodeMCU)
- Windows PC
- iOS Device
- Node.js (tested with v16.17.1) **or** Python (tested with v3.10.6)

## Setup
Clone repository: `git clone https://github.com/MaxPuig/iOS-Notifications-on-Win.git`

### ESP32 Setup
- Install Arduino IDE
- Install package https://www.github.com/Smartphone-Companions/ESP32-ANCS-Notifications.git
- Upload [./ESP32_Notifications.ino](./ESP32_Notifications.ino) to the ESP32

## Usage JavsScript (node.js) **or** Python
<details>
<summary>JavaScript</summary>

- Install node.js https://nodejs.org/en/download/
- Install dependencies `npm install`

Run [index.js](index.js) for the first time: `node index.js`. This will output something similar to this:
```
No port selected.
Listing ports:
COM1 - BlaBlaBla (COM1)
COM3 - USB-SERIAL CH340 (COM3)
```

In this case, we know that the ESP32 is connected to COM3, in which case we'll edit [index.js](index.js) and change the `name_of_device` variable to `CH340`. This will make the ESP32 connect to the correct port.
> Any string can be used as `name_of_device` as long as it is contained in the name. For example, `USB-SERIAL` would also work instead of `CH340`.

Once [index.js](index.js) has been changed, run it again, and you'll see:

```
Selected port: COM4
```
This means the js script has found the port and is reading its serial output.

**That's it!** The script will now output notifications from the iOS device to the Windows PC.
</details>

<details>
<summary>Python</summary>

- Install Python https://www.python.org/downloads/
- Install dependencies `pip install -r requirements.txt`
    - pyserial>=3.5
    - plyer>=2.0.0

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
</details>


## Extra details

You will have to have the python file running for it to receive notifications.

I personally don't like having to access the console and manually type the commands to get the python file running, so a solution has been to write a `.bat` file that runs the python file. Double-click on [receive_notifications.bat](receive_notifications.bat) and that's it :)

## Want to run the js/python file on boot?
### JavaScript
- Using PM2: 
    - https://pm2.keymetrics.io/
    - https://www.npmjs.com/package/pm2-windows-startup

- You'll have to enable scripts on boot: 
    - (Spanish) https://www.cdmon.com/es/blog/la-ejecucion-de-scripts-esta-deshabilitada-en-este-sistema-te-contamos-como-actuar
    - (English using Google Translate) https://www-cdmon-com.translate.goog/es/blog/la-ejecucion-de-scripts-esta-deshabilitada-en-este-sistema-te-contamos-como-actuar?_x_tr_sl=es&_x_tr_tl=en&_x_tr_hl=es&_x_tr_pto=wapp


### Python
- How to run a batch file each time the computer loads Windows: https://www.computerhope.com/issues/ch000322.htm