#ifndef MENU_SUPPLIER_H
#define MENU_SUPPLIER_H

#include "menu_utilities.h"

void MenuUtamaSupplier(DataUtama &data, InfoLogin infoLogin, DataMenu dataMenu)
{
    try
    {
        // Menu Utama Supplier

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