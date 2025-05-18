#ifndef MENU_SUPPLIER_H
#define MENU_SUPPLIER_H

#include "menu_utilities.h"

void MenuUtamaSupplier()
{
    try
    {
        
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