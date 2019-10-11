#include "src/view/saveLoad.h"

SaveLoad::SaveLoad()
{
    setSeparator(";");
}
void SaveLoad::setFactories(std::shared_ptr<CloudSceneFactory> scnFac,std::shared_ptr<CloudObjectFactory> objFac){
    this->sceneFactory=scnFac;
    this->objectFactory=objFac;
}
bool SaveLoad::saveTXT(QString path,const std::vector<std::string> saveVector){
    QFile file(path+"/saved.txt");
    if (file.open(QIODevice::WriteOnly| QIODevice::Truncate)) {
        QTextStream stream(&file);
        for(auto &line:saveVector){
            stream <<QString(line.c_str())<<endl;
        }
        file.close();
        qDebug()<<"TXT WITH CLOUD INFO SAVED";
        return true;
    }else {
        qDebug()<<"COULD NOT OPEN "<<path<<" for WRITNING data with CLOUD INFO";
        return false;
    }
}
/**
 * @brief SaveLoad::saveSingleCloud
 * Saves one cloud + creates single line with cloud info (name, sourcePath,class id and so on) and returnes it so it can be saved to file
 * @param cloud
 * @param saveFolderPath
 * @param saveParentScenes
 * @return one line to be saved to file with cloud info
 */
std::string SaveLoad::saveSingleCloud(CloudComponent *cloud,QString saveFolderPath,bool saveParentScenes,std::shared_ptr<SaveConditions> saveCond){
    std::stringstream line("");

    std::string FILEPATH, newParentFILEPATH;

    //children (created for. ex during segmentation) and saved parent scnenes have set sourcePath like this:
    if(ends_with(cloud->getName(),".pcd")){
        FILEPATH=saveFolderPath.toStdString()+"/"+cloud->getName();
    }else{
        FILEPATH=saveFolderPath.toStdString()+"/"+cloud->getName()+".pcd";

    }
    if(cloud->getParentSourcePath()!=""){
        if(ends_with(cloud->getParentSceneName(),".pcd")){
            newParentFILEPATH=saveFolderPath.toStdString()+"/"+cloud->getParentSceneName();
        }else{
            newParentFILEPATH=saveFolderPath.toStdString()+"/"+cloud->getParentSceneName()+".pcd";
        }
    }else {
        newParentFILEPATH=cloud->getParentSourcePath();
    }

    if(saveParentScenes){
        if(cloud->getCloudType()==type_CloudObject){
            //evaluation of CONDITIONS TO SAVE CLOUD  - WE DO IT ONLY FOR OBJECTS
            if(saveCond->getNumberOfConditions()>0){
                if(saveCond->evaluateConditions(cloud)){
                    cloud->saveCloud(saveFolderPath.toStdString());

                    line<<cloud->getCloudType()<<separator<<cloud->getName()<<separator<<FILEPATH<<separator<<cloud->getParentSceneName()<<separator
                    <</*parent source path is now in saveFolderPath*/newParentFILEPATH
                    <<separator<<cloud->getCloudID()<<separator<<cloud->getCloudClassID()<<separator<<vectorToString(cloud->getNNResopneVector(),vectorSeparator);
                }
            }else{
                cloud->saveCloud(saveFolderPath.toStdString());

                line<<cloud->getCloudType()<<separator<<cloud->getName()<<separator<<FILEPATH<<separator<<cloud->getParentSceneName()<<separator
                <</*parent source path is now in saveFolderPath*/newParentFILEPATH
                <<separator<<cloud->getCloudID()<<separator<<cloud->getCloudClassID()<<separator<<vectorToString(cloud->getNNResopneVector(),vectorSeparator);
            }


        }else if(cloud->getCloudType()==type_CloudScene){
            cloud->saveCloud(saveFolderPath.toStdString());

            line<<cloud->getCloudType()<<separator<<cloud->getName()<<separator<<FILEPATH<<separator<<cloud->getParentSceneName()<<separator<<cloud->getParentSourcePath()
                <<separator<<cloud->getCloudID()
               <<separator<<cloud->getCloudClassID()
              <<separator
             <<vectorToString(cloud->getNNResopneVector(),vectorSeparator);
        }
    }else{
        if(cloud->getCloudType()==type_CloudObject){
            //evaluation of CONDITIONS TO SAVE CLOUD  - WE DO IT ONLY FOR OBJECTS
            if(saveCond->getNumberOfConditions()>0){
                if(saveCond->evaluateConditions(cloud)){
                    cloud->saveCloud(saveFolderPath.toStdString());

                    line<<cloud->getCloudType()<<separator<<cloud->getName()<<separator<<FILEPATH<<separator<<cloud->getParentSceneName()<<separator<<cloud->getParentSourcePath()
                       <<separator<<cloud->getCloudID()<<separator<<cloud->getCloudClassID()<<separator<<vectorToString(cloud->getNNResopneVector(),vectorSeparator);
                }
            }else{
                cloud->saveCloud(saveFolderPath.toStdString());

                line<<cloud->getCloudType()<<separator<<cloud->getName()<<separator<<FILEPATH<<separator<<cloud->getParentSceneName()<<separator<<cloud->getParentSourcePath()
                   <<separator<<cloud->getCloudID()<<separator<<cloud->getCloudClassID()<<separator<<vectorToString(cloud->getNNResopneVector(),vectorSeparator);
            }



        }else if(cloud->getCloudType()==type_CloudScene){
            line<<cloud->getCloudType()<<separator<<cloud->getName()<<separator<<cloud->getSourcePath()<<separator<<cloud->getParentSceneName()<<separator<<cloud->getParentSourcePath()
                <<separator<<cloud->getCloudID()<<separator<<cloud->getCloudClassID()<<separator<<vectorToString(cloud->getNNResopneVector(),vectorSeparator);
        }
    }

    return line.str();
}
/**
 * @brief SaveLoad::save
 * @param cloudConrtainer
 * @param indexesToSave -indexesToSave[i][j] = index of j'th child of i'th topLevelCloud (topLevel - in cloudContainer)
 *                                             if indexesToSave[i].at(0)==-std::numeric_limits::max -> topLevelCloud or its children were not selected
 * @return
 */
