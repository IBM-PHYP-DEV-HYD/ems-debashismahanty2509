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
    FullEmp(EmpStatus empStatusParam);
    virtual ~FullEmp();
    size_t getEmployeeCount() override;
    const uint8_t getCurrentLeaves(void) override;
    friend std::ostream& operator<<(std::ostream& osParam , const FullEmp* empParam);

    private:
    static size_t mSizeOfFullEmployee;
    uint8_t mCurrentLeaves;
    static uint8_t mMaxLeaves;
    
};

#endif