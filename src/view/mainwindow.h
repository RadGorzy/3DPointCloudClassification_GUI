#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QVTKWidget.h>
//#include <QVTKOpenGLWidget.h>
//#include <QVTKOpenGLNativeWidget.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

#include <QFileDialog>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>

//#include <memory> //do std::make_unique
#include <string>
class CloudScene;
#include "src/model/pointCloud.h"
class CloudSceneFactory;
#include "src/model/cloudFactory.h"
////////#
// Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

// Visualization Toolkit (VTK)
#include <vtkRenderWindow.h>

class PointCloudController;
#include "src/controller/pointCloudController.h"
class ThreadController;
#include "src/controller/threadController.h"
#include "lib/qdebugStream.h"
#include "lib/helperFunctions.h"

#include "src/controller/prepareDatasetController.h"
#include "src/view/configuration.h"

#include"src/view/saveSettings.h"


typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
/////////#
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setController(std::shared_ptr<PointCloudController> contr);
    void setThreadController(std::shared_ptr<ThreadController> thCont);
    // QMessage
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    static  void QMessageOutput(QtMsgType , const QMessageLogContext &, const QString &msg);
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/


/////////#
protected:
    pcl::visualization::PCLVisualizer::Ptr viewer;
    PointCloudT::Ptr cloud;
//////////#
private slots:
    void on_segmentation_comboBox_currentIndexChanged(int index);
    void on_load_button_clicked();


    void on_projection_comboBox_currentIndexChanged(int index);

    void on_projectionSaveFolder_pushButton_clicked();

    void on_loadObjects_button_clicked();

    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_actionClassification_triggered();

    void on_actionTraining_data_preparation_triggered();

    void treeCustomMenu(const QPoint & pos);

    void on_addPrepareTreeItem_pushButton_clicked();

    void on_removePrepareTreeItem_pushButton_clicked();

    void on_actionsave_configuration_triggered();

    void on_actionload_configuration_triggered();

    void on_classificationModel_pushButton_clicked();

    void on_remove_pushButton_clicked();

    void on_actionsave_selected_clouds_triggered();

    void on_actionload_clouds_triggered();

public slots: //if we use connect (old style SLOT and SIGNAL) we have to declare used there functions as public slots
    void tescik();
    void visualize();
    void visualizeAllChildren();
    void segment();
    void project();
    void classify();
    void benchmark();
    void prepareFrom3D();


private:
    Ui::MainWindow *ui;
    vtkRenderer* _qvtkRenderer;
    QStringList loadedFiles;
    QList<QTreeWidgetItem *> items;

    //observer/controller part:
    std::shared_ptr<PointCloudController> controller;
    std::shared_ptr<PrepareDatasetController> prepareDatasetController;

    //thread controll (to prevent freezing while doing long calculation operations
    std::shared_ptr<ThreadController> threadController;

    //std::vector<std::unique_ptr<CloudScene>> cloudScenes;
    std::shared_ptr<CloudScene> scene;
    std::shared_ptr<CloudSceneFactory> sceneFactory;
    std::shared_ptr<CloudObjectFactory> objectFactory;

    //for saving configurations
    std::unique_ptr<Configuration> config;

    //consol output to text widget
    // MessageHandler for display and ThreadLogStream for redirecting cout
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    MessageHandler *msgHandler = Q_NULLPTR;
    ThreadLogStream* m_qd;
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

    //
    std::shared_ptr<ProjectionType> getProjectionType();
    std::shared_ptr<EditType> getEditType();
    std::shared_ptr<SegmentationType> getSegmentationType();
    std::shared_ptr<ClassificationType> getClassificationType();
    std::shared_ptr<BoundingBoxType> getBoundingBoxType();
    std::shared_ptr<BenchmarkType> getBenchmarkType();

};
#endif // MAINWINDOW_H
