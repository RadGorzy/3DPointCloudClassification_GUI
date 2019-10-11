#include "mainwindow.h"
#include "ui_mainwindow.h"

// Catch QMessage, redirect to cout
 /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
void MainWindow::QMessageOutput(QtMsgType , const QMessageLogContext &, const QString &msg)
{
   std::cout<<msg.toStdString().c_str()<<std::endl;
}
 /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<"URUCHOMILEM";
    // Set up ThreadLogStream, which redirect cout to signal sendLogString
    // Set up  MessageHandler,  wgucg catch message from sendLogString and Display
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    /*
    m_qd = new ThreadLogStream(std::cout); //Redirect Console output to QTextEdit
    this->msgHandler = new MessageHandler(this->ui->log_plainTextEdit, this);
    connect(m_qd, &ThreadLogStream::sendLogString, msgHandler, &MessageHandler::catchMessage);
    */
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

    //initilizes satcked widgets with apropriate initial tab
    ui->segmentation_stackedWidget->setCurrentIndex(ui->segmentation_comboBox->currentIndex());
    ui->projection_stackedWidget->setCurrentIndex(ui->projection_comboBox->currentIndex());

    _qvtkRenderer = vtkRenderer::New();
    //ui->qvtk_openGLNativeWidget->GetRenderWindow()->AddRenderer(_qvtkRenderer);
    ui->qvtkView_widget->GetRenderWindow()->AddRenderer(_qvtkRenderer);
    _qvtkRenderer->SetBackground(0,255,0);
    _qvtkRenderer->Render();

    // Set up the QVTK window, initilize it with PCLVisualizer -> do this only once!
    viewer.reset (new pcl::visualization::PCLVisualizer ("initial", false));
    ui->qvtkView_widget->SetRenderWindow (viewer->getRenderWindow ()); //#w VTK 8.2 i qvtkWidget (nie openGl)juz nie ma// tu jest poroblem (segfault)
    viewer->setupInteractor (ui->qvtkView_widget->GetInteractor (), ui->qvtkView_widget->GetRenderWindow ());
    ui->qvtkView_widget->update ();

    //Initilize treeWidget in Classify tab
    //ui->treeWidget->setColumnCount(2);
    //Initilize treeWidget in Prepare tab
    //here, column count and names are set through qt Designer
    //for context menu (right click on item): https://stackoverflow.com/questions/30475038/right-click-on-qtreeview-item/30475275
    ui->prepare_treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->prepare_treeWidget, SIGNAL(customContextMenuRequested(QPoint)),
    this, SLOT(treeCustomMenu(QPoint)));

    this->prepareDatasetController=std::make_shared<PrepareDatasetController>(this->ui->prepare_treeWidget);

    //Initilize cloud factories
    this->sceneFactory=std::make_shared<CloudSceneFactory>();
    this->objectFactory=std::make_shared<CloudObjectFactory>();

    //set streatch factors for splitter in prepare tab: ->eventually i set it in qtDesigner
    //this->ui->splitter_2->setStretchFactor(0, 0);
    //this->ui->splitter_2->setStretchFactor(1, 1);

    //classify tab:
    connect(ui->view_pushButton,SIGNAL(clicked()),this, SLOT(visualize()));
    connect(ui->viewAll_pushButton,SIGNAL(clicked()),this, SLOT(visualizeAllChildren()));
    connect(ui->segment_pushButton,SIGNAL(clicked()),this, SLOT(segment()));
    connect(ui->project_pushButton,SIGNAL(clicked()),this, SLOT(project()));
    connect(ui->classify_pushButton,SIGNAL(clicked()),this, SLOT(classify()));
    connect(ui->benchmark_pushButton,SIGNAL(clicked()),this, SLOT(benchmark()));
    //connect(ui->treeWidget,SIGNAL(itemSelectionChanged()),this, SLOT(tescik()));
    //prepare tab:
    connect(ui->prepareFrom3D_pushButton,SIGNAL(clicked()),this, SLOT(prepareFrom3D()));
    connect(ui->prepareExtractInstances_pushButton,SIGNAL(clicked()),this, SLOT(extractObjectsInstances()));


    /*
    QTreeWidgetItem * item = new QTreeWidgetItem ((QTreeWidget*)0, QStringList(QString("item: 1000")));
    QTreeWidgetItem * child = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("child")));
    for (int i = 0; i < 10; ++i)
        items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item: %1").arg(i))));
    ui->treeWidget->insertTopLevelItems(0, items);
    ui->treeWidget->insertTopLevelItem(1, item);
    item->addChild(child);
*/
    QTreeWidgetItem * item = new QTreeWidgetItem ((QTreeWidget*)0, QStringList(QString("../example_scenes/IGN_Z0_car_1.pcd")));
    QTreeWidgetItem * item1 = new QTreeWidgetItem ((QTreeWidget*)0, QStringList(QString("../example_scenes/0000000003.pcd")));
    QTreeWidgetItem * item2 = new QTreeWidgetItem ((QTreeWidget*)0, QStringList(QString("../example_scenes/000023.bin")));
    item->setText(1,"object");
    item1->setText(1,"scene");
    item2->setText(1,"scene");
    ui->treeWidget->insertTopLevelItem(0, item);
    ui->treeWidget->insertTopLevelItem(0, item1);
    ui->treeWidget->insertTopLevelItem(0, item2);

    //initilize memory settings -only once during porgram execution so we retain selected options, later we call only memorySettings->exec();
    this->memorySettings=std::make_unique<MemorySettings>(this);

    //add widgets whose text we want to save to configuration file
    config=std::make_unique<Configuration>(this);
    //config->addWidget(this->ui->decimation_spinBox);
    //config->addWidget(this->ui->scale1_doubleSpinBox);
    config->addAllWidgetsOfGivenTypes({SpinBox,DoubleSpinBox,CheckBox,ComboBox,LineEdit,GroupBox});
    //# ponizsza linijka tylko do TESTOW, potem do USUNIECIA
    this->config->loadConfiguration("../configurations/CNN_binary_Map_person_edited_3x3_KITTI.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::tescik(){
    QString cloudPath = ui->treeWidget->currentItem()->text(ui->treeWidget->currentColumn());
    if( ui->treeWidget->currentItem()->parent()!=nullptr){
        qDebug()<<cloudPath <<" objectID= "<< ui->treeWidget->currentItem()->parent()->indexOfChild(ui->treeWidget->currentItem());
    }
    else
        qDebug()<<cloudPath <<" is parent (has no parent)";

}
void MainWindow::on_actionClassification_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_actionTraining_data_preparation_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_segmentation_comboBox_currentIndexChanged(int index)
{
    ui->segmentation_stackedWidget->setCurrentIndex(index);
}
void MainWindow::on_projection_comboBox_currentIndexChanged(int index)
{
    ui->projection_stackedWidget->setCurrentIndex(index);
}

