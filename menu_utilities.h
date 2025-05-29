#ifndef UTILITIES_H
#define UTILITIES_H

// Data Utilities
#include "data/data_admin/data_admin.h"
#include "data/data_kategori/data_kategori.h"
#include "data/data_metode_transaksi/data_metode_transaksi.h"
#include "data/data_pembeli/data_pembeli.h"
#include "data/data_suplai/data_suplai.h"
#include "data/data_supplier/data_supplier.h"
#include "data/data_tanaman/data_tanaman.h"
#include "data/data_transaksi/data_transaksi.h"
#include "data/data_validasi_tanaman/data_validasi_tanaman.h"

// Struct Data Utama
#include "data/data_utilities.h"

#include <ctime>
#include <cctype>
#include <iomanip>

struct InfoLogin
{
    string id;
    string username;
    string role;
};

struct DataMenu
{
    string pilihan = "";
    bool keluar = false;
};

void RefreshDataUtama(DataUtama &data)
{
    GetAllPembeli(data.dataPembeli, data.sizeDataPembeli);
    GetAllSupplier(data.dataSupplier, data.sizeDataSupplier);
    GetAllAdmin(data.dataAdmin, data.sizeDataAdmin);
    GetAllTanaman(data.dataTanaman, data.sizeDataTanaman);
    GetAllKategori(data.dataKategori, data.sizeDataKategori);
    GetAllMetodeTransaksi(data.dataMetodeTransaksi, data.sizeDataMetodeTransaksi);
    GetAllSuplai(data.dataSuplai, data.sizeDataSuplai);
    GetAllTransaksi(data.dataTransaksi, data.sizeDataTransaksi);
    GetAllValidasiTanaman(data.dataValidasiTanaman, data.sizeDataValidasi);
}

void UpdateDataUtama(DataUtama &data)
{
    SimpanPembeli(data.dataPembeli, data.sizeDataPembeli);
    SimpanSupplier(data.dataSupplier, data.sizeDataSupplier);
    SimpanAdmin(data.dataAdmin, data.sizeDataAdmin);
    SimpanTanaman(data.dataTanaman, data.sizeDataTanaman);
    SimpanKategori(data.dataKategori, data.sizeDataKategori);
    SimpanMetodeTransaksi(data.dataMetodeTransaksi, data.sizeDataMetodeTransaksi);
    SimpanSuplai(data.dataSuplai, data.sizeDataSuplai);
    SimpanTransaksi(data.dataTransaksi, data.sizeDataTransaksi);
    SimpanValidasiTanaman(data.dataValidasiTanaman, data.sizeDataValidasi);
}

void Logout(InfoLogin &infoLogin)
{
    infoLogin.id = "";
    infoLogin.username = "";
    infoLogin.role = "";
}

bool CekLogin(InfoLogin infoLogin)
{
    return infoLogin.id != "" && infoLogin.username != "" && infoLogin.role != "";
}

void ClearScreen()
{
    system("powershell.exe -Command Clear-Host");
}

string StringPos(string text, int length, string pos = "L")
{
    stringstream streamText;

    if (text.length() < length)
    {
        if (pos == "C" || pos == "Center")
        {
            int spaceLength = (length / 2) - (text.length() / 2);

            for (int i = 0; i < spaceLength; i++)
                streamText << " ";
            
            streamText << text;
        }
        else if (pos == "R" || pos == "Right")
        {
            streamText << right << setw(length) << text;
        }
        else
        {
            streamText << left << setw(length) << text;
        }
    }
    else if (length > 0)
    {
        for (int i = 0; i < length - 1; i++)
        {
            if (i < length - 4)
                streamText << text[i];
            else
                streamText << ".";
        }
    }
    else
    {
         return text;
    }
    return streamText.str();
}

void Border(string lineType = "-", int length = 80)
{
    for (int i = 0; i < length; i++)
    {
        cout << lineType;
    }
    cout << endl;
}

void Title(string titleText, string lineType = "=", int length = 80)
{
    Border(lineType, length);
    int spaceLength = (length / 2) - (titleText.length() / 2);

    for (int i = 0; i < spaceLength; i++)
        cout << ' ';

    cout << titleText << endl;
    Border(lineType, length);
}

