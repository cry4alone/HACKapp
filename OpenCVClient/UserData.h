#ifndef USERDATA_H
#define USERDATA_H
#include <QString>
#include <QObject>
class UserData : public QObject
{
public:
    int label = 0;
    QString lastName_ = "";
    QString firstName_ = "";
    QString middleName_ = "";
    QString phone_ = "";
    UserData(QObject* parent = nullptr) : QObject(parent){}
};

#endif // USERDATA_H
