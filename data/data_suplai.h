#ifndef DATA_SUPLAI_H
#define DATA_SUPLAI_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_utilities.h"
#include "data_supplier.h"

using json = nlohmann::json;
using namespace std;

#ifdef DATA_NAME
#undef DATA_NAME
#endif
#define DATA_NAME "suplai.json"

// Mengubah nilai dari json ke data suplai per data
void from_json(json &j, Suplai &s)
{
    Supplier *dataSupplier = new Supplier[MAX_SIZE];
    int *sizeDataSupplier = new int{0};

    try
    {
        GetAllSupplier(dataSupplier, *sizeDataSupplier);

        j.at("id").get_to(s.id);
        j.at("nama_tanaman").get_to(s.namaTanaman);
        j.at("jumlah").get_to(s.jumlah);
        j.at("tanggal_suplai").get_to(s.tanggalSuplai);
        j.at("status_validasi").get_to(s.statusValidasi);

        GetSupplier(s.supplier, j.at("id_supplier"));
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
    delete sizeDataSupplier;
    dataSupplier = nullptr;
    sizeDataSupplier = nullptr;
}

// Mengubah nilai dari data suplai ke json per data
void to_json(json &j, Suplai &s)
{
    try
    {
        j = json{
            {"id", s.id},
            {"nama_tanaman", s.namaTanaman},
            {"id_supplier", s.supplier.id},
            {"jumlah", s.jumlah},
            {"tanggal_suplai", s.tanggalSuplai},
            {"status_validasi", s.statusValidasi}};
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
void GetAllSuplai(Suplai *dataSuplai, int &sizeData)
{
    json *_jsonData = new json();
    try
    {
        ReadJson(*_jsonData, sizeData, DATA_NAME);
        
        for (int i = 0; i < sizeData; i++)
            from_json((*_jsonData)[i], dataSuplai[i]);
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
void GetSuplai(Suplai &suplai, string targetId)
{
    Suplai *dataSuplai = new Suplai[MAX_SIZE];
    int *sizeDataSuplai = new int{0};

    try
    {
        GetAllSuplai(dataSuplai, *sizeDataSuplai);

        for (int i = 0; i < *sizeDataSuplai; i++)
        {
            if (dataSuplai[i].id == targetId)
                suplai = dataSuplai[i];
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
    delete[] dataSuplai;
    delete sizeDataSuplai;
    dataSuplai = nullptr;
    sizeDataSuplai = nullptr;
}

// Menyimpan Data di program saat ini ke JSON
void SimpanSuplai(Suplai *dataSuplai, int sizeData)
{
    json *_newJsonData = new json{json::array()};
    try
    {
        for (int i = 0; i < sizeData; i++)
        {
            json *j = new json();
            to_json(*j, dataSuplai[i]);

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
string GetFreeSuplaiId()
{
    Suplai *dataSuplai = new Suplai[MAX_SIZE];
    int *sizeData = new int{0};
    stringstream *freeStreamId = new stringstream();
    int *maxId = new int{0};
    try
    {
        GetAllSuplai(dataSuplai, *sizeData);
        for (int i = 0; i < *sizeData; i++)
        {
            if ((*maxId) < (stoi(dataSuplai[i].id)))
                *maxId = (stoi(dataSuplai[i].id));
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
    delete dataSuplai;
    delete sizeData;
    delete freeStreamId;
    delete maxId;
    dataSuplai = nullptr;
    sizeData = nullptr;
    freeStreamId = nullptr;
    maxId = nullptr;

    return "";
}

// Menambah dan menyimpan langsung data suplai baru ke database
void TambahSuplai(Suplai *dataSuplai, int &sizeData, Suplai suplaiBaru)
{
    time_t *curTimestamp = new time_t{time(NULL)};
    tm *curDatetime = (*localtime)(&(*curTimestamp));
    char *curTimeOutput = new char[50];
    
    try
    {
        strftime(curTimeOutput, 50, "%d-%m-%y %H:%M", &(*curDatetime));

        if (suplaiBaru.namaTanaman == "")
            throw invalid_argument("Nama Tanaman tidak bisa kosong!");
        if (suplaiBaru.jumlah <= 0)
            throw invalid_argument("Jumlah tanaman tidak bisa di bawah atau sama dengan 0!");

        dataSuplai[sizeData].id = suplaiBaru.id;
        dataSuplai[sizeData].namaTanaman = suplaiBaru.namaTanaman;
        dataSuplai[sizeData].supplier = suplaiBaru.supplier;
        dataSuplai[sizeData].jumlah = suplaiBaru.jumlah;
        dataSuplai[sizeData].tanggalSuplai = curTimeOutput;
        dataSuplai[sizeData].statusValidasi = false;
        sizeData++;

        SimpanSuplai(dataSuplai, sizeData);
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

    delete curTimestamp;
    delete curDatetime;
    delete curTimeOutput;
    curTimestamp = nullptr;
    curDatetime = nullptr;
    curTimeOutput = nullptr;
}

// Menghapus dan menyimpan langsung data suplai yang telah dihapus ke database
void HapusSuplai(Suplai *dataSuplai, int &sizeData, Suplai suplaiDihapus)
{
    int *indexDihapus = new int{-1};
    try
    {
        // Mencari indeks suplai
        for (int i = 0; i < sizeData; i++)
        {
            if (dataSuplai[i].id == suplaiDihapus.id)
            {
                // Menetapkan indeks yang dihapus dengan indeks suplai yg ditemukan
                *indexDihapus = i;
                break;
            }
        }

        if (*indexDihapus < 0 && *indexDihapus >= sizeData)
            throw invalid_argument("Tidak ada data suplai yang ingin dihapus");

        // Menghapus suplai
        for (int i = *indexDihapus; i < sizeData; i++)
        {
            dataSuplai[i] = dataSuplai[i + 1];
        }
        sizeData--;

        SimpanSuplai(dataSuplai, sizeData);
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