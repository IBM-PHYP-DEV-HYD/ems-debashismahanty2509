#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_
#include <iostream>
#include "EmployeeIF.H"
class EmployeeIF;

class Employee : public EmployeeIF
{
    private:
    std::string mName;
    std::string mID;
    char mGender; // M or F
    std::string mDOB; // DD-MM-YYYY
    static size_t mMemberNumbers;
    //Random name generator arrays
    std::string mFirstNames[10] = {"John", "Jane", "Alice", "Bob", "Charlie", "Diana", "Eve", "Frank", "Grace", "Hank"};
    std::string mLastNames[10] = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez"};

    void setDOLBasedOnDOJ(bool isDOJSet, std::string setDOLBasedOnDOJ = "");
    void setIDBasedOnMemberNumberAndType(EmpType&);
    void setDOJ(void);
    void setRandomDoj(void);
    void changeIdwithEmpType(void);
    void getTodayDate(std::string& dateParam);


    public:
    EmpType mEmployeeType;
    EmpStatus mEmployeeStatus;
    std::string mDOJ; // DD-MM-YYYY
    std::string mDOL; // DD-MM-YYYY

    //Constructors and Destructors
    Employee(EmpType empTypeParam);
    Employee(EmpType empTypeParam, EmpStatus empStatusParam);
    virtual ~Employee();

    //Member functions
    bool validCheck(std::istream& isParam);
    virtual std::string_view getAgency(void) const;
    virtual const std::string_view& getBranch(void);
    virtual void getCollege(void);
    virtual const uint8_t getCurrentLeaves(void);
    virtual size_t getEmployeeCount();
    friend std::ostream& operator<<(std::ostream& osParam, const Employee* emp);
    friend std::istream& operator>>(std::istream& isParam, Employee* emp);

    //Getter functions
    const std::string_view getName(void) const;
    const std::string_view getID(void) const;
    const std::string_view getGender(void) const;
    const std::string_view getDOB(void) const;
    const std::string_view getDOJ(void) const;

    //Setter functions
    void setEmployeeType(EmpType empTypeParam);
    void setEmployeeStatus(EmpStatus empStatusParam);
    void setDOL(const std::string& dolParam);
    virtual void setLeavesApplied(const uint8_t& leavesParam);
    virtual void renewLeaveBalance(const uint8_t& carryForwardToNextYear);
    virtual void addLeavesToAll(const uint8_t& leavesParam);



};


#endif