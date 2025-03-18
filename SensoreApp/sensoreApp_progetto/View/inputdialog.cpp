#include "inputdialog.h"

InputDialog::InputDialog(const std::vector<std::vector<QString>*>* all_sensors, const bool& onUpdatePurpose): all_sensors(all_sensors), onUpdatePurpose(onUpdatePurpose){
    QVBoxLayout* vl = new QVBoxLayout();

    //v = new std::vector<std::string>();
    data = new std::vector<QString>();


    //NAME
    QHBoxLayout* nameLayout = new QHBoxLayout();
    QLabel* nameLabel =new QLabel("Name");
    nameLineEdit = new QLineEdit();
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameLineEdit);

    vl->addLayout(nameLayout);


    //MENU A TENDINA LISTA SENSORI
    tentMenu = new QComboBox();
    tentMenu->addItem("Seleziona il tipo di sensore");
    tentMenu->addItem("Temperatura");
    tentMenu->addItem("Rumore");
    tentMenu->addItem("Umidità");
    tentMenu->setMaximumHeight(25);
    if(onUpdatePurpose == true) tentMenu->setEnabled(false);

    vl->addWidget(tentMenu);

    //MENU A TENDINA LISTA STANZE
    tentRooms = new QComboBox();
    tentRooms->addItem("Seleziona una stanza");
    tentRooms->addItem("Auditorium");
    tentRooms->addItem("Camera da letto");
    tentRooms->addItem("Arena");
    tentRooms->setMaximumHeight(25);

    vl->addWidget(tentRooms);


    //CAMPI DATI
    QHBoxLayout* minLayout = new QHBoxLayout();
    min_edit = new QLineEdit();
    min_edit->setPlaceholderText("ad es. 0.0");
    QLabel* minLabel = new QLabel("min");

    minLayout->addWidget(minLabel);
    minLayout->addWidget(min_edit);

    QHBoxLayout* heightLayout = new QHBoxLayout();
    height_edit = new QLineEdit();
    height_edit->setPlaceholderText("ad es. 1.0");
    QLabel* heightLabel = new QLabel("Height");

    heightLayout->addWidget(heightLabel);
    heightLayout->addWidget(height_edit);

    QHBoxLayout* maxLayout = new QHBoxLayout();
    max_edit = new QLineEdit();
    max_edit->setPlaceholderText("ad es. 1.0");
    QLabel* maxLabel = new QLabel("max");

    maxLayout->addWidget(maxLabel);
    maxLayout->addWidget(max_edit);

    vl->addLayout(minLayout);
    vl->addLayout(maxLayout);
    vl->addLayout(heightLayout);

    max_edit->setVisible(false);
    min_edit->setVisible(false);
    maxLabel->setVisible(false);
    minLabel->setVisible(false);
    height_edit->setVisible(false);
    heightLabel->setVisible(false);
    tentRooms->setVisible(false);

    connect(tentMenu, &QComboBox::currentIndexChanged, this, [this, maxLabel, minLabel, heightLabel]{
        if(this->tentMenu->currentIndex() == 0){
            max_edit->setVisible(false);
            min_edit->setVisible(false);
            maxLabel->setVisible(false);
            minLabel->setVisible(false);
            tentRooms->setVisible(false);
            height_edit->setVisible(false);
            heightLabel->setVisible(false);
        }
        else if(this->tentMenu->currentIndex() == 1){

            max_edit->setVisible(true);
            min_edit->setVisible(true);
            max_edit->setPlaceholderText("ad es 15.0");
            maxLabel->setVisible(true);
            minLabel->setVisible(true);
            tentRooms->setVisible(false);
            height_edit->setVisible(false);
            heightLabel->setVisible(false);
            QValidator* v = new QDoubleValidator();
            max_edit->setValidator(v);
            min_edit->setValidator(v);
        }
        else if(this->tentMenu->currentIndex() == 2){
            min_edit->setVisible(true);
            minLabel->setVisible(true);
            tentRooms->setVisible(true);
            max_edit->setVisible(false);
            maxLabel->setVisible(false);
            height_edit->setVisible(false);
            heightLabel->setVisible(false);
            QValidator* v = new QDoubleValidator();
            min_edit->setValidator(v);

        }
        else if(this->tentMenu->currentIndex() == 3){
            min_edit->setVisible(true);
            minLabel->setVisible(true);
            tentRooms->setVisible(false);
            max_edit->setVisible(false);
            maxLabel->setVisible(false);
            height_edit->setVisible(true);
            heightLabel->setVisible(true);
            QValidator* v = new QDoubleValidator();
            height_edit->setValidator(v);
            min_edit->setValidator(v);
        }
    });

    //BOTTONI
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* ok = new QPushButton("Ok");
    QPushButton* cancel = new QPushButton("Cancel");
    buttonLayout->addWidget(cancel);
    buttonLayout->addWidget(ok);

    //Controllo che user
    //  -abbia selezionato giusto tipo sensore
    //  -abbia scelto un nome non doppio

    if(this->onUpdatePurpose == false){
        connect(ok, &QPushButton::clicked, this, [this]{
            if(this->checkName(this->nameLineEdit->text())){
                this->showError("Scegli un nome unico");
            }
            else if(tentMenu->currentIndex() == 0){
                this->showError("Scegli un tipo di sensore corretto");
            }
            else if(tentMenu->currentIndex() == 3){
                if(this->min_edit->text().toDouble() < 0 || this->min_edit->text().toDouble() > 100)this->showError("Scegli un valore tra 0 e 100");
                else if(this->height_edit->text().toDouble() < 0) this->showError("Scegli un'altezza positiva");
                else this->accept();
            }
            else if(tentMenu->currentIndex() == 2){
                if(tentRooms->currentIndex() == 0) this->showError("Seleziona una stanza corretta");
                else{
                    if(min_edit->text().toDouble() > 140) showError("Inserisci un valore sotto il limite udibile");
                    else if(min_edit->text().toDouble() < 0) showError("Inserisci un valore positivo");
                    else this->accept();
                }
            }
            else this->accept();
        });
    }
    else{
        connect(ok, &QPushButton::clicked, this, [this]{
            if(nameLineEdit->isModified()){
                if(this->checkName(this->nameLineEdit->text())){
                    this->showError("Scegli un nome unico");
                    return;
                }
            }
            else if(tentMenu->currentIndex() == 0){
                this->showError("Scegli un tipo di sensore corretto");
            }
            else if(tentMenu->currentIndex() == 3){
                if(this->min_edit->text().toDouble() < 0 || this->min_edit->text().toDouble() > 100) this->showError("Scegli un valore tra 0 e 100");
                else if(this->height_edit->text().toDouble() < 0) this->showError("Scegli un'altezza positiva");
                else this->accept();
            }
            else if(tentMenu->currentIndex() == 2){
                if(tentRooms->currentIndex() == 0) this->showError("Seleziona una stanza corretta");
                else{
                    if(min_edit->text().toDouble() > 140) showError("Inserisci un valore sotto il limite udibile");
                    else if(min_edit->text().toDouble() < 0) showError("Inserisci un valore positivo");
                    else this->accept();
                }
            }
        });
    }

    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);

    connect(this, &QDialog::accepted, this, [this]{

        QString name;
        QString min_value;
        QString max_value;
        QString height;
        QString stanza;
        QString type;

        type = this->tentMenu->currentText();

        if(this->nameLineEdit->text() == "" ){
            name = "Untitled";
        }
        else name = this->nameLineEdit->text();

        if(type == "Temperatura"){
            if((min_edit->text()).isEmpty()) min_value = "0.0";
            else min_value = this->min_edit->text();


            if((max_edit->text()).isEmpty()) max_value = "15.0";
            else max_value = this->max_edit->text();

            if(max_value.toDouble() < min_value.toDouble()){
                QString t;
                t = max_value;
                max_value = min_value;
                min_value = t;
            }
        }
        else if(type == "Rumore"){
            stanza = this->tentRooms->currentText();
            if((min_edit->text()).isEmpty()) min_value = "0.0";
            else min_value = this->min_edit->text();
            max_value = "140";
        }
        else if(type == "Umidità"){
            if((min_edit->text()).isEmpty()) min_value = "0.0";
            else min_value = this->min_edit->text();

            if((height_edit->text()).isEmpty()) height = "1.0";
            else height = this->height_edit->text();
        }

        data->push_back(name);
        data->push_back(min_value);
        data->push_back(max_value);
        data->push_back(height);
        data->push_back(stanza);
        data->push_back(type);
    });

    vl->addLayout(buttonLayout);
    this->setMaximumHeight(100);

    setWindowTitle("Input Sensor");

    setLayout(vl);
}



