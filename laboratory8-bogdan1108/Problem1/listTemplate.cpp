#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <map>

// list template
template <typename T>
class List {
    private: 
        struct Node {
            T data;
            Node* next;
            Node* prev;
        };
        Node* head;
        Node* tail;
        int size;
    public:
        List() {
            head = nullptr;
            tail = nullptr;
            size = 0;
        }
        ~List() {
            clear();
        }
        void push_back(T data) {
            Node* newNode = new Node;
            newNode->data = data;
            newNode->next = nullptr;
            newNode->prev = nullptr;
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            size++;
        }
        void push_front(T data) {
            Node* newNode = new Node;
            newNode->data = data;
            newNode->next = nullptr;
            newNode->prev = nullptr;
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            size++;
        }
        void pop_back() {
            if (head == nullptr) {
                return;
            }
            if (head == tail) {
                delete head;
                head = nullptr;
                tail = nullptr;
                size--;
                return;
            }
            Node* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
            size--;
        }
        void pop_front() {
            if (head == nullptr) {
                return;
            }
            if (head == tail) {
                delete head;
                head = nullptr;
                tail = nullptr;
                size--;
                return;
            }
            Node* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
            size--;
        }
        void insert(int index, T data) {
            if (index < 0 || index > size) {
                return;
            }
            if (index == 0) {
                push_front(data);
                return;
            }
            if (index == size) {
                push_back(data);
                return;
            }
            Node* newNode = new Node;
            newNode->data = data;
            newNode->next = nullptr;
            newNode->prev = nullptr;
            Node* temp = head;
            for (int i = 0; i < index - 1; i++) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
            size++;
        }
        void remove(int index) {
            if (index < 0 || index >= size) {
                return;
            }
            if (index == 0) {
                pop_front();
                return;
            }
            if (index == size - 1) {
                pop_back();
                return;
            }
            Node* temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            delete temp;
            size--;
        }
        void print() {
            // check if list is empty
            if (head == nullptr) {
                std::cout << "List is empty" << std::endl;
                return;
            }
            Node* temp = head;
            while (temp != nullptr) {
                std::cout << temp->data << " ";
                temp = temp->next;
            }
            std::cout << std::endl;
        }
        int getSize() {
            return size;
        }
        T get(int index) {
            if (index < 0 || index >= size) {
                return T();
            }
            Node* temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            return temp->data;
        }
        void set(int index, T data) {
            if (index < 0 || index >= size) {
                return;
            }
            Node* temp = head;
            for (int i = 0; i < index; i++) {
                temp = temp->next;
            }
            temp->data = data;
        }
        void clear() {
            while (head != nullptr) {
                pop_front();
            }
        }
};


class Song {
    protected:
        std::string artist;
        std::string title;

    private:
        std::vector<std::string> lyrics;

    public:
        Song(std::string artist, std::string title, std::vector<std::string> lyrics) {
            this->artist = artist;
            this->title = title;

            // transform lyrics to lowercase
            for (int i = 0; i < lyrics.size(); i++) {
                std::string line = lyrics[i];
                for (int j = 0; j < line.size(); j++) {
                    line[j] = tolower(line[j]);
                }
                this->lyrics.push_back(line);
            }

            // remove punctuation
            for (int i = 0; i < this->lyrics.size(); i++) {
                std::string line = this->lyrics[i];
                for (int j = 0; j < line.size(); j++) {
                    if (ispunct(line[j])) {
                        line.erase(j--, 1);
                    }
                }
                this->lyrics[i] = line;
            }

            // split lyrics into words
            std::vector<std::string> words;
            for (int i = 0; i < this->lyrics.size(); i++) {
                std::string line = this->lyrics[i];
                std::string word = "";
                for (int j = 0; j < line.size(); j++) {
                    if (line[j] == ' ') {
                        words.push_back(word);
                        word = "";
                    } else {
                        word += line[j];
                    }
                }
                words.push_back(word);
            }
            this->lyrics = words;

            // remove empty strings
            for (int i = 0; i < this->lyrics.size(); i++) {
                if (this->lyrics[i] == "") {
                    this->lyrics.erase(this->lyrics.begin() + i);
                    i--;
                }
            }

            // // print lyrics
            // for (int i = 0; i < this->lyrics.size(); i++) {
            //     std::cout << this->lyrics[i] << std::endl;
            // }
        }

        std::string getArtist() {
            return artist;
        }

        std::string getTitle() {
            return title;
        }

