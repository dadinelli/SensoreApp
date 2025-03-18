#ifndef UMIDITA_H
#define UMIDITA_H

#include "Model/abstractsensor.h"
#include <vector>
#include <cmath>
#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>

class Umidita: public AbstractSensor{
private:
    double min;
    double height;
    std::vector<double>* last_simulation;
public:
    Umidita(const std::string& name, const double& min = 0.0, const double& height = 1.0);

    std::vector<double>* generate_values() override;
    void resetLastSim();
    std::vector<double>* getLastSim() const;
    void setLastSim(std::vector<double>* v);

    void setMin(const double& new_min);
    void setHeight(const double& new_height);

    const double& getMin() const;
    const double& getHeight() const;
};

#endif // UMIDITA_H
