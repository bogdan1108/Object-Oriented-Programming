#ifndef TESTS_H
#define TESTS_H
#pragma once
#include "song.h"
#include "repo.h"
#include "song_exception.h"
#include "controller.h"
#include <QDir>


#include <cassert>

class RepositoryTest {
public:
    static void test() {
        Repository repository;

        // Add songs
        Song song1("Title1", "Artist1", "2021", "Lyrics1", "URL1");
        Song song2("Title2", "Artist2", "2022", "Lyrics2", "URL2");
        Song song3("Title3", "Artist3", "2023", "Lyrics3", "URL3");
        repository.store(song1);
        repository.store(song2);
        repository.store(song3);

        // Get all songs
        const std::vector<Song>& allSongs = repository.getAllSongs();
        assert(allSongs.size() == 3);

        // Remove song
        repository.remove(song2);
        assert(allSongs.size() == 2);

        // Find song
        const Song& foundSong = repository.find("Title1", "Artist1");
        assert(foundSong.getTitle() == "Title1");
        assert(foundSong.getArtist() == "Artist1");
    }
};

class FileRepositoryTest {
public:
    static void test() {
        FileRepository fileRepository("/Users/bogdan/OOP_Project/songs.txt");

        // Load songs from file
        fileRepository.load();

        // Add a new song
        Song newSong("NewTitle", "NewArtist", "2024", "NewLyrics", "NewURL");
        fileRepository.store(newSong);

        // Remove a song
        fileRepository.remove(newSong);

        // Save songs to file
        fileRepository.save();
    }
};

class SongControllerTest {
public:
    static void test() {
        Repository repository;
        SongController songController(repository);

        // Add songs using SongController
        songController.addSong("Title1", "Artist1", "2021", "Lyrics1", "URL1");
        songController.addSong("Title2", "Artist2", "2022", "Lyrics2", "URL2");
        songController.addSong("Title3", "Artist3", "2023", "Lyrics3", "URL3");

        // Search for a song
        const Song& foundSong = songController.searchSong("Title1", "Artist1");
        assert(foundSong.getTitle() == "Title1");
        assert(foundSong.getArtist() == "Artist1");

        // Get songs sorted by artist
        std::vector<Song> songsByArtist = songController.getFilesByArtist(true);
        assert(songsByArtist.size() == 3);
        assert(songsByArtist[0].getArtist() == "Artist1");
        assert(songsByArtist[1].getArtist() == "Artist2");
        assert(songsByArtist[2].getArtist() == "Artist3");

        // Get songs sorted by title
        std::vector<Song> songsByTitle = songController.getSortedFilesByTitle(false);
        assert(songsByTitle.size() == 3);
        assert(songsByTitle[0].getTitle() == "Title3");
        assert(songsByTitle[1].getTitle() == "Title2");
        assert(songsByTitle[2].getTitle() == "Title1");
    }
};

#endif // TESTS_H
