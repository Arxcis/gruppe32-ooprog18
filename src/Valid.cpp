#include <gruppe32/Valid.hpp>

namespace gruppe32::Valid
{
    using std::string;
    using std::regex;
    using std::regex_match;

    bool isAsciiChar(const string& value)
    {
        const static regex compiledRegex(Valid::regexAsciiChar);
        return regex_match(value, compiledRegex);
    }
    bool isPostnummer(const string& value)
    {   
        const static regex compiledRegex(Valid::regexPostnummer);
        return regex_match(value, compiledRegex);
    }
    bool isUint(const string& value)
    {
        const static regex compiledRegex(Valid::regexUint);
        return regex_match(value, compiledRegex);
    }
    bool isName(const string& value)
    {
        const static regex compiledRegex(Valid::regexName);
        return regex_match(value, compiledRegex);
    }
    bool isYear(const string& value)
    {
        const static regex compiledRegex(Valid::regexYear);
        return regex_match(value, compiledRegex);
    }
    bool isMonth(const string& value)
    {
        const static regex compiledRegex(Valid::regexMonth);
        return regex_match(value, compiledRegex);
    }
    bool isDay(const string& value)
    {
        const static regex compiledRegex(Valid::regexDay);
        return regex_match(value, compiledRegex);
    } 
    bool isAddress(const string& value)
    {
        const static regex compiledRegex(Valid::regexAddress);
        return regex_match(value, compiledRegex);
    }   
} // end namespace