//
// Created by radek on 14.03.19.
//
#include "model/pointCloud.h"
#include <pcl/io/pcd_io.h>
#include <opencv2/opencv.hpp>

CloudComponent::CloudComponent(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name):cloud(_cloud),name(_name){}
CloudComponent::CloudComponent(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name,std::string src_path):cloud(_cloud),name(_name),sourcePath(src_path){}
CloudComponent::CloudComponent(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name,std::string src_path,std::string parName, std::string parSrcPath)
    :cloud(_cloud),name(_name),sourcePath(src_path),parentSceneName(parName),parentSourcePath(parSrcPath){}

void CloudComponent::setFactory(std::shared_ptr<CloudObjectFactory> fc){
    std::cout<<"Cannot setFactory(CloudObjectFactory) for this cloudType. Operation is supported for scenes."<<std::endl;
}

void CloudComponent::segment(std::shared_ptr<SegmentationType> segmentationType){}//{ std::cout<<"Cannot segment - Operation not supported for this cloudType class";}
void CloudComponent::project(std::shared_ptr<ProjectionType> projTyp){ throw std::runtime_error ("Operation not supported for this cloudType class");}
void CloudComponent::project(std::shared_ptr<ProjectionType> projTyp, int objectID){ throw std::runtime_error ("Operation not supported for this cloudType class");}
void CloudComponent::edit(std::shared_ptr<EditType> eType){throw std::runtime_error ("Cannot edit - Operation not supported for this cloudType class");}
void CloudComponent::edit(std::shared_ptr<EditType> eType, int objectID){throw std::runtime_error ("Cannot edit - Operation not supported for this cloudType class");}
void CloudComponent::classify(std::shared_ptr<ClassificationType> cTyp, std::string modelDir,int numOfClasses){ throw std::runtime_error ("Cannot classify - operation not supported for this cloudType class");}
//# przemysl implementacje ponizszej funkcji dla CloudObject
void CloudComponent::classify(std::shared_ptr<ClassificationType> cTyp,std::shared_ptr<SegmentationType> sTyp,std::shared_ptr<ProjectionType> pTyp,std::shared_ptr<EditType> eTyp, std::string modelDir,int numOfClasses){}
void CloudComponent::classify(std::shared_ptr<ClassificationType> cTyp, std::string modelDir,int numOfClasses, int object_id){ throw std::runtime_error ("Cannot classify - operation not supported for this cloudType class");}
void CloudComponent::visualize(std::shared_ptr<VisualizationType> vTyp){throw std::runtime_error ("Cannot visualize - Operation not supported for this cloudType class");}
void CloudComponent::visualizeAllChildren(std::shared_ptr<VisualizationType> vTyp,pcl::visualization::PCLVisualizer::Ptr viewer){std::cout<<"Cannot visualize - Operation not supported for this cloudType class";}
void CloudComponent::visualize(std::shared_ptr<VisualizationType> vTyp,pcl::visualization::PCLVisualizer::Ptr viewer){std::cout<<"Cannot visualize - Operation not supported for this cloudType class";}
void CloudComponent::visualize(std::shared_ptr<VisualizationType> vTyp,int object_id){throw std::runtime_error ("Cannot visualize - Operation not supported for this cloudType class");}
void CloudComponent::visualize(std::shared_ptr<VisualizationType> vTyp,int object_id,pcl::visualization::PCLVisualizer::Ptr viewer){throw std::runtime_error ("Cannot visualize - Operation not supported for this cloudType class");}
void CloudComponent::benchmark(std::shared_ptr<BenchmarkType> bType, std::string FILEPATH){ throw std::runtime_error ("Operation not supported for this cloudType class");}
void CloudComponent::benchmark(std::shared_ptr<BenchmarkType> bType, std::string FILEPATH,int object_id){ throw std::runtime_error ("Operation not supported for this cloudType class");}

