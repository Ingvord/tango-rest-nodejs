//
// Created by ingvord on 23.10.2020.
//
#include <sstream>
#include <tango.h>
#include "AsyncTangoAttribute.h"

void AsyncTangoAttribute::Execute() {
    std::stringstream ss;
    ss << "tango://" << this->host << ":" << this->port << "/" << this->device << "/" << this->name;
    std::string fqdn = ss.str();
    auto proxy = Tango::AttributeProxy(fqdn);
    result = proxy.read();
}

void AsyncTangoAttribute::HandleOKCallback() {
    Nan::HandleScope scope;
    double value;
    this->result >> value;

    auto localValue = Nan::New<v8::Number>(value);

    v8::Local<v8::Value> argv[] = {Nan::Null(), localValue};
    callback->Call(2, argv);
}
