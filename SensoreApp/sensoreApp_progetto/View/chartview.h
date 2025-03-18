#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <iostream>
#include <QtCharts>
#include <QtCharts/QLineSeries>

class ChartView: public QWidget{
    Q_OBJECT
private:
    QChart* chart;
    QLineSeries* series;
    QVBoxLayout* chartLayout;

    QValueAxis* axisX;
    QValueAxis* axisY;
public:
    ChartView();

    QLineSeries* createSeries(const std::vector<double>* values);
    void drawChart(const std::vector<double>* values, const QString& type);
    void clearChart(const double& min = 0.0, const double& max = 1.0);

    QVBoxLayout* getChartLayout() const;
    QChart* getChart() const;
};

#endif // CHARTVIEW_H
