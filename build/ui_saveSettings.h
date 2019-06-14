/********************************************************************************
** Form generated from reading UI file 'saveSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVESETTINGS_H
#define UI_SAVESETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SaveSettings
{
public:
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *clsIDs_lineEdit;
    QLabel *label_2;
    QDoubleSpinBox *nnRespon_doubleSpinBox;
    QLabel *label_3;
    QSpinBox *cloudSize_spinBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *save_pushButton;

    void setupUi(QDialog *SaveSettings)
    {
        if (SaveSettings->objectName().isEmpty())
            SaveSettings->setObjectName(QString::fromUtf8("SaveSettings"));
        SaveSettings->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(SaveSettings);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(-1, 9, -1, -1);
        label = new QLabel(SaveSettings);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        clsIDs_lineEdit = new QLineEdit(SaveSettings);
        clsIDs_lineEdit->setObjectName(QString::fromUtf8("clsIDs_lineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, clsIDs_lineEdit);

        label_2 = new QLabel(SaveSettings);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setWordWrap(true);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        nnRespon_doubleSpinBox = new QDoubleSpinBox(SaveSettings);
        nnRespon_doubleSpinBox->setObjectName(QString::fromUtf8("nnRespon_doubleSpinBox"));

        formLayout->setWidget(1, QFormLayout::FieldRole, nnRespon_doubleSpinBox);

        label_3 = new QLabel(SaveSettings);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setWordWrap(true);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        cloudSize_spinBox = new QSpinBox(SaveSettings);
        cloudSize_spinBox->setObjectName(QString::fromUtf8("cloudSize_spinBox"));

        formLayout->setWidget(2, QFormLayout::FieldRole, cloudSize_spinBox);


        verticalLayout_2->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_2 = new QPushButton(SaveSettings);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        save_pushButton = new QPushButton(SaveSettings);
        save_pushButton->setObjectName(QString::fromUtf8("save_pushButton"));

        horizontalLayout->addWidget(save_pushButton);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(SaveSettings);

        QMetaObject::connectSlotsByName(SaveSettings);
    } // setupUi

    void retranslateUi(QDialog *SaveSettings)
    {
        SaveSettings->setWindowTitle(QApplication::translate("SaveSettings", "Dialog", nullptr));
        label->setText(QApplication::translate("SaveSettings", "classes ids to save (seperate by \";\") (leave empty for all)", nullptr));
        label_2->setText(QApplication::translate("SaveSettings", "minimum nn response strength for object", nullptr));
        label_3->setText(QApplication::translate("SaveSettings", "minimum cloud size [points]", nullptr));
        pushButton_2->setText(QApplication::translate("SaveSettings", "cancel", nullptr));
        save_pushButton->setText(QApplication::translate("SaveSettings", "save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SaveSettings: public Ui_SaveSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVESETTINGS_H
