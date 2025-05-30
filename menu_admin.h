#ifndef MENU_ADMIN_H
#define MENU_ADMIN_H

#include "menu_utilities.h"

void FormTambahKategori(DataUtama &data)
{
    data.flagRefreshKategori = true;

    ClearScreen();
    Title("Lihat Kategori");
    cout << StringPos("ID", 5, "Left");
    cout << StringPos("Nama Kategori", 24, "Left");
    cout << StringPos("Suhu", 14, "Left");
    cout << StringPos("Media Tanam", 20, "Left") << endl;
    cout << endl;

    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        cout << StringPos(data.dataKategori[i].id, 5, "Left");
        cout << StringPos(data.dataKategori[i].namaKategori, 24, "Left");
        cout << StringPos(ftos(data.dataKategori[i].minSuhu) + " - " + ftos(data.dataKategori[i].maxSuhu) + " C", 14, "Left");
        cout << StringPos(data.dataKategori[i].mediaTanam, 20, "Left") << endl;
    }
    cout << endl;

    string temp;
    Title("Tambah Kategori");
    cout << "Nama Kategori: ";
    string nama_kategori;
    getline(cin, nama_kategori);

    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        if (LowerCase(data.dataKategori[i].namaKategori) == LowerCase(nama_kategori))
        {
            cout << "Nama Kategori sudah ada!";
            getline(cin, temp);
            return;
        }
        else if (IsValidString(nama_kategori) == false)
        {
            cout << "Nama Kategori harus berupa string alfabet!";
            getline(cin, temp);
            return;
        }
    }

    float min_suhu;
    cout << "Min Suhu: ";
    getline(cin, temp);
    if (!IsValidNumeric(temp))
    {
        cout << "Input harus angka atau angka tidak valid!";
        getline(cin, temp);
        return;
    }
    min_suhu = stof(temp);

    float max_suhu;
    cout << "Max Suhu: ";
    getline(cin, temp);
    if (!IsValidNumeric(temp))
    {
        cout << "Input harus angka atau angka tidak valid!";
        getline(cin, temp);
        return;
    }
    max_suhu = stof(temp);

    if (min_suhu > max_suhu)
    {
        cout << "Maksimum Suhu tidak boleh kurang dari Minimum Suhu!";
        getline(cin, temp);
        return;
    }
    else
    {
        cout << "Media Tanam: ";
        string media_tanam;
        getline(cin, media_tanam);
        if (IsValidString(media_tanam) == false)
        {
            cout << "Media Tanam harus berupa string alfabet!";
            getline(cin, temp);
            return;
        }
        cout << "Apakah anda yakin ingin menambahkan kategori " << nama_kategori << "? [y/n]: ";
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
        {
            Kategori kategoriBaru = {GetFreeKategoriId(), nama_kategori, min_suhu, max_suhu, media_tanam};
            TambahKategori(data.dataKategori, data.sizeDataKategori, kategoriBaru);
            cout << endl;
            cout << "Kategori berhasil ditambahkan!" << endl;
            cout << "Tekan [enter] untuk kembali ...";
            getline(cin, temp);
        }
        else
        {
            return;
        }
    }
}

void FormHapusKategori(DataUtama &data)
{
    data.flagRefreshKategori = true;

    ClearScreen();
    Title("Lihat Kategori");
    cout << StringPos("ID", 5, "Left");
    cout << StringPos("Nama Kategori", 24, "Left");
    cout << StringPos("Suhu", 14, "Left");
    cout << StringPos("Media Tanam", 20, "Left") << endl;
    cout << endl;

    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        cout << StringPos(data.dataKategori[i].id, 5, "Left");
        cout << StringPos(data.dataKategori[i].namaKategori, 24, "Left");
        cout << StringPos(ftos(data.dataKategori[i].minSuhu) + " - " + ftos(data.dataKategori[i].maxSuhu) + " C", 14, "Left");
        cout << StringPos(data.dataKategori[i].mediaTanam, 20, "Left") << endl;
    }
    cout << endl;

    string temp;
    Title("Hapus Kategori");
    cout << "Masukan ID : ";
    Kategori kategoriDihapus;
    string ID;
    getline(cin, ID);

    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        if (data.dataKategori[i].id == ID)
        {
            kategoriDihapus = data.dataKategori[i];
            break;
        }
    }
    if (!kategoriDihapus.id.empty())
    {
        cout << "Anda yakin ingin menghapus kategori " << kategoriDihapus.namaKategori << "? [y/n]: ";
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
        {
            HapusKategori(data.dataKategori, data.sizeDataKategori, kategoriDihapus);
            cout << endl;
            cout << "Kategori berhasil dihapus!" << endl;
            cout << "Tekan [enter] untuk kembali ...";
            getline(cin, temp);
            return;
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "ID Kategori tidak ditemukan!";
        getline(cin, temp);
        return;
    }
}

