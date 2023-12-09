#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QMessageBox>

namespace Ui {
class EntryWindow;
}

class EntryWindow : public QWidget
{
Q_OBJECT

public:
    explicit EntryWindow(QWidget *parent = nullptr);
    ~EntryWindow();
    bool checkValidAddress();
private:
    Ui::EntryWindow *eUi;
    bool AddressIsValid = false;
signals:
    void signalLoginButtonClicked();
    void signalRegistrationButtonClicked();
    void signalConnectButtonClicked();
};

#endif // ENTRYWINDOW_H