// void TableHead(string itemHead[], int lenHeads[])
// {
//     if (sizeof(itemHead) / sizeof(string) != sizeof(lenHeads) / sizeof(int))
//     {
//         cout << "Elemen judul dengan panjang tidak sama";
//     }

//     cout <<

// }

void FixString(string &str)
{
    stringstream *stream = new stringstream();
    try
    {
        for (int i = 0; i < str.length(); i++)
        {
            if (!isspace(str[i]))
            {
                // Menambah Karakter Terlihat
                (*stream) << str[i];
            }
            else if (isspace(str[i]) && !((*stream).str().empty()))
            {
                // Menambah Spasi
                if (i + 1 < str.length())
                {
                    if (!isspace(str[i + 1]) && !isspace((*stream).str()[(*stream).str().length() - 1]))
                    {
                        (*stream) << str[i];
                    }
                }
            }
        }
        str = (*stream).str();
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    delete stream;
    stream = nullptr;
}

bool IsValidString(string &str)
{
    string *fixedStr = new string();
    try
    {
        *fixedStr = str;
        FixString((*fixedStr));
        if ((*fixedStr).length() <= 0)
            return false;

        for (int i = 0; i < (*fixedStr).length(); i++)
        {
            if (!(isprint((*fixedStr)[i]) && (isalpha((*fixedStr)[i]) || isspace((*fixedStr)[i]))))
            {
                return false;
            }
        }
        return true;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    delete fixedStr;
    fixedStr = nullptr;

    return false;
}

int JumlahJenisTanamanSupplier(DataUtama &data, string &idSupplier)
{
    int jumlahJenis = 0;
    for (int i = 0; i < data.sizeDataTanaman; i++)
    {
        if (data.dataTanaman[i].supplier.id == idSupplier)
            jumlahJenis += 1;
    }

    return jumlahJenis;
}

int StokTerjualSupplier(DataUtama &data, string &idSupplier)
{
    int stokTerjual = 0;
    for (int i = 0; i < data.sizeDataTransaksi; i++)
    {
        if (data.dataTransaksi[i].tanaman.supplier.id == idSupplier)
            stokTerjual += data.dataTransaksi[i].jumlahTanaman;
    }

    return stokTerjual;
}

void ParseTime(tm &time, stringstream &timestr)
{
    timestr >> get_time(&time, "%d-%m-%y %H:%M");
}

int CompareTimeRangeByMonth(tm &dateTimeToCompare, int month)
{
    time_t *curTimestamp = new time_t(time(NULL));
    tm *curDatetime = (*localtime)(&(*curTimestamp));

    try
    {

        int &currentMonth = curDatetime->tm_mon;
        int &currentYear = curDatetime->tm_year;

        currentMonth -= month;
        while (currentMonth < 0)
        {
            currentMonth += 12;
            currentYear -= 1;
        }

        curDatetime->tm_hour = 0;
        curDatetime->tm_min = 0;
        curDatetime->tm_sec = 0;
        curDatetime->tm_isdst = -1;
        curDatetime->tm_mday = 1;

        auto diffs = _difftime64(mktime(&dateTimeToCompare), mktime(curDatetime));

        if (diffs > 0)
            return 1;
        else if (diffs < 0)
            return -1;
        else
            return 0;
    }
    catch (exception &e)
    {
        cout << e.what() << '\n';
    }
    delete curTimestamp;
    delete curDatetime;
    curTimestamp = nullptr;
    curDatetime = nullptr;

    return 0;
}

int GetPemasukanBulanIniSupplier(DataUtama &data, string &idSupplier)
{
    int *pemasukanBulanIni = new int{0};
    stringstream *timestr = new stringstream();
    tm *timeTransaksi = new tm();
    try
    {
        for (int i = 0; i < data.sizeDataTransaksi; i++)
        {
            if (data.dataTransaksi[i].tanaman.supplier.id == idSupplier && data.dataTransaksi[i].status == "Selesai")
            {
                timestr = new stringstream();
                (*timestr) << data.dataTransaksi[i].tanggalTransaksi;
                ParseTime((*timeTransaksi), (*timestr));

                if (CompareTimeRangeByMonth((*timeTransaksi), 0) > 0)
                    *pemasukanBulanIni += data.dataTransaksi[i].totalHarga;
            }
        }

        return *pemasukanBulanIni;
    }
    catch (exception &e)
    {
        cout << e.what() << '\n';
    }
    delete pemasukanBulanIni;
    delete timestr;
    delete timeTransaksi;
    pemasukanBulanIni = nullptr;
    timestr = nullptr;
    timeTransaksi = nullptr;

    return 0;
}

void quickSort(Tanaman arr[], int low, int high)
{
    if (low >= high)
        return;

    // menentukan data tengah sebagai pivot
    int mid = low + (high - low) / 2;
    int pivot = arr[mid].stok;
    int i = low, j = high;
    while (i <= j)
    {
        while (arr[i].stok > pivot)
        {
            i++;
        }
        while (arr[j].stok < pivot)
        {
            j--;
        }
        if (i <= j)
        { // Tukar elemen jika berada di posisi yang salah
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    // Rekursi untuk bagian kiri dan kanan array
    if (low < j)
    {
        quickSort(arr, low, j);
    }
    if (i < high)
    {
        quickSort(arr, i, high);
    }
}

void DataTanamanTerlarisSupplier(DataUtama &data, string &idSupplier, Tanaman *dataTanamanTerlaris, int &sizeDataTanamanTerlaris)
{
    const int *jumlahTanaman = new int{JumlahJenisTanamanSupplier(data, idSupplier)};
    Tanaman *dataTanamanSupplier = new Tanaman[*jumlahTanaman];
    int *sizeDataTanamanSupplier = new int{0};

    try
    {
        // Mencari semua jenis tanaman milik supplier
        for (int i = 0; i < data.sizeDataTanaman; i++)
        {
            if (data.dataTanaman[i].supplier.id == idSupplier)
            {
                dataTanamanSupplier[(*sizeDataTanamanSupplier)] = data.dataTanaman[i];
                dataTanamanSupplier[(*sizeDataTanamanSupplier)].stok = 0;
                (*sizeDataTanamanSupplier)++;
            }
        }

        // Menambahkan jumlah tanaman dari setiap transaksi
        for (int i = 0; i < data.sizeDataTransaksi; i++)
        {
            for (int j = 0; i < (*jumlahTanaman); i++)
            {
                if (data.dataTransaksi[i].tanaman.id == dataTanamanSupplier[j].id && data.dataTransaksi[i].status == "Selesai")
                {
                    dataTanamanSupplier[j].stok += data.dataTransaksi[i].jumlahTanaman;
                }
            }
        }

        quickSort(dataTanamanSupplier, 0, (*jumlahTanaman) - 1);

        sizeDataTanamanTerlaris = 0;
        for (int i = 0; i < (*jumlahTanaman); i++)
        {
            if (dataTanamanSupplier[i].stok > 0)
            {
                dataTanamanTerlaris[sizeDataTanamanTerlaris] = dataTanamanSupplier[i];
                sizeDataTanamanTerlaris++;
            }
        }
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
    delete jumlahTanaman;
    delete[] dataTanamanSupplier;
    delete sizeDataTanamanSupplier;
    jumlahTanaman = nullptr;
    dataTanamanSupplier = nullptr;
    sizeDataTanamanSupplier = nullptr;
}

int GetJumlahSupplierAktif(DataUtama &data)
{
    int jumlahSupplier = 0;
    try
    {
        for (int i = 0; i < data.sizeDataSupplier; i++)
        {
            if (data.dataSupplier[i].status == "aktif")
            {
                jumlahSupplier += 1;
            }
        }
        return jumlahSupplier;
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    return 0;
}

int GetPenjualanBulanIniAdmin(DataUtama &data)
{
    int *penjualanBulanIni = new int{0};
    stringstream *timestr = new stringstream();
    tm *timeTransaksi = new tm();
    try
    {
        for (int i = 0; i < data.sizeDataTransaksi; i++)
        {
            if (data.dataTransaksi[i].status == "Selesai")
            {
                timestr = new stringstream();
                (*timestr) << data.dataTransaksi[i].tanggalTransaksi;
                ParseTime((*timeTransaksi), (*timestr));

                if (CompareTimeRangeByMonth((*timeTransaksi), 0) > 0)
                    *penjualanBulanIni += data.dataTransaksi[i].totalHarga;
            }
        }

        return *penjualanBulanIni;
    }
    catch (exception &e)
    {
        cout << e.what() << '\n';
    }
    delete penjualanBulanIni;
    delete timestr;
    delete timeTransaksi;
    penjualanBulanIni = nullptr;
    timestr = nullptr;
    timeTransaksi = nullptr;

    return 0;
}

int GetTransaksiBulanIniAdmin(DataUtama &data)
{
    int *jumlahTransaksi = new int{0};
    stringstream *timestr = new stringstream();
    tm *timeTransaksi = new tm();
    try
    {
        for (int i = 0; i < data.sizeDataTransaksi; i++)
        {
            if (data.dataTransaksi[i].status == "Selesai")
            {
                timestr = new stringstream();
                (*timestr) << data.dataTransaksi[i].tanggalTransaksi;
                ParseTime((*timeTransaksi), (*timestr));

                if (CompareTimeRangeByMonth((*timeTransaksi), 0) > 0)
                    *jumlahTransaksi += 1;
            }
        }

        return *jumlahTransaksi;
    }
    catch (exception &e)
    {
        cout << e.what() << '\n';
    }
    delete jumlahTransaksi;
    delete timestr;
    delete timeTransaksi;
    jumlahTransaksi = nullptr;
    timestr = nullptr;
    timeTransaksi = nullptr;

    return 0;
}

void insertionSort(int a[], int panjang, Supplier *dataSupplier)
{
    for (int i = 1; i < panjang; i++)
    {
        Supplier supplierKey = dataSupplier[i];
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] < key)
        {
            dataSupplier[j + 1] = dataSupplier[j];
            a[j + 1] = a[j];
            j = j - 1;
        }
        dataSupplier[j + 1] = supplierKey;
        a[j + 1] = key;
    }
}

void GetDataSupplierTerlaris(DataUtama &data, Supplier *dataSupplierTerlaris, int &sizeDataSupplierTerlaris, int *dataStokTerjualSupplierAktif)
{
    const int *jumlahSupplierAktif = new int{GetJumlahSupplierAktif(data)};
    Supplier *dataSupplierAktif = new Supplier[*jumlahSupplierAktif];
    int *sizeDataSupplierAktif = new int{0};

    int *jumlahTransaksi = new int{0};
    stringstream *timestr = new stringstream();
    tm *timeTransaksi = new tm();

    try
    {
        // Mencari semua supplier aktif
        for (int i = 0; i < data.sizeDataSupplier; i++)
        {
            if (data.dataSupplier[i].status == "aktif")
            {
                dataSupplierAktif[(*sizeDataSupplierAktif)] = data.dataSupplier[i];
                dataStokTerjualSupplierAktif[(*sizeDataSupplierAktif)] = 0;
                (*sizeDataSupplierAktif)++;
            }
        }

        // Menambahkan jumlah tanaman dari setiap transaksi
        for (int i = 0; i < data.sizeDataTransaksi; i++)
        {
            for (int j = 0; j < (*jumlahSupplierAktif); j++)
            {
                if (data.dataTransaksi[i].tanaman.supplier.id == dataSupplierAktif[j].id && data.dataTransaksi[i].status == "Selesai")
                {
                    timestr = new stringstream();
                    (*timestr) << data.dataTransaksi[i].tanggalTransaksi;
                    ParseTime((*timeTransaksi), (*timestr));

                    if (CompareTimeRangeByMonth((*timeTransaksi), 0) > 0)
                        dataStokTerjualSupplierAktif[j] += data.dataTransaksi[i].jumlahTanaman;
                }
            }
        }

        insertionSort(dataStokTerjualSupplierAktif, (*sizeDataSupplierAktif), dataSupplierAktif);

        sizeDataSupplierTerlaris = 0;
        for (int i = 0; i < (*jumlahSupplierAktif); i++)
        {
            dataSupplierTerlaris[sizeDataSupplierTerlaris] = dataSupplierAktif[i];
            sizeDataSupplierTerlaris++;
        }
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
    }
    delete jumlahSupplierAktif;
    delete[] dataSupplierAktif;
    delete sizeDataSupplierAktif;
    delete jumlahTransaksi;
    delete timestr;
    delete timeTransaksi;
    jumlahSupplierAktif = nullptr;
    dataSupplierAktif = nullptr;
    sizeDataSupplierAktif = nullptr;
    jumlahTransaksi = nullptr;
    timestr = nullptr;
    timeTransaksi = nullptr;
}

#endif