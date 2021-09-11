#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>
#include <QSplashScreen>

namespace Ui {
class SplashScreen;
}

class SplashScreen : public QSplashScreen
{
    Q_OBJECT

public:
    explicit SplashScreen(QString filePath,QWidget *parent = nullptr);
    ~SplashScreen();

private:
    Ui::SplashScreen *ui;
};

#endif // SPLASHSCREEN_H
