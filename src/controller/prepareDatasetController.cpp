#include "src/controller/prepareDatasetController.h"

PrepareDatasetController::PrepareDatasetController(QTreeWidget* trWid):treeWidget(trWid)
{

}
void PrepareDatasetController::updateView(QTreeWidgetItem* item,const QString state){
    item->setText(finishedIndicatorColumn,state);

}

void PrepareDatasetController::prepare(std::shared_ptr<PrepareDatasetFrom3D> prepareDatasetFrom3D){
    QList<QTreeWidgetItem*> selectedItems = this->treeWidget->selectedItems();
    for (auto item:selectedItems){
        updateView(item,"processing ...");
        prepareDatasetFrom3D->prepare(item->text(this->srcPathColumn).toStdString(),item->text(this->dstPathColumn).toStdString());
        updateView(item,"finished");
    }
}

void PrepareDatasetController::extract(std::shared_ptr<ExtractObjectsInstances> extractObjectsInstances){
    QList<QTreeWidgetItem*> selectedItems = this->treeWidget->selectedItems();
    for (auto item:selectedItems){
        updateView(item,"processing ...");
        extractObjectsInstances->setInPath(item->text(this->srcPathColumn).toStdString());
        extractObjectsInstances->setOutPath(item->text(this->dstPathColumn).toStdString());
        extractObjectsInstances->extract();
        updateView(item,"finished");
    }
}
