#ifndef DATA_SUPPLIER_H
#define DATA_SUPPLIER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_struct.h"
#include "data_metode_transaksi.h"

using json = nlohmann::json;
using namespace std;

void GetSupplierMetodeTersedia(Supplier &dataSupplier, string *arrIdMetode, int jumlahMetode)
{
    MetodeTransaksi *dataMetodeTransaksi = new MetodeTransaksi[MAX_SIZE];
    int *sizeMetodeTransaksi = new int{0};
    
    try
    {
        GetAllMetodeTransaksi(dataMetodeTransaksi, *sizeMetodeTransaksi);

        dataSupplier.sizeMetodeTersedia = jumlahMetode;
    
        for (int i = 0; i < jumlahMetode; i++)
        {
            dataSupplier.metodeTersedia[i] = {};
            GetMetodeTransaksi(dataSupplier.metodeTersedia[i], arrIdMetode[i]);
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

// Mengubah nilai dari json ke supplier per data
void from_json(json &j, Supplier &s)
{
    string *_tempArr = new string[MAX_SIZE];
    
    try
    {
        j.at("id").get_to(s.id);
        j.at("username").get_to(s.username);
        for (int i = 0; i < j.at("metode_tersedia").size(); i++)
            (j.at("metode_tersedia")[i]).get_to(_tempArr[i]);
    
        GetSupplierMetodeTersedia(s, _tempArr, (j.at("metode_tersedia")).size());
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

// Mengubah nilai dari supplier ke json per data
void to_json(json &j, json &oldJsonData, Supplier &s)
{
    string *newPassword = new string();
    string *newStatus = new string();
    json *dataMetode = new json();

    try
    {
        *dataMetode = json::array();
        for (int i = 0; i < s.sizeMetodeTersedia; i++)
        {
            (*dataMetode).push_back(s.metodeTersedia[i].id);
        }

        *newPassword = s.password;
        if (*newPassword == "")
            *newPassword = oldJsonData.at("password");

        *newStatus = s.status;
        if (*newStatus == "")
            *newStatus = oldJsonData.at("status");

        j = json{
            {"id", s.id},
            {"username", s.username},
            {"password", *newPassword},
            {"metode_tersedia", *dataMetode},
            {"status", *newStatus}};
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

    delete newPassword;
    delete newStatus;
    delete dataMetode;
    newPassword = nullptr;
    newStatus = nullptr;
    dataMetode = nullptr;
}

// Mencari ID otomatis yang belum digunakan
string GetFreeSupplierId(Supplier *dataSupplier, int &sizeData)
{
    stringstream* freeStreamId = new stringstream();
    int *maxId = new int{0};
    try
    {
        for (int i = 0; i < sizeData; i++)
        {
            if ((*maxId) < (stoi(dataSupplier[i].id)))
                *maxId = (stoi(dataSupplier[i].id));
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

// Mengambil semua data supplier (Supplier[])
void GetAllSupplier(Supplier *dataSupplier, int &sizeData)
{
    json* _jsonData = new json();
    try
    {
        ifstream readFile("./database/supplier.json");
        *_jsonData = json::parse(readFile);
        sizeData = min(int((*_jsonData).size()), int(MAX_SIZE));
    
        for (int i = 0; i < sizeData; i++)
            from_json((*_jsonData)[i], dataSupplier[i]);
    
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

// Mencari Supplier dari ID dan ambil dari data yang memiliki id yang sama dengan targetId
void GetSupplier(Supplier &supplier, string targetId)
{
    Supplier *dataSupplier = new Supplier[MAX_SIZE];
    int *sizeDataSupplier = new int{0};

    try
    {
        GetAllSupplier(dataSupplier, *sizeDataSupplier);
    
        for (int i = 0; i < *sizeDataSupplier; i++)
        {
            if (dataSupplier[i].id == targetId)
                supplier = dataSupplier[i];
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
    delete[] dataSupplier;
    delete sizeDataSupplier;
    dataSupplier = nullptr;
    sizeDataSupplier= nullptr;
}

// Menyimpan Data di program saat ini ke JSON
void SimpanDataSupplier(Supplier *dataSupplier, int &sizeData)
{
    json *_oldJsonData = new json();
    json *_newJsonData = new json();
    try
    {
        ifstream readOldFile("./database/supplier.json");
        *_oldJsonData = json::parse(readOldFile);
        *_newJsonData = json::array();
    
        for (int i = 0; i < sizeData; i++)
        {
            json *j = new json();
            to_json(*j, (*_oldJsonData)[i], dataSupplier[i]);
    
            // Menambah 1 elemen (data json) array ke belakang
            (*_newJsonData).push_back(*j);
            
            delete j;
            j = nullptr;
        }
    
        ofstream writeFile("./database/supplier.json");
        writeFile << *_newJsonData;
    
        readOldFile.close();
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

    delete _oldJsonData;
    delete _newJsonData;
    _oldJsonData = nullptr;
    _newJsonData = nullptr;
}

// Menambah dan menyimpan langsung data supplier baru ke database
void TambahSupplier(Supplier *dataSupplier, int &sizeData, Supplier supplierBaru)
{
    try
    {
        if (supplierBaru.username == "")
            throw invalid_argument("Username tidak bisa kosong!");
        if (supplierBaru.password == "")
            throw invalid_argument("Password tidak bisa kosong!");

        dataSupplier[sizeData].id = GetFreeSupplierId(dataSupplier, sizeData);
        dataSupplier[sizeData].username = supplierBaru.username;
        dataSupplier[sizeData].password = supplierBaru.password;
        dataSupplier[sizeData].status = "aktif";
        sizeData++;

        SimpanDataSupplier(dataSupplier, sizeData);
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

// Menghapus dan menyimpan langsung data supplier yang telah dihapus ke database
void HapusSupplier(Supplier *dataSupplier, int &sizeData, Supplier supplierDihapus)
{
    int *indexDihapus = new int{-1};
    try
    {

        // Mencari indeks supplier
        for (int i = 0; i < sizeData; i++)
        {
            if (dataSupplier[i].id == supplierDihapus.id)
            {
                // Menetapkan indeks yang dihapus dengan indeks supplier yg ditemukan
                *indexDihapus = i;
                break;
            }
        }

        if (*indexDihapus < 0 && *indexDihapus >= sizeData)
            throw invalid_argument("Tidak ada supplier yang ingin dihapus");

        // Menghapus supplier
        for (int i = *indexDihapus; i < sizeData; i++)
        {
            dataSupplier[i] = dataSupplier[i + 1];
        }
        sizeData--;

        SimpanDataSupplier(dataSupplier, sizeData);
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

bool LoginSupplier(string username, string password, Supplier currentSupplier, Supplier *dataSupplier, int &sizeDataSupplier)
{
    Supplier _tempDataSupplier[MAX_SIZE];

    ifstream readFile("./database/supplier.json");
    json _jsonData = json::parse(readFile);

    // Inisialisasi username dan password dari data supplier
    for (int i = 0; i < sizeDataSupplier; i++)
    {
        _jsonData[i].at("username").get_to(_tempDataSupplier[i].username);
        _jsonData[i].at("password").get_to(_tempDataSupplier[i].password);
    }

    // Pencocokan dengan data akun
    for (int i = 0; i < sizeDataSupplier; i++)
    {
        if (_tempDataSupplier[i].username == username && _tempDataSupplier[i].password == password)
        {
            currentSupplier = dataSupplier[i];
            return true;
        }
    }

    return false;
}

#endif