#include <gruppe32/Parser.hpp>

namespace gruppe32::Parser 
{
using std::string;
using std::string_view;

auto encodeIdrettene(const DB::Idrettene& idrettene) -> string 
{
	return Parser::SUCCESS;
}

auto decodeIdrettene(DB::Idrettene& idrettene, string_view strview) -> Parser::Status 
{
	return Parser::SUCCESS;
}

}