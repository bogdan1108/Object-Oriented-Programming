#include "controller.h"
#include <iostream>

SongController::SongController(Repository& repo) : repository(repo) {}

void SongController::addSong(const std::string& title, const std::string& artist, const std::string& year,
                             const std::string& lyrics, const std::string& url) {
    try {
        repository.find(title, artist);  // Check if the song already exists
        throw song_exception("A song '" + title + "' by '" + artist + "' already exists.");
    } catch (const song_exception&) {
        Song newSong(title, artist, year, lyrics, url);
        repository.store(newSong);
        addAction(std::make_unique<ActionAdd>(repository, newSong));
    }
}

void SongController::removeSong(const std::string &title, const std::string &artist) {
    const Song& song = searchSong(title, artist);
    std::unique_ptr<Action> action = std::make_unique<ActionDelete>(repository, song);
    addAction(std::move(action));
    repository.remove(song);
}

const Song& SongController::searchSong(const std::string& title, const std::string& artist) {
    try {
        return repository.find(title, artist);
    } catch (const song_exception& ex) {
        throw;
    }
}

std::vector<Song> SongController::getFilesByArtist(bool increasingOrder) {
    std::vector<Song> allSongs = repository.getAllSongs();

    // Sort the songs by artist using a lambda function
    std::sort(allSongs.begin(), allSongs.end(), [increasingOrder](const Song& song1, const Song& song2) {
        if (increasingOrder) {
            return song1.getArtist() < song2.getArtist();
        } else {
            return song1.getArtist() > song2.getArtist();
        }
    });

    return allSongs;
}

std::vector<Song> SongController::getSortedFilesByTitle(bool increasingOrder) {
    std::vector<Song> allSongs = repository.getAllSongs();

    // Sort the songs by title using a lambda function
    std::sort(allSongs.begin(), allSongs.end(), [increasingOrder](const Song& song1, const Song& song2) {
        if (increasingOrder) {
            return song1.getTitle() < song2.getTitle();
        } else {
            return song1.getTitle() > song2.getTitle();
        }
    });

    return allSongs;
}


void SongController::addAction(std::unique_ptr<Action> action) {
    undoStack.push(std::move(action));
    redoStack = std::stack<std::unique_ptr<Action>>();
}

void SongController::addActionToUndoStack(std::unique_ptr<Action> action)
{
    undoStack.push(std::move(action));
}

void SongController::undo() {
    if (!undoStack.empty()) {
        std::unique_ptr<Action> action = std::move(undoStack.top());
        undoStack.pop();
        action->apply();
        redoStack.push(std::move(action));
    }
}

void SongController::redo() {
    if (!redoStack.empty()) {
        std::unique_ptr<Action> action = std::move(redoStack.top());
        redoStack.pop();
        action->apply();
        undoStack.push(std::move(action));
    }
}
