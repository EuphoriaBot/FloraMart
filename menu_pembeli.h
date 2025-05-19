#ifndef MENU_PEMBELI_H
#define MENU_PEMBELI_H
#include <iostream>
#include <filesystem>
#include "menu_utilities.h"
using namespace std;

void loadDataTanaman(DataUtama &data)
{
    json tanamanJson;
    ReadJson(tanamanJson, data.sizeDataTanaman, "data_tanaman.json");

    for (int i = 0; i < data.sizeDataTanaman; i++)
    {
        data.dataTanaman[i].id = tanamanJson[i]["id"];
        data.dataTanaman[i].namaTanaman = tanamanJson[i]["namaTanaman"];
        data.dataTanaman[i].harga = tanamanJson[i]["harga"];
        data.dataTanaman[i].stok = tanamanJson[i]["stok"];
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
        cout << data.dataTanaman[i].id << "\t" << data.dataTanaman[i].namaTanaman << "\t\t" << data.dataTanaman[i].harga << "\t" << endl;
    }
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
                loadDataTanaman(data);
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
                cout << "Pilihan tidak valid." << endl;
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