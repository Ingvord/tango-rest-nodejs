const tango = require("bindings")("TangoRestServer")

const proxy = new tango.DeviceProxy('localhost', 10000, 'sys/tg_test/1');

// proxy.readAttribute('double_scalar_w', (err, result) => {
//         console.log(result)
// })


proxy.writeAttribute('double_scalar_w', 2.87, (err, result) => {
        console.log(result)
})




