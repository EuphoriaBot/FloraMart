#ifndef MENU_ADMIN_H
#define MENU_ADMIN_H

#include "menu_utilities.h"

void FormTambahKategori(DataUtama &data)
{
    ClearScreen();
    RefreshDataUtama(data);
    cout << "ID Kategori\tNama Kategori\tMin Suhu\tMax Suhu\tMedia Tanam" << endl;
    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        cout << data.dataKategori[i].id << "\t\t";
        cout << data.dataKategori[i].namaKategori << "\t\t";
        cout << data.dataKategori[i].minSuhu << "\t\t";
        cout << data.dataKategori[i].maxSuhu << "\t\t";
        cout << data.dataKategori[i].mediaTanam << endl;
    } 
    cout << endl;

    string temp;
    cout << "=== Tambah Kategori ===" << endl;
    cout << "Nama Kategori: ";
    string nama_kategori;
    getline(cin, nama_kategori);
    
    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        if (data.dataKategori[i].namaKategori == nama_kategori)
        {
            cout << "Nama Kategori sudah ada!" << endl;
            return;
        }
        else if (IsValidString(nama_kategori) == false)
        {
            cout << "Nama Kategori harus berupa string alfabet!" << endl;
            return;
        }
    }

    cout << "Min Suhu: ";
    float min_suhu; 
    getline(cin, temp);
    min_suhu = stof(temp); // Convert string to float
    cout << "Max Suhu: ";
    getline(cin, temp);
    float max_suhu;
    max_suhu = stof(temp); 
    
    if (min_suhu > max_suhu){
        cout << "Maksimum Suhu tidak boleh kurang dari Minimum Suhu!" << endl;
        return;
    }
    else{
        cout << "Media Tanam: ";
        string media_tanam;
        getline(cin, media_tanam);
        if (IsValidString(media_tanam) == false)
        {
            cout << "Media Tanam harus berupa string alfabet!" << endl;
            return;
        }
        cout << "Apakah anda yakin ingin menambahkan kategori " << nama_kategori << "? [y/n]" << endl;
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
        {
            Kategori kategoriBaru = {GetFreeKategoriId(), nama_kategori, min_suhu, max_suhu, media_tanam};
            TambahKategori(data.dataKategori, data.sizeDataKategori, kategoriBaru);
            cout << endl;
            cout << "Kategori berhasil ditambahkan!" << endl;
        }
        else
        {
            return;
        }
    }
}

void FormHapusKategori(DataUtama &data)
{
    ClearScreen();
    RefreshDataUtama(data);
    cout << "ID Kategori\tNama Kategori\tMin Suhu\tMax Suhu\tMedia Tanam" << endl;
    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        cout << data.dataKategori[i].id << "\t\t";
        cout << data.dataKategori[i].namaKategori << "\t\t";
        cout << data.dataKategori[i].minSuhu << "\t\t";
        cout << data.dataKategori[i].maxSuhu << "\t\t";
        cout << data.dataKategori[i].mediaTanam << endl;
    } 
    cout << endl;

    string temp;
    cout << "=== Hapus Kategori ===" << endl;
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
        cout << "Anda yakin ingin menghapus kategori " << kategoriDihapus.namaKategori << "? [y/n]" << endl;
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
        {
            HapusKategori(data.dataKategori, data.sizeDataKategori, kategoriDihapus);
            cout << endl;
            cout << "Kategori berhasil dihapus!" << endl;
            return;
        }
        else 
        {
            return;
        }
       
    }
    else 
    {
        cout << "ID Kategori tidak ditemukan!" << endl;
        return;
    }
}

