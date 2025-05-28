#ifndef UTILITIES_H
#define UTILITIES_H

// Data Utilities
#include "data/data_admin/data_admin.h"
#include "data/data_kategori/data_kategori.h"
#include "data/data_metode_transaksi/data_metode_transaksi.h"
#include "data/data_pembeli/data_pembeli.h"
#include "data/data_suplai/data_suplai.h"
#include "data/data_supplier/data_supplier.h"
#include "data/data_tanaman/data_tanaman.h"
#include "data/data_transaksi/data_transaksi.h"
#include "data/data_validasi_tanaman/data_validasi_tanaman.h"

// Struct Data Utama
#include "data/data_utilities.h"

struct InfoLogin
{
    string id;
    string username;
    string role;
};

struct DataMenu
{
    string pilihan = "";
    bool keluar = false;
};

template <typename T>
bool CheckStructChanges(T *struct1, int sizeStruct1, T *struct2, int sizeStruct2)
{
    bool _isChanged = true;
    if (sizeStruct1 == sizeStruct2)
    {
        for (int i = 0; i < sizeStruct1; i++)
        {
            if (struct1[i] == &(struct1[i]))
            {
                _isChanged = false;
                break;
            }
        }
    }
    return _isChanged;
}

template <typename T>
void CopyStruct(T *structSrc, int sizeStructSrc, T *structDst, int sizeStructDst)
{
    for (int i = 0; i < sizeStructSrc; i++)
        structDst = structSrc;
    
    sizeStructDst = sizeStructSrc;
}

void RefreshDataUtama(DataUtama &data)
{
    
    if (CheckStructChanges(data.dataPembeli, data.sizeDataPembeli, data._tempDataPembeli, data._tempSizeDataPembeli))
    {
        GetAllPembeli(data.dataPembeli, data.sizeDataPembeli);
        CopyStruct(data.dataPembeli, data.sizeDataPembeli, data._tempDataPembeli, data._tempSizeDataPembeli);
    }
    
    if (CheckStructChanges(data.dataSupplier, data.sizeDataSupplier, data._tempDataSupplier, data._tempSizeDataSupplier))
    {
        GetAllSupplier(data.dataSupplier, data.sizeDataSupplier);
        CopyStruct(data.dataSupplier, data.sizeDataSupplier, data._tempDataSupplier, data._tempSizeDataSupplier);
    }

    if (CheckStructChanges(data.dataAdmin, data.sizeDataAdmin, data._tempDataAdmin, data._tempSizeDataAdmin))
    {
        GetAllAdmin(data.dataAdmin, data.sizeDataAdmin);
        CopyStruct(data.dataAdmin, data.sizeDataAdmin, data._tempDataAdmin, data._tempSizeDataAdmin);
    }

    if (CheckStructChanges(data.dataTanaman, data.sizeDataTanaman, data._tempDataTanaman, data._tempSizeDataTanaman))
    {
        GetAllTanaman(data.dataTanaman, data.sizeDataTanaman);
        CopyStruct(data.dataTanaman, data.sizeDataTanaman, data._tempDataTanaman, data._tempSizeDataTanaman);
    }

    if (CheckStructChanges(data.dataKategori, data.sizeDataKategori, data._tempDataKategori, data._tempSizeDataKategori))
    {
        GetAllKategori(data.dataKategori, data.sizeDataKategori);
        CopyStruct(data.dataKategori, data.sizeDataKategori, data._tempDataKategori, data._tempSizeDataKategori);
    }

    if (CheckStructChanges(data.dataMetodeTransaksi, data.sizeDataMetodeTransaksi, data._tempDataMetodeTransaksi, data._tempSizeDataMetodeTransaksi))
    {
        GetAllMetodeTransaksi(data.dataMetodeTransaksi, data.sizeDataMetodeTransaksi);
        CopyStruct(data.dataMetodeTransaksi, data.sizeDataMetodeTransaksi, data._tempDataMetodeTransaksi, data._tempSizeDataMetodeTransaksi);
    }

    if (CheckStructChanges(data.dataSuplai, data.sizeDataSuplai, data._tempDataSuplai, data._tempSizeDataSuplai))
    {
        GetAllSuplai(data.dataSuplai, data.sizeDataSuplai);
        CopyStruct(data.dataSuplai, data.sizeDataSuplai, data._tempDataSuplai, data._tempSizeDataSuplai);
    }

    if (CheckStructChanges(data.dataTransaksi, data.sizeDataTransaksi, data._tempDataTransaksi, data._tempSizeDataTransaksi))
    {
        GetAllTransaksi(data.dataTransaksi, data.sizeDataTransaksi);
        CopyStruct(data.dataTransaksi, data.sizeDataTransaksi, data._tempDataTransaksi, data._tempSizeDataTransaksi);
    }

    if (CheckStructChanges(data.dataValidasiTanaman, data.sizeDataValidasi, data._tempDataValidasiTanaman, data._tempSizeDataValidasi))
    {
        GetAllValidasiTanaman(data.dataValidasiTanaman, data.sizeDataValidasi);
        CopyStruct(data.dataValidasiTanaman, data.sizeDataValidasi, data._tempDataValidasiTanaman, data._tempSizeDataValidasi);
    }
}

void UpdateDataUtama(DataUtama &data)
{
    SimpanPembeli(data.dataPembeli, data.sizeDataPembeli);
    SimpanSupplier(data.dataSupplier, data.sizeDataSupplier);
    SimpanAdmin(data.dataAdmin, data.sizeDataAdmin);
    SimpanTanaman(data.dataTanaman, data.sizeDataTanaman);
    SimpanKategori(data.dataKategori, data.sizeDataKategori);
    SimpanMetodeTransaksi(data.dataMetodeTransaksi, data.sizeDataMetodeTransaksi);
    SimpanSuplai(data.dataSuplai, data.sizeDataSuplai);
    SimpanTransaksi(data.dataTransaksi, data.sizeDataTransaksi);
    SimpanValidasiTanaman(data.dataValidasiTanaman, data.sizeDataValidasi);
}

void Logout(InfoLogin &infoLogin)
{
    infoLogin.id = "";
    infoLogin.username = "";
    infoLogin.role = "";
}

bool CekLogin(InfoLogin infoLogin)
{
    return infoLogin.id != "" && infoLogin.username != "" && infoLogin.role != "";
}

void ClearScreen()
{
    system("powershell.exe -Command Clear-Host");
}

// Unused
// time_t timestamp = time(NULL);
// tm datetime = *localtime(&timestamp);
// string _temp = "";

// char output[50];
// strftime(output, 50, "%d-%m-%y %H:%M", &datetime);

// cout << ctime(&timestamp) << endl;
// cout << output << endl;

// getline(cin, _temp);

#endif