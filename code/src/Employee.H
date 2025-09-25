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

    void setDOLBasedOnDOJ(bool isDOJSet, std::string setDOLBasedOnDOJ = "");
    void setIDBasedOnMemberNumberAndType(EmpType&);
    void setDOJ(void);
    void changeIdwithEmpType(void);
    void getTodayDate(std::string& dateParam);


    public:
    EmpType mEmployeeType;
    EmpStatus mEmployeeStatus;
    std::string mDOJ; // DD-MM-YYYY
    std::string mDOL; // DD-MM-YYYY

    //Constructors and Destructors
    Employee();
    Employee(EmpType empTypeParam=EmpType::NONE, EmpStatus empStatusParam=EmpStatus::ACTIVE);
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

    //Setter functions
    void setEmployeeType(EmpType empTypeParam);
    void setEmployeeStatus(EmpStatus empStatusParam);
    void setDOL(const std::string& dolParam);


};


#endif