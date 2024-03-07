#ifndef CONTROLLER_H
#define CONTROLLER_H
#pragma once
#include "repo.h"
#include "song_exception.h"
#include <stack>
#include <memory>

class Action {
public:
    virtual ~Action() = default;
    virtual void apply() = 0;
};

class ActionAdd : public Action {
private:
    Repository& repository;
    Song song;

public:
    ActionAdd(Repository& repo, const Song& s) : repository(repo), song(s) {}

    void apply() override {
        repository.store(song);
    }
};

class ActionDelete : public Action {
private:
    Repository& repository;
    Song song;

public:
    ActionDelete(Repository& repo, const Song& s) : repository(repo), song(s) {}

    void apply() override {
        repository.remove(song);
    }
};

class SongController {
private:
    Repository& repository;

    std::stack<std::unique_ptr<Action>> undoStack;
    std::stack<std::unique_ptr<Action>> redoStack;

public:
    SongController(Repository& repo);

    void addSong(const std::string& title, const std::string& artist, const std::string& year,
                 const std::string& lyrics = "", const std::string& url = "");
    const Song& searchSong(const std::string& title, const std::string& artist);
    void removeSong(const std::string& title, const std::string& artist);
    std::vector<Song> getFilesByArtist(bool increasingOrder);
    std::vector<Song> getSortedFilesByTitle(bool increasingOrder);

    void undo();
    void redo();
    void addAction(std::unique_ptr<Action> action);
    void addActionToUndoStack(std::unique_ptr<Action> action);
};

#endif // CONTROLLER_H
