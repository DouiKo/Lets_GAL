#include "addgamedialog.h"
#include "ui_addgamedialog.h"

AddGameDialog::AddGameDialog(QString path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGameDialog)
{
    ui->setupUi(this);
    findGameEXE(findFileFromFilter(path,"*.exe"));
    findFloder(path);
    initGameMessage();
}

AddGameDialog::~AddGameDialog()
{
    delete ui;
}

QFileInfoList AddGameDialog::findFileFromFilter(const QString &strFilePath, const QString &strNameFilters)
{
    QFileInfoList fileList;
    QDir dir;
    QStringList filters;
    filters << strNameFilters;
    dir.setPath(strFilePath);
    dir.setNameFilters(filters);
    QDirIterator iter(dir,QDirIterator::Subdirectories);
    while (iter.hasNext())
    {
        iter.next();
        QFileInfo info=iter.fileInfo();
        if (info.isFile())
        {
            fileList.append(info);
        }
    }
    return fileList;
}

void AddGameDialog::findFloder(const QString &strFilePath)
{
    QDir dir;
    dir.setPath(strFilePath);
    foreach (auto var, dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        if(var.fileName().contains("save")){
            savePath = var.filePath();
        }
    }
}

void AddGameDialog::findGameEXE(QFileInfoList fileList)
{
    if(!fileList.isEmpty()){
        foreach (auto var, fileList) {
            exeMap[var.fileName()] = var.filePath();
            if(var.fileName().contains("chs") || var.fileName().contains("CHS") || var.fileName().contains("汉化")){
                chsEXE = var.fileName();
            }
        }
    }
}

void AddGameDialog::initGameMessage()
{
    QStringList list = exeMap.values().first().split("/");
    ui->lineEditName->setText(list.value(list.size()-2));
    for (int i = 0; i < exeMap.size(); ++i) {
        ui->comboBoxEXE->addItem(exeMap.keys().value(i));
    }
    ui->comboBoxEXE->setCurrentText(chsEXE);
    ui->lineEditSaveData->setText(savePath);
}

void AddGameDialog::on_pushButtonCancel_clicked()
{
    this->close();
}

void AddGameDialog::on_pushButtonConfirm_clicked()
{

}
