#include "sensorentry.h"

SensorEntry::SensorEntry(const std::vector<QString>* data):data(data){
    name = (*data)[0];
    QString min_value = (*data)[1];
    QString max_value = (*data)[2];
    QString height = (*data)[3];
    QString stanza = (*data)[4];
    QString type = (*data)[5];

    entry = new QGroupBox(name);
    edit_button = new QPushButton("Edit");
    del_button = new QPushButton("Del");

    //BOTTONI
    QVBoxLayout* button_layout = new QVBoxLayout();

    edit_button->setMaximumWidth(50);
    del_button->setMaximumWidth(50);

    button_layout->addWidget(edit_button);
    button_layout->addWidget(del_button);
    button_layout->setAlignment(Qt::AlignRight);
    QVBoxLayout* left = new QVBoxLayout();

    if(type == "Temperatura"){
        min_label = new QLabel(min_value);
        max_label = new QLabel(max_value);
        QLabel* min_textlabel = new QLabel("Min: ");
        QLabel* max_textlabel = new QLabel("Max: ");

        QHBoxLayout* minLayout = new QHBoxLayout();
        QHBoxLayout* maxLayout = new QHBoxLayout();

        minLayout->addWidget(min_textlabel);
        minLayout->addWidget(min_label);
        maxLayout->addWidget(max_textlabel);
        maxLayout->addWidget(max_label);

        left->addLayout(minLayout);
        left->addLayout(maxLayout);
    }
    else if(type == "Rumore"){
        min_label = new QLabel(min_value);
        stanza_label = new QLabel(stanza);
        QLabel* min_textlabel = new QLabel("Min: ");
        QLabel* stanza_textLabel = new QLabel("Stanza: ");
        QHBoxLayout* minLayout = new QHBoxLayout();
        QHBoxLayout* stanzaLayout = new QHBoxLayout();

        minLayout->addWidget(min_textlabel);
        minLayout->addWidget(min_label);
        stanzaLayout->addWidget(stanza_textLabel);
        stanzaLayout->addWidget(stanza_label);

        left->addLayout(minLayout);
        left->addLayout(stanzaLayout);
    }
    else if(type == "Umidità"){
        min_label = new QLabel(min_value);
        height_label = new QLabel(height);
        QLabel* min_textlabel = new QLabel("Min: ");
        QLabel* height_textlabel = new QLabel("Altezza: ");

        QHBoxLayout* minLayout = new QHBoxLayout();
        QHBoxLayout* heightLayout = new QHBoxLayout();

        minLayout->addWidget(min_textlabel);
        minLayout->addWidget(min_label);
        heightLayout->addWidget(height_textlabel);
        heightLayout->addWidget(height_label);

        left->addLayout(minLayout);
        left->addLayout(heightLayout);
    }

    QHBoxLayout* mainEntryLayout = new QHBoxLayout();
    mainEntryLayout->addLayout(left);
    mainEntryLayout->addLayout(button_layout);

    entry->setLayout(mainEntryLayout);
    entry->setMinimumHeight(75);

    connect(edit_button, &QPushButton::clicked, this, [this]{
        emit onEditButton(this->data);
    });

    connect(del_button, &QPushButton::clicked, this, [this]{
        emit onDeleteButton(this->data);
    });
}



void SensorEntry::setProperties(const std::vector<QString>* set_data){

    this->name = (*set_data)[0];
    this->data = set_data;
    this->entry->setTitle(name);

    if( (*data)[5] == "Temperatura"){
        this->min_label->setText( (*set_data)[1] );
        this->max_label->setText( (*set_data)[2] );
    }
    else if( (*data)[5] == "Rumore"){
        this->min_label->setText( (*set_data)[1] );
        this->stanza_label->setText( (*set_data)[4] );
    }
    else if((*set_data)[5] == "Umidità"){
        this->min_label->setText( (*set_data)[1] );
        this->height_label->setText( (*set_data)[3] );
    }
}


QGroupBox* SensorEntry::getEntry() const {return entry;}

