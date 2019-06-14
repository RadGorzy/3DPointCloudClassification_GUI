//
// Created by radek on 26.03.19.
//

#ifndef INC_3DPOINTCLOUDCLASSIFICATION_PREPAREDATASET_H
#define INC_3DPOINTCLOUDCLASSIFICATION_PREPAREDATASET_H

#include <string>
class CloudObject;
class CloudObjectFactory;
#include "pointCloud.h"

class PrepareDataset {

};
class PrepareDatasetFrom3D:public PrepareDataset{
protected:
    std::shared_ptr<CloudObject> object=nullptr;
    std::shared_ptr<CloudObjectFactory> factory=nullptr;
    std::shared_ptr<ProjectionType> projection=nullptr;
    std::vector<std::string> fnames; //fnames of 3D objects
    uint TOTAL_PROJECTIONS;
    uint default_num_of_proj_per_obj=36;
    double START_DEGREE=0;
    double END_DEGREE=360;
    double START_v=0;
    double END_v=0;
    int N_v=1;
    //bool RANGE_IMAGE=false
    //bool EDIT=false
public:
    PrepareDatasetFrom3D(uint TOTAL_PROJECTIONS,double START_DEGREE,double END_DEGREE ,double START_v,double END_v,int N_v);
    virtual void prepare(std::string SRC_PATH, std::string PROJECTIONS_PATH)=0;
    int calculateNumberOfProjections(uint num_of_class_obj);
    void removeSurplusProjections(std::string PROJECTIONS_PATH,int n_horizontal, int num_of_class_obj);
};

class PrepareBinaryImages:public PrepareDatasetFrom3D{
public:
    PrepareBinaryImages(uint TOTAL_PROJECTIONS,double START_DEGREE,double END_DEGREE ,double START_v,double END_v,int N_v);
    void prepare(std::string SRC_PATH, std::string PROJECTIONS_PATH);
};

class PrepareRangeImages:public PrepareDatasetFrom3D{
public:
    PrepareRangeImages(uint TOTAL_PROJECTIONS,double START_DEGREE,double END_DEGREE ,double START_v,double END_v,int N_v);
    void prepare(std::string SRC_PATH, std::string PROJECTIONS_PATH);
};


#endif //INC_3DPOINTCLOUDCLASSIFICATION_PREPAREDATASET_H
