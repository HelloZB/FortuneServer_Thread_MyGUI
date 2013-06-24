#include "mygui_threded_server.h"
#include "ui_mygui_threded_server.h"
#include <QMessageBox>
#include <QtNetwork>

#include <stdlib.h>

MyGUI_Threded_Server::MyGUI_Threded_Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyGUI_Threded_Server)
{
    ui->setupUi(this);
    connect(&server, SIGNAL(dataFromSocket(QString)), this, SLOT(vyvidReadData(QString)));
    connect(this, SIGNAL(dataFromGUIToServer(QString)), &server, SIGNAL(dataFromGUI(QString)));
    connect(ui->leSend, SIGNAL(returnPressed()), this, SLOT(dataMustBeWrited()));
    connect(ui->pbSend, SIGNAL(clicked()), this, SLOT(dataMustBeWrited()));

    server.modeSendRec=ui->comboBox->currentIndex();
    if (!server.listen(QHostAddress::Any, 35546)) {
        QMessageBox::critical(this, tr("Threaded Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(server.errorString()));
       // close();
        //return;
    }else { ui->pbStartStop->setChecked(1);}

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    ui->leIP->setText(ipAddress);
    ui->sbPort->setValue(server.serverPort());
    /*statusLabel->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                            "Run the Fortune Client example now.")
                         .arg(ipAddress).arg(server.serverPort()));

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));*/

}

//-----------------------------------------------------------------------------------------------------------
MyGUI_Threded_Server::~MyGUI_Threded_Server()
{
    delete ui;
}

//-----------------------------------------------------------------------------------------------------------
void MyGUI_Threded_Server::on_pbStartStop_clicked(bool checked)
{
    if(checked) {
        server.modeSendRec=ui->comboBox->currentIndex();
        if (!server.listen(QHostAddress::Any, 35546)) {
            QMessageBox::critical(this, tr("Threaded Fortune Server"),
                                  tr("Unable to start the server: %1.")
                                  .arg(server.errorString()));
            ui->pbStartStop->setChecked(0);
            //close();
            //return;
        }else ui->sbPort->setValue(server.serverPort());
    } else server.closeTheServer();
}

//-----------------------------------------------------------------------------------------------------------
void MyGUI_Threded_Server::vyvidReadData(QString arg1)
{
//    QTcpSocket* clientConnection = (QTcpSocket*)sender();
//    quint16 blockSize;
//    QDataStream in(clientConnection);
//    in.setVersion(QDataStream::Qt_4_0);
//    in >> blockSize;

//    while (clientConnection->bytesAvailable() < blockSize) {
//        if (!clientConnection->waitForReadyRead(5000)) {
//            qDebug() << QString::fromUtf8("socket.error()");
//           // emit error(socket.error(), socket.errorString());
//            return;
//        }
//    }
//    QString fortune;
//    in >> fortune;
    //ui->plainTextEdit->appendPlainText(fortune+"yes");

    ui->peLog->appendHtml(tr("<p>%1</p>").arg(arg1));
    ui->leSend->clear();
//    if(ui->pushButton->text()=="Cl&ose")
//        mySerialPort->write(fortune.toLocal8Bit());

}

//-----------------------------------------------------------------------------------------------------------
void MyGUI_Threded_Server::dataMustBeWrited()
{
    ui->peLog->appendHtml(tr("<b>%1</b>").arg(ui->leSend->text()));
    emit dataFromGUIToServer(ui->leSend->text());
}

//-----------------------------------------------------------------------------------------------------------
