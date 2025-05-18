#include <iostream>

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
        // Menu Awal
        // 1. Login
        // 2. Registrasi Pembeli
        // 3. Registrasi Penjual
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
        // Form Registrasi Supplier/
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