void CloudComponent::addCloud(std::unique_ptr<CloudComponent> cc/*CloudComponent *cc*/){std::cout<<"Cannot addCloud(cc/*CloudComponent *cc*/) - Operation not supported for this cloudType class"<<std::endl;} //when we are adding objects or clouds by one (for example manually)
void CloudComponent::removeCloud(int object_ID){std::cout<<"Cannot removeCloud(object_ID) - Operation not supported for this cloudType class"<<std::endl;}
void CloudComponent::saveClouds(std::string FILEPATH){throw std::runtime_error ("Cannot save - Operation not supported for this cloudType class");}
void CloudComponent::saveClouds(std::string FILEPATH, int object_ID){std::cout<<"Cannot saveCloud(FILEPATH,object_ID)- Operation not supported for this cloudType class"<<endl;}
void CloudComponent::saveProjections(std::string FILEPATH){throw std::runtime_error ("Cannot save - Operation not supported for this cloudType class");}
void CloudComponent::saveProjections(std::string FILEPATH, int objectID){throw std::runtime_error ("Cannot save - Operation not supported for this cloudType class");}
void CloudComponent::setProjectionType(std::shared_ptr<ProjectionType> pTyp){throw std::runtime_error ("Cannot setProjectionType - Operation not supported for this cloudType class");}
void CloudComponent::setSegmentationType(std::shared_ptr<SegmentationType> sTyp){throw std::runtime_error ("Cannot setSegmentationType - Operation not supported for this cloudType class");}
void CloudComponent::setClassificationType(std::shared_ptr<ClassificationType> cTyp){throw std::runtime_error ("Cannot setClassificationType - Operation not supported for this cloudType class");}
void CloudComponent::setBenchmarkType(std::shared_ptr<BenchmarkType> benchamrkType,int objectID){}
void CloudComponent::setBenchmarkType(std::shared_ptr<BenchmarkType> bType){
    this->benchmarkType=bType;
}

CloudComponent* CloudComponent::getCloud(int object_ID){
    return nullptr;
}
std::vector<std::string> CloudComponent::getCloudsNames(){
    throw std::runtime_error ("Cannot getCloudNames() - Operation not supported for this cloudType class");
    return {};
}
std::vector<int> CloudComponent::getCloudsClassIDs(){
    std::cout<<"Cannot getCloudsClassIDs - Operation not supported for this cloudType class"<<std::endl;
    return {};
}
int CloudComponent::getCloudClassID(){
    std::cout<<"Cannot getCloudClassID - Operation not supported for this cloudType class"<<std::endl;
    return -2;
}
std::vector<float> CloudComponent::getNNResopneVector(){return {};}
int CloudComponent::getNumberOfClouds(){
    return 0;
}
std::size_t CloudComponent::getCloudSize(){
    std::cout<<"Cannot getCloudSize() - Operation not supotted for this cloudType class"<<std::endl;
    return 0;
}
std::string CloudComponent::getCloudClassName(){
    if(benchmarkType!=nullptr){
        return this->benchmarkType->mapClass(this->getCloudClassID());
    }else{
        return "No benchmarkType set (class mapping not set)";
    }

}
int CloudComponent::getCloudID(){
    std::cout<<"Cannot getCloudID - Operation not supported for this cloudType class"<<std::endl;
    return -2;
}
std::vector<int> CloudComponent::getCloudsIDs(){
    std::cout<<"Cannot getCloudsIDs() - Operation not supported for this cloudType class"<<std::endl;
    return {};
}
void CloudComponent::saveCloud(std::string FILEPATH){
    std::cout<<"Cannot saveCloud() - operation not suppoerted for this cloudType"<<std::endl;
}
CloudComponent* CloudComponent::getCloud(){
    return this;
}
size_t CloudComponent::getCloudNumberOfPoints(){
    if(this->cloud!=nullptr){
        return this->cloud->size();
    }else{
        return 0;
    }
}
cloudType CloudComponent::getCloudType(){
    return this->type;
}
std::string CloudComponent::getName(){
    return  this->name;
}
std::string CloudComponent::getSourcePath(){
    return this->sourcePath;
}
std::string CloudComponent::getParentSceneName(){
    return this->parentSceneName;
}
std::string CloudComponent::getParentSourcePath(){
    return this->parentSourcePath;
}
void CloudComponent::setParentSourcePath(std::string parentSrcPath){
    this->parentSourcePath=parentSrcPath;
}

void CloudComponent::setController(std::shared_ptr<PointCloudController> ctr){std::cout<<"Could not setController - Operation not supported for this cloudType class"<<std::endl;}
void CloudComponent::updateView(){std::cout<<"Could not updateView - Operation not supported for this cloudType class"<<std::endl;}

void CloudComponent::clearProjections(){}
//////////////////////////////////////////////////////////////