void MainWindow::on_load_button_clicked()
{
    QTreeWidgetItem* item;
    loadedFiles=QFileDialog::getOpenFileNames(this, ("Open Cloud Scene/s"), "/home/", tr("(*.pcd *.bin)"));
    if (loadedFiles.size()>0){
        for(auto filepath:loadedFiles){
            qDebug()<<filepath;
            item=new QTreeWidgetItem ((QTreeWidget*)nullptr, QStringList(filepath));
            item->setText(1,"scene");//set data type (CloudObject or CloudScene) in "type" column
            items.append(item);
            //this->cloudScenes.push_back(sceneFactory->create(filepath.toStdString())); ->tak nie mozna robic-> za dlugi czas wczytywania
        }
        ui->treeWidget->insertTopLevelItems(0,items);
    }

}
void MainWindow::on_loadObjects_button_clicked()
{
    QTreeWidgetItem* item;
    loadedFiles=QFileDialog::getOpenFileNames(this, ("Open Cloud Object/s"), "/home/", tr("(*.pcd *.bin)"));
    if (loadedFiles.size()>0){
        for(auto filepath:loadedFiles){
            qDebug()<<filepath;
            item=new QTreeWidgetItem ((QTreeWidget*)nullptr, QStringList(filepath));
            item->setText(1,"object");//set data type (CloudObject or CloudScene) in "type" column
            items.append(item);
            //this->cloudScenes.push_back(sceneFactory->create(filepath.toStdString())); ->tak nie mozna robic-> za dlugi czas wczytywania
        }
        ui->treeWidget->insertTopLevelItems(0,items);
    }
}
void MainWindow::on_remove_pushButton_clicked()
{
    QList<QTreeWidgetItem*> selectedClouds=ui->treeWidget->selectedItems();
    this->controller->remove(selectedClouds);
}
void MainWindow::on_projectionSaveFolder_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if(dir!=""){
        ui->projectionSaveFolder_lineEdit->setText(dir);
    }else{
        qDebug()<<"No folder selected.";
    }

}
void MainWindow::on_classificationModel_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open model directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if(dir!=""){
        ui->classificationModel_lineEdit->setText(dir);
    }else{
        qDebug()<<"No model selected.";
    }

}
void MainWindow::on_benchmarkSaveFolder_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open benchmark save directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    ui->benchmarkSaveFolder_lineEdit->setText(dir);
}
void MainWindow::on_selectClassMapping_pushButton_clicked()
{
    QString classMappingFilePath="";
    classMappingFilePath=QFileDialog::getOpenFileName(this,tr("Select file with class mapping"),"/home/",tr("(*.txt)"));
    ui->selectClassMapping_lineEdit->setText(classMappingFilePath);
}

