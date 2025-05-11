#include <iostream>
using namespace std;

struct Kategori
{
    string jenistanaman;
    string mediatanam;
    double suhumin;
    double suhumax;
};

struct Tanaman
{
    string nama;
    double harga;
    int stok;
    Kategori kategori;
};

int main()
{
    Tanaman tanaman1;

    tanaman1.nama = "Mawar";
    tanaman1.harga = 5000;
    tanaman1.stok = 20;
    tanaman1.kategori.jenistanaman = "Bunga";
    tanaman1.kategori.mediatanam = "awokaowk";
    tanaman1.kategori.suhumin = 20;
    tanaman1.kategori.suhumax = 27;

    cout << "Nama: " << tanaman1.nama << endl;
    cout << "Harga: " << tanaman1.harga << endl;
    cout << "Jenis Tanaman: " << tanaman1.kategori.jenistanaman << endl;
    cout << "Media Tanam: " << tanaman1.kategori.mediatanam << endl;
    cout << "Suhu Minimum: " << tanaman1.kategori.suhumin << " Derajat Celcius" << endl;
    cout << "Suhu Maksimum: " << tanaman1.kategori.suhumax << " Derajat Celcius" << endl;

    return 0;
}