void FormEditKategori(DataUtama &data)
{
    RefreshDataUtama(data);
    ClearScreen();
    
    cout << "ID Kategori\tNama Kategori\tMin Suhu\tMax Suhu\tMedia Tanam" << endl;
    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        cout << data.dataKategori[i].id << "\t\t";
        cout << data.dataKategori[i].namaKategori << "\t\t";
        cout << data.dataKategori[i].minSuhu << "\t\t";
        cout << data.dataKategori[i].maxSuhu << "\t\t";
        cout << data.dataKategori[i].mediaTanam << endl;
    } 
    cout << endl;

    string temp;
    cout << "=== Edit Kategori ===" << endl;
    cout << "Masukan Id yang ingin diedit: ";
    getline(cin, temp); // Convert string to int
    Kategori *kategoriDiedit;

    for (int i = 0; i < data.sizeDataKategori; i++){
        if (data.dataKategori[i].id == temp)
        {
            kategoriDiedit = &data.dataKategori[i];
            break;
        }
    }
    if (kategoriDiedit->id.empty())
    {
        cout << "ID Kategori tidak ditemukan!" << endl;
        return;
    }

    cout << "Nama Kategori: ";
    getline(cin, temp);
    if (!temp.empty())
    {
        kategoriDiedit->namaKategori = temp;
    }

    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        if (IsValidString(kategoriDiedit->namaKategori) == false)
        {
            cout << "Nama Kategori harus berupa string alfabet!" << endl;
            return;
        }
    }
    cout << "Min Suhu: ";
    getline(cin, temp);
    if (!temp.empty())
    {
        kategoriDiedit->minSuhu = stof(temp);
    }

    cout << "Max Suhu: ";
    getline(cin, temp);
    if (!temp.empty())
    {
        kategoriDiedit->maxSuhu = stof(temp);
        ;
    }
   
    if (kategoriDiedit->maxSuhu < kategoriDiedit->minSuhu)
    {
        cout << "Maksimum Suhu tidak boleh kurang dari Minimum Suhu!" << endl;
        return;
    }
    else{
        cout << "Media Tanam: ";
        getline(cin, temp);
        if (!temp.empty())
        {
            kategoriDiedit->mediaTanam = temp;
        }
        else if (IsValidString(kategoriDiedit->mediaTanam) == false)
        {
            cout << "Media Tanam harus berupa string alfabet!" << endl;
            return;
        }
        cout << "Apakah anda yakin ingin mengedit kategori " << kategoriDiedit->namaKategori << "? [y/n]" << endl;
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
        {
            UpdateDataUtama(data);
            cout << endl;
            cout << "Kategori berhasil diedit!" << endl;
        }
        else
        {
            return;
        }
    }
}

void FormLihatKategori(DataUtama &data)
{
    ClearScreen();
    RefreshDataUtama(data);
    Border();
    cout << "\t\t\t\t Lihat Kategori" << endl;
    Border();
    cout << "ID Kategori\tNama Kategori\tMin Suhu\tMax Suhu\tMedia Tanam" << endl;
    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        cout << data.dataKategori[i].id << "\t\t";
        cout << data.dataKategori[i].namaKategori << "\t\t";
        cout << data.dataKategori[i].minSuhu << "\t\t";
        cout << data.dataKategori[i].maxSuhu << "\t\t";
        cout << data.dataKategori[i].mediaTanam << endl;
    } 
    cout << endl;
    cout << "Tekan [enter] untuk kembali ..." <<endl;
    getline (cin, data.dataKategori[0].id); // To pause the screen
}

