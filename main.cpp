#include "comradewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    comradeWidget w;
    w.show();
    return a.exec();
}
