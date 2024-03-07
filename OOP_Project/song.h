#include <QString>
#include <string>

#ifndef SONG_H
#define SONG_H
#pragma once


class Song {
private :
    std::string title;
    std::string artist;
    std::string link;
    std::string year;
    std::string lyrics;

public :
    Song(const std::string& title, const std::string& artist, const std::string& year, const std::string& lyrics, const std::string& link) :
        title(title), artist(artist), year(year), lyrics(lyrics), link(link) {}

    std::string getTitle() const {
        return title;
    }

    std::string getArtist() const {
        return artist;
    }

    std::string getYear() const {
        return year;
    }

    std::string getLink() const {
        return link;
    }

    std::string getLyrics() const {
        return lyrics;
    }

    bool operator==(const Song& other) const {
        return title == other.title && artist == other.artist;
    }
};

#endif // SONG_H
