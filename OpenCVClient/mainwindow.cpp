#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stackedWidget_ = new QStackedWidget(this);
    entryWindow_ = new EntryWindow(stackedWidget_);
    loginWindow_ = new LoginWindow(stackedWidget_);
    registrationWindow_ = new RegistrationWindow(stackedWidget_);
    photoWindow_ = new PhotoWindow(stackedWidget_);

    stackedWidget_->addWidget(entryWindow_);
    stackedWidget_->addWidget(loginWindow_);
    stackedWidget_->addWidget(registrationWindow_);
    stackedWidget_->addWidget(photoWindow_);
    stackedWidget_->setCurrentIndex(0);
    setCentralWidget(stackedWidget_);

    connect(entryWindow_,SIGNAL(signalLoginButtonClicked()),SLOT(setLoginWindow()));
    connect(entryWindow_,SIGNAL(signalRegistrationButtonClicked()),SLOT(setRegistrationWindow()));
    connect(entryWindow_,SIGNAL(signalConnectButtonClicked()),SLOT(slotConnetion()));
    connect(loginWindow_,SIGNAL(signalBackButtonClicked()),SLOT(setEntryWindow()));
    connect(registrationWindow_,SIGNAL(signalBackButtonClicked()),SLOT(setEntryWindow()));
    connect(registrationWindow_,SIGNAL(signalNextButtonClicked()),SLOT(setPhotoWindow()));
    connect(photoWindow_,SIGNAL(signalBackButtonClicked()),SLOT(setRegistrationWindow()));
    connect(photoWindow_,SIGNAL(signalNotAllPhoto()),SLOT(slotNotAllPhoto()));
    connect(photoWindow_,SIGNAL(signalRegistration()),SLOT(slotSendRegistration()));
}

void MainWindow::slotSendRegistration(){
    TCPClient_->slotSendToServerRegistration(userData,photoWindow_->getBlockPhoto());
}

void MainWindow::slotNotAllPhoto(){
    ui->statusbar->showMessage("Недостаточно фотографий", 3000);
}
void MainWindow::setEntryWindow(){
    //
    qDebug("central");
    stackedWidget_->setCurrentIndex(0);
    if(TCPClient_ != NULL){
        disconnect(TCPClient_,SIGNAL(signalRectReceived(QRect)),loginWindow_,SLOT(slotRectRecived(QRect)));
        qDebug("Rect отключён");
    }
}

void MainWindow::setPhotoWindow(){
    stackedWidget_->setCurrentIndex(3);
    photoWindow_->getCamera()->start();
    userData = registrationWindow_->getUserData();
    connect(TCPClient_,SIGNAL(signalRectReceived(QRect)),photoWindow_,SLOT(slotRectRecived(QRect)));
}

void MainWindow::setLoginWindow(){
    stackedWidget_->setCurrentIndex(1);
    loginWindow_->getCamera()->start();
    loginWindow_->getTimer()->start();
    loginWindow_->ResetTimerCnt();
    connect(TCPClient_,SIGNAL(signalRectReceived(QRect)),loginWindow_,SLOT(slotRectRecived(QRect)));
    qDebug("Окно входа");
}
void MainWindow::slotStatusLoginNo(){
    ui->statusbar->showMessage("Сервер отклонил подключение", 2000);
}

void MainWindow::setRegistrationWindow(){
    stackedWidget_->setCurrentIndex(2);
    disconnect(TCPClient_,SIGNAL(signalRectReceived(QRect)),loginWindow_,SLOT(slotRectRecived(QRect)));
    qDebug("Окно регистрации");
}
void MainWindow::slotConnetion(){
    if(entryWindow_->checkValidAddress()){
        TCPClient_ = new Client(); //Добавить чтение ip адреса из поля

        connect(TCPClient_,SIGNAL(signalLoginNo()),SLOT(slotStatusLoginNo()));
        connect(loginWindow_,SIGNAL(signalSendToServerGetRectangle(QVideoFrame)),TCPClient_,SLOT(slotSendToServerGetReactangle(QVideoFrame)));
        connect(loginWindow_,SIGNAL(signalSendToServerLogin(QVideoFrame)),TCPClient_,SLOT(slotSendToServerLogin(QVideoFrame)));
        //connect(photoWindow_,SIGNAL(signalSendToServerGetRectangle(QVideoFrame)),TCPClient_,SLOT(slotSendToServerGetReactangle(QVideoFrame)));
    }
    else{
        qDebug("Неверный адрес");
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

