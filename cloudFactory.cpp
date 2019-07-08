//
// Created by radek on 16.03.19.
//
#include "cloudFactory.h"
#include "helperFunctions.h"
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <fstream>

void loadPointCloud(std::string FILEPATH,pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud){
    if(ends_with(FILEPATH,".bin"))
    {
        // load point cloud
        pcl::PointCloud<pcl::PointXYZI>::Ptr points (new pcl::PointCloud<pcl::PointXYZI>);
        std::fstream input(FILEPATH.c_str(), std::ios::in | std::ios::binary); //read (ios::in) file "FILEPATH" in binary mode (ios::binary) -> for more info check fstream initializetion constructor parameters
        if(!input.good()){
            std::cout << "Could not read file: " << FILEPATH << std::endl;
            //std::exit(EXIT_FAILURE);
        }
        input.seekg(0, std::ios::beg);

        int i;
        for (i=0; input.good() && !input.eof(); i++) {
            pcl::PointXYZI point;
            input.read((char *) &point.x, 3*sizeof(float));
            input.read((char *) &point.intensity, sizeof(float));
            points->push_back(point);
        }
        input.close();
        pcl::copyPointCloud<pcl::PointXYZI,pcl::PointXYZ>(*points, *cloud); //konwersja z typu PointXYZI do PointXYZ
    }
    else if(ends_with(FILEPATH,".pcd"))
    {
        pcl::PCLPointCloud2 blob;
        pcl::io::loadPCDFile (FILEPATH.c_str(), blob);
        pcl::fromPCLPointCloud2 (blob, *cloud);
    } else
        std::cout<<"Could not read file - wrong expression (only .pcd and .bin supported"<<std::endl;

}
/*
std::vector<std::shared_ptr<CloudObject>> AbstractCloudFactory::create(const std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr>  &clouds,const std::string parentSceneName){throw std::runtime_error ("Operation not supported for this factory class");}
//std::vector<std::shared_ptr<CloudObject>> AbstractCloudFactory::create(std::vector<pcl::PointIndices>* clusterIndices, pcl::PointCloud<pcl::PointNormal>::Ptr doncloud){throw std::runtime_error ("Operation not supported for this factory class");}

//std::shared_ptr<CloudComponent> AbstractCloudFactory::create(std::string FILEPATH){throw std::runtime_error ("Operation not supported for this factory class");}
std::shared_ptr<CloudObject> AbstractCloudFactory::create(std::string FILEPATH){throw std::runtime_error ("Operation not supported for this factory class");}
std::shared_ptr<CloudScene> AbstractCloudFactory::create(std::string FILEPATH){throw std::runtime_error ("Operation not supported for this factory class");}
*/
std::vector<std::unique_ptr<CloudObject>> CloudObjectFactory::create(const std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr>  &clouds,const std::string parentSceneName,const std::string parentSourcePath){

    std::vector<std::unique_ptr<CloudObject>> cloudObjects;
    for (int i=0; i<clouds.size();++i){
        std::unique_ptr<CloudObject> cloudObject= std::make_unique<CloudObject>(clouds.at(i),i); //set id of j'th object
        cloudObject->setName(parentSceneName+"_object"+std::to_string(i));
        cloudObject->setParentSceneName(parentSceneName);
        cloudObject->setParentSourcePath(parentSourcePath);
        //->? tu tez trzeba dawac nazwe obiektom (albo poprzez setName, albo poprzez konstruktor w linijce powyzje)
        //nazwe sceny (chmury - rodzica) mozna przekazywac np. jako parametr do tej funkcji
        cloudObjects.push_back(std::move(cloudObject));
    }
    return cloudObjects;
}
std::vector<std::unique_ptr<CloudObject>> CloudObjectFactory::create(const std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr>  &clouds,std::shared_ptr<PointCloudController> controller, const std::string parentSceneName,const std::string parentSourcePath){
    std::vector<std::unique_ptr<CloudObject>> cloudObjects;
    for (int i=0; i<clouds.size();++i){
        std::unique_ptr<CloudObject> cloudObject= std::make_unique<CloudObject>(clouds.at(i),i); //set id of j'th object
        cloudObject->setName(parentSceneName+"_object"+std::to_string(i));
        cloudObject->setParentSceneName(parentSceneName);
        cloudObject->setParentSourcePath(parentSourcePath);
        cloudObject->setController(controller);
        //->? tu tez trzeba dawac nazwe obiektom (albo poprzez setName, albo poprzez konstruktor w linijce powyzje)
        //nazwe sceny (chmury - rodzica) mozna przekazywac np. jako parametr do tej funkcji
        cloudObjects.push_back(std::move(cloudObject));
    }
    return cloudObjects;
}
std::unique_ptr<CloudObject> CloudObjectFactory::create(std::string FILEPATH,std::shared_ptr<PointCloudController> controller,const std::string sourcePath, const std::string parentSceneName,const std::string parentSourcePath,int id, int classID,std::vector<float> nnResponseVector){
    std::unique_ptr<CloudObject> cloudObject;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    loadPointCloud(FILEPATH,cloud);

    //create object
    cloudObject= std::make_unique<CloudObject>(cloud
                                               ,/*name*/parentSceneName+"_object"+std::to_string(id)
                                               , sourcePath
                                               ,parentSceneName
                                               , parentSourcePath
                                               ,id
                                               ,classID
                                               ,nnResponseVector);

    cloudObject->setController(controller);
    //->? tu tez trzeba dawac nazwe obiektom (albo poprzez setName, albo poprzez konstruktor w linijce powyzje)
    //nazwe sceny (chmury - rodzica) mozna przekazywac np. jako parametr do tej funkcji
    return std::move(cloudObject);
}
std::unique_ptr<CloudObject> CloudObjectFactory::create(std::string FILEPATH){
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    loadPointCloud(FILEPATH,cloud);

    std::string cloud_name=get_filename(FILEPATH,0);

    //create object
    std::unique_ptr<CloudObject> cloudObject= std::make_unique<CloudObject>(cloud,cloud_name,FILEPATH);
    return cloudObject;
}
/*std::vector<std::shared_ptr<CloudObject>> CloudObjectFactory::create(std::vector<pcl::PointIndices>* clusterIndices, pcl::PointCloud<pcl::PointNormal>::Ptr doncloud){
    std::cout<<"USING doncloud"<<std::endl;
    int j = 0;
    std::vector<std::shared_ptr<CloudObject>> cloudObjects;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_xyz (new pcl::PointCloud<pcl::PointXYZ>); //do konwersji z PointNormal

    for (std::vector<pcl::PointIndices>::const_iterator it = clusterIndices->begin (); it != clusterIndices->end (); ++it, j++)
    {
        pcl::PointCloud<pcl::PointNormal>::Ptr cloud_cluster_don (new pcl::PointCloud<pcl::PointNormal>);

        for (auto pit = it->indices.begin (); pit != it->indices.end (); ++pit)
        {
            cloud_cluster_don->points.push_back (doncloud->points[*pit]); //->?!! orginalnie bylo cloud_cluster_don->points.push_back (doncloud->points[*pit]);
            //zamienilem doncloud na cloud (orginalna scene) bo jak mam wspolrzedne punktow i nie zalezy mi na zachowaniu
            //mapy normalnych to moge je od razu braz z orginalnej sceny (x,y,z), TAK MI SIE PRZYNAJMNIEJ WYDAJE
            ///CHYBA JEDNAK TU JEST PROBLEM !!! - sprobuj spowrotem na
        }

        cloud_cluster_don->width = static_cast<uint32_t >(cloud_cluster_don->points.size ());
        cloud_cluster_don->height = 1;
        cloud_cluster_don->is_dense = true;

        pcl::copyPointCloud<pcl::PointNormal,pcl::PointXYZ>(*cloud_cluster_don, *cloud_xyz);

        std::shared_ptr<CloudObject> cloudObject= std::make_shared<CloudObject>(cloud_xyz,j); //set id of j'th object
        //->? tu tez trzeba dawac nazwe obiektom (albo poprzez setName, albo poprzez konstruktor w linijce powyzje)
        //nazwe sceny (chmury - rodzica) mozna przekazywac np. jako parametr do tej funkcji

        cloudObjects.push_back(cloudObject);
    }

    return cloudObjects;
}
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::unique_ptr<CloudScene> CloudSceneFactory::create(std::string FILEPATH){
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    loadPointCloud(FILEPATH,cloud);

    std::string cloud_name=get_filename(FILEPATH,0);

    //create object
    std::unique_ptr<CloudScene> cloudScene= std::make_unique<CloudScene>(cloud,cloud_name,FILEPATH);
    return cloudScene;
}
std::unique_ptr<CloudScene> CloudSceneFactory::create(std::string FILEPATH,std::shared_ptr<PointCloudController> controller){
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    loadPointCloud(FILEPATH,cloud);

    std::string cloud_name=get_filename(FILEPATH,0);

    //create object
    std::unique_ptr<CloudScene> cloudScene= std::make_unique<CloudScene>(cloud,cloud_name,FILEPATH);
    cloudScene->setController(controller);
    return cloudScene;
}
