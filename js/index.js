//Libraries
const delay = require('delay');
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

//Declare arduino's COM port and init limiter
const port = new SerialPort('insertComPortHere', { baudRate: 9600 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));

//Confirms that the COM port is correct
port.on("open", () => {
  console.log('Serial port open.');
});

//Reads data via serial
parser.on('data', data =>{
  console.log('Data recieved from arduino:', data);
});



