#include <gruppe32/Valid.hpp>

namespace gruppe32::Valid
{
	bool isAsciiChar(const std::string& value)
	{
		return std::regex_match(value, Valid::regexAsciiChar);
	}

	bool isPostnummer(const std::string& value)
	{
		return true;
	}

	bool isUint(const std::string& value)
	{
		return true;
	}

	bool isName(const std::string& value)
	{
		return true;
	}

	bool isDate(const std::string& value)
	{
		return true;
	}

} // end namespace