CloudObject::CloudObject(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,int id):CloudComponent(_cloud,"object"){ //->?czyli domyslna nazwa obiektu jest "object"
    this->id=id;
    this->type=type_CloudObject;
} //->? NAUKA - przekazywanie parametrow do konstruktora bazowego
CloudObject::CloudObject(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name):CloudComponent(_cloud,_name){
    //# co z id w przypadku tego konstruktora ?
    this->type=type_CloudObject;
}
CloudObject::CloudObject(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name,std::string src_path):CloudComponent(_cloud,_name,src_path){
    this->type=type_CloudObject;
}
CloudObject::CloudObject(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name,std::string src_path,std::string parName, std::string parSrcPath,int id_,int cls_id,std::vector<float> nnRespVec)
    :CloudComponent(_cloud,_name,src_path,parName,parSrcPath)
{
    this->type=type_CloudObject;
    this->id=id_;
    this->class_id=cls_id;
    this->nnResponseVector=nnRespVec;
}
void CloudObject::setProjectionType(std::shared_ptr<ProjectionType> pTyp){
    this->projectionType=pTyp;
}
void CloudObject::setClassificationType(std::shared_ptr<ClassificationType> cTyp){
    this->classificationType=cTyp;
}
void CloudObject::project(std::shared_ptr<ProjectionType> projTyp) {
    setProjectionType(projTyp);
    if(projectionType!= nullptr){
        std::cout<<"PROJECTING "<<name<<" "<<id<<std::endl;
        projections=projectionType->project(this->cloud);
    } else{
        throw std::runtime_error ("Set projectionType for CloudObject class first!");
    }
}
void CloudObject::edit(std::shared_ptr<EditType> eType){
    if(eType!=nullptr){
        eType->edit(this->projections); //we pass projections by reference so we are editing this class "projections" member
    }
}
void CloudObject::classify(std::shared_ptr<ClassificationType> cTyp,std::string modelDir,int numOfClasses) {
    this->classificationType=cTyp;
    if(classificationType!= nullptr){
        std::cout<<"CLASSIFYING "<<name<<" "<<id<<std::endl;
        //this->class_id=classificationType->classify(this->projections,modelDir,numOfClasses);
        this->nnResponseVector=classificationType->classifyAndGetNNResponeVector(this->projections,modelDir,numOfClasses); //returns vector-> vecotr[0]=classification result=classID, the rest of vector is a NeuralNet response vector
        if(!nnResponseVector.empty()){
            this->class_id=static_cast<int>(nnResponseVector.at(0));
            this->nnResponseVector=std::vector<float>(this->nnResponseVector.cbegin()+1,this->nnResponseVector.cend());
        }

        clearProjections();

        updateView();
    } else{
        throw std::runtime_error ("Set classificationType for CloudObject class first!");
    }
}
void CloudObject::classify(std::shared_ptr<ClassificationType> cTyp,std::shared_ptr<SegmentationType> sTyp,std::shared_ptr<ProjectionType> pTyp,std::shared_ptr<EditType> eTyp, std::string modelDir,int numOfClasses){
    project(pTyp);
    edit(eTyp);
    classify(cTyp,modelDir,numOfClasses);
}
void CloudObject::benchmark(std::shared_ptr<BenchmarkType> bType,std::string FILEPATH){
    std::cout<<"ADDING BENCHMARK LABEL FOR "<<name<<" CLOUD"<<std::endl;
    bType->setFileName(this->parentSceneName);
    bType->setFilePath(FILEPATH);
    this->benchmarkType=bType;
    bType->benchmark(this->cloud,this->class_id);
    updateView();
}
void CloudObject::visualize(std::shared_ptr<VisualizationType> vTyp,pcl::visualization::PCLVisualizer::Ptr viewer){
    vTyp->visualize(this->cloud,this->class_id,this->name,viewer);
}
void CloudObject::visualize(){
    std::cout<<"To be defined"<<std::endl;
    //...
}
void CloudObject::saveCloud(std::string FILEPATH){
    FILEPATH=FILEPATH+"/"+this->name;
    if(!ends_with(this->name,".pcd")){
            FILEPATH=FILEPATH+".pcd";
    }
    std::cout<<"Saving cloud to"<<FILEPATH<<std::endl;
    pcl::io::savePCDFileASCII (FILEPATH, *cloud);
}
void CloudObject::saveClouds(std::string FILEPATH){
    saveCloud(FILEPATH);
}
void CloudObject::saveProjections(std::string FILEPATH){
    for(int i=0; i<projections.size();++i){
        cv::imwrite(FILEPATH+"/"+name+
        /*"_"+std::to_string(id)*/
        /*TU POWIENNO BYC: NUMER ALBO KAT RZUTU W PIONIE I POZIOMIE, TYMCZASOWO DAJE PO PROSTU NUMER RZUTU*/
        this->projectionType->getProjectionNameSuffix(i)+".jpg",projections.at(i));
    }
}
void CloudObject::setName(std::string name){this->name=name;}
void CloudObject::setParentSceneName(std:: string name){this->parentSceneName=name;}
std::vector<std::string> CloudObject::getCloudsNames(){
    return {};
}
int CloudObject::getCloudClassID(){
    return this->class_id;
}
int CloudObject::getCloudID(){
    return this->id;
}
/**
 * @brief CloudObject::getNNResopneVector
 * @return response vector of neural net (without id of max response = class_id)
 */
