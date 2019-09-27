#ifndef TYPEDEFFORTHREDING_H
#define TYPEDEFFORTHREDING_H
/**
 * INFO - passing custom paramertes in connect(signal, slots ):
 * 1. typedef CUSTOMTYPE customType -> for ex. typedef std::vector<MyObject*> vectorOfMyObjects
 * 2. declare type from 1. using Q_DECLARE_METATYPE() -> for ex. Q_DECLARE_METATYPE(vectorOfMyObjects)
 * 3. in function (for ex. constructor) use qRegisterMetaType<customType>() before using connect(SIGNAL,SLOTS) -> for ex. qRegisterMetaType<vectorOfMyObjects>();
 * more info: https://doc.qt.io/qt-5/qmetatype.html#qRegisterMetaType-1
 * https://doc.qt.io/qt-5/qmetatype.html#Q_DECLARE_METATYPE
**/

#include <memory>
#include <QMetaType>
class PointCloudController;
class QTreeWidgetItem;
class ClassificationType;
class SegmentationType;
class ProjectionType;
class EditType;
class BenchmarkType;
class PrepareDatasetController;
class PrepareDatasetFrom3D;
class ExtractObjectsInstances;

typedef std::shared_ptr<PointCloudController> cloudControllerSharedPtr;
typedef QList<QTreeWidgetItem*> listOfTreeWidgetItemRawPtr;
typedef std::shared_ptr<ClassificationType> classificationTypeSharedPtr;
typedef std::shared_ptr<SegmentationType> segmentationTypeSharedPtr;
typedef std::shared_ptr<ProjectionType> projectionTypeSharedPtr;
typedef std::shared_ptr<EditType> editTypeSharedPtr;
typedef std::shared_ptr<BenchmarkType> benchmarkTypeSharedPtr;
typedef std::string stdString;
typedef int integer;



typedef std::shared_ptr<PrepareDatasetController> prepareDatasetControllerSharedPtr;
typedef std::shared_ptr<PrepareDatasetFrom3D> prepareDatasetFrom3DSharedPtr;
typedef std::shared_ptr<ExtractObjectsInstances> extractObjectsInstancesSharedPtr;
//we have to Q_DECLARE_METATYPE(type)  before calling qRegisterMetaType<>() (https://doc.qt.io/qt-5/qmetatype.html#qRegisterMetaType-1)
Q_DECLARE_METATYPE(cloudControllerSharedPtr);
Q_DECLARE_METATYPE(listOfTreeWidgetItemRawPtr);
Q_DECLARE_METATYPE(classificationTypeSharedPtr);
Q_DECLARE_METATYPE(segmentationTypeSharedPtr);
Q_DECLARE_METATYPE(projectionTypeSharedPtr);
Q_DECLARE_METATYPE(editTypeSharedPtr);
Q_DECLARE_METATYPE(benchmarkTypeSharedPtr);
Q_DECLARE_METATYPE(stdString);
Q_DECLARE_METATYPE(integer);

Q_DECLARE_METATYPE(prepareDatasetControllerSharedPtr);
Q_DECLARE_METATYPE(prepareDatasetFrom3DSharedPtr);
Q_DECLARE_METATYPE(extractObjectsInstancesSharedPtr);
#endif // TYPEDEFFORTHREDING_H
