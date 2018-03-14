#pragma once

#include <string>
#include <vector>
#include <regex>

#include <gruppe32/DB.hpp>

namespace gruppe32::Valid 
{
    /// <summary> std::regex - validating single letter A-Z, a-z </summary>
    const static std::regex regexAsciiChar(R"(^[a-zA-Z]$)");
    
    /// <summary> std::regex - validating single letter A-Z, a-z, æ,ø,å,Æ,Ø,Å </summary>
    const static std::regex regexAsciiCharPlusNorwegian(R"(^[a-zA-ZøæåØÆÅ]$)");
    
    /// <summary> std::regex - validating any norwegian postnumber between 0000-9999 </summary>
    const static std::regex regexPostnummer(R"(^[0-9]{4}$)");

    /// <summary> std::regex - validating uint Min 0, Max 3 999 999 999 </summary>
    const static std::regex regexUint   (R"((^[1-9][0-9]{0,8}$)|(^[1-3]([0-9]{0,9})$|(^[0]$)))");

    ///  <summary> std::regex - validating any norwegian single name.
    ///            * With or without hyphen '-'. 
    ///            * Possibly ending with '.' </summary>
    ///  @robustness - It is now possible to start a name with hyphen '-'.
    const static std::regex regexName   (R"(^(([a-zA-ZÆØÅæøå\-]([\.]?))+)$)");
    

    /// <summary> std::regex - validating a date yyyy.mm.dd </summary>
    /// @robustness - Does not account for varying month-length and year-length
    ///               This could possible be handled somewhere else in the code.
    ///               For instance in the IO-namespace.
    const static std::regex regexDate   (R"([\s]*(([0][1-9])|([1-2][0-9])|([3][0-1]))[\.]([0][1-9]|[1][0-2])[\.](([1][9])|([2][0]))?([0-9]{2})$)"); 
    
    bool isAsciiChar(const std::string& value);
    bool isPostnummer(const std::string& value);
    bool isUint(const std::string& value);
    bool isName(const std::string& value);
    bool isDate(const std::string& value);
}