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
    enum State{
        NotStart = 0, //通关
        Played = 1, // 游玩过
        Running = 2,  //游玩中
        Clear = 3,  //未游玩
    };

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

    QString getExePath() const;
    void setExePath(const QString &value);

    GameItem::State getState() const;
    void setState(GameItem::State state);

    double getRunningTime() const;
    void setRunningTime(double value);

    QString getSaveDataPath() const;
    void setSaveDataPath(const QString &value);

    QString getFloderPath() const;
    void setFloderPath(const QString &value);

    QString getId() const;
    void setId(const QString &value);

private:
    QPixmap icon;
    QString exePath;
    QString filePath;
    QString id;
    QString name;
    QString time;
    QStringList tagList;
    GameItem::State currentState;
    double runningTime;
    QString saveDataPath;
};

Q_DECLARE_METATYPE(GameItem)

#endif // GAMEITEM_H
