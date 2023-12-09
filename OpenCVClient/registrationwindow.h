#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QWidget>
#include "UserData.h"

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();
    UserData* getUserData();

private:
    Ui::RegistrationWindow *rUi;
signals:
    void signalBackButtonClicked();
    void signalNextButtonClicked();
};

#endif // REGISTRATIONWINDOW_H
