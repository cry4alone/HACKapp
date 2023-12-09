#include "photowindow.h"
#include "ui_photowindow.h"
QCamera* PhotoWindow::getCamera(){
    return camera_;
}
PhotoWindow::PhotoWindow(QWidget *parent) :
    QWidget(parent),
    pUi(new Ui::PhotoWindow)
{
    pUi->setupUi(this);

    Counter = pUi->Counter;
    videoWidget_ = pUi->VideoWid;
    videoWidget_->resize(640,480);
    videoWidget_->setAspectRatioMode(Qt::KeepAspectRatio);
    videoSinkWidget_ = videoWidget_->videoSink();

    camera_ = new QCamera(QMediaDevices::defaultVideoInput());

    captureSession_ = new QMediaCaptureSession;
    captureSession_->setCamera(camera_);
    videoSinkCamera_ = new QVideoSink;
    captureSession_->setVideoSink(videoSinkCamera_);

    connect(pUi->BackButton,SIGNAL(clicked()),SLOT(slotBackButtonClicked()));
    connect(pUi->PhotoButton,SIGNAL(clicked()),SLOT(slotTakePhoto()));
    connect(pUi->RegistrationButton,SIGNAL(clicked()),SLOT(slotRegistrationButtonClicked()));
    connect(videoSinkCamera_,SIGNAL(videoFrameChanged(QVideoFrame)),SLOT(slotFrameChanged(QVideoFrame)));
}
QByteArray PhotoWindow::getBlockPhoto(){
    return BlockPhotoSendToServer;
}
void PhotoWindow::slotRegistrationButtonClicked(){
    if(PhotoCounter < 10){
        emit signalNotAllPhoto();
        return;
    }
    emit signalRegistration();
}
void PhotoWindow::AddPhotoToBlock(QVideoFrame frame){
    QByteArray Block;
    QBuffer buffer(&Block);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    out<<quint16(0);
    frame.map(QVideoFrame::ReadOnly);
    QImage img = frame.toImage();
    img.save(&buffer,"JPG");
    buffer.seek(0);
    out<<quint16(Block.size()-sizeof(quint16));
    BlockPhotoSendToServer.append(Block);
    buffer.close();
    frame.unmap();
}
void PhotoWindow::slotTakePhoto(){
    if(PhotoCounter >= 10)
        return;
    AddPhotoToBlock(lastFrame);
    PhotoCounter++;
    IncrementCounter();
}
void PhotoWindow::IncrementCounter(){
    QString str = QString::number(PhotoCounter) + "/10";
    Counter->setText(str);
}
void PhotoWindow::slotBackButtonClicked(){
    camera_->stop();
    emit signalBackButtonClicked();
}
void PhotoWindow::slotFrameChanged(QVideoFrame frame){
    lastFrame = frame;
    PaintRectangle(frame,lastRect);
    emit signalSendToServerGetRectangle(frame);
    videoSinkWidget_->setVideoFrame(frame);
}

void PhotoWindow::slotRectRecived(QRect rectangle){
    if((rectangle.x() == 0) && (rectangle.y() == 0))
        rectIsCorrect = false;
    else
        rectIsCorrect = true;
    lastRect = rectangle;
}
PhotoWindow::~PhotoWindow()
{
    delete pUi;
}
