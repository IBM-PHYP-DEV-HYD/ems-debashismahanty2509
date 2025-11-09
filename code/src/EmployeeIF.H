#ifndef _EMPLOYEEIF_H_
#define _EMPLOYEEIF_H_

#include <iostream>

/**
 * @class EmployeeIF
 * @brief An interface class for Employee types in the Employee Management System.
 * @details This class defines the common interface for different types of employees, including methods for getting and setting employee attributes.
 */
class EmployeeIF
{
    public:
    // Enumerations for Employee Type, Status, Gender, Agency, College, Branch, Input Type, and Width for Printing
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
        ACTIVE       = 0,
        INACTIVE     = 1,
        RESIGNED     = 2,
    };
    enum Agency
    {
        Avengers     = 0,
        JusticeLeague= 1,
        XMen         = 2,
    };
    enum College
    {
        IitDelhi      = 0,
        IitMumbai     = 1,
        IitKanpur     = 2,
        IitHyderabad  = 3,
        NitWarangal   = 4,
        NitTiruchi    = 5,
        IiitHyderabad = 6,
    };
    enum Branch
    {
        CSE          = 0,
        ECE          = 1,
        CSIT         = 2,
    };
    enum InputType
    {
        RANDOM       = 0,
        USERINPUT    = 1,
    };
    enum WidthPrint
    {
        Name         = 17,
        Id           = 12,
        Gender       = 10,
        Dob          = 12,
        Doj          = 12,
        Dol          = 12,
        Type         = 12,
        Status       = 10,
        Clg          = 15,
        Bnh          = 11,
        CLeaves      = 18,
        LevApp       = 18,
        Agncy        = 15,
        LeftMar      = 13,
    };


    virtual ~EmployeeIF() = default;

    //Getter Functions
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
    virtual const EmpType getEmployeeType(void) const = 0;
    virtual const EmpStatus getEmployeeStatus(void) const = 0;
    virtual const std::string_view getDOJ(void) const = 0;
    virtual const std::string_view getDOL(void) const = 0;

    //Setter Functions
    virtual void setEmployeeType(EmpType empTypeParam) = 0;
    virtual void setEmployeeStatus(EmpStatus empStatusParam) = 0;
    virtual void setDOL() = 0;

    virtual void setLeavesApplied(const uint8_t& leavesParam) = 0;
    virtual void renewLeaveBalance(const uint8_t& carryForwardToNextYearParam) = 0;
    virtual void addLeavesToAll(const uint8_t& leavesParam) = 0;


};

#endif