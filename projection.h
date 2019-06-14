//
// Created by radek on 15.03.19.
//

#ifndef INC_3DPOINTCLOUDCLASSIFICATION_PROJECTION_H
#define INC_3DPOINTCLOUDCLASSIFICATION_PROJECTION_H

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <opencv2/opencv.hpp>
#include <pcl/range_image/range_image_planar.h>
#include <string>
struct ProjectionParameters{ //# NAUKA-> CZYTAJ: https://stackoverflow.com/questions/4203010/how-to-initialize-member-struct-in-initializer-list-of-c-class
    ProjectionParameters(double min_deg,double max_deg , int n, double min_h, double max_h,int n_h);
    double min_h=0;  //min observation angle vertically
    double max_h=0; //max -||-
    //#zrob jakos tak, zeby wartosci min_h max_h itd. nie mozna bylo zmiennic przez przypadek (zeby tylko sie dalo przez konstruktor lub przez f. setParametes())_
    int n_h=1;// number of vertical angles at witch we want to project object

    double min_deg=0;// for horizontal observations, analogously as for vertical
    double max_deg=0;
    int n=1;// number of horizontal angles at witch we want to project object
};

class ProjectionType{
protected:
    ///->? Uwaga - tu mozna rozwazyc deklaracje niektorych zmiennych (np. alfa_deg) jako static, poniewaz nie musimy tworzyc nowych tych zmiennych przey inicjalizowaniu nowego obiektu tej klasy
    ///moze to miec znaczenie chyba dla wydajnosci, jezeli towrzylibysmy duzo obiektow tej klasy -> ale ostateczenie nie towrzymy przeciez duzo obiektow typu ProjectionType wiec raczej nie stanowi problemu, ze nie uzwywamy static
    std::vector<cv::Mat> projections;//stores projections //vector<cv::Mat ...> projections; // jakis vector projekcji (juz obrazow 2D) danej chmury (najpewniej obiektu) - tutaj jedne, albo w kazdej z klas pochodnych
    std::vector<std::vector<uchar>> vec; //same as above but in 2D uchar vector type instead of cv::Mat
    ProjectionParameters projParam;
    double alfa_h=0;//current angle (deg) at wich we're observing the object along its heigth (vertically)
    double step_h=0;// number of deegres between two consecutive projections (vertically)

    //static double alfa_deg;//current angle (deg) at wich we're observing the object across (horizontaly, arround)
    double alfa_deg=0;//current horizontal angle
    double step=0;// number of deegres between two consecutive projections (horizontally)

    int w=299; // height of projection image (number of rows)
    int k=299;// width of projection image (number of columns)

    pcl::PointXYZ object_min_pt=pcl::PointXYZ(0,0,0);  //we store min and max pt of bounding box of an axis aligned bounding box, so we dont have to calculate them later
    pcl::PointXYZ object_max_pt=pcl::PointXYZ(0,0,0);
public:
    //ProjectionType();
    ProjectionType(double min_deg,double max_deg , int n, double min_h, double max_h,int n_h);
    //ProjectionType();
    virtual std::vector<cv::Mat> project(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud); //cout<<Projection operation not supported
    void setVerticalAngle(double va);
    void setHorizontalAngle(double ha);
    void setImageHeight(int height);
    void setImageWidth(int width);
    void setParameters(double min_deg, double max_deg , int n,double min_h,double max_h,int n_h);
    void calculateStep();
    std::string getProjectionNameSuffix(int projectionNumber);
    std::vector<cv::Mat> getProjections();//->? raczej nie uzywane, bo funkcja project() zwraca juz vector z projekcjami
    std::vector<pcl::PointXYZ> getObjectMinMaxPt();
};

class BinaryProjection:public ProjectionType{
private:
    //ewentualnie bool edit; + dodatkowo funkcja setEdit(bool e) -> w ten sposob ustalamy, czy chcemy edytowac czy nie
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloudProjected;
public:
    BinaryProjection(double min_deg,double max_deg , int n, double min_h, double max_h,int n_h);
    //BinaryProjection();
    void calculateCloudProjected(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud); //->? = my_Cloud::project
    cv::Mat getCloudProjectedToImage(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud); //->? = my_Cloud::get_projection_as_array
    std::vector<cv::Mat> project(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
};

class RangeImageProjection:public ProjectionType{
private:
    pcl::RangeImagePlanar::Ptr rangeImage;
    Eigen::Affine3f sensorPose;//(Eigen::Affine3f)Eigen::Translation3f(0.0f, 0.0f, 0.0f);
    pcl::RangeImagePlanar::CoordinateFrame cordinate_frame ;
    float center_x;
    float center_y;
    float fx;//=1192;//=298; //tak bylo w ApolloScape SceneParsing camera_inttinics.txt
    float fy;
    Eigen::Quaternionf R;
    Eigen::Vector3f T;
    Eigen::Matrix4f Transformation;
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW  //inaczej blad:SegAndProj_1: /usr/include/eigen3/Eigen/src/Core/DenseStorage.h:128: Eigen::internal::plain_array<T, Size, MatrixOrArrayOptions, 32>::plain_array() [with T = float; int Size = 16; int MatrixOrArrayOptions = 0]: Assertion `(reinterpret_cast<size_t>(eigen_unaligned_array_assert_workaround_gcc47(array)) & (31)) == 0 && "this assertion is explained here: " "http://eigen.tuxfamily.org/dox-devel/group__TopicUnalignedArrayAssert.html" " **** READ THIS WEB PAGE !!! ****"' failed.
    RangeImageProjection(double min_deg,double max_deg , int n, double min_h, double max_h,int n_h); //->? zamiast tego ponizszego uzyj initilizer list i ewentualnie przenies kod do projection.cpp
                            //->? NAUKA - Constructor for 'RangeImageProjection' must explicitly initialize the base class 'ProjectionType' which does not have a default constructor
                            //czyli jak zmienie domyslny konstruktor w klasie bazowej, to w kazdej z klad pochodnuch musze go zainicjalizowac recznie
    //RangeImageProjection();
    void calculateCameraStartPosition(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,double &x_s,double &y_s);// ->? zmiana pierwszego parametru w stosunku do SegAndProj1
    Eigen::Vector4f calculatePose(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,double _x_s,double _y_s);
    void create(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);//creates range image based on camera position and pose of the camrea (use after setting all parameters (camera start position and pose))
    cv::Mat getPCLRangeImageToRangeImage(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,bool save_projections,bool normalize);
    std::vector<cv::Mat> project(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
};
#endif //INC_3DPOINTCLOUDCLASSIFICATION_PROJECTION_H
