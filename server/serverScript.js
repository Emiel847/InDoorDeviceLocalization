var http = require('http');
var express = require('express');
var app = express();
var fs = require('fs');
var ttn = require('ttn');
//var images = require("images");

var appId = 'projlab_2tst';
var accessKey = 'ttn-account-v2.k-UdLimcxHKDoXLKitj-ryjzMzx4hYVA2urPGr9LP2M';

var client = new ttn.DataClient(appId, accessKey, 'eu.thethings.network:1883');

//console.log(client)
//client.on('uplink', function (msg) { console.log('Received message', msg);});

var output = {utcTime:"", verdiep:0, accesPoint:0, devId:""};
client.on("uplink", function (devId, payload) {
	
    console.log("*** Received uplink from*** ", devId)
	console.log(payload)
	console.log()
	
	output.utcTime = payload.metadata.time;
	output.verdiep = payload.payload_fields.verdiep;
	output.accesPoint = payload.payload_fields.accesPoint;
	output.devId = devId;
	
	console.log("utcTime ", output.utcTime);
	console.log("verdiep ", output.verdiep);
	console.log("accesPoint ", output.accesPoint);
	console.log("devId ", output.devId);
    console.log()
});

app.use(express.static(__dirname));
app.get('*', function(req, res){
    res.setHeader('Access-Control-Allow-Origin', '*');
	res.setHeader('Access-Control-Request-Method', '*');
	res.setHeader('Access-Control-Allow-Methods', 'OPTIONS, GET');
    res.setHeader('Access-Control-Allow-Headers', '*');
  });
app.listen(9000);

http.createServer(function (req, res) {
    res.setHeader('Access-Control-Allow-Origin', '*');
	res.setHeader('Access-Control-Request-Method', '*');
	res.setHeader('Access-Control-Allow-Methods', 'OPTIONS, GET');
    res.setHeader('Access-Control-Allow-Headers', '*');
    res.writeHead(200, {'Content-Type': 'application/json'});
    res.end(JSON.stringify(output));
  }).listen(8080);