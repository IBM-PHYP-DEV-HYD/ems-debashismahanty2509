#include "Employee.H"
#include "iomanip"

size_t Employee::mMemberNumbers = 0;
std::string Employee::mFirstNames[10] = {"John", "Jane", "Alice", "Bob", "Charlie", "Diana", "Eve", "Frank", "Grace", "Hank"};
std::string Employee::mLastNames[10] = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez"};
Employee::Employee(EmpType empTypeParam) : mEmployeeType(empTypeParam), mEmployeeStatus(EmpStatus::ACTIVE), mGender(EmployeeIF::EmpGender::None)
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

Employee::Employee(EmpType empTypeParam, EmpStatus empStatusParam) : mEmployeeType(empTypeParam), mEmployeeStatus(empStatusParam)
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
    mGender = static_cast<EmployeeIF::EmpGender>(rand() % 2);
}

void Employee::setDOLBasedOnDOJ(bool isDOJSetParam, std::string basedOnTodayDateParam)
{
    if (isDOJSetParam == true)
    {
        if (mDOJ.length() != 10 || mEmployeeType == EmpType::NONE || mEmployeeType == EmpType::FULLTIME)
        {
            mDOL = "NA";
            mDOJ.length() != 10 ? std::cout << "DOJ is not set properly\n"
                                            << std::endl
                                : std::cout << "DOL is set to NA\n"
                                            << std::endl;
            return;
        }
        else if (mEmployeeType == EmpType::CONTRACTUAL)
        {
            mDOL = mDOJ.substr(0, 6) + std::to_string(std::stoi(mDOJ.substr(6, 4)) + 1);
            return;
        }
        else if (mEmployeeType == EmpType::INTERN)
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
        if (basedOnTodayDateParam.length() != 10 || mEmployeeType == EmpType::NONE || mEmployeeType == EmpType::FULLTIME)
        {
            mDOL = "NA";
            basedOnTodayDateParam.length() != 10 ? std::cout << "DOJ is not set properly\n"
                                                             << std::endl
                                                 : std::cout << "DOL is set to NA\n"
                                                             << std::endl;
            return;
        }
        else if (mEmployeeType == EmpType::CONTRACTUAL)
        {
            mDOL = basedOnTodayDateParam.substr(0, 6) + std::to_string(std::stoi(basedOnTodayDateParam.substr(6, 4)) + 1);
            return;
        }
        else if (mEmployeeType == EmpType::INTERN)
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
void Employee::setIDBasedOnMemberNumberAndType(EmpType &empTypeParam)
{
    mID = "XYZ" + std::to_string(mMemberNumbers++);

    if (empTypeParam == EmpType::INTERN)
    {
        mID += "I";
    }
    else if (empTypeParam == EmpType::FULLTIME)
    {
        mID += "F";
    }
    else if (empTypeParam == EmpType::CONTRACTUAL)
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
    if (mGender == EmployeeIF::Male)
    {
        return "Male";
    }
    else if (mGender == EmployeeIF::Female)
    {
        return "Female";
    }
    else
    {
        return "NA";
    }
}

const EmployeeIF::EmpGender &Employee::getGenderType(void) const
{
    return mGender;
}

const std::string_view Employee::getDOB(void) const
{
    return mDOB;
}

void Employee::setEmployeeType(EmpType empTypeParam)
{
    mEmployeeType = empTypeParam;
    changeIdwithEmpType();
    std::string sDate;
    pGetTodayDate(sDate);
    setDOLBasedOnDOJ(false, sDate);
}

void Employee::setEmployeeStatus(EmpStatus empStatusParam)
{
    mEmployeeStatus = empStatusParam;
}

void Employee::setDOL(const std::string &dolParam)
{
    mDOL = dolParam;
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
    if (mEmployeeType == EmpType::INTERN)
    {
        mID += "I";
    }
    else if (mEmployeeType == EmpType::FULLTIME)
    {
        mID += "F";
    }
    else if (mEmployeeType == EmpType::CONTRACTUAL)
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

const Employee::EmpType Employee::getEmployeeType(void) const
{
    return mEmployeeType;
}

const Employee::EmpStatus Employee::getEmployeeStatus(void) const
{
    return mEmployeeStatus;
}

void Employee::setRandomDoj(void)
{
    // Randomly DOJ generation based on Employee type
    if (mEmployeeType == EmpType::FULLTIME)
    {
        mDOJ += std::to_string(rand() % 28 + 1);
        mDOJ.length() == 1 ? mDOJ = "0" + mDOJ + "-" : mDOJ += "-";
        mDOJ += std::to_string(rand() % 11 + 1);
        mDOJ.length() == 4 ? mDOJ = mDOJ.substr(0, 3) + "0" + mDOJ.substr(3, 1) + "-" : mDOJ += "-";
        mDOJ += std::to_string(rand() % 10 + 2015);
    }
    else if (mEmployeeType == EmpType::INTERN)
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
    else if (mEmployeeType == EmpType::CONTRACTUAL)
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
            << "| " << std::setw(EmployeeIF::Name) << empParam->mName
            << "| " << std::setw(EmployeeIF::Id) << empParam->mID
            << "| " << std::setw(EmployeeIF::Gender) << empParam->getGender()
            << "| " << std::setw(EmployeeIF::Dob) << empParam->mDOB
            << "| " << std::setw(EmployeeIF::Doj) << empParam->mDOJ
            << "| " << std::setw(EmployeeIF::Dol) << empParam->mDOL
            << "| " << std::setw(EmployeeIF::Type);
    switch (empParam->mEmployeeType)
    {
    case EmployeeIF::EmpType::FULLTIME:
        osParam << "Full Time";
        break;
    case EmployeeIF::EmpType::INTERN:
        osParam << "Intern";
        break;
    case EmployeeIF::EmpType::CONTRACTUAL:
        osParam << "Contractual";
        break;
    default:
        osParam << "None";
        break;
    }
    osParam << "| " << std::setw(EmployeeIF::Status);
    switch (empParam->mEmployeeStatus)
    {
    case EmployeeIF::EmpStatus::ACTIVE:
        osParam << "Active";
        break;
    case EmployeeIF::EmpStatus::INACTIVE:
        osParam << "Inactive";
        break;
    case EmployeeIF::EmpStatus::RESIGNED:
        osParam << "Resigned";
        break;
    default:
        osParam << "None";
        break;
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
        empParam->mGender = EmployeeIF::EmpGender::None;
    }
    if (sGender == 'M' || sGender == 'm')
    {
        empParam->mGender = EmployeeIF::EmpGender::Male;
    }
    else if (sGender == 'F' || sGender == 'f')
    {
        empParam->mGender = EmployeeIF::EmpGender::Female;
    }

    std::cout << "Enter DOB (DD-MM-YYYY): ";
    std::getline(std::cin >> std::ws, empParam->mDOB);
    return isParam;
}