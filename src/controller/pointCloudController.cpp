#include "controller/pointCloudController.h"


PointCloudController::PointCloudController()
{
    boundingBox= std::make_shared<AxisAlignedBoudningBox>();
    visualization= std::make_shared<VisualizationWithBB>(boundingBox);
    objectFactory= std::make_shared<CloudObjectFactory>();
    sceneFactory=std::make_shared<CloudSceneFactory>();
    saveLoad = std::make_shared<SaveLoad>();
    saveLoad->setFactories(this->sceneFactory,this->objectFactory);
}
void PointCloudController::registerQTreeWidgetObserver(QTreeWidget *treeWiOb){
    this->treeWidgetObserver=treeWiOb;
}
void PointCloudController::registerQVTKidgetObserver(QVTKWidget *qVTKWiOb){
    this->qVTKWidgetObserver=qVTKWiOb;
}
void PointCloudController::registerPCLViewerObserver(pcl::visualization::PCLVisualizer::Ptr viewOb){
    this->viewerObserver=viewOb;
}
QTreeWidgetItem* PointCloudController::getTopLevelItem(QTreeWidgetItem* item){
    while(item->parent()!=nullptr){
        item=item->parent();
    }
    return item;
}
/**
 * @brief CloudScenesObservable::getTopLevelIndexOfSelectedCloud
 * @param cloudPath
 * @return Index of selected cloud in treeWidget or of parent (top level) of selected cloud (if selected cloud is not in a top level item in a tree widget -> cloud is an object after segmentation)
 */
int PointCloudController::getTopLevelIndexOfSelectedCloud(QTreeWidgetItem* item){
    item=getTopLevelItem(item);
    //index=this->treeWidgetObserver->indexOfTopLevelItem(item); //# tego nie moge uzywac, bo powinieme zwrocic index w vektorze cachedClouds, a nie w hierarchi treeWidget
    //qDebug()<<"INDEX RETURNED FORM QTreeWidget::indexOfTopLevelItem(item)="<<index;
    for(int i=0; i<cachedClouds.size();++i){
        if(cachedClouds.at(i)->getSourcePath()==item->text(0).toStdString())
            return i;
    }
    //we didnt found cloudScene witch such sourcePath
    return -1;
}
QTreeWidgetItem* PointCloudController::getChildItemWithID(QTreeWidgetItem* parent,int id){
    //# TA FUNKCJA NIE DZIALA -> zwraca np. rodzica zamiast dziecko o danym id
    QTreeWidgetItemIterator it(parent);
    while(*it){
        //# qDebug()<<"CHILD DATA-id is null?="<<(*it)->data(0, Qt::UserRole).isNull();
        //# qDebug()<<"CHILD DATA-id="<<(*it)->data(0, Qt::UserRole).toInt();
        //iterate over parent children that have given id
        if(!(*it)->data(0, Qt::UserRole).isNull() && (*it)->parent()==parent && (*it)->data(0, Qt::UserRole).toInt()==id){
            return *it;
        }
        ++it;
    }
    return nullptr;
}
void PointCloudController::clearViewer(pcl::visualization::PCLVisualizer::Ptr viewer){
    viewer->removeAllPointClouds();
    viewer->removeAllShapes();
}
void PointCloudController::clearTreeWidgetTreeChildren(){
    QTreeWidgetItemIterator it(this->treeWidgetObserver,QTreeWidgetItemIterator::HasChildren); //iterate only over items that have children
      while (*it) {
          //we only clear objects on the top level
          if((*it)->parent()!=nullptr)
          {
              qDebug()<<"CHILDREN SKIPPING";
              continue;
          }
          (*it)->takeChildren();
          ++it;
      }
}
std::size_t PointCloudController::getMemoryUsageOfCachedClouds(){
    std::size_t total_size=0;
    for(auto const &cloud:cachedClouds){
        //updateTreeWidgetItem(cloud->getSourcePath(),cloud->getCloudsNames());
        total_size=total_size+cloud->getCloudSize();
    }
    return total_size;
}
void PointCloudController::setCachedCloudsMemoryLimit(std::size_t limit){
    this->cachedCloudsMemoryLimit=limit;
}
/**
 * @brief PointCloudController::updateView
 * updates whole view
 */
