#pragma once //without this line this problem appears: https://bugreports.qt.io/browse/QTCREATORBUG-20883
#ifndef INC_3DPOINTCLOUDCLASSIFICATION_POINTCLOUDCONTROLLER_H
#define INC_3DPOINTCLOUDCLASSIFICATION_POINTCLOUDCONTROLLER_H

#include "model/cloudFactory.h"
class MainWindow;
#include "view/mainwindow.h"

class CloudComponent;
class CloudScene;
class CloudObject;
#include "model/pointCloud.h"
class SaveLoad;
#include "view/saveLoad.h"
#include <limits>

class PointCloudController: public std::enable_shared_from_this<PointCloudController> //#//https://stackoverflow.com/questions/27894246/cast-this-to-stdshared-ptr
{
private:
    std::vector<std::unique_ptr<CloudComponent>> cachedClouds;
    std::shared_ptr<CloudSceneFactory> sceneFactory;
    std::shared_ptr<CloudObjectFactory> objectFactory;
    std::shared_ptr<BoundingBoxType> boundingBox;
    std::shared_ptr<VisualizationType> visualization;
    std::shared_ptr<SaveLoad> saveLoad;
    QTreeWidget *treeWidgetObserver;
    QVTKWidget *qVTKWidgetObserver;
    pcl::visualization::PCLVisualizer::Ptr viewerObserver;
    int cachedCloudScenesLimit=2;
    std::size_t cachedCloudsMemoryLimit=10000; //in MB
    int treeWidgetNameColumnID=0;
    int treeWidgetCloudTypeID=1;
    int treeWidgetClassIDColumnID=2;
    int treeWidgetClassNameColumnID=3;
    int treeWidgetNNResponseVectorColumnID=4;
public:
    PointCloudController();
    int getTopLevelIndexOfSelectedCloud(QTreeWidgetItem* item); //# funkcja nie edytuje orginalnych danych (item), ale zeby to podkreslic wartobyloby dac const -> to skolei powoduje inne problemy)
    QTreeWidgetItem* getChildItemWithID(QTreeWidgetItem* parent,int id);
    QTreeWidgetItem* getTopLevelItem(QTreeWidgetItem* item);//#funkcja nie edytuje orginalnych danych (item), ale zeby to podkreslic wartobyloby dac const -> to skolei powoduje inne problemy)
    void registerQTreeWidgetObserver(QTreeWidget *treeWidgetObserver);
    void registerQVTKidgetObserver(QVTKWidget *QVTKWidgetObserver);
    void registerPCLViewerObserver(pcl::visualization::PCLVisualizer::Ptr viewOb);
    std::size_t getMemoryUsageOfCachedClouds();
    void setCachedCloudsMemoryLimit(std::size_t limit);
    void updateView(QTreeWidgetItem* item);
    //void updateTreeWidgetItem(std::string cloudPath,std::vector<std::string> children);//std::unique_ptr<CloudScene> scene
    //#ponizej uzywam zwyklego wskaznika, bo w pointCloud.cpp wywoluje ta funkcje ze wskaznikiem do obiektu "this" ktory jest raw (zwykly) pointer
    void updateTreeWidgetItem(CloudComponent *cloud);//void updateTreeWidgetItem(const std::unique_ptr<CloudComponent> &cloud);
    void updateView();
    //#ponizej uzywam zwyklego wskaznika, bo w pointCloud.cpp wywoluje ta funkcje ze wskaznikiem do obiektu "this" ktory jest raw (zwykly) pointer
    void updateView(CloudComponent *cloud);//void updateView(const std::unique_ptr<CloudComponent> &cloud);
    void updateQVTKWidget();
    bool updateCachedCloudsContainer(QTreeWidgetItem* selectedItem);
    void clearViewer(pcl::visualization::PCLVisualizer::Ptr viewer);
    void clearTreeWidgetTreeChildren();
    void remove(QList<QTreeWidgetItem*> selectedClouds);
    void visualize(QTreeWidgetItem* selectedItem,pcl::visualization::PCLVisualizer::Ptr viewer);//visualize scene or single object
    void visualizeAllChildren(QTreeWidgetItem* selectedItem,pcl::visualization::PCLVisualizer::Ptr viewer);
    //void visualize(std::string cloudPath, int objectID,pcl::visualization::PCLVisualizer::Ptr viewer); //visualize segmented object
    void segment(QList<QTreeWidgetItem*> selectedClouds,std::shared_ptr<SegmentationType> segmentationType);//we should pass to this function only CloudScenes type
    void project(QList<QTreeWidgetItem*> selectedClouds,std::shared_ptr<ProjectionType> projectionType,std::shared_ptr<EditType> editType=nullptr);
    void saveProjections(QList<QTreeWidgetItem*> selectedClouds,std::string folderPath);
    //stara wersja classify
    //void classify(QList<QTreeWidgetItem*> selectedClouds,std::shared_ptr<ClassificationType> classificationType,std::string modelPath,int numOfClasses);
    void classify(QList<QTreeWidgetItem*> selectedClouds,std::shared_ptr<ClassificationType> classificationType,std::shared_ptr<SegmentationType> segmentationType,std::shared_ptr<ProjectionType> projectionType,std::shared_ptr<EditType> editType,std::string modelPath,int numOfClasses);
    void benchmark(QList<QTreeWidgetItem*> selectedClouds,std::shared_ptr<BenchmarkType> benchmarkType, std::string folderPath="./");
    //void setBenchmarkType(QList<QTreeWidgetItem*> selectedClouds,std::shared_ptr<BenchmarkType> benchmarkType);
    void saveClouds(QList<QTreeWidgetItem*> selectedClouds,QString folderPath,std::shared_ptr<SaveConditions> saveCond);
    void loadClouds(QString path);
};

#endif // CLOUDSCENESOBSERVABLE_H