void FormSortingKategori(DataUtama &data)
{
    ClearScreen();
    RefreshDataUtama(data);
    cout << "=== Sorting Kategori Berdasarkan Nama Secara Ascending ===" << endl;
    for (int i = 0; i < data.sizeDataKategori; i++)
    {
        cout << data.dataKategori[i].namaKategori << endl;
    }
    cout << endl;
    cout << "Apakah Anda yakin ingin mengurutkan kategori berdasarkan nama secara ascending? [y/n]" << endl;
    string konfirmasi;
    getline(cin, konfirmasi);
    cout << endl;
    if (konfirmasi == "y" || konfirmasi == "Y")
    {
        for (int i = 0; i < data.sizeDataKategori - 1; i++) {
            for (int j = 0; j < data.sizeDataKategori - i - 1; j++) {
                if (data.dataKategori[j].namaKategori > data.dataKategori[j + 1].namaKategori) {
                    Kategori temp = data.dataKategori[j];
                    data.dataKategori[j] = data.dataKategori[j + 1];
                    data.dataKategori[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < data.sizeDataKategori; i++) {
            cout << data.dataKategori[i].namaKategori << endl;
        }
        cout << "Kategori berhasil diurutkan!" << endl;
        cout << endl;
        cout << "Tekan [enter] untuk kembali ..." << endl;
        getline(cin, data.dataKategori[0].id); // To pause the screen
    }
    else
    {
        return;
    }
}

void MenuManajemenKategori(DataUtama &data , InfoLogin &infoLogin)
{
    while (CekLogin(infoLogin)){
    RefreshDataUtama(data);
    ClearScreen();
    Border();
    cout << "\t\t\t\t Manajemen Kategori" << endl;
    Border();
    cout << "1. Lihat Kategori" << endl;
    cout << "2. Tambah Kategori" << endl;
    cout << "3. Edit Kategori" << endl;
    cout << "4. Hapus Kategori" << endl;
    cout << "5. Sorting Kategori Berdasarkan Nama Secara Ascending" << endl;
    cout << "6. Kembali ke Menu Utama" << endl;
    cout << endl;
    cout << "Pilih menu: ";

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
    }
    }
}

void FormKesiapanTanaman(DataUtama &data)
{
    RefreshDataUtama(data);
    ClearScreen();
    Suplai suplaidipilih;
    Tanaman tanamandipilih;
    Border();
    cout << "\t\t\t\t Kesiapan Tanaman" << endl;
    Border();
    for (int i = 0; i < data.sizeDataSuplai; i++)
    {
        if (data.dataSuplai[i].statusValidasi == false)
        {
            cout << data.dataSuplai[i].id << " | " << data.dataSuplai[i].namaTanaman << " | " << data.dataSuplai[i].jumlah << endl;
            ;
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
            cout << "Nama tanaman tidak boleh kosong" << endl;
            return;
        }
        else if (IsValidString(nama_tanaman) == false)
        {
            cout << "Nama tanaman harus berupa string alfabet!" << endl;
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
        tanamanBaru.supplier = suplaidipilih.supplier;
        tanamanBaru.harga = harga;
        tanamanBaru.namaTanaman = nama_tanaman;
        tanamanBaru.kategori = data.dataKategori[pilihan_kategori];

        ValidasiTanaman validasiBaru;
        validasiBaru.id = GetFreeValidasiId();
        validasiBaru.tanaman = tanamanBaru;
        validasiBaru.stokDiterima = stok_diterima;
        validasiBaru.suplai = suplaidipilih;

        cout << "Apakah anda yakin ingin menambahkan tanaman " << tanamanBaru.namaTanaman << "? [y/n]" << endl;
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
        {
            TambahTanaman(data.dataTanaman, data.sizeDataTanaman, tanamanBaru);
            TambahValidasi(data.dataValidasiTanaman, data.sizeDataValidasi, validasiBaru);
            cout << endl;
            cout << "Suplai berhasil divalidasi!" << endl;
        }
        else
        {
            return;
        }
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
        validasiBaru.stokDiterima = stok_diterima;
        validasiBaru.suplai = suplaidipilih;

        cout << "Apakah anda yakin ingin menambahkan tanaman " << tanamandipilih.namaTanaman << "? [y/n]" << endl;
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
        {
            TambahValidasi(data.dataValidasiTanaman, data.sizeDataValidasi, validasiBaru);
            return;
        }
        else
        {
            return;
        }
    }
}

void MenuNotifikasi(DataUtama &data, InfoLogin &infoLogin)
{
    while (CekLogin(infoLogin)){
    string temp;
    RefreshDataUtama(data);
    for (int i = 0; i < data.sizeDataTransaksi; i++)
    {
        if (data.dataTransaksi[i].status == "Menunggu Konfirmasi")
        {
            cout << data.dataTransaksi[i].id << " | " << data.dataTransaksi[i].tanaman.namaTanaman << " | " << data.dataTransaksi[i].jumlahTanaman << endl;
        }
    }
    Transaksi *pilihanTransaksi;
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
    if (!pilihanTransaksi->id.empty())
    {
        cout << "=== Detail Transaksi ===" << endl;
        cout << pilihanTransaksi->id << endl;
        cout << pilihanTransaksi->tanaman.namaTanaman << endl;
        cout << pilihanTransaksi->pembeli.username << endl;
        cout << pilihanTransaksi->jumlahTanaman << endl;
        cout << pilihanTransaksi->tanggalTransaksi << endl;
        cout << pilihanTransaksi->totalHarga << endl;
    }
    cout << "Apakah Anda ingin mengkonfirmasi transaksi ini? (y/n): ";
    getline(cin, temp);
    if (temp == "y" || temp == "Y")
    {
        pilihanTransaksi->status = "Selesai";
        cout << "Transaksi berhasil dikonfirmasi!" << endl;
        UpdateDataUtama(data);
    }
    else if (temp == "n" || temp == "N")
    {
        return;
    }
    else
    {
        cout << "Pilihan tidak valid!" << endl;
        return;
    }
}

}
void FormLihatSupplier(DataUtama &data)
{
    RefreshDataUtama(data);
    cout << "=== Lihat Supplier ===" << endl;
    cout << "ID Supplier\tUsername\tStatus" << endl;
    for (int i = 0; i < data.sizeDataSupplier; i++)
    {
        cout << data.dataSupplier[i].id << "\t\t";
        cout << data.dataSupplier[i].username << "\t\t";
        cout << data.dataSupplier[i].status << endl;
    }
}

void FormHapusSupplier(DataUtama &data)
{
    RefreshDataUtama(data);
    ClearScreen();

    cout << "ID Supplier\tUsername\tStatus" << endl;
    for (int i = 0; i < data.sizeDataSupplier; i++)
    {
        cout << data.dataSupplier[i].id << "\t\t";
        cout << data.dataSupplier[i].username << "\t\t";
        cout << data.dataSupplier[i].status << endl;
    }
    cout << endl;

    cout << "=== Hapus Supplier ===" << endl;
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
        cout << "Anda yakin ingin menghapus supplier " << supplierDipilih.username << "? [y/n]" << endl;
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi != "y" && konfirmasi != "Y")
        {
            cout << "Pembatalan penghapusan supplier." << endl;
            return;
        } 
        else
        {
            HapusSupplier(data.dataSupplier, data.sizeDataSupplier, supplierDipilih);
            cout << "Supplier berhasil dihapus!" << endl;
        }
    }
    else
    {
        cout << "ID Supplier tidak ditemukan!" << endl;
        return;
    }
   
}

void FormBlokirSupplier(DataUtama &data)
{
    RefreshDataUtama(data);
    ClearScreen();
    
    cout << "ID Supplier\tUsername\tStatus" << endl;
    for (int i = 0; i < data.sizeDataSupplier; i++)
    {
        cout << data.dataSupplier[i].id << "\t\t";
        cout << data.dataSupplier[i].username << "\t\t";
        cout << data.dataSupplier[i].status << endl;
    }
    cout << endl;

    cout << "=== Blokir Supplier ===" << endl;

    for (int i = 0; i < data.sizeDataSupplier; i++)
    {
        cout << data.dataSupplier[i].id << " | " << data.dataSupplier[i].username << " | " << data.dataSupplier[i].status << endl;
    }
    cout << "Masukkan ID Supplier yang ingin diblokir atau unblokir: ";
    string id;
    getline(cin, id);
    Supplier *supplierDipilih;

    for (int i = 0; i < data.sizeDataSupplier; i++)
    {
        if (data.dataSupplier[i].id == id)
        {
            supplierDipilih = &data.dataSupplier[i];
            break;
        }
    }
    if (supplierDipilih->status == "aktif")
    {
        cout << "Apakah Anda yakin ingin memblokir akun supplier " << supplierDipilih->username << "?  [y/n]" << endl;
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
        {
            supplierDipilih->status = "blokir";
            cout << "Supplier berhasil diblokir!" << endl;
        }
        else
        {
            cout << "Pembatalan blokir akun supplier." << endl;
            return;
        }
    }
    else if (supplierDipilih->status == "blokir")
    {
        cout << "Apakah Anda yakin ingin mengaktifkan akun supplier " << supplierDipilih->username << "?  [y/n]" << endl;
        string konfirmasi;
        getline(cin, konfirmasi);
        if (konfirmasi == "y" || konfirmasi == "Y")
        {
            supplierDipilih->status = "aktif";
            cout << "Supplier berhasil diaktifkan!" << endl;
        }
        else
        {
            cout << "Pembatalan aktifasi akun supplier." << endl;
            return;
        }
    }
    else
    {
        cout << "Status supplier tidak valid!" << endl;
        return;
    }
    UpdateDataUtama(data);
}

void MenuManajemenTanaman(DataUtama &data, InfoLogin &infoLogin)
{
    while (CekLogin(infoLogin)){
    RefreshDataUtama(data);
    ClearScreen();
    Border();
    cout << "\t\t\t\t Manajemen Tanaman " << endl;
    Border();
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
    }
}
    }

