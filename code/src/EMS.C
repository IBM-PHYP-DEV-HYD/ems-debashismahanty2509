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
    if(NULL != ems.managerPtr)
    {
        ems.managerPtr->addEmployee(Employee::EmpType::FULLTIME);
        ems.managerPtr->addEmployee(Employee::EmpType::INTERN);
        ems.managerPtr->addEmployee(Employee::EmpType::CONTRACTUAL);
        ems.managerPtr->displayAllEmployee();
    }
    return 0;
}