//setw untuk mengatur lebar kolom

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Struct barang inventory
struct InventoryItem {
    string name;
    string quantity;
    string category;
};

const int MAX_INVENTORY_SIZE = 100; // Jumlah maksimum barang dalam inventory

/*Struct untuk counter jumlah barang dalam inventory
   dan counter untuk array-nya*/
struct Inventory {
    InventoryItem items[MAX_INVENTORY_SIZE];
    int count = 0;
};

/* Fungsi untuk menampilkan daftar inventory
   (Memiliki jeda 5 detik di akhir, digunakan pada case 1)) */
void tampilkanInventory(const Inventory& inventory) {
    if (inventory.count == 0) {
        cout << "Inventory masih kosong." << endl;
        _sleep (2000);
        cout << "\033[2J\033[H"; // clear screen
        return;
    }
    cout << "Daftar Inventory:" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << left << setw(6) << "Index" << setw(21) << "| Nama" << " " << "| " << setw(15) << "Jumlah" << "| " << "Kategori" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0; i < inventory.count; ++i) {
        cout << left << setw(6) << i << "| " << setw(20) << inventory.items[i].name << "| " << setw(15) << inventory.items[i].quantity << "| " << inventory.items[i].category << endl;
    }
    cout << "-------------------------------------------------------------" << endl;
    cout << endl;
    _sleep (5000);
}

/* Fungsi untuk menampilkan daftar inventory
   (Tidak memiliki jeda di akhir, digunakan pada case 3 dan 4) */
void tampilkanInven(const Inventory& inventory) {
    if (inventory.count == 0) {
        cout << "Inventory masih kosong." << endl;
        _sleep (2000);
        cout << "\033[2J\033[H"; // clear screen
        return;
    }
    cout << "Daftar Inventory:" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << left << setw(6) << "Index" << setw(21) << "| Nama" << " " << "| " << setw(15) << "Jumlah" << "| " << "Kategori" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0; i < inventory.count; ++i) {
        cout << left << setw(6) << i << "| " << setw(20) << inventory.items[i].name << "| " << setw(15) << inventory.items[i].quantity << "| " << inventory.items[i].category << endl;
    }
    cout << "-------------------------------------------------------------" << endl;
}

// Fungsi untuk menghapus barang pada index tertentu
void hapusItemBerdasarkanIndex(Inventory& inventory, int itemIndex) {
    if (itemIndex >= 0 && itemIndex < inventory.count) {
        for (int i = itemIndex; i < inventory.count - 1; ++i) {
            inventory.items[i] = inventory.items[i + 1];
        }
        inventory.count--;
        cout << "Barang pada indeks " << itemIndex << " berhasil dihapus dari inventory." << endl;
        _sleep (3000);
        cout << "\033[2J\033[H"; // clear screen
    } else {
        cout << "Indeks barang tidak valid." << endl;
    }
}

// Fungsi untuk menyimpan data inventory ke dalam sebuah file txt
void simpanInventoryKeFile(const Inventory& inventory) {
    ofstream outFile("inventory.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < inventory.count; ++i) {
            outFile << inventory.items[i].name << "," << inventory.items[i].quantity << "," << inventory.items[i].category << endl;
        }
        outFile.close();
        cout << "Data inventory berhasil disimpan ke dalam file 'inventory.txt'." << endl;
    } else {
        cout << "Gagal menyimpan data inventory." << endl;
    }
}

// Fungsi untuk memuat data inventory dari sebuah file txt
void muatInventoryDariFile(Inventory& inventory) {
    ifstream inFile("inventory.txt");
    if (inFile.is_open()) {
        while (getline(inFile, inventory.items[inventory.count].name, ',') &&
               getline(inFile, inventory.items[inventory.count].quantity, ',') &&
               getline(inFile, inventory.items[inventory.count].category)) {
            inventory.count++;
        }
        inFile.close();
        cout << "Data inventory berhasil dimuat dari file 'inventory.txt'." << endl;
    } else {
        cout << "File 'inventory.txt' tidak ditemukan. Membuat file inventory baru." << endl;
    }
}

