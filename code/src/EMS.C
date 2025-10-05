#include "iostream"
#include "Manager.H"

class EMS
{
    public:
    Manager<std::string> *managerPtr = nullptr;
    EMS() = default;
    ~EMS() = default;
};

int main()
{
    EMS ems;
    ems.managerPtr = Manager<std::string>::getInstance("XYZ Corp", "admin", "password123");
    return 0;
}