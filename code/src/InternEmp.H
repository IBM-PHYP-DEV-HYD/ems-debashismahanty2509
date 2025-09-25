#ifndef _INTEREMP_H_
#define _INTEREMP_H_
#include <iostream>
#include "Employee.H"

//Declaration
class Employee;

class InternEmp : public Employee
{
    public:
    InternEmp();
    virtual ~InternEmp();
    size_t getEmployeeCount() override;
    friend std::ostream& operator<<(std::ostream& osParam , const InternEmp* empParam);
    friend std::istream& operator>>(std::istream& isParam , InternEmp* empParam);

    private:
    std::string mCollege;
    std::string mBranch;
    static size_t mSizeOfInternEmployee;
    
};
size_t InternEmp::mSizeOfInternEmployee = 0;

InternEmp::InternEmp() : Employee()
{
    mSizeOfInternEmployee++;
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
    // Implement your output logic here, for example:
    osParam << "InternEmp: College=" << emp->mCollege << ", Branch=" << emp->mBranch;
    return osParam;
}

std::istream& operator>>(std::istream& isParam, InternEmp* emp)
{
    // Implement your input logic here, for example:
    return isParam;
}

#endif