void FormEditKategori(DataUtama &data)
{
    data.flagRefreshKategori = true;
    data.flagRefreshTanaman = true;
    data.flagRefreshTransaksi = true;

    ClearScreen();

    Title("Lihat Kategori");
    cout << StringPos("ID", 5, "Left");
    cout << StringPos("Nama Kategori", 24, "Left");
    cout << StringPos("Suhu", 14, "Left");
    cout << StringPos("Media Tanam", 20, "Left") << endl;
    cout << endl;

    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        cout << StringPos(data.dataKategori[i].id, 5, "Left");
        cout << StringPos(data.dataKategori[i].namaKategori, 24, "Left");
        cout << StringPos(ftos(data.dataKategori[i].minSuhu) + " - " + ftos(data.dataKategori[i].maxSuhu) + " C", 14, "Left");
        cout << StringPos(data.dataKategori[i].mediaTanam, 20, "Left") << endl;
    }
    cout << endl;

    string temp;
    Title("Edit Kategori");
    cout << "Masukan Id yang ingin diedit: ";
    getline(cin, temp);
    Kategori *kategoriDiedit = new Kategori();

    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        if (data.dataKategori[i].id == temp)
        {
            kategoriDiedit = &data.dataKategori[i];
            break;
        }
    }

    if (kategoriDiedit->id.empty())
    {
        cout << "ID Kategori tidak ditemukan!";
        getline(cin, temp);
        return;
    }

    cout << "Nama Kategori: ";
    getline(cin, temp);
    if (!temp.empty())
    {
        if (IsValidString(temp) == false)
        {
            cout << "Nama Kategori harus berupa string alfabet!";
            getline(cin, temp);
            return;
        }
        for (int i = 0; i < data.sizeDataKategori; i++)
        {
            if (LowerCase(data.dataKategori[i].namaKategori) == LowerCase(temp))
            {
                cout << "Nama Kategori sudah digunakan!";
                getline(cin, temp);
                return;
            }
        }

        kategoriDiedit->namaKategori = temp;
    }

    cout << "Min Suhu: ";
    getline(cin, temp);
    if (!temp.empty())
    {
        if (!IsValidNumeric(temp))
        {
            cout << "Input harus angka atau angka tidak valid!";
            getline(cin, temp);
            return;
        }
        kategoriDiedit->minSuhu = stof(temp);
    }

    cout << "Max Suhu: ";
    getline(cin, temp);
    if (!temp.empty())
    {
        if (!IsValidNumeric(temp))
        {
            cout << "Input harus angka atau angka tidak valid!";
            getline(cin, temp);
            return;
        }
        kategoriDiedit->maxSuhu = stof(temp);
    }

    if (kategoriDiedit->maxSuhu < kategoriDiedit->minSuhu)
    {
        cout << "Maksimum Suhu tidak boleh kurang dari Minimum Suhu!";
        getline(cin, temp);
        return;
    }
    else
    {
        cout << "Media Tanam: ";
        getline(cin, temp);
        if (!temp.empty())
        {
            if (IsValidString(temp) == false)
            {
                cout << "Media Tanam harus berupa string alfabet!";
                getline(cin, temp);
                return;
            }
            kategoriDiedit->mediaTanam = temp;
        }
        cout << "Apakah anda yakin ingin mengedit kategori " << kategoriDiedit->namaKategori << "? [y/n]: ";
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
        {
            UpdateDataUtama(data);
            cout << endl;
            cout << "Kategori berhasil diedit!" << endl;
            cout << "Tekan [enter] untuk kembali ..." << endl;
            getline(cin, temp);
        }
        else
        {
            return;
        }
    }
}

