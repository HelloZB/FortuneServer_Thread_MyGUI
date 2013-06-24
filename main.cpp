#include "mygui_threded_server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyGUI_Threded_Server w;
    w.show();
    
    return a.exec();
}
