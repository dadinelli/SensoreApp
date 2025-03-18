#ifndef SENSORVIEW_H
#define SENSORVIEW_H

#include <QWidget>
#include <vector>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCalendar>
#include <QMenuBar>
#include <QMessageBox>
#include <QScrollArea>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QtCharts>
#include <QString>
#include <QComboBox>
#include <QGroupBox>
#include "Controller/controller.h"
#include "chartview.h"
#include "sensorlistview.h"

class SensorView: public QWidget{
    Q_OBJECT
private:
    QMenuBar* menubar;
    QScrollArea* scrollArea;
    QPushButton* plus;
    QLineEdit* searchbar;
    QChart* chart;
    QPushButton* play;
    QPushButton* clear;
    QLabel* properties;
    SensorListView* listView;
    QPixmap pixmap;
    QLabel* iconLabel;

    Controller* controller;
    ChartView* chartView;

public:
    explicit SensorView(QWidget *parent = nullptr);

    void showDialog();

    //QVBoxLayout* getChartLayout() const;
    QLabel* getProperties() const;
    void setProperties(const QString& s);

    void onSelectedEntry(const std::vector<QString>* data = nullptr);
};

#endif // SENSORVIEW_H
