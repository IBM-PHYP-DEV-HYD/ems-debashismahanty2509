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
    void pInputEmpType(EmployeeIF::EmpType& sEmpTypeParam);
    void pInputEmpStatus(EmployeeIF::EmpStatus& sEmpStatusParam);
    void pInputEmpGender(EmployeeIF::EmpGender& sEmpGenderParam);
    bool pDisplayMainMenu(uint16_t& sChoiceParam);
    Opeartion pDisplayAddEmployeeMenu(uint16_t& sChoiceParam, EmployeeIF::EmpType& sEmpTypeParam, int16_t& numOfEmpParam);
    Opeartion pDisplayEmployeeDetailsMenu(uint16_t& sChoiceParam, EmployeeIF::EmpType& sEmpTypeParam, EmployeeIF::EmpStatus& sEmpStatusParam, EmployeeIF::EmpGender& sEmpGenderParam, std::string& sEmpIdParam);
    Opeartion pDisplayOthersMenu(uint16_t& sChoiceParam, std::string& sEmpIdParam, std::string& sEmpName,int16_t& numOfLeavesParam);
};
#endif