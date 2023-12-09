#ifndef PHOTOWINDOW_H
#define PHOTOWINDOW_H
#include "Global.h"
#include "UserData.h"
#include <QWidget>
#include <QVideoWidget>
#include <QMediaCaptureSession>
#include <QCamera>
#include <QVideoSink>
#include <QRect>
#include <QMediaDevices>
#include <QVideoFrame>
#include <QLabel>

namespace Ui {
class PhotoWindow;
}

class PhotoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PhotoWindow(QWidget *parent = nullptr);
    ~PhotoWindow();
    QCamera* getCamera();
    QByteArray getBlockPhoto();

private:
    QVideoWidget* videoWidget_;
    QVideoSink* videoSinkWidget_;
    QVideoSink* videoSinkCamera_;
    QMediaCaptureSession* captureSession_;
    QCamera* camera_;
    int PhotoCounter = 0;
    QByteArray BlockPhotoSendToServer;
    bool rectIsCorrect = false;
    QRect lastRect;
    QVideoFrame lastFrame;
    Ui::PhotoWindow *pUi;
    QLabel* Counter;

    void AddPhotoToBlock(QVideoFrame frame);
    void IncrementCounter();

signals:
    void signalBackButtonClicked();
    //void signalRegistrationButtonClicked();
    void singalPhotoButtonClicked();
    void signalRegistration();
    void signalSendToServerGetRectangle(QVideoFrame frame);
    void signalNotAllPhoto();
public slots:
    void slotRegistrationButtonClicked();
    void slotFrameChanged(QVideoFrame frame);
    void slotBackButtonClicked();
    void slotRectRecived(QRect rectangle);
    void slotTakePhoto();
};

#endif // PHOTOWINDOW_H
