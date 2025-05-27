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
#include <zlib.h>

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

void RefreshDataUtama(DataUtama &data)
{
    GetAllPembeli(data.dataPembeli, data.sizeDataPembeli);
    GetAllSupplier(data.dataSupplier, data.sizeDataSupplier);
    GetAllAdmin(data.dataAdmin, data.sizeDataAdmin);
    GetAllTanaman(data.dataTanaman, data.sizeDataTanaman);
    GetAllKategori(data.dataKategori, data.sizeDataKategori);
    GetAllMetodeTransaksi(data.dataMetodeTransaksi, data.sizeDataMetodeTransaksi);
    GetAllSuplai(data.dataSuplai, data.sizeDataSuplai);
    GetAllTransaksi(data.dataTransaksi, data.sizeDataTransaksi);
    GetAllValidasiTanaman(data.dataValidasiTanaman, data.sizeDataValidasi);
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

void Logout(DataMenu &dataMenu, InfoLogin &infoLogin)
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