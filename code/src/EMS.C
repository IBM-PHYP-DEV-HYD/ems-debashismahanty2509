#include "iostream"
#include "Manager.H"

class EMS
{
    public:
    enum Opeartion
    {
        AddAnEmployee   = 0,
        AddEmpRandom    = 1,
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
        uint8_t sChoice;
        while(sChoice = displayMainMenu() && sChoice != Exit)
        {
            switch(sChoice)
            {
                case AddAnEmployee:
                    {
                        Opeartion sType = displayAddEmployeeMenu(sChoice);
                        if(sType == AddEmpRandom)
                        {
                            // managerPtr->
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
    uint8_t displayMainMenu(void)
    {
        uint8_t sChoice;
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
        }
        return sChoice;
    }
    Opeartion displayAddEmployeeMenu(uint8_t& sChoiceParam)
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
                break;
            case 3:
                return MainMenu;
                break;
            default:
                break;
        }
        return MainMenu;
    }
    void displayEmployeeDetailsMenu(uint8_t& sChoiceParam)
    {
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
        } while (validCheck(std::cin) == false || sChoiceParam > 6);
    }
    void displayOthersMenu(uint8_t& sChoiceParam)
    {
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
        } while (validCheck(std::cin) == false || sChoiceParam > 5);
    }
};

int main()
{
    EMS ems;
    ems.managerPtr = Manager::getInstance("XYZ Corp", "admin", "password123");
    if(NULL != ems.managerPtr)
    {
        ems.managerPtr->addEmployee(Employee::EmpType::FULLTIME);
        ems.managerPtr->addEmployee(Employee::EmpType::INTERN);
        ems.managerPtr->addEmployee(Employee::EmpType::CONTRACTUAL);
        ems.managerPtr->displayAllEmployee();
    }
    return 0;
}