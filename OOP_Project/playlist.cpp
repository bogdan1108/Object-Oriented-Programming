#include "playlist.h"

void Playlist::add(const Song& song) {
    songs.push_back(song);
}

void Playlist::clear() {
    songs.clear();
}

void Playlist::remove(const Song& song) {
    songs.erase(std::remove(songs.begin(), songs.end(), song), songs.end());
}

void Playlist::generateRandom(size_t n, const std::vector<Song>& songList) {
    songs.clear();

    if (n > songList.size())
        n = songList.size();

    // Shuffle the song list
    std::vector<Song> shuffledSongs = songList;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(shuffledSongs.begin(), shuffledSongs.end(), generator);

    // Add the first n shuffled songs to the playlist
    for (size_t i = 0; i < n; ++i) {
        songs.push_back(shuffledSongs[i]);
    }
}

