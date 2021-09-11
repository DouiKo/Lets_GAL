#include "splashscreen.h"
#include "ui_splashscreen.h"

#include <QImageReader>
#include <QDir>
#include <QDebug>
#include <QTime>

SplashScreen::SplashScreen(QString filePath, QWidget *parent) :
    QSplashScreen(parent),
    ui(new Ui::SplashScreen)
{
    ui->setupUi(this);
    this->layout()->setMargin(0);
    ui->label->setBackgroundRole(QPalette::Base);
    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label->setScaledContents(true);
    ui->label->adjustSize();

    if(!filePath.isEmpty()){
        QDir dir(filePath);
        QStringList fileFilter;
        fileFilter << "*.jpg" << "*.png" << "*.gif";
        QFileInfoList fileList = dir.entryInfoList(fileFilter);
        if(!fileList.isEmpty()){
            qsrand(QTime::currentTime().msec()+QTime::currentTime().second()*1000);
            int i = qrand()%fileList.size();
            QImageReader reader(fileList.value(i).filePath());
            reader.setAutoTransform(true);
            const QImage newImage = reader.read();
            if(!newImage.isNull()){
                QSize imageSize = newImage.size();
                while (imageSize.width() > 700 || imageSize.height() > 700) {
                    imageSize = imageSize * 0.7;
                }
                this->resize(imageSize);
                ui->label->setPixmap(QPixmap::fromImage(newImage));
            }
        }
    }



}

SplashScreen::~SplashScreen()
{
    delete ui;
}
