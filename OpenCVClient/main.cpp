#include "mainwindow.h"
#include "Client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    //Client client;
    //client.show();
    return a.exec();
}
