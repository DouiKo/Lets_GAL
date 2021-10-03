#include "mainscn.h"
#include "ui_mainscn.h"

#include <QGraphicsDropShadowEffect>
#include <QLayout>
#include <QMouseEvent>
#include <QProcess>
#include <qdatetime.h>
#include <QSqlQuery>
#include <QSqlError>

extern QSqlQuery writeQuery;
extern QSqlQuery readQuery;

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

void MainScn::setStateToGameItem(GameItem &game,QString id){
    writeQuery.prepare("select * from gamestate where gameid = :gameid");
    writeQuery.bindValue(":gameid",id);
    writeQuery.exec();
    if(writeQuery.next()){
        game.setTime(writeQuery.value(1).toString());
        game.setState(GameItem::State(readQuery.value(2).toUInt()));
    }
}

void MainScn::setTagsToGameItem(GameItem &game,QString id){
    writeQuery.prepare("select * from tag where gameid = :gameid");
    writeQuery.bindValue(":gameid",id);
    writeQuery.exec();
    while (writeQuery.next()) {
        game.insertTagToList(writeQuery.value(1).toString());
    }
}

void MainScn::setStorageToGameItem(GameItem &game,QString id){
    writeQuery.prepare("select * from storage where gameid = :gameid");
    writeQuery.bindValue(":gameid",id);
    writeQuery.exec();
    if(writeQuery.next()){
        QString exePath = writeQuery.value(1).toString();
        QString filePath = writeQuery.value(2).toString();
        QString savePath = writeQuery.value(3).toString();
        game.setExePath(exePath);
        game.setSaveDataPath(savePath);
        game.setFloderPath(filePath);
    }
}

void MainScn::UpdataGameState(GameItem::State state, QString id)
{
    int counts = 0;
    readQuery.prepare("select runningcounts from gamestate where gameid = :gameid");
    readQuery.bindValue(":gameid",id);
    readQuery.exec();
    if(readQuery.next()){
        counts = readQuery.value(0).toUInt() + 1;
        writeQuery.prepare("update gamestate set time = :time,state = :state,runningcounts = :counts where gameid = :gameid");
        writeQuery.bindValue(":gameid",id);
        writeQuery.bindValue(":time",QDateTime::currentDateTime().toString("MM/dd hh:mm"));
        writeQuery.bindValue(":state",state);
        writeQuery.bindValue(":counts",counts);
        if(!writeQuery.exec()){
            qDebug()<<id + " could not updated state:" << writeQuery.lastError();
        }else{
            qDebug()<<id + " updated success:"  << writeQuery.lastError();
        }
    }else{
        qDebug()<<id + " could not found game:" << readQuery.lastError();
    }
}

void MainScn::initGameData()
{
    libraryModel = new QStandardItemModel(this);

    readQuery.prepare("select * from game");
    readQuery.exec();
    while (readQuery.next()) {
        QStandardItem *item = new QStandardItem();
        GameItem game;
        QString id = readQuery.value(0).toString();
        QString name = readQuery.value(1).toString();
        game.setId(id);
        game.setName(name);

        setStorageToGameItem(game,id);
        setTagsToGameItem(game,id);
        setStateToGameItem(game,id);

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
//    qDebug()<<item.getName()<<item.getExePath();
    this->showMinimized();
    //step1
    if(openExeFromPath(item.getExePath(),item.getFloderPath())){
        qDebug()<<QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss") + item.getName() + " success!";
        UpdataGameState(GameItem::State::Running,item.getId());
        //step2
    }else{
        //error
        qDebug()<<QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss") + item.getName() + " failed!";
    }
}

bool MainScn::openExeFromPath(QString exePath,QString floderPath)
{
    if(!exePath.isEmpty()){
        QProcess process;
        qint64 *processid = new qint64;
        process.startDetached(exePath,QStringList(),floderPath,processid);
        qDebug()<<*processid;
        qDebug()<<process.exitStatus();
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
