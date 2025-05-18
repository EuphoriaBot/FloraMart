#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_utilities.h"
#include "data_kategori.h"

using json = nlohmann::json;
using namespace std;

// Mengubah nilai dari json ke kategori per data
int main()
{
    // --- Contoh Penggunaan ---

    // Deklarasi Variabel
    Kategori dataKategori[MAX_SIZE]; // Data Utama
    int sizeDataKategori = 0;        // Size Data Utama

    // -- (READ) Menampilkan Data --
    GetAllKategori(dataKategori, sizeDataKategori); // Mengambil data terbaru dari JSON

    for (int i = 0; i < sizeDataKategori; i++)
    {
        cout << i++ << "." << endl;
        cout << "ID: " << dataKategori[i].id << endl;
        cout << "Kategori: " << dataKategori[i].namaKategori << endl;
        cout << "Suhu: " << dataKategori[i].minSuhu << "C" << " - " << dataKategori[i].maxSuhu << "C" << endl;
        cout << "Media Tanam: " << dataKategori[i].mediaTanam << endl;
        cout << endl;
    }

    // -- (CREATE) Menambahkan Data Baru --
    Kategori dataKategoriBaru;                           // Deklarasi Data Kategori baru
    dataKategoriBaru.id = GetFreeKategoriId();           // Isi ID secara otomatis
    dataKategoriBaru.namaKategori = "Ini Kategori Baru"; // Input Manual: getline(cin, dataKategori.namaKategori);
    dataKategoriBaru.minSuhu = -1;                       // Input Manual: getline(cin, dataKategori.minSuhu);
    dataKategoriBaru.maxSuhu = 39.39;                    // Input Manual: getline(cin, dataKategori.maxSuhu);
    dataKategoriBaru.mediaTanam = "Air Coy";             // Input Manual: getline(cin, dataKategori.mediaTanam);

    TambahKategori(dataKategori, sizeDataKategori, dataKategoriBaru);

    // -- (UPDATE) Memperbarui Data --
    int updateIndex = -1;
    string _updateTemp; // Jika input manual

    // Pilih item yang diedit
    updateIndex = 4; // Memilih nomor 4
    updateIndex--;   // Menurunkan 1 angka untuk menyesuaikan offset index

    // Versi Input Manual:
    // getline(cin, _updateTemp);
    // updateIndex = stoi(_updateTemp)--

    // Membuat pointer untuk menunjuk ke item data utama yang diedit
    Kategori *dataKategoriDiperbarui;
    dataKategoriDiperbarui = &dataKategori[updateIndex];
    dataKategoriDiperbarui->namaKategori = "Apalah nama baru kategori"; // Input Manual: getline(cin, dataKategoriDiperbarui->namaKategori);

    SimpanKategori(dataKategori, sizeDataKategori); // Note: Simpan dengan menggunakan data utama, jangan data yang diperbarui

    // -- (DELETE) Menghapus Data --
    int deleteIndex = -1;
    string _deleteTemp; // Jika input manual

    // Pilih item yang diedit
    deleteIndex = 4; // Memilih nomor 4
    deleteIndex--;   // Menurunkan 1 angka untuk menyesuaikan offset index

    // Versi Input Manual:
    // getline(cin, _deleteTemp); // Memilih nomor
    // deleteIndex = stoi(_deleteTemp)-- // Menurunkan 1 angka untuk menyesuaikan offset index

    HapusKategori(dataKategori, sizeDataKategori, dataKategori[deleteIndex]); // (Data Utama, Size Data Utama, Data Utama Indeks Dihapus)

    return 0;
}