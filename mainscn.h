#ifndef MAINSCN_H
#define MAINSCN_H

#include <QWidget>
#include "gameitem.h"
#include <QFileDialog>
#include <addgamedialog.h>
#include "itemdelegate.h"
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainScn; }
QT_END_NAMESPACE

class MainScn : public QWidget
{
    Q_OBJECT

public:
    MainScn(QWidget *parent = nullptr);
    ~MainScn();

private slots:
    void on_pushButtonMini_clicked();

    void on_pushButtonMaxAndNormal_clicked(bool checked);

    void on_pushButtonClose_clicked();

    void on_pushButtonFloder_clicked();

    void on_radioButtonLibrary_clicked();

    void on_radioButtonAddGame_clicked();

    void on_listViewLibrary_doubleClicked(const QModelIndex &index);

private:
    //初始化
    void initWindowEffect();

    void setWindowToShawdow(bool isShow);

    void initListViewLibrary();

    void initGameData();

    //数据库操作
    void setStateToGameItem(GameItem &game, QString id);

    void setTagsToGameItem(GameItem &game, QString id);

    void setStorageToGameItem(GameItem &game, QString id);

    void UpdataGameState(GameItem::State state,QString id);

    //游戏操作
    void startGameFromItem(GameItem item);



    //文件操作
    bool openExeFromPath(QString path, QString floderPath);

private:
    QStandardItemModel *libraryModel;
    AddGameDialog *addGame;
    QPoint oldPos;
    bool press;
    Ui::MainScn *ui;
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
};
#endif // MAINSCN_H
