#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <iostream>
#include <vector>
#include <QString>
#include <QMessageBox>

class InputDialog: public QDialog{
private:
    const std::vector<std::vector<QString>*>* all_sensors;
    bool onUpdatePurpose;

    std::vector<QString>* data;

    QLineEdit* nameLineEdit;
    QComboBox* tentMenu;
    QLabel* typeLabel;
    QComboBox* tentRooms;
    QLineEdit* min_edit;
    QLineEdit* max_edit;
    QLineEdit* height_edit;

public:
    InputDialog(const std::vector<std::vector<QString>*>* all_sensors = nullptr, const bool& onUpdatePurpose = false);

    void showError(const QString& s);
    bool checkName(const QString& n);
    void updateDialog(const std::vector<QString>* data);

    std::vector<QString>* getVector() const;
};

#endif // INPUTDIALOG_H
