//
// Created by ingvord on 23.10.2020.
//
#ifndef TANGORESTSERVER_ASYNCTANGOATTRIBUTE_H
#define TANGORESTSERVER_ASYNCTANGOATTRIBUTE_H

#include <nan.h>
#include <tango.h>

class AsyncTangoAttribute : public Nan::AsyncWorker {
protected:
    std::string host;
    int port;
    std::string device;
    std::string name;
    //TODO TangoProxy cache
    Tango::DeviceAttribute result;

public:
    AsyncTangoAttribute(Nan::Callback *callback, std::string host, int port, std::string device, std::string name) :
            Nan::AsyncWorker(callback),
            host(std::move(host)),
            port(port),
            device(std::move(device)),
            name(std::move(name)) {}

    void Execute();

    void HandleOKCallback();
};

class AsyncTangoAttributeWriter : public AsyncTangoAttribute {
private:
    double value;


public:
    AsyncTangoAttributeWriter(Nan::Callback *callback, std::string host, int port, std::string device, std::string name, double v) :
            AsyncTangoAttribute(callback,std::move(host),port,std::move(device),std::move(name)),
            value(v){}

    void Execute();
};


#endif //TANGORESTSERVER_ASYNCTANGOATTRIBUTE_H
