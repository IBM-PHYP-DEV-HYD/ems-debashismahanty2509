#ifndef _MANAGER_H_
#define _MANAGER_H_
#include <iostream>
#include "Employee.H"
//Declaration

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
    EDLL<EmployeeIF*>* mEmployeeList=nullptr;
    EDLL<EmployeeIF*>* mResignedEmployeeList=nullptr;

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
    EmployeeIF* sNewEmp = nullptr;
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
            std::cout << "Invalid Employee Type!" << std::endl;
            return;
            break;
    }
    if(nullptr==mEmployeeList)
    {
        mEmployeeList = new EDLL<EmployeeIF*>(1, sNewEmp);
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
        EmployeeIF* sEmp = (*mEmployeeList)[sItr];
        if(sEmp->mID == empIDParam && sEmp->mEmployeeType == empTypeParam)
        {
            if(nullptr==mResignedEmployeeList)
            {
                mResignedEmployeeList = new EDLL<EmployeeIF*>(1, sEmp);
            }
            mResignedEmployeeList->pushBack(sEmp);
            mEmployeeList->remElementMiddle(sItr);
            break;
        }
    }
}

template<class T> void Manager<T>::displayEmployeeType(Employee::EmpType empTypeParam)
{
    // Implementation to display employees based on empTypeParam
    if(nullptr==mEmployeeList || mEmployeeList->empty())
    {
        std::cout << "No employees to display!" << std::endl;
        return;
    }
    for(size_t sItr=0;sItr<mEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mEmployeeList)[sItr];
        if(sEmp->mEmployeeType == empTypeParam)
        {
            if(sEmp->mEmployeeType == Employee::EmpType::FULLTIME)
            {
                std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
            }
            else if(sEmp->mEmployeeType == Employee::EmpType::INTERN)
            {
                std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
            }
            else if(sEmp->mEmployeeType == Employee::EmpType::CONTRACTUAL)
            {
                std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
            }
        }
    }
}

template<class T> void Manager<T>::displayResignedEmployeeList(void)
{
    // Implementation to display resigned employees
    if(nullptr==mResignedEmployeeList || mResignedEmployeeList->empty())
    {
        std::cout << "No resigned employees to display!" << std::endl;
        return;
    }
    for(size_t sItr=0;sItr<mResignedEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mResignedEmployeeList)[sItr];
        if(sEmp->mEmployeeType == Employee::EmpType::FULLTIME)
        {
            std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
        }
        else if(sEmp->mEmployeeType == Employee::EmpType::INTERN)
        {
            std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
        }
        else if(sEmp->mEmployeeType == Employee::EmpType::CONTRACTUAL)
        {
            std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
        }
    }
}

template<class T> void Manager<T>::displayAllEmployee(void)
{
    // Implementation to display all employees
    if(nullptr==mEmployeeList || mEmployeeList->empty())
    {
        std::cout << "No employees to display!" << std::endl;
        return;
    }
    for(size_t sItr=0;sItr<mEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mEmployeeList)[sItr];
        if(sEmp->mEmployeeType == Employee::EmpType::FULLTIME)
        {
            std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
        }
        else if(sEmp->mEmployeeType == Employee::EmpType::INTERN)
        {
            std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
        }
        else if(sEmp->mEmployeeType == Employee::EmpType::CONTRACTUAL)
        {
            std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
        }
    }
}

template<class T> void Manager<T>::searchWithID(const std::string& empIDParam)
{
    // Implementation to search employee based on empIDParam
    if(nullptr==mEmployeeList || mEmployeeList->empty())
    {
        std::cout << "No employees to search!" << std::endl;
        return;
    }
    for(size_t sItr=0;sItr<mEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mEmployeeList)[sItr];
        if(sEmp->mID == empIDParam)
        {
            if(sEmp->mEmployeeType == Employee::EmpType::FULLTIME)
            {
                std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
            }
            else if(sEmp->mEmployeeType == Employee::EmpType::INTERN)
            {
                std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
            }
            else if(sEmp->mEmployeeType == Employee::EmpType::CONTRACTUAL)
            {
                std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
            }
            return;
        }
    }
    std::cout << "Employee with ID " << empIDParam << " not found!" << std::endl;
}

template<class T> void Manager<T>::addLeavesToAll(const uint8_t& leavesParam)
{
    FullEmp::mMaxLeaves += leavesParam;
    if(nullptr==mEmployeeList || mEmployeeList->empty())
    {
        std::cout << "No employees to add leaves!" << std::endl;
        return;
    }
    for(size_t sItr=0;sItr<mEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mEmployeeList)[sItr];
        if(sEmp->mEmployeeType == Employee::EmpType::FULLTIME)
        {
            sEmp->addLeavesToAll(leavesParam);
        }
    }
}


#endif