void FormLihatKategori(DataUtama &data)
{
    data.flagRefreshKategori = true;
    RefreshDataUtama(data);

    ClearScreen();
    Title("Lihat Kategori");
    cout << StringPos("ID", 5, "Left");
    cout << StringPos("Nama Kategori", 24, "Left");
    cout << StringPos("Suhu", 14, "Left");
    cout << StringPos("Media Tanam", 20, "Left") << endl;
    cout << endl;

    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        cout << StringPos(data.dataKategori[i].id, 5, "Left");
        cout << StringPos(data.dataKategori[i].namaKategori, 24, "Left");
        cout << StringPos(ftos(data.dataKategori[i].minSuhu) + " - " + ftos(data.dataKategori[i].maxSuhu) + " C", 14, "Left");
        cout << StringPos(data.dataKategori[i].mediaTanam, 20, "Left") << endl;
    }
    cout << endl;
    cout << "Tekan [enter] untuk kembali ..." << endl;
    getline(cin, data.dataKategori[0].id); // To pause the screen
}

void FormSortingKategori(DataUtama &data)
{
    data.flagRefreshKategori = true;
    RefreshDataUtama(data);

    string temp;

    ClearScreen();
    Title("Sorting Kategori Berdasarkan Nama Secara Ascending");
    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        cout << data.dataKategori[i].namaKategori << endl;
    }
    cout << endl;
    cout << "Apakah Anda yakin ingin mengurutkan kategori berdasarkan nama secara ascending? [y/n]: ";
    string konfirmasi;
    getline(cin, konfirmasi);
    cout << endl;
    Border();
    if (konfirmasi == "y" || konfirmasi == "Y")
    {
        for (int i = 0; i < data.sizeDataKategori - 1; i++)
        {
            for (int j = 0; j < data.sizeDataKategori - i - 1; j++)
            {
                if (data.dataKategori[j].namaKategori > data.dataKategori[j + 1].namaKategori)
                {
                    Kategori temp = data.dataKategori[j];
                    data.dataKategori[j] = data.dataKategori[j + 1];
                    data.dataKategori[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < data.sizeDataKategori; i++)
        {
            cout << data.dataKategori[i].namaKategori << endl;
        }
        cout << endl;
        cout << "Kategori berhasil diurutkan!" << endl;
        cout << "Tekan [enter] untuk kembali ..." << endl;
        getline(cin, temp); // To pause the screen
    }
    else
    {
        return;
    }
}

void MenuManajemenKategori(DataUtama &data, InfoLogin &infoLogin)
{
    while (CekLogin(data, infoLogin))
    {
        data.flagRefreshKategori = true;
        RefreshDataUtama(data);
        ClearScreen();
        Title("Manajemen Kategori");
        cout << endl;
        cout << "Pilihan Menu yang Tersedia: " << endl;
        cout << endl;
        cout << "1. Lihat Kategori" << endl;
        cout << "2. Tambah Kategori" << endl;
        cout << "3. Edit Kategori" << endl;
        cout << "4. Hapus Kategori" << endl;
        cout << "5. Sorting Kategori Berdasarkan Nama Secara Ascending" << endl;
        cout << "6. Kembali ke Manajemen Tanaman" << endl;
        cout << endl;
        cout << "Pilih menu: ";

        string pilihan;
        string temp;
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
        else if (pilihan == "5")
        {
            FormSortingKategori(data);
        }
        else if (pilihan == "6")
        {
            return;
        }
        else
        {
            cout << "Pilihan tidak valid!" << endl;
            getline(cin, temp);
        }
    }
}

void FormKesiapanTanaman(DataUtama &data)
{
    data.flagRefreshValidasiTanaman = true;
    string temp;
    Suplai suplaidipilih;
    Tanaman tanamandipilih;

    ClearScreen();
    Title("Validasi Suplai Tanaman");
    cout << endl;
    cout << "Tanaman yang menunggu validasi: " << endl;
    cout << endl;

    cout << StringPos("ID Suplai", 13, "Left");
    cout << StringPos("Nama Tanaman", 28, "Left");
    cout << StringPos("Jumlah", 8, "Left");
    cout << StringPos("Supplier", 24, "Left") << endl;

    for (int i = 0; i < data.sizeDataSuplai; i++)
    {
        if (data.dataSuplai[i].statusValidasi == false)
        {
            cout << StringPos(data.dataSuplai[i].id, 13, "Left");
            cout << StringPos(data.dataSuplai[i].namaTanaman, 28, "Left");
            cout << StringPos(to_string(data.dataSuplai[i].jumlah), 8, "Left");
            cout << StringPos(data.dataSuplai[i].supplier.username, 24, "Left");
            cout << endl;
        }
    }
    cout << endl;
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
        cout << "ID Suplai tidak ditemukan atau sudah divalidasi.";
        getline(cin, temp);
        return;
    }

    bool punyaTanaman = false;

    for (int i = 0; i < data.sizeDataTanaman; i++)
    {
        if (data.dataTanaman[i].supplier.id == suplaidipilih.supplier.id)
        {
            punyaTanaman = true;
        }
    }

    Border();
    cout << "Validasi Tanaman" << endl;
    cout << endl;
    if (punyaTanaman)
    {
        cout << "Apakah Tanaman sudah pernah disuplai? (y/n): ";
        getline(cin, temp);
    }
    else
    {
        temp = "n";
    }
    cout << endl;

    if (temp == "n" || temp == "N")
    {
        string nama_tanaman;
        cout << StringPos("Masukkan nama tanaman baru", 31) << ": ";
        getline(cin, nama_tanaman);
        if (nama_tanaman.empty())
        {
            cout << "Nama tanaman tidak boleh kosong";
            getline(cin, temp);
            return;
        }
        else if (IsValidString(nama_tanaman) == false)
        {
            cout << "Nama tanaman harus berupa string alfabet!";
            getline(cin, temp);
            return;
        }
        double harga;
        cout << StringPos("Masukkan harga tanaman (Rp)", 31) << ": ";
        getline(cin, temp);
        if (!IsValidNumeric(temp))
        {
            cout << "Input harus angka atau angka tidak valid!";
            getline(cin, temp);
            return;
        }
        harga = stod(temp);
        if (harga < 1000)
        {
            cout << "Minimal harga harus 1000!";
            getline(cin, temp);
            return;
        }

        cout << endl;
        cout << "Kategori:" << endl;
        cout << StringPos("ID", 8)
             << StringPos("Kategori", 28) << endl;
        for (int i = 0; i < data.sizeDataKategori; i++)
        {
            cout << StringPos(data.dataKategori[i].id, 5) << " > " << data.dataKategori[i].namaKategori << endl;
        }
        int pilihan_kategori;
        cout << endl;
        cout << StringPos("Pilih ID Kategori", 31) << ": ";
        getline(cin, temp);
        if (!IsValidNumeric(temp))
        {
            cout << "Input harus angka atau angka tidak valid!";
            getline(cin, temp);
            return;
        }
        pilihan_kategori = stoi(temp) - 1;
        if (pilihan_kategori < 0 || pilihan_kategori >= data.sizeDataKategori)
        {
            cout << "Pilihan kategori tidak valid";
            getline(cin, temp);
            return;
        }

        int stok_diterima;
        cout << StringPos("Jumlah stok yang diterima", 31) << ": ";
        getline(cin, temp);
        if (!IsValidNumeric(temp))
        {
            cout << "Input harus angka atau angka tidak valid!";
            getline(cin, temp);
            return;
        }
        stok_diterima = stoi(temp);
        if (stok_diterima < 0)
        {
            cout << "Jumlah stok tidak boleh kurang dari 0!";
            getline(cin, temp);
            return;
        }
        Tanaman tanamanBaru;
        tanamanBaru.id = GetFreeTanamanId();
        tanamanBaru.supplier = suplaidipilih.supplier;
        tanamanBaru.harga = harga;
        tanamanBaru.namaTanaman = nama_tanaman;
        tanamanBaru.kategori = data.dataKategori[pilihan_kategori];

        ValidasiTanaman validasiBaru;
        validasiBaru.id = GetFreeValidasiId();
        validasiBaru.tanaman = tanamanBaru;
        validasiBaru.stokDiterima = stok_diterima;
        validasiBaru.suplai = suplaidipilih;

        cout << endl;
        cout << StringPos("Apakah data sudah benar? (y/n): ", 31);
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
        {
            TambahTanaman(data.dataTanaman, data.sizeDataTanaman, tanamanBaru);
            TambahValidasi(data.dataValidasiTanaman, data.sizeDataValidasi, validasiBaru);
            cout << endl;
            cout << "Suplai berhasil divalidasi!" << endl;
            cout << endl;
            cout << "Tekan [enter] untuk kembali ..." << endl;
            getline(cin, temp);
        }
        else if (konfirmasi == "n" || konfirmasi == "N")
        {
            cout << "Membatalkan validasi ...";
            getline(cin, temp);
            return;
        }
        else
        {
            cout << "Pilihan tidak valid ...";
            getline(cin, temp);
            return;
        }
    }
    else if (temp == "y" || temp == "Y")
    {
        cout << "Tanaman Supplier \"" << suplaidipilih.supplier.username << "\":" << endl;
        cout << StringPos("ID", 8)
             << StringPos("Tanaman", 28) << endl;
        for (int i = 0; i < data.sizeDataTanaman; i++)
        {
            if (suplaidipilih.supplier.id == data.dataTanaman[i].supplier.id)
            {
                cout << StringPos(data.dataSuplai[i].id, 5) << " > " << data.dataTanaman[i].namaTanaman << endl;
            }
        }

        cout << endl;
        cout << StringPos("Pilih ID Tanaman", 31) << ": ";
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
            cout << "ID Tanaman tidak ditemukan.";
            getline(cin, temp);
            return;
        }

        int stok_diterima;
        cout << StringPos("Jumlah stok yang diterima", 31) << ": ";
        getline(cin, temp);
        if (!IsValidNumeric(temp))
        {
            cout << "Input harus angka atau angka tidak valid!";
            getline(cin, temp);
            return;
        }
        stok_diterima = stoi(temp);
        if (stok_diterima < 0)
        {
            cout << "Jumlah stok tidak boleh kurang dari 0!";
            getline(cin, temp);
            return;
        }

        ValidasiTanaman validasiBaru;
        validasiBaru.id = GetFreeValidasiId();
        validasiBaru.tanaman = tanamandipilih;
        validasiBaru.stokDiterima = stok_diterima;
        validasiBaru.suplai = suplaidipilih;

        cout << endl;
        cout << StringPos("Apakah data sudah benar? (y/n): ", 31);
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
        {
            TambahValidasi(data.dataValidasiTanaman, data.sizeDataValidasi, validasiBaru);
            cout << endl;
            cout << "Suplai berhasil divalidasi!" << endl;
            cout << endl;
            cout << "Tekan [enter] untuk kembali ...";
            getline(cin, temp);
            return;
        }
        else if (konfirmasi == "n" || konfirmasi == "N")
        {
            cout << "Membatalkan validasi ...";
            getline(cin, temp);
            return;
        }
        else
        {
            cout << "Pilihan tidak valid ...";
            getline(cin, temp);
            return;
        }
    }
    else
    {
        cout << "Pilihan tidak valid!";
        getline(cin, temp);
        return;
    }
}

