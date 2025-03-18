#include "chartview.h"

ChartView::ChartView(){
    chart = new QChart();
    chart->legend()->hide();
    //chart->createDefaultAxes();

    series = new QLineSeries();
    series->setColor(Qt::blue);
    chart->addSeries(series);

    axisX = new QValueAxis();
    axisY = new QValueAxis();

    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);
    axisX->setRange(0, 100);
    axisY->setRange(0, 1);

    //DEPRECATED METHODS
    //chart->setAxisX(axisX, series);
    //chart->setAxisY(axisY, series);

    //NEW METHODS
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartLayout = new QVBoxLayout();
    chartLayout->addWidget(chartView);
}

void ChartView::drawChart(const std::vector<double>* v, const QString& type){
    double min = (*v)[0];
    double max = (*v)[1];

    this->clearChart(min, max);

    series = this->createSeries(v);
    chart->addSeries(series);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->update();
    if(type == "Temperatura") series->setColor(QColorConstants::Blue);
    else if(type == "Rumore") series->setColor(QColorConstants::Red);
    else if(type == "Umidità") series->setColor(QColorConstants::Yellow);
}

QLineSeries* ChartView::createSeries(const std::vector<double>* values){
    QLineSeries* res = new QLineSeries();

    if(!(values->empty())){
        for(long unsigned int i = 0; i<values->size()-2; i++){
            res->append(i, (*values)[i+2]);
        }
    }

    return res;
}

void ChartView::clearChart(const double& min, const double& max){
    if(series->count() != 0){
        series->clear();
        chart->removeSeries(series);
        series = new QLineSeries();
        chart->addSeries(series);
    }

    if(axisX) chart->removeAxis(axisX);
    if(axisY) chart->removeAxis(axisY);

    axisY->setRange(min, max);
    axisX->setRange(0, 100);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);
}

QChart* ChartView::getChart() const {return chart;}

QVBoxLayout* ChartView::getChartLayout() const {return chartLayout;}
