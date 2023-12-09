#ifndef CLIENT_H
#define CLIENT_H
#include <QRect>
#include <QWidget>
#include <QtWidgets>
#include <QTcpSocket>
#include <QVideoFrame>
#include <QBuffer>
#include <QByteArray>
#include <QDataStream>
#include <QVBoxLayout>
#include <QString>
#include <QPixmap>
#include "UserData.h"

class Client : public QWidget
{
Q_OBJECT
public:
    Client(QWidget* = 0);
private:
    QTcpSocket* TcpSocket;
    quint16 BlockSize = 0;
public slots:
    void slotSendToServerGetReactangle(QVideoFrame frame);
    void slotSendToServerLogin(QVideoFrame frame);
    void slotSendToServerRegistration(UserData* userData, QByteArray BlockImages);
    void slotReadyRead();
signals:
    void signalRectReceived(QRect rectangle);
    void signalLoginNo();
};
#endif // CLIENT_H
