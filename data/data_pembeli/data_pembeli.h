#ifndef DATA_PEMBELI_H
#define DATA_PEMBELI_H

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
#define DATA_NAME "pembeli.json"

// Mengubah nilai dari json ke pembeli per data
void from_json(json &j, Pembeli &p)
{
    string* _tempArr = new string[MAX_SIZE];
    try
    {
        j.at("id").get_to(p.id);
        j.at("username").get_to(p.username);
        j.at("password").get_to(p.password);
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

    delete[] _tempArr;
    _tempArr = nullptr;
}

// Mengubah nilai dari pembeli ke json per data
void to_json(json &j, Pembeli &p)
{
    try
    {
        j = json{
            {"id", p.id},
            {"username", p.username},
            {"password", p.password}};
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

// Mengambil semua data pembeli (Pembeli[])
void GetAllPembeli(Pembeli *dataPembeli, int &sizeData)
{
    json *_jsonData = new json();
    try
    {
        ReadJson(*_jsonData, sizeData, DATA_NAME);
        
        for (int i = 0; i < sizeData; i++)
            from_json((*_jsonData)[i], dataPembeli[i]);
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

// Mencari Pembeli dari ID dan ambil dari data yang memiliki id yang sama dengan targetId
void GetPembeli(Pembeli &pembeli, string targetId)
{
    Pembeli *dataPembeli = new Pembeli[MAX_SIZE];
    int *sizeDataPembeli = new int{0};

    try
    {
        GetAllPembeli(dataPembeli, *sizeDataPembeli);

        for (int i = 0; i < *sizeDataPembeli; i++)
        {
            if (dataPembeli[i].id == targetId)
                pembeli = dataPembeli[i];
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
    delete[] dataPembeli;
    delete sizeDataPembeli;
    dataPembeli = nullptr;
    sizeDataPembeli = nullptr;
}

// Mencari ID otomatis yang belum digunakan
string GetFreePembeliId()
{
    Pembeli *dataPembeli = new Pembeli[MAX_SIZE];
    int *sizeData = new int{0};
    stringstream *freeStreamId = new stringstream();
    int *maxId = new int{0};
    try
    {
        GetAllPembeli(dataPembeli, *sizeData);

        for (int i = 0; i < *sizeData; i++)
        {
            if ((*maxId) < (stoi(dataPembeli[i].id)))
                *maxId = (stoi(dataPembeli[i].id));
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

    delete[] dataPembeli;
    delete sizeData;
    delete freeStreamId;
    delete maxId;
    dataPembeli = nullptr;
    sizeData = nullptr;
    freeStreamId = nullptr;
    maxId = nullptr;

    return "";
}

// Menyimpan Data di program saat ini ke JSON
void SimpanPembeli(Pembeli *dataPembeli, int sizeData)
{
    json *_newJsonData = new json();
    try
    {
        *_newJsonData = json::array();
        for (int i = 0; i < sizeData; i++)
        {
            json *j = new json();
            to_json(*j, dataPembeli[i]);

            // Menambah 1 elemen (data json) array ke belakang
            (*_newJsonData).push_back(*j);

            delete j;
            j = nullptr;
        }

        WriteJson((*_newJsonData), DATA_NAME);
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

// Menambah dan menyimpan langsung data pembeli baru ke database
void TambahPembeli(Pembeli *dataPembeli, int &sizeData, Pembeli pembeliBaru)
{
    try
    {
        if (pembeliBaru.username == "")
            throw invalid_argument("Username tidak bisa kosong!");
        if (pembeliBaru.password == "")
            throw invalid_argument("Password tidak bisa kosong!");

        dataPembeli[sizeData].id = pembeliBaru.id;
        dataPembeli[sizeData].username = pembeliBaru.username;
        dataPembeli[sizeData].password = pembeliBaru.password;
        sizeData++;

        SimpanPembeli(dataPembeli, sizeData);
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

// Menghapus dan menyimpan langsung data pembeli yang telah dihapus ke database
void HapusPembeli(Pembeli *dataPembeli, int &sizeData, Pembeli pembeliDihapus)
{
    int * indexDihapus = new int{-1};
    try
    {

        // Mencari indeks pembeli
        for (int i = 0; i < sizeData; i++)
        {
            if (dataPembeli[i].id == pembeliDihapus.id)
            {
                // Menetapkan indeks yang dihapus dengan indeks pembeli yg ditemukan
                *indexDihapus = i;
                break;
            }
        }

        if (*indexDihapus < 0 && *indexDihapus >= sizeData)
            throw invalid_argument("Tidak ada pembeli yang ingin dihapus");

        // Menghapus pembeli
        for (int i = *indexDihapus; i < sizeData; i++)
        {
            dataPembeli[i] = dataPembeli[i + 1];
        }
        sizeData--;

        SimpanPembeli(dataPembeli, sizeData);
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