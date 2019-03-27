
var http = require('http');
var ttn = require('ttn');


var appId = 'projlab_2tst';
var accessKey = 'ttn-account-v2.k-UdLimcxHKDoXLKitj-ryjzMzx4hYVA2urPGr9LP2M';

var client = new ttn.DataClient(appId, accessKey, 'eu.thethings.network:1883');

//console.log(client)
//client.on('uplink', function (msg) { console.log('Received message', msg);});

var output = "";

client.on("uplink", function (devID, payload) {
    console.log("*** Received uplink from*** ", devID)
    output = payload.payload_raw;
    console.log(payload.metadata.time);
    console.log()
})

http.createServer(function (req, res) {
    res.setHeader('Access-Control-Allow-Origin', '*');
	res.setHeader('Access-Control-Request-Method', '*');
	res.setHeader('Access-Control-Allow-Methods', 'OPTIONS, GET');
    res.setHeader('Access-Control-Allow-Headers', '*');
    res.writeHead(200, {'Content-Type': 'text/plain'});
    res.end(output);
  }).listen(8080);