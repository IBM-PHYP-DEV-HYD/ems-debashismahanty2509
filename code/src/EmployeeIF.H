#ifndef _EMPLOYEEIF_H_
#define _EMPLOYEEIF_H_

#include <iostream>
class EmployeeIF
{
    public:
    enum EmpGender
    {
        Male        = 0,
        Female      = 1,
        None        = 2,
    };
    enum EmpType
    {
        FULLTIME    = 0,
        INTERN      = 1,
        CONTRACTUAL = 2,
        NONE        = 3,
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
    enum WidthPrint
    {
        Name    = 15,
        Id      = 12,
        Gender  = 10,
        Dob     = 12,
        Doj     = 12,
        Dol     = 12,
        Type    = 12,
        Status  = 10,
        Clg     = 15,
        Bnh     = 11,
        CLeaves = 18,
        LevApp  = 18,
        Agncy   = 8,
    };


    virtual ~EmployeeIF() = default;
    virtual size_t getEmployeeCount() = 0;
    virtual std::string_view getAgency(void) const = 0;
    virtual const std::string_view& getBranch(void) const = 0;
    virtual std::string getCollege(void) const = 0;
    virtual const uint8_t getCurrentLeaves(void) = 0;

    virtual const std::string_view getName(void) const = 0;
    virtual const std::string_view getID(void) const = 0;
    virtual const std::string_view getGender(void) const = 0;
    virtual const EmployeeIF::EmpGender& getGenderType(void) const = 0;
    virtual const std::string_view getDOB(void) const = 0;

    virtual void setEmployeeType(EmpType empTypeParam) = 0;
    virtual void setEmployeeStatus(EmpStatus empStatusParam) = 0;
    virtual void setDOL() = 0;

    virtual void setLeavesApplied(const uint8_t& leavesParam) = 0;
    virtual void renewLeaveBalance(const uint8_t& carryForwardToNextYearParam) = 0;
    virtual void addLeavesToAll(const uint8_t& leavesParam) = 0;
    virtual const EmpType getEmployeeType(void) const = 0;
    virtual const EmpStatus getEmployeeStatus(void) const = 0;

};

#endif