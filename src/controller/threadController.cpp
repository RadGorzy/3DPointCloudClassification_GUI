#include "controller/threadController.h"
/* stara wersja classify
void Worker::classify(const cloudControllerSharedPtr modelController, listOfTreeWidgetItemRawPtr selectedClouds,clsificationTypeSharedPtr classificationType,stdString modelPath,integer numOfClasses){
    QString result="CLASSIFICATION FINISHED";
    //qDebug()<<"CLASSIFICATION thread:  "<<thread()->currentThreadId();
    modelController->classify(selectedClouds,classificationType,modelPath,numOfClasses);
    emit resultReady(result);
}
*/
void Worker::classify(const cloudControllerSharedPtr modelController, listOfTreeWidgetItemRawPtr selectedClouds
              ,clsificationTypeSharedPtr classificationType,segmentationTypeSharedPtr segmentationType
              ,projectionTypeSharedPtr projectionType, editTypeSharedPtr editType
                      ,stdString modelPath,integer numOfClasses){
    QString result="CLASSIFICATION FINISHED";
    //qDebug()<<"CLASSIFICATION thread:  "<<thread()->currentThreadId();
    modelController->classify(selectedClouds,classificationType,segmentationType,projectionType,editType,modelPath,numOfClasses);
    emit resultReady(result);
}
void Worker::benchmark(const cloudControllerSharedPtr modelController, listOfTreeWidgetItemRawPtr selectedClouds,benchmarkTypeSharedPtr benchmarkType, stdString folderPath){
    QString result="BENCHMARK FINISHED";
    modelController->benchmark(selectedClouds,benchmarkType,folderPath);
    //qDebug()<<"BENCHMARK thread:  "<<thread()->currentThreadId();
    emit resultReady(result);
}
void Worker::prepareFrom3D(const prepareDatasetControllerSharedPtr controller, prepareDatasetFrom3DSharedPtr prepareDatasetFrom3D){
    QString result="PREPARING DATA FROM 3D OBJECTS FINISHED";
    controller->prepare(prepareDatasetFrom3D);
    emit resultReady(result);
}
void Worker::extractObjectsInstances(const prepareDatasetControllerSharedPtr controller,extractObjectsInstancesSharedPtr extractObjectsInstances){
    QString result="EXTRACTING SINGLE INSTANCES FROM SCENES WITH OBJECTS BELONGING TO SAME CLASSES FINISHED";
    controller->extract(extractObjectsInstances);
    emit resultReady(result);
}
///////////////////////////////////////////
ThreadController::ThreadController()
{
    //we have to register custom type in order to use it in connect (https://doc.qt.io/qt-5/qmetatype.html#qRegisterMetaType-1)
    qRegisterMetaType<cloudControllerSharedPtr>();
    qRegisterMetaType<listOfTreeWidgetItemRawPtr>();
    qRegisterMetaType<clsificationTypeSharedPtr>("clsificationTypeSharedPtr");
    qRegisterMetaType<segmentationTypeSharedPtr>("segmentationTypeSharedPtr");
    qRegisterMetaType<projectionTypeSharedPtr>("projectionTypeSharedPtr");
    qRegisterMetaType<editTypeSharedPtr>("editTypeSharePtr");
    qRegisterMetaType<benchmarkTypeSharedPtr>();
    qRegisterMetaType<stdString>();
    qRegisterMetaType<integer>("integer");//have to fill parenthesis otherwise : QObject::connect: Cannot queue arguments of type 'integer' ,(Make sure 'integer' is registered using qRegisterMetaType().)

    qRegisterMetaType<prepareDatasetControllerSharedPtr>();
    qRegisterMetaType<prepareDatasetFrom3DSharedPtr>();
    qRegisterMetaType<extractObjectsInstancesSharedPtr>();

    Worker *worker = new Worker;
    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &ThreadController::classify, worker, &Worker::classify);
    connect(this, &ThreadController::benchmark, worker, &Worker::benchmark);
    connect(this, &ThreadController::prepareFrom3D, worker, &Worker::prepareFrom3D);
    connect(this, &ThreadController::extractObjectsInstances, worker, &Worker::extractObjectsInstances);
    connect(worker, &Worker::resultReady, this, &ThreadController::handleResults);
    workerThread.start();
}
ThreadController::~ThreadController(){
    workerThread.quit();
    workerThread.wait();
}
void ThreadController::handleResults(const QString &result){
    qDebug()<<result;
}