std::vector<float> CloudObject::getNNResopneVector(){
    if(this->nnResponseVector.size()>=1){
        return this->nnResponseVector;
    }else{
        return {};
    }
}
std::size_t CloudObject::getCloudSize(){
    return sizeof(pcl::PointXYZ)*this->cloud->size();
}

void CloudObject::setController(std::shared_ptr<PointCloudController> ctr){
    this->controller=ctr;
}
void CloudObject::updateView(){
    if(this->controller!=nullptr){
        this->controller->updateView(this); //albo this->controller->updateView(this), ktore z kolei updateuje np. treeWidgetItem
    }else{
        std::cout<<"Could not update view for CloudObject - set controller in model (CloudComponent in pointCloud.h)"<<std::endl;
    }
}

void CloudObject::clearProjections(){
    this->projections.clear();
}
/////////////////////////////////////////////////////////////////////////////////////////
CloudScene::CloudScene(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,std::string _name): CloudComponent(cloud,_name){
    this->type=type_CloudScene;
}
CloudScene::CloudScene(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,std::string _name,std::string src_path): CloudComponent(cloud,_name,src_path){
    this->type=type_CloudScene;
}
CloudScene::CloudScene(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,std::string _name,std::string src_path,std::string parName, std::string parSrcPath)
    :CloudComponent(cloud,_name,src_path,parName,parSrcPath)
{
    this->type=type_CloudScene;
}
void CloudScene::addCloud(std::unique_ptr<CloudComponent> cc/*CloudComponent *cc*/) {
    clouds.push_back(std::move(cc));
}
void CloudScene::addClouds(std::vector<std::unique_ptr<CloudComponent>> vec) {
    for(int i=0; i<vec.size();++i){
        clouds.push_back(std::move(vec.at(i)));
    }
}
void CloudScene::addClouds(std::vector<std::unique_ptr<CloudObject>> vec) { //->? musialem dac const bo inaczej "cannot bind non-const lvalue reference of type ‘std::vector<std::shared_ptr<CloudObject> >&’ to an rvalue of type ‘std::vector<std::shared_ptr<CloudObject> >’
                                                                                    // addClouds(obFactory->create(segmentationType->segment(this->cloud),this->cloud));"
                                                                  //wynika to pewnie z tego, ze ten vector uzyskany z obCreate jest tymczasowy i nie powinienem go edytowac ?
    for(int i=0; i<vec.size();++i){
        clouds.push_back(std::move(vec.at(i)));
    }
}