void PointCloudController::updateView(){
    clearTreeWidgetTreeChildren();
    for(auto const &cloud:cachedClouds){
        //updateTreeWidgetItem(cloud->getSourcePath(),cloud->getCloudsNames());
        cloud->updateView();
    }
    qDebug()<<"TOTAL MEMORY USAGE BY CLOUDS[MB]="<<static_cast<float>(getMemoryUsageOfCachedClouds())/static_cast<float>(1000000);
}
/**
 * @brief PointCloudController::updateView
 * @param cloud
 * Updates only one item in view that referes to particular cloud
 */
void PointCloudController::updateView(CloudComponent *cloud){
    updateTreeWidgetItem(cloud);
}
/**
 * @brief PointCloudController::updateView
 * @param cloud
 * Updates only one selected item in view
 */
void PointCloudController::updateView(QTreeWidgetItem* item){
    int topLevelCloudIndex;
    std::string cloudPath="";
    topLevelCloudIndex=getTopLevelIndexOfSelectedCloud(item);
    //item=getTopLevelItem(item);
    //cloudPath=item->text(0).toStdString();

    //# UWAGA - tu przekazuje raw ptr (pobrany z unique_ptr  -> ptr.get()), bo taki akceptuje ponizsza funkcja- powinienem tak robic tylko
    //# wtedy, gdy jestem pewny ze obiekt wskazywany przez unique_ptr bedzie caly czas istnial w trakcie wykonywania ponizszej funkcji :https://stackoverflow.com/questions/30905487/how-can-i-pass-stdunique-ptr-into-a-function
    try {
        updateTreeWidgetItem(this->cachedClouds.at(topLevelCloudIndex).get());
    } catch (const std::out_of_range& e) {
        qDebug()<<"Cannot update view - Worng topLevelCloudIndex ="<<topLevelCloudIndex<<" . chachedClouds.size()="<<cachedClouds.size();
    }

    //qDebug()<<"cloudNames size: "<<this->cachedClouds.at(topLevelCloudIndex)->getCloudsNames().size();
}
/*
void PointCloudController::updateTreeWidgetItem(std::string cloudPath,std::vector<std::string> children){

    QList<QTreeWidgetItem *> foundItems=this->treeWidgetObserver->findItems(QString::fromStdString(cloudPath),Qt::MatchCaseSensitive);
    QTreeWidgetItem * treeChildObject;
    // we assume thad CloudPath is unique, so there is only one item in TreeWidget witch such text
    foundItems.at(0)->takeChildren(); //remove children (objects list)
    //and fill the list according to model
    for(auto child:children){
        //treeChildObject=new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString::number(child)));
        treeChildObject=new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString(child.c_str())));
        foundItems.at(0)->addChild(treeChildObject);
    }

}
*/
void PointCloudController::updateTreeWidgetItem(CloudComponent *cloud){
    QList<QTreeWidgetItem *> foundItems;
    QTreeWidgetItem* child;
    int childIndex=-1;

    //cloud has no parent
    if(cloud->getParentSceneName()==""){
        foundItems=this->treeWidgetObserver->findItems(QString::fromStdString(cloud->getSourcePath()),Qt::MatchCaseSensitive);
        if(!foundItems.empty()){
            //only one item should be found while using uniqe identifier (here cloud source path)
            foundItems.at(0)->setText(treeWidgetNameColumnID,QString(cloud->getSourcePath().c_str()));
            if(cloud->getCloudType()==type_CloudScene){
                foundItems.at(0)->setText(treeWidgetCloudTypeID,QString("scene"));
            }else if(cloud->getCloudType()==type_CloudObject){
                foundItems.at(0)->setText(treeWidgetCloudTypeID,QString("object"));
            }
            foundItems.at(0)->setText(treeWidgetClassIDColumnID,QString::number(cloud->getCloudClassID()));
            foundItems.at(0)->setText(treeWidgetClassNameColumnID,QString(cloud->getCloudClassName().c_str()));
            //std::string responseVector=vectorToString(cloud->getNNResopneVector()," ");
            //foundItems.at(0)->setText(treeWidgetNNResponseVectorColumnID,QString(responseVector.c_str()));
            foundItems.at(0)->setText(treeWidgetNNResponseVectorColumnID,QString(vectorToString(cloud->getNNResopneVector()," ",true).c_str()));
        }else{
            //create newItem with cloud sourcePath in first column
            QTreeWidgetItem * newItem = new QTreeWidgetItem (this->treeWidgetObserver, QStringList(QString(cloud->getSourcePath().c_str())));
            qDebug()<<"Could not find parent by sourcePath ="<<cloud->getSourcePath().c_str()<<" for parent cloud: "<<cloud->getName().c_str();
            qDebug()<<"Adding new qTreeWidget item.";
            treeWidgetObserver->addTopLevelItem(newItem);
            updateTreeWidgetItem(cloud);
        }
    }//cloud is a child
    else{
        foundItems=this->treeWidgetObserver->findItems(QString::fromStdString(cloud->getParentSourcePath()),Qt::MatchCaseSensitive);
        if(!foundItems.empty()){
            childIndex=cloud->getCloudID();
            //# UWAGA ->TU nie przeprowadzilem jeszcze child->setData() wiec wywolywanie tej funkcji (getChildItemWithID - bazuje ona na id dzieci) nie ma sensu
            child=getChildItemWithID(foundItems.at(0),childIndex);
            //child=foundItems.at(0)->child(childIndex);//# UWAGA - tu trzeba znajdowac inaczej (child dla ktorego item->data(0, Qt::UserRole).toInt() ==childIndex)
            if(child==nullptr){
                child=new QTreeWidgetItem(((QTreeWidget*)0));
                child->setText(treeWidgetNameColumnID,QString(cloud->getName().c_str()));
                child->setText(treeWidgetClassIDColumnID,QString::number(cloud->getCloudClassID()));
                child->setText(treeWidgetClassNameColumnID,QString(cloud->getCloudClassName().c_str()));
                child->setText(treeWidgetNNResponseVectorColumnID,QString(vectorToString(cloud->getNNResopneVector()," ",true).c_str()));
                //# UWAGA tu moze potencjalnie wystapic blad -> niezsynchronizowanie id obiektu z id w treeWidgetItems childs
                //# to moze wystapic w kazdym przypadku, gdy nie dodajemy hurtowo wszystkich posegmentowanych obiektow do TreeWidget
                //# ale QTreeWidgetItem->insert juz chyba rozwiazjuje ten problem (wstawaimy na konkretnym miejscu a nie koncu)
                //# OSTATECZNE ROZWIAZANIE - nie uzywam indexu childItem w QTreeWidget, tylko dodaje do kazdego childItem id tak jak ponizej i tu :https://stackoverflow.com/questions/28791549/qtreewidgteritem-hidden-value-or-addition-attribute
                //# to id jest zawsze takie samo jak cloud id i nie musi korespondiwac z chilItem index, czyli tez nie musi byc wyswietlane na pozycji o danym childIndex w QTreeWidget
                //set QTreeWidget Item child ID = child cloud ID
                // WARNING - position of QTreeWidget child Item in QTreeWidget doesnt have to correspond to its id (cloud ID)
                child->setData(0, Qt::UserRole, childIndex);
                foundItems.at(0)->addChild(child);
                //foundItems.at(0)->insertChild(childIndex,child);

            }else{
                //# UWAGA problem jest w funkcji getChildItemWithID -> funkcja zamiast child zwraca parent, i edytujemy wowczas tekst rodzica - stad ta zmiana nazwy rodzica na nazwe dziecka
                child->setText(treeWidgetNameColumnID,QString(cloud->getName().c_str()));
                child->setText(treeWidgetClassIDColumnID,QString::number(cloud->getCloudClassID()));
                child->setText(treeWidgetClassNameColumnID,QString(cloud->getCloudClassName().c_str()));
                child->setText(treeWidgetNNResponseVectorColumnID,QString(vectorToString(cloud->getNNResopneVector()," ",true).c_str()));
            }
        }else{
            qDebug()<<"Could not find parent by parentSourcePath ="<<cloud->getParentSourcePath().c_str()<<" for child cloud: "<<cloud->getName().c_str();
        }

    }
}

