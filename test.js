const tango = require("bindings")("TangoRestServer")

const proxy = new tango.DeviceProxy('hzgxenvtest.desy.de', 10000, 'sys/tg_test/0');

proxy.readAttribute('double_scalar', (err, result) => {
    console.log(result)
})