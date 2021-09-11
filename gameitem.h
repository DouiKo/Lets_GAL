#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QString>
#include <QStringList>
#include <QMetaType>
#include <QPixmap>
#include <QFileInfo>
#include <QFileIconProvider>

class GameItem
{
public:
    GameItem();

    QString getName() const;
    void setName(const QString &value);

    QString getTime() const;
    void setTime(const QString &value);

    QStringList getTagList() const;
    void insertTagToList(const QString &tag);
    void setTagList(const QStringList &value);

    QString getTagsString() const;

    QPixmap getIcon() const;

    QString getFilePath() const;
    void setFilePath(const QString &value);

private:
    QPixmap icon;
    QString filePath;
    QString name;
    QString time;
    QStringList tagList;
};

Q_DECLARE_METATYPE(GameItem)

#endif // GAMEITEM_H
