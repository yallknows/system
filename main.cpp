#include "welcomeWindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    WelcomeWindow welcomeWindow;
    welcomeWindow.show();

    return a.exec();
}
