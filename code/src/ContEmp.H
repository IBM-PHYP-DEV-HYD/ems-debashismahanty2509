#ifndef _CONTEMP_H_
#define _CONTEMP_H_
#include <iostream>
#include "Employee.H"

//Declaration
class Employee;

class ContEmp : public Employee
{
    public:
    ContEmp();
    virtual ~ContEmp();
    size_t getEmployeeCount() override;
    std::string_view getAgency(void) const override;
    friend std::ostream& operator<<(std::ostream& osParam , const ContEmp* empParam);
    friend std::istream& operator>>(std::istream& isParam , ContEmp* empParam);

    private:
    size_t mSizeOfContEmployee;
    std::string mAgency;
};

ContEmp::ContEmp() : Employee() , mSizeOfContEmployee(0)
{

}

ContEmp::~ContEmp()
{

}

size_t ContEmp::getEmployeeCount()
{
    return mSizeOfContEmployee;
}

std::string_view ContEmp::getAgency(void) const
{
    return mAgency;
}

std::ostream& operator<<(std::ostream& osParam , const ContEmp* emp)
{

}

std::istream& operator>>(std::istream& isParam , ContEmp* emp)
{

}


#endif