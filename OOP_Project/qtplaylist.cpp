#include "qtplaylist.h"
#include "./ui_qtplaylist.h"
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <iostream>
#include <QGridLayout>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QListWidgetItem>
#include <random>
#include <QKeyEvent>

QtPlaylist::QtPlaylist(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QtPlaylist),
    repository()
{
    ui->setupUi(this);

    songController = new SongController(repository);

    connect(ui->addButton, &QPushButton::clicked, this, &QtPlaylist::addSongToList);
    connect(ui->removeButton, &QPushButton::clicked, this, &QtPlaylist::removeSongFromList);
    connect(ui->sortByArtist, &QPushButton::clicked, this, &QtPlaylist::sortSongsByArtist);
    connect(ui->sortByTitle, &QPushButton::clicked, this, &QtPlaylist::sortSongsByTitle);
    connect(ui->viewLyricsButton, &QPushButton::clicked, this, &QtPlaylist::viewLyrics);
    connect(ui->randomPlaylistButton, &QPushButton::clicked, this, &QtPlaylist::generateRandomPlaylist);
    connect(ui->moveToPlaylist, &QPushButton::clicked, this, &QtPlaylist::moveSongToPlaylist);
    connect(ui->removeFromPlaylist, &QPushButton::clicked, this, &QtPlaylist::removeSong);
}

void QtPlaylist::addSongToList() {
    // Read the song details from the line edits
    QString title = ui->titleEdit->text();
    QString artist = ui->artistEdit->text();
    QString year = ui->yearEdit->text();
    QString link = ui->linkEdit->text();
    QString lyrics = ui->lyricsEdit->text();

    try {
        // Call the addSong function in the SongController
        songController->addSong(title.toStdString(), artist.toStdString(), year.toStdString(), lyrics.toStdString(), link.toStdString());

        // Add the song title to the songs list widget
        ui->songsList->addItem(title + " - " + artist);

        // Optional: Clear the line edit fields after adding the song
        ui->titleEdit->clear();
        ui->artistEdit->clear();
        ui->yearEdit->clear();
        ui->linkEdit->clear();
        ui->lyricsEdit->clear();
    } catch (const song_exception& e) {
        // Handle the exception (e.g., display an error message)
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }
}

void QtPlaylist::removeSongFromList()
{
    // Retrieve the selected item from the playlist QListWidget
    QListWidgetItem* selectedItem = ui->songsList->currentItem();
    if (!selectedItem)
        return; // No item selected

    // Get the title and artist of the selected song
        QString selectedText = selectedItem->text();
        QStringList parts = selectedText.split(" - ");
        if (parts.size() >= 2) {
            QString title = parts[0];
            QString artist = parts[1];
            try {
                songController->removeSong(title.toStdString(), artist.toStdString());
                // Remove the item from the playlist QListWidget
                ui->songsList->takeItem(ui->songsList->row(selectedItem));
                delete selectedItem;
            } catch (const song_exception& ex) {
                // Handle the exception (display an error message, etc.)
                QMessageBox::critical(this, "Error", ex.what());
            }
            // Now you can use the title and artist variables as needed
        }
        // Remove the song using the SongController

}

void QtPlaylist::sortSongsByArtist()
{
        // Get the number of items in the songs list
        int itemCount = ui->songsList->count();

        // Create a vector to store the songs
        std::vector<QString> songs;

        // Store the songs in the vector
        for (int i = 0; i < itemCount; ++i) {
            QListWidgetItem* item = ui->songsList->item(i);
            if (item) {
                songs.push_back(item->text());
            }
        }

        // Sort the songs vector by artist
        std::sort(songs.begin(), songs.end(), [](const QString& song1, const QString& song2) {
            QStringList parts1 = song1.split(" - ");
            QStringList parts2 = song2.split(" - ");
            if (parts1.size() >= 2 && parts2.size() >= 2) {
                return parts1[1] < parts2[1];
            }
            return false;
        });

        // Clear the songs list
        ui->songsList->clear();

        // Add the sorted songs back to the songs list
        for (const QString& song : songs) {
            ui->songsList->addItem(song);
        }
}

