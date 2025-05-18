#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_utilities.h"
#include "data_transaksi.h"

using json = nlohmann::json;
using namespace std;

int main()
{
    // --- Contoh Penggunaan ---
    // Deklarasi Variabel
    Transaksi dataTransaksi[MAX_SIZE]; // Data Utama Transaksi
    int sizeDataTransaksi = 0;         // Size Data Utama Transaksi

    Tanaman dataTanaman[MAX_SIZE]; // Data Utama Tanaman
    int sizeDataTanaman = 0;       // Size Data Utama Tanaman

    Pembeli dataPembeli[MAX_SIZE]; // Data Utama Pembeli
    int sizeDataPembeli = 0;       // Size Data Utama Pembeli

    MetodeTransaksi dataMetodeTransaksi[MAX_SIZE]; // Data Utama Transaksi
    int sizeDataMetodeTransaksi = 0; // Size Data Utama Transaksi

    // -- (READ) Contoh Menampilkan Data --
    GetAllTransaksi(dataTransaksi, sizeDataTransaksi); // Mengambil data terbaru dari JSON
    GetAllTanaman(dataTanaman, sizeDataTanaman);
    GetAllPembeli(dataPembeli, sizeDataPembeli);
    GetAllMetodeTransaksi(dataMetodeTransaksi, sizeDataTransaksi);

    // Menampilkan Data
    for (int i = 0; i < sizeDataMetodeTransaksi; i++)
    {
        cout << i + 1 << "." << endl;
        cout << "ID: " << dataTransaksi[i].id << endl;
        cout << "Tanggal Transaksi: " << dataTransaksi[i].tanggalTransaksi << endl;
        cout << "Tanaman: " << dataTransaksi[i].tanaman.namaTanaman << "(" << dataTransaksi[i].tanaman.supplier.username <<")" << endl;
        cout << "Pembeli: " << dataTransaksi[i].pembeli.username << endl;
        cout << "Jumlah: " << dataTransaksi[i].jumlahTanaman << endl;
        cout << "Total Harga: " << dataTransaksi[i].totalHarga << endl;
        cout << "Metode Bayar : " << dataTransaksi[i].metodeBayar.metode << endl;
        cout << "Status: " << dataTransaksi[i].status << endl;
        cout << "Tanggal Pembayaran : " << dataTransaksi[i].tanggalPembayaran << endl;

        cout << endl;
    }
    cout << endl;

    // -- (CREATE) Proses Membeli Tanaman --
    string _temp;
    int _indexTanaman;
    int _indexMetodeBayar;

    Suplai suplaiBelumDivalidasi[MAX_SIZE];
    int sizeBelumDivalidasi = 0;

    cout << "Tanaman" << endl;
    for (int i = 0; i < sizeDataTanaman; i++)
    {
        cout << i + 1 << ". " << dataTanaman[i].namaTanaman << "(" << dataTanaman[i].supplier.username << ")" << endl;
    }
    cout << endl;
    // Pilih Tanaman Untuk dibeli
    _indexTanaman = 3; // Pilih nomor 3
    _indexTanaman--;

    // --- Proses Transaksi ---
    Tanaman tanamanBaru;
    int _indexKategori;

    cout << "Metode Bayar" << endl;
    for (int i = 0; i < sizeDataPembeli; i++)
    {
        cout << i + 1 << ". " << dataMetodeTransaksi[i].metode << endl;
    }
    cout << endl;
    _indexMetodeBayar = 2; // Pilih nomor 2
    _indexMetodeBayar--;

    // Mengisi data tanaman baru dan validasi (Form)
    Transaksi transaksiBaru;
    transaksiBaru.id = GetFreeTransaksiId();
    transaksiBaru.tanaman = dataTanaman[_indexTanaman];
    transaksiBaru.pembeli = dataPembeli[0]; // Membeli dengan akun pembeli1
    transaksiBaru.jumlahTanaman = 5; // Jumlah Pembelian Tanaman
    transaksiBaru.metodeBayar = dataMetodeTransaksi[_indexMetodeBayar];

    // Memanggil fungsi untuk menyimpan data baru tanaman dan validasi
    TambahTransaksi(dataTransaksi, sizeDataTransaksi, transaksiBaru);

    return 0;
}