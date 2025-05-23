#ifndef MENU_ADMIN_H
#define MENU_ADMIN_H

#include "menu_utilities.h"

void FormTambahKategori(DataUtama &data)
{
    RefreshDataUtama(data);
    cout << "=== Tambah Kategori ===" << endl;
    cout << "Nama Kategori: ";
    string nama_kategori;
    cin.ignore();
    getline(cin, nama_kategori);
    cout << "Min Suhu: ";
    int min_suhu;
    cin >> min_suhu;
    cout << "Max Suhu: ";
    int max_suhu;
    cin >> max_suhu;
    cout << "Media Tanam: ";
    string media_tanam;
    cin.ignore();
    getline(cin, media_tanam);
    
    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        if (data.dataKategori[i].namaKategori == nama_kategori)
        {
            cout << "Nama kategori sudah ada!" << endl;
            return;
        }
    }
    Kategori kategoriBaru = {GetFreeKategoriId(), nama_kategori, min_suhu, max_suhu, media_tanam};
    
    TambahKategori(data.dataKategori, data.sizeDataKategori, kategoriBaru);
    
    cout << "Kategori berhasil ditambahkan!" << endl;
}

void FormHapusKategori(DataUtama &data)
{
    RefreshDataUtama(data);
    cout << "=== Hapus Kategori ===" << endl;
    cout << "ID Kategori: ";
    int id_kategori;
    cin >> id_kategori;
    id_kategori--;

    if (id_kategori <= 0 || id_kategori > data.sizeDataKategori)
    {
        cout << "ID kategori tidak valid!" << endl;
        return;
    }

    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        string nama_kategori;
        cout << "Nama Kategori: "; 
        if (data.dataKategori[i].namaKategori == nama_kategori)
        {
            HapusKategori(data.dataKategori, data.sizeDataKategori, data.dataKategori [i]);
            cout << "Kategori berhasil dihapus!" << endl;
            return;
        }
    }
    cout << "Kategori tidak ditemukan!" << endl;
}

void FormEditKategori(DataUtama &data)
{
    RefreshDataUtama(data);
    cout << "=== Edit Kategori ===" << endl;
    cout << "ID Kategori: ";
    int id_kategori;
    cin >> id_kategori;
    id_kategori--;

    if (id_kategori <= 0 || id_kategori > data.sizeDataKategori)
    {
        cout << "ID kategori tidak valid!" << endl;
        return;
    }

    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        string nama_kategori;
        cout << "Nama Kategori: ";
        if (data.dataKategori[i].namaKategori == nama_kategori)
        {
            cout << "Nama Kategori Baru: ";
            string nama_kategori_baru;
            cin.ignore();
            getline(cin, nama_kategori_baru);
            cout << "Min Suhu Baru: ";
            int min_suhu_baru;
            cin >> min_suhu_baru;
            cout << "Max Suhu Baru: ";
            int max_suhu_baru;
            cin >> max_suhu_baru;
            cout << "Media Tanam Baru: ";
            string media_tanam_baru;
            cin.ignore();
            getline(cin, media_tanam_baru);

            data.dataKategori[i].namaKategori = nama_kategori_baru;
            data.dataKategori[i].minSuhu = min_suhu_baru;
            data.dataKategori[i].maxSuhu = max_suhu_baru;
            data.dataKategori[i].mediaTanam = media_tanam_baru;
            cout << "Kategori berhasil diedit!" << endl;
            return;
        }
    }

    cout << "Kategori tidak ditemukan!" << endl;
}
void FormLihatKategori(DataUtama &data)
{
    RefreshDataUtama(data);
    cout << "=== Lihat Kategori ===" << endl;
    cout << "ID Kategori\tNama Kategori\tMin Suhu\tMax Suhu\tMedia Tanam" << endl;
    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        cout << data.dataKategori[i].id << "\t\t";
        cout << data.dataKategori[i].namaKategori << "\t\t";
        cout << data.dataKategori[i].minSuhu << "\t\t";
        cout << data.dataKategori[i].maxSuhu << "\t\t";
        cout << data.dataKategori[i].mediaTanam << endl;
    }
}

void MenuManajemenKategori (DataUtama &data)
{
    RefreshDataUtama(data);
    cout << "===> Manajemen Kategori <===" << endl;
    cout << "1. Lihat Kategori" << endl;
    cout << "2. Tambah Kategori" << endl;  
    cout << "3. Edit Kategori" << endl;
    cout << "4. Hapus Kategori" << endl;
    cout << "Pilih menu:";

    string pilihan;
    getline(cin, pilihan);
    if (pilihan == "1")
    {
        FormLihatKategori(data);
    }
    else if (pilihan == "2")
    {
        FormTambahKategori(data);
    }
    else if (pilihan == "3")
    {
        FormEditKategori(data);
    }
    else if (pilihan == "4")
    {
        FormHapusKategori(data);
    }
    else
    {
        cout << "Pilihan tidak valid!" << endl;
    }
}

void MenuManajemenTanaman (DataUtama &data)
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
        MenuManajemenKategori(data);
    }
    else if (pilihan == "2")
    {
        // HapusTanaman(data);
    }
}

void MenuManajemenSupplier (DataUtama &data)
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
            cout << "3. Notifikasi" << endl;
            cout << "4. Logout" << endl;
            cout << "Pilih menu: ";

            string pilihan;
            getline(cin, pilihan);

            if (pilihan == "1")
            {
                MenuManajemenTanaman(data);
            }
            else if (pilihan == "2")
            {
                // MenuManajemenSupplier(data, infoLogin, dataMenu);
            }
            else if (pilihan == "3")
            {
                // MenuNotifikasi(data, infoLogin, dataMenu);
            }
            else if (pilihan == "4")
            {
                cout << "Anda telah logout!" << endl;
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