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

QString GameItem::getFilePath() const
{
    return filePath;
}

void GameItem::setFilePath(const QString &value)
{
    filePath = value;
    QFileInfo fileInfo(filePath);
    QFileIconProvider seekIcon;
    QIcon image = seekIcon.icon(fileInfo);
    icon = image.pixmap(QSize(32,32));
}
