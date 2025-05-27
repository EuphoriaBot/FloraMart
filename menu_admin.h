#ifndef MENU_ADMIN_H
#define MENU_ADMIN_H

#include "menu_utilities.h"

void FormTambahKategori(DataUtama &data)
{
    string temp;
    RefreshDataUtama(data);
    cout << "=== Tambah Kategori ===" << endl;
    cout << "Nama Kategori: ";
    string nama_kategori;
    getline(cin, nama_kategori);
    cout << "Min Suhu: ";
    float min_suhu; // Note: Jadiin float
    getline(cin, temp);
    min_suhu = stof(temp); // Convert string to float
    cout << "Max Suhu: ";
    getline(cin, temp);
    float max_suhu;
    max_suhu = stof(temp); // Convert string to float
    cout << "Media Tanam: ";
    string media_tanam;
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
    string temp;
    RefreshDataUtama(data);
    cout << "=== Hapus Kategori ===" << endl;
    cout << "Masukan Index : ";
    int NomorIndeks;
    getline(cin, temp);
    NomorIndeks = stoi(temp); // Convert string to int
    NomorIndeks -= 1;

    if (NomorIndeks < 0 || NomorIndeks >= data.sizeDataKategori)
    {
        cout << "ID kategori tidak valid!" << endl;
        return;
    }

    HapusKategori(data.dataKategori, data.sizeDataKategori, data.dataKategori[NomorIndeks]);
    cout << "Kategori berhasil dihapus!" << endl;
}

void FormEditKategori(DataUtama &data)
{
    string temp;
    RefreshDataUtama(data);
    cout << "=== Edit Kategori ===" << endl;
    cout << "Masukan Index: ";
    int NomorIndeks;
    getline(cin, temp);
    NomorIndeks = stoi(temp); // Convert string to int
    NomorIndeks -= 1;

    if (NomorIndeks < 0 || NomorIndeks >= data.sizeDataKategori)
    {
        cout << "ID kategori tidak valid!" << endl;
        return;
    }
    Kategori *KategoriDiedit = &data.dataKategori[NomorIndeks];

    cout << "Nama Kategori: ";
    getline(cin, temp);
    if (!temp.empty())
    {
        KategoriDiedit->namaKategori = temp;
    }

    cout << "Min Suhu: ";
    getline(cin, temp);
    if (!temp.empty())
    {
        KategoriDiedit->minSuhu = stof(temp);
    }

    cout << "Max Suhu: ";
    getline(cin, temp);
    if (!temp.empty())
    {
        KategoriDiedit->maxSuhu = stof(temp);
        ;
    }

    cout << "Media Tanam: ";
    getline(cin, temp);
    if (!temp.empty())
    {
        KategoriDiedit->mediaTanam = temp;
    }

    UpdateDataUtama(data);
    cout << "Kategori berhasil diperbarui!" << endl;
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

void MenuManajemenKategori(DataUtama &data)
{
    RefreshDataUtama(data);
    ClearScreen();
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
        FormLihatKategori(data);
        FormTambahKategori(data);
    }
    else if (pilihan == "3")
    {
        FormLihatKategori(data);
        FormEditKategori(data);
    }
    else if (pilihan == "4")
    {
        FormLihatKategori(data);
        FormHapusKategori(data);
    }
    else
    {
        cout << "Pilihan tidak valid!" << endl;
    }
}

