#pragma once //without this line this problem appears: https://bugreports.qt.io/browse/QTCREATORBUG-20883

#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

#include <QObject>
#include <QThread>
#include <pointCloudController.h>
#include "typeDefForThreding.h"

class Worker : public QObject
{
    Q_OBJECT

public slots:
    // stara wersja classify
    //void classify(const cloudControllerSharedPtr modelController, listOfTreeWidgetItemRawPtr selectedClouds,classificationTypeSharedPtr classificationType,stdString modelPath,integer numOfClasses);
    //# np. dodaj jeszcze analogicznie segmentation (bo to tez moze dlugo zajac)
    //added benchmark function (despite sole file saving being quickly), because it have to wait untill classification is finished, so to handle it correctly I put it in the same thread
    void classify(const cloudControllerSharedPtr modelController, listOfTreeWidgetItemRawPtr selectedClouds
                  ,classificationTypeSharedPtr classificationType,segmentationTypeSharedPtr segmentationType
                  ,projectionTypeSharedPtr projectionType, editTypeSharedPtr editType
                  ,stdString modelPath,integer numOfClasses);
    void benchmark(const cloudControllerSharedPtr modelController, listOfTreeWidgetItemRawPtr selectedClouds,benchmarkTypeSharedPtr benchmarkType, stdString folderPath);
    void prepareFrom3D(const prepareDatasetControllerSharedPtr controller,prepareDatasetFrom3DSharedPtr prepareDatasetFrom3D);
signals:
    void resultReady(const QString &result);
};

class ThreadController:public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    ThreadController();
    ~ThreadController();

public slots:
    void handleResults(const QString &result);
signals:
    // stara wersja classify
    //void classify(const cloudControllerSharedPtr modelController, listOfTreeWidgetItemRawPtr selectedClouds,classificationTypeSharedPtr classificationType,stdString modelPath,integer numOfClasses);
    void classify(const cloudControllerSharedPtr modelController, listOfTreeWidgetItemRawPtr selectedClouds
                  ,classificationTypeSharedPtr classificationType,segmentationTypeSharedPtr segmentationType
                  ,projectionTypeSharedPtr projectionType, editTypeSharedPtr editType
                  ,stdString modelPath,integer numOfClasses);
    void benchmark(const cloudControllerSharedPtr modelController, listOfTreeWidgetItemRawPtr selectedClouds,benchmarkTypeSharedPtr benchmarkType, stdString folderPath);
    void prepareFrom3D(const prepareDatasetControllerSharedPtr controller, prepareDatasetFrom3DSharedPtr prepareDatasetFrom3D);
};

#endif // THREADCONTROLLER_H