void PointCloudController::updateQVTKWidget(){
    this->viewerObserver->resetCamera(); //to center camera on object
    this->qVTKWidgetObserver->update ();
}
bool PointCloudController::updateCachedCloudsContainer(QTreeWidgetItem* selectedItem){

    //if top Level Scene or Object object is already created
    if(getTopLevelIndexOfSelectedCloud(selectedItem)>=0){
        return true;
    }
    //else check if memory is available and create new CloudScene or CloudObject object
    else{
        //if cached cloud scenes occupy to much memory, delete the oldest (first added) ones
        while(getMemoryUsageOfCachedClouds()>static_cast<std::size_t>(cachedCloudsMemoryLimit*1000000)){
            qDebug()<<"deleting: "<<cachedClouds.at(0)->getName().c_str()<<" beacuse memory limit for cached clouds was exceeded - you can change it in settings";
            cachedClouds.erase(cachedClouds.begin());
            //this->observer->updateTreeWidgetItem(cloudPath,{}); //we delete items assosiated with segmented objects which doesnt exist any more (because we deleted secen holding them)
            //#UWAGA -> czy na pewno usuwajac scene usuwam tez obiekty (posegmentowane) znajdujace sie w niej w postaci wektora clouds ? -> moze cloud objects tez powinny byc unique_ptr, albo powienienm je usuwac jakosc dla pewnosci w destruktorze CloudScene ?
        }

        //# I TUTAJ TWORZE CloudScene albo CloudObject (w zaleznosci od typu wczytanego obiketu ->kolumna nr 1 w QTreeWidget, uzupelniania wtrakcie wczytywania)
        //Create CloudScene or CloudObject object depending on top level item type (selected while loading by user)
        selectedItem=getTopLevelItem(selectedItem);
        std::string cloudPath=selectedItem->text(treeWidgetNameColumnID).toStdString();

        if(selectedItem->text(treeWidgetCloudTypeID)=="scene"){
            std::unique_ptr<CloudScene> newScene =sceneFactory->create(cloudPath);
            newScene->setFactory(objectFactory);
            newScene->setController(shared_from_this());//#https://stackoverflow.com/questions/27894246/cast-this-to-stdshared-ptr
            cachedClouds.push_back(std::move(newScene)); //#we have to move unique_ptr : https://stackoverflow.com/questions/3283778/why-can-i-not-push-back-a-unique-ptr-into-a-vector
        }else{
            //UWAGA -> TRZEBA CHYBA wszedzie przerobic w modelu w CloudObject shared_ptr na unique_ptr (i tak to powinno byc chyba lepsze - shared_ptr jest wydaje mi sie niepotrzebny)
            std::unique_ptr<CloudObject> newObject=objectFactory->create(cloudPath);
            newObject->setController(shared_from_this());
            cachedClouds.push_back(std::move(newObject));
        }
        updateView();
        return true;
    }
}
void PointCloudController::remove(QList<QTreeWidgetItem*> selectedClouds){
    int selectedSceneIndex;
    if(selectedClouds.size()>0){
        for (auto item:selectedClouds){
            //updateCachedCloudsContainer(item);
            selectedSceneIndex=getTopLevelIndexOfSelectedCloud(item);
            if(selectedSceneIndex>=0){
                //selected child cloud (after segmentation)
                if(item->parent()!=nullptr){
                    cachedClouds.at(selectedSceneIndex)->removeCloud(/*id*/item->data(0, Qt::UserRole).toInt());
                    delete item;
                }
                //selected top level cloud (scene or object)
                else{
                    //this->observable->visualize(selectedItem->text(0).toStdString(),viewer);
                    cachedClouds.erase(cachedClouds.begin()+selectedSceneIndex);
                    delete item;
                }
            }else{
                //we delete only item in view:
                delete item;
                qDebug()<<"Could not find selected cloudScene in cachedClouds vector or could not find parent cloudScene for selected  object in cachedClouds vector";
            }
        }
        updateView();
    }
}
void PointCloudController::visualize(QTreeWidgetItem* selectedItem,pcl::visualization::PCLVisualizer::Ptr viewer){
    //We are using same viewer, so we have to clear all added point clouds and shapes
    clearViewer(viewer);
    int selectedSceneIndex;
    if(selectedItem!=nullptr){
        updateCachedCloudsContainer(selectedItem);
        selectedSceneIndex=getTopLevelIndexOfSelectedCloud(selectedItem);

        if(selectedSceneIndex>=0){
            //selected child cloud (after segmentation)
            if(selectedItem->parent()!=nullptr){
                //this->observable->visualize(selectedItem->parent()->text(0).toStdString(),selectedItem->parent()->indexOfChild(selectedItem),viewer);
                if(cachedClouds.at(selectedSceneIndex)->getCloudType()==type_CloudScene){
                    cachedClouds.at(selectedSceneIndex)->visualize(visualization,/*id*/selectedItem->data(0, Qt::UserRole).toInt(),viewer);
                    updateQVTKWidget();
                }else{
                    qDebug()<<"This operation is supported only for CloudScene";
                    qDebug()<<cachedClouds.at(selectedSceneIndex)->getName().c_str();
                }
            }
            //selected top level cloud (scene or object)
            else{
                //this->observable->visualize(selectedItem->text(0).toStdString(),viewer);
                cachedClouds.at(selectedSceneIndex)->visualize(visualization, viewer);
                updateQVTKWidget();
            }
        }else{
            qDebug()<<"Could not find selected cloudScene in cachedClouds vector or could not find parent cloudScene for selected  object in cachedClouds vector";
        }
    }
    else{
        qDebug()<<"No items selected ";
    }


}
void PointCloudController::visualizeAllChildren(QTreeWidgetItem* selectedItem,pcl::visualization::PCLVisualizer::Ptr viewer){
    //We are using same viewer, so we have to clear all added point clouds and shapes
    clearViewer(viewer);
    int selectedSceneIndex;
    if(selectedItem!=nullptr){
        updateCachedCloudsContainer(selectedItem);
        selectedSceneIndex=getTopLevelIndexOfSelectedCloud(selectedItem);

        if(selectedSceneIndex>=0){
            //selected child cloud (after segmentation)
            if(selectedItem->parent()!=nullptr){
                //this->observable->visualize(selectedItem->parent()->text(0).toStdString(),selectedItem->parent()->indexOfChild(selectedItem),viewer);
                if(cachedClouds.at(selectedSceneIndex)->getCloudType()==type_CloudScene){
                    //#tu powinna tez byc opcja visualizeAllChildren dla sceny-dziecka
                    cachedClouds.at(selectedSceneIndex)->visualize(visualization,selectedItem->data(0, Qt::UserRole).toInt(),viewer);
                    updateQVTKWidget();
                }else{
                    qDebug()<<"This operation is supported only for CloudScene";
                    qDebug()<<cachedClouds.at(selectedSceneIndex)->getName().c_str();
                }
            }
            //selected top level cloud (scene or object)
            else{
                //this->observable->visualize(selectedItem->text(0).toStdString(),viewer);
                cachedClouds.at(selectedSceneIndex)->visualizeAllChildren(visualization, viewer);
                updateQVTKWidget();
            }
        }else{
            qDebug()<<"Could not find selected cloudScene in cachedClouds vector or could not find parent cloudScene for selected  object in cachedClouds vector";
        }
    }
    else{
        qDebug()<<"No items selected ";
    }
}
void PointCloudController::segment(QList<QTreeWidgetItem*> selectedClouds,std::shared_ptr<SegmentationType> segmentationType){
    int selectedSceneIndex;
    //remove from selection already segmented cloudObjects
    //# na razie nie wspieram segmentacji posegmentowanych obiektow
    for (int i=0; i<selectedClouds.size();++i){
        if(selectedClouds.at(i)->parent()!=nullptr){
            selectedClouds.removeAt(i);
        }
    }

    if(selectedClouds.size()>0){
        for (auto item:selectedClouds){
            //cloudPath=item->text(0).toStdString();  //# tutaj kolumna zawierajaca lokalizacje pliku
            updateCachedCloudsContainer(item);
            selectedSceneIndex=getTopLevelIndexOfSelectedCloud(item);
            if(selectedSceneIndex>=0){
                cachedClouds.at(selectedSceneIndex)->segment(segmentationType);
                //notifyObserver(item);
                //updateView(item); //# to cos jeszcze nie dziala-> POPRAW, bo ze wzgledu na wydajnosc lepiej updateowac tylko chmure,ktroej to dotyuczy niz wszstkie
                updateView();
            }else{
                qDebug()<<"Could not find any cloudScene in cachedClouds vector";
            }
        }
    }else{
        qDebug()<<"No items selected for segmentation, you can only segment scenes";
    }

}
void PointCloudController::project(QList<QTreeWidgetItem*> selectedClouds,std::shared_ptr<ProjectionType> projectionType,std::shared_ptr<EditType> editType){
    int selectedSceneIndex;
    if(selectedClouds.size()>0){

        for (auto item:selectedClouds){
            updateCachedCloudsContainer(item);
            selectedSceneIndex=getTopLevelIndexOfSelectedCloud(item);
            if(selectedSceneIndex>=0){
                //selected child cloud (after segmentation)
                if(item->parent()!=nullptr){
                    //this->observable->visualize(selectedItem->parent()->text(0).toStdString(),selectedItem->parent()->indexOfChild(selectedItem),viewer);
                    cachedClouds.at(selectedSceneIndex)->project(projectionType,item->data(0, Qt::UserRole).toInt());
                    if(editType!=nullptr){
                        cachedClouds.at(selectedSceneIndex)->edit(editType,item->data(0, Qt::UserRole).toInt());
                    }
                    //# scenes.at(selectedSceneIndex)->saveProjections(folderPath,item->parent()->indexOfChild(item));
                }
                //selected top level cloud (scene or object)
                //# jak na razie w modelu to jest zdefiniowane tak, ze robimy projekcje wszystkich podchmur (wysegmentowanych obiektow w scenie)
                else{
                    //this->observable->visualize(selectedItem->text(0).toStdString(),viewer);
                    cachedClouds.at(selectedSceneIndex)->project(projectionType);
                    if(editType!=nullptr){
                        cachedClouds.at(selectedSceneIndex)->edit(editType);
                    }
                    //# scenes.at(selectedSceneIndex)->saveProjections(folderPath);
                }
            }else{
                qDebug()<<"Could not find selected cloudScene in cachedClouds vector or could not find parent cloudScene for selected  object in cachedClouds vector";
            }
        }
    }

}
void PointCloudController::saveProjections(QList<QTreeWidgetItem*> selectedClouds,std::string folderPath){
    int selectedSceneIndex;
    for (auto item:selectedClouds){
        updateCachedCloudsContainer(item);
        selectedSceneIndex=getTopLevelIndexOfSelectedCloud(item);
        if(selectedSceneIndex>=0){
            //selected child cloud (after segmentation)
            if(item->parent()!=nullptr){
                //this->observable->visualize(selectedItem->parent()->text(0).toStdString(),selectedItem->parent()->indexOfChild(selectedItem),viewer);
                cachedClouds.at(selectedSceneIndex)->saveProjections(folderPath,item->data(0, Qt::UserRole).toInt());
            }
            //selected top level cloud (Scene or Object)
            //# jak na razie w modelu to jest zdefiniowane tak, ze robimy projekcje wszystkich podchmur (wysegmentowanych obiektow w scenie)
            else{
                //this->observable->visualize(selectedItem->text(0).toStdString(),viewer);
                cachedClouds.at(selectedSceneIndex)->saveProjections(folderPath);
            }
        }else{
            qDebug()<<"Could not find selected cloudScene in cachedClouds vector or could not find parent cloudScene for selected  object in cachedClouds vector";
        }
    }
}

