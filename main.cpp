#include <iostream>
#include <filesystem>

#include "menu_utilities.h"
#include "menu_supplier.h"
#include "menu_pembeli.h"
#include "menu_admin.h"

using namespace std;

void MenuAwal(DataUtama &data, InfoLogin &infoLogin, DataMenu &dataMenu); // Menu Awal di mana user belum login
void FormLogin(DataUtama &data, InfoLogin &infoLogin);                    // Form ketika user mencoba login
void FormRegistrasiPembeli(DataUtama &data);                              // Form untuk user yang ingin mendaftar sebagai pembeli
void FormRegistrasiSupplier(DataUtama &data);                             // Form untuk user yang ingin mendaftar sebagai supplier

int main()
{
    DataUtama data = {};
    InfoLogin infoLogin = {};
    DataMenu dataMenu = {};

    RefreshDataUtama(data);

    // Contoh Membaca Data
    // for (int i = 0; i < data.sizeDataSupplier; i++)
    // {
    //     cout << i + 1 << ". ";
    //     cout << "\tUsername: " << data.dataSupplier[i].username << endl;
    //     cout << "\tMetode Tersedia: ";
    //     for (int j = 0; j < data.dataSupplier[i].sizeMetodeTersedia; j++)
    //     {
    //         cout << j + 1 << ". " << data.dataSupplier[i].metodeTersedia[j].metode << " ";
    //     }
    //     cout << endl;
    // }

    while (!dataMenu.keluar)
    {
        if (!CekLogin(infoLogin))
        {
            // Menampilkan halaman jika user belum login

            MenuAwal(data, infoLogin, dataMenu);
        }
        else if (infoLogin.role == "pembeli")
        {
            // Menampilkan halaman Pembeli

            MenuUtamaPembeli();
        }
        else if (infoLogin.role == "supplier")
        {
            // Menampilkan halaman Supplier

            MenuUtamaSupplier();
        }
        else if (infoLogin.role == "admin")
        {
            // Menampilkan halaman Admin

            MenuUtamaAdmin();
        }
        else
        {
            // Menghapus info login jika role tidak valid

            infoLogin = {};
        }
    }

    return 0;
}

void MenuAwal(DataUtama &data, InfoLogin &infoLogin, DataMenu &dataMenu)
{
    try
    {
        cout << "Menu Awal" << endl;
        // string pilihan
        //
        // Menu Awal
        // 1. Login
        // 2. Registrasi Pembeli
        // 3. Registrasi Penjual
        // 
        // input pilihan
        //
        // if pilihan == "1"
        //    form_login()
        // else if pilihan == "2"
        //    form_registrasi_pembeli()
        // else if pilihan == "3"
        //    form_registrasi_supplier()
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

void FormLogin(DataUtama &data, InfoLogin &infoLogin)
{
    try
    {
        // Form Login

        // string input_username, input_password
        // 
        // input input_username
        // input input_password
        //
        // for i:data.data_admin
        //     if data_admin[i].username == input_username && data.data_admin[i].password == input_password:
        //         infoLogin.id = data_admin[i].id
        //         infoLogin.username = data_admin[i].username
        //         infoLogin.role = "admin"
        //
        // for i:data.data_pembeli
        //     if data_pembeli[i].username == input_username && data.data_pembeli[i].password == input_password:
        //         infoLogin.id = data_pembeli[i].id
        //         infoLogin.username = data_pembeli[i].username
        //         infoLogin.role = "pembeli"
        //
        // for i:data.data_supplier
        //     if data.data_supplier[i] == input_username && data.data_supplier[i].password == input_password:
        //         infoLogin.id = data_supplier[i].id
        //         infoLogin.username = data_supplier[i].username
        //         infoLogin.role = "supplier"
        //
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

void FormRegistrasiPembeli(DataUtama &data)
{
    try
    {
        // Form Registrasi Pembeli
        //
        // string input_username, input_password
        // Pembeli pembeli_baru
        // 
        // input input_username
        // input input_password
        //
        // pembeli_baru.id = get_free_pembeli_id()
        // pembeli_baru.username = input_username
        // pembeli_baru.password = input_password
        //
        // tambah_pembeli(pembeli)
        //
        // print("berhasil membuat akun pembeli")
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

void FormRegistrasiSupplier(DataUtama &data)
{
    try
    {
        // Form Registrasi Pembeli
        //
        // string input_username, input_password
        // Pembeli pembeli_baru
        // 
        // input input_username
        // input input_password
        //
        // pembeli_baru.id = get_free_supplier_id()
        // pembeli_baru.username = input_username
        // pembeli_baru.password = input_password
        //
        // tambah_pembeli(pembeli)
        //
        // print("berhasil membuat akun supplier")
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