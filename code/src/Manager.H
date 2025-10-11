#ifndef _MANAGER_H_
#define _MANAGER_H_
#include <iostream>
#include "Employee.H"
#include "FullEmp.H"
#include "InternEmp.H"
#include "ContEmp.H"
#include "EDLL.H"
//Declaration

template<class T> class EDLL;
template<class T> class Node;


class Manager
{
    public:
    virtual ~Manager();

    std::string mCompanyName;
    std::string* mUserName=nullptr;
    std::string* mPassword=nullptr;
    EDLL<EmployeeIF*>* mEmployeeList=nullptr;
    EDLL<EmployeeIF*>* mResignedEmployeeList=nullptr;

    size_t mSizeOfFullTimeEmployee=0;
    size_t mSizeOfInternEmployee=0;
    size_t mSizeOfContractualEmployee=0;

    

    static Manager* getInstance(const std::string& companyNameParam, std::string_view userNameParam = "admin", std::string_view PassParam = "admin");
    void addCredentials(std::string_view userNameParam, std::string_view PassParam);
    void addEmployee(Employee::EmpType empTypeParam);
    void removeEmployee(Employee::EmpType empTypeParam , const std::string& empIDParam);
    void displayEmployeeType(Employee::EmpType empTypeParam);
    void displayResignedEmployeeList(void);
    void displayAllEmployee(void);
    void searchWithID(const std::string& empIDParam);
    void addLeavesToAll(const uint8_t& leavesParam);

    private:
    Manager(std::string companyNameParam);
    static Manager* mOwnPtr;
    
};
#endif