void QtPlaylist::sortSongsByTitle()
{
        // Get the number of items in the songs list
        int itemCount = ui->songsList->count();

        // Create a vector to store the songs
        std::vector<QString> songs;

        // Store the songs in the vector
        for (int i = 0; i < itemCount; ++i) {
            QListWidgetItem* item = ui->songsList->item(i);
            if (item) {
                songs.push_back(item->text());
            }
        }

        // Sort the songs vector by title
        std::sort(songs.begin(), songs.end(), [](const QString& song1, const QString& song2) {
            QStringList parts1 = song1.split(" - ");
            QStringList parts2 = song2.split(" - ");
            if (parts1.size() >= 2 && parts2.size() >= 2) {
                return parts1[0] < parts2[0];
            }
            return false;
        });

        // Clear the songs list
        ui->songsList->clear();

        // Add the sorted songs back to the songs list
        for (const QString& song : songs) {
            ui->songsList->addItem(song);
        }
}

void QtPlaylist::viewLyrics()
{
        // Retrieve the selected item from the songsList QListWidget
        QListWidgetItem* selectedItem = ui->songsList->currentItem();
        if (!selectedItem)
            return; // No item selected

        // Get the lyrics of the selected song
        QString lyrics = selectedItem->data(Qt::UserRole + 1).toString();

        // Show a message box with the lyrics
        QMessageBox::information(this, "Lyrics", lyrics);
}

void QtPlaylist::generateRandomPlaylist()
{
        // Retrieve the songs from the songsList QListWidget
        QList<QListWidgetItem*> songs = ui->songsList->findItems("", Qt::MatchContains);

        // Generate a random playlist
        std::random_device rd;
        std::mt19937 generator(rd());
        std::shuffle(songs.begin(), songs.end(), generator);

        // Clear the playlist QListWidget
        ui->playlistList->clear();

        // Add the shuffled songs to the playlist QListWidget
        for (QListWidgetItem* song : songs) {
            QString title = song->text();
            QString songInfo = title;
            ui->playlistList->addItem(songInfo);
        }
}

void QtPlaylist::removeSong()
{
        // Retrieve the selected item from the songsList QListWidget
        QListWidgetItem* selectedItem = ui->playlistList->currentItem();
        if (!selectedItem)
            return; // No item selected

        // Remove the selected item from the playlistList QListWidget
        ui->playlistList->takeItem(ui->playlistList->row(selectedItem));

        // Add the selected item back to the songsList QListWidget
        ui->songsList->addItem(selectedItem->text());
}

void QtPlaylist::moveSongToPlaylist()
{
        // Retrieve the selected item from the songsList QListWidget
        QListWidgetItem* selectedItem = ui->songsList->currentItem();
        if (!selectedItem)
            return; // No item selected

        // Remove the selected item from the songsList QListWidget
        ui->songsList->takeItem(ui->songsList->row(selectedItem));

        // Add the selected item to the playlistList QListWidget
        ui->playlistList->addItem(selectedItem->text());
}

void QtPlaylist::keyPressEvent(QKeyEvent* event)
{
        if (event->modifiers() == Qt::ControlModifier || event->modifiers() == Qt::MetaModifier)
        {
            if (event->key() == Qt::Key_Z)
            {
                // CTRL+Z or Command+Z pressed, perform undo operation
                songController->undo();
                event->accept();
                return;
            }
            else if (event->key() == Qt::Key_Y)
            {
                // CTRL+Y or Command+Y pressed, perform redo operation
                songController->redo();
                event->accept();
                return;
            }
        }

        QMainWindow::keyPressEvent(event);
}



QtPlaylist::~QtPlaylist()
{
    delete ui;
}