void MenuNotifikasi(DataUtama &data, InfoLogin &infoLogin)
{
    while (CekLogin(data, infoLogin))
    {
        data.flagRefreshTransaksi = true;
        RefreshDataUtama(data);
        string temp;

        ClearScreen();
        Title("Notifikasi");
        cout << StringPos("ID", 15, "Left");
        cout << StringPos("Tanaman", 30, "Left");
        cout << StringPos("Jumlah", 10, "Left");
        cout << endl;

        for (int i = 0; i < data.sizeDataTransaksi; i++)
        {
            if (data.dataTransaksi[i].status == "Menunggu Konfirmasi")
            {
                cout << StringPos(data.dataTransaksi[i].id, 15, "Left");
                cout << StringPos(data.dataTransaksi[i].tanaman.namaTanaman, 30, "Left");
                cout << StringPos(to_string(data.dataTransaksi[i].jumlahTanaman), 10, "Left") << endl;
            }
        }
        cout << endl;
        Transaksi *pilihanTransaksi = new Transaksi();
        cout << "Masukkan ID Transaksi yang ingin dikonfirmasi: ";
        getline(cin, temp);

        for (int i = 0; i < data.sizeDataTransaksi; i++)
        {
            if (data.dataTransaksi[i].id == temp)
            {
                pilihanTransaksi = &data.dataTransaksi[i];
                break;
            }
        }

        if (pilihanTransaksi->id.empty())
        {
            cout << "ID Transaksi tidak valid";
            getline(cin, temp);
            return;
        }

        ClearScreen();
        Title("Detail Transaksi");
        cout << pilihanTransaksi->id << endl;
        cout << pilihanTransaksi->tanaman.namaTanaman << endl;
        cout << pilihanTransaksi->pembeli.username << endl;
        cout << pilihanTransaksi->jumlahTanaman << endl;
        cout << pilihanTransaksi->tanggalTransaksi << endl;
        cout << pilihanTransaksi->totalHarga << endl;
        Border();
        cout << "Apakah Anda ingin mengkonfirmasi transaksi ini? (y/n): ";
        getline(cin, temp);
        if (temp == "y" || temp == "Y")
        {
            data.flagRefreshTransaksi = true;
            pilihanTransaksi->status = "Selesai";
            UpdateDataUtama(data);
            cout << "Transaksi berhasil dikonfirmasi!" << endl;
            cout << endl;
            cout << "Tekan [enter] untuk kembali ...";
            getline(cin, temp);
            return;
        }
        else if (temp == "n" || temp == "N")
        {
            return;
        }
        else
        {
            cout << "Pilihan tidak valid!";
            getline(cin, temp);
            return;
        }
    }
}
void FormLihatSupplier(DataUtama &data)
{
    data.flagRefreshSupplier = true;
    RefreshDataUtama(data);

    string temp;

    ClearScreen();
    Title("Lihat Supplier");
    cout << StringPos("ID", 5, "Left");
    cout << StringPos("Username", 20, "Left");
    cout << StringPos("Status", 10, "Left");
    cout << endl;

    for (int i = 0; i < data.sizeDataSupplier; i++)
    {
        cout << StringPos(data.dataSupplier[i].id, 5, "Left");
        cout << StringPos(data.dataSupplier[i].username, 20, "Left");
        cout << StringPos(data.dataSupplier[i].status, 10, "Left") << endl;
    }
    cout << endl;
    cout << "Tekan [enter] untuk kembali ..." << endl;
    getline(cin, temp);
    return;
}

