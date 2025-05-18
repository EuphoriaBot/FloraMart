#ifndef MENU_PEMBELI_H
#define MENU_PEMBELI_H

#include "menu_utilities.h"

void MenuUtamaPembeli()
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