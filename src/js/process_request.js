const Tango = require("bindings")("TangoRestServer");

const proxies = new Map();

function processGetRequest(req){
    const proxyId = `tango://${req.host}:${req.port}/${req.device}`;

    let proxy = proxies.get(proxyId);
    if(!proxy) {
        proxy = new Tango.DeviceProxy(req.host, parseInt(req.port), req.device);
        proxies.set(proxyId, proxy)
    }

    return new Promise((resolve, reject) => {
        proxy.readAttribute(req.name, (err, value) => {
            if(err) reject(err)
            else resolve(value)
        })
    })
}

function processPutRequest(req){
    const proxyId = `tango://${req.host}:${req.port}/${req.device}`;

    let proxy = proxies.get(proxyId);
    if(!proxy) {
        proxy = new Tango.DeviceProxy(req.host, parseInt(req.port), req.device);
        proxies.set(proxyId, proxy)
    }

    return new Promise((resolve, reject) => {
        proxy.writeAttribute(req.name, parseFloat(req.value), (err, value) => {
            if(err) reject(err)
            else resolve(value)
        })
    })
}

module.exports.processGetRequest = processGetRequest;
module.exports.processPutRequest = processPutRequest;
