#include "View/mainwindow.h"
#include "Model/temperatura.h"
#include "Model/abstractsensor.h"
#include "View/sensorview.h"

#include <iostream>
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    SensorView* s = new SensorView();
    s->show();

    return a.exec();
}
