#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_utilities.h"
#include "data_pembeli.h"

using json = nlohmann::json;
using namespace std;

int main()
{
    // --- Contoh Penggunaan ---
    // Deklarasi Variabel
    Pembeli dataPembeli[MAX_SIZE]; // Data Utama Pembeli
    int sizeDataPembeli = 0;        // Size Data Utama Pembeli

    // -- (READ) Contoh Menampilkan Data --
    GetAllPembeli(dataPembeli, sizeDataPembeli); // Mengambil data terbaru dari JSON

    // Menampilkan Data
    for (int i = 0; i < sizeDataPembeli; i++)
    {
        cout << i + 1 << "." << endl;
        cout << "ID: " << dataPembeli[i].id << endl;
        cout << "Username: " << dataPembeli[i].username << endl;

        cout << endl;
    }

    // -- (CREATE) Register Pembeli Baru --
    Pembeli dataPembeliBaru;
    dataPembeliBaru.id = GetFreePembeliId();
    dataPembeliBaru.username = "Dimas";
    dataPembeliBaru.password = "057";

    TambahPembeli(dataPembeli, sizeDataPembeli, dataPembeliBaru);

    // -- (UPDATE) Memperbarui Data --
    int updateIndex = -1;
    string _updateTemp; // Jika input manual

    // Pilih item yang diedit
    updateIndex = 2; // Memilih nomor 2
    updateIndex--;   // Menurunkan 1 angka untuk menyesuaikan offset index

    // Versi Input Manual:
    // getline(cin, _updateTemp);
    // updateIndex = stoi(_updateTemp)--

    // Membuat pointer untuk menunjuk ke item data utama yang diedit
    Pembeli *dataPembeliDiedit;
    dataPembeliDiedit = &dataPembeli[updateIndex];
    dataPembeliDiedit->username = "xxX_Tzy_Xxx"; // Input Manual: getline(cin, dataPembeliDiedit->username->username);

    SimpanPembeli(dataPembeli, sizeDataPembeli); // Note: Simpan dengan menggunakan data utama, jangan data yang diperbarui

    // -- (DELETE) Menghapus Data --
    int deleteIndex = -1;
    string _deleteTemp;

    // Pilih item yang diedit
    deleteIndex = 1; // Memilih nomor 1
    deleteIndex--;   // Menurunkan 1 angka untuk menyesuaikan offset index

    // Versi Input Manual:
    // getline(cin, _deleteTemp); // Memilih nomor
    // deleteIndex = stoi(_deleteTemp)-- // Menurunkan 1 angka untuk menyesuaikan offset index

    HapusPembeli(dataPembeli, sizeDataPembeli, dataPembeli[deleteIndex]); // (Data Utama, Size Data Utama, Data Utama Indeks Dihapus)

    return 0;
}