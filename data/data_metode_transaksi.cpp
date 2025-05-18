#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_utilities.h"
#include "data_metode_transaksi.h"

using json = nlohmann::json;
using namespace std;

int main()
{
    // --- Contoh Penggunaan ---

    // Deklarasi Variabel
    MetodeTransaksi dataMetodeTransaksi[MAX_SIZE]; // Data Utama
    int sizeDataMetodeTransaksi = 0;               // Size Data Utama

    // -- (READ) Menampilkan Data --
    GetAllMetodeTransaksi(dataMetodeTransaksi, sizeDataMetodeTransaksi); // Mengambil data terbaru dari JSON

    for (int i = 0; i < sizeDataMetodeTransaksi; i++)
    {
        cout << i + 1 << "." << endl;
        cout << "ID: " << dataMetodeTransaksi[i].id << endl;
        cout << "Metode: " << dataMetodeTransaksi[i].metode << endl;
        cout << endl;
    }

    // -- (CREATE) Menambahkan Data Baru --
    MetodeTransaksi dataMetodeBaru;                            // Input Manual: getline(cin, dataMetodeBaru.metode);
    dataMetodeBaru.id = GetFreeMetodeTransaksiId(dataMetodeTransaksi, sizeDataMetodeTransaksi);
    cout << "Masukkan Nama Metode Baru:";
    getline(cin, dataMetodeBaru.metode);
    cout << endl;

    TambahMetodeTransaksi(dataMetodeTransaksi, sizeDataMetodeTransaksi, dataMetodeBaru);

    // -- (UPDATE) Memperbarui Data --
    int updateIndex = -1;
    string _updateTemp; // Jika input manual

    cout << "Mengubah data metode transaksi" << endl;
    for (int i = 0; i < sizeDataMetodeTransaksi; i++)
    {
        cout << i + 1 << "." << endl;
        cout << "ID: " << dataMetodeTransaksi[i].id << endl;
        cout << "Metode: " << dataMetodeTransaksi[i].metode << endl;
        cout << endl;
    }

    getline(cin, _updateTemp);
    updateIndex = stoi(_updateTemp); // string to integer
    updateIndex--;

    // Membuat pointer untuk menunjuk ke item data utama yang diedit
    MetodeTransaksi *dataMetodeDiperbarui;
    dataMetodeDiperbarui = &dataMetodeTransaksi[updateIndex];

    getline(cin, _updateTemp);
    if (_updateTemp != "")
    {
        dataMetodeDiperbarui->metode = _updateTemp;
    }
    
    SimpanValidasiTanaman(dataMetodeTransaksi, sizeDataMetodeTransaksi); // Note: Simpan dengan menggunakan data utama, jangan data yang diperbarui

    // -- (DELETE) Menghapus Data --
    int deleteIndex = -1;
    string _deleteTemp; // Jika input manual

    cout << "Menghapus data metode transaksi" << endl;
    for (int i = 0; i < sizeDataMetodeTransaksi; i++)
    {
        cout << i++ << "." << endl;
        cout << "ID: " << dataMetodeTransaksi[i].id << endl;
        cout << "Metode: " << dataMetodeTransaksi[i].metode << endl;
        cout << endl;
    }

    getline(cin, _deleteTemp); // Input Data
    deleteIndex = stoi(_deleteTemp); // Konversi ke integer
    deleteIndex--; // Kurangkan sesuai offset index (-1)

    MetodeTransaksi dataMetodeDihapus = dataMetodeTransaksi[deleteIndex];
    HapusMetodeTransaksi(dataMetodeTransaksi, sizeDataMetodeTransaksi, dataMetodeDihapus); // (Data Utama, Size Data Utama, Data Utama Indeks Dihapus)

    return 0;
}