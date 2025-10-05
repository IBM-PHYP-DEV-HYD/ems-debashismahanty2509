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
    InternEmp();
    InternEmp(EmpStatus empStatusParam);
    virtual ~InternEmp();
    size_t getEmployeeCount() override;
    friend std::ostream& operator<<(std::ostream& osParam , const InternEmp* empParam);
    friend std::istream& operator>>(std::istream& isParam, InternEmp* emp);

    private:
    EmployeeIF::College mCollege;
    std::string mBranch;
    static size_t mSizeOfInternEmployee;
    
};

#endif