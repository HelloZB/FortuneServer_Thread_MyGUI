#ifndef MYFORTUNESERVER_H
#define MYFORTUNESERVER_H

#include <QTcpServer>
#include <QStringList>

class MyFortuneServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyFortuneServer(QObject *parent = 0);
    bool modeSendRec;

signals:
    void dataFromSocket(QString);
    void dataFromGUI(QString);
    void signalToStopSockets();

public slots:
    void slotCouter();
     void slotCouterDisc();
     void closeTheServer();

protected:
    void incomingConnection(int socketDescriptor);

private:
    QStringList fortunes;
    qint32 counter;

};

#endif // MYFORTUNESERVER_H
