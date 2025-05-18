#ifndef DATA_VALIDASI_TANAMAN_H
#define DATA_VALIDASI_TANAMAN_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_utilities.h"
#include "data_tanaman.h"
#include "data_suplai.h"

using json = nlohmann::json;
using namespace std;

#ifdef DATA_NAME
#undef DATA_NAME
#endif
#define DATA_NAME "validasi_tanaman.json"

// Mengubah nilai dari json ke data suplai per data
void from_json(json &j, ValidasiTanaman &validasi)
{
    Tanaman *dataTanaman = new Tanaman[MAX_SIZE];
    int *sizeDataTanaman = new int{0};
    
    Suplai *dataSuplai = new Suplai[MAX_SIZE];
    int *sizeDataSuplai = new int{0};
    try
    {
        GetAllTanaman(dataTanaman, *sizeDataTanaman);
        GetAllSuplai(dataSuplai, *sizeDataSuplai);

        j.at("id").get_to(validasi.id);
        j.at("stok_diterima").get_to(validasi.stok_diterima);

        GetTanaman(validasi.tanaman, j.at("id_tanaman"));
        GetSuplai(validasi.suplai, j.at("id_suplai"));
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
    delete[] dataSuplai;
    delete sizeDataSuplai;
    delete sizeDataTanaman;
    dataTanaman = nullptr;
    dataSuplai = nullptr;
    sizeDataSuplai = nullptr;
    sizeDataTanaman = nullptr;
}

// Mengubah nilai dari data suplai ke json per data
void to_json(json &j, ValidasiTanaman &v)
{
    try
    {
        j = json{
            {"id", v.id},
            {"id_tanaman", v.tanaman.id},
            {"stok_diterima", v.stok_diterima},
            {"id_suplai", v.suplai.id}};
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

// Mengambil semua data suplai (Suplai[])
void GetAllValidasiTanaman(ValidasiTanaman *dataValidasi, int &sizeData)
{
    json *_jsonData = new json();
    try
    {
        ReadJson(*_jsonData, sizeData, DATA_NAME);
        
        for (int i = 0; i < sizeData; i++)
            from_json((*_jsonData)[i], dataValidasi[i]);
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

// Mencari data suplai dari ID dan ambil dari data yang memiliki id yang sama dengan targetId
void GetValidasiTanaman(ValidasiTanaman &validasiTanaman, string targetId)
{
    ValidasiTanaman *dataValidasi = new ValidasiTanaman[MAX_SIZE];
    int *sizeDataValidasi = new int{0};

    try
    {
        GetAllValidasiTanaman(dataValidasi, *sizeDataValidasi);

        for (int i = 0; i < *sizeDataValidasi; i++)
        {
            if (dataValidasi[i].id == targetId)
                validasiTanaman = dataValidasi[i];
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
    delete[] dataValidasi;
    delete sizeDataValidasi;
    dataValidasi = nullptr;
    sizeDataValidasi = nullptr;
}

// Menyimpan Data di program saat ini ke JSON
void SimpanValidasiTanaman(ValidasiTanaman *dataValidasiTanaman, int sizeData)
{
    json *_newJsonData = new json{json::array()};
    try
    {
        for (int i = 0; i < sizeData; i++)
        {
            json *j = new json();
            to_json(*j, dataValidasiTanaman[i]);

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
string GetFreeValidasiId()
{
    ValidasiTanaman *dataValidasi = new ValidasiTanaman[MAX_SIZE];
    int *sizeData = new int{0};
    stringstream *freeStreamId = new stringstream();
    int *maxId = new int{0};
    try
    {
        GetAllValidasiTanaman(dataValidasi, *sizeData);
        for (int i = 0; i < *sizeData; i++)
        {
            if ((*maxId) < (stoi(dataValidasi[i].id)))
                *maxId = (stoi(dataValidasi[i].id));
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
    delete[] dataValidasi;
    delete sizeData;
    delete freeStreamId;
    delete maxId;
    dataValidasi = nullptr;
    sizeData = nullptr;
    freeStreamId = nullptr;
    maxId = nullptr;

    return "";
}

// Menambah dan menyimpan langsung data suplai baru ke database
void TambahValidasi(ValidasiTanaman *dataValidasi, int &sizeData, ValidasiTanaman validasiBaru)
{
    Suplai *dataSuplai = new Suplai[MAX_SIZE];
    int *sizeDataSuplai = new int{0};

    Tanaman *dataTanaman = new Tanaman[MAX_SIZE];
    int *sizeDataTanaman = new int{0};
    try
    {
        GetAllSuplai(dataSuplai, *sizeDataSuplai);
        GetAllTanaman(dataTanaman, *sizeDataTanaman);
        
        bool tanamanDitemukan = false;
        for (int i = 0; i < *sizeDataTanaman; i++)
        {
            if (dataTanaman[i].id == validasiBaru.tanaman.id)
            {
                tanamanDitemukan = true;
                break;
            }
        }
        
        for (int i = 0; i < sizeData; i++)
        {
            if (dataValidasi[i].id == validasiBaru.id)
                throw invalid_argument("ID sudah digunakan");
        }

        if (!tanamanDitemukan)
            throw invalid_argument("Tidak ada tanaman divalidasi!");
        if (validasiBaru.stok_diterima < 0)
            throw invalid_argument("Stok diterima tidak bisa di bawah 0!");
        if (validasiBaru.stok_diterima > validasiBaru.suplai.jumlah)
            throw invalid_argument("Stok diterima tidak bisa lebih dari jumlah suplai!");
        if (validasiBaru.suplai.statusValidasi == true)
            throw invalid_argument("Tanaman sudah divalidasi!");

        dataValidasi[sizeData].id = validasiBaru.id;
        dataValidasi[sizeData].tanaman = validasiBaru.tanaman;
        dataValidasi[sizeData].stok_diterima = validasiBaru.stok_diterima;
        dataValidasi[sizeData].suplai = validasiBaru.suplai;

        for (int i = 0; i < *sizeDataSuplai; i++)
        {
            // Mengubah status validasi ke Database Suplai
            if (dataValidasi[sizeData].suplai.id == dataSuplai[i].id)
            {
                dataSuplai[i].statusValidasi = true;
                break;
            }
        }

        for (int i = 0; i < *sizeDataTanaman; i++)
        {
            // Menambah Stok ke Database Tanaman
            if (dataValidasi[sizeData].tanaman.id == dataTanaman[i].id)
            {
                dataTanaman[i].stok += validasiBaru.stok_diterima;
                break;
            }
        }
        sizeData++;

        SimpanValidasiTanaman(dataValidasi, sizeData);
        SimpanSuplai(dataSuplai, *sizeDataSuplai);
        SimpanTanaman(dataTanaman, *sizeDataTanaman);
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

    delete[] dataSuplai;
    delete[] dataTanaman;
    delete sizeDataSuplai;
    delete sizeDataTanaman;
    dataSuplai = nullptr;
    dataTanaman = nullptr;
    sizeDataSuplai = nullptr;
    sizeDataTanaman = nullptr;
}

#endif