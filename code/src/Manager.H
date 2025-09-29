#ifndef _MANAGER_H_
#define _MANAGER_H_
#include <iostream>
#include "Employee.H"
//Declaration
class Employee;
template<class T> class EDLL;
template<class T> class Node;


template<class T = std::string>
class Manager
{
    public:
    virtual ~Manager();

    T mCompanyName;
    string* mUserName=nullptr;
    string* mPassword=nullptr;
    EDLL<Employee*>* mEmployeeList=nullptr;
    EDLL<Employee*>* mResignedEmployeeList=nullptr;

    size_t mSizeOfFullTimeEmployee=0;
    size_t mSizeOfInternEmployee=0;
    size_t mSizeOfContractualEmployee=0;

    

    static Manager* getInstance(std::string_view userNameParam, std::string_view PassParam, const T& companyNameParam);
    void addCredentials(std::string_view userNameParam, std::string_view PassParam);
    void addEmployee(Employee::EmpType empTypeParam);
    void removeEmployee(Employee::EmpType empTypeParam , const std::string& empIDParam);
    void displayEmployeeType(Employee::EmpType empTypeParam);
    void displayResignedEmployeeList(void);
    void displayAllEmployee(void);
    void searchWithID(const std::string& empIDParam);
    void addLeavesToAll(const uint8_t& leavesParam);

    private:
    Manager(T companyNameParam);
    static Manager* ownPtr=nullptr;
    
};

template<class T> Manager<T>::Manager(T companyNameParam) : mCompanyName(companyNameParam), 
mEmployeeList(nullptr), mResignedEmployeeList(nullptr), mSizeOfFullTimeEmployee(0), 
mSizeOfInternEmployee(0), mSizeOfContractualEmployee(0)
{

}

template<class T> Manager<T>::~Manager()
{
    if(nullptr!=mEmployeeList)
    {
        delete mEmployeeList;
        mEmployeeList = nullptr;
    }
    if(nullptr!=mResignedEmployeeList)
    {
        delete mResignedEmployeeList;
        mResignedEmployeeList = nullptr;
    }
}

template<class T> Manager<T>* Manager<T>::getInstance(std::string_view userNameParam, std::string_view PassParam, const T& companyNameParam)
{
    if(nullptr != ownPtr && nullptr != ownPtr->mUserName && nullptr != ownPtr->mPassword)
    {
        if(*(ownPtr->mUserName) == userNameParam && *(ownPtr->mPassword) == PassParam)
        {
            return ownPtr;
        }
        else
        {
            std::cout << "Invalid Credentials" << std::endl;
            return nullptr;
        }
    }
    if(nullptr==ownPtr)
    {
        ownPtr = new Manager(companyNameParam);
    }
    return ownPtr;
}

template<class T> void Manager<T>::addCredentials(std::string_view userNameParam, std::string_view PassParam)
{
    if(nullptr==mUserName && nullptr==mPassword)
    {
        mUserName = new std::string(userNameParam);
        mPassword = new std::string(PassParam);
        return;
    }
    else
    {
        std::cout << "Credentials already exist!" << std::endl;
        return;
    }
}

template<class T> void Manager<T>::addEmployee(Employee::EmpType empTypeParam)
{
    Employee* sNewEmp = nullptr;
    // Implementation to add employee based on empTypeParam
    switch (empTypeParam)
    {
        case Employee::EmpType::FULLTIME:
            mSizeOfFullTimeEmployee++;
            sNewEmp = new FullEmp();
            break;
        case Employee::EmpType::INTERN:
            mSizeOfInternEmployee++;
            sNewEmp = new InternEmp();
            break;
        case Employee::EmpType::CONTRACTUAL:
            mSizeOfContractualEmployee++;
            sNewEmp = new ContEmp();
            break;    
        default:
            break;
    }
    if(nullptr==mEmployeeList)
    {
        mEmployeeList = new EDLL<Employee*>(1, sNewEmp);
        return;
    }
    mEmployeeList->pushBack(sNewEmp);
}

template<class T> void Manager<T>::removeEmployee(Employee::EmpType empTypeParam , const std::string& empIDParam)
{
    // Implementation to remove employee based on empTypeParam and empIDParam
    if(nullptr==mEmployeeList || mEmployeeList->empty())
    {
        std::cout << "No employees to remove!" << std::endl;
        return;
    }
    for(size_t sItr=0;sItr<mEmployeeList->size();sItr++)
    {
        if(mEmployeeList->operator[](sItr)->mID == empIDParam && mEmployeeList->operator[](sItr)->mEmployeeType == empTypeParam)
        {
            if(nullptr==mResignedEmployeeList)
            {
                mResignedEmployeeList = new EDLL<Employee*>(1, mEmployeeList->operator[](sItr));
            }
            mResignedEmployeeList->pushBack(mEmployeeList->operator[](sItr));
            mEmployeeList->remElementMiddle(sItr);
            break;
        }
    }
}


#endif