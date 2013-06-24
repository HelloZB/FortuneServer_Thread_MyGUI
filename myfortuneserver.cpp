#include "myfortuneserver.h"
#include "myfortunethread.h"

MyFortuneServer::MyFortuneServer(QObject *parent) :
    QTcpServer(parent)
{
    counter=0;
    fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
                 << tr("You've got to think about tomorrow.")
                 << tr("You will be surprised by a loud noise.")
                 << tr("You will feel hungry again in another hour.")
                 << tr("You might have mail.")
                 << tr("You cannot kill time without injuring eternity.")
                 << tr("Computers are not intelligent. They only think they are.");

}
void MyFortuneServer::incomingConnection(int socketDescriptor)
{
    QString fortune = fortunes.at(qrand() % fortunes.size());
    MyFortuneThread *thread = new MyFortuneThread(socketDescriptor, fortune, this);

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(dataFromSocketSignal(QString)), this, SIGNAL(dataFromSocket(QString)));
    connect(this, SIGNAL(dataFromGUI(QString)), thread, SLOT(writeToSockets(QString)));
    connect(thread, SIGNAL(zypynyvs()), this, SLOT(slotCouterDisc()));
   // connect(thread, SIGNAL(finished()), this, SLOT(slotCouterDisc()));
    //connect(thread, SIGNAL(terminated()), this, SLOT(slotCouterDisc()));

    connect(this, SIGNAL(signalToStopSockets()), thread, SLOT(slotStop()));
    thread->modeSendRec=this->modeSendRec;
    thread->start();
    counter++;
    QString str;
    str="One connected! Total "+QString::number(counter);
    emit dataFromSocket(str);
}

void MyFortuneServer::slotCouter()
{
    counter++;
    QString str;
    str="One connected! Total "+QString::number(counter);
    emit dataFromSocket(str);
}

void MyFortuneServer::slotCouterDisc()
{
    counter--;
    QString str;
    str="One disconnected! Total "+QString::number(counter);
    emit dataFromSocket(str);
}

void MyFortuneServer::closeTheServer()
{
    emit signalToStopSockets();
    this->close();
}
