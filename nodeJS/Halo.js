var http = require('http');
var fs = require('fs');
var ttn = require('ttn');
var images = require("images");

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

fs.readFile('./index.html', function (err, html) {

    if (err) throw err;

    http.createServer(function(request, response) {  

	response.setHeader('Access-Control-Allow-Origin', '*');
	response.setHeader('Access-Control-Request-Method', '*');
	response.setHeader('Access-Control-Allow-Methods', 'OPTIONS, GET');
    response.setHeader('Access-Control-Allow-Headers', '*');
        response.writeHeader(200, {"Content-Type": "text/html"});  
        response.write(html);  
        response.end(output);
    }).listen(8080);});