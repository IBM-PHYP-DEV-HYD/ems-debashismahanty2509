#include "Manager.H"
#include <iomanip>

Manager* Manager::mOwnPtr = nullptr;

Manager::Manager(std::string companyNameParam) : mCompanyName(companyNameParam),
mEmployeeList(nullptr), mResignedEmployeeList(nullptr), mSizeOfFullTimeEmployee(0),
mSizeOfInternEmployee(0), mSizeOfContractualEmployee(0)
{

}

Manager::~Manager()
{
    if(nullptr!=mEmployeeList)
    {
        delete mEmployeeList;
        mEmployeeList = nullptr;
    }
    if(nullptr!=mResignedEmployeeList)
    {
        delete mResignedEmployeeList;
        mResignedEmployeeList = nullptr;
    }
}

Manager* Manager::getInstance(const std::string& companyNameParam, std::string_view userNameParam, std::string_view PassParam)
{
    if(nullptr != mOwnPtr && nullptr != mOwnPtr->mUserName && nullptr != mOwnPtr->mPassword)
    {
        if(*(mOwnPtr->mUserName) == userNameParam && *(mOwnPtr->mPassword) == PassParam)
        {
            return mOwnPtr;
        }
        else
        {
            std::cout << "Invalid Credentials" << std::endl;
            return nullptr;
        }
    }
    if(nullptr==mOwnPtr)
    {
        mOwnPtr = new Manager(companyNameParam);

        std::cout << "Adding Credentials" << std::endl;
        mOwnPtr->addCredentials(userNameParam, PassParam);
        //std::cout<< "Manager instance created for company: " << companyNameParam << " To get the instance again, please provide credentials. If not set call default credential" << std::endl;
        return mOwnPtr;
    }
    return nullptr;
}

void Manager::addCredentials(std::string_view userNameParam, std::string_view PassParam)
{
    if(nullptr==mUserName && nullptr==mPassword)
    {
        mUserName = new std::string(userNameParam);
        mPassword = new std::string(PassParam);
        return;
    }
    else
    {
        std::cout << "Credentials already exist!" << std::endl;
        return;
    }
}

void Manager::addEmployee(Employee::EmpType empTypeParam)
{
    EmployeeIF* sNewEmp = nullptr;
    // Implementation to add employee based on empTypeParam
    switch (empTypeParam)
    {
        case Employee::EmpType::FULLTIME:
            mSizeOfFullTimeEmployee++;
            sNewEmp = new FullEmp();
            break;
        case Employee::EmpType::INTERN:
            mSizeOfInternEmployee++;
            sNewEmp = new InternEmp();
            break;
        case Employee::EmpType::CONTRACTUAL:
            mSizeOfContractualEmployee++;
            sNewEmp = new ContEmp();
            break;
        default:
            std::cout << "Invalid Employee Type!" << std::endl;
            return;
            break;
    }
    if(nullptr==mEmployeeList)
    {
        mEmployeeList = new EDLL<EmployeeIF*>(1, sNewEmp);
        return;
    }
    mEmployeeList->pushBack(sNewEmp);
}

void Manager::addRandomEmp(uint16_t numOfEmp)
{
    for(uint8_t i=0; i<numOfEmp; i++)
    {
        addEmployee(static_cast<Employee::EmpType>(rand() % 3));
    }
}

void Manager::removeEmployee(const std::string& empIDParam)
{
    // Implementation to remove employee based on empIDParam
    bool isSuccess = false;
    if(nullptr==mEmployeeList || mEmployeeList->empty())
    {
        std::cout << "No employees to remove!" << std::endl;
        return;
    }
    for(size_t sItr=1;sItr<=mEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mEmployeeList)[sItr];
        if(sEmp->getID() == empIDParam)
        {
            if(nullptr==mResignedEmployeeList)
            {
                mResignedEmployeeList = new EDLL<EmployeeIF*>(1, sEmp);
            }
            else
            {
                mResignedEmployeeList->pushBack(sEmp);
            }
            mEmployeeList->remElementMiddle(sItr);
            isSuccess = true;
            std::cout<<"Removed Emp Successfully \n";
            break;
        }
    }
    if(isSuccess == false)
    {
        std::cout<<"Please Enter a Valid Id \n";
    }
}

