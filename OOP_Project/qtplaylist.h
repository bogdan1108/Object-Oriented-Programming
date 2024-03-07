#ifndef QTPLAYLIST_H
#define QTPLAYLIST_H

#include <QMainWindow>
#include <QList>
#include <QPushButton>
#include <QListWidget>
#include "song.h"
#include "repo.h"
#include "song_exception.h"
#include "controller.h"
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class QtPlaylist; }
QT_END_NAMESPACE

class QtPlaylist : public QMainWindow
{
    Q_OBJECT

public:
    QtPlaylist(QWidget *parent = nullptr);
    ~QtPlaylist();


private slots:
    void addSongToList();
    void removeSongFromList();
    void sortSongsByArtist();
    void sortSongsByTitle();
    void viewLyrics();
    void generateRandomPlaylist();
    void moveSongToPlaylist();
    void removeSong();

private:
    Ui::QtPlaylist *ui;
    Repository repository; // Declare Repository as a member
    SongController* songController;

protected:
    void keyPressEvent(QKeyEvent* event) override;

};


#endif // QTPLAYLIST_H