void MenuManajemenSupplier(DataUtama &data, InfoLogin &infoLogin)
{
    while (CekLogin(infoLogin)){
    RefreshDataUtama(data);
    ClearScreen();
    Border();
    cout << "\t\t\t\t Manajemen Supplier" << endl;
    Border();
    cout << "1. Lihat Supplier" << endl;
    cout << "2. Hapus Supplier" << endl;
    cout << "3. Blokir Supplier" << endl;
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
        ClearScreen();
        Title("Dashboard");
        cout << "Supplier Terdaftar\t: " << GetJumlahSupplierAktif(data) << " Supplier" << endl;
        cout << "Penjualan Bulan Ini\t: Rp" << GetPenjualanBulanIniAdmin(data) << endl;
        cout << "Jumlah Jenis Tanaman\t: " << data.sizeDataTanaman << " Tanaman" << endl;
        cout << "Transaksi Bulan Ini\t: " << GetTransaksiBulanIniAdmin(data) << " Transaksi" << endl;
        Border();
        
        GetDataSupplierTerlaris(data, dataSupplierTerlaris, (*sizeDataSupplierTerlaris), dataStokTerjualSupplierAktif);
        cout << "Supplier Terlaris Bulan Ini" << endl;
        if ((*sizeDataSupplierTerlaris) > 0)
        {
            for (int i = 0; i < (*sizeDataSupplierTerlaris); i++)
            {
                cout << i + 1 << ". " << dataSupplierTerlaris[i].username << "\t: " << dataStokTerjualSupplierAktif[i] << " Stok Tanaman Terjual" << endl;
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
    catch(exception& e)
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
        RefreshDataUtama(data);
        while (CekLogin(infoLogin))
        {
            ClearScreen();
            Border();
            cout << "\t\t\t\t Menu Utama Admin" << endl;
            Border();
            cout << "Selamat datang, " << infoLogin.username << "!" << endl;
            cout << endl;
            cout << "Menu yang tersedia:" << endl;
            cout << endl;
            cout << "1. Dashboard" << endl;
            cout << "2. Manajemen Tanaman" << endl;
            cout << "3. Manajemen Supplier" << endl;
            cout << "4. Notifikasi" << endl;
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
                Logout (infoLogin);
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