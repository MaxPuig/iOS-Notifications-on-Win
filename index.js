const notifier = require('node-notifier');
const { SerialPort } = require('serialport')
const { ReadlineParser } = require('@serialport/parser-readline')
const name_of_device = "CH340";
const baudRate = 115200;
let selected_port;


async function find_port() {
    const ports = await SerialPort.list();
    let found_port;
    ports.forEach(port => {
        if (port.friendlyName.toLowerCase().includes(name_of_device.toLowerCase())) {
            found_port = port.path;
        }
    });
    if (!found_port) {
        console.log('No port selected.\nListing ports:');
        ports.forEach(port => { console.log(port.path + ' - ' + port.friendlyName) });
    } else {
        return found_port;
    }
}

function notify(serial_data) {
    if (serial_data.startsWith('$s$')) {
        let text = serial_data.split('$*$');
        const title = text[1];
        const message = text[2];
        notifier.notify({
            title,
            message,
            icon: 'No Image',
            sound: true,
            timeout: 4,
            appID: '🔔📱 ' + text[0].substring(3),
            urgency: 'critical',
            actions: ['OK', 'Cancel']
        });
        notifier.on('click', function () {
            console.log('Clicked');
        });
    }
}

async function main() {
    selected_port = await find_port();
    if (!selected_port) return;
    console.log('Selected port: ' + selected_port);
    const port = new SerialPort({ path: selected_port, baudRate: baudRate });
    const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }));
    parser.on('data', notify)

}

main()