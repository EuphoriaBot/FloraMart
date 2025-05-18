#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>
using namespace std;

#define MAX_SIZE 25

struct MetodeTransaksi
{
    string id;
    string metode;
};

struct Supplier
{
    string id;
    string username;
    string password;
    MetodeTransaksi metodeTersedia[MAX_SIZE];
    int sizeMetodeTersedia = 0;
    string status;
};

struct Pembeli
{
    string id;
    string username;
    string password;
};

struct Admin
{
    string id;
    string username;
    string password;
};

struct Kategori
{
    string id;
    string namaKategori;
    float minSuhu = 0;
    float maxSuhu = 0;
    string mediaTanam;
};

struct Tanaman
{
    string id;
    string namaTanaman;
    Supplier supplier;
    Kategori kategori;
    double harga = 0;
    int stok;
};

struct Transaksi
{
    string id;
    Tanaman tanaman;
    Pembeli pembeli;
    int jumlahTanaman = 0;
    int totalHarga = 0;
    MetodeTransaksi metodeBayar;
    string status;
    string tanggalTransaksi;
    string tanggalPembayaran;
};

struct Suplai
{
    string id;
    string namaTanaman;
    Supplier supplier;
    int jumlah;
    string tanggalSuplai;
    bool statusValidasi;
};

struct ValidasiTanaman
{
    string id;
    Tanaman tanaman;
    int stok_diterima;
    Suplai suplai;
};

struct DataUtama
{
    Pembeli dataPembeli[MAX_SIZE];
    int sizeDataPembeli;

    Supplier dataSupplier[MAX_SIZE];
    int sizeDataSupplier;

    Admin dataAdmin[MAX_SIZE];
    int sizeDataAdmin;

    Tanaman dataTanaman[MAX_SIZE];
    int sizeDataTanaman;
    
    Kategori dataKategori[MAX_SIZE];
    int sizeDataKategori;

    MetodeTransaksi dataMetodeTransaksi[MAX_SIZE];
    int sizeDataMetodeTransaksi;

    Suplai dataSuplai[MAX_SIZE];
    int sizeDataSuplai;

    Transaksi dataTransaksi[MAX_SIZE];
    int sizeDataTransaksi;

    ValidasiTanaman dataValidasiTanaman[MAX_SIZE];
    int sizeDataValidasi;
};

#endif