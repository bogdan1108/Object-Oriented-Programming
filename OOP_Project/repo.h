#ifndef REPO_H
#define REPO_H
#pragma once
#include <QString>
#include <vector>
#include <string>
#include "song.h"

class Repository {
public :
    Repository();
    Repository(const Repository&) = delete;

    void store(const Song& s);
    const Song& find(std::string title, std::string artist);
    void remove(const Song& s);
    const std::vector<Song>& getAllSongs() const {
        return allSongs;
    }

private:
    std::vector<Song> allSongs;
};

class FileRepository : public Repository {
private :
    std::string filepath;
public :
    FileRepository(const std::string& filePath);
    FileRepository(const FileRepository&) = delete;

    void load();
    void save();

    void store(const Song &s);
    void remove(const Song &s);
};

#endif // REPO_H
