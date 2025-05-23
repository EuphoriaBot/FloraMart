#ifndef MENU_SUPPLIER_H
#define MENU_SUPPLIER_H
#include <iostream>
#include <filesystem>
#include "menu_utilities.h"
using namespace std;

void NambahSuplai(Suplai dataSuplai[], int &size, Suplai suplaiBaru)
{
    if (size < MAX_SIZE)
    {
        dataSuplai[size] = suplaiBaru;
        size++;
    }
}

void SuplaiTanaman(DataUtama &data, InfoLogin infoLogin)
{
    if (data.sizeDataTanaman >= MAX_SIZE)
    {
        cout << "Kapasitas data tanaman sudah penuh";
        return;
    }

    string nama, stokStr;
    int stok;

    cout << "Nama Tanaman : ";
    getline(cin, nama);
    cout << "Stok         : ";
    getline(cin, stokStr);

    stok = stoi(stokStr);

    Suplai suplaiBaru;
    suplaiBaru.namaTanaman = nama;
    suplaiBaru.jumlah = stok;

    // Yo, jangan lupa isi atribut suplaiBaru yg lainnya :D
    // suplaiBaru.id = GetFreeSuplaiId(); // Dapatin id suplai yang bisa dipakai
    // suplaiBaru.supplier.id = infoLogin.id; // Dapatin id akun dari supplier yang dipakai

    TambahSuplai(data.dataSuplai, data.sizeDataSuplai, suplaiBaru);

    cout << "Tanaman berhasil disuplai " << endl;
}

void LihatLaporanTransaksi(DataUtama &data, InfoLogin infoLogin)
{
}

void MenuUtamaSupplier(DataUtama &data, InfoLogin infoLogin, DataMenu dataMenu)
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
                infoLogin = {};
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