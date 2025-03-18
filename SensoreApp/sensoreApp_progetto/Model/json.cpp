#include "json.h"

Json::Json(const QString& name): name(name) {}

void Json::save(const std::vector<AbstractSensor*>* all_sensors){

    QJsonArray a;

    if(all_sensors){
        for(auto it = all_sensors->begin(); it != all_sensors->end(); ++it){
            QJsonObject o;
            if(dynamic_cast<Temperatura*>(*it)){
                Temperatura* s = dynamic_cast<Temperatura*>(*it);
                o["name"] = QString::fromStdString(s->getName());
                o["min"] = QString::number(s->getMin());
                o["max"] = QString::number(s->getMax());
                o["altezza"] = "";
                o["stanza"] = "";
                o["type"] = "Temperatura";
            }
            else if(dynamic_cast<Rumore*>(*it)){
                Rumore* r = dynamic_cast<Rumore*>(*it);
                o["name"] = QString::fromStdString(r->getName());
                o["min"] = QString::number(r->getMin());
                o["max"] = "";
                o["altezza"] = "";
                o["stanza"] = QString::fromStdString(r->getStanza());
                o["type"] = "Rumore";
            }
            else if(dynamic_cast<Umidita*>(*it)){
                Umidita* u = dynamic_cast<Umidita*>(*it);
                o["name"] = QString::fromStdString(u->getName());
                o["min"] = QString::number(u->getMin());
                o["max"] = "";
                o["altezza"] = QString::number(u->getHeight());
                o["stanza"] = "";
                o["type"] = "Umidità";
            }
            a.append(o);
        }
    }

    QJsonDocument doc(a);
    QFile file(this->name);
    if(!file.open(QIODevice::WriteOnly)) {
        std::cerr << "Cannot open file for writing: " << qPrintable(file.errorString()) << std::endl;
        return;
    }
    file.write(doc.toJson());
}

std::vector<std::vector<QString>*>* Json::open(const QString& filePath) const {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Impossibile aprire il file per la lettura:" << filePath;
        return nullptr;
    }

    QByteArray jsonData = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(jsonData));
    QJsonArray a = doc.array();

    std::vector<std::vector<QString>*>* all_data = new std::vector<std::vector<QString>*>();

    for(int i = 0; i<a.size(); i++){
        std::vector<QString>* data = new std::vector<QString>();
        QJsonObject o = a[i].toObject();
        QString type = o["type"].toString();
        QString name = o["name"].toString();

        data->push_back(name);
        data->push_back(o["min"].toString());
        data->push_back(o["max"].toString());
        data->push_back(o["altezza"].toString());
        data->push_back(o["stanza"].toString());
        data->push_back(type);

        all_data->push_back(data);
    }

    return all_data;
}
