#ifndef DATA_ADMIN_H
#define DATA_ADMIN_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include "nlohmann/json.hpp"
#include "data_utilities.h"

using json = nlohmann::json;
using namespace std;

#ifdef DATA_NAME
#undef DATA_NAME
#endif
#define DATA_NAME "admin.json"

// Mengubah nilai dari json ke admin per data
void from_json(json &j, Admin &admin)
{
    try
    {
        j.at("id").get_to(admin.id);
        j.at("username").get_to(admin.username);
        j.at("password").get_to(admin.password);
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
        ReadJson(*_jsonData, sizeData, "admin.json");
        for (int i = 0; i < sizeData; i++)
            from_json((*_jsonData)[i], dataAdmin[i]);
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
void SimpanAdmin(Admin *dataAdmin, int &sizeData)
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

#endif