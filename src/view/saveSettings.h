#pragma once //without this line this problem appears: https://bugreports.qt.io/browse/QTCREATORBUG-20883
#ifndef SAVESETTINGS_H
#define SAVESETTINGS_H

#include <QDialog>
#include <QDebug>
#include <QFileDialog>
//#include <pointCloud.h>
class SaveConditions;
#include "src/view/saveLoad.h"
class CloudComponent;
namespace Ui {
class SaveSettings;
}

class SaveSettings : public QDialog
{
    Q_OBJECT

public:
    explicit SaveSettings(QWidget *parent = nullptr);
    QString getSavePath();
    QStringList getClassesIDs();
    float getMinNnResponseStrength();
    uint getMinNumOfPoints();
    void addCondition(std::function<bool(CloudComponent*)> condition);
    std::shared_ptr<SaveConditions> getSaveConditions();

    bool isAmongClasses(CloudComponent* cloud);
    bool hasNnResponseStrengthBiggerEqualThan(CloudComponent* cloud);
    bool hasNumOfPointsBiggerEqualThan(CloudComponent* cloud);
    ~SaveSettings();

private slots:
    void on_pushButton_2_clicked();

    void on_save_pushButton_clicked();

private:
    Ui::SaveSettings *ui;
    QString savePath="";
    QString classesSeparator=";";

    std::shared_ptr<SaveConditions> saveConditions;
};

#endif // SAVESETTINGS_H
