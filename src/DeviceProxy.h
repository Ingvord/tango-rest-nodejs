//
// Created by ingvord on 21.10.2020.
//
#ifndef TANGO_REST_NODEJS_DEVICEPROXY_H
#define TANGO_REST_NODEJS_DEVICEPROXY_H

#include <nan.h>
#include <tango.h>

class DeviceProxy : public Nan::ObjectWrap {
private:
    Tango::DeviceProxy *_proxy;
public:
    std::string host;
    int port;
    std::string device;

    static NAN_MODULE_INIT(Init);

    static NAN_METHOD(New);

    static NAN_METHOD(ReadAttribute);

    static NAN_METHOD(WriteAttribute);

    static NAN_GETTER(HandleGetters);

    static NAN_SETTER(HandleSetters);

    static Nan::Persistent<v8::FunctionTemplate> constructor;
};


#endif //TANGO_REST_NODEJS_DEVICEPROXY_H
