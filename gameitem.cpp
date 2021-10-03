#include "gameitem.h"

GameItem::GameItem()
{

}

QString GameItem::getName() const
{
    return name;
}

void GameItem::setName(const QString &value)
{
    name = value;
}

QString GameItem::getTime() const
{
    if(time.isEmpty())return "未启动";
    return time;
}

void GameItem::setTime(const QString &value)
{
    time = value;
}

QStringList GameItem::getTagList() const
{
    return tagList;
}

void GameItem::insertTagToList(const QString &tag)
{
    tagList.append(tag);
}

void GameItem::setTagList(const QStringList &value)
{
    tagList = value;
}

QString GameItem::getTagsString() const
{
    QString tags = "";
    foreach (auto var, tagList) {
        if(!tags.isEmpty())tags.append("/");
        tags.append(var);
    }
    return tags;
}

QPixmap GameItem::getIcon() const
{
    return icon;
}

QString GameItem::getExePath() const
{
    return exePath;
}

void GameItem::setExePath(const QString &value)
{
    exePath = value;
    QFileInfo fileInfo(exePath);
    QFileIconProvider seekIcon;
    QIcon image = seekIcon.icon(fileInfo);
    icon = image.pixmap(QSize(32,32));
}

GameItem::State GameItem::getState() const
{
    return currentState;
}

void GameItem::setState(GameItem::State state)
{
    currentState = state;
}

double GameItem::getRunningTime() const
{
    return runningTime;
}

void GameItem::setRunningTime(double value)
{
    runningTime = value;
}

QString GameItem::getSaveDataPath() const
{
    return saveDataPath;
}

void GameItem::setSaveDataPath(const QString &value)
{
    saveDataPath = value;
}

QString GameItem::getFloderPath() const
{
    return filePath;
}

void GameItem::setFloderPath(const QString &value)
{
    filePath = value;
}

QString GameItem::getId() const
{
    return id;
}

void GameItem::setId(const QString &value)
{
    id = value;
}
