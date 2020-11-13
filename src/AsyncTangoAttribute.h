//
// Created by ingvord on 23.10.2020.
//
#ifndef TANGORESTSERVER_ASYNCTANGOATTRIBUTE_H
#define TANGORESTSERVER_ASYNCTANGOATTRIBUTE_H

#include <nan.h>
#include <tango.h>

class AsyncTangoAttribute : public Nan::AsyncWorker {
protected:
    Tango::DeviceProxy* device;
    std::string name;
    //TODO TangoProxy cache
    Tango::DeviceAttribute result;

public:
    AsyncTangoAttribute(Nan::Callback *callback, Tango::DeviceProxy* device, std::string name) :
            Nan::AsyncWorker(callback),
            device(device),
            name(std::move(name)) {}

    void Execute();

    void HandleOKCallback();
};

class AsyncTangoAttributeWriter : public AsyncTangoAttribute {
private:
    double value;


public:
    AsyncTangoAttributeWriter(Nan::Callback *callback, Tango::DeviceProxy* device, std::string name, double v) :
            AsyncTangoAttribute(callback,device,std::move(name)),
            value(v){}

    void Execute();
};


#endif //TANGORESTSERVER_ASYNCTANGOATTRIBUTE_H
