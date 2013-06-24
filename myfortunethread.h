#ifndef MYFORTUNETHREAD_H
#define MYFORTUNETHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>

class MyFortuneThread : public QThread
{
    Q_OBJECT
//public:
   // explicit MyFortuneThread(QObject *parent = 0);


public:
    MyFortuneThread(int socketDescriptor, const QString &fortune, QObject *parent);
     bool modeSendRec;

    void run();
public slots:
    void writeToSockets(QString arg1);
    void readyRead();

//private slots:
    void slotStop();

signals:
    void error(QTcpSocket::SocketError socketError);
    void dataFromSocketSignal(QString);
    void zypynyvs();

private:
    int socketDescriptor;
    QString text;
    bool stopped;
     QTcpSocket *tcpSocket;
};

#endif // MYFORTUNETHREAD_H
