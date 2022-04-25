#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QMainWindow>
#include <QWidget>
#include <QSpinBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <memory>
#include <QFile>
#include <QDataStream>
#include <QTextStream>

#include <QDebug>
class QSpinBoxConfigurationAdapter;
class QWidgetConfigurationAdapter;

enum QWidgetType{SpinBox,DoubleSpinBox,LineEdit,CheckBox,ComboBox,GroupBox};

class Configuration
{
    QMainWindow *mainWindow;
    QList<QWidget*> widgets;
public:
    Configuration(QMainWindow* mW);
    void addWidget(QWidget* widget);
    void addAllWidgetsOfGivenTypes(QList<QWidgetType> widgetTypes);
    bool saveConfiguration(QString path);
    int findWidgetWithName(QString widgetName);
    void clear();
    bool loadConfiguration(QString path);
    std::unique_ptr<QWidgetConfigurationAdapter> wrap(QWidget *qWidget);
    //std::unique_ptr<QSpinBoxConfigurationAdapter> wrap(QSpinBox *qSpinBox);
};
class QWidgetConfigurationAdapter:public QWidget{
    Q_OBJECT
    public:
    QWidgetConfigurationAdapter();
    virtual QString getConfigurationData();
    virtual void setConfigurationData(QString value);
    virtual void clearData(){}
};
//QSpinbox inherits QWidget
class QSpinBoxConfigurationAdapter:public QWidgetConfigurationAdapter{
    Q_OBJECT
    QSpinBox *qSpinBox;
public:
    QSpinBoxConfigurationAdapter(QSpinBox* qSpBo);
    QString getConfigurationData();
    void setConfigurationData(QString value);
    void clearData(){
        this->qSpinBox->setValue(qSpinBox->minimum());
    }
};
class QDoubleSpinBoxConfigurationAdapter:public QWidgetConfigurationAdapter{
    Q_OBJECT
    QDoubleSpinBox *qDoubleSpinBox;
public:
    QDoubleSpinBoxConfigurationAdapter(QDoubleSpinBox* qDoSpBo);
    QString getConfigurationData();
    void setConfigurationData(QString value);
    void clearData(){
        this->qDoubleSpinBox->setValue(qDoubleSpinBox->minimum());
    }
};
class QLineEditConfigurationAdapter:public QWidgetConfigurationAdapter{
    Q_OBJECT
    QLineEdit *qLineEdit;
public:
    QLineEditConfigurationAdapter(QLineEdit* qLiEd);
    QString getConfigurationData();
    void setConfigurationData(QString value);
    void clearData(){
        this->qLineEdit->clear();
    }
};
class QCheckBoxConfigurationAdapter:public QWidgetConfigurationAdapter{
    Q_OBJECT
    QCheckBox *qCheckBox;
public:
    QCheckBoxConfigurationAdapter(QCheckBox* qChBo);
    QString getConfigurationData();
    void setConfigurationData(QString value);
    void clearData(){
        this->qCheckBox->setCheckState(Qt::CheckState::Unchecked);
    }
};
class QComboBoxConfigurationAdapter:public QWidgetConfigurationAdapter{
    Q_OBJECT
    QComboBox *qComboBox;
public:
    QComboBoxConfigurationAdapter(QComboBox* qCoBo);
    QString getConfigurationData();
    void setConfigurationData(QString value);
    void clearData(){
        this->qComboBox->setCurrentIndex(0);
    }
};
class QGroupBoxConfigurationAdapter:public QWidgetConfigurationAdapter{
    Q_OBJECT
    QGroupBox *qGroupBox;
public:
    QGroupBoxConfigurationAdapter(QGroupBox* qGrBo);
    QString getConfigurationData();
    void setConfigurationData(QString value);
    void clearData(){
        this->qGroupBox->setChecked(false);
    }
};

#endif // CONFIGURATION_H