        std::vector<std::string> getLyrics() {
            return lyrics;
        }
};

class SongCollection {
    // stores a vector of songs from a file
    private:
        std::vector<Song> songs;

    public:
        SongCollection(std::string filename) {
            // std::ifstream file("lyrics.txt");
            // std::string line;
            // std::vector<std::string> lyrics;
            // std::string artist;
            // std::string title;
            // int lineNum = 0;
            // while (std::getline(file, line)) {
            //     if (lineNum == 0) {
            //         size_t start = line.find('"') + 1;
            //         size_t end = line.find('"', start);
            //         artist = line.substr(start, end - start);
            //     } else if (lineNum == 1) {
            //         size_t start = line.find('"') + 1;
            //         size_t end = line.find('"', start);
            //         title = line.substr(start, end - start);
            //     } else {
            //         size_t start = line.find('"') + 1;
            //         size_t end = line.find('"', start);
            //         lyrics.push_back(line.substr(start, end - start));
            //     }
            //     lineNum++;
            // }
            // songs.push_back(Song(artist, title, lyrics));

            std::ifstream file(filename);
            if(!file.is_open()) {
                std::cout << "Error opening file" << std::endl;
                return;
            }
            std::string line;
            std::vector<std::string> lyrics;
            std::string artist;
            std::string title;
            int lineNum = 0;
            while (std::getline(file, line)) {
                if (line.find("ARTIST") != std::string::npos) {
                    size_t start = line.find('"') + 1;
                    size_t end = line.find('"', start);
                    if(!artist.empty()) {
                        songs.push_back(Song(artist, title, lyrics));
                    }
                    artist = line.substr(start, end - start);
                } else if (line.find("TITLE") != std::string::npos) {
                    size_t start = line.find('"') + 1;
                    size_t end = line.find('"', start);
                    title = line.substr(start, end - start);
                } else if (line.find("LYRICS") != std::string::npos) {
                    lineNum = 0;
                } else {
                    if (lineNum == 0) {
                        lyrics.clear();
                    }
                    size_t start = line.find('"') + 1;
                    size_t end = line.find('"', start);
                    lyrics.push_back(line.substr(start, end - start));
                    lineNum++;
                }
            }
            songs.push_back(Song(artist, title, lyrics));

            // close file
            file.close();


        }

        std::vector<Song> getSongs() {
            return songs;
        }

        // check if songs is empty
        bool isEmpty() {
            return songs.size() == 0;
        }

        // method that computes and reutrns the unique artists from the songs using std::set
        std::set<std::string> getArtists() {
            std::set<std::string> artists;
            for (int i = 0; i < songs.size(); i++) {
                artists.insert(songs[i].getArtist());
            }
            return artists;
        }

        // method that group the songs based on the artists and returns the first x artists based on the number of songs and their number of songs
        std::vector<std::pair<std::string, int>> getTopArtists(int x) {
            std::vector<std::pair<std::string, int>> topArtists;
            std::set<std::string> artists = getArtists();
            for (std::set<std::string>::iterator it = artists.begin(); it != artists.end(); it++) {
                std::string artist = *it;
                int numSongs = 0;
                for (int i = 0; i < songs.size(); i++) {
                    if (songs[i].getArtist() == artist) {
                        numSongs++;
                    }
                }
                topArtists.push_back(std::make_pair(artist, numSongs));
            }
            std::sort(topArtists.begin(), topArtists.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b) {
                return a.second > b.second;
            });
            if (x > topArtists.size()) {
                x = topArtists.size();
            }
            std::vector<std::pair<std::string, int>> topXArtists;
            for (int i = 0; i < x; i++) {
                topXArtists.push_back(topArtists[i]);
            }
            return topXArtists;
        }

        // method to efficiently search for songs that contain a specified word
        std::vector<Song> search(std::string word) {
            std::vector<Song> songsWithWord;
            for (int i = 0; i < songs.size(); i++) {
                std::vector<std::string> lyrics = songs[i].getLyrics();
                for (int j = 0; j < lyrics.size(); j++) {
                    if (lyrics[j].find(word) != std::string::npos) {
                        songsWithWord.push_back(songs[i]);
                        break;
                    }
                }
            }
            return songsWithWord;
        }
};

