#pragma once

#include <string>
#include <vector>
#include <regex>

#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>

/// <summary> String validation module </summary>
namespace gruppe32::Valid 
{
    /// <summary> string - validating single letter A-Z, a-z </summary>
    constexpr char regexAsciiChar[] = R"(^[a-zA-Z]$)";
    
    /// <summary> string - validating single letter A-Z, a-z, æ,ø,å,Æ,Ø,Å </summary>
    constexpr char regexAsciiCharPlusNorwegian[] = R"(^[a-zA-ZøæåØÆÅ]$)";
    
    /// <summary> string - validating any norwegian postnumber between 0001-9999 </summary>
    constexpr char regexPostnummer[] = R"(^000[1-9]$|^00[1-9][0-9]$|^0[1-9][0-9]{2}$|^[1-9][0-9]{3}$)";

    /// <summary> string - validating uint Min 0, Max 3 999 999 999 </summary>
    constexpr char regexUint[] = R"((^[1-9][0-9]{0,8}$)|(^[1-3]([0-9]{0,9})$|(^0$)))";

    ///  <summary> string - validating any norwegian single name, with an optional hyphen to
    ///                     to separate a composite name.
    ///                     Example of valid names:
    ///                     * Jonas
    ///                     * NORGE
    ///                     * NorGe
    ///                     * Bjørn-Magne </summary>
    constexpr char regexName[] = R"(^([a-zA-ZÆØÅæøå]+)(-[a-zA-ZÆØÅæøå]+)?$)";
    
    /// <summary> string - validating a year 'yyyy' in the range [1970-2099] </summary>
    constexpr char regexYear[] = R"(^19[7-9][0-9]$|^20[0-9][0-9]$)";

    /// <summary> string - validating a month 'mm' in the range [01-12] </summary>
    constexpr char regexMonth[] = R"(^0[1-9]$|^1[012]$)";

    /// <summary> string - validating a day 'dd' in the range [01-31] </summary>
    constexpr char regexDay[] = R"(^0[1-9]$|^[12][0-9]$|^3[01]$)";

    /// <summary> string - validating a norwegian address. robustness is very-relaxed </summary>
    constexpr char regexAddress[]  = R"(^[A-Za-z0-9\ \. \-ÆØÅæøå]+$)";

    using std::string;

    /// <summary> isAsciiChar() </summary>
    bool isAsciiChar(const string& value);
    /// <summary> isPostnummer() </summary>
    bool isPostnummer(const string& value);
    /// <summary> isUint() </summary>
    bool isUint(const string& value);
    /// <summary> isName() </summary>
    bool isName(const string& value);
    /// <summary> isYear() </summary>
    bool isYear(const string& value);
    /// <summary> isMonth() </summary>
    bool isMonth(const string& value);
    /// <summary> isDay() </summary>
    bool isDay(const string& value);
    /// <summary> isAddress() </summary>
    bool isAddress(const string& value);
}