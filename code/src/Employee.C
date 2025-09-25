#include "Employee.H"

size_t Employee::mMemberNumbers = 0;

Employee::Employee() : mEmployeeType(EmpType::NONE), mEmployeeStatus(EmpStatus::ACTIVE), mGender('N'), mDOB("NA")
{
    std::cout<< "Enter Name: ";
    std::getline(std::cin>>std::ws,mName);
    setIDBasedOnMemberNumberAndType(mEmployeeType);
    setDOJ();
}
Employee::Employee(EmpType empTypeParam, EmpStatus empStatusParam) : mEmployeeType(empTypeParam), mEmployeeStatus(empStatusParam)
{
    std::cout<< "Enter Name: ";
    std::getline(std::cin>>std::ws,mName);

    //id should be XYZ + mMemberNumbers + EmployeeType
    setIDBasedOnMemberNumberAndType(empTypeParam);
    

    std::cout<<"Enter the Gender (M/F): ";
    std::cin>>mGender;
    if(validCheck(std::cin) ==false)
    {
        mGender = 'N';
    }

    std::cout<<"Enter DOB (DD-MM-YYYY): ";
    std::getline(std::cin>>std::ws,mDOB);

    setDOJ();
}

Employee::~Employee()
{

}

void Employee::setDOLBasedOnDOJ(bool isDOJSet, std::string basedOnTodayDate = "")
{
    if(isDOJSet == true)
    {
        if(mDOJ.length() != 10 || mEmployeeType == EmpType::NONE || mEmployeeType == EmpType::FULLTIME)
        {
            mDOL = "NA";
            mDOJ.length() != 10 ? std::cout<<"DOJ is not set properly\n"<<std::endl : std::cout<<"DOL is set to NA\n"<<std::endl;
            return;
        }
        else if(mEmployeeType == EmpType::CONTRACTUAL)
        {
            mDOL = mDOJ.substr(0,6) + std::to_string(std::stoi(mDOJ.substr(6,4)) + 1);
            return;
        }
        else if(mEmployeeType == EmpType::INTERN)
        {
            int month = std::stoi(mDOJ.substr(3,2));
            int year = std::stoi(mDOJ.substr(6,4));
            month += 6;
            if(month > 12)
            {
                month -= 12;
                year += 1;
            }
            std::string monthStr = (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
            mDOL = mDOJ.substr(0,3) + monthStr + "-" + std::to_string(year);
            return;
        }
    }
    else
    {
        if(basedOnTodayDate.length() != 10 || mEmployeeType == EmpType::NONE || mEmployeeType == EmpType::FULLTIME)
        {
            mDOL = "NA";
            basedOnTodayDate.length() != 10 ? std::cout<<"DOJ is not set properly\n"<<std::endl : std::cout<<"DOL is set to NA\n"<<std::endl;
            return;
        }
        else if(mEmployeeType == EmpType::CONTRACTUAL)
        {
            mDOL = basedOnTodayDate.substr(0,6) + std::to_string(std::stoi(basedOnTodayDate.substr(6,4)) + 1);
            return;
        }
        else if(mEmployeeType == EmpType::INTERN)
        {
            int month = std::stoi(basedOnTodayDate.substr(3,2));
            int year = std::stoi(basedOnTodayDate.substr(6,4));
            month += 6;
            if(month > 12)
            {
                month -= 12;
                year += 1;
            }
            std::string monthStr = (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
            mDOL = basedOnTodayDate.substr(0,3) + monthStr + "-" + std::to_string(year);
            return;
        }
    }
}
void Employee::setIDBasedOnMemberNumberAndType(EmpType& empTypeParam)
{
    mID = "XYZ" + std::to_string(mMemberNumbers++);

    if(empTypeParam == EmpType::INTERN)
    {
        mID += "I";
    }
    else if(empTypeParam == EmpType::FULLTIME)
    {
        mID += "F";
    }
    else if(empTypeParam == EmpType::CONTRACTUAL)
    {
        mID += "C";
    }
    else
    {
        mID += "N";
    }
}

bool Employee::validCheck(std::istream& isParam)
{
    if(isParam.fail() == 1)
    {
        isParam.clear();
        isParam.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout<<"Please enter a valid type\n"<<std::endl;
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
    if(mGender=='M')
    {
        return "Male";
    }
    else if(mGender=='F')
    {
        return "Female";
    }
    else
    {
        return "NA";
    }
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
    getTodayDate(sDate);
    setDOLBasedOnDOJ(false,sDate);
}

void Employee::setEmployeeStatus(EmpStatus empStatusParam) 
{ 
    mEmployeeStatus = empStatusParam; 
}

void Employee::setDOL(const std::string& dolParam) 
{ 
    mDOL = dolParam; 
}
void Employee::setDOJ(void)
{
    // take today date as DOJ
    getTodayDate(mDOJ);
    setDOLBasedOnDOJ(true);
}

void Employee::getTodayDate(std::string& dateParam)
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
    if(mEmployeeType == EmpType::INTERN)
    {
        mID += "I";
    }
    else if(mEmployeeType == EmpType::FULLTIME)
    {
        mID += "F";
    }
    else if(mEmployeeType == EmpType::CONTRACTUAL)
    {
        mID += "C";
    }
    else
    {
        mID += "N";
    }
}