void FormHapusSupplier(DataUtama &data)
{
    string temp;
    ClearScreen();
    Title("Lihat Supplier");
    cout << StringPos("ID", 5, "Left");
    cout << StringPos("Username", 20, "Left");
    cout << StringPos("Status", 10, "Left");
    cout << endl;

    for (int i = 0; i < data.sizeDataSupplier; i++)
    {
        cout << StringPos(data.dataSupplier[i].id, 5, "Left");
        cout << StringPos(data.dataSupplier[i].username, 20, "Left");
        cout << StringPos(data.dataSupplier[i].status, 10, "Left") << endl;
    }
    cout << endl;

    Title("Hapus Supplier");
    cout << "Masukkan ID: ";
    string id;
    getline(cin, id);
    Supplier supplierDipilih;

    for (int i = 0; i < data.sizeDataSupplier; i++)
    {
        if (data.dataSupplier[i].id == id)
        {
            supplierDipilih = data.dataSupplier[i];
            break;
        }
    }
    if (!supplierDipilih.id.empty())
    {
        cout << "Anda yakin ingin menghapus supplier " << supplierDipilih.username << "? [y/n]: ";
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi != "y" && konfirmasi != "Y")
        {
            cout << "Pembatalan penghapusan supplier.";
            getline(cin, temp);
            return;
        }
        else
        {
            HapusSupplier(data.dataSupplier, data.sizeDataSupplier, supplierDipilih);
            cout << "Supplier berhasil dihapus!" << endl;
            cout << endl;
            cout << "Tekan [enter] untuk kembali ...";
            getline(cin, temp);
            return;
        }
    }
    else
    {
        cout << "ID Supplier tidak ditemukan!";
        getline(cin, temp);
        return;
    }
}

