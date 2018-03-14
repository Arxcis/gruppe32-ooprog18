#include <gruppe32/Valid.hpp>

namespace gruppe32::Valid
{
	bool isAsciiChar(const std::string& value)
	{
		IO::printline("isAsciiChar() ? ");
		return std::regex_match(value, Valid::regexAsciiChar);
	}

	bool isPostnummer(const std::string& value)
	{
		IO::printline("isPostnummer() ? ");
		return true;
	}

	bool isUint(const std::string& value)
	{
		IO::printline("isUint() ? ");
		return true;
	}

	bool isName(const std::string& value)
	{
		IO::printline("isName() ? ");
		return true;
	}

	bool isDate(const std::string& value)
	{
		IO::printline("isDate() ? ");
		return true;
	}

} // end namespace