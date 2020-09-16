#if defined(_WIN32)
    #define PLATFORM_NAME "windows"
#elif defined(__linux__)
    #define PLATFORM_NAME "linux"
#else
    #define PLATFORM_NAME ""
#endif

//system("systeminfo >> text.txt"); // Windows
//system("lshw -short >> text.txt"); // Unix

#include "welcomewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WelcomeWindow welcomeWindow;
    welcomeWindow.show();

    return a.exec();
}