bool SaveLoad::save(QString saveFolderPath,const std::vector<std::unique_ptr<CloudComponent> > &cloudConrtainer, const std::vector<std::vector<int> > &indexesToSave,std::shared_ptr<SaveConditions> saveCond){
    int i=-1;
    int j=0;
    bool cloudWasSelected=false;
    std::vector<std::string> saveVector;
    std::string line;
    CloudComponent* cloud;
    for(auto topLevelIndex:indexesToSave){
        ++i;
        cloudWasSelected=false;
        //if we selected Top level cloud at ith place (otherwise topLevelIndex.at(notSelectedCloud)={-std::numeric_limits<int>::max()}
        if(!topLevelIndex.empty()){
            if(topLevelIndex.at(0)!=-std::numeric_limits<int>::max()){
                cloudWasSelected=true;
            }else{
                cloudWasSelected=false;
            }
        }else{
            cloudWasSelected=true;
        }

        if(cloudWasSelected){
            line="";//CLEAR LINE
            //save or not TopLevel Cloud (top parent)
            cloud=cloudConrtainer.at(i)->getCloud();
            if(cloud!=nullptr){
                line=saveSingleCloud(cloud,saveFolderPath,saveCond->getSaveParentScene(),saveCond);
            }
            if(line!=""){saveVector.push_back(line);}
            //save children
            for(auto childIndex:topLevelIndex){
                line="";
                cloud=cloudConrtainer.at(i)->getCloud(childIndex);
                if(cloud!=nullptr){ 
                    line=saveSingleCloud(cloud,saveFolderPath,saveCond->getSaveParentScene(),saveCond);
                    if(line!=""){saveVector.push_back(line);}
                }
            }
            saveVector.push_back("#");//SYMBOL SEPRERATING TopLevelClouds
        }else{
            continue;
        }
    }
    return saveTXT(saveFolderPath,saveVector);
}
bool SaveLoad::load(QString path,std::vector<std::unique_ptr<CloudComponent> > &cloudConrtainer, std::shared_ptr<PointCloudController> controller,std::shared_ptr<CloudObjectFactory> objectFactory){
    cloudType type;
    std::map<std::string, cloudType> cloudTypeMap {
        {"0", type_CloudScene},
        {"1", type_CloudObject},
        {"type_CloudScene", type_CloudScene},
        {"type_CloudObject", type_CloudObject},
      };
    std::string name;
    std::string sourcePath;
    std::string parentSceneName;
    std::string parentSourcePath;
    int class_id=-1;
    int id=-1;
    std::vector<float> nnResponseVector={};

    QFile file(path);
    QString data="";
    QStringList singleLineWords={};


    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        std::unique_ptr<CloudComponent> parent=nullptr;
        std::unique_ptr<CloudComponent> child=nullptr;

        //We are using searching by name so in case of change made in vector of widgets types we want to save, added new widgets to application and so on
        //it takes more time but it assures that configurations are always compatible and can be always loaded (as long as there are widgets (with names form configuration) in application)
        while(!stream.atEnd()){
            data=stream.readLine();
            if(data=="#"){
                if(parent!=nullptr){
                    //add previous parent filled with children
                    cloudConrtainer.push_back(std::move(parent));
                }
                continue;
            }

            singleLineWords=data.split(QString(separator.c_str()));
            try {
                type=cloudTypeMap.at(QVariant(singleLineWords.at(0)).toString().toStdString());
            } catch (std::out_of_range ) {
                qDebug()<<"Could not read cloud type !";
                return false;
            }
            try{
                name=QVariant(singleLineWords.at(1)).toString().toStdString();
                sourcePath=QVariant(singleLineWords.at(2)).toString().toStdString();
                parentSceneName=QVariant(singleLineWords.at(3)).toString().toStdString();
                parentSourcePath=QVariant(singleLineWords.at(4)).toString().toStdString();
                id=QVariant(singleLineWords.at(5)).toInt();
                class_id=QVariant(singleLineWords.at(6)).toInt();
                nnResponseVector=stringToFloatVector(singleLineWords.at(7),QString(vectorSeparator.c_str()));
            }catch (std::out_of_range ){
                qDebug()<<"cannot acces singleLineWords.at(x) - out_of_range";
                return false;
            }

            if(parentSourcePath==""){
                if(type==type_CloudScene){
                    parent=sceneFactory->create(sourcePath,controller);
                    parent->setFactory(objectFactory); //set factory for creating objets (for. ex. after segmentation) used in controller
                }else if(type==type_CloudObject){
                    parent=objectFactory->create(sourcePath,controller,sourcePath,parentSceneName,parentSourcePath
                                                 ,id,class_id,nnResponseVector);
                }else{
                    qDebug()<<"Cannot load cloud"<<sourcePath.c_str()<<" - no such  cloud_type";
                    continue;
                }

            }else if(parent!=nullptr){
                if(parentSourcePath==parent->getSourcePath()){
                    if(type==type_CloudScene){
                        child=sceneFactory->create(sourcePath,controller);
                        parent->setFactory(objectFactory); //set factory for creating objets (for. ex. after segmentation) used in controller
                    }else if(type==type_CloudObject){
                        child=objectFactory->create(sourcePath,controller,sourcePath,parentSceneName,parentSourcePath
                                                    ,id,class_id,nnResponseVector);
                    }else{
                        qDebug()<<"Cannot load cloud"<<sourcePath.c_str()<<" - no such  cloud_type";
                        continue;
                    }
                    if(parent!=nullptr && child!=nullptr){
                        parent->addCloud(std::move(child));
                    }
            }
            }else{
                qDebug()<<"Problem with parentSourcePath";
                qDebug()<<"parentSourcePath (txt)="<<parentSourcePath.c_str();
                continue;
            }
            /*
            qDebug()<<"type="<<type;
            qDebug()<<"name="<<name.c_str();
            qDebug()<<"sourcePath="<<sourcePath.c_str();
            qDebug()<<"parentSceneName="<<parentSceneName.c_str();
            qDebug()<<"parentSourcePath="<<parentSourcePath.c_str();
            qDebug()<<"id="<<id;
            qDebug()<<"class_id="<<class_id;
            */
        }

        file.close();
        qDebug()<<"CLOUD/S LOADED";
        return true;
    }else{
        qDebug()<<"COULD NOT OPEN "<<path<<" for READING data.";
        return false;
    }
}
std::vector<float> SaveLoad::stringToFloatVector(const QString &stringVector,const QString separator){
    std::vector<float> fVec={};
    QStringList strVec={};
    strVec=stringVector.split(separator);
    for(auto element:strVec){
        fVec.push_back((element.toFloat()));
    }
    return fVec;
}
//# funckja do testow
void SaveLoad::setSeparator(std::string separator){
    this->separator=separator;
}

