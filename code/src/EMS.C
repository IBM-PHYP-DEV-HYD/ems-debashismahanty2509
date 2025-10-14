#include "iostream"
#include "Manager.H"

class EMS
{
    public:
    enum Opeartion
    {
        AddAnEmployee   = 0,
        AddEmpRandom    = 1,
        AddEmpWithType  = 2,

        RemoveAnEmployee= 5,

        EmployeeDetails = 6,
        AllEmpSummary   = 7,
        EmpSummaryType  = 8,
        EmpSummaryGender= 9,
        EmpSummaryStatus= 10,
        EmpDetailsWtId  = 11,

        Other           = 14,
        AddnNumLeaves   = 15,
        ConvIntern2Full = 16,
        SearchEmpId     = 17,
        SearchEmpName   = 18,

        MainMenu        = 12,
        Exit            = 13
    };
    Manager *managerPtr = nullptr;
    EMS() = default;
    ~EMS() = default;
    bool validCheck(std::istream& isParam)
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
    void handleMenu(void)
    {
        //NULL check
        uint16_t sChoice = 0;
        while(displayMainMenu(sChoice) && sChoice != Exit)
        {
            switch(sChoice)
            {
                case AddAnEmployee:
                    {
                        EmployeeIF::EmpType sEmpType;
                        Opeartion sType = displayAddEmployeeMenu(sChoice,sEmpType);
                        if(sType == AddEmpRandom)
                        {
                            managerPtr->addRandomEmp();
                        }
                        else if(sType == AddEmpWithType)
                        {
                            managerPtr->addEmployee(sEmpType);
                        }
                    }
                    break;
                case RemoveAnEmployee:
                    {
                        std::string sId;
                        std::cout << "Enter the Emp Id: \n";
                        std::getline(std::cin>>std::ws,sId);
                        managerPtr->removeEmployee(sId);
                    }
                    break;
                case EmployeeDetails:
                    {
                        EmployeeIF::EmpType sEmpType;
                        Employee::EmpStatus sEmpStatus;
                        EmployeeIF::EmpGender sEmpGender;
                        std::string sEmpId;
                        Opeartion sType = displayEmployeeDetailsMenu(sChoice,sEmpType,sEmpStatus,sEmpGender,sEmpId);
                        if(sType == AllEmpSummary)
                        {
                            managerPtr->displayAllEmployee();
                        }
                        else if(sType == EmpSummaryType)
                        {
                            managerPtr->displayEmployeeType(sEmpType);
                        }
                        else if(sType == EmpSummaryGender)
                        {
                            managerPtr->searchWithGender(sEmpGender);
                        }
                        else if(sType == EmpSummaryStatus)
                        {
                            managerPtr->searchWithStatus(sEmpStatus);
                        }
                        else if(sType == EmpDetailsWtId)
                        {
                            managerPtr->searchWithID(sEmpId);
                        }
                    }
                    break;
                case Other:
                    {
                        std::string sEmpName,sEmpId;
                        Opeartion sType = displayOthersMenu(sChoice,sEmpId,sEmpName);
                        if(sType == AddnNumLeaves)
                        {
                            managerPtr->addLeavesToAll(1);
                        }
                        else if(sType == ConvIntern2Full)
                        {
                            managerPtr->conv2Full(sEmpId);
                        }
                        else if(sType == SearchEmpId)
                        {
                            managerPtr->searchWithID(sEmpId);
                        }
                        else if(sType == SearchEmpName)
                        {
                            managerPtr->searchWithName(sEmpName);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
    //Implement a menu-driven approach for the following as follows:
    // Main Menu Option - Operation - Inputs from user
    // 1 Add an Employee NA
    // 2 Remove an Employee Emp ID
    // 3 Employee Details NA
    // 4 Others NA
    // Sub-Menu-1 Op(ons Add an Employee Inputs from user
    // 1 Add an Employee at Random N/A
    // 2 Add an Employee (F/C/I) Type
    // Sub-Menu-2 Op(ons Employee Details Inputs from user
    // 1 All Employees Summary NA
    // 2 Employee Summary (F/C/I) Type
    // 3 Employee Summary (M/F) Gender
    // 4 Employee Summary (A/I/R) Status
    // 5 Display Employee Details Emp ID
    // Sub-Menu-3 Op(ons Others Inputs from user
    // 1 Add ‘n’ number of leaves to all
    // the Full-Time employees
    // NA
    // 2 Convert an Intern to Full-Time
    // employee.
    // Emp ID
    // 3 Search an Employee by ID Emp ID
    // 4 Search an Employee by Name Name / part of the name
    protected:
    void inputEmpType(EmployeeIF::EmpType& sEmpTypeParam)
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
            sEmpTypeParam = EmployeeIF::FULLTIME;
        }
        else if(sInput == 'C' || sInput == 'c')
        {
            sEmpTypeParam = EmployeeIF::CONTRACTUAL;
        }
        else
        {
            sEmpTypeParam = EmployeeIF::INTERN;
        }
    }
    void inputEmpStatus(EmployeeIF::EmpStatus& sEmpStatusParam)
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
            sEmpStatusParam = EmployeeIF::ACTIVE;
        }
        else if(sInput == 'i' || sInput == 'I')
        {
            sEmpStatusParam = EmployeeIF::INACTIVE;
        }
        else
        {
            sEmpStatusParam = EmployeeIF::RESIGNED;
        }
    }
    void inputEmpGender(EmployeeIF::EmpGender& sEmpGenderParam)
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
            sEmpGenderParam = EmployeeIF::Male;
        }
        else if(sInput == 'F' || sInput == 'f')
        {
            sEmpGenderParam = EmployeeIF::Female;
        }
    }
    bool displayMainMenu(uint16_t& sChoice)
    {
        bool isValid = true;
        do
        {
            std::cout << "Welcome to Employee Management System" << std::endl;
            std::cout << "1. Add an Employee" << std::endl;
            std::cout << "2. Remove an Employee" << std::endl;
            std::cout << "3. Employee Details" << std::endl;
            std::cout << "4. Others" << std::endl;
            std::cout << "5. Exit" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> sChoice;
            if(validCheck(std::cin) == false)
            {
                isValid = false;
            }
            else
            {
                isValid = true;
            }
        } while (isValid == false || sChoice > 5 || sChoice == 0);
        if(sChoice == 5)
        {
            sChoice = Exit;
            return false;
        }
        else if(sChoice == 2)
        {
            sChoice = RemoveAnEmployee;
        }
        else if(sChoice == 3)
        {
            sChoice = EmployeeDetails;
        }
        else if(sChoice == 1)
        {
            sChoice = AddAnEmployee;
        }
        else if(sChoice == 4)
        {
            sChoice = Other;
        }
        return true;
    }
    Opeartion displayAddEmployeeMenu(uint16_t& sChoiceParam, EmployeeIF::EmpType& sEmpTypeParam)
    {
        bool isValid = true;
        do
        {
            std::cout << "Add an Employee" << std::endl;
            std::cout << "1. Add an Employee at Random" << std::endl;
            std::cout << "2. Add an Employee (F/C/I)" << std::endl;
            std::cout << "3. Back to Main Menu" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> sChoiceParam;
            if(validCheck(std::cin) == false)
            {
                isValid = false;
            }
            else
            {
                isValid = true;
            }
        } while (isValid == false || sChoiceParam > 3 || sChoiceParam == 0);
        switch(sChoiceParam)
        {
            case 1:
                return AddEmpRandom;
                break;
            case 2:
                inputEmpType(sEmpTypeParam);
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
    Opeartion displayEmployeeDetailsMenu(uint16_t& sChoiceParam, EmployeeIF::EmpType& sEmpTypeParam, EmployeeIF::EmpStatus& sEmpStatusParam, EmployeeIF::EmpGender& sEmpGenderParam, std::string& sEmpIdParam)
    {
        bool isValid = true;
        do
        {
            std::cout << "Employee Details" << std::endl;
            std::cout << "1. All Employees Summary" << std::endl;
            std::cout << "2. Employee Summary (F/C/I)" << std::endl;
            std::cout << "3. Employee Summary (M/F)" << std::endl;
            std::cout << "4. Employee Summary (A/I/R)" << std::endl;
            std::cout << "5. Display Employee Details" << std::endl;
            std::cout << "6. Back to Main Menu" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> sChoiceParam;
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
            inputEmpType(sEmpTypeParam);
            return EmpSummaryType;
        }
        else if(sChoiceParam == 3)
        {
            inputEmpGender(sEmpGenderParam);
            return EmpSummaryGender;
        }
        else if(sChoiceParam == 4)
        {
            inputEmpStatus(sEmpStatusParam);
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
    Opeartion displayOthersMenu(uint16_t& sChoiceParam, std::string& sEmpIdParam, std::string& sEmpName)
    {
        bool isValid = true;
        do
        {
            std::cout << "Others" << std::endl;
            std::cout << "1. Add 'n' number of leaves to all the Full-Time employees" << std::endl;
            std::cout << "2. Convert an Intern to Full-Time employee" << std::endl;
            std::cout << "3. Search an Employee by ID" << std::endl;
            std::cout << "4. Search an Employee by Name" << std::endl;
            std::cout << "5. Back to Main Menu" << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> sChoiceParam;
            if(validCheck(std::cin) == false)
            {
                isValid = false;
            }
            else
            {
                isValid = true;
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
};

int main()
{
    EMS ems;
    ems.managerPtr = Manager::getInstance("XYZ Corp", "admin", "password123");
    if(NULL != ems.managerPtr)
    {
        // ems.managerPtr->addEmployee(Employee::EmpType::FULLTIME);
        // ems.managerPtr->addEmployee(Employee::EmpType::INTERN);
        // ems.managerPtr->addEmployee(Employee::EmpType::CONTRACTUAL);
        // ems.managerPtr->displayAllEmployee();
        ems.handleMenu();
    }
    return 0;
}