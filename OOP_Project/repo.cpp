#include "repo.h"
#include "song_exception.h"
#include <fstream>

Repository::Repository() {}

void Repository::store(const Song& s)
{
    auto it = std::find_if(allSongs.begin(), allSongs.end(), [&](const Song& song) {
        return song.getTitle() == s.getTitle() && song.getArtist() == s.getArtist();
    });

    if (it != allSongs.end()) {
        throw song_exception("A song '" + s.getTitle() + "' by '" + s.getArtist() + "' already exists.");
    }

    allSongs.push_back(s);
}

const Song& Repository::find(std::string title, std::string artist)
{
    auto it = std::find_if(allSongs.begin(), allSongs.end(), [&](const Song& song) {
        return song.getTitle() == title && song.getArtist() == artist;
    });

    if (it == allSongs.end()) {
        throw song_exception("The song '" + title + "' by '" + artist + "'does not exist!");
    }

    return *it;
}

void Repository::remove(const Song& s) {
    auto it = std::find_if(allSongs.begin(), allSongs.end(), [&](const Song& song) {
        return song.getTitle() == s.getTitle() && song.getArtist() == s.getArtist();
    });

    if (it != allSongs.end()) {
        allSongs.erase(it);
    } else {
        throw song_exception("The song " + s.getTitle() + " by " + s.getArtist() + " does not exist");
    }
}



FileRepository::FileRepository(const std::string &filePath) : filepath(filePath) {}

void FileRepository::load() {
    std::ifstream inputFile(filepath);
    if(!inputFile.is_open()) {
        throw std::runtime_error("Failed to open the input file");
    }

    std::string line;
    while(std::getline(inputFile, line)) {
        std::string title, artist, year, lyrics, url;
        Song song(title, artist, year, lyrics, url);
        store(song);
    }

    inputFile.close();

}

void FileRepository::save() {
    std::ofstream outputFile(filepath);
    if(!outputFile.is_open()) {
        throw std::runtime_error("Failed to open the output file");
    }

    const std::vector<Song>& allSongs = getAllSongs();

    for(const Song& song : allSongs) {
        outputFile << song.getTitle() << "|" << song.getArtist() << "|" << song.getYear() << "|" << song.getLyrics() << "|" << song.getLink() << "\n";
    }

    outputFile.close();
}

void FileRepository::store(const Song &s) {
    Repository::store(s);
    save();
}

void FileRepository::remove(const Song &s) {
    Repository::remove(s);
    save();
}
