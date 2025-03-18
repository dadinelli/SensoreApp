#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <QObject>
#include <iostream>
#include <vector>
#include "Model/json.h"
#include "Model/abstractsensor.h"
#include "Model/rumore.h"
#include "Model/temperatura.h"
#include "Model/umidita.h"

class Controller: public QWidget{
    Q_OBJECT
private:
    std::vector<AbstractSensor*>* sensors;
public:
    explicit Controller();

    void save();

    void open();

    void addSensor(const std::vector<QString>* data);

    void checkSensors();

    AbstractSensor* findSensor(const QString& s) const;

    std::vector<double>* generateSimulation(const QString& sensor_name);

    void updateSensor(const std::vector<QString>* data, const std::vector<QString>* new_data);

    std::vector<double>* getLastSimulation(const QString& name) const;

    void setLastSimulation(const QString& name, std::vector<double>* last_simulation);

    void resetLastSimulation(const QString& name);

    void deleteSensor(const std::vector<QString>* data);

    std::vector<AbstractSensor*>* getVector() const;

signals:
    void onOpenTrigger(const std::vector<std::vector<QString>*>* data);
};

#endif // CONTROLLER_H
