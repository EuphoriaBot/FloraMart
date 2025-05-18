#ifndef DATA_METODE_TRANSAKSI_H
#define DATA_METODE_TRANSAKSI_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_struct.h"

using json = nlohmann::json;
using namespace std;

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
        ifstream readFile("./database/metode_transaksi.json");
        *_jsonData = json::parse(readFile);
        sizeData = min(int((*_jsonData).size()), int(MAX_SIZE));

        for (int i = 0; i < sizeData; i++)
            from_json((*_jsonData)[i], dataMetodeTransaksi[i]);

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
void SimpanDataMetodeTransaksi(MetodeTransaksi *dataMetodeTransaksi, int &sizeData)
{
    json *_jsonData = new json();
    try
    {
        *_jsonData = json::array();
        for (int i = 0; i < sizeData; i++)
        {
            json j;
            to_json(j, dataMetodeTransaksi[i]);

            // Menambah 1 elemen (data json) array ke belakang
            (*_jsonData).push_back(j);
        }

        ofstream writeFile("./database/metode_transaksi.json");
        writeFile << (*_jsonData);
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

    delete _jsonData;
    _jsonData = nullptr;
}

// Mencari ID otomatis yang belum digunakan
string GetFreeMetodeTransaksiId(MetodeTransaksi *dataMetodeTransaksi, int &sizeData)
{
    stringstream *freeStreamId = new stringstream();
    int *maxId = new int{0};
    try
    {
        GetAllMetodeTransaksi(dataMetodeTransaksi, sizeData);
        
        for (int i = 0; i < sizeData; i++)
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

    delete freeStreamId;
    delete maxId;
    freeStreamId = nullptr;
    maxId = nullptr;

    return "";
}

// Menambah dan menyimpan langsung data metode transaksi baru ke database
void TambahMetodeTransaksi(MetodeTransaksi *dataMetodeTransaksi, int &sizeData, MetodeTransaksi metodeBaru)
{
    try
    {
        if (metodeBaru.metode == "")
            throw invalid_argument("Nama metode transaksi tidak boleh kosong!");

        dataMetodeTransaksi[sizeData].id = metodeBaru.id;
        dataMetodeTransaksi[sizeData].metode = metodeBaru.metode;
        sizeData++;

        SimpanDataMetodeTransaksi(dataMetodeTransaksi, sizeData);
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
    int * indexDihapus = new int{-1};
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

        SimpanDataMetodeTransaksi(dataMetodeTransaksi, sizeData);
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