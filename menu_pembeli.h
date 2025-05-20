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

    cout << "ID\tNama\t\tHarga\t\tSupplier";
    for (int i = 0; i < data.sizeDataTanaman; i++)
    {
        cout << data.dataTanaman[i].id << "" << data.dataTanaman[i].namaTanaman << "" << data.dataTanaman[i].harga << "" << data.dataTanaman[i].supplier.username << endl;
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

                int index[MAX_SIZE], cari = 0;
                for (int i = 0; i < data.sizeDataTanaman; i++)
                    if (data.dataTanaman[i].namaTanaman == key)
                        index[cari++] = i;

                if (!cari)
                {
                    cout << "Tanaman '" << key << "' tidak ditemukan.\n";
                    continue;
                }

                cout << "\nHasil:\n";
                for (int j = 0; j < cari; j++)
                    cout << j + 1 << ". "
                         << data.dataTanaman[index[j]].namaTanaman
                         << " (" << data.dataSupplier[index[j]].username << ")\n";

                cout << "Pilih nomor: ";
                int pilihan = stoi((getline(cin, key), key));
                if (pilihan > 0 && pilihan <= cari)
                {
                    int i = index[pilihan - 1];
                    cout << "\n=== Detail Informasi ===\n"
                         << "ID            : " << data.dataTanaman[i].id << "\n"
                         << "Nama          : " << data.dataTanaman[i].namaTanaman << "\n"
                         << "Harga         : " << data.dataTanaman[i].harga << "\n"
                         << "Stok          : " << data.dataTanaman[i].stok << "\n"
                         << "Supplier      : " << data.dataSupplier[i].username << "\n"
                         << "Kategori      : " << data.dataKategori[i].namaKategori << "\n"
                         << "Min Suhu      : " << data.dataKategori[i].minSuhu << "\n"
                         << "Max Suhu      : " << data.dataKategori[i].maxSuhu << "\n"
                         << "HIDUP JOKOWI  : " << data.dataKategori[i].mediaTanam << "\n";
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