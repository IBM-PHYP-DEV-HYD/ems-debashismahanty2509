#ifndef _EMPLOYEEIF_H_
#define _EMPLOYEEIF_H_

#include <iostream>
class EmployeeIF
{
    public:
    enum EmpType
    {
        NONE,
        FULLTIME,
        INTERN,
        CONTRACTUAL
    };
    enum EmpStatus
    {
        ACTIVE,
        INACTIVE,
        RESIGNED
    };
    enum Agency
    {
        Avengers,
        JusticeLeague,
        XMen
    };
    enum College
    {
        IitDelhi,
        IitMumbai,
        IitKanpur,
        IitHyderabad,
        NitWarangal,
        NitTiruchi,
        IiitHyderabad
    };
    enum Branch
    {
        CSE,
        ECE,
        CSIT
    };
    enum InputType
    {
        RANDOM = 0,
        USERINPUT = 1
    };


    virtual ~EmployeeIF() = default;
    virtual size_t getEmployeeCount() = 0;
    virtual std::string_view getAgency(void) const = 0;
    virtual const std::string_view& getBranch(void) = 0;
    virtual const std::string& getCollege(void) = 0;
    virtual const uint8_t getCurrentLeaves(void) = 0;

    virtual const std::string_view getName(void) const = 0;
    virtual const std::string_view getID(void) const = 0;
    virtual const std::string_view getGender(void) const = 0;
    virtual const std::string_view getDOB(void) const = 0;

    virtual void setEmployeeType(EmpType empTypeParam) = 0;
    virtual void setEmployeeStatus(EmpStatus empStatusParam) = 0;
    virtual void setDOL(const std::string& dolParam) = 0;

    virtual void setLeavesApplied(const uint8_t& leavesParam) = 0;
    virtual void renewLeaveBalance(const uint8_t& carryForwardToNextYear) = 0;
    virtual void addLeavesToAll(const uint8_t& leavesParam) = 0;
    virtual const EmpType getEmployeeType(void) const = 0;
    virtual const EmpStatus getEmployeeStatus(void) const = 0;

};

#endif