#include "Client.h"
void Client::slotReadyRead(){
    QDataStream in(TcpSocket);
    for(;;){
        if(!BlockSize)
        {
            if(TcpSocket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> BlockSize;
        }

        if (TcpSocket->bytesAvailable() < BlockSize)
        {
            break;
        }

        QString TypeOfRequest;
        QRect rect;
        in >> TypeOfRequest;

        if(TypeOfRequest == "SET-RECTANGLE"){
            in >> rect;
            emit signalRectReceived(rect);
        }
        else if(TypeOfRequest == "LOGIN-NO"){
            emit signalLoginNo();
        }

        BlockSize = 0;
    }
}
Client::Client(QWidget* parent) : QWidget(parent)
{
    TcpSocket = new QTcpSocket(this);
    TcpSocket->connectToHost("localhost", 8800);
    connect(TcpSocket,SIGNAL(readyRead()),SLOT(slotReadyRead()));
}

void Client::slotSendToServerGetReactangle(QVideoFrame frame)
{
    qDebug("Попытка определить положение лица");
    QByteArray Block;
    QBuffer buffer(&Block);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    out<<quint16(0);
    out<<QString("GET-RECTANGLE");
    if(!frame.map(QVideoFrame::ReadOnly))
        qDebug("Ошибка getRect");
    QImage img = frame.toImage();
    img.save(&buffer,"JPG");
    buffer.seek(0);
    out<<quint16(Block.size()-sizeof(quint16));
    TcpSocket->write(Block);
    buffer.close();
    frame.unmap();
}

void Client::slotSendToServerLogin(QVideoFrame frame){
    qDebug("Поптыка логина");
    QByteArray Block;
    QBuffer buffer(&Block);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    out<<quint16(0);
    out<<QString("LOGIN");
    frame.map(QVideoFrame::ReadOnly);
    QImage img = frame.toImage();
    img.save(&buffer,"JPG");
    buffer.seek(0);
    out<<quint16(Block.size()-sizeof(quint16));
    TcpSocket->write(Block);
    buffer.close();
    frame.unmap();
}

void Client::slotSendToServerRegistration(UserData* userData, QByteArray BlockImages){
    QByteArray Block;
    QBuffer buffer(&Block);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    out<<quint16(0);
    out<<QString("REGISTRATION");
    out<<userData->lastName_;
    out<<userData->firstName_;
    out<<userData->middleName_;
    out<<userData->phone_;
    Block.append(BlockImages);
    buffer.seek(0);
    out<<quint16(Block.size()-sizeof(quint16));
    TcpSocket->write(Block);
    buffer.close();
}