void InputDialog::showError(const QString& s){
    QMessageBox* errorBox = new QMessageBox();
    errorBox->setIcon(QMessageBox::Critical);
    errorBox->setText("Errore");
    errorBox->setInformativeText(s);
    errorBox->exec();
}



bool InputDialog::checkName(const QString& n){

    if(all_sensors == nullptr || all_sensors->empty()){
        return false;
    }

    std::vector<QString>* all_sensors_name = new std::vector<QString>();

    for(auto it = this->all_sensors->begin(); it != this->all_sensors->end(); ++it){
        all_sensors_name->push_back( (**it)[0] );
    }

    for(auto it = all_sensors_name->begin(); it != all_sensors_name->end(); ++it){
        if((*it) == n) return true;
    }

    return false;
}



void InputDialog::updateDialog(const std::vector<QString>* data){
    QString name = (*data)[0];
    QString min_value = (*data)[1];
    QString max_value = (*data)[2];
    QString height = (*data)[3];
    QString stanza = (*data)[4];
    QString type = (*data)[5];

    this->tentMenu->setCurrentText(type);

    this->nameLineEdit->setText(name);

    if(type == "Temperatura" || type == "Umidita"){
        this->min_edit->setText(min_value);
        this->max_edit->setText(max_value);
    }
    else if(type == "Rumore"){
        this->min_edit->setText(min_value);
        this->tentRooms->setCurrentText(stanza);
    }
    else if(type == "Umidità"){
        this->min_edit->setText(min_value);
        this->height_edit->setText(height);
    }

    this->setWindowTitle("Update Sensor");
}



std::vector<QString>* InputDialog::getVector() const {return data;}
