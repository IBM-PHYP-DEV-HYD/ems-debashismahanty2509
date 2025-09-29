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
    friend std::ostream& operator<<(std::ostream& osParam , const FullEmp* empParam);

    private:
    static size_t mSizeOfFullEmployee;
    uint8_t mCurrentLeaves=0;
    static uint8_t mMaxLeaves;
    
};
size_t FullEmp::mSizeOfFullEmployee = 0;
uint8_t FullEmp::mMaxLeaves = 22;
FullEmp::FullEmp() : Employee(EmployeeIF::EmpType::FULLTIME)
{
    mSizeOfFullEmployee++;
    std::string_view sDOJ = getDOJ();

    if(sDOJ != "NA" && sDOJ.length() == 10)
    {
        int8_t sLeftMonth = 12 - std::stoi(std::string(sDOJ.substr(3,2)));
        mCurrentLeaves = (sLeftMonth * mMaxLeaves) / 12;
    }
    
}

FullEmp::~FullEmp()
{
    mSizeOfFullEmployee--;
}

size_t FullEmp::getEmployeeCount()
{
    return mSizeOfFullEmployee;
}

const uint8_t FullEmp::getCurrentLeaves(void)
{
    return mCurrentLeaves;
}

std::ostream& operator<<(std::ostream& osParam , const FullEmp* empParam)
{
    osParam << static_cast<const Employee*>(empParam);
    osParam << "Current Leaves: " << empParam->mCurrentLeaves << std::endl;
    return osParam;
}

#endif