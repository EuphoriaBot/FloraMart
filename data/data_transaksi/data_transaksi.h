#ifndef DATA_TRANSAKSI_H
#define DATA_TRANSAKSI_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "../nlohmann/json.hpp"
#include "../data_utilities.h"
#include "../data_tanaman/data_tanaman.h"
#include "../data_pembeli/data_pembeli.h"
#include "../data_metode_transaksi/data_metode_transaksi.h"

using json = nlohmann::json;
using namespace std;

#ifdef DATA_NAME
#undef DATA_NAME
#endif
#define DATA_NAME "transaksi.json"

// Mengubah nilai dari json ke tanaman per data
void from_json(json &j, Transaksi &transaksi)
{
    Tanaman *dataTanaman = new Tanaman[MAX_SIZE];
    int *sizeDataTanaman = new int{0};

    Pembeli *dataPembeli = new Pembeli[MAX_SIZE];
    int *sizeDataPembeli = new int{0};

    MetodeTransaksi *dataMetodeTransaksi = new MetodeTransaksi[MAX_SIZE];
    int *sizeDataMetodeTransaksi = new int{0};
    try
    {
        GetAllTanaman(dataTanaman, *sizeDataTanaman);
        GetAllPembeli(dataPembeli, *sizeDataPembeli);
        GetAllMetodeTransaksi(dataMetodeTransaksi, *sizeDataMetodeTransaksi);

        j.at("id").get_to(transaksi.id);
        j.at("jumlah").get_to(transaksi.jumlahTanaman);
        j.at("total_harga").get_to(transaksi.totalHarga);
        j.at("tanggal_transaksi").get_to(transaksi.tanggalTransaksi);
        j.at("status").get_to(transaksi.status);

        GetTanaman(transaksi.tanaman, j.at("id_tanaman"));
        GetPembeli(transaksi.pembeli, j.at("id_pembeli"));
        GetMetodeTransaksi(transaksi.metodeBayar, j.at("id_metode_bayar"));
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
    delete[] dataPembeli;
    delete[] dataMetodeTransaksi;
    delete sizeDataTanaman;
    delete sizeDataPembeli;
    delete sizeDataMetodeTransaksi;
    dataTanaman = nullptr;
    dataPembeli = nullptr;
    dataMetodeTransaksi = nullptr;
    sizeDataTanaman = nullptr;
    sizeDataPembeli = nullptr;
    sizeDataMetodeTransaksi = nullptr;
}

// Mengubah nilai dari tanaman ke json per data
void to_json(json &j, Transaksi &transaksi)
{
    try
    {
        j = json{
            {"id", transaksi.id},
            {"id_tanaman", transaksi.tanaman.id},
            {"id_pembeli", transaksi.pembeli.id},
            {"jumlah", transaksi.jumlahTanaman},
            {"id_metode_bayar", transaksi.metodeBayar.id},
            {"tanggal_transaksi", transaksi.tanggalTransaksi},
            {"jumlah", transaksi.jumlahTanaman},
            {"total_harga", transaksi.totalHarga},
            {"status", transaksi.status}};
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
void GetAllTransaksi(Transaksi *dataTanaman, int &sizeData)
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
void GetTransaksi(Transaksi &transaksi, string targetId)
{
    Transaksi *dataTransaksi = new Transaksi[MAX_SIZE];
    int *sizeDataTransaksi = new int{0};
    try
    {
        GetAllTransaksi(dataTransaksi, *sizeDataTransaksi);

        for (int i = 0; i < *sizeDataTransaksi; i++)
        {
            if (dataTransaksi[i].id == targetId)
                transaksi = dataTransaksi[i];
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
    delete dataTransaksi;
    delete sizeDataTransaksi;
    dataTransaksi = nullptr;
    sizeDataTransaksi = nullptr;
}

// Menyimpan Data di program saat ini ke JSON
void SimpanTransaksi(Transaksi *dataTransaksi, int sizeData)
{
    json *_newJsonData = new json{};
    try
    {
        *_newJsonData = json::array();
        for (int i = 0; i < sizeData; i++)
        {
            json *j = new json();
            to_json(*j, dataTransaksi[i]);

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
string GetFreeTransaksiId()
{
    Transaksi *dataTransaksi = new Transaksi[MAX_SIZE];
    int *sizeData = new int{0};
    stringstream *freeStreamId = new stringstream();
    int *maxId = new int{0};
    try
    {
        GetAllTransaksi(dataTransaksi, *sizeData);
        
        for (int i = 0; i < *sizeData; i++)
        {
            if ((*maxId) < (stoi(dataTransaksi[i].id)))
                *maxId = (stoi(dataTransaksi[i].id));
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
    delete[] dataTransaksi;
    delete sizeData;
    delete freeStreamId;
    delete maxId;
    dataTransaksi = nullptr;
    sizeData = nullptr;
    freeStreamId = nullptr;
    maxId = nullptr;

    return "";
}

// Menambah dan menyimpan langsung data tanaman baru ke database
void TambahTransaksi(Transaksi *dataTransaksi, int &sizeData, Transaksi transaksiBaru)
{
    Tanaman *dataTanaman = new Tanaman[MAX_SIZE];
    int *sizeDataTanaman = new int{0};

    time_t *curTimestamp = new time_t{time(NULL)};
    tm *curDatetime = (*localtime)(&(*curTimestamp));
    char *curTimeOutput = new char[50];

    try
    {
        strftime(curTimeOutput, 50, "%d-%m-%y %H:%M", &(*curDatetime));

        GetAllTanaman(dataTanaman, *sizeDataTanaman);
        
        if (transaksiBaru.id == "")
            throw invalid_argument("ID tanaman tidak boleh kosong!");
        if (transaksiBaru.jumlahTanaman <= 0)
            throw invalid_argument("Jumlah tanaman tidak bisa di bawah atau sama dengan 0!");
        if (transaksiBaru.metodeBayar.id == "")
            throw invalid_argument("Metode pembayaran tidak boleh kosong!");
        if (transaksiBaru.pembeli.id == "")
            throw invalid_argument("Pembeli tidak boleh kosong!");
        if (transaksiBaru.jumlahTanaman <= 0)
            throw invalid_argument("Jumlah tanaman tidak bisa di bawah atau sama dengan 0!");
        if (transaksiBaru.jumlahTanaman <= 0)
            throw invalid_argument("Jumlah tanaman tidak bisa di bawah atau sama dengan 0!");

        for (int i = 0; i < sizeData; i++)
        {
            if (dataTransaksi[i].id == transaksiBaru.id)
                throw invalid_argument("ID sudah digunakan");
        }

        dataTransaksi[sizeData].id = transaksiBaru.id;
        dataTransaksi[sizeData].tanaman = transaksiBaru.tanaman;
        dataTransaksi[sizeData].pembeli = transaksiBaru.pembeli;
        dataTransaksi[sizeData].jumlahTanaman = transaksiBaru.jumlahTanaman;
        dataTransaksi[sizeData].metodeBayar = transaksiBaru.metodeBayar;
        dataTransaksi[sizeData].tanggalTransaksi = curTimeOutput;
        dataTransaksi[sizeData].totalHarga = (transaksiBaru.tanaman.harga * transaksiBaru.jumlahTanaman);
        dataTransaksi[sizeData].status = "Menunggu Konfirmasi";
        sizeData++;

        for (int i = 0; i < *sizeDataTanaman; i++)
        {
            if (dataTanaman[i].id == transaksiBaru.id)
            {
                dataTanaman[i].stok -= transaksiBaru.jumlahTanaman;
                break;
            }
        }

        SimpanTransaksi(dataTransaksi, sizeData);
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
    delete[] curTimestamp;
    delete sizeDataTanaman;
    delete curDatetime;
    delete curTimeOutput;
    dataTanaman = nullptr;
    curTimestamp = nullptr;
    sizeDataTanaman = nullptr;
    curDatetime = nullptr;
    curTimeOutput = nullptr;

}

// Menghapus dan menyimpan langsung data tanaman yang telah dihapus ke database
void HapusTanaman(Transaksi *dataTanaman, int &sizeData, Tanaman tanamanDihapus)
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

        SimpanTransaksi(dataTanaman, sizeData);
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