#ifndef RUMORE_H
#define RUMORE_H

#include "Model/abstractsensor.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>

class Rumore: public AbstractSensor{
private:
    std::string stanza;
    double min;
    std::vector<double>* last_simulation;
public:
    Rumore(const std::string& name, const std::string& stanza, const double& min);

    std::vector<double>* generate_values();

    void setStanza(const std::string& new_stanza);
    void setMin(const double& m);
    void resetLastSim();
    void setLastSim(std::vector<double>* v);

    std::string getStanza() const;
    double getMin() const;
    std::vector<double>* getLastSim() const;

    ~Rumore();
};

#endif // RUMORE_H
