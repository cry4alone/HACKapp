#include "registrationwindow.h"
#include "ui_registrationwindow.h"

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QWidget(parent),
    rUi(new Ui::RegistrationWindow)
{
    rUi->setupUi(this);
    connect(rUi->backButton,SIGNAL(clicked()),SIGNAL(signalBackButtonClicked()));
    connect(rUi->nextButton,SIGNAL(clicked()),SIGNAL(signalNextButtonClicked()));
}

UserData* RegistrationWindow::getUserData(){
    UserData* usData = new UserData();
    usData->lastName_ = rUi->LineLastName->text();
    usData->firstName_ = rUi->LineFirstName->text();
    usData->middleName_ = rUi->LineMiddleName->text();
    usData->phone_ = rUi->LinePhone->text();
    return usData;
}

RegistrationWindow::~RegistrationWindow()
{
    delete rUi;
}
