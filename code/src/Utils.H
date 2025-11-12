#ifndef _UTILS_H_
#define _UTILS_H_
#include <iostream>

// Enumerations for Employee Type, Status, Gender, Agency, College, Branch, Input Type, and Width for Printing
namespace Utils
{
    enum EmpGender
    {
        Male        = 0,
        Female      = 1,
        None        = 2,
    };
    enum EmpType
    {
        FULLTIME    = 0,
        INTERN      = 1,
        CONTRACTUAL = 2,
        NONE        = 3,
    };
    enum EmpStatus
    {
        ACTIVE       = 0,
        INACTIVE     = 1,
        RESIGNED     = 2,
    };
    enum Agency
    {
        Avengers     = 0,
        JusticeLeague= 1,
        XMen         = 2,
    };
    enum College
    {
        IitDelhi      = 0,
        IitMumbai     = 1,
        IitKanpur     = 2,
        IitHyderabad  = 3,
        NitWarangal   = 4,
        NitTiruchi    = 5,
        IiitHyderabad = 6,
    };
    enum Branch
    {
        CSE          = 0,
        ECE          = 1,
        CSIT         = 2,
    };
    enum InputType
    {
        RANDOM       = 0,
        USERINPUT    = 1,
    };
    enum WidthPrint
    {
        Name         = 17,
        Id           = 12,
        Gender       = 10,
        Dob          = 12,
        Doj          = 12,
        Dol          = 12,
        Type         = 12,
        Status       = 10,
        Clg          = 15,
        Bnh          = 11,
        CLeaves      = 18,
        LevApp       = 18,
        Agncy        = 15,
        LeftMar      = 13,
    };
}

#endif