#ifndef MENU_SUPPLIER_H
#define MENU_SUPPLIER_H
#include <iostream>
#include <filesystem>
#include "menu_utilities.h"
using namespace std;

void SuplaiTanaman(DataUtama &data, InfoLogin &infoLogin)
{
    if (data.sizeDataTanaman >= MAX_SIZE)
    {
        cout << "Kapasitas data tanaman sudah penuh\n";
        return;
    }

    string nama, stokStr;
    int stok;

    cout << "Nama Tanaman : ";
    getline(cin, nama);
    cout << "Stok         : ";
    getline(cin, stokStr);

    try
    {
        stok = stoi(stokStr);
    }
    catch (...)
    {
        cout << "Input stok tidak valid";
        return;
    }

    Suplai suplaiBaru;
    suplaiBaru.id = GetFreeSuplaiId();
    suplaiBaru.namaTanaman = nama;
    suplaiBaru.jumlah = stok;
    suplaiBaru.supplier.id = infoLogin.id;
    suplaiBaru.supplier.username = infoLogin.username;

    TambahSuplai(data.dataSuplai, data.sizeDataSuplai, suplaiBaru);

    cout << "Tanaman berhasil disuplai";
    cout << "ID Suplai     : " << suplaiBaru.id << endl;
    cout << "Nama Tanaman  : " << suplaiBaru.namaTanaman << endl;
    cout << "Jumlah        : " << suplaiBaru.jumlah << endl;
    cout << "Supplier      : " << suplaiBaru.supplier.username << endl;
}

void NambahSuplai(Suplai dataSuplai[], int &size, Suplai suplaiBaru)
{
    if (size < MAX_SIZE)
    {
        dataSuplai[size] = suplaiBaru;
        size++;
    }
}

void LihatLaporanTransaksi(DataUtama &data, InfoLogin &infoLogin)
{
    bool ditemukan = false;

    cout << "LAPORAN TRANSAKSI";

    for (int i = 0; i < data.sizeDataTransaksi; i++)
    {
        Transaksi &transaksi = data.dataTransaksi[i];

        if (transaksi.tanaman.supplier.id == infoLogin.id)
        {
            ditemukan = true;

            cout << "ID Transaksi : " << transaksi.id << endl;
            cout << "Tanaman      : " << transaksi.tanaman.namaTanaman << endl;
            cout << "Jumlah       : " << transaksi.jumlahTanaman << endl;
            cout << "Tanggal      : " << transaksi.tanggalTransaksi << endl;
            cout << "Pembeli      : " << transaksi.pembeli.username << endl;
        }
    }

    if (!ditemukan)
    {
        cout << "Belum ada transaksi";
    }
}

void MenuUtamaSupplier(DataUtama &data, InfoLogin &infoLogin, DataMenu &dataMenu)
{
    try
    {
        RefreshDataUtama(data);

        while (true)
        {
            cout << "\n=== MENU UTAMA SUPPLIER ===\n";
            cout << "1. Suplai Tanaman\n";
            cout << "2. Lihat Laporan Transaksi\n";
            cout << "3. Logout\n";
            cout << "Pilih menu: ";

            string pilihan;
            getline(cin, pilihan);

            if (pilihan == "1")
            {
                RefreshDataUtama(data);
                SuplaiTanaman(data, infoLogin);
            }
            else if (pilihan == "2")
            {
                LihatLaporanTransaksi(data, infoLogin);
            }
            else if (pilihan == "3")
            {
                Logout(infoLogin);
                break;
            }
            else
            {
                cout << "Pilihan tidak valid \n";
            }
        }
    }
    catch (invalid_argument &e)
    {
        cout << e.what() << '\n';
    }
    catch (exception &e)
    {
        cout << e.what() << '\n';
    }
}

#endif