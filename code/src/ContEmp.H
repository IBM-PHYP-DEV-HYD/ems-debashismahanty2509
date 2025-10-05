#ifndef _CONTEMP_H_
#define _CONTEMP_H_
#include <iostream>
#include "Employee.H"

//Declaration
class EmployeeIF;
class Employee;

class ContEmp : public Employee
{
    public:
    ContEmp();
    ContEmp(EmpStatus empStatusParam);
    virtual ~ContEmp();
    size_t getEmployeeCount() override;
    std::string_view getAgency(void) const override;
    friend std::ostream& operator<<(std::ostream& osParam , const ContEmp* empParam);
    friend std::istream& operator>>(std::istream& isParam , ContEmp* empParam);

    private:
    static size_t mSizeOfContEmployee;
    EmployeeIF::Agency mAgency;
};
#endif