int main() {
    Inventory inventory;

    muatInventoryDariFile(inventory);

    int pilihan;
    // loop do while agar user dapat masuk kembali ke dalam menu setelah memilih menu 1-6
    do {
        cout << "-----------------------------------------------" << endl;
        cout << "                Program Inventory               " << endl;
        cout << "-----------------------------------------------" << endl << endl;
        cout << "Jumlah total barang: " << inventory.count << endl;
        cout << "Maksimum jumlah barang: " << MAX_INVENTORY_SIZE << endl;
        cout << endl << "Menu:" << endl;
        cout << "1. Tampilkan Inventory" << endl;
        cout << "2. Tambah Barang Baru" << endl;
        cout << "3. Ubah Data Inventory" << endl;
        cout << "4. Hapus Barang" << endl;
        cout << "5. Hapus Semua Data Inventory" << endl;
        cout << "6. Simpan Data Inventory" << endl;
        cout << "7. Keluar" << endl << endl;
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "\033[2J\033[H"; // clear screen
                tampilkanInventory(inventory);
                break;
            case 2: {
                cout << "\033[2J\033[H"; // clear screen
                InventoryItem barang;
                cout << "Masukkan Nama Barang: ";
                cin.ignore();
                getline(cin, barang.name);
                cout << "WARNING!! UNTUK BERAT BARANG JIKA MENGGUNAKAN KOMA HARAP MENGGUNAKAN TITIK!!" << endl;
                cout << "Masukkan Jumlah/Berat Barang: ";
                getline(cin, barang.quantity);
                cout << "Masukkan Kategori Barang: ";
                getline(cin, barang.category);

                if (inventory.count < MAX_INVENTORY_SIZE) {
                    inventory.items[inventory.count] = barang;
                    inventory.count++;
                    cout << "Barang baru berhasil ditambahkan!" << endl;
                    _sleep (3000);
                    cout << "\033[2J\033[H"; // clear screen
                } else {
                    cout << "Inventory sudah penuh. Tidak dapat menambahkan barang baru." << endl;
                    _sleep (3000);
                    cout << "\033[2J\033[H"; // clear screen
                }
                break;
            }
            case 3: {
                cout << "\033[2J\033[H"; // clear screen
                if (inventory.count > 0) {
                    char a;
                    cout << "Apakah anda ingin mengubah data inventory? (y/n): ";
                    cin >> a;
                    if (a == 'y' || a == 'Y') {
                        tampilkanInven(inventory);
                        int itemIndex;
                        cout << "Masukkan indeks barang yang ingin diubah: ";
                        cin >> itemIndex;
                        cin.ignore(); // Membersihkan newline di buffer

                        if (itemIndex >= 0 && itemIndex < inventory.count) {
                            int pilihan;
                            cout << "Pilih data yang ingin diubah:" << endl;
                            cout << "1. Nama Barang" << endl;
                            cout << "2. Jumlah Barang" << endl;
                            cout << "3. Kategori Barang" << endl;
                            cout << "Pilih: ";
                            cin >> pilihan;
                            cin.ignore(); // Membersihkan newline di buffer

                            switch (pilihan) {
                                case 1:
                                    cout << "Masukkan Nama Barang baru: ";
                                    getline(cin, inventory.items[itemIndex].name);
                                    cout << "Nama Barang berhasil diubah.";
                                    _sleep (3000);
                                    break;
                                case 2:
                                    cout << "WARNING!! UNTUK BERAT BARANG JIKA MENGGUNAKAN KOMA HARAP MENGGUNAKAN TITIK!!" << endl;
                                    cout << "Masukkan Jumlah Barang baru: ";
                                    getline(cin, inventory.items[itemIndex].quantity);
                                    cout << "Jumlah Barang berhasil diubah.";
                                    _sleep (3000);
                                    break;
                                case 3:
                                    cout << "Masukkan Kategori Barang baru: ";
                                    getline(cin, inventory.items[itemIndex].category);
                                    cout << "Kategori Barang berhasil diubah.";
                                    _sleep (3000);
                                    break;
                                default:
                                    cout << "Pilihan tidak valid. Tidak ada perubahan yang dilakukan." << endl;
                                    _sleep (2000);
                                    break;
                            }
                        } else {
                            cout << endl << "Indeks barang tidak valid." << endl;
                            _sleep (3000);
                        }
                    }else{
                        cout << endl << "Tidak ada perubahan yang dilakukan." << endl;
                        _sleep (3000);
                    }
                    cout << "\033[2J\033[H"; // clear screen
                } else {
                    cout << "Inventory kosong. Tidak ada data yang dapat diubah." << endl;
                }
                break;
            }
            case 4: {
                cout << "\033[2J\033[H"; // clear screen
                if (inventory.count > 0) {
                    tampilkanInven(inventory);
                    int itemIndex;
                    cout << "Masukkan indeks barang yang ingin dihapus: ";
                    cin >> itemIndex;
                    cin.ignore(); // Membersihkan newline di buffer
                    hapusItemBerdasarkanIndex(inventory, itemIndex);
                } else {
                    cout << "Tidak ada barang dalam inventory yang dapat dihapus." << endl;
                    _sleep (3000);
                    cout << "\033[2J\033[H"; // clear screen
                }
                break;
            }
            case 5: {
                cout << "\033[2J\033[H"; // clear screen
                char option;
                cout << "Hapus semua data inventory? (y/n): ";
                cin >> option;
                if (option == 'y' || option == 'Y') {
                    inventory.count = 0;
                    cout << "Semua data inventory berhasil dihapus." << endl;
                    _sleep (3000);
                }else{
                    cout << "Semua data inventory tidak dihapus." << endl;
                    _sleep (2000);
                }
                cout << "\033[2J\033[H"; // clear screen
                break;
            }
            case 6:
                cout << "\033[2J\033[H"; // clear screen
                simpanInventoryKeFile(inventory);
                _sleep (3000);
                cout << endl;
                break;
            case 7:
                cout << "Menutup program..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
                break;
        }
    } while (pilihan != 7);

    return 0;
}
