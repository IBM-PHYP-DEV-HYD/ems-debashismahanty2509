#ifndef _CONTEMP_H_
#define _CONTEMP_H_
#include <iostream>
#include "Employee.H"

//Declaration
class EmployeeIF;
class Employee;

class ContEmp : public Employee
{
    public:
    ContEmp(EmployeeIF::InputType empInputTypeParam);
    virtual ~ContEmp();
    size_t getEmployeeCount() override;
    std::string_view getAgency(void) const override;
    friend std::ostream& operator<<(std::ostream& osParam , const ContEmp* empParam);
    friend std::istream& operator>>(std::istream& isParam , ContEmp* empParam);

    private:
    static size_t mSizeOfContEmployee;
    EmployeeIF::Agency mAgency;
};
size_t ContEmp::mSizeOfContEmployee = 0;
ContEmp::ContEmp(EmployeeIF::InputType empInputTypeParam) : Employee(EmployeeIF::EmpType::CONTRACTUAL)
{
    mSizeOfContEmployee++;
    if(empInputTypeParam == EmployeeIF::InputType::USERINPUT)
    {
        std::cin >> this;
    }
    else if(empInputTypeParam == EmployeeIF::InputType::RANDOM)
    {
        mAgency = static_cast<EmployeeIF::Agency>(rand() % 3);
    }
}

ContEmp::~ContEmp()
{

}

size_t ContEmp::getEmployeeCount()
{
    return mSizeOfContEmployee;
}

std::string_view ContEmp::getAgency(void) const
{
    switch(mAgency)
    {
        case EmployeeIF::Agency::Avengers:
            return "Avengers";
            break;
        case EmployeeIF::Agency::JusticeLeague:
            return "JusticeLeague";
            break;
        case EmployeeIF::Agency::XMen:
            return "XMen";
            break;
        default:
            return "NA";
            break;
    }
}

std::ostream& operator<<(std::ostream& osParam , const ContEmp* emp)
{
    osParam << static_cast<const Employee*>(emp);
}

std::istream& operator>>(std::istream& isParam , ContEmp* emp)
{
    std::cout << "Select Agency from the following options:" << std::endl;
    std::cout << "1. Avengers\n 2. JusticeLeague\n 3. XMen" << std::endl;
    uint8_t sAgencyInput = 0;
    isParam >> sAgencyInput;
    if(emp->validCheck(isParam) == false || sAgencyInput < 1 || sAgencyInput > 3)
    {
        std::cout << "Invalid input. Setting dafult to Avengers" << std::endl;
        emp->mAgency = static_cast<EmployeeIF::Agency>(0);
    }
    else
    {
        emp->mAgency = static_cast<EmployeeIF::Agency>(sAgencyInput - 1);
    }
    
}


#endif