#ifndef MENU_SUPPLIER_H
#define MENU_SUPPLIER_H
#include <iostream>
#include <filesystem>
#include "menu_utilities.h"
using namespace std;

void SuplaiTanaman(DataUtama &data, InfoLogin &infoLogin)
{
    string _temp;

    ClearScreen();
    Title("Suplai Tanaman");
    if (data.sizeDataTanaman >= MAX_SIZE)
    {
        cout << "Kapasitas data tanaman sudah penuh\n";
        return;
    }

    string nama, stokStr;
    int stok;

    cout << StringPos("Nama Tanaman", 16) << ": ";
    getline(cin, nama);
    cout << StringPos("Stok", 16) << ": ";
    getline(cin, stokStr);

    try
    {
        stok = stoi(stokStr);

        if (stok <= 0)
        {
            cout << "Input stok tidak bisa kurang atau sama dengan 0!";
            getline(cin, _temp);
            return;
        }
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
    cout << endl;
    cout << StringPos("ID Suplai", 16) << " : " << suplaiBaru.id << endl;
    cout << StringPos("Nama Tanaman", 16) << ": " << suplaiBaru.namaTanaman << endl;
    cout << StringPos("Jumlah", 16) << ": " << suplaiBaru.jumlah << endl;
    cout << StringPos("Supplier", 16) << ": " << suplaiBaru.supplier.username << endl;

    cout << endl;
    cout << "Tekan [Enter] untuk kembali ke menu...";
    getline(cin, _temp);
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

    ClearScreen();
    Title("Laporan Transaksi");

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
            cout<< endl;
        }
    }
    cout << endl;
    string temp;
    getline(cin, temp); // To pause the screen
    cout << "Tekan [Enter] untuk melanjutkan...";
    return;

    if (!ditemukan)
    {
        cout << "Belum ada transaksi";
    }
}

void DashboardSupplier(DataUtama &data, InfoLogin &infoLogin)
{
    Tanaman *dataTanamanTerlaris = new Tanaman[MAX_SIZE];
    int *sizeDataTanamanTerlaris = new int{0};
    string *_temp = new string();

    try
    {
        ClearScreen();
        Title("Dashboard");
        cout << StringPos("Jenis Tanaman Disuplai", 26) << ": " << JumlahJenisTanamanSupplier(data, infoLogin.id) << " Jenis Tanaman" << endl;
        cout << StringPos("Pemasukan Bulan Ini", 26) << ": Rp" << GetPemasukanBulanIniSupplier(data, infoLogin.id) << endl;
        cout << StringPos("Stok Tanaman Terjual", 26) << ": " << StokTerjualSupplier(data, infoLogin.id) << " Stok Tanaman" << endl;
        Border();

        DataTanamanTerlarisSupplier(data, infoLogin.id, dataTanamanTerlaris, (*sizeDataTanamanTerlaris));

        cout << "Tanaman Terlaris" << endl;
        if ((*sizeDataTanamanTerlaris) > 0)
        {
            for (int i = 0; i < (*sizeDataTanamanTerlaris); i++)
            {
                cout << (i + 1) << ". " << StringPos(dataTanamanTerlaris[i].namaTanaman, 23) << ": " << dataTanamanTerlaris[i].stok << " Buah" << endl;
            }
        }
        else
        {
            cout << "Belum ada tanaman yang terjual" << endl;
        }
        Border();

        cout << "Tekan [Enter] untuk kembali...";
        getline(cin, (*_temp));
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    delete[] dataTanamanTerlaris;
    delete sizeDataTanamanTerlaris;
    delete _temp;
    dataTanamanTerlaris = nullptr;
    sizeDataTanamanTerlaris = nullptr;
    _temp = nullptr;
}

void MenuUtamaSupplier(DataUtama &data, InfoLogin &infoLogin, DataMenu &dataMenu)
{
    try
    {
        while (CekLogin(data, infoLogin))
        {
            RefreshDataUtama(data);
            ClearScreen();
            Title("Menu Utama Supplier");
            cout << "Selamat Datang, " << infoLogin.username  << endl;
            cout << "1. Dashboard" << endl;
            cout << "2. Suplai Tanaman" << endl;
            cout << "3. Lihat Laporan Transaksi" << endl;
            cout << "4. Logout"<< endl;
            cout << endl;
            cout << "Pilih menu: ";

            string pilihan;
            getline(cin, pilihan);

            if (pilihan == "1")
            {
                DashboardSupplier(data, infoLogin);
            }
            else if (pilihan == "2")
            {
                SuplaiTanaman(data, infoLogin);
            }
            else if (pilihan == "3")
            {
                LihatLaporanTransaksi(data, infoLogin);
            }
            else if (pilihan == "4")
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