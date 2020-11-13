//
// Created by ingvord on 23.10.2020.
//
#include <sstream>
#include <tango.h>
#include "AsyncTangoAttribute.h"

void AsyncTangoAttribute::Execute() {
    result = device->read_attribute(name);
}

void AsyncTangoAttribute::HandleOKCallback() {
    Nan::HandleScope scope;
    double value;
    this->result >> value;

    auto localValue = Nan::New<v8::Number>(value);

    v8::Local<v8::Value> argv[] = {Nan::Null(), localValue};
    callback->Call(2, argv);
}

void AsyncTangoAttributeWriter::Execute() {
    Tango::DeviceAttribute da(this->name, this->value);

    result = device->write_read_attribute(da);
}
