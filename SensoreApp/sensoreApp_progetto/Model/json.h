#ifndef JSON_H
#define JSON_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include "Model/abstractsensor.h"
#include "Model/rumore.h"
#include "Model/temperatura.h"
#include "Model/umidita.h"

class Json{
private:
    QString name;
public:
    Json(const QString& name);

    void save(const std::vector<AbstractSensor*>* all_sensors);
    std::vector<std::vector<QString>*>* open(const QString& filePath) const;
};

#endif // JSON_H
