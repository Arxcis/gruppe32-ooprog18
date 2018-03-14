#pragma once

#include <string>
#include <vector>
#include <regex>

#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>

/// <summary> Validates strings </summary>
namespace gruppe32::Valid 
{
    /// <summary> string - validating single letter A-Z, a-z </summary>
    constexpr char regexAsciiChar[] = R"(^[a-zA-Z]$)";
    
    /// <summary> string - validating single letter A-Z, a-z, æ,ø,å,Æ,Ø,Å </summary>
    constexpr char regexAsciiCharPlusNorwegian[] = R"(^[a-zA-ZøæåØÆÅ]$)";
    
    /// <summary> string - validating any norwegian postnumber between 0000-9999 </summary>
    constexpr char regexPostnummer[] = R"(^[0-9]{4}$)";

    /// <summary> string - validating uint Min 0, Max 3 999 999 999 </summary>
    constexpr char regexUint[] = R"((^[1-9][0-9]{0,8}$)|(^[1-3]([0-9]{0,9})$|(^[0]$)))";

    ///  <summary> string - validating any norwegian single name.
    ///            * With or without hyphen '-'. 
    ///            * Possibly ending with '.' </summary>
    ///  @robustness - It is now possible to start a name with hyphen '-'.
    constexpr char regexName[] = R"(^(([a-zA-ZÆØÅæøå\-]([\.]?))+)$)";
    

    /// <summary> string - validating a date yyyy.mm.dd </summary>
    /// @robustness - Does not account for varying month-length and year-length
    ///               This could possible be handled somewhere else in the code.
    ///               For instance in the IO-namespace.
    constexpr char regexDate[] = R"([\s]*(([0][1-9])|([1-2][0-9])|([3][0-1]))[\.]([0][1-9]|[1][0-2])[\.](([1][9])|([2][0]))?([0-9]{2})$)";
    
    using std::string;
    bool isAsciiChar(const string& value);
    bool isPostnummer(const string& value);
    bool isUint(const string& value);
    bool isName(const string& value);
    bool isDate(const string& value);
}