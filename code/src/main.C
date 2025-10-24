
#include "EMS.H"

int main()
{
    EMS ems;
    ems.mManagerPtr = Manager::getInstance("XYZ Corp", "admin", "password123");
    if(NULL != ems.mManagerPtr)
    {
        ems.handleMenu();
    }
    return 0;
}