#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_struct.h"
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
        cout << i++ << "." << endl;
        cout << "ID: " << dataMetodeTransaksi[i].id << endl;
        cout << "Metode: " << dataMetodeTransaksi[i].metode << endl;
        cout << endl;
    }

    // -- (CREATE) Menambahkan Data Baru --
    MetodeTransaksi dataMetodeBaru;                                                             // Deklarasi Data Metode baru
    dataMetodeBaru.id = GetFreeMetodeTransaksiId(dataMetodeTransaksi, sizeDataMetodeTransaksi); // Isi ID secara otomatis
    dataMetodeBaru.metode = "DANA";                                                             // Input Manual: getline(cin, dataMetodeBaru.metode);

    TambahMetodeTransaksi(dataMetodeTransaksi, sizeDataMetodeTransaksi, dataMetodeBaru);

    // -- (UPDATE) Memperbarui Data --
    int updateIndex = -1;
    string _updateTemp; // Jika input manual

    cout << "Mengubah data metode transaksi" << endl;
    for (int i = 0; i < sizeDataMetodeTransaksi; i++)
    {
        cout << i++ << "." << endl;
        cout << "ID: " << dataMetodeTransaksi[i].id << endl;
        cout << "Metode: " << dataMetodeTransaksi[i].metode << endl;
        cout << endl;
    }

    // Pilih item yang diedit
    updateIndex = 2; // Memilih nomor 2 (Mengubah metode gopay)
    updateIndex--;   // Menurunkan 1 angka untuk menyesuaikan offset index

    // Versi Input Manual:
    // getline(cin, _updateTemp);
    // updateIndex = stoi(_updateTemp)--

    // Membuat pointer untuk menunjuk ke item data utama yang diedit
    MetodeTransaksi *dataMetodeDiperbarui;
    dataMetodeDiperbarui = &dataMetodeTransaksi[updateIndex];
    dataMetodeDiperbarui->metode = "GoPay"; // Input Manual: getline(cin, dataMetodeDiperbarui->metode);

    // Menyimpan data yang sudah diperbarui
    SimpanDataMetodeTransaksi(dataMetodeTransaksi, sizeDataMetodeTransaksi); // Note: Simpan dengan menggunakan data utama, jangan data yang diperbarui

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

    // Pilih item yang diedit
    deleteIndex = 1; // Memilih nomor 1 (Menghapus qris)
    deleteIndex--;   // Menurunkan 1 angka untuk menyesuaikan offset index

    // Versi Input Manual:
    // getline(cin, _deleteTemp); // Memilih nomor
    // deleteIndex = stoi(_deleteTemp)-- // Menurunkan 1 angka untuk menyesuaikan offset index

    HapusMetodeTransaksi(dataMetodeTransaksi, sizeDataMetodeTransaksi, dataMetodeTransaksi[deleteIndex]); // (Data Utama, Size Data Utama, Data Utama Indeks Dihapus)

    return 0;
}