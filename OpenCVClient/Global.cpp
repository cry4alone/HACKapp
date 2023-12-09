#include "Global.h"
bool PaintRectangle(QVideoFrame &frame,QRect rect){
    if(frame.map(QVideoFrame::ReadOnly)){
        QImage img = frame.toImage();
         QPainter painter;
         painter.begin(&img);
         QPen pen(Qt::red);
         pen.setWidth(4);
         painter.setPen(pen);
         painter.drawRect(rect);
         painter.end();
        QByteArray Block;
        QBuffer buf(&Block);
        img.save(&buf, "JPG");
        frame.unmap();
        QImage img2;
        img2.loadFromData(Block);
        frame = (QVideoFrameFormat(img2.size(), QVideoFrameFormat::pixelFormatFromImageFormat(img2.format())));
        if(frame.map(QVideoFrame::WriteOnly)){
            memcpy(frame.bits(0),img2.bits(),img2.sizeInBytes());
            frame.unmap();
        }
    }
}
