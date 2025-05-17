#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include "nlohmann/json.hpp"
#include "data_struct.h"
#include "data_suplai.h"

using json = nlohmann::json;
using namespace std;

int main()
{
    // --- Contoh Penggunaan ---
    // Deklarasi Variabel
    Suplai dataSuplai[MAX_SIZE]; // Data Utama Suplai
    int sizeDataSuplai = 0;      // Size Data Utama Suplai

    Supplier dataSupplier[MAX_SIZE]; // Data Utama Supplier
    int sizeDataSupplier = 0;        // Size Data Utama Supplier
    
    MetodeTransaksi dataMetodeTransaksi[MAX_SIZE]; // Data Utama Metode Transaksi
    int sizeDataMetodeTransaksi = 0;               // Size Data Utama Metode Transaksi
    
    // -- (READ) Contoh Menampilkan Data --
    GetAllSuplai(dataSuplai, sizeDataSuplai); // Mengambil data terbaru dari JSON
    GetAllSupplier(dataSupplier, sizeDataSupplier);
    GetAllMetodeTransaksi(dataMetodeTransaksi, sizeDataMetodeTransaksi);

    // Menampilkan Data
    for (int i = 0; i < sizeDataSuplai; i++)
    {
        cout << i + 1 << "." << endl;
        cout << "ID: " << dataSuplai[i].id << endl;
        cout << "Nama Tanaman: " << dataSuplai[i].namaTanaman << endl;
        cout << "Supplier: " << dataSuplai[i].supplier.username << endl;
        cout << "Jumlah: " << dataSuplai[i].jumlah << endl;
        cout << "Tanggal Suplai: Rp" << dataSuplai[i].tanggalSuplai << endl;
        cout << endl;

        cout << endl;
    }

    // -- (CREATE) Menambahkan Data Baru --
    string _temp;
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

    Suplai dataSuplaiBaru;
    dataSuplaiBaru.id = GetFreeSuplaiId(dataSuplai, sizeDataSuplai);
    dataSuplaiBaru.namaTanaman = "Hawktus";
    dataSuplaiBaru.supplier = dataSupplier[_indexSupplier];
    dataSuplaiBaru.jumlah = 10;

    TambahSuplai(dataSuplai, sizeDataSuplai, dataSuplaiBaru);

    // -- (UPDATE) Memperbarui Data --
    int updateIndex = -1;
    string _updateTemp; // Jika input manual

    // Pilih item yang diedit
    updateIndex = 5; // Memilih nomor 2
    updateIndex--;   // Menurunkan 1 angka untuk menyesuaikan offset index

    // Versi Input Manual:
    // getline(cin, _updateTemp);
    // updateIndex = stoi(_updateTemp)--

    // Membuat pointer untuk menunjuk ke item data utama yang diedit
    Suplai *dataSuplaiDiedit;
    dataSuplaiDiedit = &dataSuplai[updateIndex];
    dataSuplaiDiedit->namaTanaman = "Kaktus"; // Input Manual: getline(cin, dataMetodeDiperbarui->metode);

    SimpanDataSuplai(dataSuplai, sizeDataSuplai); // Note: Simpan dengan menggunakan data utama, jangan data yang diperbarui

    // -- (DELETE) Menghapus Data --
    int deleteIndex = -1;
    string _deleteTemp;

    // Pilih item yang diedit
    deleteIndex = 1; // Memilih nomor 1
    deleteIndex--;   // Menurunkan 1 angka untuk menyesuaikan offset index

    // Versi Input Manual:
    // getline(cin, _deleteTemp); // Memilih nomor
    // deleteIndex = stoi(_deleteTemp)-- // Menurunkan 1 angka untuk menyesuaikan offset index

    HapusSuplai(dataSuplai, sizeDataSuplai, dataSuplai[deleteIndex]); // (Data Utama, Size Data Utama, Data Utama Indeks Dihapus)

    return 0;
}