void MainWindow::setController(std::shared_ptr<PointCloudController> contr){
    this->controller=contr;
    this->controller->registerQTreeWidgetObserver(this->ui->treeWidget);
    this->controller->registerQVTKidgetObserver(this->ui->qvtkView_widget);
    this->controller->registerPCLViewerObserver(this->viewer);
    //this->controller->registerObserver(this);
}
void MainWindow::setThreadController(std::shared_ptr<ThreadController> thCont){
    this->threadController=thCont;
}
void MainWindow::visualize(){
    QTreeWidgetItem *selectedItem=ui->treeWidget->currentItem();
    this->controller->visualize(selectedItem,viewer);
}
void MainWindow::visualizeAllChildren(){
    QTreeWidgetItem *selectedItem=ui->treeWidget->currentItem();
    this->controller->visualizeAllChildren(selectedItem,viewer);
}
void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    this->controller->visualize(item,viewer);
}
std::shared_ptr<SegmentationType> MainWindow::getSegmentationType(){
    std::shared_ptr<SegmentationType> segmentationType;
    switch(ui->segmentation_comboBox->currentIndex()){
    //one step segmentation
    case 0:
    {
        segmentationType = std::make_shared<DONSegmentation>(/*scale1*/ui->scale1_doubleSpinBox->value()
                                                             ,/*scale2*/ ui->scale2_doubleSpinBox_2->value()
                                                             ,/*threshold*/ ui->threshold_doubleSpinBox_3->value()
                                                             ,/*segradius*/ ui->segradius_doubleSpinBox_4->value()
                                                             ,/*approx*/ ui->approx_checkBox->isChecked()
                                                             ,/*decimation*/ ui->decimation_spinBox->value()
                                                             ,/*TWO_STEP_SEGMENTATION*/false
                                                             ,/*scale1_1*/ui->scale1_1_twoStep_doubleSpinBox_9->value()
                                                             ,/*scale2_1*/ui->scale2_1_twoStep_doubleSpinBox_10->value());
        break;
    }
    //two step segmentation
    case 1:
    {
        segmentationType = std::make_shared<DONSegmentation>(/*scale1*/ui->scale1_twoStep_doubleSpinBox_5->value()
                                                             ,/*scale2*/ ui->scale2_twoStep_doubleSpinBox_6->value()
                                                             ,/*threshold*/ui->threshold_twoStep_doubleSpinBox_7->value()
                                                             ,/*segradius*/ ui->segradius_twoStep_doubleSpinBox_8->value()
                                                             ,/*approx*/ ui->approx_twoStep_checkBox_2->isChecked()
                                                             ,/*decimation*/ ui->decimation_twoStep_spinBox_2->value()
                                                             ,/*TWO_STEP_SEGMENTATION*/true
                                                             ,/*scale1_1*/ui->scale1_1_twoStep_doubleSpinBox_9->value()
                                                             ,/*scale2_1*/ui->scale2_1_twoStep_doubleSpinBox_10->value());
        break;
    }
    //just euclidean cluster extraction
    case 2:
    {
        segmentationType = std::make_shared<EuclideanClustering>(/*radius*/ui->EuclideanCluSegRadius_doubleSpinBox->value()
                                                                 ,/*min cluster size*/ui->EuclideanCluMinClusterSize_spinBox->value()
                                                                 ,/*max cluster size*/ui->EuclideanCluMaxClusterSize_spinBox_2->value());
        break;
    }
    default:
    {
        qDebug()<<"No such segmentation type defined, select different";
        return nullptr;
    }
    }
    return segmentationType;
}
std::shared_ptr<ProjectionType> MainWindow::getProjectionType(){
    std::shared_ptr<ProjectionType> projectionType;
    switch(ui->projection_comboBox->currentIndex()){
    case 0:
    {
        projectionType=std::shared_ptr<ProjectionType>(new BinaryProjection(/*min_degree*/ui->min_deg_doubleSpinBox_3->value()
                                                                            ,/*max_degree*/ui->max_deg_doubleSpinBox_4->value()
                                                                            ,/*num_hor_proj*/ui->n_proj_spinBox_6->value()
                                                                            ,/*min_h*/ui->min_h_doubleSpinBox_5->value()
                                                                            ,/*max_h*/ui->max_h_doubleSpinBox_7->value()
                                                                            ,/*num_vert_proj*/ui->n_h_proj_spinBox_8->value()));
        break;
    }
    case 1:
    {
        projectionType=std::shared_ptr<ProjectionType>(new RangeImageProjection(/*min_degree*/ui->min_deg_rangeImg_doubleSpinBox_11->value()
                                                                            ,/*max_degree*/ui->max_deg_rangeImgdoubleSpinBox_12->value()
                                                                            ,/*num_hor_proj*/ui->n_proj_rangeImg_spinBox_13->value()
                                                                            ,/*min_h*/ui->min_h_rangeImgdoubleSpinBox_14->value()
                                                                            ,/*max_h*/ui->max_h_rangeImg_doubleSpinBox_15->value()
                                                                            ,/*num_vert_proj*/ui->n_h_proj_rangeImg_spinBox_16->value()));
        break;
    }
    default:
    {
        qDebug()<<"No such projection type defined, select different";
        return nullptr;
    }
    }
    return projectionType;
}
std::shared_ptr<EditType> MainWindow::getEditType(){
    std::shared_ptr<EditType> editType;
    cv::MorphShapes kerShape;
    if(ui->editProjection_groupBox->isChecked()){
        switch(ui->editProjKernelShape_comboBox->currentIndex()){
        case 0:
        {
                kerShape=cv::MORPH_ELLIPSE;
                break;
        }
        case 1:
        {
            kerShape=cv::MORPH_CROSS;
            break;
        }
        case 2:
        {
            kerShape=cv::MORPH_RECT;
            break;
        }
        default:
        {
            qDebug()<<"No such kernel shape defined, select different";
            return nullptr;
        }
        }
        editType=std::make_shared<ProjectionEdit>(kerShape,
                                                  ui->editProjKernelWidth_spinBox_9->value(),
                                                  ui->editProjKernelHeight_spinBox_10->value());
        return editType;
    }else{
        return nullptr;
    }
}
std::shared_ptr<ClassificationType> MainWindow::getClassificationType(){
    std::shared_ptr<ClassificationType> classificationType = std::make_shared<MultiViewClassification>();
    return classificationType;
}
std::shared_ptr<BoundingBoxType> MainWindow::getBoundingBoxType(){
    std::shared_ptr<BoundingBoxType> boundingBox;
    if(ui->orientedBB_checkBox->isChecked()){
        boundingBox= std::make_shared<AxisAlignedBoudningBox>();
    }else{
        boundingBox=std::make_shared<OrientedBoundingBox>();
    }
    return boundingBox;
}
std::shared_ptr<BenchmarkType> MainWindow::getBenchmarkType(){
    std::shared_ptr<BenchmarkType> benchmarkType;
    std::vector<std::string> classMapping{};
    std::string filePath=ui->selectClassMapping_lineEdit->text().toStdString();
    read_txt_lines(filePath,classMapping);


    //benchmark type
    switch(ui->benchmark_comboBox->currentIndex()){
    case 0:
    {
        benchmarkType= std::make_shared<CustomBenchmark>(getBoundingBoxType());
        break;
    }
    case 1:
    {
        benchmarkType= std::make_shared<KITTIBenchmark>(getBoundingBoxType());
        break;
    }
    default:
    {
        qDebug()<<"No such benchmark type defined, select different";
        return nullptr;
    }
    }

    benchmarkType->setClassMapping(classMapping);

    return benchmarkType;
}
void MainWindow::segment(){
    QList<QTreeWidgetItem*> selectedScenes=ui->treeWidget->selectedItems();

    if(selectedScenes.size()>0){
        std::shared_ptr<SegmentationType> segmentationType;
        segmentationType=getSegmentationType();
        this->controller->segment(selectedScenes,segmentationType);
    }
    else{
        qDebug()<<"No items selected for segmentation";
    }

}
void MainWindow::project(){
    QList<QTreeWidgetItem*> selectedClouds=ui->treeWidget->selectedItems();
    std::string folderPath=ui->projectionSaveFolder_lineEdit->text().toStdString();
    std::shared_ptr<ProjectionType> projectionType;
    std::shared_ptr<EditType> editType;
//PROJECTION TYPE
    projectionType=getProjectionType();
//EDIT
    if(ui->editProjection_groupBox->isChecked()){
        editType=getEditType();
        this->controller->project(selectedClouds,projectionType,editType);
    }else{
        this->controller->project(selectedClouds,projectionType);
    }
    //save projections
    if(folderPath!=""){
       qDebug()<<"SAVING PROJECTIONS TO "<<folderPath.c_str();
       this->controller->saveProjections(selectedClouds,folderPath);
    }else{
        qDebug()<<"NOT SAVING PROJECTIONS - SAVE FOLDER PATH NOT GIVEN ";
    }
}
/* stara wersja classify - > dzialala dla malych chmur, ale dla duzych pobierala juz zbyt duzo ramu ->
 * bylo tak dlatego ze w tej wersji nie usuwalem na biezaco projekcji 2D zapinaych w wektorze projections w klasie CloudObject
 * void MainWindow::classify(){
    QList<QTreeWidgetItem*> selectedClouds=ui->treeWidget->selectedItems();
    std::string modelPath=ui->classificationModel_lineEdit->text().toStdString();
    int numOfClasses=ui->numberOfClasses_spinBox_17->value();
    if(modelPath!=""){
        segment();
        project();
        //numOfClasses=countTxtLines(classMappingPath);
        //"/home/radek/Documents/Qt5/data/zapisane/CNN_range_3D_BIWI"
        std::shared_ptr<ClassificationType> classificationType = getClassificationType();
        this->threadController->classify(this->controller,selectedClouds,classificationType,modelPath,numOfClasses);
        //this->controller->classify(selectedClouds,classificationType);
    }else{
        qDebug()<<"SELECT CLASSIFICATION MODEL !";
    }

}
*/
void MainWindow::classify(){
    QList<QTreeWidgetItem*> selectedClouds=ui->treeWidget->selectedItems();
    std::string modelPath=ui->classificationModel_lineEdit->text().toStdString();
    int numOfClasses=ui->numberOfClasses_spinBox_17->value();
    if(modelPath!=""){
        std::shared_ptr<ClassificationType> classificationType = getClassificationType();
        std::shared_ptr<SegmentationType> segmentationType = getSegmentationType();
        std::shared_ptr<ProjectionType> projectionType = getProjectionType();
        std::shared_ptr<EditType> editType = getEditType();
        this->threadController->classify(this->controller,selectedClouds,classificationType,segmentationType,projectionType
                                         ,editType,modelPath,numOfClasses);
        //this->controller->classify(selectedClouds,classificationType);
    }else{
        qDebug()<<"SELECT CLASSIFICATION MODEL !";
    }
}
void MainWindow::benchmark(){
    QList<QTreeWidgetItem*> selectedClouds=ui->treeWidget->selectedItems();
    std::shared_ptr<BoundingBoxType> boundingBox;
    std::shared_ptr<BenchmarkType> benchmarkType;

    std::string benchmarkFileFolder=ui->benchmarkSaveFolder_lineEdit->text().toStdString();
    benchmarkType=getBenchmarkType();
    /*
    //we set benchmarkType for a cloud here (before optional classification), so we can see live classNames updates (not only class IDs) in view
    this->controller->setBenchmarkType(selectedClouds,benchmarkType);
    */
    //by default we classify then benchmark, but if user pressed classify buton manually before, we can skip this proces now
    if(!this->ui->dontClassify_checkBox->isChecked()){
        classify();
    }


    this->threadController->benchmark(this->controller,selectedClouds,benchmarkType,benchmarkFileFolder);
}
void MainWindow::on_actionsave_selected_clouds_triggered()
{
    QList<QTreeWidgetItem*> selectedClouds=ui->treeWidget->selectedItems();
    QString saveFolder="";
    std::shared_ptr<SaveConditions> saveConditions=nullptr;
    SaveSettings saveSettings(this);
    bool accepted=0;
    accepted=saveSettings.exec();

    if(accepted){
        saveConditions=saveSettings.getSaveConditions();
        saveFolder=saveSettings.getSavePath();
        this->controller->saveClouds(selectedClouds,saveFolder,saveConditions);
    }

    /*
    saveFolder=QFileDialog::getExistingDirectory(this,tr("Select clouds save folder"),"/home/");
    this->controller->saveClouds(selectedClouds,saveFolder);
    */
}
void MainWindow::on_actionload_clouds_triggered()
{
    QString loadCloudsFile="";
    loadCloudsFile=QFileDialog::getOpenFileName(this,tr("Select folder with clouds to load"),"/home/",tr("(*.txt)"));
    this->controller->loadClouds(loadCloudsFile);
}

