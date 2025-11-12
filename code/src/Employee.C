#include "Employee.H"
#include "iomanip"

size_t Employee::mMemberNumbers = 0;
std::string Employee::mFirstNames[10] = {"John", "Jane", "Alice", "Bob", "Charlie", "Diana", "Eve", "Frank", "Grace", "Hank"};
std::string Employee::mLastNames[10] = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez"};
Employee::Employee(Utils::EmpType empTypeParam) : mEmployeeType(empTypeParam), mEmployeeStatus(Utils::EmpStatus::ACTIVE), mGender(Utils::EmpGender::None)
{
    // Randomly generate employee type and Name
    mName = mFirstNames[rand() % 10] + " " + mLastNames[rand() % 10];
    setIDBasedOnMemberNumberAndType(mEmployeeType);
    setRandomDoj();
    setRandomGender();
    setRandomDOB();
}

void Employee::setRandomDOB(void)
{
    // set a random DOB between 20 to 60 years based on todays date
    std::string sTodayDate;
    pGetTodayDate(sTodayDate);
    mDOB += std::to_string(rand() % 28 + 1);
    mDOB.length() == 1 ? mDOB = "0" + mDOB + "-" : mDOB += "-";
    mDOB += std::to_string(rand() % 11 + 1);
    mDOB.length() == 4 ? mDOB = mDOB.substr(0, 3) + "0" + mDOB.substr(3, 1) + "-" : mDOB += "-";
    mDOB += std::to_string(std::stoi(sTodayDate.substr(6, 4)) - 20 - (rand() % 40));
}

Employee::Employee(Utils::EmpType empTypeParam, Utils::EmpStatus empStatusParam) : mEmployeeType(empTypeParam), mEmployeeStatus(empStatusParam)
{
    std::cin >> this;
    // id should be XYZ + mMemberNumbers + EmployeeType
    setIDBasedOnMemberNumberAndType(empTypeParam);
    setDOJ();
}

Employee::~Employee()
{
}

void Employee::setRandomGender(void)
{
    mGender = static_cast<Utils::EmpGender>(rand() % 2);
}