/*
std::vector<std::unique_ptr<CloudComponent>>* CloudScene::getClouds(){
    return &this->clouds;
}
*/
void CloudScene::removeCloud(int object_ID) {
    int index=0;
    for(auto &cloud:clouds){
        if(cloud->getCloudID()==object_ID){
            clouds.erase(clouds.begin()+index);
            std::cout<<"Removed object with ID "<<object_ID<<std::endl;
            break;
        }
        ++index;
    }
}
void CloudScene::setFactory(std::shared_ptr<CloudObjectFactory> fc){
    this->obFactory=fc;
}
void CloudScene::setSegmentationType(std::shared_ptr<SegmentationType> sTyp){
    this->segmentationType=sTyp;
}
void CloudScene::segment(std::shared_ptr<SegmentationType> segmentationType) {
    if(obFactory!= nullptr){
        std::cout<<"SEGMETING "<<name<<" scene"<<std::endl;
        clouds.clear(); //we have to clear this vector otherwise when segmenting same scene n times we would get new cloud.size()=n*primary clouds.size()
        //# czy to na pewno oznacza, ze usunolem tez obiekty CloudObject zawarte w Clouds? -> moze lepiej zastosowac do CloudObject tez unique_ptr ?
        this->setSegmentationType(segmentationType);
        ///addClouds(obFactory->create(segmentationType->segment(this->cloud),this->cloud)); //segment-> get clusterIndices->create from them CloudObjects-> add those objects to the clouds vector
        //this->doncloud=(this->segmentationType->getDonCloud());
        if(this->controller==nullptr){
            addClouds(obFactory->create(segmentationType->segment(this->cloud),this->name,this->sourcePath));
        }else{
            addClouds(obFactory->create(segmentationType->segment(this->cloud),this->controller,this->name,this->sourcePath));
        }

    }
    else
        throw std::runtime_error ("Set factory for creating objects first");
}
void CloudScene::project(std::shared_ptr<ProjectionType> projectionType){
    for(int i=0; i<clouds.size();++i){
        //clouds.at(i)->setProjectionType(projectionType); //->?UWAGA, tu zeby korzystac jak w CompositePattern (rekursywnie dla scen i obiektow), to deklaracje funkcji project(...) itd. powunny byc takie same w CloudScene i CloudObject
        clouds.at(i)->project(projectionType);
    }
}
void CloudScene::project(std::shared_ptr<ProjectionType> projectionType,int object_id){
    bool projected=false;
    for(auto &cloud:clouds){
        if(cloud->getCloudID()==object_id){
            cloud->project(projectionType);
            projected=true;
            break;
        }
    }

    if(projected==false){
        std::cout<<"Could not project cloud with ID = "<<object_id<<" -> cloud not found"<<std::endl;
    }
}
void CloudScene::edit(std::shared_ptr<EditType> eType){
    std::cout<<"EDITING "<<std::endl;
    for(int i=0; i<clouds.size();++i){
        clouds.at(i)->edit(eType);
    }
}
void CloudScene::edit(std::shared_ptr<EditType> eType, int object_id){
    std::cout<<"EDITING "<<object_id<<" OBJECT PROJECTIONS"<<std::endl;
    bool edited=false;
    for(auto &cloud:clouds){
        if(cloud->getCloudID()==object_id){
            cloud->edit(eType);
            edited=true;
            break;
        }
    }

    if(edited==false){
        std::cout<<"Could not edit projections of cloud with ID = "<<object_id<<" -> cloud not found"<<std::endl;
    }
}
void CloudScene::classify(std::shared_ptr<ClassificationType> cTyp, std::string modelDir,int numOfClasses) {
    ///init_ar(); //PYTHON EMBEDDING INITIALIZATION
    for(int i=0; i<clouds.size();++i){
        //clouds.at(i)->setClassificationType(cTyp);
        clouds.at(i)->classify(cTyp,modelDir,numOfClasses);
    }
    ///Py_Finalize();//PYTHON EMBEDDING FINALIZATION
}
//Use this function for classifing big scenes ->saves memory-> it keeeps only one projections vector (in CloudObject class) at once (we classyfing one object, clear projections vector and so on)
void CloudScene::classify(std::shared_ptr<ClassificationType> cTyp,std::shared_ptr<SegmentationType> sTyp,std::shared_ptr<ProjectionType> pTyp,std::shared_ptr<EditType> eTyp, std::string modelDir,int numOfClasses){
    segment(sTyp);//# INFO -> to ozacza, ze jak usniemy jakies chmury nalezace do sceny (np. po segmentacji), to po wywolaniu tej funkcji znowu bedziemy klasyfikowac wszystkie obiekty (a nie tylko te co zostaly)
    for(auto &cloud:clouds){
        cloud->segment(sTyp);
        cloud->project(pTyp);
        if(eTyp!=nullptr){
            cloud->edit(eTyp);
        }
        cloud->classify(cTyp,modelDir,numOfClasses);
    }
}
void CloudScene::classify(std::shared_ptr<ClassificationType> cTyp, std::string modelDir,int numOfClasses,int object_id){
    std::cout<<"CLASSIFINIG "<<object_id<<" OBJECT IN"<<this->name<<" SCENE"<<std::endl;
    bool classified=false;
    for(auto &cloud:clouds){
        if(cloud->getCloudID()==object_id){
            cloud->classify(cTyp,modelDir,numOfClasses);
            classified=true;
            break;
        }
    }

    if(classified==false){
        std::cout<<"Could not classify cloud with ID = "<<object_id<<" -> cloud not found"<<std::endl;
    }
}
void CloudScene::benchmark(std::shared_ptr<BenchmarkType> bType,std::string FILEPATH){
    std::cout<<"BENCHMARKING"<<std::endl;
    this->benchmarkType=bType;
    for(int i=0; i<clouds.size();++i){
        clouds.at(i)->benchmark(bType,FILEPATH);
    }
}
void CloudScene::benchmark(std::shared_ptr<BenchmarkType> bType,std::string FILEPATH,int object_id){
    std::cout<<"BENCHMARKING "<<object_id<<" OBJECT IN"<<this->name<<" SCENE"<<std::endl;
    this->benchmarkType=bType; //# moze tutaj nie powinienem ustawiac benchmarkType dla rodzica ?
    for(auto &cloud:clouds){
        if(cloud->getCloudID()==object_id){
            cloud->benchmark(bType,FILEPATH);
            break;
        }
    }
}
void CloudScene::visualize(std::shared_ptr<VisualizationType> vTyp,pcl::visualization::PCLVisualizer::Ptr viewer){
    std::cout<<"VISUALIZING "<<this->name<<" SCENE"<<std::endl;
    //viewer->reset(new pcl::visualization::PCLVisualizer(this->name,false));//# UWAGA w QT MUSI BYC FALSE :http://www.pointclouds.org/documentation/tutorials/qt_visualizer.php
    viewer->setWindowName(this->name);
    vTyp->visualize(this->cloud,-1,this->name,viewer); // passing -1, as class id (visualizing unclassifed scene)
}
void CloudScene::visualize(std::shared_ptr<VisualizationType> vTyp){
    std::cout<<"VISUALIZING OBJECTS IN "<<this->name<<" SCENE"<<std::endl;
    pcl::visualization::PCLVisualizer::Ptr viewer (new pcl::visualization::PCLVisualizer (this->name));
    for(int i=0; i<clouds.size();++i){
        clouds.at(i)->visualize(vTyp,viewer);
    }
    while (!viewer->wasStopped())
    {
        viewer->spinOnce (100);
    }
}
void CloudScene::visualizeAllChildren(std::shared_ptr<VisualizationType> vTyp,pcl::visualization::PCLVisualizer::Ptr viewer){
    std::cout<<"VISUALIZING OBJECTS IN "<<this->name<<" SCENE"<<std::endl;
    for(int i=0; i<clouds.size();++i){
        clouds.at(i)->visualize(vTyp,viewer);
    }
}
void CloudScene::visualize(std::shared_ptr<VisualizationType> vTyp,int object_id, pcl::visualization::PCLVisualizer::Ptr viewer){
    std::cout<<"VISUALIZING OBJECT IN "<<this->name<<" SCENE, WITH "<<object_id<<" ID"<<std::endl;
    for(auto &cloud:clouds){
        if(cloud->getCloudID()==object_id){
            cloud->visualize(vTyp,viewer);
            break;
        }
    }
}
void CloudScene::saveCloud(std::string FILEPATH){
    std::cout<<"Saving "<<FILEPATH+"/"+name<<" cloud scene"<<std::endl;
    pcl::io::savePCDFileASCII (FILEPATH+"/"+name, *cloud);
}
void CloudScene::saveClouds(std::string FILEPATH){ //->? zapisuje wszystkie obiekty (nie sceny) dodaj jeszcze ewentualnie funkcje do zapisu scene oraz zapisu konkretnych scen i obiektow
    for(int i=0; i<clouds.size();++i){
        clouds.at(i)->saveClouds(FILEPATH);
    }
}
void CloudScene::saveClouds(std::string FILEPATH, int object_ID){
    bool saved=false;
    for(auto &cloud:clouds){
        if(cloud->getCloudID()==object_ID){
            cloud->saveClouds(FILEPATH);
            saved=true;
            break;
        }
    }

    if(saved==false){
        std::cout<<"Could not save cloud with ID = "<<object_ID<<" -> cloud not found"<<std::endl;
    }
}

