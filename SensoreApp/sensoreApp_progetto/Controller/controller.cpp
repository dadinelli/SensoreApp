#include "controller.h"

Controller::Controller(){
    sensors = new std::vector<AbstractSensor*>();
}

void Controller::save(){
    std::vector<AbstractSensor*>* all_sensors = sensors;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"), "",tr("JSON Files (*.json);;All Files (*)"));
    Json* j = new Json(fileName);
    j->save(all_sensors);
}

void Controller::open(){

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",tr("JSON Files (*.json);;All Files (*)"));

    if (fileName.isEmpty()) return;

    Json* j = new Json(fileName);
    const std::vector<std::vector<QString>*>* all_data = j->open(fileName);
    emit onOpenTrigger(all_data);
}

void Controller::addSensor(const std::vector<QString>* data){

    AbstractSensor* b = nullptr;

    std::string name = ((*data)[0]).toStdString();
    double min = (*data)[1].toDouble();
    double max = (*data)[2].toDouble();
    double height = (*data)[3].toDouble();
    std::string stanza = ((*data)[4]).toStdString();
    std::string type = ((*data)[5]).toStdString();

    if(type == "Temperatura"){
        Temperatura* a = new Temperatura(name, min, max);
        b = dynamic_cast<AbstractSensor*>(a);
    }
    else if(type == "Rumore"){
        Rumore* a = new Rumore(name, stanza, min);
        b = dynamic_cast<AbstractSensor*>(a);
    }
    else if(type == "Umidità"){
        Umidita* a = new Umidita(name, min, height);
        b = dynamic_cast<AbstractSensor*>(a);
    }

    if(b){
        sensors->push_back(b);
    }
}



void Controller::checkSensors(){
    for(auto it = sensors->begin(); it != sensors->end(); ++it){
        std::cout<< (*it)->getName() <<std::endl;
    }
}



AbstractSensor* Controller::findSensor(const QString& s) const {
    for(auto it = sensors->begin(); it != sensors->end(); ++it){
        if((*it)->getName() == s.toStdString()) return *it;
    }
    return nullptr;
}



std::vector<double>* Controller::generateSimulation(const QString& sensor_name){
    std::vector<double>* res = new std::vector<double>();

    AbstractSensor* a = findSensor(sensor_name);
    if(a){
        if(dynamic_cast<Temperatura*>(a)){
            auto b = dynamic_cast<Temperatura*>(a);
            res = b->generate_values();
        }
        if(dynamic_cast<Rumore*>(a)){
            auto b = dynamic_cast<Rumore*>(a);
            res = b->generate_values();
        }
        if(dynamic_cast<Umidita*>(a)){
            auto b = dynamic_cast<Umidita*>(a);
            res = b->generate_values();
        }
    }

    return res;
}



void Controller::updateSensor(const std::vector<QString>* data, const std::vector<QString>* new_data){
    AbstractSensor* a = this->findSensor((*data)[0]);

    std::string name = ((*new_data)[0]).toStdString();
    double min = (*new_data)[1].toDouble();
    double max = (*new_data)[2].toDouble();
    double height = (*data)[3].toDouble();
    std::string stanza = (*new_data)[4].toStdString();
    std::string type = (*new_data)[5].toStdString();

    if(type == "Temperatura"){
        Temperatura* c = dynamic_cast<Temperatura*>(a);
        if(c){                                          //se il tipo nuovo e vecchio selezionato è temperatura
            c->Temperatura::setMin(min);
            c->Temperatura::setMax(max);
            c->Temperatura::resetLastSim();
        }
        else{                                           //se il tipo nuovo è != da temperatura
            Temperatura* b = new Temperatura(name, min, max);
            AbstractSensor* b_abstract = dynamic_cast<AbstractSensor*>(b);
            if(b_abstract){
                delete c;
                a = b_abstract;
            }
        }
    }
    else if(type == "Rumore"){
        Rumore* c = dynamic_cast<Rumore*>(a);
        if(c){
            c->Rumore::setMin(min);
            c->Rumore::setStanza(stanza);
            c->Rumore::resetLastSim();
        }
        else{
            Rumore* b = new Rumore(name, stanza, min);
            AbstractSensor* b_abstract = dynamic_cast<AbstractSensor*>(b);
            if(b_abstract){
                delete c;
                a = b_abstract;
            }
        }
    }
    else if(type == "Umidità"){
        Umidita* c = dynamic_cast<Umidita*>(a);
        if(c){
            c->Umidita::setMin(min);
            c->Umidita::setHeight(height);
            c->Umidita::resetLastSim();
        }
        else{
            Umidita* b = new Umidita(name, min, height);
            AbstractSensor* b_abstract = dynamic_cast<AbstractSensor*>(b);
            if(b_abstract){
                delete c;
                a = b_abstract;
            }
        }
    }

    a->setName(((*new_data)[0]).toStdString());
}



std::vector<double>* Controller::getLastSimulation(const QString& name) const{
    AbstractSensor* a = this->findSensor(name);

    if(dynamic_cast<Temperatura*>(a)){
        Temperatura* b = nullptr;
        b = dynamic_cast<Temperatura*>(a);
        if(b) return b->getLastSim();
    }
    else if(dynamic_cast<Rumore*>(a)){
        Rumore* b = nullptr;
        b = dynamic_cast<Rumore*>(a);
        if(b) return b->getLastSim();
    }
    else if(dynamic_cast<Umidita*>(a)){
        Umidita* b = nullptr;
        b = dynamic_cast<Umidita*>(a);
        if(b) return b->getLastSim();
    }

    return nullptr;
}



void Controller::setLastSimulation(const QString& name, std::vector<double>* last_simulation){
    AbstractSensor* a = this->findSensor(name);

    if(dynamic_cast<Temperatura*>(a)){
        Temperatura* b = nullptr;
        b = dynamic_cast<Temperatura*>(a);
        if(b) b->setLastSim(last_simulation);
    }
    else if(dynamic_cast<Rumore*>(a)){
        Rumore* b = nullptr;
        b = dynamic_cast<Rumore*>(a);
        if(b) b->setLastSim(last_simulation);
    }
    else if(dynamic_cast<Umidita*>(a)){
        Umidita* b = nullptr;
        b = dynamic_cast<Umidita*>(a);
        if(b) b->setLastSim(last_simulation);
    }
}



void Controller::resetLastSimulation(const QString& name){
    AbstractSensor* a = findSensor(name);
    if(a){
        if(dynamic_cast<Temperatura*>(a)){
            auto b = dynamic_cast<Temperatura*>(a);
            b->resetLastSim();
        }
        if(dynamic_cast<Rumore*>(a)){
            auto b = dynamic_cast<Rumore*>(a);
            b->resetLastSim();
        }
        if(dynamic_cast<Umidita*>(a)){
            auto b = dynamic_cast<Umidita*>(a);
            b->resetLastSim();
        }
    }
}



void Controller::deleteSensor(const std::vector<QString>* data){
    AbstractSensor* a = this->findSensor((*data)[0]);

    std::vector<AbstractSensor*>::iterator it = sensors->begin();

    if(sensors->size() == 1) sensors->erase(it);
    else{
        for(auto it = sensors->begin(); it != sensors->end(); ++it){
            if(*it == a){
                delete a;
                sensors->erase(it);
                it--;
            }
        }
    }
}



std::vector<AbstractSensor*>* Controller::getVector() const {return sensors;}
