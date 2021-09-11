#ifndef ADDGAMEDIALOG_H
#define ADDGAMEDIALOG_H

#include <QDialog>
#include <QFileInfoList>
#include <QDir>
#include <QDirIterator>
#include <QtDebug>

namespace Ui {
class AddGameDialog;
}

class AddGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddGameDialog(QString path,QWidget *parent = nullptr);
    ~AddGameDialog();

private slots:
    void on_pushButtonCancel_clicked();

    void on_pushButtonConfirm_clicked();

private:
    QString savePath;
    QString chsEXE;
    QMap<QString,QString>exeMap;
    Ui::AddGameDialog *ui;
    QFileInfoList findFileFromFilter(const QString &strFilePath, const QString &strNameFilters);
    void findGameEXE(QFileInfoList fileList);
    void initGameMessage();
    void findFloder(const QString &strFilePath);
};

#endif // ADDGAMEDIALOG_H
