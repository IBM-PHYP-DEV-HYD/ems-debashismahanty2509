#ifndef _FULLEMP_H_
#define _FULLEMP_H_
#include <iostream>
#include "Employee.H"

//Declaration
class Employee;

class FullEmp : public Employee
{
    public:
    FullEmp();
    virtual ~FullEmp();
    size_t getEmployeeCount() override;
    const uint8_t getCurrentLeaves(void) override;
    friend std::ostream& operator<<(std::ostream& osParam , const FullEmp* emp);
    friend std::istream& operator>>(std::istream& isParam , FullEmp* emp);

    private:
    size_t mSizeOfFullEmployee=0;
    uint8_t mCurrentLeaves=0;
    uint8_t mMaxLeaves=18;
    
};

FullEmp::FullEmp() : Employee() , mSizeOfFullEmployee(0)
{

}

FullEmp::~FullEmp()
{

}

size_t FullEmp::getEmployeeCount()
{
    return mSizeOfFullEmployee;
}

const uint8_t FullEmp::getCurrentLeaves(void)
{
    return mCurrentLeaves;
}

std::ostream& operator<<(std::ostream& osParam , const FullEmp* emp)
{

}

std::istream& operator>>(std::istream& isParam , FullEmp* emp)
{

}

#endif