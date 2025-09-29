#ifndef _INTEREMP_H_
#define _INTEREMP_H_
#include <iostream>
#include "Employee.H"

//Declaration
class EmployeeIF;
class Employee;

class InternEmp : public Employee
{
    public:
    InternEmp(EmployeeIF::InputType empInputTypeParam);
    virtual ~InternEmp();
    size_t getEmployeeCount() override;
    friend std::ostream& operator<<(std::ostream& osParam , const InternEmp* empParam);
    friend std::istream& operator>>(std::istream& isParam, InternEmp* emp);

    private:
    EmployeeIF::College mCollege;
    std::string mBranch;
    static size_t mSizeOfInternEmployee;
    
};
size_t InternEmp::mSizeOfInternEmployee = 0;


InternEmp::InternEmp(EmployeeIF::InputType empInputTypeParam) : Employee(EmployeeIF::EmpType::INTERN)
{
    mSizeOfInternEmployee++;
    if(empInputTypeParam == EmployeeIF::InputType::RANDOM)
    {
        mCollege = static_cast<EmployeeIF::College>(rand() % 7);
        mBranch = static_cast<EmployeeIF::Branch>(rand() % 3);
    }
    else if(empInputTypeParam == EmployeeIF::InputType::USERINPUT)
    {
        std::cin >> this;
    }
}

InternEmp::~InternEmp()
{
    mSizeOfInternEmployee--;
}

size_t InternEmp::getEmployeeCount()
{
    return mSizeOfInternEmployee;
}

std::ostream& operator<<(std::ostream& osParam, const InternEmp* emp)
{
    osParam << static_cast<const Employee*>(emp);
    osParam << "InternEmp: College=" << emp->mCollege;
    osParam <<  "\nBranch=" << emp->mBranch;
    return osParam;
}

std::istream& operator>>(std::istream& isParam, InternEmp* emp)
{
    std::cout<< "Enter College: \n1. IitDelhi\n2. IitMumbai\n3. IitKanpur\n4. IitHyderabad\n5. NitWarangal\n6. NitTiruchi\n7. IiitHyderabad\n";
    std::cout<< "Enter choice (1-7): ";
    uint8_t sCollege;
    isParam >> sCollege;
    if(emp->validCheck(isParam) == false || (sCollege < 1 || sCollege > 7))
    {
        std::cout<<"Invalid input, setting default college to IitDelhi\n"<<std::endl;
        emp->mCollege = static_cast<EmployeeIF::College>(0);
    }
    else
    {
        emp->mCollege = static_cast<EmployeeIF::College>(sCollege - 1);
    }

    std::cout<< "Enter Branch: \n1. CSE\n2. ECE\n3. CSIT\n";
    std::cout<< "Enter choice (1-3): ";
    isParam >> emp->mBranch;
    if(emp->validCheck(isParam) == false || (emp->mBranch < "1" || emp->mBranch > "3"))
    {
        std::cout<<"Invalid input, setting default branch to CSE\n"<<std::endl;
        emp->mBranch = static_cast<EmployeeIF::Branch>(0);
    }
    else
    {
        emp->mBranch = static_cast<EmployeeIF::Branch>(std::stoi(emp->mBranch) - 1);
    }

    return isParam;
}

#endif