void FormBlokirSupplier(DataUtama &data)
{
    data.flagRefreshSupplier = true;
    RefreshDataUtama(data);

    string temp;
    ClearScreen();
    Title("Lihat Supplier");
    cout << StringPos("ID", 5, "Left");
    cout << StringPos("Username", 20, "Left");
    cout << StringPos("Status", 10, "Left");
    cout << endl;

    for (int i = 0; i < data.sizeDataSupplier; i++)
    {
        cout << StringPos(data.dataSupplier[i].id, 5, "Left");
        cout << StringPos(data.dataSupplier[i].username, 20, "Left");
        cout << StringPos(data.dataSupplier[i].status, 10, "Left") << endl;
    }
    cout << endl;
    Title("Blokir atau Unblokir Supplier");
    cout << "Masukkan ID Supplier yang ingin diblokir atau unblokir:";
    cout << endl;
    string id;
    getline(cin, id);
    Supplier *supplierDipilih = new Supplier();

    for (int i = 0; i < data.sizeDataSupplier; i++)
    {
        if (data.dataSupplier[i].id == id)
        {
            supplierDipilih = &data.dataSupplier[i];
            break;
        }
    }

    if (supplierDipilih->id.empty())
    {
        cout << "ID Supplier tidak valid";
        getline(cin, temp);
        return;
    }

    if (supplierDipilih->status == "aktif")
    {
        cout << "Apakah Anda yakin ingin memblokir akun supplier " << supplierDipilih->username << "?  [y/n]: ";
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
        {
            supplierDipilih->status = "blokir";
            cout << "Supplier berhasil diblokir!" << endl;
            cout << endl;
            UpdateDataUtama(data);
            cout << "Tekan [enter] untuk kembali ..." << endl;
            getline(cin, temp);
            return;
        }
        else
        {
            cout << "Pembatalan blokir akun supplier!";
            getline(cin, temp);
            return;
        }
    }
    else if (supplierDipilih->status == "blokir")
    {
        cout << "Apakah Anda yakin ingin mengaktifkan akun supplier " << supplierDipilih->username << "?  [y/n]: ";
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
        {
            supplierDipilih->status = "aktif";
            cout << "Supplier berhasil diaktifkan!" << endl;
            cout << endl;
            UpdateDataUtama(data);
            cout << "Tekan [enter] untuk kembali ...";
            getline(cin, temp);
            return;
        }
        else
        {
            cout << "Pembatalan aktifasi akun supplier!";
            getline(cin, temp);
            return;
        }
    }
    else
    {
        cout << "Status supplier tidak valid!";
        getline(cin, temp);
        return;
    }
}