void FormKesiapanTanaman(DataUtama &data)
{
    RefreshDataUtama(data);
    Suplai suplaidipilih;
    Tanaman tanamandipilih;
    cout << "=== Kesiapan Tanaman ===" << endl;
    for (int i = 0; i < data.sizeDataSuplai; i++)
    {
        if (data.dataSuplai[i].statusValidasi == false)
        {
            cout << data.dataSuplai[i].id << "|" << data.dataSuplai[i].namaTanaman << "|" << data.dataSuplai[i].jumlah << endl;
            ;
        }
    }
    cout << "Masukkan ID Suplai yang ingin divalidasi: ";
    string id_suplai;
    getline(cin, id_suplai);
    bool suplaiditemukan = false;
    for (int i = 0; i < data.sizeDataSuplai; i++)
    {
        if (data.dataSuplai[i].statusValidasi == false && data.dataSuplai[i].id == id_suplai)
        {
            suplaiditemukan = true;
            suplaidipilih = data.dataSuplai[i];
            break;
        }
    }
    if (!suplaiditemukan)
    {
        cout << "ID Tanaman tidak ditemukan atau sudah divalidasi." << endl;
        return;
    }
    string temp;

    cout << "Apakah Tanaman sudah pernah disuplai? (y/n): ";
    getline(cin, temp);
    if (temp == "n" || temp == "N")
    {
        string nama_tanaman;
        cout << "Masukkan nama tanaman: ";
        getline(cin, nama_tanaman);
        if (nama_tanaman.empty())
        {
            cout << "Nama tanaman tidak boleh" << endl;
            return;
        }
        double harga;
        cout << "Masukkan harga tanaman:";
        getline(cin, temp);
        harga = stod(temp); // Convert string to double
        if (harga < 1000)
        {
            cout << "Minimal harga harus 1000!" << endl;
            return;
        }
        for (int i = 0; i < data.sizeDataKategori; i++)
        {
            cout << i + 1 << ". " << data.dataKategori[i].namaKategori << endl;
        }
        cout << "Pilih Kategori: ";
        int pilihan_kategori;
        getline(cin, temp);
        pilihan_kategori = stoi(temp); // Convert string to int
        pilihan_kategori -= 1;

        int stok_diterima;
        cout << "Masukkan jumlah stok yang diterima: ";
        getline(cin, temp);
        stok_diterima = stoi(temp); // Convert string to int
        if (stok_diterima < 0)
        {
            cout << "Jumlah stok tidak boleh kurang dari nol!" << endl;
            return;
        }
        Tanaman tanamanBaru;
        tanamanBaru.id = GetFreeTanamanId();
        tanamanBaru.harga = harga;
        tanamanBaru.namaTanaman = nama_tanaman;
        tanamanBaru.kategori = data.dataKategori[pilihan_kategori];

        ValidasiTanaman validasiBaru;
        validasiBaru.id = GetFreeValidasiId();
        validasiBaru.tanaman = tanamanBaru;
        validasiBaru.stok_diterima = stok_diterima;
        validasiBaru.suplai = suplaidipilih;

        TambahTanaman(data.dataTanaman, data.sizeDataTanaman, tanamanBaru);
        TambahValidasi(data.dataValidasiTanaman, data.sizeDataValidasi, validasiBaru);
    }
    else if (temp == "y" || temp == "Y")
    {
        for (int i = 0; i < data.sizeDataTanaman; i++)
        {
            if (suplaidipilih.supplier.id == data.dataTanaman[i].supplier.id)
            {
                cout << data.dataSuplai[i].id << "|" << data.dataTanaman[i].namaTanaman << endl;
                ;
            }
        }
        cout << "Pilih Tanaman: ";
        string id_tanaman;
        getline(cin, id_tanaman);
        bool tanamanditemukan = false;
        for (int i = 0; i < data.sizeDataTanaman; i++)
        {
            if (data.dataTanaman[i].id == id_tanaman)
            {
                tanamanditemukan = true;
                tanamandipilih = data.dataTanaman[i];
                break;
            }
        }

        if (!tanamanditemukan)
        {
            cout << "ID Tanaman tidak ditemukan." << endl;
            return;
        }

        int stok_diterima;
        cout << "Masukkan jumlah stok yang diterima: ";
        getline(cin, temp);
        stok_diterima = stoi(temp); // Convert string to int
        if (stok_diterima < 0)
        {
            cout << "Jumlah stok tidak boleh kurang dari nol!" << endl;
            return;
        }

        ValidasiTanaman validasiBaru;
        validasiBaru.id = GetFreeValidasiId();
        validasiBaru.tanaman = tanamandipilih;
        validasiBaru.stok_diterima = stok_diterima;
        validasiBaru.suplai = suplaidipilih;

        TambahValidasi(data.dataValidasiTanaman, data.sizeDataValidasi, validasiBaru);
    }
}
// void MenuValidasiStatus(DataUtama &data)
// {
//     RefreshDataUtama(data);
//     cout << "=== Validasi Status ===" << endl;
//     cout << "1. Nambah Harga" << endl;
//     cout << "2. Kesiapan Tanaman" << endl;
//     cout << "Pilih menu: ";

//     string pilihan;
//     getline(cin, pilihan);

//     if (pilihan == "1")
//     {

//         FormNambahHarga(data);
//     }
//     else if (pilihan == "2")
//     {
//         FormKesiapanTanaman(data);
//     }
//     else
//     {
//         cout << "Pilihan tidak valid!" << endl;
//     }
// }

void MenuManajemenTanaman(DataUtama &data)
{
    RefreshDataUtama(data);
    ClearScreen();
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
        FormKesiapanTanaman(data);
    }
    else
    {
        cout << "Pilihan tidak valid!" << endl;
    }
}

void MenuManajemenSupplier(DataUtama &data)
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
        ClearScreen();
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