void MainWindow::on_actionMemory_triggered()
{

    bool accepted=0;
    accepted=memorySettings->exec();

    if(accepted){
        this->controller->setCachedCloudsMemoryLimit(memorySettings->getMemoryLimit());
    }
}
//////////////////////Prepare tab /////////////////
std::shared_ptr<PrepareDatasetFrom3D> MainWindow::getPrepareDatasetFrom3DType(){
    std::shared_ptr<PrepareDatasetFrom3D> prepareDatasetType;
    switch(ui->preparedImageType_comboBox->currentIndex()){
    //binary
    case 0:
    {
        prepareDatasetType = std::make_shared<PrepareBinaryImages>(/*TOTAL_PROJECTIONS*/ui->prepareTotalProj_spinBox_18->value()
                                                                   , /*START_DEGREE*/ui->prepareHorStartDeg_doubleSpinBox_11->value()
                                                                   , /*END_DEGREE*/ui->prepareHorEndDeg_doubleSpinBox_12->value()
                                                                   , /*START_v*/ui->prepareVertStartDeg_doubleSpinBox_13->value()
                                                                   , /*END_v*/ui->prepareVertEndDeg_doubleSpinBox_14->value()
                                                                   , /*N_v*/ui->prepareNumOfVertViews_spinBox_19->value());
        break;
    }
    //range image
    case 1:
    {
        prepareDatasetType = std::make_shared<PrepareRangeImages>(/*TOTAL_PROJECTIONS*/ui->prepareTotalProj_spinBox_18->value()
                                                                  , /*START_DEGREE*/ui->prepareHorStartDeg_doubleSpinBox_11->value()
                                                                  , /*END_DEGREE*/ui->prepareHorEndDeg_doubleSpinBox_12->value()
                                                                  , /*START_v*/ui->prepareVertStartDeg_doubleSpinBox_13->value()
                                                                  , /*END_v*/ui->prepareVertEndDeg_doubleSpinBox_14->value()
                                                                  , /*N_v*/ui->prepareNumOfVertViews_spinBox_19->value());
        break;
    }
    default:
    {
        qDebug()<<"No such PrepareDatasetFrom3D type defined, select different";
        return nullptr;
    }
    }
    return prepareDatasetType;
}
void MainWindow::prepareFrom3D(){

    std::shared_ptr<PrepareDatasetFrom3D> prepareDatasetType=getPrepareDatasetFrom3DType();
    this->threadController->prepareFrom3D(this->prepareDatasetController,prepareDatasetType);
}
//EXTRACT single instances
/**
 * @brief MainWindow::getClassesIDsToExtract, Optionaly set what classes we want to take into account (based on clouds parent folders names),
 *  if user doesn give any classes (empty "prepareClsOfInterest_lineEdit") all cloud files will be taken into account
 * classes should be seperated by ";" in "prepareClsOfInterest_lineEdit"
 * @return
 */
