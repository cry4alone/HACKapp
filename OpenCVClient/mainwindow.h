#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "UserData.h"
#include <QHBoxLayout>
#include <QMetaType>
#include <QMainWindow>
#include <QCameraFormat>
#include <QVideoFrameFormat>
#include "entrywindow.h"
#include "loginwindow.h"
#include "registrationwindow.h"
#include "photowindow.h"
#include "Client.h"
#include <QStackedWidget>
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStackedWidget* stackedWidget_;
    EntryWindow* entryWindow_;
    LoginWindow* loginWindow_;
    RegistrationWindow* registrationWindow_;
    PhotoWindow* photoWindow_;
    Client* TCPClient_;
    UserData* userData;

public slots:
    void setLoginWindow();
    void setRegistrationWindow();
    void setEntryWindow();
    void setPhotoWindow();
    void slotConnetion();
    void slotStatusLoginNo();
    void slotNotAllPhoto();
    void slotSendRegistration();
};
#endif // MAINWINDOW_H
