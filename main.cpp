#include "mainwindow.h"
#include "calculation.h"

int main(int argc, char *argv[])
{
   try{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    }
    catch(error& e)
    {
        e.show();
    }
    return 0;
}
