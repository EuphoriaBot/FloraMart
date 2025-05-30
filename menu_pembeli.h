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

void HalamanTransaksi(DataUtama &data, int indexTanaman, InfoLogin &infoLogin)
{
    string temp;
    int stokTersedia = data.dataTanaman[indexTanaman].stok;

    Border();
    cout << "Transaksi" << endl
         << endl;
    cout << "Stok tersedia\t: " << stokTersedia << " Buah" << endl;
    cout << "Jumlah Pembelian: ";

    string inputJumlah;
    getline(cin, inputJumlah);
    int jumlah = stoi(inputJumlah);

    if (jumlah <= 0)
    {
        cout << "Jumlah tidak valid!";
        getline(cin, temp);
        return;
    }

    if (jumlah > stokTersedia)
    {
        cout << "Jumlah melebihi stok yang tersedia!";
        getline(cin, temp);
        return;
    }

    int totalHarga = data.dataTanaman[indexTanaman].harga * jumlah;
    cout << endl;
    cout << "Total harga\t: Rp" << totalHarga << endl;

    for (int i = 0; i < data.sizeDataPembeli; i++)
    {
        if (data.dataPembeli[i].id == infoLogin.id)
        {
            cout << "Saldo Anda\t: Rp" << data.dataPembeli[i].saldo << endl;
        }
    }

    Border();
    cout << "Lanjutkan pembelian? (y/n): ";
    string konfirmasi;
    getline(cin, konfirmasi);
    cout << endl;
    if (konfirmasi == "y")
    {
        Transaksi transaksiBaru;
        transaksiBaru.id = GetFreeTransaksiId();
        transaksiBaru.tanaman = data.dataTanaman[indexTanaman];
        transaksiBaru.pembeli.id = infoLogin.id;
        transaksiBaru.jumlahTanaman = jumlah;

        TambahTransaksi(data.dataTransaksi, data.sizeDataTransaksi, transaksiBaru);
        RefreshDataUtama(data);

        cout << "Pembelian berhasil!" << endl;
        cout << "Sisa stok: " << data.dataTanaman[indexTanaman].stok << " Buah";
        getline(cin, temp);
    }
    else
    {
        cout << "Pembelian dibatalkan!";
        getline(cin, temp);
    }
}

void MenuTopUp(DataUtama &data, InfoLogin &infoLogin)
{
    string temp;
    ClearScreen();
    Title("Menu Top Up");
    cout << "1. Rp50.000" << endl;
    cout << "2. Rp100.000" << endl;
    cout << "3. Rp200.000" << endl;
    Border();
    cout << "Pilih menu: ";

    string pilihan;
    getline(cin, pilihan);
    int indexPembeli = -1;

    for (int i = 0; i < data.sizeDataPembeli; i++)
    {
        if (data.dataPembeli[i].id == infoLogin.id)
        {
            if (pilihan == "1")
            {
                data.dataPembeli[i].saldo += 50000;
                cout << "Berhasil Menambahkan Saldo Sebesar Rp50.000" << endl;
                cout << "Saldo Anda Sekarang Adalah Rp" << data.dataPembeli[i].saldo << endl;
            }
            else if (pilihan == "2")
            {
                data.dataPembeli[i].saldo += 100000;
                cout << "Berhasil Menambahkan Saldo Sebesar Rp100.000" << endl;
                cout << "Saldo Anda Sekarang Adalah Rp" << data.dataPembeli[i].saldo << endl;
            }
            else if (pilihan == "3")
            {
                data.dataPembeli[i].saldo += 150000;
                cout << "Berhasil Menambahkan Saldo Sebesar Rp200.000" << endl;
                cout << "Saldo Anda Sekarang Adalah Rp" << data.dataPembeli[i].saldo << endl;
            }
            else
            {
                cout << "Pilihan tidak valid" << endl;
                getline(cin, temp);
            }
            UpdateDataUtama(data);
            cout << "Tekan [Enter] untuk kembali...";
            getline(cin, (temp));
            break;
        }
    }
}

