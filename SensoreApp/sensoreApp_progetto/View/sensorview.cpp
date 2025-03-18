#include "sensorview.h"

SensorView::SensorView(QWidget* parent) : QWidget(parent){
    controller = new Controller();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* topLayout = new QHBoxLayout();
    QHBoxLayout *bottomLayout = new QHBoxLayout();

    QVBoxLayout* rightLayout = new QVBoxLayout();
    QVBoxLayout* scrollLayout = new QVBoxLayout();

    QVBoxLayout* chartLayout = new QVBoxLayout();


    //MENUBAR
    QMenuBar* menubar = new QMenuBar(this);

    QAction* saveAction = new QAction("Save", menubar);
    QAction* openAction = new QAction("Open", menubar);

    menubar->addAction(saveAction);
    menubar->addAction(openAction);

    connect(saveAction, &QAction::triggered, this, [this]{
        this->controller->save();
    });

    connect(openAction, &QAction::triggered, this, [this]{
        this->controller->open();
    });

    connect(controller, &Controller::onOpenTrigger, this, [this](const std::vector<std::vector<QString>*>* all_data){
        this->listView->openSensors(all_data);
    });

    //SCROLLAREA
    scrollArea = new QScrollArea();
    scrollLayout->addWidget(scrollArea);

    listView = new SensorListView();

    QVBoxLayout* list_container_layout = new QVBoxLayout();

    QListWidget* list = listView->getList();

    QPushButton* plus = new QPushButton("+");
    list_container_layout->addWidget(plus);
    list_container_layout->addWidget(list);

    QWidget* list_container = new QWidget();
    list_container->setLayout(list_container_layout);
    list_container_layout->setAlignment(Qt::AlignTop);

    scrollArea->setWidget(list_container);
    scrollArea->setWidgetResizable(true);


    //CLICK PLUS BUTTON
    connect(plus, &QPushButton::clicked, this, [this]{
        listView->showDialog();
    });


    //CLICK LIST ITEMS
    connect(list, &QListWidget::itemClicked, this, [this, list](QListWidgetItem* item){
        list->setCurrentItem(item);

        int index;

        if(list->currentRow() == -1) index = 0;
        else index = list->currentRow();

        if(list->count() == 0){
            this->chartView->clearChart();
        }
        else{
            std::vector<QString>* data = (*(listView->getVector_data()))[index];
            double min = ((*data)[1]).toDouble();
            double max = ((*data)[2]).toDouble();


            if((*data)[5] == "Temperatura") min = ((*data)[1]).toDouble();
            else if((*data)[5] == "Rumore"){
                min = 0;
                max = 140;
            }
            else if((*data)[5] == "Umidità"){
                min = 0;
                max = 100;
            }
            QString name = (*data)[0];

            if(this->controller->getLastSimulation(name)->size() == 0){
                chartView->clearChart(min, max);
            }
            else{
                std::vector<double>* sim = new std::vector<double>();
                sim = this->controller->getLastSimulation(name);
                chartView->drawChart(sim, (*data)[5]);
            }

            this->onSelectedEntry(data);
        }
    });


    //CONTROLLER ADD TRIGGER
    connect(listView, &SensorListView::addSensorSignal, this, [this](const std::vector<QString>* data){
        this->controller->addSensor(data);
    });


    //CONTROLLER UPDATE TRIGGER
    connect(listView, &SensorListView::updateSensorSignal, this, [this](const std::vector<QString>* data, const std::vector<QString>* new_data){
        this->controller->updateSensor(data, new_data);

        double min = (*new_data)[1].toDouble();
        double max = (*new_data)[2].toDouble();
        //double height = (*new_data)[3];

        if((*new_data)[5] == "Temperatura") this->chartView->clearChart(min, max);
        else if((*new_data)[5] == "Rumore") this->chartView->clearChart(0, 140);
        else if ((*new_data)[5] == "Umidità") this->chartView->clearChart(0, 100);
    });

    //CONTROLLER DELETE TRIGGER
    connect(listView, &SensorListView::deleteSensorSignal, this, [this, list](const std::vector<QString>* data){
        this->controller->deleteSensor(data);

        if(list->count() == 0){
            std::cout<<"list count == 0"<<std::endl;
            this->onSelectedEntry(nullptr);
        }
    });


    //SEARCHBAR
    QLineEdit* searchbar = new QLineEdit();
    searchbar->setPlaceholderText("Search...");
    scrollLayout->addWidget(searchbar);

    connect(searchbar, &QLineEdit::textChanged, this, [this, list](const QString &text){
        for(int i = 0; i<list->count(); i++){
            QListWidgetItem* item = list->item(i);
            std::vector<std::vector<QString>*>* all_data = listView->getVector_data();
            std::vector<QString>* data = (*all_data)[i];
            if( (*data)[0].contains(text, Qt::CaseInsensitive)) item->setHidden(false);
            else item->setHidden(true);
        }
    });

    searchbar->setMaximumWidth(275);
    scrollArea->setMaximumWidth(275);

    //CHART
    chartView = new ChartView();
    chartLayout->addLayout(chartView->ChartView::getChartLayout());



    //PLAY BUTTON
    play = new QPushButton();
    clear = new QPushButton();
    QVBoxLayout* playLayout = new QVBoxLayout();
    QWidget* w = new QWidget();
    QIcon playIcon = w->style()->standardIcon(QStyle::SP_MediaPlay);
    QIcon clearIcon = w->style()->standardIcon(QStyle::SP_DialogResetButton);
    play->setIcon(playIcon);
    clear->setIcon(clearIcon);

    play->setMaximumWidth(40);
    play->setMinimumHeight(40);
    clear->setMaximumWidth(40);
    clear->setMinimumHeight(40);

    playLayout->addWidget(play);
    playLayout->addWidget(clear);

    //PROPERTIES
    QString s = "Tipo: \n"
                "Nome: \n"
                "Valore minimo: \n"
                "Valore massimo: ";

    properties = new QLabel(s);
    properties->setMinimumHeight(75);
    properties->setMaximumHeight(75);

    //ICON
    QHBoxLayout* topRightLayout = new QHBoxLayout();
    iconLabel = new QLabel();
    iconLabel->setFixedSize(100, 100);

    topRightLayout->addWidget(iconLabel);
    topRightLayout->addWidget(properties);
    topRightLayout->addLayout(playLayout);

    //PLAY BUTTON
    connect(play, &QPushButton::clicked, this, [this, list]{

        if(list->currentRow() != -1){
            int index = list->currentRow();
            std::vector<QString>* data = new std::vector<QString>();
            data = (*(listView->getVector_data()))[index];
            std::vector<double>* values = this->controller->generateSimulation((*data)[0]);
            //il primo e secondo elemento del vettore contengno il valore minimo e massimo
            chartView->drawChart(values, (*data)[5]);
        }
    });


    //CLEAR BUTTON
    connect(clear, &QPushButton::clicked, this, [this, list]{
        if(list->count() > 0){
            int index;
            double min;

            if(list->currentRow() == -1){
                index = 0;
                chartView->clearChart();
            }
            else index = list->currentRow();

            std::vector<QString>* data = (*(listView->getVector_data()))[index];

            if((*data)[5] == "Temperatura") min = ((*data)[1]).toDouble();
            else if((*data)[5] == "Rumore") min = 0;

            double max = ((*data)[2]).toDouble();
            QString name = (*data)[0];

            this->controller->resetLastSimulation(name);
            this->chartView->clearChart(min, max);
        }
    });


    //WINDOW
    topLayout->addWidget(menubar);

    rightLayout->addLayout(topRightLayout);
    rightLayout->addLayout(chartLayout);

    bottomLayout->addLayout(scrollLayout);
    bottomLayout->addLayout(rightLayout);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);


    setWindowTitle("Sensor");
    setGeometry(100, 100, 700, 450);

    setLayout(mainLayout);
}



