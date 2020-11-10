//
// Created by ingvord on 21.10.2020.
//
#include <iostream>
#include "DeviceProxy.h"
#include "AsyncTangoAttribute.h"

Nan::Persistent<v8::FunctionTemplate> DeviceProxy::constructor;

NAN_MODULE_INIT(DeviceProxy::Init) {
    v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(DeviceProxy::New);
    constructor.Reset(ctor);
    ctor->InstanceTemplate()->SetInternalFieldCount(1);
    ctor->SetClassName(Nan::New("DeviceProxy").ToLocalChecked());

    // link our getters and setter to the object property
    Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("host").ToLocalChecked(), DeviceProxy::HandleGetters,
                     DeviceProxy::HandleSetters);
    Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("port").ToLocalChecked(), DeviceProxy::HandleGetters,
                     DeviceProxy::HandleSetters);
    Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("device").ToLocalChecked(), DeviceProxy::HandleGetters,
                     DeviceProxy::HandleSetters);

    Nan::SetPrototypeMethod(ctor, "readAttribute", ReadAttribute);

    Nan::SetPrototypeMethod(ctor, "writeAttribute", WriteAttribute);

    target->Set(Nan::New("DeviceProxy").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(DeviceProxy::New) {
    // throw an error if constructor is called without new keyword
    if (!info.IsConstructCall()) {
        return Nan::ThrowError(Nan::New("DeviceProxy::New - called without new keyword").ToLocalChecked());
    }

    // expect exactly 3 arguments
    if (info.Length() != 3) {
        return Nan::ThrowError(Nan::New("DeviceProxy::New - expected arguments host, port, device").ToLocalChecked());
    }

    // expect arguments to be numbers
    if (!info[0]->IsString() || !info[1]->IsNumber() || !info[2]->IsString()) {
        return Nan::ThrowError(Nan::New("DeviceProxy::New - expected arguments to be numbers").ToLocalChecked());
    }

    // create a new instance and wrap our javascript instance
    auto proxy = new DeviceProxy();
    proxy->Wrap(info.Holder());

    // initialize it's values
    v8::String::Utf8Value host(info[0]->ToString());
    proxy->host = std::string(*host);
    proxy->port = info[1]->NumberValue();
    v8::String::Utf8Value device(info[2]->ToString());
    proxy->device = std::string(*device);

    std::stringstream ss;
    ss << "tango://" << proxy->host << ":" << proxy->port << "/" << proxy->device;
    std::string fqdn = ss.str();
    std::cout << "FQDN=" << fqdn << std::endl;
    proxy->_proxy = new Tango::DeviceProxy(fqdn);



    // return the wrapped javascript instance
    info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(DeviceProxy::ReadAttribute) {
    // unwrap this Vector
    auto self = Nan::ObjectWrap::Unwrap<DeviceProxy>(info.This());

    if (!info[0]->IsString()) {
        return Nan::ThrowError(Nan::New(
                "DeviceProxy::ReadAttribute - expected argument - attribute name - to be instance of string").ToLocalChecked());
    }

    v8::String::Utf8Value arg(info[0]->ToString());

    std::string attribute(*arg);
    std::cout << "Attribute=" << attribute << std::endl;

    //TODO clever logic
//    auto resp = self->_proxy->read_attribute(attribute);

//    double value;
//    resp >> value;
    // unwrap the Vector passed as argument
//    info.GetReturnValue().Set(value);
    auto callback = new Nan::Callback(info[1].As<v8::Function>());

    Nan::AsyncQueueWorker(new AsyncTangoAttribute(callback, self->host, self->port, self->device, attribute));

}

NAN_METHOD(DeviceProxy::WriteAttribute) {
        // unwrap this Vector
        auto self = Nan::ObjectWrap::Unwrap<DeviceProxy>(info.This());

        if (!info[0]->IsString()) {
            return Nan::ThrowError(Nan::New(
                    "DeviceProxy::WriteAttribute - expected argument - attribute name - to be instance of string").ToLocalChecked());
        }

        if (!info[1]->IsNumber()) {
            return Nan::ThrowError(Nan::New(
                    "DeviceProxy::WriteAttribute - expected argument - attribute value - to be instance of number").ToLocalChecked());
        }

        v8::String::Utf8Value arg(info[0]->ToString());
        auto value(info[1]->NumberValue());

        std::string attribute(*arg);
        std::cout << "Attribute=" << attribute << std::endl;

        //TODO clever logic
//    auto resp = self->_proxy->read_attribute(attribute);

//    double value;
//    resp >> value;
        // unwrap the Vector passed as argument
//    info.GetReturnValue().Set(value);
        auto callback = new Nan::Callback(info[2].As<v8::Function>());

        Nan::AsyncQueueWorker(new AsyncTangoAttributeWriter(callback, self->host, self->port, self->device, attribute, value));

}

NAN_GETTER(DeviceProxy::HandleGetters) {
    auto *self = Nan::ObjectWrap::Unwrap<DeviceProxy>(info.This());

    auto propertyName = std::string(*Nan::Utf8String(property));
    if (propertyName == "host") {
        info.GetReturnValue().SetUndefined();
    } else if (propertyName == "port") {
        info.GetReturnValue().Set(self->port);
    } else if (propertyName == "device") {
        info.GetReturnValue().SetUndefined();
    } else {
        info.GetReturnValue().Set(Nan::Undefined());
    }
}

NAN_SETTER(DeviceProxy::HandleSetters) {
    return Nan::ThrowError(Nan::New("UnsupportedOperation").ToLocalChecked());
}
