#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_utilities.h"
#include "data_tanaman.h"

using json = nlohmann::json;
using namespace std;

int main()
{
    // --- Contoh Penggunaan ---
    // Deklarasi Variabel
    Tanaman dataTanaman[MAX_SIZE]; // Data Utama Tanaman
    int sizeDataTanaman = 0;       // Size Data Utama Tanaman

    Supplier dataSupplier[MAX_SIZE]; // Data Utama Supplier
    int sizeDataSupplier = 0;        // Size Data Utama Supplier

    MetodeTransaksi dataMetodeTransaksi[MAX_SIZE]; // Data Utama Metode Transaksi
    int sizeDataMetodeTransaksi = 0;               // Size Data Utama Metode Transaksi

    Kategori dataKategori[MAX_SIZE]; // Data Utama Metode Transaksi
    int sizeDataKategori = 0;        // Size Data Utama Metode Transaksi

    // -- (READ) Contoh Menampilkan Data --
    GetAllTanaman(dataTanaman, sizeDataTanaman); // Mengambil data terbaru dari JSON
    GetAllSupplier(dataSupplier, sizeDataSupplier);
    GetAllMetodeTransaksi(dataMetodeTransaksi, sizeDataMetodeTransaksi);
    GetAllKategori(dataKategori, sizeDataKategori);

    // Menampilkan Data
    for (int i = 0; i < sizeDataTanaman; i++)
    {
        cout << i + 1 << "." << endl;
        cout << "ID: " << dataTanaman[i].id << endl;
        cout << "Nama Tanaman: " << dataTanaman[i].namaTanaman << endl;
        cout << "Supplier: " << dataTanaman[i].supplier.username << endl;
        cout << "Kategori: " << dataTanaman[i].kategori.namaKategori << endl;
        cout << "Harga: Rp" << dataTanaman[i].harga << endl;
        cout << endl;

        cout << endl;
    }

    // -- (CREATE) Menambahkan Data Baru --
    string _temp;
    int _indexKategori;
    int _indexSupplier;

    // Pilih Supplier
    cout << "Supplier" << endl;
    for (int i = 0; i < sizeDataSupplier; i++)
    {
        cout << i + 1 << ". " << dataSupplier[i].username << endl;
    }
    cout << endl;

    _indexSupplier = 2; // Memilih kategori nomor 2
    _indexSupplier--;   // Menurunkan 1 angka untuk menyesuaikan offset index

    // Pilih Kategori
    cout << "Kategori" << endl;
    for (int i = 0; i < sizeDataKategori; i++)
    {
        cout << i + 1 << ". " << dataKategori[i].namaKategori << endl;
    }
    cout << endl;

    _indexKategori = 2; // Memilih kategori nomor 2
    _indexKategori--;   // Menurunkan 1 angka untuk menyesuaikan offset index

    Tanaman dataTanamanBaru;
    dataTanamanBaru.id = GetFreeTanamanId();
    dataTanamanBaru.namaTanaman = "Kipli";
    dataTanamanBaru.supplier = dataSupplier[_indexSupplier];
    dataTanamanBaru.kategori = dataKategori[_indexKategori];
    dataTanamanBaru.harga = 5000;

    TambahTanaman(dataTanaman, sizeDataTanaman, dataTanamanBaru);

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
    Tanaman *dataTanamanDiedit;
    dataTanamanDiedit = &dataTanaman[updateIndex];
    dataTanamanDiedit->namaTanaman = "Kipli Es"; // Input Manual: getline(cin, dataMetodeDiperbarui->metode);

    SimpanTanaman(dataTanaman, sizeDataTanaman); // Note: Simpan dengan menggunakan data utama, jangan data yang diperbarui

    // -- (DELETE) Menghapus Data --
    int deleteIndex = -1;
    string _deleteTemp;

    // Pilih item yang diedit
    deleteIndex = 1; // Memilih nomor 1
    deleteIndex--;   // Menurunkan 1 angka untuk menyesuaikan offset index

    // Versi Input Manual:
    // getline(cin, _deleteTemp); // Memilih nomor
    // deleteIndex = stoi(_deleteTemp)-- // Menurunkan 1 angka untuk menyesuaikan offset index

    HapusTanaman(dataTanaman, sizeDataTanaman, dataTanaman[deleteIndex]); // (Data Utama, Size Data Utama, Data Utama Indeks Dihapus)

    return 0;
}