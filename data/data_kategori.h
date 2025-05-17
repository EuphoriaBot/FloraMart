#ifndef DATA_KATEGORI_H
#define DATA_KATEGORI_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_struct.h"

using json = nlohmann::json;
using namespace std;

// Mengubah nilai dari json ke kategori per data
void from_json(json &j, Kategori &kat)
{
    j.at("id").get_to(kat.id);
    j.at("nama_kategori").get_to(kat.namaKategori);
    j.at("min_suhu").get_to(kat.minSuhu);
    j.at("max_suhu").get_to(kat.maxSuhu);
    j.at("media_tanam").get_to(kat.mediaTanam);
}

// Mengubah nilai dari kategori ke json per data
void to_json(json &j, Kategori &kat)
{
    j = json{
        {"id", kat.id},
        {"nama_kategori", kat.namaKategori},
        {"min_suhu", kat.minSuhu},
        {"max_suhu", kat.maxSuhu},
        {"media_tanam", kat.mediaTanam}};
}

// Mencari ID otomatis yang belum digunakan
string GetFreeKategoriId(Kategori *dataKategori, int &sizeData)
{
    stringstream *freeStreamId = new stringstream();
    int *maxId = new int{0};
    try
    {
        for (int i = 0; i < sizeData; i++)
        {
            if ((*maxId) < (stoi(dataKategori[i].id)))
                *maxId = (stoi(dataKategori[i].id));
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

// Mengambil semua data kategori (Kategori[])
void GetAllKategori(Kategori *dataKategori, int &sizeData)
{
    json *_jsonData = new json();
    try
    {
        ifstream readFile("./database/kategori.json");
        *_jsonData = json::parse(readFile);
        sizeData = min(int((*_jsonData).size()), int(MAX_SIZE));

        for (int i = 0; i < sizeData; i++)
            from_json((*_jsonData)[i], dataKategori[i]);

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

// Mencari Kategori dari ID dan ambil dari data yang memiliki id yang sama dengan targetId
void GetKategori(Kategori &kategori, string targetId)
{
    Kategori *dataKategori = new Kategori[MAX_SIZE];
    int *sizeDataKategori = new int{0};

    try
    {
        GetAllKategori(dataKategori, *sizeDataKategori);

        for (int i = 0; i < *sizeDataKategori; i++)
        {
            if (dataKategori[i].id == targetId)
                kategori = dataKategori[i];
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

    delete[] dataKategori;
    delete sizeDataKategori;
    dataKategori = nullptr;
    sizeDataKategori = nullptr;
}

// Menyimpan Data di program saat ini ke JSON
void SimpanDataKategori(Kategori *dataKategori, int &sizeData)
{
    json *_jsonData = new json();
    try
    {
        *_jsonData = json::array();
        for (int i = 0; i < sizeData; i++)
        {
            json *j = new json();
            to_json(*j, dataKategori[i]);

            // Menambah 1 elemen (data json) array ke belakang
            (*_jsonData).push_back(*j);
            
            delete j;
            j = nullptr;
        }

        ofstream writeFile("./database/kategori.json");
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

// Menambah dan menyimpan langsung data kategori baru ke database
void TambahKategori(Kategori *dataKategori, int &sizeData, Kategori kategoriBaru)
{
    try
    {
        if (kategoriBaru.maxSuhu < kategoriBaru.minSuhu)
            throw invalid_argument("Maksimum Suhu tidak bisa kurang dari Minimum Suhu!");
        if (kategoriBaru.mediaTanam == "")
            throw invalid_argument("Media tanam tidak boleh kosong!");

        dataKategori[sizeData].id = kategoriBaru.id;
        dataKategori[sizeData].minSuhu = kategoriBaru.minSuhu;
        dataKategori[sizeData].maxSuhu = kategoriBaru.maxSuhu;
        dataKategori[sizeData].mediaTanam = kategoriBaru.mediaTanam;
        sizeData++;

        SimpanDataKategori(dataKategori, sizeData);
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

// Menghapus dan menyimpan langsung data kategori yang telah dihapus ke database
void HapusKategori(Kategori *dataKategori, int &sizeData, Kategori kategoriDihapus)
{
    int * indexDihapus = new int{-1};
    try
    {

        // Mencari indeks kategori
        for (int i = 0; i < sizeData; i++)
        {
            if (dataKategori[i].id == kategoriDihapus.id)
            {
                // Menetapkan indeks yang dihapus dengan indeks kategori yg ditemukan
                *indexDihapus = i;
                break;
            }
        }
        
        if (*indexDihapus < 0 && *indexDihapus >= sizeData)
            throw invalid_argument("Tidak ada kategori yang ingin dihapus");

        // Menghapus kategori
        for (int i = *indexDihapus; i < sizeData; i++)
        {
            dataKategori[i] = dataKategori[i + 1];
        }
        sizeData--;

        SimpanDataKategori(dataKategori, sizeData);
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