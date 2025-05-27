#include <iostream>
#include <iomanip>
#include <fstream>
#include "data_supplier.h"

using json = nlohmann::json;
using namespace std;

int main()
{
    // --- Contoh Penggunaan ---
    // Deklarasi Variabel
    Supplier dataSupplier[MAX_SIZE]; // Data Utama Supplier
    int sizeDataSupplier = 0;        // Size Data Utama Supplier

    MetodeTransaksi dataMetodeTransaksi[MAX_SIZE]; // Data Utama Metode Transaksi
    int sizeDataMetodeTransaksi = 0;               // Size Data Utama Metode Transaksi

    // -- (READ) Contoh Menampilkan Data --
    GetAllSupplier(dataSupplier, sizeDataSupplier); // Mengambil data terbaru dari JSON
    GetAllMetodeTransaksi(dataMetodeTransaksi, sizeDataMetodeTransaksi);

    // Menampilkan Data
    for (int i = 0; i < sizeDataSupplier; i++)
    {
        cout << i + 1 << "." << endl;
        cout << "ID: " << dataSupplier[i].id << endl;
        cout << "Username: " << dataSupplier[i].username << endl;
        cout << "Metode Tersedia: ";
        for (int j = 0; j < dataSupplier[i].sizeMetodeTersedia; j++)
        {
            cout << j + 1 << ". " << dataSupplier[i].metodeTersedia[j].metode << " ";
        }
        cout << endl;

        cout << endl;
    }

    // -- (CREATE) Register Supplier Baru --
    Supplier dataSupplierBaru;
    dataSupplierBaru.id = GetFreeSupplierId();
    dataSupplierBaru.username = "MTHermawan";
    dataSupplierBaru.password = "pointerko-cak";

    TambahSupplier(dataSupplier, sizeDataSupplier, dataSupplierBaru);

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
    Supplier *dataSupplierDiedit;
    dataSupplierDiedit = &dataSupplier[updateIndex];
    dataSupplierDiedit->username = "Remptyh"; // Input Manual: getline(cin, dataMetodeDiperbarui->metode);

    SimpanSupplier(dataSupplier, sizeDataSupplier); // Note: Simpan dengan menggunakan data utama, jangan data yang diperbarui

    // -- (DELETE) Menghapus Data --
    int deleteIndex = -1;
    string _deleteTemp;

    // Pilih item yang diedit
    deleteIndex = 2; // Memilih nomor 2
    deleteIndex--;   // Menurunkan 1 angka untuk menyesuaikan offset index

    // Versi Input Manual:
    // getline(cin, _deleteTemp); // Memilih nomor
    // deleteIndex = stoi(_deleteTemp)-- // Menurunkan 1 angka untuk menyesuaikan offset index

    HapusSupplier(dataSupplier, sizeDataSupplier, dataSupplier[deleteIndex]); // (Data Utama, Size Data Utama, Data Utama Indeks Dihapus)

    return 0;
}