std::vector<std::string> MainWindow::getClassesIDsToExtract(){
    QStringList qSList= this->ui->prepareClsOfInterest_lineEdit->text().split(";",QString::SkipEmptyParts);
    std::vector<std::string> vecOfStr={};
    for(auto &element:qSList){
        vecOfStr.push_back(element.toStdString());
    }
    return vecOfStr;
}
std::shared_ptr<ExtractObjectsInstances> MainWindow::getExtractInstancesType(){
    std::shared_ptr<SegmentationType> sType=std::make_shared<EuclideanClustering>(/*segRadius*/ui->prepareEuclideanCluSegRadius_doubleSpinBox->value()
                                                                                  ,/*minClusterSize*/ui->prepareEuclideanCluMinClusterSize_spinBox->value()
                                                                                  ,/*maxClusterSize*/ui->prepareEuclideanCluMaxClusterSize_spinBox->value());
    std::shared_ptr<ExtractObjectsInstances> extractObjectsInstancesType = std::make_shared<ExtractObjectsInstances>(
                /*segmentation type = euclidean clustering*/sType,
                /*source path ->default value ->actual value is set in "prepareDatasetController" when user
                 * has chosen item in  prepare qTreeWidget*/"",
                /*destination path ->default value -> -||-*/"");
    extractObjectsInstancesType->setClassesOfInterest(getClassesIDsToExtract()); //optionaly set what classes we want to take into account (based on clouds parent folder name)
    return extractObjectsInstancesType;
}

