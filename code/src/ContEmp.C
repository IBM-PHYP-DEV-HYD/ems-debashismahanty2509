#include "ContEmp.H"
#include "iomanip"

size_t ContEmp::mSizeOfContEmployee = 0;
ContEmp::ContEmp() : Employee(EmployeeIF::EmpType::CONTRACTUAL)
{
    mSizeOfContEmployee++;
    mAgency = static_cast<EmployeeIF::Agency>(rand() % 3);
}

ContEmp::ContEmp(EmpStatus empStatusParam) : Employee(EmployeeIF::EmpType::CONTRACTUAL, empStatusParam)
{
    mSizeOfContEmployee++;
    std::cin >> this;
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
    osParam << std::left;
    osParam << "| " << std::setw(EmployeeIF::Clg) << "--";
    osParam << "| " << std::setw(EmployeeIF::Bnh) << "--";
    osParam << "| " << std::setw(EmployeeIF::CLeaves) << "--";
    osParam << "| " << std::setw(EmployeeIF::LevApp) << "--";
    osParam << "| " << std::setw(EmployeeIF::Agncy) << emp->getAgency();
    osParam << std::setw(EmployeeIF::LeftMar) << " " << "|";
    osParam.unsetf(std::ios::adjustfield);
    return osParam;
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
    return isParam;
}