void MenuManajemenTanaman(DataUtama &data, InfoLogin &infoLogin)
{
    while (CekLogin(data, infoLogin))
    {
        data.flagRefreshTanaman = true;
        RefreshDataUtama(data);

        string temp;

        ClearScreen();
        Title("Manajemen Tanaman");
        cout << endl;
        cout << "Pilihan Menu yang Tersedia: " << endl;
        cout << endl;
        cout << "1. Manajemen Kategori" << endl;
        cout << "2. Validasi Status " << endl;
        cout << "3. Kembali ke Menu Utama" << endl;
        cout << endl;
        cout << "Pilih menu: ";

        string pilihan;
        getline(cin, pilihan);

        if (pilihan == "1")
        {
            MenuManajemenKategori(data, infoLogin);
        }
        else if (pilihan == "2")
        {
            FormKesiapanTanaman(data);
        }
        else if (pilihan == "3")
        {
            return;
        }
        else
        {
            cout << "Pilihan tidak valid!" << endl;
            getline(cin, temp);
        }
    }
}

void MenuManajemenSupplier(DataUtama &data, InfoLogin &infoLogin)
{
    while (CekLogin(data, infoLogin))
    {
        data.flagRefreshSupplier = true;
        RefreshDataUtama(data);
        ClearScreen();

        string temp;

        Title("Manajemen Supplier");
        cout << endl;
        cout << "Pilihan Menu yang Tersedia: " << endl;
        cout << endl;
        cout << "1. Lihat Supplier" << endl;
        cout << "2. Hapus Supplier" << endl;
        cout << "3. Blokir atau unblokir Supplier" << endl;
        cout << "4. Kembali ke Menu Utama" << endl;
        cout << endl;
        cout << "Pilih menu: ";

        string pilihan;
        getline(cin, pilihan);

        if (pilihan == "1")
        {
            FormLihatSupplier(data);
        }
        else if (pilihan == "2")
        {
            FormHapusSupplier(data);
        }
        else if (pilihan == "3")
        {
            FormBlokirSupplier(data);
        }
        else if (pilihan == "4")
        {
            return;
        }
        else
        {
            cout << "Pilihan tidak valid!" << endl;
            getline(cin, temp);
        }
    }
}