/////////////////////////////////////////
SaveConditions::SaveConditions(){
    /*
    //std::function<bool(CloudComponent*)> testFunc(std::bind(&SaveConditions::isAmongClasses, this, std::placeholders::_1));
    //# addCondition(isAmongClasses); //# w tym przypadku funkcja isAmongClasses powinna byc static (ale wtedy nie mialbym w niej dostepu do czlonkow klasy SaveConditions)
    addCondition(std::bind(&SaveConditions::isAmongClasses, this, std::placeholders::_1));//https://stackoverflow.com/questions/10022789/stdfunction-with-non-static-member-functions
    addCondition(std::bind(&SaveConditions::hasNnResponseStrengthBiggerEqualThan, this, std::placeholders::_1));
    addCondition(std::bind(&SaveConditions::hasNumOfPointsBiggerEqualThan, this, std::placeholders::_1));
    */
}
void SaveConditions::addCondition(std::function<bool(CloudComponent*)> condition){
    this->cloudConditions.push_back(condition);
}
/**
 * @brief SaveConditions::evaluateConditions
 * returns binary PRODUCT of all conditions
 * @param cloud
 * @return
 */
bool SaveConditions::evaluateConditions(CloudComponent* cloud){
    bool result=true;
    for(auto condition:cloudConditions){
       result=result*condition(cloud);
    }
    return result;
}
size_t SaveConditions::getNumberOfConditions(){
    return this->cloudConditions.size();
}
void SaveConditions::setSaveParentScene(bool save){
    this->saveParentScene=save;
}
bool SaveConditions::getSaveParentScene(){
    return this->saveParentScene;
}
