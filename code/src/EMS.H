#ifndef _EMS_H_
#define _EMS_H_
#include <iostream>
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
    Manager *mManagerPtr = nullptr;
    EMS() = default;
    ~EMS() = default;

    bool validCheck(std::istream& isParam);
    void handleMenu(void);

    protected:
    void inputEmpType(EmployeeIF::EmpType& sEmpTypeParam);
    void inputEmpStatus(EmployeeIF::EmpStatus& sEmpStatusParam);
    void inputEmpGender(EmployeeIF::EmpGender& sEmpGenderParam);
    bool displayMainMenu(uint16_t& sChoice);
    Opeartion displayAddEmployeeMenu(uint16_t& sChoiceParam, EmployeeIF::EmpType& sEmpTypeParam);
    Opeartion displayEmployeeDetailsMenu(uint16_t& sChoiceParam, EmployeeIF::EmpType& sEmpTypeParam, EmployeeIF::EmpStatus& sEmpStatusParam, EmployeeIF::EmpGender& sEmpGenderParam, std::string& sEmpIdParam);
    Opeartion displayOthersMenu(uint16_t& sChoiceParam, std::string& sEmpIdParam, std::string& sEmpName);
};
#endif