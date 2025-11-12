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
    Utils::EmpGender mGender;
    std::string mDOB; // DD-MM-YYYY
    Utils::EmpType mEmployeeType;
    Utils::EmpStatus mEmployeeStatus;
    std::string mDOL; // DD-MM-YYYY
    std::string mDOJ; // DD-MM-YYYY
    static size_t mMemberNumbers;
    //Random name generator arrays
    static std::string mFirstNames[10];
    static std::string mLastNames[10];

    void setDOLBasedOnDOJ(bool isDOJSetParam, std::string basedOnTodayDateParam = "");
    void setIDBasedOnMemberNumberAndType(Utils::EmpType&);
    void setDOJ(void);
    void setRandomDoj(void);
    void changeIdwithEmpType(void);
    void setRandomGender(void);
    void setRandomDOB(void);


    protected:
    void pGetTodayDate(std::string& dateParam);

    public:
    //Constructors and Destructors
    Employee(Utils::EmpType empTypeParam);
    Employee(Utils::EmpType empTypeParam, Utils::EmpStatus empStatusParam);
    virtual ~Employee();
    // Default Copy Constructor
    Employee(const Employee&) = default;
    // delete move constructor
    Employee(Employee&&) = delete;

    //Member functions
    bool validCheck(std::istream& isParam);
    friend std::ostream& operator<<(std::ostream& osParam, const Employee* empParam);
    friend std::istream& operator>>(std::istream& isParam, Employee* empParam);
    friend void convertIntern2FullTime(FullEmp* fullEmpParam, const Employee* empParam);


    //Getter functions
    const std::string_view getName(void) const;
    const std::string_view getID(void) const;
    const std::string_view getGender(void) const;
    const Utils::EmpGender& getGenderType(void) const;
    const std::string_view getDOB(void) const;
    const std::string_view getDOJ(void) const;
    const std::string_view getDOL(void) const;
    const Utils::EmpType getEmployeeType(void) const;
    const Utils::EmpStatus getEmployeeStatus(void) const;
    virtual std::string_view getAgency(void) const;
    virtual const std::string_view& getBranch(void) const;
    virtual std::string getCollege(void) const;
    virtual const uint8_t getCurrentLeaves(void);
    virtual size_t getEmployeeCount();

    //Setter functions
    void setEmployeeType(Utils::EmpType empTypeParam);
    void setEmployeeStatus(Utils::EmpStatus empStatusParam);
    void setDOL();
    virtual void setLeavesApplied(const uint8_t& leavesParam);
    virtual void renewLeaveBalance(const uint8_t& carryForwardToNextYearParam);
    virtual void addLeavesToAll(const uint8_t& leavesParam);



};


#endif