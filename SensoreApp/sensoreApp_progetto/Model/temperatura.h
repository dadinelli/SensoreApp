    #ifndef TEMPERATURA_H
#define TEMPERATURA_H

#include "Model/abstractsensor.h"
#include <vector>
#include <QWidget>
#include <QDate>

class Temperatura: public AbstractSensor{
private:
    double min;
    double max;
    std::vector<double>* last_simulation;
public:
    Temperatura(const std::string& name, const double& min = 0.0, const double& max = 1.0);
    std::vector<double>* generate_values() override;
    void resetLastSim();

    void setMin(double new_min);
    void setMax(double new_max);

    double getMin() const;
    double getMax() const;
    std::vector<double>* getLastSim() const;
    void setLastSim(std::vector<double>* v);

    ~Temperatura();
};

#endif // TEMPERATURA_H
