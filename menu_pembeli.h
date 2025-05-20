#ifndef MENU_PEMBELI_H
#define MENU_PEMBELI_H
#include <iostream>
#include <filesystem>
#include "menu_utilities.h"
using namespace std;

void loadDataTanaman(DataUtama &data)
{
    json tanamanJson;

    for (int i = 0; i < data.sizeDataTanaman; i++)
    {
        data.dataTanaman[i].id = tanamanJson[i]["id"];
        data.dataTanaman[i].namaTanaman = tanamanJson[i]["namaTanaman"];
        data.dataTanaman[i].harga = tanamanJson[i]["harga"];
    }
}

void DaftarTanaman(DataUtama &data)
{
    cout << "=== Daftar Tanaman ===" << endl;

    if (data.sizeDataTanaman == 0)
    {
        cout << "Belum Ada Tanaman Yang Mulia!!!" << endl;
        return;
    }

    cout << "ID\tNama\t\tHarga";
    for (int i = 0; i < data.sizeDataTanaman; i++)
    {
        cout << data.dataTanaman[i].id << "" << data.dataTanaman[i].namaTanaman << "" << data.dataTanaman[i].harga << "" << endl;
    }
}

int interpolationSearchInt(const int arr[], int lo, int hi, int x)
{
    if (lo <= hi && x >= arr[lo] && x <= arr[hi])
    {
        int pos = lo + ((double)(hi - lo) / (arr[hi] - arr[lo])) * (x - arr[lo]);
        if (arr[pos] == x)
            return pos;
        if (arr[pos] < x)
            return interpolationSearchInt(arr, pos + 1, hi, x);
        if (arr[pos] > x)
            return interpolationSearchInt(arr, lo, pos - 1, x);
    }
    return -1;
}

void MenuUtamaPembeli(DataUtama &data, InfoLogin &infoLogin, DataMenu &dataMenu)
{
    try
    {
        RefreshDataUtama(data);

        while (true)
        {
            cout << "\n=== Menu Utama Pembeli ===" << endl;
            cout << "1. Daftar Tanaman" << endl;
            cout << "2. Searching Tanaman" << endl;
            cout << "3. Logout" << endl;
            cout << "Pilih menu: ";

            string pilihan;
            getline(cin, pilihan);

            if (pilihan == "1")
            {
                RefreshDataUtama(data);
                DaftarTanaman(data);
            }
            else if (pilihan == "2")
            {
            }
            else if (pilihan == "3")
            {
                infoLogin = {};
                break;
            }
            else
            {
                cout << "Pilihan tidak valid" << endl;
            }
        }
    }
    catch (invalid_argument &e)
    {
        cout << "Error: " << e.what() << '\n';
    }
    catch (exception &e)
    {
        cout << "Error: " << e.what() << '\n';
    }
}

#endif