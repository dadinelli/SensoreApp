#include "abstractsensor.h"

AbstractSensor::AbstractSensor(const std::string& name): name(name){}
AbstractSensor::AbstractSensor(const AbstractSensor& sensor): name(sensor.name){}

void AbstractSensor::setName(const std::string& n){this->name = n;}
//std::vector<double>* AbstractSensor::generate_values(){}

AbstractSensor::~AbstractSensor(){}