void DashboardAdmin(DataUtama data)
{
    Supplier *dataSupplierTerlaris = new Supplier[MAX_SIZE];
    int *sizeDataSupplierTerlaris = new int{0};
    int *dataStokTerjualSupplierAktif = new int[GetJumlahSupplierAktif(data)];
    string *_temp = new string();

    try
    {
        data.flagRefreshTransaksi = true;
        data.flagRefreshTanaman = true;
        data.flagRefreshSupplier = true;

        RefreshDataUtama(data);

        ClearScreen();
        Title("Dashboard");
        cout << StringPos("Supplier Terdaftar", 26) << ": " << GetJumlahSupplierAktif(data) << " Supplier" << endl;
        cout << StringPos("Penjualan Bulan Ini", 26) << ": Rp" << GetPenjualanBulanIniAdmin(data) << endl;
        cout << StringPos("Jumlah Jenis Tanaman", 26) << ": " << data.sizeDataTanaman << " Tanaman" << endl;
        cout << StringPos("Transaksi Bulan Ini", 26) << ": " << GetTransaksiBulanIniAdmin(data) << " Transaksi" << endl;
        Border();

        GetDataSupplierTerlaris(data, dataSupplierTerlaris, (*sizeDataSupplierTerlaris), dataStokTerjualSupplierAktif);
        cout << "Supplier Terlaris Bulan Ini" << endl;
        if ((*sizeDataSupplierTerlaris) > 0)
        {
            for (int i = 0; i < (*sizeDataSupplierTerlaris); i++)
            {
                cout << i + 1 << ". " << StringPos(dataSupplierTerlaris[i].username, 23) << ": " << dataStokTerjualSupplierAktif[i] << " Stok Tanaman Terjual" << endl;
            }
        }
        else
        {
            cout << "Tidak ada data" << endl;
        }
        Border();

        cout << "Tekan [Enter] untuk kembali...";
        getline(cin, (*_temp));
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    delete[] dataSupplierTerlaris;
    delete sizeDataSupplierTerlaris;
    delete[] dataStokTerjualSupplierAktif;
    delete _temp;
    dataSupplierTerlaris = nullptr;
    sizeDataSupplierTerlaris = nullptr;
    dataStokTerjualSupplierAktif = nullptr;
    _temp = nullptr;
}

void MenuUtamaAdmin(DataUtama &data, InfoLogin &infoLogin, DataMenu &dataMenu)
{
    try
    {
        while (CekLogin(data, infoLogin))
        {
            RefreshDataUtama(data);

            ClearScreen();
            Title("Menu Utama Admin");
            cout << "Selamat datang, " << infoLogin.username << "!" << endl;
            cout << endl;
            cout << "Menu yang tersedia:" << endl;
            cout << endl;
            cout << "1. Dashboard" << endl;
            cout << "2. Manajemen Tanaman" << endl;
            cout << "3. Manajemen Supplier" << endl;
            cout << "4. Notifikasi Transaksi" << endl;
            cout << "5. Logout" << endl;
            cout << endl;
            cout << "Pilih menu: ";

            string pilihan;
            getline(cin, pilihan);

            if (pilihan == "1")
            {
                DashboardAdmin(data);
            }
            else if (pilihan == "2")
            {
                MenuManajemenTanaman(data, infoLogin);
            }
            else if (pilihan == "3")
            {
                MenuManajemenSupplier(data, infoLogin);
            }
            else if (pilihan == "4")
            {
                MenuNotifikasi(data, infoLogin);
            }
            else if (pilihan == "5")
            {
                cout << "Anda telah logout!" << endl;
                Logout(infoLogin);
                break;
            }
            else
            {
                cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
            }
        }
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