void MainWindow::extractObjectsInstances(){
    std::shared_ptr<ExtractObjectsInstances> extractObjectsInstancesType = getExtractInstancesType();
    this->threadController->extractObjectsInstances(this->prepareDatasetController,extractObjectsInstancesType);
}
void MainWindow::treeCustomMenu(const QPoint & pos)
{
    QString loaded="";
    //Implement your menu here using myTreeView->itemAt(pos);
    if(this->ui->prepare_treeWidget->itemAt(pos)!=nullptr){
      //loaded=QFileDialog::getOpenFileName(this,("Select folder or cloud"), "/home/",tr("(*.pcd *.bin);;(*./)"),nullptr,QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
        loaded=QFileDialog::getExistingDirectory(this, tr("Open Directory with 3D clouds"),
                                                        "/home",
                                                        /*QFileDialog::DontUseNativeDialog  //so we can see files (not only folders) on windows
                                                        |*/ QFileDialog::DontResolveSymlinks);
      if(loaded!=""){
        this->ui->prepare_treeWidget->itemAt(pos)->setText(this->ui->prepare_treeWidget->currentColumn(),loaded);
      }
    }

}

void MainWindow::on_addPrepareTreeItem_pushButton_clicked()
{
    QTreeWidgetItem * item = new QTreeWidgetItem ((QTreeWidget*)0, QStringList{QString("right click to select folder path"),QString("right click to select folder path")});
    item->setFlags(item->flags()|Qt::ItemIsEditable);
    ui->prepare_treeWidget->insertTopLevelItem(0, item);
}

void MainWindow::on_removePrepareTreeItem_pushButton_clicked()
{
    QList<QTreeWidgetItem*> selectedItems=ui->prepare_treeWidget->selectedItems();
    for(auto item:selectedItems){
        delete item;
    }
}

void MainWindow::on_actionsave_configuration_triggered()
{
    QString selected="";
    selected=QFileDialog::getSaveFileName(this,tr("Save configuration file"),"/home/",tr("(*.txt *dat)"));
    this->config->saveConfiguration(selected);//"/home/radek/Documents/Qt5/data/configuration/configuration.txt"
}

void MainWindow::on_actionload_configuration_triggered()
{
    QString selected="";
    selected=QFileDialog::getOpenFileName(this,tr("Load configuration file"),"/home/",tr("(*.txt *dat)"));
    this->config->loadConfiguration(selected);
}





