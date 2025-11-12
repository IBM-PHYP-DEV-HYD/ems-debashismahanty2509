#ifndef _EMPLOYEEIF_H_
#define _EMPLOYEEIF_H_

#include <iostream>
#include "Utils.H"
/**
 * @class EmployeeIF
 * @brief An interface class for Employee types in the Employee Management System.
 * @details This class defines the common interface for different types of employees, including methods for getting and setting employee attributes.
 */
class EmployeeIF
{
    public:
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
    virtual const Utils::EmpGender& getGenderType(void) const = 0;
    virtual const std::string_view getDOB(void) const = 0;
    virtual const Utils::EmpType getEmployeeType(void) const = 0;
    virtual const Utils::EmpStatus getEmployeeStatus(void) const = 0;
    virtual const std::string_view getDOJ(void) const = 0;
    virtual const std::string_view getDOL(void) const = 0;

    //Setter Functions
    virtual void setEmployeeType(Utils::EmpType empTypeParam) = 0;
    virtual void setEmployeeStatus(Utils::EmpStatus empStatusParam) = 0;
    virtual void setDOL() = 0;

    virtual void setLeavesApplied(const uint8_t& leavesParam) = 0;
    virtual void renewLeaveBalance(const uint8_t& carryForwardToNextYearParam) = 0;
    virtual void addLeavesToAll(const uint8_t& leavesParam) = 0;


};

#endif