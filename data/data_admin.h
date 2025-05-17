#ifndef DATA_ADMIN_H
#define DATA_ADMIN_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_struct.h"

using json = nlohmann::json;
using namespace std;

// Mengubah nilai dari json ke admin per data
void from_json(json &j, Admin &admin)
{
    try
    {
        j.at("id").get_to(admin.id);
        j.at("username").get_to(admin.username);
    }
    catch (const invalid_argument &e)
    {
        cout << endl
             << e.what() << endl;
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << endl;
    }
}

// Mengubah nilai dari admin ke json per data
void to_json(json &j, json &oldJsonData, Admin &admin)
{
    string *newPassword = new string();
    try
    {
        *newPassword = admin.password;
        if (*newPassword == "")
            *newPassword = oldJsonData.at("password");

        j = json{
            {"id", admin.id},
            {"username", admin.username},
            {"password", *newPassword}};
    }
    catch (const invalid_argument &e)
    {
        cout << endl
             << e.what() << endl;
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << endl;
    }
    
    delete newPassword;
    newPassword = nullptr;
}

// Mengambil semua data admin (Admin[])
void GetAllAdmin(Admin *dataAdmin, int &sizeData)
{
    json *_jsonData = new json();
    try
    {
        ifstream readFile("data_admin.json");
        *_jsonData = json::parse(readFile);
        sizeData = min(int((*_jsonData).size()), int(MAX_SIZE));

        for (int i = 0; i < sizeData; i++)
            from_json((*_jsonData)[i], dataAdmin[i]);

        readFile.close();
    }
    catch (const invalid_argument &e)
    {
        cout << endl
             << e.what() << endl;
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << endl;
    }
    
    delete _jsonData;
    _jsonData = nullptr;
}

// Mencari Admin dari ID dan ambil dari data yang memiliki id yang sama dengan targetId
void GetAdmin(Admin &admin, string targetId)
{
    Admin *dataAdmin = new Admin[MAX_SIZE];
    int *sizeDataAdmin = new int{0};

    try
    {
        GetAllAdmin(dataAdmin, *sizeDataAdmin);

        for (int i = 0; i < *sizeDataAdmin; i++)
        {
            if (dataAdmin[i].id == targetId)
                admin = dataAdmin[i];
        }
    }
    catch (const invalid_argument &e)
    {
        cout << endl
             << e.what() << endl;
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << endl;
    }
    delete[] dataAdmin;
    delete sizeDataAdmin;
    dataAdmin = nullptr;
    sizeDataAdmin = nullptr;
}

// Menyimpan Data di program saat ini ke JSON
void SimpanDataAdmin(Admin *dataAdmin, int &sizeData)
{
    json *_oldJsonData = new json();
    json *_newJsonData = new json();

    try
    {
        ifstream readOldFile("./database/admin.json");
        *_oldJsonData = json::parse(readOldFile);
        *_newJsonData = json::array();

        for (int i = 0; i < sizeData; i++)
        {
            json j;
            to_json(j, (*_oldJsonData)[i], dataAdmin[i]);

            // Menambah 1 elemen (data json) array ke belakang
            (*_newJsonData).push_back(j);
        }

        ofstream writeFile("./database/admin.json");
        writeFile << (*_newJsonData);

        readOldFile.close();
        writeFile.close();
    }
    catch (const invalid_argument &e)
    {
        cout << endl
             << e.what() << endl;
    }
    catch (const exception &e)
    {
        cout << endl
             << e.what() << endl;
    }

    delete _oldJsonData;
    delete _newJsonData;
    _oldJsonData = nullptr;
    _newJsonData = nullptr;
}

bool LoginAdmin(string username, string password, Admin currentAdmin, Admin *dataAdmin, int &sizeDataAdmin)
{
    Admin *_tempDataAdmin = new Admin[MAX_SIZE];

    ifstream readFile("./database/admin.json");
    json _jsonData = json::parse(readFile);

    // Inisialisasi username dan password dari data admin
    for (int i = 0; i < sizeDataAdmin; i++)
    {
        _jsonData[i].at("username").get_to(_tempDataAdmin[i].username);
        _jsonData[i].at("password").get_to(_tempDataAdmin[i].password);
    }

    // Pencocokan dengan data akun
    for (int i = 0; i < sizeDataAdmin; i++)
    {
        if (_tempDataAdmin[i].username == username && _tempDataAdmin[i].password == password)
        {
            currentAdmin = dataAdmin[i];
            return true;
        }
    }

    delete[] _tempDataAdmin;
    _tempDataAdmin = nullptr;

    return false;
}

#endif