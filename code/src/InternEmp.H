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
    InternEmp(Utils::EmpStatus empStatusParam);
    virtual ~InternEmp();
    size_t getEmployeeCount() override;
    const std::string_view& getBranch(void) const override;
    std::string getCollege(void) const override;
    friend std::ostream& operator<<(std::ostream& osParam , const InternEmp* empParam);
    friend std::istream& operator>>(std::istream& isParam, InternEmp* emp);

    private:
    Utils::College mCollege;
    std::string mBranch;
    static size_t mSizeOfInternEmployee;

};

#endif