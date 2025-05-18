#define MAX_SIZE 25

#ifndef DATA_UTILITIES_H
#define DATA_UTILITIES_H

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

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

void ReadJson(json &jsonData, int &sizeData, string fileName)
{
    string *curPath = new string();
    try
    {
        *curPath = ((filesystem::absolute(__FILE__)).remove_filename()).string();
        ifstream readFile((*curPath) + "\\database\\" + fileName);
        jsonData = json::parse(readFile);
        sizeData = min(int((jsonData).size()), int(MAX_SIZE));

        readFile.close();
    }
    catch (const invalid_argument &e)
    {
        cout << endl
             << e.what() << endl;
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << endl;
    }

    delete curPath;
    curPath = nullptr;
}

void WriteJson(json &jsonData, string fileName)
{
    string *curPath = new string();
    try
    {
        *curPath = ((filesystem::absolute(__FILE__)).remove_filename()).string();
        ofstream writeFile((*curPath) + "\\database\\" + fileName);
        writeFile << (jsonData);

        writeFile.close();
    }
    catch (const invalid_argument &e)
    {
        cout << endl
             << e.what() << endl;
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << endl;
    }

    delete curPath;
    curPath = nullptr;
}

#endif