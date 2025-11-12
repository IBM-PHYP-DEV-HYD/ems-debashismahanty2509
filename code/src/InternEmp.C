#include "InternEmp.H"
#include "iomanip"

size_t InternEmp::mSizeOfInternEmployee = 0;


InternEmp::InternEmp() : Employee(Utils::EmpType::INTERN)
{
    mSizeOfInternEmployee++;
    mCollege = static_cast<Utils::College>(rand() % 7);
    switch(static_cast<Utils::Branch>(rand() % 3))
    {
        case Utils::CSE:
            mBranch = "CSE";
            break;
        case Utils::ECE:
            mBranch = "ECE";
            break;
        case Utils::CSIT:
            mBranch = "CSIT";
            break;
        default:
            mBranch = "NA";
            break;

    }
}

InternEmp::InternEmp(Utils::EmpStatus empStatusParam) : Employee(Utils::EmpType::INTERN, empStatusParam)
{
    mSizeOfInternEmployee++;
    std::cin >> this;
}

InternEmp::~InternEmp()
{
    mSizeOfInternEmployee--;
}

size_t InternEmp::getEmployeeCount()
{
    return mSizeOfInternEmployee;
}

std::ostream& operator<<(std::ostream& osParam, const InternEmp* emp)
{
    osParam << static_cast<const Employee*>(emp);
    osParam << std::left;
    osParam << "| " << std::setw(Utils::Clg) << emp->getCollege();
    osParam << "| " << std::setw(Utils::Bnh) << emp->getBranch();
    osParam << "| " << std::setw(Utils::CLeaves) << "--";
    osParam << "| " << std::setw(Utils::LevApp) << "--";
    osParam << "| " << std::setw(Utils::Agncy) << "--";
    osParam << std::setw(Utils::LeftMar) << " " << "|";
    osParam.unsetf(std::ios::adjustfield);
    return osParam;
}

const std::string_view& InternEmp::getBranch(void) const
{
    return mBranch;
}

std::string InternEmp::getCollege(void) const
{
    switch(mCollege)
    {
        case Utils::College::IitDelhi:
            return "IitDelhi";
        case Utils::College::IitMumbai:
            return "IitMumbai";
        case Utils::College::IitKanpur:
            return "IitKanpur";
        case Utils::College::IitHyderabad:
            return "IitHyderabad";
        case Utils::College::NitWarangal:
            return "NitWarangal";
        case Utils::College::NitTiruchi:
            return "NitTiruchi";
        case Utils::College::IiitHyderabad:
            return "IiitHyderabad";
        default:
            return "NA";
    }
}

std::istream& operator>>(std::istream& isParam, InternEmp* emp)
{
    std::cout<< "Enter College: \n1. IitDelhi\n2. IitMumbai\n3. IitKanpur\n4. IitHyderabad\n5. NitWarangal\n6. NitTiruchi\n7. IiitHyderabad\n";
    std::cout<< "Enter choice (1-7): ";
    uint8_t sCollege;
    isParam >> sCollege;
    if(emp->validCheck(isParam) == false || (sCollege < 1 || sCollege > 7))
    {
        std::cout<<"Invalid input, setting default college to IitDelhi\n"<<std::endl;
        emp->mCollege = static_cast<Utils::College>(0);
    }
    else
    {
        emp->mCollege = static_cast<Utils::College>(sCollege - 1);
    }

    std::cout<< "Enter Branch: \n1. CSE\n2. ECE\n3. CSIT\n";
    std::cout<< "Enter choice (1-3): ";
    isParam >> emp->mBranch;
    if(emp->validCheck(isParam) == false || (emp->mBranch < "1" || emp->mBranch > "3"))
    {
        std::cout<<"Invalid input, setting default branch to CSE\n"<<std::endl;
        emp->mBranch = static_cast<Utils::Branch>(0);
    }
    else
    {
        emp->mBranch = static_cast<Utils::Branch>(std::stoi(emp->mBranch) - 1);
    }

    return isParam;
}