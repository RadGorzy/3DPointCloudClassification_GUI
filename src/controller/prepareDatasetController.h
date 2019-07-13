#ifndef PREPAREDATASETCONTROLLER_H
#define PREPAREDATASETCONTROLLER_H
#include <QTreeWidget>
#include <prepareDataset.h>
class PrepareDatasetController
{
private:
    QTreeWidget* treeWidget=nullptr;
    const int srcPathColumn=0;
    const int dstPathColumn=1;
    const int finishedIndicatorColumn=2;
public:
    PrepareDatasetController(QTreeWidget* trWid);
    void updateView(QTreeWidgetItem* item,const QString state);
    void prepare(std::shared_ptr<PrepareDatasetFrom3D> prepareDatasetFrom3D);
};

#endif // PREPAREDATASETCONTROLLER_H