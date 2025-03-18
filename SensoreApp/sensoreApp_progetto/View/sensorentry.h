#ifndef SENSORENTRY_H
#define SENSORENTRY_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <iostream>
#include <vector>

class SensorEntry: public QObject{
    Q_OBJECT
private:
    const std::vector<QString>* data;
    QGroupBox* entry;
    QString name;
    QLabel* stanza_label;
    QLabel* min_label;
    QLabel* max_label;
    QLabel* height_label;
    QPushButton* edit_button;
    QPushButton* del_button;
public:
    SensorEntry(const std::vector<QString>* data);

    void setProperties(const std::vector<QString>* data);

    QGroupBox* getEntry() const;
signals:
    void onEditButton(const std::vector<QString>* data);
    void onDeleteButton(const std::vector<QString>* data);
};

#endif // SENSORENTRY_H
