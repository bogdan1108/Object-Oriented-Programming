#include "qtplaylist.h"

#include <QApplication>
#include <iostream>
#include "tests.h"
int main(int argc, char *argv[])
{
    RepositoryTest::test();
    FileRepositoryTest::test();
    SongControllerTest::test();
    QApplication a(argc, argv);
    QtPlaylist w;
    w.show();
    return a.exec();
}
