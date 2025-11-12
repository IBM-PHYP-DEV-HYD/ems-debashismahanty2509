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

Manager* Manager::getInstance(const std::string& companyNameParam, std::string_view userNameParam, std::string_view passParam)
{
    if(nullptr != mOwnPtr && nullptr != mOwnPtr->mUserName && nullptr != mOwnPtr->mPassword)
    {
        if(*(mOwnPtr->mUserName) == userNameParam && *(mOwnPtr->mPassword) == passParam)
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
        mOwnPtr->addCredentials(userNameParam, passParam);
        //std::cout<< "Manager instance created for company: " << companyNameParam << " To get the instance again, please provide credentials. If not set call default credential" << std::endl;
        return mOwnPtr;
    }
    return nullptr;
}

void Manager::addCredentials(std::string_view userNameParam, std::string_view passParam)
{
    if(nullptr==mUserName && nullptr==mPassword)
    {
        mUserName = new std::string(userNameParam);
        mPassword = new std::string(passParam);
        return;
    }
    else
    {
        std::cout << "Credentials already exist!" << std::endl;
        return;
    }
}

void Manager::addEmployee(Utils::EmpType empTypeParam)
{
    EmployeeIF* sNewEmp = nullptr;
    // Implementation to add employee based on empTypeParam
    switch (empTypeParam)
    {
        case Utils::EmpType::FULLTIME:
            mSizeOfFullTimeEmployee++;
            sNewEmp = new FullEmp();
            break;
        case Utils::EmpType::INTERN:
            mSizeOfInternEmployee++;
            sNewEmp = new InternEmp();
            break;
        case Utils::EmpType::CONTRACTUAL:
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

void Manager::addRandomEmp(uint16_t numOfEmpParam)
{
    for(uint8_t i=0; i<numOfEmpParam; i++)
    {
        addEmployee(static_cast<Utils::EmpType>(rand() % 3));
    }
}

void Manager::removeEmployee(const std::string& empIDParam,bool isResignedReqParam)
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
            sEmp->setEmployeeStatus(Utils::RESIGNED);
            sEmp->setDOL();
            EmployeeIF* newREmp = new Employee(*static_cast<Employee*>(sEmp));
            if(nullptr==mResignedEmployeeList && isResignedReqParam)
            {
                mResignedEmployeeList = new EDLL<EmployeeIF*>(1, newREmp);
            }
            else if(isResignedReqParam)
            {
                mResignedEmployeeList->pushBack(newREmp);
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

void Manager::displayEmployeeType(Utils::EmpType empTypeParam)
{
    // Implementation to display employees based on empTypeParam
    bool isTableCalled = false;
    if(NULL != mEmployeeList && !mEmployeeList->empty())
    {
        for(size_t sItr=1;sItr<=mEmployeeList->size();sItr++)
        {
            EmployeeIF* sEmp = (*mEmployeeList)[sItr];
            Utils::EmpType sEmpType = sEmp->getEmployeeType();
            if(sEmpType == empTypeParam)
            {
                if(!isTableCalled)
                {
                    isTableCalled = true;
                    designForAll();
                }
                if(sEmpType == Utils::EmpType::FULLTIME)
                {
                    std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::INTERN)
                {
                    std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::CONTRACTUAL)
                {
                    std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
                }
            }
        }
    }
    if(NULL != mResignedEmployeeList && !mResignedEmployeeList->empty())
    {
        for(size_t sItr=1;sItr<=mResignedEmployeeList->size();sItr++)
        {
            EmployeeIF* sEmp = (*mResignedEmployeeList)[sItr];
            Utils::EmpType sEmpType = sEmp->getEmployeeType();
            if(sEmpType == empTypeParam)
            {
                if(!isTableCalled)
                {
                    isTableCalled = true;
                    designForAll();
                }
                if(sEmpType == Utils::EmpType::FULLTIME)
                {
                    std::cout << static_cast<const Employee*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::INTERN)
                {
                    std::cout << static_cast<const Employee*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::CONTRACTUAL)
                {
                    std::cout << static_cast<const Employee*>(sEmp) << std::endl;
                }
            }
        }
    }
    if(isTableCalled)
    {
        displayEndLine();
    }
    else
    {
        std::cout << "No employees found" << std::endl;
    }
}

void Manager::designForAll(void)
{
    using namespace std;  // only applies inside this fuction()
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << left
        << "| " << setw(Utils::Name) << "Name"
        << "| " << setw(Utils::Id) << "ID"
        << "| " << setw(Utils::Gender) << "Gender"
        << "| " << setw(Utils::Dob) << "DOB"
        << "| " << setw(Utils::Doj) << "DOJ"
        << "| " << setw(Utils::Dol) << "DOL"
        << "| " << setw(Utils::Type) << "Type"
        << "| " << setw(Utils::Status) << "Status"
        << "| " << setw(Utils::Clg) << "College"
        << "| " << setw(Utils::Bnh) << "Branch"
        << "| " << setw(Utils::CLeaves) << "Current Leaves"
        << "| " << setw(Utils::LevApp) << "Leaves Applied"
        << "| " << setw(Utils::Agncy) << "Agency"
        << setw(Utils::LeftMar) << " " << "|"
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
        Utils::EmpType sEmpType = sEmp->getEmployeeType();
        if(sEmpType == Utils::EmpType::FULLTIME)
        {
            std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
        }
        else if(sEmpType == Utils::EmpType::INTERN)
        {
            std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
        }
        else if(sEmpType == Utils::EmpType::CONTRACTUAL)
        {
            std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
        }
    }
}


void Manager::displayAllEmployee(void)
{
    // Implementation to display all employees
    bool isTableCalled = false;

    if(NULL != mEmployeeList && !mEmployeeList->empty())
    {
        isTableCalled = true;
        designForAll();
        for(size_t sItr=1;sItr<=mEmployeeList->size();sItr++)
        {
            EmployeeIF* sEmp = (*mEmployeeList)[sItr];
            const Utils::EmpType sEmpType = sEmp->getEmployeeType();
            if(sEmpType == Utils::EmpType::FULLTIME)
            {
                std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
            }
            else if(sEmpType == Utils::EmpType::INTERN)
            {
                std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
            }
            else if(sEmpType == Utils::EmpType::CONTRACTUAL)
            {
                std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
            }
        }
    }
    if(NULL != mResignedEmployeeList && !mResignedEmployeeList->empty())
    {
        if(!isTableCalled)
        {
            designForAll();
            isTableCalled = true;
        }
        for(size_t sItr=1;sItr<=mResignedEmployeeList->size();sItr++)
        {
            EmployeeIF* sEmp = (*mResignedEmployeeList)[sItr];
            const Utils::EmpType sEmpType = sEmp->getEmployeeType();
            if(sEmpType == Utils::EmpType::FULLTIME)
            {
                std::cout << static_cast<const Employee*>(sEmp) << std::endl;
            }
            else if(sEmpType == Utils::EmpType::INTERN)
            {
                std::cout << static_cast<const Employee*>(sEmp) << std::endl;
            }
            else if(sEmpType == Utils::EmpType::CONTRACTUAL)
            {
                std::cout << static_cast<const Employee*>(sEmp) << std::endl;
            }
        }
    }
    if(isTableCalled)
    {
        displayEndLine();
    }
    else
    {
        std::cout << "No employees found" << std::endl;
    }
}

bool Manager::isEmpEmpty(void)
{
    return ((nullptr == mEmployeeList) || mEmployeeList->empty());
}

void Manager::searchWithID(const std::string& empIDParam)
{
    // Implementation to search employee based on empIDParam
    bool isTableCalled = false;
    bool isFound = false;
    if(NULL != mEmployeeList && !mEmployeeList->empty())
    {
        for(size_t sItr=1;sItr<=mEmployeeList->size();sItr++)
        {
            EmployeeIF* sEmp = (*mEmployeeList)[sItr];
            Utils::EmpType sEmpType = sEmp->getEmployeeType();
            if(sEmp->getID() == empIDParam)
            {
                isTableCalled = true;
                isFound = true;
                designForAll();
                if(sEmpType == Utils::EmpType::FULLTIME)
                {
                    std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::INTERN)
                {
                    std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::CONTRACTUAL)
                {
                    std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
                }
                break;
            }
        }
    }
    if( !isFound && NULL != mResignedEmployeeList && !mResignedEmployeeList->empty())
    {
        for(size_t sItr=1;sItr<=mResignedEmployeeList->size();sItr++)
        {
            EmployeeIF* sEmp = (*mResignedEmployeeList)[sItr];
            Utils::EmpType sEmpType = sEmp->getEmployeeType();
            if(sEmp->getID() == empIDParam)
            {
                if(!isTableCalled)
                {
                    isTableCalled = true;
                    designForAll();
                }
                isFound = true;
                if(sEmpType == Utils::EmpType::FULLTIME)
                {
                    std::cout << static_cast<const Employee*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::INTERN)
                {
                    std::cout << static_cast<const Employee*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::CONTRACTUAL)
                {
                    std::cout << static_cast<const Employee*>(sEmp) << std::endl;
                }
                break;
            }
        }
    }
    if(isTableCalled)
    {
        displayEndLine();
    }
    if(!isFound)
    {
        std::cout << "Employee with ID " << empIDParam << " not found!" << std::endl;
    }
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
        Utils::EmpType sEmpType = sEmp->getEmployeeType();
        if(sEmp->getID() == empIdParam && sEmpType == Utils::EmpType::INTERN)
        {
            return sEmp;
        }
    }
    return NULL;
}

void Manager::searchWithGender(const Utils::EmpGender& sEmpGenderParam)
{
    // Implementation to search employee based on sEmpGenderParam
    bool isTableCalled = false;
    if(NULL != mEmployeeList && !mEmployeeList->empty())
    {
        for(size_t sItr=1;sItr<=mEmployeeList->size();sItr++)
        {
            EmployeeIF* sEmp = (*mEmployeeList)[sItr];
            Utils::EmpType sEmpType = sEmp->getEmployeeType();
            if(sEmp->getGenderType() == sEmpGenderParam)
            {
                if(!isTableCalled)
                {
                    isTableCalled = true;
                    designForAll();
                }
                if(sEmpType == Utils::EmpType::FULLTIME)
                {
                    std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::INTERN)
                {
                    std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::CONTRACTUAL)
                {
                    std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
                }
            }
        }
    }
    if(NULL != mResignedEmployeeList && !mResignedEmployeeList->empty())
    {
        for(size_t sItr=1;sItr<=mResignedEmployeeList->size();sItr++)
        {
            EmployeeIF* sEmp = (*mResignedEmployeeList)[sItr];
            Utils::EmpType sEmpType = sEmp->getEmployeeType();
            if(sEmp->getGenderType() == sEmpGenderParam)
            {
                if(!isTableCalled)
                {
                    isTableCalled = true;
                    designForAll();
                }
                if(sEmpType == Utils::EmpType::FULLTIME)
                {
                    std::cout << static_cast<const Employee*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::INTERN)
                {
                    std::cout << static_cast<const Employee*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::CONTRACTUAL)
                {
                    std::cout << static_cast<const Employee*>(sEmp) << std::endl;
                }
            }
        }
    }
    if(isTableCalled)
    {
        displayEndLine();
    }
    else
    {
        std::cout << "No employees found with this gender" << std::endl;
    }
}

void Manager::searchWithStatus(const Utils::EmpStatus & sEmpStatusParam)
{
    // Implementation to search employee based on sEmpStatusParam
    if(nullptr==mEmployeeList && nullptr == mResignedEmployeeList)
    {
        std::cout << "No employees to search!" << std::endl;
        return;
    }
    size_t max_size = 0;
    bool isTableCalled = false;
    //find gretter size between mEmployeeList and mResignedEmployeeList
    findSizeInEmp(max_size);
    for(size_t sItr=1;sItr<=max_size;sItr++)
    {
        EmployeeIF* sEmp = nullptr;
        if(sEmpStatusParam == Utils::RESIGNED)
        {
            sEmp = (*mResignedEmployeeList)[sItr];
        }
        else
        {
            sEmp = (*mEmployeeList)[sItr];
        }

        if(nullptr != sEmp)
        {
            Utils::EmpType sEmpType = sEmp->getEmployeeType();
            if(sEmp->getEmployeeStatus() == sEmpStatusParam)
            {
                if(!isTableCalled)
                {
                    isTableCalled = true;
                    designForAll();
                }
                displayEmpBasedOnType(sEmp,sEmpType,sEmpStatusParam);
            }
        }
        else
        {
            break;
        }
    }
    if(isTableCalled)
    {
        displayEndLine();
    }
    else
    {
        std::cout << "No employees found" << std::endl;
    }
}

void Manager::findSizeInEmp(size_t& sEmpSizeParam)
{
    if(NULL != mResignedEmployeeList && NULL != mEmployeeList)
    {
        sEmpSizeParam = std::max(mEmployeeList->size(), mResignedEmployeeList->size());
    }
    else if(NULL != mEmployeeList)
    {
        sEmpSizeParam = mEmployeeList->size();
    }
    else
    {
        sEmpSizeParam = 0;
    }
}

void Manager::displayEndLine(void)
{
    std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void Manager::displayEmpBasedOnType(const EmployeeIF* const sEmpParam,const Utils::EmpType& sEmpTypeParam, const Utils::EmpStatus& sEmpStatusParam)
{
    if(sEmpTypeParam == Utils::EmpType::FULLTIME)
    {
        (sEmpStatusParam == Utils::RESIGNED) ?
        std::cout << static_cast<const Employee*>(sEmpParam) << std::endl
        :
        std::cout << static_cast<const FullEmp*>(sEmpParam) << std::endl;
    }
    else if(sEmpTypeParam == Utils::EmpType::INTERN)
    {
        (sEmpStatusParam == Utils::RESIGNED) ?
        std::cout << static_cast<const Employee*>(sEmpParam) << std::endl
        :
        std::cout << static_cast<const InternEmp*>(sEmpParam) << std::endl;
    }
    else if(sEmpTypeParam == Utils::EmpType::CONTRACTUAL)
    {
        (sEmpStatusParam == Utils::RESIGNED) ?
        std::cout << static_cast<const Employee*>(sEmpParam) << std::endl
        :
        std::cout << static_cast<const ContEmp*>(sEmpParam) << std::endl;
    }
}
void Manager::searchWithName(const std::string& sEmpNameParam)
{
    // Implementation to search employee based on sEmpStatusParam
    bool isTableCalled = false;
    if(NULL != mEmployeeList && !mEmployeeList->empty())
    {
        for(size_t sItr=1;sItr<=mEmployeeList->size();sItr++)
        {
            EmployeeIF* sEmp = (*mEmployeeList)[sItr];
            Utils::EmpType sEmpType = sEmp->getEmployeeType();
            if(sEmp->getName().find(sEmpNameParam) != std::string::npos)
            {
                if(!isTableCalled)
                {
                    isTableCalled = true;
                    designForAll();
                }
                if(sEmpType == Utils::EmpType::FULLTIME)
                {
                    std::cout << static_cast<const FullEmp*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::INTERN)
                {
                    std::cout << static_cast<const InternEmp*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::CONTRACTUAL)
                {
                    std::cout << static_cast<const ContEmp*>(sEmp) << std::endl;
                }
            }
        }
    }
    if(NULL != mResignedEmployeeList && !mResignedEmployeeList->empty())
    {
        for(size_t sItr=1;sItr<=mResignedEmployeeList->size();sItr++)
        {
            EmployeeIF* sEmp = (*mResignedEmployeeList)[sItr];
            Utils::EmpType sEmpType = sEmp->getEmployeeType();
            if(sEmp->getName().find(sEmpNameParam) != std::string::npos)
            {
                if(!isTableCalled)
                {
                    isTableCalled = true;
                    designForAll();
                }
                if(sEmpType == Utils::EmpType::FULLTIME)
                {
                    std::cout << static_cast<const Employee*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::INTERN)
                {
                    std::cout << static_cast<const Employee*>(sEmp) << std::endl;
                }
                else if(sEmpType == Utils::EmpType::CONTRACTUAL)
                {
                    std::cout << static_cast<const Employee*>(sEmp) << std::endl;
                }
            }
        }
    }
    if(isTableCalled)
    {
        displayEndLine();
    }
    else
    {
        std::cout << "No employees found with name containing: " << sEmpNameParam << std::endl;
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
        if(sEmp->getEmployeeType() == Utils::EmpType::FULLTIME)
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
        removeEmployee(empIDParam,false);
    }
    else
    {
        std::cout << "We did not found any employee with this id having a Intern type\n";
    }
}
