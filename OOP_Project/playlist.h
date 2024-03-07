#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <vector>
#include <random>
#include <algorithm>
#include "song.h"

class Playlist {
private:
    std::vector<Song> songs;

public:
    void add(const Song& song);

    void clear();

    void remove(const Song& song);

    void generateRandom(size_t n, const std::vector<Song>& songList);
};

#endif // PLAYLIST_H
