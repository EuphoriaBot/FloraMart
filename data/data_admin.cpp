#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_struct.h"
#include "data_admin.h"

using json = nlohmann::json;
using namespace std;

int main()
{
    // --- Contoh Penggunaan ---
    // Deklarasi Variabel
    Admin dataAdmin[MAX_SIZE]; // Data Utama Admin
    int sizeDataAdmin = 0;        // Size Data Utama Admin

    // -- (READ) Contoh Menampilkan Data --
    GetAllAdmin(dataAdmin, sizeDataAdmin); // Mengambil data terbaru dari JSON

    // Menampilkan Data
    for (int i = 0; i < sizeDataAdmin; i++)
    {
        cout << i + 1 << "." << endl;
        cout << "ID: " << dataAdmin[i].id << endl;
        cout << "Username: " << dataAdmin[i].username << endl;

        cout << endl;
    }

    // -- (UPDATE) Memperbarui Data --
    int updateIndex = -1;
    string _updateTemp; // Jika input manual

    // Pilih item yang diedit
    updateIndex = 1; // Memilih nomor 2
    updateIndex--;   // Menurunkan 1 angka untuk menyesuaikan offset index

    // Versi Input Manual:
    // getline(cin, _updateTemp);
    // updateIndex = stoi(_updateTemp)--

    // Membuat pointer untuk menunjuk ke item data utama yang diedit
    Admin *dataAdminDiedit;
    dataAdminDiedit = &dataAdmin[updateIndex];
    dataAdminDiedit->username = "Gweh Admin"; // Input Manual: getline(cin, dataPembeliDiedit->username->username);

    SimpanDataAdmin(dataAdmin, sizeDataAdmin); // Note: Simpan dengan menggunakan data utama, jangan data yang diperbarui
    return 0;
}