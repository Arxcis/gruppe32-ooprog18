#include <gruppe32/Valid.hpp>

namespace gruppe32
{

using std::string;
using std::regex;
using std::regex_match;

bool Valid::isAsciiChar(const string& value)
{
    constexpr char regexAsciiChar[] = R"(^[a-zA-Z]$)";

    const static regex compiledRegex(regexAsciiChar);
    return regex_match(value, compiledRegex);
}

bool Valid::isAsciiCharPlusNorwegian(const string& value)
{
    constexpr char regexAsciiCharPlusNorwegian[] = R"(^[a-zA-ZøæåØÆÅ]$)";

    const static regex compiledRegex(regexAsciiCharPlusNorwegian);
    return regex_match(value, compiledRegex);   
}

bool Valid::isPostnummer(const string& value)
{   
    constexpr char regexPostnummer[] = R"(^000[1-9]$|^00[1-9][0-9]$|^0[1-9][0-9]{2}$|^[1-9][0-9]{3}$)";

    const static regex compiledRegex(regexPostnummer);
    return regex_match(value, compiledRegex);
}
bool Valid::isUint(const string& value)
{
    constexpr char regexUint[] = R"((^[1-9][0-9]{0,8}$)|(^[1-3]([0-9]{0,9})$|(^0$)))";

    const static regex compiledRegex(regexUint);
    return regex_match(value, compiledRegex);
}
bool Valid::isName(const string& value)
{
    constexpr char regexName[] = R"(^([a-zA-ZÆØÅæøå]+)(-[a-zA-ZÆØÅæøå]+)?$)";

    const static regex compiledRegex(regexName);
    return regex_match(value, compiledRegex);
}
bool Valid::isYear(const string& value)
{
    constexpr char regexYear[] = R"(^19[7-9][0-9]$|^20[0-9][0-9]$)";

    const static regex compiledRegex(regexYear);
    return regex_match(value, compiledRegex);
}
bool Valid::isMonth(const string& value)
{
    constexpr char regexMonth[] = R"(^0[1-9]$|^1[012]$)";

    const static regex compiledRegex(regexMonth);
    return regex_match(value, compiledRegex);
}
bool Valid::isDay(const string& value)
{
    constexpr char regexDay[] = R"(^0[1-9]$|^[12][0-9]$|^3[01]$)";

    const static regex compiledRegex(regexDay);
    return regex_match(value, compiledRegex);
} 
bool Valid::isAddress(const string& value)
{
    constexpr char regexAddress[]  = R"(^[A-Za-z0-9\ \. \-ÆØÅæøå]+$)";

    const static regex compiledRegex(regexAddress);
    return regex_match(value, compiledRegex);
}   
} // ::gruppe32