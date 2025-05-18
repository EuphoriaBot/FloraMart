#ifndef MENU_ADMIN_H
#define MENU_ADMIN_H

#include "menu_utilities.h"

void MenuUtamaAdmin(DataUtama &data, InfoLogin infoLogin, DataMenu dataMenu)
{
    try
    {
        // Menu Utama Admin

        // Note: Disarankan untuk Refresh Data Utama di awal Fungsi
        RefreshDataUtama(data);
    }
    catch(invalid_argument& e)
    {
        cout << e.what() << '\n';
    }
    catch(exception& e)
    {
        cout << e.what() << '\n';
    }
}

void MenuManajemenTanaman(DataUtama &data, InfoLogin infoLogin, DataMenu dataMenu)
{
    try
    {
        // Menu Manajmene Tanaman

        // Note: Disarankan untuk Refresh Data Utama di awal Fungsi
        RefreshDataUtama(data);
    }
    catch(invalid_argument& e)
    {
        cout << e.what() << '\n';
    }
    catch(exception& e)
    {
        cout << e.what() << '\n';
    }
}

#endif