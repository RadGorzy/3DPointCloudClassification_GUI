#include "src/view/saveSettings.h"
#include "ui_saveSettings.h"

SaveSettings::SaveSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveSettings)
{
    ui->setupUi(this);
    saveConditions=std::make_shared<SaveConditions>();
}

SaveSettings::~SaveSettings()
{
    delete ui;
}
QString SaveSettings::getSavePath(){
    return this->savePath;
}
void SaveSettings::on_pushButton_2_clicked()
{
     reject();
}

void SaveSettings::on_save_pushButton_clicked()
{
    savePath=QFileDialog::getExistingDirectory(this,tr("Select clouds save folder"),"/home/");
    if(this->ui->clsIDs_lineEdit->text()!=""){
        addCondition(std::bind(&SaveSettings::isAmongClasses, this, std::placeholders::_1));
    }
    if(this->ui->nnRespon_doubleSpinBox->value()>0){
        addCondition(std::bind(&SaveSettings::hasNnResponseStrengthBiggerEqualThan, this, std::placeholders::_1));
    }
    if(this->ui->cloudSize_spinBox->value()>0){
        addCondition(std::bind(&SaveSettings::hasNumOfPointsBiggerEqualThan, this, std::placeholders::_1));
    }
    accept();
}
QStringList SaveSettings::getClassesIDs(){
    return this->ui->clsIDs_lineEdit->text().split(classesSeparator,QString::SkipEmptyParts);
}
float SaveSettings::getMinNnResponseStrength(){
    return static_cast<float>(this->ui->nnRespon_doubleSpinBox->value());
}
uint SaveSettings::getMinNumOfPoints(){
    return static_cast<uint>(this->ui->cloudSize_spinBox->value());
}
void SaveSettings::addCondition(std::function<bool(CloudComponent*)> condition){
    this->saveConditions->addCondition(condition);
}
std::shared_ptr<SaveConditions> SaveSettings::getSaveConditions(){
    if(this->saveConditions->getNumberOfConditions()>0){
        return this->saveConditions;
    }
    //if no conditions were added we pass nullptr to let the caller know that there's no need for conditions evaluation
    else
    {
        return nullptr;
    }
}
//Conditions: //
bool SaveSettings::isAmongClasses(CloudComponent *cloud){
    QStringList classesIDs;
    const QString cloudClassID=QString::number(cloud->getCloudClassID()); //# musze wiec zaincludowac pointCloud.h -> ale wtedy znowu bug ze na szaro saveSettings.h ->pewnie zapetlenie
    classesIDs=getClassesIDs();

    return classesIDs.contains(cloudClassID);
}
bool SaveSettings::hasNnResponseStrengthBiggerEqualThan(CloudComponent* cloud){
     float max_response=0;
     std::vector<float> responseVector=cloud->getNNResopneVector();
     std::vector<float>::iterator iterToMaxResponse;
     iterToMaxResponse=std::max_element(responseVector.begin(),responseVector.end());
     // if range is empty
     if(iterToMaxResponse==responseVector.end()){
         return false;
     }

     max_response=*iterToMaxResponse;
     if(max_response >= getMinNnResponseStrength()){
         return true;
     }
     else{
         return false;
     }
}
bool SaveSettings::hasNumOfPointsBiggerEqualThan(CloudComponent* cloud){
    if(cloud->getCloudSize()>=getMinNumOfPoints()){
        return true;
    }else{
        return false;
    }
}
