#ifndef MENU_PEMBELI_H
#define MENU_PEMBELI_H

#include "menu_utilities.h"

void MenuUtamaPembeli(DataUtama &data, InfoLogin infoLogin, DataMenu dataMenu)
{
    try
    {
        // Menu Utama Pembeli
        
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