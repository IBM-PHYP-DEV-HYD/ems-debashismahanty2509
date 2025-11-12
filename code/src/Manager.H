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
        void addEmployee(Utils::EmpType empTypeParam);
        void addRandomEmp(uint16_t numOfEmpParam);
        void removeEmployee(const std::string& empIDParam,bool isResignedReqParam = true);
        void displayEmployeeType(Utils::EmpType empTypeParam);
        void displayResignedEmployeeList(void);
        void displayAllEmployee(void);
        void searchWithID(const std::string& empIDParam);
        void searchWithGender(const Utils::EmpGender& sEmpGenderParam);
        void searchWithStatus(const Utils::EmpStatus & sEmpStatusParam);
        void searchWithName(const std::string& sEmpNameParam);
        void addLeavesToAll(const uint8_t& leavesParam);
        void conv2Full(const std::string& empIDParam);
        bool isEmpEmpty(void);

    private:
        Manager(std::string companyNameParam);
        static Manager* mOwnPtr;
        EmployeeIF* searchIDIntern(const std::string& empIdParam);
        void designForAll(void);
        void displayEndLine(void);
        void displayEmpBasedOnType(const EmployeeIF* const sEmp, const Utils::EmpType& sEmpType, const Utils::EmpStatus& sEmpStatusParam);
        void findSizeInEmp(size_t& sEmpSizeParam);

};
#endif