#include "iostream"
#include "EMS.H"

bool EMS::validCheck(std::istream& isParam)
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
void EMS::handleMenu(void)
{
    //NULL check
    uint16_t sChoice = 0;
    while(pDisplayMainMenu(sChoice) && sChoice != Exit)
    {
        switch(sChoice)
        {
            case AddAnEmployee:
                {
                    Utils::EmpType sEmpType;
                    int16_t sNumOfEmp = 0;
                    Opeartion sType = pDisplayAddEmployeeMenu(sChoice,sEmpType,sNumOfEmp);
                    if(sType == AddEmpRandom)
                    {
                        mManagerPtr->addRandomEmp(sNumOfEmp);
                    }
                    else if(sType == AddEmpWithType)
                    {
                        mManagerPtr->addEmployee(sEmpType);
                    }
                }
                break;
            case RemoveAnEmployee:
                {
                    if(mManagerPtr->isEmpEmpty())
                    {
                        printf("There is no Emp found, So please add an employee\n");
                        break;
                    }
                    std::string sId;
                    std::cout << "Enter the Emp Id: \n";
                    std::getline(std::cin>>std::ws,sId);
                    mManagerPtr->removeEmployee(sId);
                }
                break;
            case EmployeeDetails:
                {
                    if(mManagerPtr->isEmpEmpty())
                    {
                        printf("There is no Emp found, So please add an employee\n");
                        break;
                    }
                    Utils::EmpType sEmpType;
                    Utils::EmpStatus sEmpStatus;
                    Utils::EmpGender sEmpGender;
                    std::string sEmpId;
                    Opeartion sType = pDisplayEmployeeDetailsMenu(sChoice,sEmpType,sEmpStatus,sEmpGender,sEmpId);
                    if(sType == AllEmpSummary)
                    {
                        mManagerPtr->displayAllEmployee();
                    }
                    else if(sType == EmpSummaryType)
                    {
                        mManagerPtr->displayEmployeeType(sEmpType);
                    }
                    else if(sType == EmpSummaryGender)
                    {
                        mManagerPtr->searchWithGender(sEmpGender);
                    }
                    else if(sType == EmpSummaryStatus)
                    {
                        mManagerPtr->searchWithStatus(sEmpStatus);
                    }
                    else if(sType == EmpDetailsWtId)
                    {
                        mManagerPtr->searchWithID(sEmpId);
                    }
                }
                break;
            case Other:
                {
                    if(mManagerPtr->isEmpEmpty())
                    {
                        printf("There is no Emp found, So please add an employee\n");
                        break;
                    }
                    std::string sEmpName,sEmpId;
                    int16_t numOfLeaves = 0;
                    Opeartion sType = pDisplayOthersMenu(sChoice,sEmpId,sEmpName,numOfLeaves);
                    if(sType == AddnNumLeaves)
                    {
                        mManagerPtr->addLeavesToAll(numOfLeaves);
                    }
                    else if(sType == ConvIntern2Full)
                    {
                        mManagerPtr->conv2Full(sEmpId);
                    }
                    else if(sType == SearchEmpId)
                    {
                        mManagerPtr->searchWithID(sEmpId);
                    }
                    else if(sType == SearchEmpName)
                    {
                        mManagerPtr->searchWithName(sEmpName);
                    }
                }
                break;
            default:
                break;
        }
    }
}
void EMS::pInputEmpType(Utils::EmpType& sEmpTypeParam)
{
    bool isValid = true;
    char sInput;
    do
    {
        std::cout << "Enter the Emp Type (F/C/I)\n";
        std::cin >> sInput;
        if(validCheck(std::cin) == false)
        {
            isValid = false;
        }
        else if(sInput != 'F' && sInput != 'C' && sInput != 'I' && sInput != 'f' && sInput != 'c' && sInput != 'i')
        {
            isValid = false;
        }
        else
        {
            isValid = true;
        }
    } while (isValid == false);
    if(sInput == 'F' || sInput == 'f')
    {
        sEmpTypeParam = Utils::FULLTIME;
    }
    else if(sInput == 'C' || sInput == 'c')
    {
        sEmpTypeParam = Utils::CONTRACTUAL;
    }
    else
    {
        sEmpTypeParam = Utils::INTERN;
    }
}
void EMS::pInputEmpStatus(Utils::EmpStatus& sEmpStatusParam)
{
    bool isValid = true;
    char sInput;
    do
    {
        std::cout << "Enter the Emp Status (A->Active/I->InActive/R->Resigned)\n";
        std::cin >> sInput;
        if(validCheck(std::cin) == false)
        {
            isValid = false;
        }
        else if(sInput != 'A' && sInput != 'I' && sInput != 'R' && sInput != 'a' && sInput != 'i' && sInput != 'r')
        {
            isValid = false;
        }
        else
        {
            isValid = true;
        }
    } while (isValid == false);
    if(sInput == 'A' || sInput == 'a')
    {
        sEmpStatusParam = Utils::ACTIVE;
    }
    else if(sInput == 'i' || sInput == 'I')
    {
        sEmpStatusParam = Utils::INACTIVE;
    }
    else
    {
        sEmpStatusParam = Utils::RESIGNED;
    }
}
void EMS::pInputEmpGender(Utils::EmpGender& sEmpGenderParam)
{
    bool isValid = true;
    char sInput;
    do
    {
        std::cout << "Enter the Gender (M/F)\n";
        std::cin >> sInput;
        if(validCheck(std::cin) == false)
        {
            isValid = false;
        }
        else if(sInput != 'M' && sInput != 'm' && sInput != 'F' && sInput != 'f')
        {
            isValid = false;
        }
        else
        {
            isValid = true;
        }
    } while (isValid == false);
    if(sInput == 'M' || sInput == 'm')
    {
        sEmpGenderParam = Utils::Male;
    }
    else if(sInput == 'F' || sInput == 'f')
    {
        sEmpGenderParam = Utils::Female;
    }
}
bool EMS::pDisplayMainMenu(uint16_t& sChoiceParam)
{
    bool isValid = true;
    do
    {
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Welcome to Employee Management System" << std::endl;
        std::cout << "1. Add an Employee" << std::endl;
        std::cout << "2. Remove an Employee" << std::endl;
        std::cout << "3. Employee Details" << std::endl;
        std::cout << "4. Others" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> sChoiceParam;
        std::cout << "-----------------------------------------" << std::endl;
        if(validCheck(std::cin) == false)
        {
            isValid = false;
        }
        else
        {
            isValid = true;
        }
    } while (isValid == false || sChoiceParam > 5 || sChoiceParam == 0);
    if(sChoiceParam == 5)
    {
        sChoiceParam = Exit;
        return false;
    }
    else if(sChoiceParam == 2)
    {
        sChoiceParam = RemoveAnEmployee;
    }
    else if(sChoiceParam == 3)
    {
        sChoiceParam = EmployeeDetails;
    }
    else if(sChoiceParam == 1)
    {
        sChoiceParam = AddAnEmployee;
    }
    else if(sChoiceParam == 4)
    {
        sChoiceParam = Other;
    }
    return true;
}
EMS::Opeartion EMS::pDisplayAddEmployeeMenu(uint16_t& sChoiceParam, Utils::EmpType& sEmpTypeParam, int16_t& numOfEmpParam)
{
    bool isValid = true;
    do
    {
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Add an Employee" << std::endl;
        std::cout << "1. Add an Employee at Random" << std::endl;
        std::cout << "2. Add an Employee (F/C/I)" << std::endl;
        std::cout << "3. Back to Main Menu" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> sChoiceParam;
        std::cout << "-----------------------------------------" << std::endl;
        if(validCheck(std::cin) == false)
        {
            isValid = false;
        }
        else
        {
            isValid = true;
            if(sChoiceParam == 1)
            {
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Enter the Num of random emp you want to create: ";
                std::cin >> numOfEmpParam;
                std::cout << "---------------------------------------------------" << std::endl;
                if(validCheck(std::cin) == false)
                {
                    isValid = false;
                }
                if(numOfEmpParam <= 0)
                {
                    isValid = false;
                    std::cout << "Please enter a positive or valid number\n";
                }
            }
        }
    } while (isValid == false || sChoiceParam > 3 || sChoiceParam == 0);
    switch(sChoiceParam)
    {
        case 1:
            return AddEmpRandom;
            break;
        case 2:
            pInputEmpType(sEmpTypeParam);
            return AddEmpWithType;
            break;
        case 3:
            return MainMenu;
            break;
        default:
            break;
    }
    return MainMenu;
}
EMS::Opeartion EMS::pDisplayEmployeeDetailsMenu(uint16_t& sChoiceParam, Utils::EmpType& sEmpTypeParam, Utils::EmpStatus& sEmpStatusParam, Utils::EmpGender& sEmpGenderParam, std::string& sEmpIdParam)
{
    bool isValid = true;
    do
    {
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Employee Details" << std::endl;
        std::cout << "1. All Employees Summary" << std::endl;
        std::cout << "2. Employee Summary (F/C/I)" << std::endl;
        std::cout << "3. Employee Summary (M/F)" << std::endl;
        std::cout << "4. Employee Summary (A/I/R)" << std::endl;
        std::cout << "5. Display Employee Details" << std::endl;
        std::cout << "6. Back to Main Menu" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> sChoiceParam;
        std::cout << "-----------------------------------------" << std::endl;
        if(validCheck(std::cin) == false)
        {
            isValid = false;
        }
        else
        {
            isValid = true;
        }
    } while (isValid == false || sChoiceParam > 6 || sChoiceParam == 0);

    if(sChoiceParam == 1)
    {
        return AllEmpSummary;
    }
    else if(sChoiceParam == 2)
    {
        pInputEmpType(sEmpTypeParam);
        return EmpSummaryType;
    }
    else if(sChoiceParam == 3)
    {
        pInputEmpGender(sEmpGenderParam);
        return EmpSummaryGender;
    }
    else if(sChoiceParam == 4)
    {
        pInputEmpStatus(sEmpStatusParam);
        return EmpSummaryStatus;
    }
    else if(sChoiceParam == 5)
    {
        std::cout << "Enter the Emp Id: \n";
        std::getline(std::cin>>std::ws,sEmpIdParam);
        return EmpDetailsWtId;
    }
    return MainMenu;
}
EMS::Opeartion EMS::pDisplayOthersMenu(uint16_t& sChoiceParam, std::string& sEmpIdParam, std::string& sEmpName, int16_t& numOfLeavesParam)
{
    bool isValid = true;
    do
    {
        std::cout << "----------------------------------------------------------------" << std::endl;
        std::cout << "Others" << std::endl;
        std::cout << "1. Add 'n' number of leaves to all the Full-Time employees" << std::endl;
        std::cout << "2. Convert an Intern to Full-Time employee" << std::endl;
        std::cout << "3. Search an Employee by ID" << std::endl;
        std::cout << "4. Search an Employee by Name" << std::endl;
        std::cout << "5. Back to Main Menu" << std::endl;
        std::cout << "----------------------------------------------------------------" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> sChoiceParam;
        std::cout << "----------------------------------------------------------------" << std::endl;
        if(validCheck(std::cin) == false)
        {
            isValid = false;
        }
        else
        {
            isValid = true;
            if(sChoiceParam == 1)
            {
                std::cout << "---------------------------------------------------" << std::endl;
                std::cout << "Enter the Num of leaves you want to add: ";
                std::cin >> numOfLeavesParam;
                std::cout << "---------------------------------------------------" << std::endl;
                if(validCheck(std::cin) == false)
                {
                    isValid = false;
                }
                if(numOfLeavesParam <= 0 || numOfLeavesParam > 8)
                {
                    isValid = false;
                    std::cout << "Please enter a positive or valid number it should not exceed 30 leaves in total\n";
                }
            }
        }
    } while (isValid == false || sChoiceParam > 5);
    if(sChoiceParam == 1)
    {
        return AddnNumLeaves;
    }
    else if(sChoiceParam == 2)
    {
        std::cout << "Enter the Emp Id: \n";
        std::getline(std::cin>>std::ws,sEmpIdParam);
        return ConvIntern2Full;
    }
    else if(sChoiceParam == 3)
    {
        std::cout << "Enter the Emp Id: \n";
        std::getline(std::cin>>std::ws,sEmpIdParam);
        return SearchEmpId;
    }
    else if(sChoiceParam == 4)
    {
        std::cout << "Enter the Emp Name: \n";
        std::getline(std::cin>>std::ws,sEmpName);
        return SearchEmpName;
    }
    return MainMenu;
}
