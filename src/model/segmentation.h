//
// Created by radek on 15.03.19.
//

#ifndef INC_3DPOINTCLOUDCLASSIFICATION_SEGMENTATION_H
#define INC_3DPOINTCLOUDCLASSIFICATION_SEGMENTATION_H


#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/PointIndices.h>

class SegmentationType{
public:
    virtual std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr>  segment(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
    virtual  pcl::PointCloud<pcl::PointNormal> getDonCloud();
};

class DONSegmentation:public SegmentationType{
private:
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
    pcl::PointCloud<pcl::PointNormal>::Ptr doncloud ; //->? czy to jest prawidlowo nadpisywane (czy resetowane i nadpisywane) pomiedzy kolejnymi scenami?
    std::vector<pcl::PointIndices> clusterIndices;
    double scale1,scale2,threshold, segradius,scale1_1, scale2_1;
    bool approx=1;
    double decimation=5;
    bool TWO_STEP_SEGMENTATION=false;
    bool VISUALIZE_NORMALS=false;
    bool SAVE=false;
public:
    DONSegmentation(double scale1=0.4,double scale2=4, double threshold=0.25,double segradius=0.4,bool approx=1,double decimation=5,bool TWO_STEP_SEGMENTATION=0, double scale1_1=0.8, double scale2_1=8);
    std::vector<pcl::PointCloud<pcl::PointNormal>::Ptr> calculateDONAndFilter(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud);
    void cluster();
    std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr>  segment(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
    pcl::PointCloud<pcl::PointNormal> getDonCloud();
};

class EuclideanClustering:public SegmentationType{
private:
    double segradius, minClusterSize, maxClusterSize;
    std::vector<pcl::PointIndices> clusterIndices;
    void getClustersIndecies(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
public:
    EuclideanClustering(double segRadius=0.4, int minClusterSize=50, int maxClusterSize=4000000);
    std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr> segment(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
};

#endif //INC_3DPOINTCLOUDCLASSIFICATION_SEGMENTATION_H
