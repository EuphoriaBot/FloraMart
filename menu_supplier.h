#ifndef MENU_SUPPLIER_H
#define MENU_SUPPLIER_H
#include <iostream>
#include <filesystem>
#include "menu_utilities.h"
using namespace std;

void SuplaiTanaman(DataUtama &data, InfoLogin infoLogin)
{
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
                SuplaiTanaman(data, infoLogin);
            }
            else if (pilihan == "2")
            {
                LihatLaporanTransaksi(data, infoLogin);
            }
            else if (pilihan == "3")
            {
                cout << "Logout berhasil.\n";
                break;
            }
            else
            {
                cout << "Pilihan tidak valid. Coba lagi.\n";
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