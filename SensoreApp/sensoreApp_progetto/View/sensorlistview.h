#ifndef SENSORLISTVIEW_H
#define SENSORLISTVIEW_H

#include <iostream>
#include <QListWidget>
#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <vector>
#include "View/sensorentry.h"
#include "View/inputdialog.h"

class SensorListView: public QObject{
    Q_OBJECT
private:
    QListWidget* list;
    std::vector<std::vector<QString>*>* data_vector;
public:
    SensorListView();

    void showDialog();
    void addQListWidgetItem(const std::vector<QString>* data);

    void openSensors(const std::vector<std::vector<QString>*>* all_data);

    void addSensor(const std::vector<QString>* data);
    QMessageBox* confirmBox() const;
    void showError(const QString& sensorName) const;

    QListWidget* getList() const;
    std::vector<std::vector<QString>*>* getVector_data() const;
signals:
    void addSensorSignal(const std::vector<QString>* data);
    void updateSensorSignal(const std::vector<QString>* data, const std::vector<QString>* new_data);
    void deleteSensorSignal(const std::vector<QString>* data);
};

#endif // SENSORLISTVIEW_H
