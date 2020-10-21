let TangoRestServer

if (process.env.DEBUG) {
    TangoRestServer = require('./build/Debug/TangoRestServer.node')
} else {
    TangoRestServer = require('./build/Release/TangoRestServer.node')
}

module.exports = TangoRestServer