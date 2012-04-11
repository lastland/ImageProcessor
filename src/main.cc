#include <Qt/QtGui>
#include "MainWindow.hh"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    return app.exec();
}
