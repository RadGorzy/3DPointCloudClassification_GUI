//
// Created by radek on 21.03.19.
//

#ifndef INC_3DPOINTCLOUDCLASSIFICATION_BENCHMARKANDVISUALIZE_H
#define INC_3DPOINTCLOUDCLASSIFICATION_BENCHMARKANDVISUALIZE_H
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/features/moment_of_inertia_estimation.h>
#include <pcl/common/common.h>//do getMinMax3D
#include <fstream> //->?do zapisywania do pliku .txt
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
enum BBType{type_AxisAlignedBoundingBox, type_OrientedBoundingBox, type_NotSpecified};

class BoundingBoxType{
protected:
    pcl::PointXYZ min_point;
    pcl::PointXYZ max_point;
    pcl::PointXYZ center; //->? ustaw paramtery domyslne ! np. #include <limits> + center=std::numeric_limits<float>::quiet_NaN();
    float l=-1; //object (or max bounding box when using AABB) length
    float w=-1; //
    float h=-1;
    float yaw;//->? ustaw paramtery domyslne ! np. #include <limits> + center=std::numeric_limits<float>::quiet_NaN();
    BBType bbType = type_NotSpecified;
public:
    explicit BoundingBoxType(BBType type);
    virtual void calculate(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)=0;
    pcl::PointXYZ getMinPt();
    pcl::PointXYZ getMaxPt();
    pcl::PointXYZ getCenter();
    float getLength();
    float getWidth();
    float getHeight();
    float getYaw();
    BBType getType();
    virtual Eigen::Quaternionf getQuaternionf();
    virtual Eigen::Vector3f getOBB_positionV3f();
};
class AxisAlignedBoudningBox:public BoundingBoxType{
public:
    AxisAlignedBoudningBox();
    void calculate(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
};
class OrientedBoundingBox:public BoundingBoxType{
private:
    BBType bbType = type_OrientedBoundingBox;
    Eigen::Quaternionf OBB_quaternion;//wykorzystywane tylko do rysowania boundingboxa (funkcja addCube z kwaternionem)
    Eigen::Vector3f OBB_positionV3f;//wykorzystywane tylko do rysowania boundingboxa (funkcja addCube z kwaternionem)
public:
    OrientedBoundingBox();
    void calculate(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
    Eigen::Quaternionf getQuaternionf();
    Eigen::Vector3f getOBB_positionV3f();
};

class BenchmarkType{
protected:
    std::shared_ptr<BoundingBoxType> boundingBox;
    bool class_mapping_set=false;
    std::vector<std::string> classList;
    int class_id=-1;
    std::string FILEPATH=""; //path to the labels.txt folder
    std::string FILENAME="object_labels.txt";
public:
    explicit BenchmarkType(std::shared_ptr<BoundingBoxType> bBox);
    virtual void calculateParameters(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)=0;
    virtual void saveTxt()=0;
    void setFileName(std::string fName);
    void setFilePath(std::string fPath);
    void setClassMapping(std::vector<std::string> classList); //classList - on i'th index should contain class name associated with i'th class_id (f.e. classList[4]='pedestrain' -> so 'pedestrian' class_id = 4)
    virtual std::string mapClass(int i); //default class mapping (f.e. cloud class_id = 0 = 'car')
    std::vector<pcl::PointXYZ> getBoundingBox();
    virtual void benchmark(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, int c_id);
};
class CustomBenchmark:public BenchmarkType{
public:
    CustomBenchmark(std::shared_ptr<BoundingBoxType> bBox);
    void saveTxt();
    void calculateParameters(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
};
class KITTIBenchmark:public BenchmarkType{
private:
    std::string calib_path; //filepath of KITTI calibration file
    std::string left_image_path;
    bool CALCULATE_2D_BB=0;
    double bb2D_Xmin=0;
    double bb2D_Ymin=0;
    double bb2D_Xmax=0;
    double bb2D_Ymax=0;
    double score=1; //->? to jest przekoanie ze obiekt nalezy do klasy class_id
    bool add_only_if_visable_on_image=false;
    unsigned int im_width=0;  //dimensions of 2D images from KITTI dataset
    unsigned  int im_height=0;
public:
    KITTIBenchmark(std::shared_ptr<BoundingBoxType> bBox);
    void saveTxt();
    void calculateParameters(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
    void getMatrix(Eigen::MatrixXd &mat, std::string line);
    void transformToLeftImage(pcl::PointXYZ point,Eigen::VectorXd &point_transformed,bool only_to_camera_coordinates=false);
    void setCALCULATE_2D_BB(bool calculate);
    void benchmark(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,int c_id);
};

class VisualizationType{
public:
    virtual void visualize(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,int class_id,std::string name, pcl::visualization::PCLVisualizer::Ptr viewer)=0;
    std::vector<uint8_t> mapColor(int class_id);
};
class VisualizationNoBB:public VisualizationType{
public:
    void visualize(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,int class_id,std::string name, pcl::visualization::PCLVisualizer::Ptr viewer);
};
class VisualizationWithBB:public VisualizationType{
private:
    std::shared_ptr<BoundingBoxType> boundingBox= nullptr;
public:
    VisualizationWithBB(std::shared_ptr<BoundingBoxType> bBox); //use this constructor if you want to draw bounding boxes
    void visualize(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,int class_id,std::string name, pcl::visualization::PCLVisualizer::Ptr viewer);
};

#endif //INC_3DPOINTCLOUDCLASSIFICATION_BENCHMARKANDVISUALIZE_H
