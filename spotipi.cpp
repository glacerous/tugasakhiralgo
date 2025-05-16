#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Song {
    string title;
    string artist;
    Song* next;
};

void addSong(string title, string artist);
void displaySongs();
void searchSong(string keyword);
void sortSongs();
void saveToFile();
void loadFromFile();
void clearMemory();
void createPlaylist();

Song* head = nullptr;

int main() {
    int choice;
    string title, artist, keyword;

    loadFromFile();

    do {
        cout << "\n=== spotipy ===\n";
        cout << "1. Tambah Lagu\n";
        cout << "2. Lihat Semua Lagu\n";
        cout << "3. Cari Lagu\n";
        cout << "4. Urutkan Lagu (berdasarkan judul)\n";
        cout << "5. Simpan & Keluar\n";
        cout << "6. Buat Playlist\n";
        cout << "Pilihan: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Judul: ";
                getline(cin, title);
                cout << "Artis: ";
                getline(cin, artist);
                addSong(title, artist);
                break;
            case 2:
                displaySongs();
                break;
            case 3:
                cout << "Masukkan keyword judul: ";
                getline(cin, keyword);
                searchSong(keyword);
                break;
            case 4:
                sortSongs();
                break;
            case 5:
                saveToFile();
                break;
            case 6:
                createPlaylist();
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (choice != 5);

    clearMemory();
    return 0;
}


void addSong(string title, string artist) {
    // kosong
}

void displaySongs() {
    // kosong
}

void searchSong(string keyword) {
    // kosong
}

void sortSongs() {
    // kosong
}

void saveToFile() {
    // kosong
}

void loadFromFile() {
    // kosong
}

void clearMemory() {
    // kosong
}

void createPlaylist() {
    // kosong
}
