#ifndef MENU_PEMBELI_H
#define MENU_PEMBELI_H
#include <iostream>
#include <filesystem>
#include "menu_utilities.h"
using namespace std;

void HalamanTransaksi(DataUtama &data, int indexTanaman, InfoLogin &infoLogin)
{
    data.flagRefreshTanaman = true;
    data.flagRefreshTransaksi = true;
    RefreshDataUtama(data);

    string temp;
    int stokTersedia = data.dataTanaman[indexTanaman].stok;

    Border();
    cout << "Transaksi" << endl
         << endl;
    cout << StringPos("Stok tersedia", 27) << ": " << stokTersedia << " Buah" << endl;
    cout << StringPos("Jumlah pembelian", 27) << ": ";

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
    cout << StringPos("Total Harga", 27) << ": Rp" << totalHarga << endl;

    for (int i = 0; i < data.sizeDataPembeli; i++)
    {
        if (data.dataPembeli[i].id == infoLogin.id)
        {
            cout << StringPos("Sisa Stok", 27) << ": Rp" << data.dataPembeli[i].saldo << endl;
        }
    }

    Border();
    cout << StringPos("Lanjutkan pembelian? (y/n)", 27) << ": ";
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

        data.flagRefreshTanaman = true;
        data.flagRefreshTransaksi = true;
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
            data.flagRefreshPembeli = true;
            RefreshDataUtama(data);

            cout << endl;
            cout << "Tekan [Enter] untuk kembali...";
            getline(cin, (temp));
            break;
        }
    }
}

void DaftarTanaman(DataUtama &data, InfoLogin &infoLogin)
{
    data.flagRefreshTanaman = true;
    RefreshDataUtama(data);
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
    cout << StringPos("ID", 27) << ": " << data.dataTanaman[index].id << endl
         << StringPos("Nama Tanaman", 27) << ": " << data.dataTanaman[index].namaTanaman << endl
         << StringPos("Harga", 27) << ": " << data.dataTanaman[index].harga << endl
         << StringPos("Stok", 27) << ": " << data.dataTanaman[index].stok << endl
         << StringPos("Supplier", 27) << ": " << data.dataTanaman[index].supplier.username << endl
         << StringPos("Kategori", 27) << ": " << data.dataKategori[index].namaKategori << endl
         << StringPos("Suhu", 27) << ": " << data.dataKategori[index].minSuhu << " - " << data.dataKategori[index].minSuhu << "\u00B0C" << endl
         << StringPos("Media Tanam", 27) << ": " << data.dataKategori[index].mediaTanam << endl;
    Border();
    cout << StringPos("Beli Tanaman? (y/n)", 27) << ": ";
    string jawab;
    getline(cin, jawab);
    if (jawab == "y" || jawab == "Y")
    {
        HalamanTransaksi(data, index, infoLogin);
    }
}

void SearchingTanaman(DataUtama &data, InfoLogin &infoLogin)
{
    data.flagRefreshTanaman = true;
    RefreshDataUtama(data);

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
        cout << "Tekan [Enter] untuk kembali ke menu utama...";
        getline(cin, temp);
        return;
    }

    cout << "Hasil:" << endl;
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
        cout << StringPos("ID", 27) << ": " << data.dataTanaman[i].id << endl
             << StringPos("Nama Tanaman", 27) << ": " << data.dataTanaman[i].namaTanaman << endl
             << StringPos("Harga", 27) << ": " << data.dataTanaman[i].harga << endl
             << StringPos("Stok", 27) << ": " << data.dataTanaman[i].stok << endl
             << StringPos("Supplier", 27) << ": " << data.dataTanaman[i].supplier.username << endl
             << StringPos("Kategori", 27) << ": " << data.dataKategori[i].namaKategori << endl
             << StringPos("Suhu", 27) << ": " << data.dataKategori[i].minSuhu << " - " << data.dataKategori[i].minSuhu << "\u00B0C" << endl
             << StringPos("Media Tanam", 27) << ": " << data.dataKategori[i].mediaTanam << endl;
        Border();
        cout << StringPos("Beli Tanaman? (y/n)", 27) << ": ";
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
        string temp;

        while (CekLogin(data, infoLogin))
        {
            RefreshDataUtama(data);
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
                return;
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