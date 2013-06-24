#ifndef MYGUI_THREDED_SERVER_H
#define MYGUI_THREDED_SERVER_H

#include <QWidget>
#include "myfortuneserver.h"

namespace Ui {
class MyGUI_Threded_Server;
}

class MyGUI_Threded_Server : public QWidget
{
    Q_OBJECT
    
public:
    explicit MyGUI_Threded_Server(QWidget *parent = 0);
    ~MyGUI_Threded_Server();
    public slots:
        void vyvidReadData(QString arg1);
private slots:
    void dataMustBeWrited();
    void on_pbStartStop_clicked(bool checked);

signals:
    void dataFromGUIToServer(QString);


private:
    Ui::MyGUI_Threded_Server *ui;
    MyFortuneServer server;
};

#endif // MYGUI_THREDED_SERVER_H
