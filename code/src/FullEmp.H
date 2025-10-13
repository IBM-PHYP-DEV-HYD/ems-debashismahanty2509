#ifndef _FULLEMP_H_
#define _FULLEMP_H_
#include <iostream>
#include "Employee.H"


//Declaration
class Employee;
class InternEmp;

class FullEmp : public Employee
{
    public:
    FullEmp();
    FullEmp(EmpStatus empStatusParam);
    FullEmp(const InternEmp& objParam);
    virtual ~FullEmp();
    size_t getEmployeeCount() override;
    const uint8_t getCurrentLeaves(void) override;
    void setLeavesApplied(const uint8_t& leavesParam) override;
    void renewLeaveBalance(const uint8_t& carryForwardToNextYear) override;
    void addLeavesToAll(const uint8_t& leavesParam) override;
    static void setMaxLeaves(const uint8_t& maxLeavesParam);
    friend std::ostream& operator<<(std::ostream& osParam , const FullEmp* empParam);
    // friend void Manager::setMaxLeaves(const uint8_t& maxLeavesParam);
    friend void convertIntern2FullTime(FullEmp* fullEmpParam, const Employee* empParam);

    private:
    static size_t mSizeOfFullEmployee;
    uint8_t mCurrentLeaves;
    uint8_t mLeaveApplied;
    static uint8_t mMaxLeaves;
    void genericConstCall(void);
    
};

#endif