void SensorView::onSelectedEntry(const std::vector<QString>* data){
    QString p;

    if(data == nullptr){
        p = "Tipo: \n"
            "Nome: \n"
            "Valore minimo: \n"
            "Valore massimo: ";

        pixmap = QPixmap();
        iconLabel->setPixmap(pixmap);
        iconLabel->setScaledContents(true);
    }
    else if((*data)[5] == "Temperatura"){
        p = "Tipo: " + (*data)[5] + "\n"
            + "Nome: " + (*data)[0] + "\n"
            + "Valore minimo: " + (*data)[1] + "\n"
            + "Valore massimo: " + (*data)[2];

        pixmap = QPixmap("/home/dadi/UNI/UNI/PAO/Progetto PAO/sensoreApp_progetto/icons/temperatura.png");
        iconLabel->setPixmap(pixmap);
        iconLabel->setScaledContents(true);
    }
    else if( (*data)[5] == "Rumore"){
        p = "Tipo: " + (*data)[5] + "\n"
            + "Nome: " + (*data)[0] + "\n"
            + "Valore minimo: " + (*data)[1] + "\n"
            + "Stanza: " + (*data)[4];

        pixmap = QPixmap("/home/dadi/UNI/UNI/PAO/Progetto PAO/sensoreApp_progetto/icons/rumore.png");
        iconLabel->setPixmap(pixmap);
        iconLabel->setScaledContents(true);
    }
    else if((*data)[5] == "Umidità"){
        p = "Tipo: " + (*data)[5] + "\n"
            + "Nome: " + (*data)[0] + "\n"
            + "Valore minimo: " + (*data)[1] + "\n"
            + "Altezza: " + (*data)[3];

        pixmap = QPixmap("/home/dadi/UNI/UNI/PAO/Progetto PAO/sensoreApp_progetto/icons/umidita.png");
        iconLabel->setPixmap(pixmap);
        iconLabel->setScaledContents(true);

    }

    this->setProperties(p);
}


QLabel* SensorView::getProperties() const {return properties;}



void SensorView::setProperties(const QString& s) {this->properties->setText(s);}