void CloudScene::saveProjections(std::string FILEPATH){
    std::cout<<"SAVING PROJECTIONS"<<std::endl;
    for(int i=0; i<clouds.size();++i){
        clouds.at(i)->saveProjections(FILEPATH);
    }
}
void CloudScene::saveProjections(std::string FILEPATH,int id){
    std::cout<<"SAVING PROJECTIONS of object with "<<id<<" id"<<std::endl;
    bool saved=false;
    for(auto &cloud:clouds){
        if(cloud->getCloudID()==id){
            cloud->saveProjections(FILEPATH);
            saved=true;
            break;
        }
    }

    if(saved==false){
        std::cout<<"CANNOT SAVE PROJECTIONS - cloud with"<<id<<" -> cloud not found"<<std::endl;
    }
}
//# UWAGA tu zwracam zwykly wskaznik pobrany z unique_ptr:
//# ale to nieszkodzi, bo uniqe_ptr dalej zarzadza tym obiektem (usuwaniem)->dlatego lepiej nie USUWAC OBIEKTU ZWROCONEGO PRZEZ TA FUNKCJE (delete CloudComponent*) (i tak nie ma potrzeby tego robic)
//# Notice that a call to this function does not make unique_ptr release ownership of the pointer (i.e., it is still responsible for deleting the managed data at some point). Therefore, the value returned by this function shall not be used to construct a new managed pointer.
CloudComponent* CloudScene::getCloud(int object_ID){
    int index=0;
    for(auto &cloud:clouds){
        if(cloud->getCloudID()==object_ID){
            return clouds.at(index).get();
        }
        ++index;
    }

    std::cout<<"No cloud with ID "<<object_ID<<" was found"<<endl;
    return nullptr;
}
std::vector<std::string> CloudScene::getCloudsNames(){
    std::vector<std::string> cloudNames;
    for (int i=0; i<clouds.size();++i){
        cloudNames.push_back(clouds.at(i)->getName());
    }
    return cloudNames;
}

