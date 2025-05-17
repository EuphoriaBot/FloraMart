#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>
using namespace std;

#define MAX_SIZE 8

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

#endif