void DaftarTanaman(DataUtama &data, InfoLogin &infoLogin)
{
    string temp;

    ClearScreen();
    Title("Daftar Tanaman");
    if (data.sizeDataTanaman == 0)
    {
        cout << "Belum Ada Tanaman Yang Mulia!!!";
        getline(cin, temp);
        return;
    }

    Border("-", 80);
    cout << "| "
         << StringPos("ID", 5) << " | "
         << StringPos("Nama", 28) << " | "
         << StringPos("Harga", 14) << " | "
         << StringPos("Supplier", 20) << " |" << endl;
    Border("-", 80);
    for (int i = 0; i < data.sizeDataTanaman; i++)
    {
        cout << "| "
             << StringPos(data.dataTanaman[i].id, 5) << " | "
             << StringPos(data.dataTanaman[i].namaTanaman, 28) << " | "
             << StringPos("Rp" + dtos(data.dataTanaman[i].harga), 14) << " | "
             << StringPos(data.dataTanaman[i].supplier.username, 20) << " |" << endl;
    }
    Border("-", 80);

    cout << "\nMasukkan ID tanaman untuk melihat detail: ";
    string idInput;
    getline(cin, idInput);

    int index = -1;
    for (int i = 0; i < data.sizeDataTanaman; i++)
    {
        if (data.dataTanaman[i].id == idInput)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Tanaman dengan ID '" << idInput << "' tidak ditemukan" << endl;
        getline(cin, temp);
        return;
    }

    ClearScreen();
    Title("Detail Informasi");
    cout << "ID            : " << data.dataTanaman[index].id << endl
         << "Nama          : " << data.dataTanaman[index].namaTanaman << endl
         << "Harga         : " << data.dataTanaman[index].harga << endl
         << "Stok          : " << data.dataTanaman[index].stok << endl
         << "Supplier      : " << data.dataSupplier[index].username << endl
         << "Kategori      : " << data.dataKategori[index].namaKategori << endl
         << "Min Suhu      : " << data.dataKategori[index].minSuhu << endl
         << "Max Suhu      : " << data.dataKategori[index].maxSuhu << endl
         << "Media Tanam   : " << data.dataKategori[index].mediaTanam << endl;
    Border();
    cout << "Apakah Anda ingin melakukan transaksi? (y/n): ";
    string jawab;
    getline(cin, jawab);
    if (jawab == "y" || jawab == "Y")
    {
        HalamanTransaksi(data, index, infoLogin);
    }
}

void SearchingTanaman(DataUtama &data, InfoLogin &infoLogin)
{
    ClearScreen();
    Title("Searching Tanaman");
    string temp;
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
        getline(cin, temp);
        cout << "Tekan [Enter] untuk kembali ke menu utama...";
        return;
    }

    cout << "Hasil:";
    for (int j = 0; j < cari; j++)
        cout << j + 1 << ". "
             << data.dataTanaman[index[j]].namaTanaman
             << " (" << data.dataTanaman[index[j]].supplier.username << ")\n";

    cout << "Pilih nomor: ";
    int pilihan = stoi((getline(cin, key), key));
    if (pilihan > 0 && pilihan <= cari)
    {
        int i = index[pilihan - 1];
        ClearScreen();
        Title("Detail Informasi");
        cout << "ID            : " << data.dataTanaman[i].id << endl
             << "Nama          : " << data.dataTanaman[i].namaTanaman << endl
             << "Harga         : " << data.dataTanaman[i].harga << endl
             << "Stok          : " << data.dataTanaman[i].stok << endl
             << "Supplier      : " << data.dataSupplier[i].username << endl
             << "Kategori      : " << data.dataKategori[i].namaKategori << endl
             << "Min Suhu      : " << data.dataKategori[i].minSuhu << endl
             << "Max Suhu      : " << data.dataKategori[i].maxSuhu << endl
             << "HIDUP JOKOWI  : " << data.dataKategori[i].mediaTanam << endl;
        Border();
        cout << "Apakah Anda ingin melakukan transaksi? (y/n): ";
        string jawab;
        getline(cin, jawab);
        if (jawab == "y" || jawab == "Y")
        {
            HalamanTransaksi(data, i, infoLogin);
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
        string temp;

        while (CekLogin(data, infoLogin))
        {
            ClearScreen();
            Title("Menu Utama Pembeli");
            cout << "Selamat Datang, " << infoLogin.username << endl;
            cout << "1. Daftar Tanaman" << endl;
            cout << "2. Searching Tanaman" << endl;
            cout << "3. Top Up" << endl;
            cout << "4. Logout" << endl;
            Border();
            cout << "Pilih menu: ";

            string pilihan;
            getline(cin, pilihan);

            if (pilihan == "1")
            {
                RefreshDataUtama(data);
                DaftarTanaman(data, infoLogin);
            }
            else if (pilihan == "2")
            {
                SearchingTanaman(data, infoLogin);
            }
            else if (pilihan == "3")
            {
                MenuTopUp(data, infoLogin);
            }
            else if (pilihan == "4")
            {
                Logout(infoLogin);
                break;
            }
            else
            {
                cout << "Pilihan tidak valid" << endl;
                getline(cin, temp);
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