#pragma once

#include <string>
#include <vector>
#include <regex>

#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>

/// <summary> String validation module </summary>
namespace gruppe32::Valid 
{
using std::string;

/// <summary> string - validating single letter A-Z, a-z </summary>
bool isAsciiChar(const string& value);

/// <summary> string - validating single letter A-Z, a-z, æ,ø,å,Æ,Ø,Å </summary>
bool isAsciiCharPlusNorwegian(const string& value);

/// <summary> string - validating uint Min 0, Max 3 999 999 999 </summary>
bool isUint(const string& value);

///  <summary> string - validating any norwegian single name, with an optional hyphen to
///                     to separate a composite name.
///                     Example of valid names:
///                     * Jonas
///                     * NORGE
///                     * NorGe
///                     * Bjørn-Magne </summary>
bool isName(const string& value);

/// <summary> string - validating a year 'yyyy' in the range [1970-2099] </summary>
bool isYear(const string& value);

/// <summary> string - validating a month 'mm' in the range [01-12] </summary>
bool isMonth(const string& value);

/// <summary> string - validating a day 'dd' in the range [01-31] </summary>
bool isDay(const string& value);

/// <summary> string - validating a norwegian address. robustness is very-relaxed </summary>
bool isAddress(const string& value);

} // ::Valid ::gruppe32