/* stara wersja classify
 *
void PointCloudController::classify(QList<QTreeWidgetItem*> selectedClouds,std::shared_ptr<ClassificationType> classificationType,std::string modelPath,int numOfClasses){
    int selectedSceneIndex;
    //segment(selectedClouds,segmentationType);
    //project(selectedClouds,projectionType,editType);
    //# UWAGA DODAC OPCJE KLASYFIKACJI POJEDYNCZYCH, POSEGMENTOWANYCH OBIKETOW (CZYLI TAKICH DLA KTORYCH item->parent()!=nullptr)
    for (auto item:selectedClouds){
        //cloudPath=item->text(0).toStdString();  //# tutaj kolumna zawierajaca lokalizacje pliku
        updateScenesContainer(item);
        selectedSceneIndex=getTopLevelIndexOfSelectedCloud(item);
        if(selectedSceneIndex>=0){
            //selected child cloud (after segmentation)
            if(item->parent()!=nullptr){
                cachedClouds.at(selectedSceneIndex)->classify(classificationType,modelPath,numOfClasses,item->parent()->indexOfChild(item));
            }
            //selected top level cloud (scene or object)
            else
            {
                cachedClouds.at(selectedSceneIndex)->classify(classificationType,modelPath,numOfClasses);
            }
        }else{
            qDebug()<<"Could not find any cloudScene in cachedClouds vector";
        }
    }

}
*/
void PointCloudController::classify(QList<QTreeWidgetItem*> selectedClouds,std::shared_ptr<ClassificationType> classificationType,std::shared_ptr<SegmentationType> segmentationType,std::shared_ptr<ProjectionType> projectionType,std::shared_ptr<EditType> editType,std::string modelPath,int numOfClasses){
    int selectedSceneIndex;
    //segment(selectedClouds,segmentationType);
    //project(selectedClouds,projectionType,editType);
    //# UWAGA DODAC OPCJE KLASYFIKACJI POJEDYNCZYCH, POSEGMENTOWANYCH OBIKETOW (CZYLI TAKICH DLA KTORYCH item->parent()!=nullptr)
    for (auto item:selectedClouds){
        //cloudPath=item->text(0).toStdString();  //# tutaj kolumna zawierajaca lokalizacje pliku
        updateCachedCloudsContainer(item);
        selectedSceneIndex=getTopLevelIndexOfSelectedCloud(item);
        if(selectedSceneIndex>=0){
            //selected child cloud (after segmentation)
            if(item->parent()!=nullptr){
                //# zaimplementowac ponizsza funkcje (na razie nie uzywam ale moze na przyszlosc)
                //cachedClouds.at(selectedSceneIndex)->segment(segmentationType,item->parent()->indexOfChild(item));
                cachedClouds.at(selectedSceneIndex)->project(projectionType,item->data(0, Qt::UserRole).toInt());
                if(editType!=nullptr){
                    cachedClouds.at(selectedSceneIndex)->edit(editType,item->data(0, Qt::UserRole).toInt());
                }
                cachedClouds.at(selectedSceneIndex)->classify(classificationType,modelPath,numOfClasses,item->data(0, Qt::UserRole).toInt());
            }
            //selected top level cloud (scene or object)
            else
            {
                cachedClouds.at(selectedSceneIndex)->classify(classificationType,segmentationType,projectionType,editType,modelPath,numOfClasses);
            }
        }else{
            qDebug()<<"Could not find any cloudScene in cachedClouds vector";
        }
    }
}
/*
void PointCloudController::setBenchmarkType(QList<QTreeWidgetItem*> selectedClouds,std::shared_ptr<BenchmarkType> benchmarkType){
    int selectedCloudTopIndex;
    //# UWAGA DODAC OPCJE BENCHMARKU POJEDYNCZYCH, POSEGMENTOWANYCH OBIKETOW (CZYLI TAKICH DLA KTORYCH item->parent()!=nullptr)
    for (auto item:selectedClouds){
        //cloudPath=item->text(0).toStdString();  //# tutaj kolumna zawierajaca lokalizacje pliku
        updateScenesContainer(item);
        selectedCloudTopIndex=getTopLevelIndexOfSelectedCloud(item);
        if(selectedCloudTopIndex>=0){
            //selected child cloud (after segmentation)
            if(item->parent()!=nullptr){
                cachedClouds.at(selectedCloudTopIndex)->setBenchmarkType(benchmarkType,item->parent()->indexOfChild(item));
            }
            //selected top level cloud (scene or object)
            else
            {
                cachedClouds.at(selectedCloudTopIndex)->setBenchmarkType(benchmarkType);
            }
        }else{
            qDebug()<<"Could not find such parent cloud in cachedClouds vector";
        }
        updateView(item);
    }
}*/
void PointCloudController::benchmark(QList<QTreeWidgetItem*> selectedClouds,std::shared_ptr<BenchmarkType> benchmarkType, std::string folderPath){
    int selectedCloudTopIndex;
    //# UWAGA DODAC OPCJE BENCHMARKU POJEDYNCZYCH, POSEGMENTOWANYCH OBIKETOW (CZYLI TAKICH DLA KTORYCH item->parent()!=nullptr)
    for (auto item:selectedClouds){
        //cloudPath=item->text(0).toStdString();  //# tutaj kolumna zawierajaca lokalizacje pliku
        updateCachedCloudsContainer(item);
        selectedCloudTopIndex=getTopLevelIndexOfSelectedCloud(item);
        if(selectedCloudTopIndex>=0){
            //selected child cloud (after segmentation)
            if(item->parent()!=nullptr){
                try {
                    cachedClouds.at(selectedCloudTopIndex)->benchmark(benchmarkType,folderPath,/*item id*/item->data(0, Qt::UserRole).toInt());

                } catch (const std::out_of_range& e) {
                    qDebug()<<"Worng0 selectedCloudTopIndex ="<<selectedCloudTopIndex<<" . chachedClouds.size()="<<cachedClouds.size();
                }
            }
            //selected top level cloud (scene or object)
            else
            {
                try {
                    cachedClouds.at(selectedCloudTopIndex)->benchmark(benchmarkType,folderPath);
                } catch (const std::out_of_range& e) {
                    qDebug()<<"Wrong1 selectedCloudTopIndex ="<<selectedCloudTopIndex<<" . chachedClouds.size()="<<cachedClouds.size();
                }

            }
        }else{
            qDebug()<<"Could not find such parent cloud in cachedClouds vector";
        }
        //wyglada na to, ze juz przed wejsciem do updateView(item) scena TopLevel jest zamieniana z object0
        updateView(item);
    }
}

