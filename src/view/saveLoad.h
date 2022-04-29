#pragma once //without this line this problem appears: https://bugreports.qt.io/browse/QTCREATORBUG-20883
#ifndef SAVELOAD_H
#define SAVELOAD_H
class CloudComponent;
#include "model/pointCloud.h"
#include "helperFunctions.h"
#include <limits>
#include <functional>//std::bind
class SaveConditions;

class SaveLoad
{
private:
    std::shared_ptr<CloudSceneFactory> sceneFactory;
    std::shared_ptr<CloudObjectFactory> objectFactory;

    std::string separator="\0"; //NULL character -> not allowed in path in unix and windows
    std::string vectorSeparator="_";
    bool saveTXT(QString path,const std::vector<std::string> saveVector);
    std::string saveSingleCloud(CloudComponent *cloud,QString saveFolderPath,bool saveParentScenes,std::shared_ptr<SaveConditions> saveCond);
    std::vector<float> stringToFloatVector(const QString &stringVector,const QString separator);
    //# funkcja tylko do testow
    void setSeparator(std::string separator);
public:
    SaveLoad();
    void setFactories(std::shared_ptr<CloudSceneFactory> scnFac,std::shared_ptr<CloudObjectFactory> objFac);
    void setSaveConditions(std::unique_ptr<SaveConditions> saveCond);
    bool save(QString saveFolderPath, const std::vector<std::unique_ptr<CloudComponent>> &cloudConrtainer, const std::vector<std::vector<int> > &indexesToSave,std::shared_ptr<SaveConditions> saveCond=nullptr);
    bool load(QString path,std::vector<std::unique_ptr<CloudComponent> > &cloudConrtainer, std::shared_ptr<PointCloudController> controller,std::shared_ptr<CloudObjectFactory> objectFactory);
};

class SaveConditions{
private:
    std::vector<std::function<bool(CloudComponent*)>> cloudConditions;
    //SaveSettings* saveSettings;
    std::vector<int> classesIDs;
    float minNnResponseStrength;
    uint minNumOfPoints;
    bool saveParentScene=false;
public:
    SaveConditions();
    void addCondition(std::function<bool(CloudComponent*)>);
    bool evaluateConditions(CloudComponent* cloud);
    size_t getNumberOfConditions();
    void setSaveParentScene(bool save);
    bool getSaveParentScene();

    //condition functions
};

#endif // SAVELOAD_H
