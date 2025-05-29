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
    ClearScreen();
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

void HalamanTransaksi(DataUtama &data, int indexTanaman)
{
    int stokTersedia = data.dataTanaman[indexTanaman].stok;
    
    ClearScreen();
    cout << "=== Halaman Transaksi ===";
    cout << "Stok tersedia: " << stokTersedia << endl;
    cout << "Masukkan jumlah yang ingin dibeli: ";

    string inputJumlah;
    getline(cin, inputJumlah);
    int jumlah = stoi(inputJumlah);

    if (jumlah <= 0)
    {
        cout << "Jumlah tidak valid" << endl;
        return;
    }

    if (jumlah > stokTersedia)
    {
        cout << "Jumlah melebihi stok yang tersedia" << endl;
        return;
    }

    int totalHarga = data.dataTanaman[indexTanaman].harga * jumlah;
    cout << "Total harga: " << totalHarga << endl;

    cout << "Lanjutkan pembelian? (y/n): ";
    string konfirmasi;
    getline(cin, konfirmasi);
    if (konfirmasi == "y")
    {
        data.dataTanaman[indexTanaman].stok -= jumlah;

        cout << "Pembelian berhasil" << endl;
        cout << "Sisa stok: " << data.dataTanaman[indexTanaman].stok << endl;
    }
    else
    {
        cout << "Pembelian dibatalkan" << endl;
    }
}

void SearchingTanaman(DataUtama &data)
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
        return;
    }

    cout << "Hasil:";
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
             << "ID            : " << data.dataTanaman[i].id << endl
             << "Nama          : " << data.dataTanaman[i].namaTanaman << endl
             << "Harga         : " << data.dataTanaman[i].harga << endl
             << "Stok          : " << data.dataTanaman[i].stok << endl
             << "Supplier      : " << data.dataSupplier[i].username << endl
             << "Kategori      : " << data.dataKategori[i].namaKategori << endl
             << "Min Suhu      : " << data.dataKategori[i].minSuhu << endl
             << "Max Suhu      : " << data.dataKategori[i].maxSuhu << endl
             << "HIDUP JOKOWI  : " << data.dataKategori[i].mediaTanam << endl;

        cout << "Apakah Anda ingin melakukan transaksi? (y/n): ";
        string jawab;
        getline(cin, jawab);
        if (jawab == "y" || jawab == "Y")
        {
            HalamanTransaksi(data, i);
        }
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
            ClearScreen();
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
                SearchingTanaman(data);
            }
            else if (pilihan == "3")
            {
                Logout(infoLogin);
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