void PointCloudController::saveClouds(QList<QTreeWidgetItem*> selectedClouds,QString folderPath,std::shared_ptr<SaveConditions> saveCond){
    int selectedCloudTopIndex;
    std::vector<std::vector<int> > indexesToSave(cachedClouds.size(),std::vector<int>(1,-std::numeric_limits<int>::max())); // {{-max}_1,{-max}_2,...,{-max}_n} n=cachedClouds.size()
    for (auto item:selectedClouds){
        selectedCloudTopIndex=getTopLevelIndexOfSelectedCloud(item);
        if(selectedCloudTopIndex>=0){
            //clear vector if he haven't added anny indexes to it yet
            if(!indexesToSave.empty()){
                if(indexesToSave.at(selectedCloudTopIndex).at(0)==-std::numeric_limits<int>::max()){
                        indexesToSave.at(selectedCloudTopIndex).clear();
                }
            }

            //selected child cloud (after segmentation)
            if(item->parent()!=nullptr){
                indexesToSave.at(selectedCloudTopIndex).push_back(item->data(0, Qt::UserRole).toInt());
            }
            //selected top level cloud (scene or object)
            else
            {
                indexesToSave.at(selectedCloudTopIndex)=cachedClouds.at(selectedCloudTopIndex)->getCloudsIDs();
            }
        }else{
            qDebug()<<"Could not find such parent cloud in cachedClouds vector";
        }
    }
    this->saveLoad->save(folderPath,this->cachedClouds,indexesToSave,saveCond);
}
void PointCloudController::loadClouds(QString path){
    this->saveLoad->load(path,this->cachedClouds,shared_from_this(),this->objectFactory);
    updateView();
}
