#include "mainscn.h"
#include "ui_mainscn.h"

#include <QGraphicsDropShadowEffect>
#include <QLayout>
#include <QMouseEvent>
#include <QProcess>
#include <qdatetime.h>

MainScn::MainScn(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainScn)
{
    ui->setupUi(this);
    initWindowEffect();
    initGameData();

}

MainScn::~MainScn()
{
    delete ui;
}

void MainScn::on_pushButtonMini_clicked()
{
    this->showMinimized();
}

void MainScn::on_pushButtonMaxAndNormal_clicked(bool checked)
{
    if(checked){
        setWindowToShawdow(false);
        this->showMaximized();
    }else{
        setWindowToShawdow(true);
        this->showNormal();
    }
}

void MainScn::on_pushButtonClose_clicked()
{
    this->close();
}

//caution:该方法设置无边框及阴影会导致最大化情况下性能消耗极大
//测试环境:AMD 1600x
//不使用QGraphicsDropShadowEffect,程序默认大小运行占用率最高3%,无体感卡顿
//应用QGraphicsDropShadowEffect,程序默认大小运行占用率最高5%,无体感卡顿
//应用QGraphicsDropShadowEffect,程序最大化大小运行占用率最高10%,明显卡顿
void MainScn::initWindowEffect()
{
    setAttribute(Qt::WA_TranslucentBackground,true);
    setWindowFlag(Qt::WindowType::FramelessWindowHint);
    setWindowToShawdow(true);
    ui->radioButtonLibrary->setChecked(true);
}

void MainScn::setWindowToShawdow(bool isShow)
{
    if(isShow){
        QGraphicsDropShadowEffect *effectShadow = new QGraphicsDropShadowEffect(this);
        effectShadow->setOffset(0, 0);
        effectShadow->setColor("#afafaf");
        effectShadow->setBlurRadius(30);
        ui->widget->setGraphicsEffect(effectShadow);
        this->layout()->setMargin(30);
    }else{
        ui->widget->setGraphicsEffect(nullptr);
        this->layout()->setMargin(0);
    }
}

void MainScn::initListViewLibrary()
{
    ui->listViewLibrary->setItemDelegate(new ItemDelegate());
    ui->listViewLibrary->setModel(libraryModel);
//    ui->listViewLibrary->setViewMode(QListView::IconMode);
    ui->listViewLibrary->setDragEnabled(false);
    ui->listViewLibrary->setEditTriggers(QListView::NoEditTriggers);
    //connect(ui->listViewLibrary,&QListView::mousePressPos,this,&Widget::onMousePressPos);
}

void MainScn::initGameData()
{
    libraryModel = new QStandardItemModel(this);

    for (int i = 0; i < 500; ++i) {
        QStandardItem *item = new QStandardItem();
        GameItem game;
        game.setName("千恋万花" + QString::number(i));
        game.setTime("09/05 22:26");
        game.insertTagToList("纯爱");
        game.insertTagToList("日常");
        game.insertTagToList("柚子");
        game.setFilePath("C:/Users/29856/AppData/Local/Programs/aDrive/aDrive.exe");
        QVariant variant = QVariant::fromValue(game);
        item->setData(variant,Qt::UserRole+1);
        libraryModel->appendRow(item);
    }
    initListViewLibrary();
}

//游戏启动步骤:
//step1.最小化程序
//step2.启动可执行文件
//step3.更新数据库游戏最后启动时间
void MainScn::startGameFromItem(GameItem item)
{
    qDebug()<<item.getName()<<item.getFilePath();
    this->showMinimized();
    //step1
    if(openExeFromPath(item.getFilePath())){
        //step2
    }else{
        //error
        qDebug()<<QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss") + item.getName() + "启动失败";
    }
}

bool MainScn::openExeFromPath(QString path)
{
    if(!path.isEmpty()){
        QProcess process;
        process.startDetached(path);
        return process.error() == QProcess::UnknownError ? true  :  false;
    }
    return false;
}

void MainScn::mouseMoveEvent(QMouseEvent *event)
{
    if (press){
        this->move(this->pos() + event->globalPos() - oldPos);
        oldPos = event->globalPos();
    }
}

void MainScn::mouseReleaseEvent(QMouseEvent *e)
{
    press = false;
}

void MainScn::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        oldPos = e->globalPos();
        press = true;
    }
}

void MainScn::on_pushButtonFloder_clicked()
{
    QString filePath = QFileDialog::getExistingDirectory(this);
    if(!filePath.isEmpty()){
        addGame = new AddGameDialog(filePath,this);
        addGame->exec();
    }
}

void MainScn::on_radioButtonLibrary_clicked()
{
    ui->stackedWidgetLibrary->setCurrentIndex(1);
}

void MainScn::on_radioButtonAddGame_clicked()
{
    ui->stackedWidgetLibrary->setCurrentIndex(0);
}

void MainScn::on_listViewLibrary_doubleClicked(const QModelIndex &index)
{
    QVariant variant = index.data(Qt::UserRole + 1);
    GameItem gameData = variant.value<GameItem>();
    startGameFromItem(gameData);
}
