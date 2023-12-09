#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QVideoWidget>
#include <QMediaDevices>
#include <QVideoFrame>
#include <QImageCapture>
#include <QVideoSink>
#include <QImage>
#include <QVideoFrameFormat>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QRectF>
#include <QTimer>
#include <QStatusBar>
#include "Global.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    QCamera* getCamera();
    QTimer* getTimer();
    void ResetTimerCnt();

private:
    Ui::LoginWindow *lUi;
    QVideoWidget* videoWidget_;
    QVideoSink* videoSinkWidget_;
    QVideoSink* videoSinkCamera_;
    QMediaCaptureSession* captureSession_;
    QCamera* camera_;
    QTimer* timer_;
    int TimerCnt = 0;
    bool rectIsCorrect = false;
    QRect lastRect;
    QVideoFrame lastFrame;
signals:
    void signalBackButtonClicked();
    void signalSendToServerGetRectangle(QVideoFrame frame);
    void signalSendToServerLogin(QVideoFrame frame);
public slots:
    void slotFrameChanged(QVideoFrame frame);
    void slotBackButtonClicked();
    void slotRectRecived(QRect rectangle);
    void slotTimerCheck();
};

#endif // LOGINWINDOW_H
