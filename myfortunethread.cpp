#include "myfortunethread.h"


MyFortuneThread::MyFortuneThread(int socketDescriptor, const QString &fortune, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor), text(fortune)
{
        /*QObject *parent) :
    QThread(parent)*/


}

void MyFortuneThread::run()
{
    stopped=0;
    tcpSocket = new QTcpSocket();
//emit dataFromSocketSignal(QString::number(QThread::idealThreadCount()));
    if (!tcpSocket->setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket->error());
        return;
    }
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(slotStop()));
    connect(tcpSocket, SIGNAL(readyRead()), this,SLOT(readyRead()));
    if(modeSendRec){
        QTextStream os(tcpSocket);
        os.setAutoDetectUnicode(true);
        os <<text;
    }else {
        QByteArray block;
           QDataStream out(&block, QIODevice::WriteOnly);
           out.setVersion(QDataStream::Qt_4_0); //Qt_4_0);
           out << (quint16)0;
           out << text;
           out.device()->seek(0);
           out << (quint16)(block.size() - sizeof(quint16));
           tcpSocket->write(block);
    }

   /* while (true) {
        tcpSocket->waitForReadyRead(3000);
        if(modeSendRec){
            QString readArr=tcpSocket->readAll();
            for (int i=0; readArr.right(2)!="\r\n" && i<25; i++)
            {
               tcpSocket->waitForReadyRead(25);
               readArr+=tcpSocket->readAll();
            }
            if(!readArr.isEmpty())
                emit dataFromSocketSignal(readArr);
        }else{
            quint16 blockSize;
            QDataStream in(tcpSocket);
           // in.setVersion(QDataStream::Qt_5_0);
            in >> blockSize;

            while (tcpSocket->bytesAvailable() < blockSize) {
                if (!tcpSocket->waitForReadyRead(5000)) {
                    qDebug() << QString::fromUtf8("socket.error() ggg");
                   // emit error(socket.error(), socket.errorString());
                    return;
                }
            }
            QString fortune;
            in >> fortune;
            if(!fortune.isEmpty())
                emit dataFromSocketSignal(fortune);
        }
    }*/
    exec();



    //tcpSocket->waitForDisconnected();
}

void MyFortuneThread::readyRead()
{

    if(modeSendRec){
        QString readArr=tcpSocket->readAll();
        for (int i=0; readArr.right(2)!="\r\n" && i<25; i++)
        {
           tcpSocket->waitForReadyRead(25);
           readArr+=tcpSocket->readAll();
        }
        if(!readArr.isEmpty())
            emit dataFromSocketSignal(readArr);
    }else{
        quint16 blockSize;
        QDataStream in(tcpSocket);
       // in.setVersion(QDataStream::Qt_5_0);
        in >> blockSize;

        while (tcpSocket->bytesAvailable() < blockSize) {
            if (!tcpSocket->waitForReadyRead(5000)) {
                qDebug() << QString::fromUtf8("socket.error() ggg");
               // emit error(socket.error(), socket.errorString());
                return;
            }
        }
        QString fortune;
        in >> fortune;
        if(!fortune.isEmpty())
            emit dataFromSocketSignal(fortune);
    }

}

void MyFortuneThread::slotStop()
{
    this->stopped=1;
    tcpSocket->disconnectFromHost();
    qDebug() << QString::fromUtf8("stopped");
    exit(0);
    emit zypynyvs();
//    this->terminate();
//    tcpSocket->disconnectFromHost();
//    tcpSocket->waitForDisconnected();
//    this->exit();
}

void MyFortuneThread::writeToSockets(QString arg1)
{

    if(!tcpSocket->isOpen())
        return;
    if(modeSendRec){
        QTextStream os(tcpSocket);
        os.setAutoDetectUnicode(true);
        os <<arg1;
        //tcpSocket->write(arg1.toLocal8Bit());
    }else {
        QByteArray block;
           QDataStream out(&block, QIODevice::WriteOnly);
           out.setVersion(QDataStream::Qt_4_0); //Qt_4_0);
           out << (quint16)0;
           out << arg1;
           out.device()->seek(0);
           out << (quint16)(block.size() - sizeof(quint16));

           tcpSocket->write(block);
    }
}
