#ifndef MENU_ADMIN_H
#define MENU_ADMIN_H

#include "menu_utilities.h"

void TambahKategori(DataUtama &data)
{
    RefreshDataUtama(data);
    cout << "=== Tambah Kategori ===" << endl;
    cout << "Nama Kategori: ";
    string nama_kategori;
    getline(cin, nama_kategori);

    if (nama_kategori.empty())
    {
        cout << "Nama kategori tidak boleh kosong!" << endl;
        return;
    }

    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        if (data.dataKategori[i].namaKategori == nama_kategori)
        {
            cout << "Kategori sudah ada!" << endl;
            return;
        }
    }

    Kategori kategori_baru;
    kategori_baru.id = GetFreeKategoriId();
    kategori_baru.namaKategori = nama_kategori;

    TambahKategori(data.dataKategori, data.sizeDataKategori, kategori_baru);
}

// void HapusKategori(DataUtama &data)
// {
//     RefreshDataUtama(data);
//     cout << "=== Hapus Kategori ===" << endl;
//     cout << "ID Kategori: ";
//     int id_kategori;
//     cin >> id_kategori;

//     if (id_kategori <= 0 || id_kategori > data.sizeDataKategori)
//     {
//         cout << "ID kategori tidak valid!" << endl;
//         return;
//     }

//     for (int i = 0; i < data.sizeDataKategori; i++)
//     {
//         if (data.dataKategori[i].id == id_kategori)
//         {
//             HapusKategori(data.dataKategori, data.sizeDataKategori, i);
//             cout << "Kategori berhasil dihapus!" << endl;
//             return;
//         }
//     }

    cout << "Kategori tidak ditemukan!" << endl;
}
void ManajemenKategori (DataUtama &data)
{
    RefreshDataUtama(data);
    cout << "===> Manajemen Kategori <===" << endl;
    cout << "1. Tambah Kategori" << endl;
    cout << "2. Hapus Kategori" << endl;  
    cout << "3. Edit Kategori" << endl;
    cout << "4. Lihat Kategori" << endl;
    cout << "Pilih menu:";

    string pilihan;
    getline(cin, pilihan);
    if (pilihan == "1")
    {
        TambahKategori(data);
    }
    else if (pilihan == "2")
    {
        // HapusKategori(data);
    }
    else if (pilihan == "3")
    {
        // EditKategori(data);
    }
    else if (pilihan == "4")
    {
        // LihatKategori(data);
    }
    else
    {
        cout << "Pilihan tidak valid!" << endl;
    }
}

void ManajemenTanaman (DataUtama &data)
{
    RefreshDataUtama(data);
    
    cout << "=== Manajemen Tanaman ===" << endl;
    cout << "1. Manajemen Kategori" << endl;
    cout << "2. Validasi Status " << endl;
    cout << "Pilih menu: ";

    string pilihan;
    getline(cin, pilihan);

    if (pilihan == "1")
    {
        ManajemenKategori(data);
    }
    else if (pilihan == "2")
    {
        // HapusTanaman(data);
    }
}

void ManajemenSupplier (DataUtama &data)
{
    RefreshDataUtama(data);
    
    cout << "=== Manajemen Supplier ===" << endl;
    cout << "1. Lihat Supplier" << endl;
    cout << "2. Blokir Supplier" << endl;
    cout << "3. Hapus Supplier" << endl;
    cout << "Pilih menu: ";

    string pilihan;
    getline(cin, pilihan);

    if (pilihan == "1")
    {
        // TambahSupplier(data);
    }
    else if (pilihan == "2")
    {
        // HapusSupplier(data);
    }
    else if (pilihan == "3")
    {
        // EditSupplier(data);
    }
}

void MenuUtamaAdmin(DataUtama &data, InfoLogin &infoLogin, DataMenu &dataMenu)
{
    try
    {
        RefreshDataUtama(data);
        
        while (true)
        {
            cout << "\n=== Menu Utama Admin ===" << endl;
            cout << "1. Manajemen Tanaman" << endl;
            cout << "2. Manajemen Supplier" << endl;
            cout << "3. Logout" << endl;
            cout << "Pilih menu: ";

            string pilihan;
            getline(cin, pilihan);

            if (pilihan == "1")
            {
                ManajemenTanaman(data);
            }
            else if (pilihan == "2")
            {
                // MenuManajemenSupplier(data, infoLogin, dataMenu);
            }
            else if (pilihan == "3")
            {
                break; // Logout
            }
            else
            {
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
            }
        }
        // Menu Utama Admin

        // Note: Disarankan untuk Refresh Data Utama di awal Fungsi
        RefreshDataUtama(data);
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

void MenuManajemenTanaman(DataUtama &data, InfoLogin infoLogin, DataMenu dataMenu)
{
    try
    {
        // Menu Manajmene Tanaman

        // Note: Disarankan untuk Refresh Data Utama di awal Fungsi
        RefreshDataUtama(data);
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