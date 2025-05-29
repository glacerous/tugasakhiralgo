#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Lagu {
    string judul;
    string artis;
    string genre;
    int durasi;
    Lagu* next;
};

struct Playlist {
    string nama;
    Lagu* head;
    Playlist* next;
};

Playlist* daftarPlaylist = nullptr;

void menuUtama();
void buatPlaylist();
void lihatDaftarPlaylist();
void tampilkanMenuPlaylist(Playlist*);
Playlist* cariPlaylist(const string&);
void tambahLagu(Playlist*);
void tampilkanPlaylist(Playlist*);
void hapusLagu(Playlist*);
void hapusPlaylist(const string&);
void simpanKeFile();
void bacaDariFile();
void hapusSemuaPlaylist();
void urutkanLagu(Playlist* pl);

int main() {
    bacaDariFile();
    menuUtama();
    hapusSemuaPlaylist();
    return 0;
}

void menuUtama() {
    int pilihan;
    do {
        cout << "\n1.  Buat Playlist" << endl;
        cout << "2.  Lihat Playlist" << endl;
        cout << "0.  Keluar" << endl;
        cout << "> Pilih Menu : ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                buatPlaylist();
                break;
            case 2:
                lihatDaftarPlaylist();
                break;
            case 0:
                cout << "Keluar dari program.\n";
                simpanKeFile();
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}

void buatPlaylist() {
    string nama;
    cout << "\n---------------------- Buat Playlist ------------------------" << endl;
    cout << " Masukkan nama playlist baru kamu: ";
    getline(cin, nama);

    Playlist* baru = new Playlist{nama, nullptr, nullptr};
    baru->next = daftarPlaylist;
    daftarPlaylist = baru;

    cout << "\n Playlist [" << nama << "] berhasil dibuat!" << endl;
    cout << " Saatnya mengisi playlist ini dengan lagu favoritmu!" << endl;

    simpanKeFile(); // otomatis simpan
    tampilkanMenuPlaylist(baru);
}

void lihatDaftarPlaylist() {
    Playlist* temp = daftarPlaylist;
    int i = 1;
    cout << "\n--- Daftar Playlist ---\n";
    while (temp) {
        cout << i++ << ". " << temp->nama << endl;
        temp = temp->next;
    }
    if (daftarPlaylist == nullptr) cout << "Belum ada playlist.\n";

    cout << "\nMasukkan nama playlist untuk dikelola (atau kosong untuk kembali): ";
    string nama;
    getline(cin, nama);
    if (!nama.empty()) {
        Playlist* p = cariPlaylist(nama);
        if (p) tampilkanMenuPlaylist(p);
        else cout << "Playlist tidak ditemukan.\n";
    }
}

void tampilkanMenuPlaylist(Playlist* pl) {
    int pilihan;
    do {
        cout << "\n---------------------- Playlist [" << pl->nama << "] ------------------------\n";
        cout << "\n Pilihan Menu:\n";
        cout << " 1. Lihat isi playlist\n";
        cout << " 2. Tambah lagu ke playlist\n";
        cout << " 3. Urutkan lagu berdasarkan durasi (short - long)\n";
        cout << " 4. Hapus lagu dari playlist\n";
        cout << " 5. Hapus playlist\n";
        
        cout << " 0. Kembali ke menu utama\n";
        cout << "\n > Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                tampilkanPlaylist(pl);
                break;
            case 2:
                tambahLagu(pl);
                break;
            case 3:
                urutkanLagu(pl);
                break;
            case 4:
                hapusLagu(pl);
                break;
            case 5:
                hapusPlaylist(pl->nama);
                return; // kembali ke menu utama
            case 0:
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}

Playlist* cariPlaylist(const string& nama) {
    Playlist* temp = daftarPlaylist;
    while (temp) {
        if (temp->nama == nama) return temp;
        temp = temp->next;
    }
    return nullptr;
}

void tambahLagu(Playlist* pl) {
    string judul, artis, genre;
    int durasi;
    cout << "Judul: "; getline(cin, judul);
    cout << "Artis: "; getline(cin, artis);
    cout << "Genre: "; getline(cin, genre);
    cout << "Durasi (detik): "; cin >> durasi; cin.ignore();

    if (judul.empty() || artis.empty() || genre.empty() || durasi <= 0) {
    cout << "Data lagu tidak valid. Lagu tidak ditambahkan.\n";
    return;
}
    Lagu* baru = new Lagu{judul, artis, genre, durasi, nullptr};
    if (!pl->head) pl->head = baru;
    else {
        Lagu* temp = pl->head;
        while (temp->next) temp = temp->next;
        temp->next = baru;
    }
    cout << "Lagu berhasil ditambahkan.\n";
    simpanKeFile();
}

void tampilkanPlaylist(Playlist* pl) {
    Lagu* temp = pl->head;
    int i = 1;
    while (temp) {
        cout << i++ << ". " << temp->judul << " - " << temp->artis
             << " [" << temp->genre << "] (" << temp->durasi << " detik)\n";
        temp = temp->next;
    }
    if (!pl->head) cout << "Playlist kosong.\n";
}

void urutkanLagu(Playlist* pl) {
    if (!pl->head || !pl->head->next) {
        cout << "Playlist terlalu sedikit untuk diurutkan.\n";
        return;
    }

    bool swapped;
    do {
        swapped = false;
        Lagu* current = pl->head;
        Lagu* prev = nullptr;
        Lagu* next = nullptr;

        while (current->next) {
            next = current->next;
            if (current->durasi > next->durasi) {
                // Tukar node
                if (prev) prev->next = next;
                else pl->head = next;

                current->next = next->next;
                next->next = current;

                swapped = true;
                prev = next;
            } else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);

    cout << "Playlist berhasil diurutkan berdasarkan durasi (pendek -> panjang).\n";
    simpanKeFile();
}

void hapusLagu(Playlist* pl) {
    string judul;
    cout << "Judul lagu yang ingin dihapus: ";
    getline(cin, judul);

    Lagu* temp = pl->head;
    Lagu* prev = nullptr;
    while (temp && temp->judul != judul) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        cout << "Lagu tidak ditemukan.\n";
        return;
    }
    if (!prev) pl->head = temp->next;
    else prev->next = temp->next;
    delete temp;
    cout << "Lagu berhasil dihapus.\n";
    simpanKeFile();
}

void hapusPlaylist(const string& nama) {
    Playlist *temp = daftarPlaylist, *prev = nullptr;
    while (temp && temp->nama != nama) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return;
    while (temp->head) {
        Lagu* hapus = temp->head;
        temp->head = temp->head->next;
        delete hapus;
    }
    if (!prev) daftarPlaylist = temp->next;
    else prev->next = temp->next;
    delete temp;
    cout << "Playlist berhasil dihapus.\n";
    simpanKeFile();
}

void simpanKeFile() {
    ofstream file("playlist.txt");
    Playlist* p = daftarPlaylist;
    while (p) {
        file << "#PLAYLIST;" << p->nama << endl;
        Lagu* l = p->head;
        while (l) {
            file << l->judul << ";" << l->artis << ";" << l->genre << ";" << l->durasi << endl;
            l = l->next;
        }
        file << "#END" << endl;
        p = p->next;
    }
    file.close();
}

void bacaDariFile() {
    ifstream file("playlist.txt");
    if (!file.is_open()) return;
    hapusSemuaPlaylist();

    string line;
    Playlist* current = nullptr;
    while (getline(file, line)) {
        if (line.find("#PLAYLIST;") == 0) {
            string nama = line.substr(10);
            current = new Playlist{nama, nullptr, daftarPlaylist};
            daftarPlaylist = current;
        } else if (line == "#END") {
            current = nullptr;
        } else if (current) {
            size_t p1 = line.find(';');
            size_t p2 = line.find(';', p1+1);
            size_t p3 = line.find(';', p2+1);
            string judul = line.substr(0, p1);
            string artis = line.substr(p1+1, p2-p1-1);
            string genre = line.substr(p2+1, p3-p2-1);
            int durasi = stoi(line.substr(p3+1));
            Lagu* baru = new Lagu{judul, artis, genre, durasi, nullptr};
            if (!current->head) current->head = baru;
            else {
                Lagu* temp = current->head;
                while (temp->next) temp = temp->next;
                temp->next = baru;
            }
        }
    }
    file.close();
}

void hapusSemuaPlaylist() {
    while (daftarPlaylist) {
        Playlist* p = daftarPlaylist;
        daftarPlaylist = daftarPlaylist->next;
        while (p->head) {
            Lagu* l = p->head;
            p->head = p->head->next;
            delete l;
        }
        delete p;
    }   
}
