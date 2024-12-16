#include "dirpaths.h"
#include "mainwindow.h"

DirPaths::DirPaths() {}

DirStruct DirPaths::buildDirPaths(MainWindow *mainWindow) {
    DirStruct dir;
    dir.today = mainWindow->getUi()->dateProcessing->date();
    dir.dateString = dir.today.toString("yyyy-MM-dd");
    dir.logDate = dir.today.toString("MM/dd/yy");
    dir.yearString = dir.today.toString("yyyy");
    dir.homeDirPath = qgetenv("USERPROFILE") + "/";
    dir.homeDirPath = dir.homeDirPath.replace("\\", "/");
    dir.LTspiceDevelopmentDirPath = dir.homeDirPath + mainWindow->getUi()->lineEditLTspiceDevelopment->text() + "/";
    dir.modelsDirPath = dir.LTspiceDevelopmentDirPath + "Models" + "/";
    dir.ecsDirPath = dir.modelsDirPath + "ECS" + "/";
    dir.libDirPath = dir.modelsDirPath + "lib" + "/";
    dir.subDirPath = dir.libDirPath + "sub" + "/";
    dir.symDirPath = dir.libDirPath + "sym" + "/";
    dir.examplesDirPath = dir.modelsDirPath + "examples" + "/";
    dir.applicationsDirPath = dir.examplesDirPath + "Applications" + "/";
    dir.applicationsBckDirPath = dir.applicationsDirPath + "BAK" + "/" + dir.yearString + "/";
    dir.newModelsDir = dir.modelsDirPath + "NewModels" + "/";
    dir.todayYearPath = dir.newModelsDir + dir.yearString + "/";
    dir.todayDirPath = dir.todayYearPath + dir.dateString + "/";
    dir.sharePointPath = mainWindow->getUi()->comboBoxSharePoint->currentText() + "/";
    dir.jsonFilePath = dir.todayDirPath + "devices.json";
    dir.jsonSharePointFilePath = dir.todayDirPath + "sharePoint.json";
    dir.toProcessDirPath = dir.modelsDirPath + mainWindow->getUi()->lineEditFilesToProcess->text() + "/";
    dir.toProcessLibPath = dir.toProcessDirPath + "lib" + "/";
    dir.toProcessExamplesPath = dir.toProcessDirPath  + "examples" + "/";
    dir.toSendDirPath = dir.modelsDirPath + mainWindow->getUi()->lineEditFilesToSend->text() + "/";
    dir.toSendFilesDirPath = dir.toSendDirPath + "files" + "/";
    dir.toSendLibDirPath = dir.toSendFilesDirPath + "lib" "/";
    dir.toSendExamplesPath = dir.toSendFilesDirPath + "examples" "/";
    dir.LTspiceExeFilePath = dir.modelsDirPath + "LTspice.exe";
    dir.encryptExeFilePath = dir.modelsDirPath + "encrypt.exe";
    dir.toSendLTspiceExeFilePath = dir.toSendDirPath + "LTspice.exe";
    dir.examplesDirPath = dir.modelsDirPath + "examples" + "/";
    dir.applicationsDirPath; dir.examplesDirPath + "Applications" + "/";
    dir.bckDirPath = dir.modelsDirPath + "BAK" + "/" + dir.yearString + "/";
    dir.yearBckDirPath = dir.bckDirPath + dir.yearString + "/";
    dir.sourceDirPath = mainWindow->getUi()->comboBoxSharePoint->currentText() + "/" + "Source" +"/";
    dir.sourceLibDirPath = dir.sourceDirPath + "lib" + "/";
    dir.sourceLibSubPath = dir.sourceLibDirPath + "sub" + "/";
    dir.sourceLibSymPath = dir.sourceLibDirPath + "sym" + "/";
    dir.sourceLibECSPath = dir.sourceLibDirPath + "ECS" + "/";
    dir.sourceExamplesLibPath = dir.sourceDirPath + "examples" + "/";
    dir.sourceApplicationsPath = dir.sourceExamplesLibPath + "Applications" + "/";
    dir.LTspiceJsonForAkamai = dir.modelsDirPath + "LTspice.json";
    dir.changeLogPath = dir.modelsDirPath + "ChangeLog.txt";
    dir.changeLogBckPath = dir.yearBckDirPath + "ChangeLog.txt" + "-" + dir.dateString;
    dir.LTspiceExeToSendPath = dir.toSendDirPath + "LTspice.exe";
    dir.dbPath = dir.modelsDirPath + "LTspice.db";



    return dir;
}
