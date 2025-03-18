#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include <iostream>
#include <vector>
#include <QDate>
#include <QDebug>

class AbstractSensor{
protected:
    std::string name;

public:
    AbstractSensor(const std::string& name = {});
    AbstractSensor(const AbstractSensor& sensor);

    std::string getName() const {return name;}

    void setName(const std::string& n);

    virtual const std::vector<double>* generate_values() = 0;
    virtual ~AbstractSensor() = 0;
};

#endif // ABSTRACTSENSOR_H
