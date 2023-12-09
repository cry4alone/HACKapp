#include "entrywindow.h"
#include "ui_entrywindow.h"

EntryWindow::EntryWindow(QWidget *parent) :
    QWidget(parent),
    eUi(new Ui::EntryWindow)
{
    eUi->setupUi(this);
    connect(eUi->loginButton,SIGNAL(clicked()),SIGNAL(signalLoginButtonClicked()));
    connect(eUi->registrationButton, SIGNAL(clicked()),SIGNAL(signalRegistrationButtonClicked()));
    connect(eUi->connectButton,SIGNAL(clicked()), SIGNAL(signalConnectButtonClicked()));
}
//void EntryWindow::openLoginWindow(){
//    if(checkValidAddress()){
//        qDebug("Good login");
//        emit signalLoginButtonClicked();
//    }
//    else{
//        QMessageBox::critical(this,"Ошибка","Неверно указан ip адрес");
//    }
//}

//void EntryWindow::openRegistrationWindow(){
//    if(checkValidAddress()){
//      qDebug("Good registration");
//      emit signalRegistrationButtonClicked();
//    }
//    else{
//        QMessageBox::critical(this,"Ошибка","Неверно указан ip адрес");
//    }
//}

bool EntryWindow::checkValidAddress(){
    return true;
}


EntryWindow::~EntryWindow()
{
    delete eUi;
}
