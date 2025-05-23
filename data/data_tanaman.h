#ifndef DATA_TANAMAN_H
#define DATA_TANAMAN_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_utilities.h"
#include "data_supplier.h"
#include "data_kategori.h"

using json = nlohmann::json;
using namespace std;

#ifdef DATA_NAME
#undef DATA_NAME
#endif
#define DATA_NAME "tanaman.json"

// Mengubah nilai dari json ke tanaman per data
void from_json(json &j, Tanaman &t)
{
    Supplier *dataSupplier = new Supplier[MAX_SIZE];
    int *sizeDataSupplier = new int{0};

    Kategori *dataKategori = new Kategori[MAX_SIZE];
    int *sizeDataKategori = new int{0};
    try
    {
        GetAllSupplier(dataSupplier, *sizeDataSupplier);
        GetAllKategori(dataKategori, *sizeDataKategori);

        j.at("id").get_to(t.id);
        j.at("nama_tanaman").get_to(t.namaTanaman);
        j.at("harga").get_to(t.harga);
        j.at("stok").get_to(t.stok);

        GetSupplier(t.supplier, j.at("id_supplier"));
        GetKategori(t.kategori, j.at("id_kategori"));

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

    delete[] dataSupplier;
    delete[] dataKategori;
    delete sizeDataSupplier;
    delete sizeDataKategori;
    dataSupplier = nullptr;
    dataKategori = nullptr;
    sizeDataSupplier = nullptr;
    sizeDataKategori = nullptr;
}

// Mengubah nilai dari tanaman ke json per data
void to_json(json &j, Tanaman &t)
{
    try
    {
        j = json{
            {"id", t.id},
            {"nama_tanaman", t.namaTanaman},
            {"id_supplier", t.supplier.id},
            {"id_kategori", t.kategori.id},
            {"harga", t.harga},
            {"stok", t.stok}};
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
}

// Mengambil semua data tanaman (Tanaman[])
void GetAllTanaman(Tanaman *dataTanaman, int &sizeData)
{
    json *_jsonData = new json();
    try
    {
        ReadJson(*_jsonData, sizeData, DATA_NAME);

        for (int i = 0; i < sizeData; i++)
            from_json((*_jsonData)[i], dataTanaman[i]);
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
    delete _jsonData;
    _jsonData = nullptr;
}

// Mencari Tanaman dari ID dan ambil dari data yang memiliki id yang sama dengan targetId
void GetTanaman(Tanaman &tanaman, string targetId)
{
    Tanaman *dataTanaman = new Tanaman[MAX_SIZE];
    int *sizeDataTanaman = new int{0};

    try
    {
        GetAllTanaman(dataTanaman, *sizeDataTanaman);

        for (int i = 0; i < *sizeDataTanaman; i++)
        {
            if (dataTanaman[i].id == targetId)
                tanaman = dataTanaman[i];
        }
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
    delete[] dataTanaman;
    delete sizeDataTanaman;
    dataTanaman = nullptr;
    sizeDataTanaman = nullptr;
}

// Menyimpan Data di program saat ini ke JSON
void SimpanTanaman(Tanaman *dataTanaman, int sizeData)
{
    json *_newJsonData = new json{json::array()};
    try
    {
        for (int i = 0; i < sizeData; i++)
        {
            json *j = new json();
            to_json(*j, dataTanaman[i]);

            // Menambah 1 elemen (data json) array ke belakang
            (*_newJsonData).push_back(*j);
            
            delete j;
            j = nullptr;
        }

        WriteJson(*_newJsonData, DATA_NAME);
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

    delete _newJsonData;
    _newJsonData = nullptr;
}

// Mencari ID otomatis yang belum digunakan
string GetFreeTanamanId()
{
    Tanaman *dataTanaman = new Tanaman[MAX_SIZE];
    int *sizeData = new int{0};
    stringstream *freeStreamId = new stringstream();
    int *maxId = new int{0};
    try
    {
        GetAllTanaman(dataTanaman, *sizeData);
        for (int i = 0; i < *sizeData; i++)
        {
            if ((*maxId) < (stoi(dataTanaman[i].id)))
                *maxId = (stoi(dataTanaman[i].id));
        }

        (*freeStreamId) << setw(4) << setfill('0') << ((*maxId) + 1);
        return (*freeStreamId).str();
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
    delete[] dataTanaman;
    delete sizeData;
    delete freeStreamId;
    delete maxId;
    dataTanaman = nullptr;
    sizeData = nullptr;
    freeStreamId = nullptr;
    maxId = nullptr;

    return "";
}

// Menambah dan menyimpan langsung data tanaman baru ke database
void TambahTanaman(Tanaman *dataTanaman, int &sizeData, Tanaman tanamanBaru)
{
    try
    {
        if (tanamanBaru.id == "")
            throw invalid_argument("ID Tanaman tidak bisa kosong!");
        if (tanamanBaru.namaTanaman == "")
            throw invalid_argument("Nama Tanaman tidak bisa kosong!");
        if (tanamanBaru.harga <= 0)
            throw invalid_argument("Harga tanaman tidak bisa di bawah atau sama dengan 0!");

        for (int i = 0; i < sizeData; i++)
        {
            if (dataTanaman[i].id == tanamanBaru.id)
                throw invalid_argument("ID sudah digunakan");
        }

        dataTanaman[sizeData].id = tanamanBaru.id;
        dataTanaman[sizeData].namaTanaman = tanamanBaru.namaTanaman;
        dataTanaman[sizeData].supplier = tanamanBaru.supplier;
        dataTanaman[sizeData].kategori = tanamanBaru.kategori;
        dataTanaman[sizeData].harga = tanamanBaru.harga;
        dataTanaman[sizeData].stok = 0;
        sizeData++;

        SimpanTanaman(dataTanaman, sizeData);
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
}

// Menghapus dan menyimpan langsung data tanaman yang telah dihapus ke database
void HapusTanaman(Tanaman *dataTanaman, int &sizeData, Tanaman tanamanDihapus)
{
    int *indexDihapus = new int{-1};
    try
    {
        // Mencari indeks tanaman
        for (int i = 0; i < sizeData; i++)
        {
            if (dataTanaman[i].id == tanamanDihapus.id)
            {
                // Menetapkan indeks yang dihapus dengan indeks tanaman yg ditemukan
                *indexDihapus = i;
                break;
            }
        }

        if (*indexDihapus < 0 && *indexDihapus >= sizeData)
            throw invalid_argument("Tidak ada tanaman yang ingin dihapus");

        // Menghapus tanaman
        for (int i = *indexDihapus; i < sizeData; i++)
        {
            dataTanaman[i] = dataTanaman[i + 1];
        }
        sizeData--;

        SimpanTanaman(dataTanaman, sizeData);
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
    
    delete indexDihapus;
    indexDihapus = nullptr;
}

#endif