void Manager::displayEmployeeType(Employee::EmpType empTypeParam)
{
    // Implementation to display employees based on empTypeParam
    if(nullptr==mEmployeeList || mEmployeeList->empty())
    {
        std::cout << "No employees to display!" << std::endl;
        return;
    }
    designForAll();
    for(size_t sItr=1;sItr<=mEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mEmployeeList)[sItr];
        Employee::EmpType sEmpType = sEmp->getEmployeeType();
        if(sEmpType == empTypeParam)
        {
            if(sEmpType == Employee::EmpType::FULLTIME)
            {
                std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
            }
            else if(sEmpType == Employee::EmpType::INTERN)
            {
                std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
            }
            else if(sEmpType == Employee::EmpType::CONTRACTUAL)
            {
                std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
            }
        }
    }
}

void Manager::designForAll(void)
{
    using namespace std;  // only applies inside this fuction()
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << left
        << "| " << setw(EmployeeIF::Name) << "Name"
        << "| " << setw(EmployeeIF::Id) << "ID"
        << "| " << setw(EmployeeIF::Gender) << "Gender"
        << "| " << setw(EmployeeIF::Dob) << "DOB"
        << "| " << setw(EmployeeIF::Doj) << "DOJ"
        << "| " << setw(EmployeeIF::Dol) << "DOL"
        << "| " << setw(EmployeeIF::Type) << "Type"
        << "| " << setw(EmployeeIF::Status) << "Status"
        << "| " << setw(EmployeeIF::Clg) << "College"
        << "| " << setw(EmployeeIF::Bnh) << "Branch"
        << "| " << setw(EmployeeIF::CLeaves) << "Current Leaves"
        << "| " << setw(EmployeeIF::LevApp) << "Leaves Applied"
        << "| " << setw(EmployeeIF::Agncy) << "Agency"
        << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout.unsetf(std::ios::adjustfield);
}

void Manager::displayResignedEmployeeList(void)
{
    // Implementation to display resigned employees
    if(nullptr==mResignedEmployeeList || mResignedEmployeeList->empty())
    {
        std::cout << "No resigned employees to display!" << std::endl;
        return;
    }
    for(size_t sItr=1;sItr<=mResignedEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mResignedEmployeeList)[sItr];
        Employee::EmpType sEmpType = sEmp->getEmployeeType();
        if(sEmpType == Employee::EmpType::FULLTIME)
        {
            std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
        }
        else if(sEmpType == Employee::EmpType::INTERN)
        {
            std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
        }
        else if(sEmpType == Employee::EmpType::CONTRACTUAL)
        {
            std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
        }
    }
}


void Manager::displayAllEmployee(void)
{
    // Implementation to display all employees
    if(nullptr==mEmployeeList || mEmployeeList->empty())
    {
        std::cout << "No employees to display!" << std::endl;
        return;
    }
    designForAll();
    for(size_t sItr=1;sItr<=mEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mEmployeeList)[sItr];
        const Employee::EmpType sEmpType = sEmp->getEmployeeType();
        if(sEmpType == Employee::EmpType::FULLTIME)
        {
            std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
        }
        else if(sEmpType == Employee::EmpType::INTERN)
        {
            std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
        }
        else if(sEmpType == Employee::EmpType::CONTRACTUAL)
        {
            std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
        }
    }
    std::cout << "\n";

}

bool Manager::isEmpEmpty(void)
{
    return ((nullptr == mEmployeeList) || mEmployeeList->empty());
}

void Manager::searchWithID(const std::string& empIDParam)
{
    // Implementation to search employee based on empIDParam
    if(nullptr==mEmployeeList || mEmployeeList->empty())
    {
        std::cout << "No employees to search!" << std::endl;
        return;
    }
    for(size_t sItr=1;sItr<=mEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mEmployeeList)[sItr];
        Employee::EmpType sEmpType = sEmp->getEmployeeType();
        if(sEmp->getID() == empIDParam)
        {
            designForAll();
            if(sEmpType == Employee::EmpType::FULLTIME)
            {
                std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
            }
            else if(sEmpType == Employee::EmpType::INTERN)
            {
                std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
            }
            else if(sEmpType == Employee::EmpType::CONTRACTUAL)
            {
                std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
            }
            return;
        }
    }
    std::cout << "Employee with ID " << empIDParam << " not found!" << std::endl;
}

