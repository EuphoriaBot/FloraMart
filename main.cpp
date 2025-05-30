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

    while (!dataMenu.keluar)
    {
        if (!CekLogin(data, infoLogin))
        {
            MenuAwal(data, infoLogin, dataMenu);
        }
        else if (infoLogin.role == "pembeli")
        {
            MenuUtamaPembeli(data, infoLogin, dataMenu);
        }
        else if (infoLogin.role == "supplier")
        {
            MenuUtamaSupplier(data, infoLogin, dataMenu);
        }
        else if (infoLogin.role == "admin")
        {
            MenuUtamaAdmin(data, infoLogin, dataMenu);
        }
        else
        {
            Logout(infoLogin);
        }
    }

    return 0;
}

void MenuAwal(DataUtama &data, InfoLogin &infoLogin, DataMenu &dataMenu)
{
    string temp;
    RefreshDataUtama(data);

    ClearScreen();
    Title("Menu Awal");
    cout << "1. Login" << endl;
    cout << "2. Registrasi Pembeli" << endl;
    cout << "3. Registrasi Supplier" << endl;
    cout << "4. Keluar" << endl;
    Border();
    cout << "Pilih menu: ";
    string pilihan;
    getline(cin, pilihan);

    if (pilihan == "1")
    {
        FormLogin(data, infoLogin);
    }
    else if (pilihan == "2")
    {
        FormRegistrasiPembeli(data);
    }
    else if (pilihan == "3")
    {
        FormRegistrasiSupplier(data);
    }
    else if (pilihan == "4")
    {
        dataMenu.keluar = true;
    }
    else
    {
        cout << "Pilihan tidak valid!";
        getline(cin, temp);
    }
}

void FormLogin(DataUtama &data, InfoLogin &infoLogin)
{
    string temp;

    ClearScreen();
    Title("Form Login");
    cout << "Username: ";
    string input_username;
    getline(cin, input_username);

    cout << "Password: ";
    string input_password;
    getline(cin, input_password);

    for (int i = 0; i < data.sizeDataAdmin; i++)
    {
        if (data.dataAdmin[i].username == input_username && data.dataAdmin[i].password == input_password)
        {
            infoLogin.id = data.dataAdmin[i].id;
            infoLogin.username = data.dataAdmin[i].username;
            infoLogin.role = "admin";
            cout << "Login sebagai admin berhasil...";
            getline(cin, temp);
            return;
        }
    }

    for (int i = 0; i < data.sizeDataPembeli; i++)
    {
        if (data.dataPembeli[i].username == input_username && data.dataPembeli[i].password == input_password)
        {
            infoLogin.id = data.dataPembeli[i].id;
            infoLogin.username = data.dataPembeli[i].username;
            infoLogin.role = "pembeli";
            cout << "Login sebagai pembeli berhasil...";
            getline(cin, temp);
            return;
        }
    }

    for (int i = 0; i < data.sizeDataSupplier; i++)
    {
        if (data.dataSupplier[i].username == input_username && data.dataSupplier[i].password == input_password)
        {
            if (data.dataSupplier[i].status == "blokir")
            {
                cout << "Akun Anda diblokir! Silakan hubungi Admin...!";
                getline(cin, temp);
                return;
            }

            infoLogin.id = data.dataSupplier[i].id;
            infoLogin.username = data.dataSupplier[i].username;
            infoLogin.role = "supplier";
            cout << "Login sebagai supplier berhasil...";
            getline(cin, temp);
            return;
        }
    }

    cout << "Username atau password salah!";
    getline(cin, temp);
}

void FormRegistrasiPembeli(DataUtama &data)
{
    data.flagRefreshPembeli = true;
    string temp;

    ClearScreen();
    Title("Registrasi Pembeli");
    cout << "Username: ";
    string input_username;
    getline(cin, input_username);
    FixString(input_username);

    cout << "Password: ";
    string input_password;
    getline(cin, input_password);
    FixString(input_password);

    if (input_username.empty() || input_password.empty())
    {
        cout << "Username dan password tidak boleh kosong";
        getline(cin, temp);
        return;
    }
    else if (!IsValidString(input_username))
    {
        cout << "Username tidak valid";
        getline(cin, temp);
        return;
    }

    for (int i = 0; i < data.sizeDataPembeli; i++)
    {
        if (data.dataPembeli[i].username == input_username || data.dataSupplier[i].username == input_username || data.dataAdmin[i].username == input_username)
        {
            cout << "Username sudah digunakan, coba yang lain.";
            getline(cin, temp);
            return;
        }
    }

    Pembeli pembeli_baru;
    pembeli_baru.id = GetFreePembeliId();
    pembeli_baru.username = input_username;
    pembeli_baru.password = input_password;

    TambahPembeli(data.dataPembeli, data.sizeDataPembeli, pembeli_baru);

    cout << "Berhasil membuat akun pembeli.";
    getline(cin, temp);
}

void FormRegistrasiSupplier(DataUtama &data)
{
    data.flagRefreshSupplier = true;
    string temp;

    ClearScreen();
    Title("Registrasi Supplier");
    cout << "Username: ";
    string input_username;
    getline(cin, input_username);
    FixString(input_username);

    cout << "Password: ";
    string input_password;
    getline(cin, input_password);
    FixString(input_password);

    if (input_username.empty() || input_password.empty())
    {
        cout << "Username dan password tidak boleh kosong";
        getline(cin, temp);
        return;
    }
    else if (!IsValidString(input_username))
    {
        cout << "Username tidak valid";
        getline(cin, temp);
        return;
    }

    for (int i = 0; i < data.sizeDataSupplier; i++)
    {
        if (data.dataPembeli[i].username == input_username || data.dataSupplier[i].username == input_username || data.dataAdmin[i].username == input_username)
        {
            cout << "Username sudah digunakan, coba yang lain.";
            getline(cin, temp);
            return;
        }
    }

    Supplier supplier_baru;
    supplier_baru.id = GetFreeSupplierId();
    supplier_baru.username = input_username;
    supplier_baru.password = input_password;

    TambahSupplier(data.dataSupplier, data.sizeDataSupplier, supplier_baru);

    cout << "Berhasil membuat akun supplier.";
    getline(cin, temp);
}