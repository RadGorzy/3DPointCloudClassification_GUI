/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClassification;
    QAction *actionTraining_data_preparation;
    QAction *actionsave_configuration;
    QAction *actionload_configuration;
    QAction *actionsave_selected_clouds;
    QAction *actionload_clouds;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_7;
    QSplitter *vertical_splitter;
    QStackedWidget *stackedWidget;
    QWidget *classify;
    QVBoxLayout *verticalLayout_14;
    QSplitter *splitter_3;
    QSplitter *splitter;
    QWidget *settings_widget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *left_verticalLayout;
    QToolBox *toolBox;
    QWidget *segmentationType;
    QVBoxLayout *verticalLayout_5;
    QComboBox *segmentation_comboBox;
    QStackedWidget *segmentation_stackedWidget;
    QWidget *DON_oneStep;
    QVBoxLayout *verticalLayout_6;
    QFormLayout *formLayout;
    QDoubleSpinBox *scale1_doubleSpinBox;
    QLabel *label;
    QLabel *label_2;
    QDoubleSpinBox *scale2_doubleSpinBox_2;
    QLabel *label_3;
    QDoubleSpinBox *threshold_doubleSpinBox_3;
    QLabel *label_4;
    QDoubleSpinBox *segradius_doubleSpinBox_4;
    QLabel *label_5;
    QCheckBox *approx_checkBox;
    QLabel *label_6;
    QSpinBox *decimation_spinBox;
    QWidget *DON_twoStep;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout_2;
    QDoubleSpinBox *scale1_twoStep_doubleSpinBox_5;
    QLabel *label_7;
    QLabel *label_8;
    QDoubleSpinBox *scale2_twoStep_doubleSpinBox_6;
    QLabel *label_9;
    QDoubleSpinBox *threshold_twoStep_doubleSpinBox_7;
    QLabel *label_10;
    QDoubleSpinBox *segradius_twoStep_doubleSpinBox_8;
    QLabel *label_11;
    QCheckBox *approx_twoStep_checkBox_2;
    QLabel *label_12;
    QSpinBox *decimation_twoStep_spinBox_2;
    QLabel *label_13;
    QDoubleSpinBox *scale1_1_twoStep_doubleSpinBox_9;
    QLabel *label_14;
    QDoubleSpinBox *scale2_1_twoStep_doubleSpinBox_10;
    QWidget *projectionType;
    QVBoxLayout *verticalLayout_8;
    QPushButton *projectionSaveFolder_pushButton;
    QLineEdit *projectionSaveFolder_lineEdit;
    QComboBox *projection_comboBox;
    QStackedWidget *projection_stackedWidget;
    QWidget *binary;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *editProjection_groupBox;
    QFormLayout *formLayout_4;
    QLabel *label_21;
    QComboBox *editProjKernelShape_comboBox;
    QSpinBox *editProjKernelWidth_spinBox_9;
    QLabel *label_22;
    QLabel *label_23;
    QSpinBox *editProjKernelHeight_spinBox_10;
    QFormLayout *formLayout_3;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_18;
    QSpinBox *n_proj_spinBox_6;
    QLabel *label_17;
    QLabel *label_20;
    QLabel *label_19;
    QSpinBox *n_h_proj_spinBox_8;
    QDoubleSpinBox *min_deg_doubleSpinBox_3;
    QDoubleSpinBox *max_deg_doubleSpinBox_4;
    QDoubleSpinBox *min_h_doubleSpinBox_5;
    QDoubleSpinBox *max_h_doubleSpinBox_7;
    QWidget *range;
    QVBoxLayout *verticalLayout_11;
    QFormLayout *formLayout_5;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QSpinBox *n_proj_rangeImg_spinBox_13;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QSpinBox *n_h_proj_rangeImg_spinBox_16;
    QDoubleSpinBox *min_deg_rangeImg_doubleSpinBox_11;
    QDoubleSpinBox *max_deg_rangeImgdoubleSpinBox_12;
    QDoubleSpinBox *min_h_rangeImgdoubleSpinBox_14;
    QDoubleSpinBox *max_h_rangeImg_doubleSpinBox_15;
    QWidget *classification;
    QVBoxLayout *verticalLayout_12;
    QPushButton *classificationModel_pushButton;
    QLineEdit *classificationModel_lineEdit;
    QFormLayout *formLayout_6;
    QLabel *label_30;
    QSpinBox *numberOfClasses_spinBox_17;
    QWidget *benchmarkType;
    QVBoxLayout *verticalLayout_13;
    QPushButton *benchmarkSaveFolder_pushButton;
    QLineEdit *benchmarkSaveFolder_lineEdit;
    QPushButton *selectClassMapping_pushButton;
    QLineEdit *selectClassMapping_lineEdit;
    QComboBox *benchmark_comboBox;
    QCheckBox *orientedBB_checkBox;
    QCheckBox *dontClassify_checkBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *view_pushButton;
    QPushButton *viewAll_pushButton;
    QPushButton *segment_pushButton;
    QPushButton *project_pushButton;
    QPushButton *classify_pushButton;
    QPushButton *benchmark_pushButton;
    QWidget *view_widget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *central_verticalLayout;
    QVTKWidget *qvtkView_widget;
    QWidget *structureView_widget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *right_verticalLayout_2;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *load_button;
    QPushButton *loadObjects_button;
    QPushButton *remove_pushButton;
    QWidget *prepareDataset;
    QHBoxLayout *horizontalLayout_4;
    QSplitter *splitter_2;
    QWidget *left_widget_1;
    QVBoxLayout *verticalLayout_16;
    QVBoxLayout *verticalLayout_15;
    QToolBox *toolBox_2;
    QWidget *imageFrom3D;
    QVBoxLayout *verticalLayout_19;
    QComboBox *preparedImageType_comboBox;
    QFormLayout *formLayout_7;
    QLabel *label_31;
    QSpinBox *spinBox_18;
    QLabel *label_33;
    QLabel *label_32;
    QLabel *label_34;
    QLabel *label_35;
    QLabel *label_36;
    QDoubleSpinBox *doubleSpinBox_11;
    QDoubleSpinBox *doubleSpinBox_12;
    QDoubleSpinBox *doubleSpinBox_13;
    QDoubleSpinBox *doubleSpinBox_14;
    QSpinBox *spinBox_19;
    QPushButton *prepareFrom3D_pushButton;
    QWidget *page_2;
    QWidget *right_widget_1;
    QVBoxLayout *verticalLayout_18;
    QVBoxLayout *verticalLayout_17;
    QTreeWidget *prepare_treeWidget;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *addPrepareTreeItem_pushButton;
    QPushButton *removePrepareTreeItem_pushButton;
    QTextEdit *log_textEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1015, 584);
        actionClassification = new QAction(MainWindow);
        actionClassification->setObjectName(QString::fromUtf8("actionClassification"));
        actionTraining_data_preparation = new QAction(MainWindow);
        actionTraining_data_preparation->setObjectName(QString::fromUtf8("actionTraining_data_preparation"));
        actionsave_configuration = new QAction(MainWindow);
        actionsave_configuration->setObjectName(QString::fromUtf8("actionsave_configuration"));
        actionload_configuration = new QAction(MainWindow);
        actionload_configuration->setObjectName(QString::fromUtf8("actionload_configuration"));
        actionsave_selected_clouds = new QAction(MainWindow);
        actionsave_selected_clouds->setObjectName(QString::fromUtf8("actionsave_selected_clouds"));
        actionload_clouds = new QAction(MainWindow);
        actionload_clouds->setObjectName(QString::fromUtf8("actionload_clouds"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_7 = new QVBoxLayout(centralWidget);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        vertical_splitter = new QSplitter(centralWidget);
        vertical_splitter->setObjectName(QString::fromUtf8("vertical_splitter"));
        vertical_splitter->setOrientation(Qt::Vertical);
        stackedWidget = new QStackedWidget(vertical_splitter);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(10);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        classify = new QWidget();
        classify->setObjectName(QString::fromUtf8("classify"));
        verticalLayout_14 = new QVBoxLayout(classify);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        splitter_3 = new QSplitter(classify);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_3);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
        splitter->setOrientation(Qt::Horizontal);
        settings_widget = new QWidget(splitter);
        settings_widget->setObjectName(QString::fromUtf8("settings_widget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(settings_widget->sizePolicy().hasHeightForWidth());
        settings_widget->setSizePolicy(sizePolicy2);
        settings_widget->setMinimumSize(QSize(100, 0));
        verticalLayout_3 = new QVBoxLayout(settings_widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        left_verticalLayout = new QVBoxLayout();
        left_verticalLayout->setSpacing(6);
        left_verticalLayout->setObjectName(QString::fromUtf8("left_verticalLayout"));
        toolBox = new QToolBox(settings_widget);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        segmentationType = new QWidget();
        segmentationType->setObjectName(QString::fromUtf8("segmentationType"));
        segmentationType->setGeometry(QRect(0, 0, 488, 310));
        verticalLayout_5 = new QVBoxLayout(segmentationType);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        segmentation_comboBox = new QComboBox(segmentationType);
        segmentation_comboBox->addItem(QString());
        segmentation_comboBox->addItem(QString());
        segmentation_comboBox->setObjectName(QString::fromUtf8("segmentation_comboBox"));

        verticalLayout_5->addWidget(segmentation_comboBox);

        segmentation_stackedWidget = new QStackedWidget(segmentationType);
        segmentation_stackedWidget->setObjectName(QString::fromUtf8("segmentation_stackedWidget"));
        DON_oneStep = new QWidget();
        DON_oneStep->setObjectName(QString::fromUtf8("DON_oneStep"));
        verticalLayout_6 = new QVBoxLayout(DON_oneStep);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        scale1_doubleSpinBox = new QDoubleSpinBox(DON_oneStep);
        scale1_doubleSpinBox->setObjectName(QString::fromUtf8("scale1_doubleSpinBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, scale1_doubleSpinBox);

        label = new QLabel(DON_oneStep);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(DON_oneStep);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        scale2_doubleSpinBox_2 = new QDoubleSpinBox(DON_oneStep);
        scale2_doubleSpinBox_2->setObjectName(QString::fromUtf8("scale2_doubleSpinBox_2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, scale2_doubleSpinBox_2);

        label_3 = new QLabel(DON_oneStep);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        threshold_doubleSpinBox_3 = new QDoubleSpinBox(DON_oneStep);
        threshold_doubleSpinBox_3->setObjectName(QString::fromUtf8("threshold_doubleSpinBox_3"));

        formLayout->setWidget(2, QFormLayout::FieldRole, threshold_doubleSpinBox_3);

        label_4 = new QLabel(DON_oneStep);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        segradius_doubleSpinBox_4 = new QDoubleSpinBox(DON_oneStep);
        segradius_doubleSpinBox_4->setObjectName(QString::fromUtf8("segradius_doubleSpinBox_4"));

        formLayout->setWidget(3, QFormLayout::FieldRole, segradius_doubleSpinBox_4);

        label_5 = new QLabel(DON_oneStep);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        approx_checkBox = new QCheckBox(DON_oneStep);
        approx_checkBox->setObjectName(QString::fromUtf8("approx_checkBox"));

        formLayout->setWidget(4, QFormLayout::FieldRole, approx_checkBox);

        label_6 = new QLabel(DON_oneStep);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        decimation_spinBox = new QSpinBox(DON_oneStep);
        decimation_spinBox->setObjectName(QString::fromUtf8("decimation_spinBox"));

        formLayout->setWidget(5, QFormLayout::FieldRole, decimation_spinBox);


        verticalLayout_6->addLayout(formLayout);

        segmentation_stackedWidget->addWidget(DON_oneStep);
        DON_twoStep = new QWidget();
        DON_twoStep->setObjectName(QString::fromUtf8("DON_twoStep"));
        verticalLayout_2 = new QVBoxLayout(DON_twoStep);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        scale1_twoStep_doubleSpinBox_5 = new QDoubleSpinBox(DON_twoStep);
        scale1_twoStep_doubleSpinBox_5->setObjectName(QString::fromUtf8("scale1_twoStep_doubleSpinBox_5"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, scale1_twoStep_doubleSpinBox_5);

        label_7 = new QLabel(DON_twoStep);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_7);

        label_8 = new QLabel(DON_twoStep);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_8);

        scale2_twoStep_doubleSpinBox_6 = new QDoubleSpinBox(DON_twoStep);
        scale2_twoStep_doubleSpinBox_6->setObjectName(QString::fromUtf8("scale2_twoStep_doubleSpinBox_6"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, scale2_twoStep_doubleSpinBox_6);

        label_9 = new QLabel(DON_twoStep);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_9);

        threshold_twoStep_doubleSpinBox_7 = new QDoubleSpinBox(DON_twoStep);
        threshold_twoStep_doubleSpinBox_7->setObjectName(QString::fromUtf8("threshold_twoStep_doubleSpinBox_7"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, threshold_twoStep_doubleSpinBox_7);

        label_10 = new QLabel(DON_twoStep);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_10);

        segradius_twoStep_doubleSpinBox_8 = new QDoubleSpinBox(DON_twoStep);
        segradius_twoStep_doubleSpinBox_8->setObjectName(QString::fromUtf8("segradius_twoStep_doubleSpinBox_8"));

        formLayout_2->setWidget(5, QFormLayout::FieldRole, segradius_twoStep_doubleSpinBox_8);

        label_11 = new QLabel(DON_twoStep);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, label_11);

        approx_twoStep_checkBox_2 = new QCheckBox(DON_twoStep);
        approx_twoStep_checkBox_2->setObjectName(QString::fromUtf8("approx_twoStep_checkBox_2"));

        formLayout_2->setWidget(6, QFormLayout::FieldRole, approx_twoStep_checkBox_2);

        label_12 = new QLabel(DON_twoStep);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        formLayout_2->setWidget(7, QFormLayout::LabelRole, label_12);

        decimation_twoStep_spinBox_2 = new QSpinBox(DON_twoStep);
        decimation_twoStep_spinBox_2->setObjectName(QString::fromUtf8("decimation_twoStep_spinBox_2"));

        formLayout_2->setWidget(7, QFormLayout::FieldRole, decimation_twoStep_spinBox_2);

        label_13 = new QLabel(DON_twoStep);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_13);

        scale1_1_twoStep_doubleSpinBox_9 = new QDoubleSpinBox(DON_twoStep);
        scale1_1_twoStep_doubleSpinBox_9->setObjectName(QString::fromUtf8("scale1_1_twoStep_doubleSpinBox_9"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, scale1_1_twoStep_doubleSpinBox_9);

        label_14 = new QLabel(DON_twoStep);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_14);

        scale2_1_twoStep_doubleSpinBox_10 = new QDoubleSpinBox(DON_twoStep);
        scale2_1_twoStep_doubleSpinBox_10->setObjectName(QString::fromUtf8("scale2_1_twoStep_doubleSpinBox_10"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, scale2_1_twoStep_doubleSpinBox_10);


        verticalLayout_2->addLayout(formLayout_2);

        segmentation_stackedWidget->addWidget(DON_twoStep);

        verticalLayout_5->addWidget(segmentation_stackedWidget);

        toolBox->addItem(segmentationType, QString::fromUtf8("Segmentation"));
        projectionType = new QWidget();
        projectionType->setObjectName(QString::fromUtf8("projectionType"));
        projectionType->setGeometry(QRect(0, 0, 488, 478));
        verticalLayout_8 = new QVBoxLayout(projectionType);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        projectionSaveFolder_pushButton = new QPushButton(projectionType);
        projectionSaveFolder_pushButton->setObjectName(QString::fromUtf8("projectionSaveFolder_pushButton"));

        verticalLayout_8->addWidget(projectionSaveFolder_pushButton);

        projectionSaveFolder_lineEdit = new QLineEdit(projectionType);
        projectionSaveFolder_lineEdit->setObjectName(QString::fromUtf8("projectionSaveFolder_lineEdit"));

        verticalLayout_8->addWidget(projectionSaveFolder_lineEdit);

        projection_comboBox = new QComboBox(projectionType);
        projection_comboBox->addItem(QString());
        projection_comboBox->addItem(QString());
        projection_comboBox->setObjectName(QString::fromUtf8("projection_comboBox"));

        verticalLayout_8->addWidget(projection_comboBox);

        projection_stackedWidget = new QStackedWidget(projectionType);
        projection_stackedWidget->setObjectName(QString::fromUtf8("projection_stackedWidget"));
        projection_stackedWidget->setAcceptDrops(false);
        binary = new QWidget();
        binary->setObjectName(QString::fromUtf8("binary"));
        verticalLayout_10 = new QVBoxLayout(binary);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(-1, 9, -1, -1);
        editProjection_groupBox = new QGroupBox(binary);
        editProjection_groupBox->setObjectName(QString::fromUtf8("editProjection_groupBox"));
        editProjection_groupBox->setCheckable(true);
        editProjection_groupBox->setChecked(false);
        formLayout_4 = new QFormLayout(editProjection_groupBox);
        formLayout_4->setSpacing(6);
        formLayout_4->setContentsMargins(11, 11, 11, 11);
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        label_21 = new QLabel(editProjection_groupBox);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_21);

        editProjKernelShape_comboBox = new QComboBox(editProjection_groupBox);
        editProjKernelShape_comboBox->addItem(QString());
        editProjKernelShape_comboBox->addItem(QString());
        editProjKernelShape_comboBox->addItem(QString());
        editProjKernelShape_comboBox->setObjectName(QString::fromUtf8("editProjKernelShape_comboBox"));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, editProjKernelShape_comboBox);

        editProjKernelWidth_spinBox_9 = new QSpinBox(editProjection_groupBox);
        editProjKernelWidth_spinBox_9->setObjectName(QString::fromUtf8("editProjKernelWidth_spinBox_9"));

        formLayout_4->setWidget(3, QFormLayout::FieldRole, editProjKernelWidth_spinBox_9);

        label_22 = new QLabel(editProjection_groupBox);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        formLayout_4->setWidget(3, QFormLayout::LabelRole, label_22);

        label_23 = new QLabel(editProjection_groupBox);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        formLayout_4->setWidget(4, QFormLayout::LabelRole, label_23);

        editProjKernelHeight_spinBox_10 = new QSpinBox(editProjection_groupBox);
        editProjKernelHeight_spinBox_10->setObjectName(QString::fromUtf8("editProjKernelHeight_spinBox_10"));

        formLayout_4->setWidget(4, QFormLayout::FieldRole, editProjKernelHeight_spinBox_10);


        verticalLayout_9->addWidget(editProjection_groupBox);

        formLayout_3 = new QFormLayout();
        formLayout_3->setSpacing(6);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        label_15 = new QLabel(binary);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_15);

        label_16 = new QLabel(binary);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_16);

        label_18 = new QLabel(binary);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_18);

        n_proj_spinBox_6 = new QSpinBox(binary);
        n_proj_spinBox_6->setObjectName(QString::fromUtf8("n_proj_spinBox_6"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, n_proj_spinBox_6);

        label_17 = new QLabel(binary);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_17);

        label_20 = new QLabel(binary);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        formLayout_3->setWidget(4, QFormLayout::LabelRole, label_20);

        label_19 = new QLabel(binary);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        formLayout_3->setWidget(5, QFormLayout::LabelRole, label_19);

        n_h_proj_spinBox_8 = new QSpinBox(binary);
        n_h_proj_spinBox_8->setObjectName(QString::fromUtf8("n_h_proj_spinBox_8"));

        formLayout_3->setWidget(5, QFormLayout::FieldRole, n_h_proj_spinBox_8);

        min_deg_doubleSpinBox_3 = new QDoubleSpinBox(binary);
        min_deg_doubleSpinBox_3->setObjectName(QString::fromUtf8("min_deg_doubleSpinBox_3"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, min_deg_doubleSpinBox_3);

        max_deg_doubleSpinBox_4 = new QDoubleSpinBox(binary);
        max_deg_doubleSpinBox_4->setObjectName(QString::fromUtf8("max_deg_doubleSpinBox_4"));
        max_deg_doubleSpinBox_4->setMaximum(360.000000000000000);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, max_deg_doubleSpinBox_4);

        min_h_doubleSpinBox_5 = new QDoubleSpinBox(binary);
        min_h_doubleSpinBox_5->setObjectName(QString::fromUtf8("min_h_doubleSpinBox_5"));

        formLayout_3->setWidget(3, QFormLayout::FieldRole, min_h_doubleSpinBox_5);

        max_h_doubleSpinBox_7 = new QDoubleSpinBox(binary);
        max_h_doubleSpinBox_7->setObjectName(QString::fromUtf8("max_h_doubleSpinBox_7"));
        max_h_doubleSpinBox_7->setMaximum(90.000000000000000);

        formLayout_3->setWidget(4, QFormLayout::FieldRole, max_h_doubleSpinBox_7);


        verticalLayout_9->addLayout(formLayout_3);


        verticalLayout_10->addLayout(verticalLayout_9);

        projection_stackedWidget->addWidget(binary);
        range = new QWidget();
        range->setObjectName(QString::fromUtf8("range"));
        verticalLayout_11 = new QVBoxLayout(range);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        formLayout_5 = new QFormLayout();
        formLayout_5->setSpacing(6);
        formLayout_5->setObjectName(QString::fromUtf8("formLayout_5"));
        label_24 = new QLabel(range);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        formLayout_5->setWidget(0, QFormLayout::LabelRole, label_24);

        label_25 = new QLabel(range);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        formLayout_5->setWidget(1, QFormLayout::LabelRole, label_25);

        label_26 = new QLabel(range);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        formLayout_5->setWidget(2, QFormLayout::LabelRole, label_26);

        n_proj_rangeImg_spinBox_13 = new QSpinBox(range);
        n_proj_rangeImg_spinBox_13->setObjectName(QString::fromUtf8("n_proj_rangeImg_spinBox_13"));

        formLayout_5->setWidget(2, QFormLayout::FieldRole, n_proj_rangeImg_spinBox_13);

        label_27 = new QLabel(range);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        formLayout_5->setWidget(3, QFormLayout::LabelRole, label_27);

        label_28 = new QLabel(range);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        formLayout_5->setWidget(4, QFormLayout::LabelRole, label_28);

        label_29 = new QLabel(range);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        formLayout_5->setWidget(5, QFormLayout::LabelRole, label_29);

        n_h_proj_rangeImg_spinBox_16 = new QSpinBox(range);
        n_h_proj_rangeImg_spinBox_16->setObjectName(QString::fromUtf8("n_h_proj_rangeImg_spinBox_16"));

        formLayout_5->setWidget(5, QFormLayout::FieldRole, n_h_proj_rangeImg_spinBox_16);

        min_deg_rangeImg_doubleSpinBox_11 = new QDoubleSpinBox(range);
        min_deg_rangeImg_doubleSpinBox_11->setObjectName(QString::fromUtf8("min_deg_rangeImg_doubleSpinBox_11"));

        formLayout_5->setWidget(0, QFormLayout::FieldRole, min_deg_rangeImg_doubleSpinBox_11);

        max_deg_rangeImgdoubleSpinBox_12 = new QDoubleSpinBox(range);
        max_deg_rangeImgdoubleSpinBox_12->setObjectName(QString::fromUtf8("max_deg_rangeImgdoubleSpinBox_12"));

        formLayout_5->setWidget(1, QFormLayout::FieldRole, max_deg_rangeImgdoubleSpinBox_12);

        min_h_rangeImgdoubleSpinBox_14 = new QDoubleSpinBox(range);
        min_h_rangeImgdoubleSpinBox_14->setObjectName(QString::fromUtf8("min_h_rangeImgdoubleSpinBox_14"));

        formLayout_5->setWidget(3, QFormLayout::FieldRole, min_h_rangeImgdoubleSpinBox_14);

        max_h_rangeImg_doubleSpinBox_15 = new QDoubleSpinBox(range);
        max_h_rangeImg_doubleSpinBox_15->setObjectName(QString::fromUtf8("max_h_rangeImg_doubleSpinBox_15"));

        formLayout_5->setWidget(4, QFormLayout::FieldRole, max_h_rangeImg_doubleSpinBox_15);


        verticalLayout_11->addLayout(formLayout_5);

        projection_stackedWidget->addWidget(range);

        verticalLayout_8->addWidget(projection_stackedWidget);

        toolBox->addItem(projectionType, QString::fromUtf8("Projection"));
        classification = new QWidget();
        classification->setObjectName(QString::fromUtf8("classification"));
        classification->setGeometry(QRect(0, 0, 488, 108));
        verticalLayout_12 = new QVBoxLayout(classification);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        classificationModel_pushButton = new QPushButton(classification);
        classificationModel_pushButton->setObjectName(QString::fromUtf8("classificationModel_pushButton"));

        verticalLayout_12->addWidget(classificationModel_pushButton);

        classificationModel_lineEdit = new QLineEdit(classification);
        classificationModel_lineEdit->setObjectName(QString::fromUtf8("classificationModel_lineEdit"));

        verticalLayout_12->addWidget(classificationModel_lineEdit);

        formLayout_6 = new QFormLayout();
        formLayout_6->setSpacing(6);
        formLayout_6->setObjectName(QString::fromUtf8("formLayout_6"));
        label_30 = new QLabel(classification);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        formLayout_6->setWidget(0, QFormLayout::LabelRole, label_30);

        numberOfClasses_spinBox_17 = new QSpinBox(classification);
        numberOfClasses_spinBox_17->setObjectName(QString::fromUtf8("numberOfClasses_spinBox_17"));

        formLayout_6->setWidget(0, QFormLayout::FieldRole, numberOfClasses_spinBox_17);


        verticalLayout_12->addLayout(formLayout_6);

        toolBox->addItem(classification, QString::fromUtf8("Classification"));
        benchmarkType = new QWidget();
        benchmarkType->setObjectName(QString::fromUtf8("benchmarkType"));
        benchmarkType->setGeometry(QRect(0, 0, 488, 231));
        verticalLayout_13 = new QVBoxLayout(benchmarkType);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        benchmarkSaveFolder_pushButton = new QPushButton(benchmarkType);
        benchmarkSaveFolder_pushButton->setObjectName(QString::fromUtf8("benchmarkSaveFolder_pushButton"));

        verticalLayout_13->addWidget(benchmarkSaveFolder_pushButton);

        benchmarkSaveFolder_lineEdit = new QLineEdit(benchmarkType);
        benchmarkSaveFolder_lineEdit->setObjectName(QString::fromUtf8("benchmarkSaveFolder_lineEdit"));

        verticalLayout_13->addWidget(benchmarkSaveFolder_lineEdit);

        selectClassMapping_pushButton = new QPushButton(benchmarkType);
        selectClassMapping_pushButton->setObjectName(QString::fromUtf8("selectClassMapping_pushButton"));

        verticalLayout_13->addWidget(selectClassMapping_pushButton);

        selectClassMapping_lineEdit = new QLineEdit(benchmarkType);
        selectClassMapping_lineEdit->setObjectName(QString::fromUtf8("selectClassMapping_lineEdit"));

        verticalLayout_13->addWidget(selectClassMapping_lineEdit);

        benchmark_comboBox = new QComboBox(benchmarkType);
        benchmark_comboBox->addItem(QString());
        benchmark_comboBox->addItem(QString());
        benchmark_comboBox->setObjectName(QString::fromUtf8("benchmark_comboBox"));

        verticalLayout_13->addWidget(benchmark_comboBox);

        orientedBB_checkBox = new QCheckBox(benchmarkType);
        orientedBB_checkBox->setObjectName(QString::fromUtf8("orientedBB_checkBox"));

        verticalLayout_13->addWidget(orientedBB_checkBox);

        dontClassify_checkBox = new QCheckBox(benchmarkType);
        dontClassify_checkBox->setObjectName(QString::fromUtf8("dontClassify_checkBox"));

        verticalLayout_13->addWidget(dontClassify_checkBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer);

        toolBox->addItem(benchmarkType, QString::fromUtf8("Benchmark"));

        left_verticalLayout->addWidget(toolBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, -1);
        view_pushButton = new QPushButton(settings_widget);
        view_pushButton->setObjectName(QString::fromUtf8("view_pushButton"));

        horizontalLayout_3->addWidget(view_pushButton);

        viewAll_pushButton = new QPushButton(settings_widget);
        viewAll_pushButton->setObjectName(QString::fromUtf8("viewAll_pushButton"));

        horizontalLayout_3->addWidget(viewAll_pushButton);


        left_verticalLayout->addLayout(horizontalLayout_3);

        segment_pushButton = new QPushButton(settings_widget);
        segment_pushButton->setObjectName(QString::fromUtf8("segment_pushButton"));

        left_verticalLayout->addWidget(segment_pushButton);

        project_pushButton = new QPushButton(settings_widget);
        project_pushButton->setObjectName(QString::fromUtf8("project_pushButton"));

        left_verticalLayout->addWidget(project_pushButton);

        classify_pushButton = new QPushButton(settings_widget);
        classify_pushButton->setObjectName(QString::fromUtf8("classify_pushButton"));

        left_verticalLayout->addWidget(classify_pushButton);

        benchmark_pushButton = new QPushButton(settings_widget);
        benchmark_pushButton->setObjectName(QString::fromUtf8("benchmark_pushButton"));

        left_verticalLayout->addWidget(benchmark_pushButton);


        verticalLayout_3->addLayout(left_verticalLayout);

        splitter->addWidget(settings_widget);
        view_widget = new QWidget(splitter);
        view_widget->setObjectName(QString::fromUtf8("view_widget"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(2);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(view_widget->sizePolicy().hasHeightForWidth());
        view_widget->setSizePolicy(sizePolicy3);
        verticalLayout = new QVBoxLayout(view_widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        central_verticalLayout = new QVBoxLayout();
        central_verticalLayout->setSpacing(6);
        central_verticalLayout->setObjectName(QString::fromUtf8("central_verticalLayout"));
        central_verticalLayout->setContentsMargins(0, -1, -1, -1);
        qvtkView_widget = new QVTKWidget(view_widget);
        qvtkView_widget->setObjectName(QString::fromUtf8("qvtkView_widget"));
        qvtkView_widget->setMinimumSize(QSize(300, 0));

        central_verticalLayout->addWidget(qvtkView_widget);


        verticalLayout->addLayout(central_verticalLayout);

        splitter->addWidget(view_widget);
        splitter_3->addWidget(splitter);
        structureView_widget = new QWidget(splitter_3);
        structureView_widget->setObjectName(QString::fromUtf8("structureView_widget"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(structureView_widget->sizePolicy().hasHeightForWidth());
        structureView_widget->setSizePolicy(sizePolicy4);
        structureView_widget->setMinimumSize(QSize(100, 0));
        verticalLayout_4 = new QVBoxLayout(structureView_widget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        right_verticalLayout_2 = new QVBoxLayout();
        right_verticalLayout_2->setSpacing(6);
        right_verticalLayout_2->setObjectName(QString::fromUtf8("right_verticalLayout_2"));
        right_verticalLayout_2->setContentsMargins(0, -1, 0, -1);
        treeWidget = new QTreeWidget(structureView_widget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("Path/Name"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

        right_verticalLayout_2->addWidget(treeWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        load_button = new QPushButton(structureView_widget);
        load_button->setObjectName(QString::fromUtf8("load_button"));

        horizontalLayout_2->addWidget(load_button);

        loadObjects_button = new QPushButton(structureView_widget);
        loadObjects_button->setObjectName(QString::fromUtf8("loadObjects_button"));

        horizontalLayout_2->addWidget(loadObjects_button);

        remove_pushButton = new QPushButton(structureView_widget);
        remove_pushButton->setObjectName(QString::fromUtf8("remove_pushButton"));

        horizontalLayout_2->addWidget(remove_pushButton);


        right_verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_4->addLayout(right_verticalLayout_2);

        splitter_3->addWidget(structureView_widget);

        verticalLayout_14->addWidget(splitter_3);

        stackedWidget->addWidget(classify);
        prepareDataset = new QWidget();
        prepareDataset->setObjectName(QString::fromUtf8("prepareDataset"));
        horizontalLayout_4 = new QHBoxLayout(prepareDataset);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        splitter_2 = new QSplitter(prepareDataset);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        left_widget_1 = new QWidget(splitter_2);
        left_widget_1->setObjectName(QString::fromUtf8("left_widget_1"));
        sizePolicy2.setHeightForWidth(left_widget_1->sizePolicy().hasHeightForWidth());
        left_widget_1->setSizePolicy(sizePolicy2);
        verticalLayout_16 = new QVBoxLayout(left_widget_1);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        toolBox_2 = new QToolBox(left_widget_1);
        toolBox_2->setObjectName(QString::fromUtf8("toolBox_2"));
        imageFrom3D = new QWidget();
        imageFrom3D->setObjectName(QString::fromUtf8("imageFrom3D"));
        imageFrom3D->setGeometry(QRect(0, 0, 474, 331));
        verticalLayout_19 = new QVBoxLayout(imageFrom3D);
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setContentsMargins(11, 11, 11, 11);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        preparedImageType_comboBox = new QComboBox(imageFrom3D);
        preparedImageType_comboBox->addItem(QString());
        preparedImageType_comboBox->addItem(QString());
        preparedImageType_comboBox->setObjectName(QString::fromUtf8("preparedImageType_comboBox"));

        verticalLayout_19->addWidget(preparedImageType_comboBox);

        formLayout_7 = new QFormLayout();
        formLayout_7->setSpacing(6);
        formLayout_7->setObjectName(QString::fromUtf8("formLayout_7"));
        label_31 = new QLabel(imageFrom3D);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        formLayout_7->setWidget(0, QFormLayout::LabelRole, label_31);

        spinBox_18 = new QSpinBox(imageFrom3D);
        spinBox_18->setObjectName(QString::fromUtf8("spinBox_18"));

        formLayout_7->setWidget(0, QFormLayout::FieldRole, spinBox_18);

        label_33 = new QLabel(imageFrom3D);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        formLayout_7->setWidget(2, QFormLayout::LabelRole, label_33);

        label_32 = new QLabel(imageFrom3D);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        formLayout_7->setWidget(1, QFormLayout::LabelRole, label_32);

        label_34 = new QLabel(imageFrom3D);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        formLayout_7->setWidget(4, QFormLayout::LabelRole, label_34);

        label_35 = new QLabel(imageFrom3D);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        formLayout_7->setWidget(3, QFormLayout::LabelRole, label_35);

        label_36 = new QLabel(imageFrom3D);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        formLayout_7->setWidget(5, QFormLayout::LabelRole, label_36);

        doubleSpinBox_11 = new QDoubleSpinBox(imageFrom3D);
        doubleSpinBox_11->setObjectName(QString::fromUtf8("doubleSpinBox_11"));

        formLayout_7->setWidget(1, QFormLayout::FieldRole, doubleSpinBox_11);

        doubleSpinBox_12 = new QDoubleSpinBox(imageFrom3D);
        doubleSpinBox_12->setObjectName(QString::fromUtf8("doubleSpinBox_12"));

        formLayout_7->setWidget(2, QFormLayout::FieldRole, doubleSpinBox_12);

        doubleSpinBox_13 = new QDoubleSpinBox(imageFrom3D);
        doubleSpinBox_13->setObjectName(QString::fromUtf8("doubleSpinBox_13"));

        formLayout_7->setWidget(3, QFormLayout::FieldRole, doubleSpinBox_13);

        doubleSpinBox_14 = new QDoubleSpinBox(imageFrom3D);
        doubleSpinBox_14->setObjectName(QString::fromUtf8("doubleSpinBox_14"));

        formLayout_7->setWidget(4, QFormLayout::FieldRole, doubleSpinBox_14);

        spinBox_19 = new QSpinBox(imageFrom3D);
        spinBox_19->setObjectName(QString::fromUtf8("spinBox_19"));
        spinBox_19->setMinimum(1);

        formLayout_7->setWidget(5, QFormLayout::FieldRole, spinBox_19);


        verticalLayout_19->addLayout(formLayout_7);

        prepareFrom3D_pushButton = new QPushButton(imageFrom3D);
        prepareFrom3D_pushButton->setObjectName(QString::fromUtf8("prepareFrom3D_pushButton"));

        verticalLayout_19->addWidget(prepareFrom3D_pushButton);

        toolBox_2->addItem(imageFrom3D, QString::fromUtf8("Image data from 3D objects"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 474, 331));
        toolBox_2->addItem(page_2, QString::fromUtf8("Page 2"));

        verticalLayout_15->addWidget(toolBox_2);


        verticalLayout_16->addLayout(verticalLayout_15);

        splitter_2->addWidget(left_widget_1);
        right_widget_1 = new QWidget(splitter_2);
        right_widget_1->setObjectName(QString::fromUtf8("right_widget_1"));
        sizePolicy3.setHeightForWidth(right_widget_1->sizePolicy().hasHeightForWidth());
        right_widget_1->setSizePolicy(sizePolicy3);
        verticalLayout_18 = new QVBoxLayout(right_widget_1);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        prepare_treeWidget = new QTreeWidget(right_widget_1);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(prepare_treeWidget);
        __qtreewidgetitem1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEditable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        new QTreeWidgetItem(prepare_treeWidget);
        prepare_treeWidget->setObjectName(QString::fromUtf8("prepare_treeWidget"));
        prepare_treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout_17->addWidget(prepare_treeWidget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 9, -1, -1);
        addPrepareTreeItem_pushButton = new QPushButton(right_widget_1);
        addPrepareTreeItem_pushButton->setObjectName(QString::fromUtf8("addPrepareTreeItem_pushButton"));

        horizontalLayout_5->addWidget(addPrepareTreeItem_pushButton);

        removePrepareTreeItem_pushButton = new QPushButton(right_widget_1);
        removePrepareTreeItem_pushButton->setObjectName(QString::fromUtf8("removePrepareTreeItem_pushButton"));

        horizontalLayout_5->addWidget(removePrepareTreeItem_pushButton);


        verticalLayout_17->addLayout(horizontalLayout_5);


        verticalLayout_18->addLayout(verticalLayout_17);

        splitter_2->addWidget(right_widget_1);

        horizontalLayout_4->addWidget(splitter_2);

        stackedWidget->addWidget(prepareDataset);
        vertical_splitter->addWidget(stackedWidget);
        log_textEdit = new QTextEdit(vertical_splitter);
        log_textEdit->setObjectName(QString::fromUtf8("log_textEdit"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(1);
        sizePolicy5.setHeightForWidth(log_textEdit->sizePolicy().hasHeightForWidth());
        log_textEdit->setSizePolicy(sizePolicy5);
        vertical_splitter->addWidget(log_textEdit);

        verticalLayout_7->addWidget(vertical_splitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1015, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setToolTipsVisible(false);
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuFile->addAction(actionsave_configuration);
        menuFile->addAction(actionload_configuration);
        menuFile->addSeparator();
        menuFile->addAction(actionsave_selected_clouds);
        menuFile->addAction(actionload_clouds);
        menuTools->addAction(actionClassification);
        menuTools->addAction(actionTraining_data_preparation);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        toolBox->setCurrentIndex(2);
        segmentation_stackedWidget->setCurrentIndex(0);
        projection_stackedWidget->setCurrentIndex(0);
        toolBox_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionClassification->setText(QApplication::translate("MainWindow", "Classification", nullptr));
        actionTraining_data_preparation->setText(QApplication::translate("MainWindow", "Training data preparation", nullptr));
        actionsave_configuration->setText(QApplication::translate("MainWindow", "save configuration", nullptr));
        actionload_configuration->setText(QApplication::translate("MainWindow", "load configuration", nullptr));
        actionsave_selected_clouds->setText(QApplication::translate("MainWindow", "save selected clouds", nullptr));
        actionload_clouds->setText(QApplication::translate("MainWindow", "load clouds", nullptr));
        segmentation_comboBox->setItemText(0, QApplication::translate("MainWindow", "Difference of Normals - one step", nullptr));
        segmentation_comboBox->setItemText(1, QApplication::translate("MainWindow", "Difference of Normals - two step", nullptr));

        label->setText(QApplication::translate("MainWindow", "scale 1", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "scale 2", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "threshold", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "segradius", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "approx", nullptr));
        approx_checkBox->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "decimation", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "scale 1", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "scale 2", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "threshold", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "segradius", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "approx", nullptr));
        approx_twoStep_checkBox_2->setText(QString());
        label_12->setText(QApplication::translate("MainWindow", "decimation", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "scale 1_1", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "scale 2_1", nullptr));
        toolBox->setItemText(toolBox->indexOf(segmentationType), QApplication::translate("MainWindow", "Segmentation", nullptr));
        projectionSaveFolder_pushButton->setText(QApplication::translate("MainWindow", "select save folder", nullptr));
        projection_comboBox->setItemText(0, QApplication::translate("MainWindow", "Binary", nullptr));
        projection_comboBox->setItemText(1, QApplication::translate("MainWindow", "Range", nullptr));

        editProjection_groupBox->setTitle(QApplication::translate("MainWindow", "edit", nullptr));
        label_21->setText(QApplication::translate("MainWindow", "Kernel shape", nullptr));
        editProjKernelShape_comboBox->setItemText(0, QApplication::translate("MainWindow", "Elipse", nullptr));
        editProjKernelShape_comboBox->setItemText(1, QApplication::translate("MainWindow", "Cross", nullptr));
        editProjKernelShape_comboBox->setItemText(2, QApplication::translate("MainWindow", "Rectangle", nullptr));

        label_22->setText(QApplication::translate("MainWindow", "Kernel width", nullptr));
        label_23->setText(QApplication::translate("MainWindow", "Kernel height", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "min. hor. angle [deg]", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "max. hor. angle [deg]", nullptr));
        label_18->setText(QApplication::translate("MainWindow", "num. of hor. projections", nullptr));
        label_17->setText(QApplication::translate("MainWindow", "min. ver. angle [deg]", nullptr));
        label_20->setText(QApplication::translate("MainWindow", "max. ver. angle [deg]", nullptr));
        label_19->setText(QApplication::translate("MainWindow", "num. of ver. projections", nullptr));
        label_24->setText(QApplication::translate("MainWindow", "min. hor. angle [deg]", nullptr));
        label_25->setText(QApplication::translate("MainWindow", "max. hor. angle [deg]", nullptr));
        label_26->setText(QApplication::translate("MainWindow", "num. of hor. projections", nullptr));
        label_27->setText(QApplication::translate("MainWindow", "min. ver. angle [deg]", nullptr));
        label_28->setText(QApplication::translate("MainWindow", "max. ver. angle [deg]", nullptr));
        label_29->setText(QApplication::translate("MainWindow", "num. of ver. projections", nullptr));
        toolBox->setItemText(toolBox->indexOf(projectionType), QApplication::translate("MainWindow", "Projection", nullptr));
        classificationModel_pushButton->setText(QApplication::translate("MainWindow", "select model", nullptr));
        label_30->setText(QApplication::translate("MainWindow", "Number of classes", nullptr));
        toolBox->setItemText(toolBox->indexOf(classification), QApplication::translate("MainWindow", "Classification", nullptr));
        benchmarkSaveFolder_pushButton->setText(QApplication::translate("MainWindow", "slect save folder", nullptr));
        benchmarkSaveFolder_lineEdit->setText(QApplication::translate("MainWindow", "/home/radek/Documents/Qt5/data/benchmark", nullptr));
        selectClassMapping_pushButton->setText(QApplication::translate("MainWindow", "select class mapping file", nullptr));
        selectClassMapping_lineEdit->setText(QApplication::translate("MainWindow", "/home/radek/Documents/Qt5/data/benchmark/class_mapping", nullptr));
        benchmark_comboBox->setItemText(0, QApplication::translate("MainWindow", "Custom benchmark", nullptr));
        benchmark_comboBox->setItemText(1, QApplication::translate("MainWindow", "KITTI benchmark", nullptr));

        orientedBB_checkBox->setText(QApplication::translate("MainWindow", "calculate orientaion", nullptr));
        dontClassify_checkBox->setText(QApplication::translate("MainWindow", "dont classify before benchmark", nullptr));
        toolBox->setItemText(toolBox->indexOf(benchmarkType), QApplication::translate("MainWindow", "Benchmark", nullptr));
        view_pushButton->setText(QApplication::translate("MainWindow", "View", nullptr));
        viewAll_pushButton->setText(QApplication::translate("MainWindow", "View all objects in scene", nullptr));
        segment_pushButton->setText(QApplication::translate("MainWindow", "Segment", nullptr));
        project_pushButton->setText(QApplication::translate("MainWindow", "Project", nullptr));
        classify_pushButton->setText(QApplication::translate("MainWindow", "Classify", nullptr));
        benchmark_pushButton->setText(QApplication::translate("MainWindow", "Benchmark", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(4, QApplication::translate("MainWindow", "NN Response Vector", nullptr));
        ___qtreewidgetitem->setText(3, QApplication::translate("MainWindow", "Class Name", nullptr));
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "Class", nullptr));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "Cloud Type", nullptr));
        load_button->setText(QApplication::translate("MainWindow", "Load scenes", nullptr));
        loadObjects_button->setText(QApplication::translate("MainWindow", "Load objects", nullptr));
        remove_pushButton->setText(QApplication::translate("MainWindow", "Remove", nullptr));
        preparedImageType_comboBox->setItemText(0, QApplication::translate("MainWindow", "Binary", nullptr));
        preparedImageType_comboBox->setItemText(1, QApplication::translate("MainWindow", "Range", nullptr));

        label_31->setText(QApplication::translate("MainWindow", "Total projections", nullptr));
        label_33->setText(QApplication::translate("MainWindow", "Horizontal end deg", nullptr));
        label_32->setText(QApplication::translate("MainWindow", "Horizontal start deg", nullptr));
        label_34->setText(QApplication::translate("MainWindow", "Vertical end deg", nullptr));
        label_35->setText(QApplication::translate("MainWindow", "Vertical start deg", nullptr));
        label_36->setText(QApplication::translate("MainWindow", "Number of vertical views", nullptr));
        prepareFrom3D_pushButton->setText(QApplication::translate("MainWindow", "Prepare", nullptr));
        toolBox_2->setItemText(toolBox_2->indexOf(imageFrom3D), QApplication::translate("MainWindow", "Image data from 3D objects", nullptr));
        toolBox_2->setItemText(toolBox_2->indexOf(page_2), QApplication::translate("MainWindow", "Page 2", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = prepare_treeWidget->headerItem();
        ___qtreewidgetitem1->setText(2, QApplication::translate("MainWindow", "state", nullptr));
        ___qtreewidgetitem1->setText(1, QApplication::translate("MainWindow", "destination", nullptr));
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "source", nullptr));

        const bool __sortingEnabled = prepare_treeWidget->isSortingEnabled();
        prepare_treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem2 = prepare_treeWidget->topLevelItem(0);
        ___qtreewidgetitem2->setText(1, QApplication::translate("MainWindow", "/home/radek/Documents/Qt5/data/prepare/car", nullptr));
        ___qtreewidgetitem2->setText(0, QApplication::translate("MainWindow", "/home/radek/DeepLearning/datasets_3D/shapenet/car/val/PCD", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = prepare_treeWidget->topLevelItem(1);
        ___qtreewidgetitem3->setText(2, QApplication::translate("MainWindow", "...", nullptr));
        ___qtreewidgetitem3->setText(1, QApplication::translate("MainWindow", "b", nullptr));
        ___qtreewidgetitem3->setText(0, QApplication::translate("MainWindow", "a", nullptr));
        prepare_treeWidget->setSortingEnabled(__sortingEnabled);

        addPrepareTreeItem_pushButton->setText(QApplication::translate("MainWindow", "Add", nullptr));
        removePrepareTreeItem_pushButton->setText(QApplication::translate("MainWindow", "Remove", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
