#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    lUi(new Ui::LoginWindow)
{
    lUi->setupUi(this);

    videoWidget_ = lUi->videoWid;
    videoWidget_->resize(640,480);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);
    videoSinkWidget_ = videoWidget_->videoSink();

    camera_ = new QCamera(QMediaDevices::defaultVideoInput());
    timer_ = new QTimer(this);
    timer_->setInterval(1000);

    captureSession_ = new QMediaCaptureSession;
    captureSession_->setCamera(camera_);
    videoSinkCamera_ = new QVideoSink;
    captureSession_->setVideoSink(videoSinkCamera_);

    connect(timer_,SIGNAL(timeout()),SLOT(slotTimerCheck()));
    connect(lUi->backButton,SIGNAL(clicked()),SLOT(slotBackButtonClicked()));
    connect(videoSinkCamera_,SIGNAL(videoFrameChanged(QVideoFrame)),SLOT(slotFrameChanged(QVideoFrame)));
}
void LoginWindow::ResetTimerCnt(){
    TimerCnt = 0;
}
void LoginWindow::slotRectRecived(QRect rectangle){
    if((rectangle.x() == 0) && (rectangle.y() == 0))
        rectIsCorrect = false;
    else
        rectIsCorrect = true;
    lastRect = rectangle;
}
void LoginWindow::slotTimerCheck(){
    TimerCnt++;
    if(TimerCnt > 10){
        timer_->stop();
    }
    emit signalSendToServerLogin(lastFrame);
}
void LoginWindow::slotFrameChanged(QVideoFrame frame){
    lastFrame = frame;
    PaintRectangle(frame,lastRect);
    emit signalSendToServerGetRectangle(frame);
    videoSinkWidget_->setVideoFrame(frame);
}
QTimer* LoginWindow::getTimer(){
    return timer_;
}
QCamera* LoginWindow::getCamera(){
    return camera_;
}
void LoginWindow::slotBackButtonClicked(){
    camera_->stop();
    timer_->stop();
    ResetTimerCnt();
    emit signalBackButtonClicked();
}
LoginWindow::~LoginWindow()
{
    delete lUi;
}
