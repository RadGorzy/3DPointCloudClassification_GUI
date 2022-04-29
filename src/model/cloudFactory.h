//
// Created by radek on 16.03.19.
//
#ifndef INC_3DPOINTCLOUDCLASSIFICATION_CLOUDFACTORY_H
#define INC_3DPOINTCLOUDCLASSIFICATION_CLOUDFACTORY_H
class PointCloudController;
#include "model/pointCloud.h"
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
class CloudObject;
class CloudScene;
class CloudComponent;
/*
class AbstractCloudFactory{
public:
    virtual std::vector<std::shared_ptr<CloudObject>> create(const std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr>  &clouds, const std::string parentSceneName);
    //virtual std::vector<std::shared_ptr<CloudObject>> create(std::vector<pcl::PointIndices>* clusterIndices, pcl::PointCloud<pcl::PointNormal>::Ptr doncloud);

    //virtual std::shared_ptr<CloudComponent> create(std::string FILEPATH);
    virtual std::shared_ptr<CloudObject> create(std::string FILEPATH);
    virtual std::shared_ptr<CloudScene> create(std::string FILEPATH);
};
*/
void loadPointCloud(std::string FILEPATH,pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud);
class CloudObjectFactory{
public:
    std::vector<std::unique_ptr<CloudObject>> create(const std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr>  &clouds,const std::string parentSceneName="",const std::string parentSourcePath=""); //crate CloudObjects from vector of point clouds (created for ex. during segmentation)
    std::vector<std::unique_ptr<CloudObject>> create(const std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr>  &clouds,std::shared_ptr<PointCloudController> controller, const std::string parentSceneName="",const std::string parentSourcePath="");//when using in model-view-controller application
    std::unique_ptr<CloudObject> create(std::string FILEPATH,std::shared_ptr<PointCloudController> controller,const std::string sourcePath="", const std::string parentSceneName="",const std::string parentSourcePath="",int id=-1, int classID=-1,std::vector<float> nnResponseVector={});//when using in model-view-controller application
    std::unique_ptr<CloudObject> create(std::string FILEPATH);
    //std::vector<std::shared_ptr<CloudObject>> create(std::vector<pcl::PointIndices>* clusterIndices, pcl::PointCloud<pcl::PointNormal>::Ptr doncloud);
};
class CloudSceneFactory{
public:
    std::unique_ptr<CloudScene> create(std::string FILEPATH); //create CloudScene from file (.pcd or .bin)
    std::unique_ptr<CloudScene> create(std::string FILEPATH,std::shared_ptr<PointCloudController> controller);
};
#endif //INC_3DPOINTCLOUDCLASSIFICATION_OBJFACTORY_H
