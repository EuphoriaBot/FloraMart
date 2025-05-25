#ifndef DATA_METODE_TRANSAKSI_H
#define DATA_METODE_TRANSAKSI_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "../nlohmann/json.hpp"
#include "../data_utilities.h"

using json = nlohmann::json;
using namespace std;

#ifdef DATA_NAME
#undef DATA_NAME
#endif
#define DATA_NAME "metode_transaksi.json"

// Mengubah nilai dari json ke metode per data
void from_json(json &j, MetodeTransaksi &mt)
{
    j.at("id").get_to(mt.id);
    j.at("metode").get_to(mt.metode);
}

// Mengubah nilai dari metode ke json per data
void to_json(json &j, MetodeTransaksi &mt)
{
    j = json{
        {"id", mt.id},
        {"metode", mt.metode}};
}

// Mengambil semua data metode transaksi (MetodeTransaksi[])
void GetAllMetodeTransaksi(MetodeTransaksi *dataMetodeTransaksi, int &sizeData)
{
    json *_jsonData = new json();
    try
    {
        ReadJson(*_jsonData, sizeData, DATA_NAME);
        for (int i = 0; i < sizeData; i++)
            from_json((*_jsonData)[i], dataMetodeTransaksi[i]);
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

// Mencari Metode Transaksi dari ID dan ambil dari data yang memiliki id yang sama dengan targetId
void GetMetodeTransaksi(MetodeTransaksi &metodeTransaksi, string targetId)
{
    MetodeTransaksi *dataMetodeTransaksi = new MetodeTransaksi[MAX_SIZE];
    int *sizeMetodeTransaksi = new int{0};

    try
    {
        GetAllMetodeTransaksi(dataMetodeTransaksi, *sizeMetodeTransaksi);

        for (int i = 0; i < *sizeMetodeTransaksi; i++)
        {
            if (dataMetodeTransaksi[i].id == targetId)
                metodeTransaksi = dataMetodeTransaksi[i];
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

    delete[] dataMetodeTransaksi;
    delete sizeMetodeTransaksi;
    dataMetodeTransaksi = nullptr;
    sizeMetodeTransaksi = nullptr;
}

// Menyimpan Data di program saat ini ke JSON
void SimpanMetodeTransaksi(MetodeTransaksi *dataMetodeTransaksi, int sizeData)
{
    json *_newJsonData = new json{json::array()};
    try
    {
        for (int i = 0; i < sizeData; i++)
        {
            json *j = new json();
            to_json(*j, dataMetodeTransaksi[i]);

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
string GetFreeMetodeTransaksiId()
{
    MetodeTransaksi *dataMetodeTransaksi = new MetodeTransaksi[MAX_SIZE];
    int *sizeData = new int{0};
    stringstream *freeStreamId = new stringstream();
    int *maxId = new int{0};
    try
    {
        GetAllMetodeTransaksi(dataMetodeTransaksi, *sizeData);

        for (int i = 0; i < *sizeData; i++)
        {
            if ((*maxId) < (stoi(dataMetodeTransaksi[i].id)))
                *maxId = (stoi(dataMetodeTransaksi[i].id));
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

    delete[] dataMetodeTransaksi;
    delete sizeData;
    delete freeStreamId;
    delete maxId;
    dataMetodeTransaksi = nullptr;
    sizeData = nullptr;
    freeStreamId = nullptr;
    maxId = nullptr;

    return "";
}

// Menambah dan menyimpan langsung data metode transaksi baru ke database
void TambahMetodeTransaksi(MetodeTransaksi *dataMetodeTransaksi, int &sizeData, MetodeTransaksi metodeBaru)
{
    try
    {
        if (metodeBaru.id == "")
            throw invalid_argument("ID Metode tidak boleh kosong!");
        if (metodeBaru.metode == "")
            throw invalid_argument("Nama metode transaksi tidak boleh kosong!");

        for (int i = 0; i < sizeData; i++)
        {
            if (dataMetodeTransaksi[i].id == metodeBaru.id)
                throw invalid_argument("ID metode transaksi sudah digunakan!");
        }

        dataMetodeTransaksi[sizeData].id = metodeBaru.id;
        dataMetodeTransaksi[sizeData].metode = metodeBaru.metode;
        sizeData++;

        SimpanMetodeTransaksi(dataMetodeTransaksi, sizeData);
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

// Menghapus dan menyimpan langsung data metode transaksi yang telah dihapus ke database
void HapusMetodeTransaksi(MetodeTransaksi *dataMetodeTransaksi, int &sizeData, MetodeTransaksi metodeDihapus)
{
    int *indexDihapus = new int{-1};
    try
    {

        for (int i = 0; i < sizeData; i++)
        {
            if (dataMetodeTransaksi[i].id == metodeDihapus.id)
            {
                *indexDihapus = i;
                break;
            }
        }

        if (*indexDihapus < 0 && *indexDihapus >= sizeData)
            throw invalid_argument("Tidak ada metode transaksi yang ingin dihapus");

        for (int i = *indexDihapus; i < sizeData; i++)
        {
            dataMetodeTransaksi[i] = dataMetodeTransaksi[i + 1];
        }
        sizeData--;

        SimpanMetodeTransaksi(dataMetodeTransaksi, sizeData);
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