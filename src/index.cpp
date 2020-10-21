//
// Created by ingvord on 20.10.2020.
//
#include <nan.h>
#include "DeviceProxy.h"

NAN_MODULE_INIT(InitModule) {
    DeviceProxy::Init(target);
}

NODE_MODULE(TangoRestServer, InitModule);
