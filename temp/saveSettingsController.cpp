#include "saveSettingsController.h"

SaveSettingsController::SaveSettingsController()
{

}
bool SaveSettingsController::isAmongClasses(CloudComponent *cloud){
    QStringList classesIDs;
    const QString cloudID=QString::number(cloud->getCloudID());
    classesIDs=saveSettings->getClassesIDs();

    return classesIDs.contains(cloudID);
}