std::vector<int> CloudScene::getCloudsClassIDs(){
    std::vector<int> cloudsIDs;
    for (int i=0; i<clouds.size();++i){
        cloudsIDs.push_back(clouds.at(i)->getCloudClassID());
    }
    return cloudsIDs;
}
std::vector<int> CloudScene::getCloudsIDs(){
    std::vector<int> cloudsIDs;
    for (int i=0; i<clouds.size();++i){
        cloudsIDs.push_back(clouds.at(i)->getCloudID());
    }
    return cloudsIDs;
}
int CloudScene::getNumberOfClouds(){
    return clouds.size();
}
std::size_t CloudScene::getCloudSize(){
    std::size_t total_size=sizeof(pcl::PointXYZ)*this->cloud->size(); //additionaly to vector of clouds, CloudComponent stores original cloud so we also have to take into account its size
    for(auto &cloud:clouds){
        total_size=total_size+cloud->getCloudSize();
    }
    return total_size;
}
void CloudScene::setController(std::shared_ptr<PointCloudController> ctr){
    this->controller=ctr;
    std::cout<<"SET CONTROLLER FOR SCENE"<<endl;
    for(auto &cloud:clouds){
        cloud->setController(ctr);
    }
}
void CloudScene::setBenchmarkType(std::shared_ptr<BenchmarkType> benchamrkType,int objectID){
    bool set=false;
    for(auto &cloud:clouds){
        if(cloud->getCloudID()==objectID){
            cloud->setBenchmarkType(benchmarkType);
            set=true;
            break;
        }
    }

    if(set==false){
        std::cout<<"Could not set benchmark type for cloud with ID = "<<objectID<<" -> cloud not found"<<std::endl;
    }
}
void CloudScene::updateView(){
    if(this->controller!=nullptr){
        this->controller->updateView(this);
        for(auto &cloud:clouds){
            cloud->updateView();
        }
    }else{
        std::cout<<"Could not update view for CloudScene - set controller in model (CloudComponent in pointCloud.h)"<<std::endl;
    }

}

void CloudScene::clearProjections(){
    for(auto &cloud:clouds){
        cloud->clearProjections();
    }
}
