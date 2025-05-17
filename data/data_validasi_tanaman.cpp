#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_struct.h"
#include "data_validasi_tanaman.h"

using json = nlohmann::json;
using namespace std;

int main()
{
    // --- Contoh Penggunaan ---
    // Deklarasi Variabel
    ValidasiTanaman dataValidasi[MAX_SIZE]; // Data Utama Validasi
    int sizeDataValidasi = 0;               // Size Data Utama Validasi

    Tanaman dataTanaman[MAX_SIZE]; // Data Utama Tanaman
    int sizeDataTanaman = 0;       // Size Data Utama Tanaman

    Kategori dataKategori[MAX_SIZE]; // Data Utama Kategori
    int sizeDataKategori = 0;       // Size Data Utama Kategori

    Suplai dataSuplai[MAX_SIZE]; // Data Utama Suplai
    int sizeDataSuplai = 0;      // Size Data Utama Suplai

    // -- (READ) Contoh Menampilkan Data --
    GetAllValidasi(dataValidasi, sizeDataValidasi); // Mengambil data terbaru dari JSON
    GetAllTanaman(dataTanaman, sizeDataTanaman);
    GetAllSuplai(dataSuplai, sizeDataSuplai);
    GetAllKategori(dataKategori, sizeDataKategori);

    // Menampilkan Data
    for (int i = 0; i < sizeDataValidasi; i++)
    {
        cout << i + 1 << "." << endl;
        cout << "ID: " << dataValidasi[i].id << endl;
        cout << "Nama Tanaman: " << dataValidasi[i].tanaman.namaTanaman << endl;
        cout << "Supplier: " << dataValidasi[i].suplai.supplier.username << endl;
        cout << "Stok Diterima (Suplai): " << dataValidasi[i].stok_diterima << "(" << dataValidasi[i].suplai.jumlah << ")" << endl;

        cout << endl;
    }
    cout << endl;

    // -- (CREATE) Proses Memvalidasi Tanaman --
    ValidasiTanaman validasiBaru;
    string _temp;
    int _indexValidasi;
    int _indexTanaman;

    Suplai suplaiBelumDivalidasi[MAX_SIZE];
    int sizeBelumDivalidasi = 0;
    for (int i = 0; i < sizeDataSuplai; i++)
    {
        if (dataSuplai[i].statusValidasi == false)
        {
            cout << sizeBelumDivalidasi + 1 << ". " << dataSuplai[i].namaTanaman << "(" << dataSuplai[i].supplier.username << ")" << endl;
            suplaiBelumDivalidasi[sizeBelumDivalidasi] = dataSuplai[i];
            sizeBelumDivalidasi++;
        }
    }
    cout << endl;
    // Pilih suplai untuk divalidasi
    _indexValidasi = 1; // Pilih nomor 1 (Paling atas)
    _indexValidasi--;

    // --- Jika Tanaman Baru --- 
    Tanaman tanamanBaru;
    int _indexKategori;

    cout << "Kategori" << endl;
    for (int i = 0; i < sizeDataSuplai; i++)
    {
        cout << i + 1 << ". " << dataKategori[i].namaKategori << endl;
    }
    cout << endl;
    _indexKategori = 3; // Pilih nomor 3
    _indexKategori--;

    // Mengisi data tanaman baru dan validasi (Form)
    tanamanBaru.id = GetFreeTanamanId(dataTanaman, sizeDataTanaman);
    tanamanBaru.namaTanaman = "Lidah Buaya";
    tanamanBaru.kategori = dataKategori[_indexKategori];
    tanamanBaru.harga = 4000;
    tanamanBaru.supplier = suplaiBelumDivalidasi[_indexValidasi].supplier; // Otomatis menetapkan supllier dari data suplai

    validasiBaru.id = GetFreeValidasiId(dataValidasi, sizeDataValidasi);
    validasiBaru.tanaman = tanamanBaru;
    validasiBaru.suplai = suplaiBelumDivalidasi[_indexValidasi];
    validasiBaru.stok_diterima = 5;

    // Memanggil fungsi untuk menyimpan data baru tanaman dan validasi
    TambahTanaman(dataTanaman, sizeDataTanaman, tanamanBaru);
    TambahValidasi(dataValidasi, sizeDataValidasi, validasiBaru);

    // --- Jika Restock --- 
    cout << endl << "Tanaman" << endl;
    for (int i = 0; i < sizeDataTanaman; i++)
    {
        cout << i + 1 << ". " << dataTanaman[i].namaTanaman << endl;
    }
    cout << endl;
    // Pilih Tanaman
    _indexTanaman = 4; // Memilih kategori nomor 2
    _indexTanaman--;   // Menurunkan 1 angka untuk menyesuaikan offset index

    validasiBaru.id = GetFreeValidasiId(dataValidasi, sizeDataValidasi);
    validasiBaru.suplai = suplaiBelumDivalidasi[_indexValidasi];
    validasiBaru.tanaman = dataTanaman[_indexTanaman];
    validasiBaru.stok_diterima = 5;

    TambahValidasi(dataValidasi, sizeDataValidasi, validasiBaru);

    return 0;
}