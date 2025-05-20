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

int LinearSearch(DataUtama &data, string &key)
{
    int n = data.sizeDataTanaman;
    for (int i = 0; i < n; i++)
    {
        if (data.dataTanaman[i].namaTanaman == key)
        {
            return i;
        }
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
                RefreshDataUtama(data);
                cout << "Masukkan nama tanaman: ";
                string key;
                getline(cin, key);
                int Index = LinearSearch(data, key);
                if (Index != -1)
                {
                    auto &dataTanaman = data.dataTanaman[Index];
                    cout << "=== Detail Tanaman ===" << endl;
                    cout << "ID               : " << dataTanaman.id << endl;
                    cout << "Nama             : " << dataTanaman.namaTanaman << endl;
                    cout << "Harga            : " << dataTanaman.harga << endl;
                    cout << "Stok             : " << dataTanaman.stok << endl;

                    auto &dataKategori = data.dataKategori[Index];
                    cout << "Kategori         : " << dataKategori.namaKategori << endl;
                    cout << "HIDUP JOKOWII    : " << dataKategori.minSuhu << endl;
                    cout << "Max Suhu         : " << dataKategori.maxSuhu << endl;
                    cout << "Media Tanam      : " << dataKategori.mediaTanam << endl;
                }
                else
                {
                    cout << "Tanaman dengan nama '" << key << "' tidak ditemukan." << endl;
                }
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