void Employee::setDOLBasedOnDOJ(bool isDOJSetParam, std::string basedOnTodayDateParam)
{
    if (isDOJSetParam == true)
    {
        if (mDOJ.length() != 10 || mEmployeeType == Utils::EmpType::NONE || mEmployeeType == Utils::EmpType::FULLTIME)
        {
            mDOL = "NA";
            mDOJ.length() != 10 ? std::cout << "DOJ is not set properly\n"
                                            << std::endl
                                : std::cout << "";
            return;
        }
        else if (mEmployeeType == Utils::EmpType::CONTRACTUAL)
        {
            mDOL = mDOJ.substr(0, 6) + std::to_string(std::stoi(mDOJ.substr(6, 4)) + 1);
            return;
        }
        else if (mEmployeeType == Utils::EmpType::INTERN)
        {
            int month = std::stoi(mDOJ.substr(3, 2));
            int year = std::stoi(mDOJ.substr(6, 4));
            month += 6;
            if (month > 12)
            {
                month -= 12;
                year += 1;
            }
            std::string monthStr = (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
            mDOL = mDOJ.substr(0, 3) + monthStr + "-" + std::to_string(year);
            return;
        }
    }
    else
    {
        if (basedOnTodayDateParam.length() != 10 || mEmployeeType == Utils::EmpType::NONE || mEmployeeType == Utils::EmpType::FULLTIME)
        {
            mDOL = "NA";
            basedOnTodayDateParam.length() != 10 ? std::cout << "DOJ is not set properly\n"
                                                             << std::endl
                                                 : std::cout << "";
            return;
        }
        else if (mEmployeeType == Utils::EmpType::CONTRACTUAL)
        {
            mDOL = basedOnTodayDateParam.substr(0, 6) + std::to_string(std::stoi(basedOnTodayDateParam.substr(6, 4)) + 1);
            return;
        }
        else if (mEmployeeType == Utils::EmpType::INTERN)
        {
            int month = std::stoi(basedOnTodayDateParam.substr(3, 2));
            int year = std::stoi(basedOnTodayDateParam.substr(6, 4));
            month += 6;
            if (month > 12)
            {
                month -= 12;
                year += 1;
            }
            std::string monthStr = (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
            mDOL = basedOnTodayDateParam.substr(0, 3) + monthStr + "-" + std::to_string(year);
            return;
        }
    }
}
void Employee::setIDBasedOnMemberNumberAndType(Utils::EmpType &empTypeParam)
{
    mID = "XYZ" + std::to_string(mMemberNumbers++);

    if (empTypeParam == Utils::EmpType::INTERN)
    {
        mID += "I";
    }
    else if (empTypeParam == Utils::EmpType::FULLTIME)
    {
        mID += "F";
    }
    else if (empTypeParam == Utils::EmpType::CONTRACTUAL)
    {
        mID += "C";
    }
    else
    {
        mID += "N";
    }
}

bool Employee::validCheck(std::istream &isParam)
{
    if (isParam.fail() == 1)
    {
        isParam.clear();
        isParam.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid type\n"
                  << std::endl;
        return false;
    }
    return true;
}

const std::string_view Employee::getName(void) const
{
    return mName;
}

const std::string_view Employee::getID(void) const
{
    return mID;
}

const std::string_view Employee::getGender(void) const
{
    if (mGender == Utils::Male)
    {
        return "Male";
    }
    else if (mGender == Utils::Female)
    {
        return "Female";
    }
    else
    {
        return "NA";
    }
}

const Utils::EmpGender &Employee::getGenderType(void) const
{
    return mGender;
}

const std::string_view Employee::getDOB(void) const
{
    return mDOB;
}

void Employee::setEmployeeType(Utils::EmpType empTypeParam)
{
    mEmployeeType = empTypeParam;
    changeIdwithEmpType();
    std::string sDate;
    pGetTodayDate(sDate);
    setDOLBasedOnDOJ(false, sDate);
}

void Employee::setEmployeeStatus(Utils::EmpStatus empStatusParam)
{
    mEmployeeStatus = empStatusParam;
}

void Employee::setDOL()
{
    std::string sDate;
    pGetTodayDate(sDate);
    mDOL = sDate;
}
void Employee::setDOJ(void)
{
    // take today date as DOJ
    pGetTodayDate(mDOJ);
    setDOLBasedOnDOJ(true);
}

void Employee::pGetTodayDate(std::string &dateParam)
{
    time_t sNow = time(0);
    tm *sLtm = localtime(&sNow);
    dateParam = (sLtm->tm_mday < 10 ? "0" : "") + std::to_string(sLtm->tm_mday) + "-" +
                (sLtm->tm_mon + 1 < 10 ? "0" : "") + std::to_string(sLtm->tm_mon + 1) + "-" +
                std::to_string(1900 + sLtm->tm_year);
}

void Employee::changeIdwithEmpType(void)
{
    mID = mID.substr(0, mID.length() - 1); // Remove the last character
    if (mEmployeeType == Utils::EmpType::INTERN)
    {
        mID += "I";
    }
    else if (mEmployeeType == Utils::EmpType::FULLTIME)
    {
        mID += "F";
    }
    else if (mEmployeeType == Utils::EmpType::CONTRACTUAL)
    {
        mID += "C";
    }
    else
    {
        mID += "N";
    }
}

const std::string_view Employee::getDOJ(void) const
{
    return mDOJ;
}

const std::string_view Employee::getDOL(void) const
{
    return mDOL;
}

size_t Employee::getEmployeeCount()
{
    return mMemberNumbers;
}

std::string_view Employee::getAgency(void) const
{
    return "";
}

const std::string_view &Employee::getBranch(void) const
{
    return "";
}

std::string Employee::getCollege(void) const
{
    return "";
}

const uint8_t Employee::getCurrentLeaves(void)
{
    return 0;
}

void Employee::setLeavesApplied(const uint8_t &leavesParam)
{
    return;
}

void Employee::renewLeaveBalance(const uint8_t &carryForwardToNextYearParam)
{
    return;
}

void Employee::addLeavesToAll(const uint8_t &leavesParam)
{
    return;
}

const Utils::EmpType Employee::getEmployeeType(void) const
{
    return mEmployeeType;
}

const Utils::EmpStatus Employee::getEmployeeStatus(void) const
{
    return mEmployeeStatus;
}

void Employee::setRandomDoj(void)
{
    // Randomly DOJ generation based on Employee type
    if (mEmployeeType == Utils::EmpType::FULLTIME)
    {
        mDOJ += std::to_string(rand() % 28 + 1);
        mDOJ.length() == 1 ? mDOJ = "0" + mDOJ + "-" : mDOJ += "-";
        mDOJ += std::to_string(rand() % 11 + 1);
        mDOJ.length() == 4 ? mDOJ = mDOJ.substr(0, 3) + "0" + mDOJ.substr(3, 1) + "-" : mDOJ += "-";
        mDOJ += std::to_string(rand() % 10 + 2015);
    }
    else if (mEmployeeType == Utils::EmpType::INTERN)
    {
        // Based on current date - 6 months randomly generate
        std::string sTodayDate;
        pGetTodayDate(sTodayDate);
        int sDay = rand() % 28;
        int sMonth = std::stoi(sTodayDate.substr(3, 2)) - rand() % 5;
        int sYear = std::stoi(sTodayDate.substr(6, 4));
        if (sMonth <= 0)
        {
            sMonth += 12;
            sYear -= 1;
        }
        mDOJ = sDay < 10 ? "0" + std::to_string(sDay) + "-" : std::to_string(sDay) + "-";
        mDOJ += sMonth < 10 ? "0" + std::to_string(sMonth) + "-" : std::to_string(sMonth) + "-";
        mDOJ += std::to_string(sYear);
    }
    else if (mEmployeeType == Utils::EmpType::CONTRACTUAL)
    {
        // Based on current date - 6 months randomly generate
        std::string sTodayDate;
        pGetTodayDate(sTodayDate);
        int sDay = rand() % 28;
        int sMonth = std::stoi(sTodayDate.substr(3, 2)) - rand() % 11;
        int sYear = std::stoi(sTodayDate.substr(6, 4));
        if (sMonth <= 0)
        {
            sMonth += 12;
            sYear -= 1;
        }
        mDOJ = sDay < 10 ? "0" + std::to_string(sDay) + "-" : std::to_string(sDay) + "-";
        mDOJ += sMonth < 10 ? "0" + std::to_string(sMonth) + "-" : std::to_string(sMonth) + "-";
        mDOJ += std::to_string(sYear);
    }
    setDOLBasedOnDOJ(true);
}

std::ostream &operator<<(std::ostream &osParam, const Employee *empParam)
{
    osParam << std::left
            << "| " << std::setw(Utils::Name) << empParam->mName
            << "| " << std::setw(Utils::Id) << empParam->mID
            << "| " << std::setw(Utils::Gender) << empParam->getGender()
            << "| " << std::setw(Utils::Dob) << empParam->mDOB
            << "| " << std::setw(Utils::Doj) << empParam->mDOJ
            << "| " << std::setw(Utils::Dol) << empParam->mDOL
            << "| " << std::setw(Utils::Type);
    switch (empParam->mEmployeeType)
    {
    case Utils::EmpType::FULLTIME:
        osParam << "Full Time";
        break;
    case Utils::EmpType::INTERN:
        osParam << "Intern";
        break;
    case Utils::EmpType::CONTRACTUAL:
        osParam << "Contractual";
        break;
    default:
        osParam << "None";
        break;
    }
    osParam << "| " << std::setw(Utils::Status);
    switch (empParam->mEmployeeStatus)
    {
    case Utils::EmpStatus::ACTIVE:
        osParam << "Active";
        break;
    case Utils::EmpStatus::INACTIVE:
        osParam << "Inactive";
        break;
    case Utils::EmpStatus::RESIGNED:
        osParam << "Resigned";
        break;
    default:
        osParam << "None";
        break;
    }

    if(empParam->getEmployeeStatus() == Utils::RESIGNED)
    {
        osParam << "| " << std::setw(Utils::Clg) << "--";
        osParam << "| " << std::setw(Utils::Bnh) << "--";
        osParam << "| " << std::setw(Utils::CLeaves) << "--";
        osParam << "| " << std::setw(Utils::LevApp) << "--";
        osParam << "| " << std::setw(Utils::Agncy) << "--";
        osParam << std::setw(Utils::LeftMar) << " " << "|";
    }
    osParam.unsetf(std::ios::adjustfield);
    return osParam;
}

std::istream &operator>>(std::istream &isParam, Employee *empParam)
{
    std::cout << "Enter Name: ";
    std::getline(std::cin >> std::ws, empParam->mName);

    char sGender;
    std::cout << "Enter the Gender (M/F): ";
    std::cin >> sGender;
    if (empParam->validCheck(std::cin) == false)
    {
        empParam->mGender = Utils::EmpGender::None;
    }
    if (sGender == 'M' || sGender == 'm')
    {
        empParam->mGender = Utils::EmpGender::Male;
    }
    else if (sGender == 'F' || sGender == 'f')
    {
        empParam->mGender = Utils::EmpGender::Female;
    }

    std::cout << "Enter DOB (DD-MM-YYYY): ";
    std::getline(std::cin >> std::ws, empParam->mDOB);
    return isParam;
}