EmployeeIF* Manager::searchIDIntern(const std::string& empIdParam)
{
    // Implementation to search employee based on empIDParam
    if(nullptr==mEmployeeList || mEmployeeList->empty())
    {
        std::cout << "No employees to search!" << std::endl;
        return NULL;
    }
    for(size_t sItr=1;sItr<=mEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mEmployeeList)[sItr];
        Employee::EmpType sEmpType = sEmp->getEmployeeType();
        if(sEmp->getID() == empIdParam && sEmpType == Employee::EmpType::INTERN)
        {
            return sEmp;
        }
    }
    return NULL;
}

void Manager::searchWithGender(const EmployeeIF::EmpGender& sEmpGenderParam)
{
    // Implementation to search employee based on sEmpGenderParam
    if(nullptr==mEmployeeList || mEmployeeList->empty())
    {
        std::cout << "No employees to search!" << std::endl;
        return;
    }
    designForAll();
    for(size_t sItr=1;sItr<=mEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mEmployeeList)[sItr];
        Employee::EmpType sEmpType = sEmp->getEmployeeType();
        if(sEmp->getGenderType() == sEmpGenderParam)
        {
            if(sEmpType == Employee::EmpType::FULLTIME)
            {
                std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
            }
            else if(sEmpType == Employee::EmpType::INTERN)
            {
                std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
            }
            else if(sEmpType == Employee::EmpType::CONTRACTUAL)
            {
                std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
            }
        }
    }
}

void Manager::searchWithStatus(const EmployeeIF::EmpStatus & sEmpStatusParam)
{
    // Implementation to search employee based on sEmpStatusParam
    if(nullptr==mEmployeeList || mEmployeeList->empty())
    {
        std::cout << "No employees to search!" << std::endl;
        return;
    }
    designForAll();
    for(size_t sItr=1;sItr<=mEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mEmployeeList)[sItr];
        Employee::EmpType sEmpType = sEmp->getEmployeeType();
        if(sEmp->getEmployeeStatus() == sEmpStatusParam)
        {
            if(sEmpType == Employee::EmpType::FULLTIME)
            {
                std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
            }
            else if(sEmpType == Employee::EmpType::INTERN)
            {
                std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
            }
            else if(sEmpType == Employee::EmpType::CONTRACTUAL)
            {
                std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
            }
        }
    }
}

void Manager::searchWithName(const std::string& sEmpNameParam)
{
    // Implementation to search employee based on sEmpStatusParam
    if(nullptr==mEmployeeList || mEmployeeList->empty())
    {
        std::cout << "No employees to search!" << std::endl;
        return;
    }
    designForAll();
    for(size_t sItr=1;sItr<=mEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mEmployeeList)[sItr];
        Employee::EmpType sEmpType = sEmp->getEmployeeType();
        if(sEmp->getName().find(sEmpNameParam) != std::string::npos)
        {
            if(sEmpType == Employee::EmpType::FULLTIME)
            {
                std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
            }
            else if(sEmpType == Employee::EmpType::INTERN)
            {
                std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
            }
            else if(sEmpType == Employee::EmpType::CONTRACTUAL)
            {
                std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
            }
        }
    }
}

void Manager::addLeavesToAll(const uint8_t& leavesParam)
{
    FullEmp::setMaxLeaves(leavesParam);
    if(nullptr==mEmployeeList || mEmployeeList->empty())
    {
        std::cout << "No employees to add leaves!" << std::endl;
        return;
    }
    for(size_t sItr=1;sItr<=mEmployeeList->size();sItr++)
    {
        EmployeeIF* sEmp = (*mEmployeeList)[sItr];
        if(sEmp->getEmployeeType() == Employee::EmpType::FULLTIME)
        {
            sEmp->addLeavesToAll(leavesParam);
        }
    }
}

void Manager::conv2Full(const std::string& empIDParam)
{
    EmployeeIF* sInternEmp = searchIDIntern(empIDParam);
    if(NULL != sInternEmp)
    {
        EmployeeIF* sNewEmp =  new FullEmp();
        convertIntern2FullTime(dynamic_cast<FullEmp*>(sNewEmp),dynamic_cast<Employee*>(sInternEmp));
        if(nullptr==mEmployeeList)
        {
            mEmployeeList = new EDLL<EmployeeIF*>(1, sNewEmp);
            return;
        }
        mEmployeeList->pushBack(sNewEmp);
        removeEmployee(empIDParam);
    }
    else
    {
        std::cout << "We did not found any employee with this id having a Intern type\n";
    }
}
