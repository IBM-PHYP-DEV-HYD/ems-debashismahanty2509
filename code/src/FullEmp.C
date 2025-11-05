#include "FullEmp.H"
#include "InternEmp.H"
#include "iomanip"
#include "EmployeeIF.H"

size_t FullEmp::mSizeOfFullEmployee = 0;
uint8_t FullEmp::mMaxLeaves = 22;
FullEmp::FullEmp() : Employee(EmployeeIF::EmpType::FULLTIME), mCurrentLeaves(0), mLeaveApplied(0)
{
    genericConstCall();
}

FullEmp::FullEmp(EmpStatus empStatusParam) : Employee(EmployeeIF::EmpType::FULLTIME, empStatusParam), mCurrentLeaves(0), mLeaveApplied(0)
{
    genericConstCall();
}

void FullEmp::genericConstCall(void)
{
    mSizeOfFullEmployee++;
    std::string_view sDOJ = getDOJ();
    std::string sTodaysDate;
    getTodayDate(sTodaysDate);
    int8_t sLeftMonth;
    if(sDOJ != "NA" && sDOJ.length() == 10)
    {
        int sTodayYear = std::stoi(std::string(sTodaysDate.substr(6,4)));
        int sDOJYear = std::stoi(std::string(sDOJ.substr(6,4)));
        if(sTodayYear == sDOJYear)
        {
            sLeftMonth = 12 - std::stoi(std::string(sDOJ.substr(3,2)));
            mCurrentLeaves = (sLeftMonth * mMaxLeaves) / 12;
        }
        else
        {
            mCurrentLeaves = mMaxLeaves;
        }

    }
}

FullEmp::~FullEmp()
{
    mSizeOfFullEmployee--;
}

size_t FullEmp::getEmployeeCount()
{
    return mSizeOfFullEmployee;
}

const uint8_t FullEmp::getCurrentLeaves(void)
{
    return mCurrentLeaves;
}

void FullEmp::setLeavesApplied(const uint8_t& leavesParam)
{
    if(leavesParam > mCurrentLeaves)
    {
        std::cout << "Cannot apply for more leaves than current leaves available. Current Leaves: " << mCurrentLeaves << std::endl;
        return;
    }
    mLeaveApplied += leavesParam;
    mCurrentLeaves -= leavesParam;
}

void FullEmp::renewLeaveBalance(const uint8_t& carryForwardToNextYear)
{
    if(carryForwardToNextYear > mMaxLeaves)
    {
        std::cout << "Cannot carry forward more than max leaves. Max Leaves: " << mMaxLeaves << std::endl;
        return;
    }
    if(mCurrentLeaves > 0)
    {
        if(carryForwardToNextYear >= mCurrentLeaves)
        {
            mCurrentLeaves += mMaxLeaves;
        }
        else
        {
            mCurrentLeaves = carryForwardToNextYear + mMaxLeaves;
        }
    }
    mLeaveApplied = 0;
}

void FullEmp::addLeavesToAll(const uint8_t& leavesParam)
{
    mCurrentLeaves += leavesParam;
}

void FullEmp::setMaxLeaves(const uint8_t& maxLeavesParam)
{
    mMaxLeaves += maxLeavesParam;
}

std::ostream& operator<<(std::ostream& osParam , const FullEmp* empParam)
{
    osParam << static_cast<const Employee*>(empParam);
    osParam << std::left;
    osParam << "| " << std::setw(EmployeeIF::Clg) << "--";
    osParam << "| " << std::setw(EmployeeIF::Bnh) << "--";
    osParam << "| " << std::setw(EmployeeIF::CLeaves) << (int)empParam->mCurrentLeaves;
    osParam << "| " << std::setw(EmployeeIF::LevApp) << (int)empParam->mLeaveApplied;
    osParam << "| " << std::setw(EmployeeIF::Agncy) << "--";
    osParam.unsetf(std::ios::adjustfield);
    return osParam;
}

void convertIntern2FullTime(FullEmp* fullEmpParam, const Employee* empParam)
{
    Employee* sEmpcastFull =  dynamic_cast<Employee*>(fullEmpParam);
    sEmpcastFull->mName = empParam->mName;
    sEmpcastFull->mGender = empParam->mGender;
    sEmpcastFull->mDOB = empParam->mDOB;
    std::string_view sDOJ = sEmpcastFull->mDOJ = empParam->mDOJ;

    std::string sTodaysDate;
    fullEmpParam->getTodayDate(sTodaysDate);
    int8_t sLeftMonth;
    if(sDOJ != "NA" && sDOJ.length() == 10)
    {
        int sTodayYear = std::stoi(std::string(sTodaysDate.substr(6,4)));
        int sDOJYear = std::stoi(std::string(sDOJ.substr(6,4)));
        if(sTodayYear == sDOJYear)
        {
            sLeftMonth = 12 - std::stoi(std::string(sDOJ.substr(3,2)));
            fullEmpParam->mCurrentLeaves = (sLeftMonth * fullEmpParam->mMaxLeaves) / 12;
        }
        else
        {
            fullEmpParam->mCurrentLeaves = fullEmpParam->mMaxLeaves;
        }

    }
}