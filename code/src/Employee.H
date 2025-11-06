#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_
#include <iostream>
#include "EmployeeIF.H"
class EmployeeIF;
class FullEmp;
class Employee : public EmployeeIF
{
    private:
    std::string mName;
    std::string mID;
    EmployeeIF::EmpGender mGender;
    // char mGender; // M or F
    std::string mDOB; // DD-MM-YYYY
    static size_t mMemberNumbers;
    //Random name generator arrays
    static std::string mFirstNames[10];
    static std::string mLastNames[10];

    void setDOLBasedOnDOJ(bool isDOJSetParam, std::string basedOnTodayDateParam = "");
    void setIDBasedOnMemberNumberAndType(EmpType&);
    void setDOJ(void);
    void setRandomDoj(void);
    void changeIdwithEmpType(void);
    void setRandomGender(void);
    void setRandomDOB(void);

    protected:
    void pGetTodayDate(std::string& dateParam);

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
    virtual const std::string_view& getBranch(void) const;
    virtual std::string getCollege(void) const;
    virtual const uint8_t getCurrentLeaves(void);
    virtual size_t getEmployeeCount();
    friend std::ostream& operator<<(std::ostream& osParam, const Employee* empParam);
    friend std::istream& operator>>(std::istream& isParam, Employee* empParam);
    friend void convertIntern2FullTime(FullEmp* fullEmpParam, const Employee* empParam);


    //Getter functions
    const std::string_view getName(void) const;
    const std::string_view getID(void) const;
    const std::string_view getGender(void) const;
    const EmployeeIF::EmpGender& getGenderType(void) const;
    const std::string_view getDOB(void) const;
    const std::string_view getDOJ(void) const;
    const EmpType getEmployeeType(void) const;
    const EmpStatus getEmployeeStatus(void) const;

    //Setter functions
    void setEmployeeType(EmpType empTypeParam);
    void setEmployeeStatus(EmpStatus empStatusParam);
    void setDOL();
    virtual void setLeavesApplied(const uint8_t& leavesParam);
    virtual void renewLeaveBalance(const uint8_t& carryForwardToNextYearParam);
    virtual void addLeavesToAll(const uint8_t& leavesParam);



};


#endif