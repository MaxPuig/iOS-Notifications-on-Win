from plyer import notification
import serial.tools.list_ports

########## Change these variables ##########
baudrate = 115200
name_of_device = "CH340"
########## Change these variables ##########

ports = list(serial.tools.list_ports.comports())


def choose_port():
    print("All ports:")
    for p in ports:
        print(p)
    for p in ports:
        if name_of_device.lower() in p.description.lower():
            print("Chosen port: " + p[0])
            return p[0]
    return False


def notify(title, message):
    notification.notify(
        title=title,
        message=message,
        # app_name='Here is the application name',
        app_icon='notif.ico'
    )


correct_port = choose_port()
if correct_port:
    esp = serial.Serial(correct_port, baudrate, timeout=1.0)
    while True:
        line = esp.readline()
        if line.startswith(b"$s$"):
            text = line.decode()
            text = text.split("$*$")
            notify(text[0][3:] + " | " + text[1], text[2])