int main() {
    List<int> list;
    std::cout << "Pushing back 1, 2, 3, 4, 5" << std::endl;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    
    std::cout << "List: ";
    list.print();

    std::cout << "Pushing front 0" << std::endl;
    list.push_front(0);

    std::cout << "List: ";
    list.print();

    std::cout << "Popping back" << std::endl;
    list.pop_back();

    std::cout << "List: ";
    list.print();

    std::cout << "Popping front" << std::endl;
    list.pop_front();

    std::cout << "List: ";
    list.print();

    std::cout << "Inserting 10 at index 2" << std::endl;
    list.insert(2, 10);

    std::cout << "List: ";
    list.print();

    std::cout << "Removing element at index 2" << std::endl;
    list.remove(2);

    std::cout << "List: ";
    list.print();

    std::cout << "Size: " << list.getSize() << std::endl;

    std::cout << "Element at index 2: " << list.get(2) << std::endl;

    std::cout << "Setting element at index 2 to 10" << std::endl;
    list.set(2, 10);

    std::cout << "List: ";
    list.print();

    std::cout << "Clearing list" << std::endl;
    list.clear();

    std::cout << "List: ";
    list.print();

    std::cout << std::endl << std::endl << std::endl;

    List<bool> list2;
    std::cout << "Pushing back 1, 0, 1, 0, 1" << std::endl;
    list2.push_back(1);
    list2.push_back(0);
    list2.push_back(1);
    list2.push_back(0);
    list2.push_back(1);

    std::cout << "List: ";
    list2.print();

    std::cout << "Pushing front 0" << std::endl;
    list2.push_front(0);

    std::cout << "List: ";
    list2.print();

    std::cout << "Popping back" << std::endl;
    list2.pop_back();

    std::cout << "List: ";
    list2.print();

    std::cout << "Popping front" << std::endl;
    list2.pop_front();

    std::cout << "List: ";
    list2.print();

    std::cout << "Inserting 1 at index 2" << std::endl;
    list2.insert(2, 1);

    std::cout << "List: ";
    list2.print();

    std::cout << "Removing element at index 2" << std::endl;
    list2.remove(2);

    std::cout << "List: ";
    list2.print();

    std::cout << "Size: " << list2.getSize() << std::endl;

    std::cout << "Element at index 2: " << list2.get(2) << std::endl;

    std::cout << "Setting element at index 2 to 1" << std::endl;
    list2.set(2, 1);

    std::cout << "List: ";
    list2.print();

    std::cout << "Clearing list" << std::endl;
    list2.clear();

    std::cout << "List: ";
    list2.print();

    std::cout << std::endl << std::endl << std::endl;

    List<std::string> list3;
    std::cout << "Pushing back \"Hello\", \"Dear\", \"World\"" << std::endl;
    list3.push_back("Hello");
    list3.push_back("Dear");
    list3.push_back("World");

    std::cout << "List: ";
    list3.print();

    std::cout << "Pushing front \"Goodbye\"" << std::endl;
    list3.push_front("Goodbye");

    std::cout << "List: ";
    list3.print();

    std::cout << "Popping back" << std::endl;
    list3.pop_back();

    std::cout << "List: ";
    list3.print();

    std::cout << "Popping front" << std::endl;
    list3.pop_front();

    std::cout << "List: ";
    list3.print();

    std::cout << "Inserting \"World\" at index 2" << std::endl;
    list3.insert(2, "World");

    std::cout << "List: ";
    list3.print();

    std::cout << "Removing element at index 2" << std::endl;
    list3.remove(2);

    std::cout << "List: ";
    list3.print();

    std::cout << "Size: " << list3.getSize() << std::endl;

    std::cout << "Element at index 2: " << list3.get(2) << std::endl;

    std::cout << "Setting element at index 2 to \"World\"" << std::endl;
    list3.set(2, "World");

    std::cout << "List: ";
    list3.print();

    std::cout << "Clearing list" << std::endl;
    list3.clear();

    std::cout << "List: ";
    list3.print();

    std::cout << std::endl << std::endl << std::endl;



    // read data from lyrics.txt
    // 1st line is artist
    // 2nd line is title
    // rest of lines are lyrics

    // std::ifstream file("lyrics.txt");
    // std::string line;
    // std::vector<std::string> lyrics;
    // std::string artist;
    // std::string title;
    // int lineNum = 0;
    // while (std::getline(file, line)) {
    //     if (lineNum == 0) {
    //         size_t start = line.find('"') + 1;
    //         size_t end = line.find('"', start);
    //         artist = line.substr(start, end - start);
    //     } else if (lineNum == 1) {
    //         size_t start = line.find('"') + 1;
    //         size_t end = line.find('"', start);
    //         title = line.substr(start, end - start);
    //     } else {
    //         size_t start = line.find('"') + 1;
    //         size_t end = line.find('"', start);
    //         lyrics.push_back(line.substr(start, end - start));
    //     }
    //     lineNum++;
    // }
    // file.close();

    // Song song(artist, title, lyrics);

    // std::cout << "Artist: " << song.getArtist() << std::endl;
    // std::cout << "Title: " << song.getTitle() << std::endl;
    // std::cout << "Lyrics: " << std::endl;
    // for (int i = 0; i < song.getLyrics().size(); i++) {
    //     std::cout << song.getLyrics()[i] << " ";
    // }

    SongCollection collection("lyrics.txt");
    std::vector<Song> songs = collection.getSongs();

    // print the song named "#9 Dream" by John Lennon
    for (int i = 0; i < songs.size(); i++) {
        if (songs[i].getTitle() == "#9 Dream" && songs[i].getArtist() == "John Lennon") {
            std::cout << "Artist: " << songs[i].getArtist() << std::endl;
            std::cout << "Title: " << songs[i].getTitle() << std::endl;
            std::cout << "Lyrics: " << std::endl;
            for (int j = 0; j < songs[i].getLyrics().size(); j++) {
                std::cout << songs[i].getLyrics()[j] << " ";
            }
            std::cout << std::endl;
        }
    }

    std::cout << std::endl << std::endl << std::endl;

    // print the unique artists in the collection using getArtists()
    std::set<std::string> artists = collection.getArtists();
    std::cout << "Artists: " << std::endl;
    for (std::set<std::string>::iterator it = artists.begin(); it != artists.end(); it++) {
        std::cout << ">> " << *it << std::endl;
    }

    std::cout << std::endl << std::endl << std::endl;

    // print the first 10 artists in the collection using getTopArtists(int) and their number of songs
    std::vector<std::pair<std::string, int>> topArtists = collection.getTopArtists(10);
    std::cout << "Top Artists: " << std::endl;
    for (int i = 0; i < topArtists.size(); i++) {
        std::cout << ">> " << topArtists[i].first << " (" << topArtists[i].second << " songs)" << std::endl;
    }


    // use lambda expressions to sort the vector of songs by:
    // 1. increasing order based on the artist's name
    // 2. decreasing order based on the title
    // 3. increasing order based on the number of words in the lyrics
    // auto sortByArtist = [](Song s1, Song s2) {
    //     return s1.getArtist() < s2.getArtist();
    // }; 
    // std::sort(songs.begin(), songs.end(), sortByArtist);

    // // print the vector of songs
    // std::cout << "Songs sorted by artist: " << std::endl;
    // for (int i = 0; i < songs.size(); i++) {
    //     std::cout << ">> " << songs[i].getArtist() << " - " << songs[i].getTitle() << std::endl;
    // }

    // std::cout << std::endl << std::endl << std::endl;
    
    auto sortByTitle = [](Song s1, Song s2) {
        return s1.getTitle() > s2.getTitle();
    };
    std::sort(songs.begin(), songs.end(), sortByTitle);

    // print the vector of songs
    std::cout << "Songs sorted by title: " << std::endl;
    for (int i = 0; i < songs.size(); i++) {
        std::cout << ">>> " << songs[i].getArtist() << " - " << songs[i].getTitle() << std::endl;
    }

    std::cout << std::endl << std::endl << std::endl;

    // auto sortByLyrics = [](Song s1, Song s2) {
    //     return s1.getLyrics().size() < s2.getLyrics().size();
    // };
    // std::sort(songs.begin(), songs.end(), sortByLyrics);

    // // print the vector of songs
    // std::cout << "Songs sorted by lyrics: " << std::endl;
    // for (int i = 0; i < songs.size(); i++) {
    //     std::cout << ">> " << songs[i].getArtist() << " - " << songs[i].getTitle() << std::endl;
    // }

    // std::cout << std::endl << std::endl << std::endl;

    // search for a word in the lyrics of the songs
    std::string word = "house";
    std::vector<Song> songsWithWord = collection.search(word);

    std::cout << "Songs with the word \"" << word << "\" in the lyrics: " << std::endl;
    for (int i = 0; i < songsWithWord.size(); i++) {
        std::cout << ">> " << songsWithWord[i].getArtist() << " - " << songsWithWord[i].getTitle() << std::endl;
    }

    return 0;
}