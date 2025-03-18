#include "sensorlistview.h"

SensorListView::SensorListView(){
    list = new QListWidget();
    data_vector = new std::vector<std::vector<QString>*>();
}

void SensorListView::addQListWidgetItem(const std::vector<QString>* data){
    SensorEntry* se = new SensorEntry(data);
    QGroupBox* entry = se->getEntry();

    QVBoxLayout* item_container_layout = new QVBoxLayout();
    QWidget* item_container = new QWidget();

    item_container_layout->addWidget(entry);
    item_container->setLayout(item_container_layout);

    QListWidgetItem* item = new QListWidgetItem(this->list);
    item->setSizeHint(entry->sizeHint());
    this->list->setItemWidget(item, item_container);

    this->list->addItem(item);
    data_vector->push_back(const_cast<std::vector<QString>*>(data));


    //EDIT BUTTON
    connect(se, &SensorEntry::onEditButton, this, [this, se, item](const std::vector<QString>* data){
        this->list->setCurrentItem(item);

        emit list->QListWidget::itemClicked(this->list->currentItem());                         //seleziona sempre il primo elemento della lista
        int index = -1;

        for(long unsigned int i = 0; i < data_vector->size(); i++){
            if((*data_vector)[i] == data) index = i;
        }

        InputDialog* i = new InputDialog(data_vector, true);
        i->updateDialog(data);

        if(i->exec() == QDialog::Accepted){
            std::vector<QString>* new_data = i->getVector();

            (*data_vector)[index] = new_data;

            emit updateSensorSignal(data, new_data);
            emit list->QListWidget::itemClicked(item);
            se->setProperties(new_data);
        }
    });


    //DELETE BUTTON
    connect(se, &SensorEntry::onDeleteButton, this, [this, se, item](const std::vector<QString>* data){
        this->list->setCurrentItem(item);

        emit this->list->QListWidget::itemClicked(this->list->currentItem());

        QMessageBox* confirm = this->confirmBox();
        if(confirm->exec() == QMessageBox::Yes){

            this->list->removeItemWidget(item);
            delete item;
            delete se;

            std::vector<std::vector<QString>*>::iterator it = data_vector->begin();

            if(data_vector->size() == 1){
                (data_vector)->erase(it);
            }
            else{
                for(; it != data_vector->end(); ++it){
                    if(*it == data){
                        data_vector->erase(it);
                        it--;
                    }
                }
            }

            int new_index = this->list->currentRow();
            QListWidgetItem* new_item = this->list->item(new_index);
            emit this->list->QListWidget::itemClicked(new_item);
            emit deleteSensorSignal(data);
        }
    });
}

QMessageBox* SensorListView::confirmBox() const{
    QMessageBox* m = new QMessageBox();
    m->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    m->setInformativeText("Vuoi veramente eliminare il sensore?");
    m->setIcon(QMessageBox::Warning);
    return m;
}

void SensorListView::showDialog(){
    InputDialog* dialog = new InputDialog(data_vector, false);
    if(dialog->exec() == QDialog::Accepted){
        std::vector<QString>* data = dialog->InputDialog::getVector();
        this->addSensor(data);
    }
}

void SensorListView::showError(const QString& sensorName) const{
    QMessageBox* m = new QMessageBox();
    m->setStandardButtons(QMessageBox::Yes);
    m->setInformativeText("Il sensore '" + sensorName + "' è già presente, modificane uno esistente oppure creane uno nuovo");
    m->setIcon(QMessageBox::Critical);
    m->exec();
}

void SensorListView::addSensor(const std::vector<QString>* data){
    emit addSensorSignal(data);
    this->addQListWidgetItem(data);
}

void SensorListView::openSensors(const std::vector<std::vector<QString>*>* all_data){
    for(auto it = all_data->begin(); it != all_data->end(); ++it) {
        std::vector<QString>* data = *it;

        bool found = false;

        for(auto iter = data_vector->begin(); iter != data_vector->end(); ++iter){
            if((*(*iter))[0] == (*data)[0]){
                found = true;
                this->showError((*data)[0]);
            }
        }

        if(!found) this->addSensor(data);
    }
}

QListWidget* SensorListView::getList() const {return list;}



std::vector<std::vector<QString>*>* SensorListView::getVector_data() const {return data_vector;}
