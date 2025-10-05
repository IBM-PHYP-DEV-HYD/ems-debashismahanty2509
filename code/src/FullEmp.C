#include "FullEmp.H"

size_t FullEmp::mSizeOfFullEmployee = 0;
uint8_t FullEmp::mMaxLeaves = 22;
FullEmp::FullEmp() : Employee(EmployeeIF::EmpType::FULLTIME), mCurrentLeaves(0), mLeaveApplied(0)
{
    mSizeOfFullEmployee++;
    std::string_view sDOJ = getDOJ();

    if(sDOJ != "NA" && sDOJ.length() == 10)
    {
        int8_t sLeftMonth = 12 - std::stoi(std::string(sDOJ.substr(3,2)));
        mCurrentLeaves = (sLeftMonth * mMaxLeaves) / 12;
    }
}

FullEmp::FullEmp(EmpStatus empStatusParam) : Employee(EmployeeIF::EmpType::FULLTIME, empStatusParam), mCurrentLeaves(0), mLeaveApplied(0)
{
    mSizeOfFullEmployee++;
    std::string_view sDOJ = getDOJ();

    if(sDOJ != "NA" && sDOJ.length() == 10)
    {
        int8_t sLeftMonth = 12 - std::stoi(std::string(sDOJ.substr(3,2)));
        mCurrentLeaves = (sLeftMonth * mMaxLeaves) / 12;
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

std::ostream& operator<<(std::ostream& osParam , const FullEmp* empParam)
{
    osParam << static_cast<const Employee*>(empParam);
    osParam << "Current Leaves: " << empParam->mCurrentLeaves << std::endl;
    osParam << "Leaves Applied: " << empParam->mLeaveApplied << std::endl;
    return osParam;
}