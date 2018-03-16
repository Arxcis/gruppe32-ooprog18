#include <gruppe32/Test.hpp>
#include <gruppe32/Parser.hpp>
#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>

namespace gruppe32
{


bool test_ParserDecodeAndEncodeIdrettene() 
{
    constexpr char encodedIdrettene[] = ""
"idretteneCount: 1\n"
"idrettene:\n"
"\n"
"- idrett: Fotball\n"
"  tabelltype: 310\n"
"  divisjoneneCount: 2\n"
"  divisjonene:\n"
"\n"
"  - divisjon: Eliteserien\n"
"    lageneCount: 2\n"
"    lagene:\n"
"\n"
"    - lag: Brann\n"
"      adresse: Bergen, Norway\n"
"      spillereneCount: 2\n"
"      spillerene:\n"
"      - spiller: 0\n"
"      - spiller: 1\n"
"\n"
"    - lag: Rosenborg\n"
"      adresse: Trondheim, Norway \n"
"      spillereneCount: 2\n"
"      spillerene:\n"
"      - spiller: 2\n"
"      - spiller: 3\n"
"\n"
"    terminliste:\n"
"      hjemmelagene:\n"
"\n"
"      - hjemmelag: Brann\n"
"        bortelagene:\n"
"\n"
"        - bortelag: Rosenborg\n"
"          dato: 2012-03-19\n"
"          resultat:\n"
"            overtid: true\n"
"            hjemmepoengCount: 4\n"
"            hjemmepoeng:\n"
"            - spiller: 0\n"
"            - spiller: 0\n"
"            - spiller: 0\n"
"            - spiller: 1\n"
"            bortepoengCount: 2\n"
"            bortepoeng:\n"
"            - spiller: 0\n"
"            - spiller: 0\n"
"\n"
"      - hjemmelag: Rosenborg\n"
"        bortelagene:\n"
"\n"
"        - bortelag: Brann\n"
"          dato: 2013-03-19\n"
"          resultat: false\n"
"\n"
"  - divisjon: Premier League 2017/2018\n"
"    lageneCount: 2\n"
"    lagene:\n"
"\n"
"    - lag: Manchester United\n"
"      adresse: Machester, United Kingdom\n"
"      spillereneCount: 2 \n"
"      spillerene: \n"
"      - spiller: 4\n"
"      - spiller: 5\n"
"\n"
"    - lag: Tottenham Hotspurs\n"
"      adresse: London, United Kingdom\n"
"      spillereneCount: 2 \n"
"      spillerene:\n"
"      - spiller: 6\n"
"      - spiller: 7\n"
"\n"
"    terminliste:\n"
"      hjemmelagene:\n"
"\n"
"      - hjemmelag: Manchester United\n"
"        bortelagene:\n"
"\n"
"        - bortelag: Tottenham Hotspurs\n"
"          dato: 2012-03-19\n"
"          resultat:\n"
"            overtid: false\n"
"            hjemmepoengCount: 1\n"
"            hjemmepoeng:\n"
"            - spiller: 1\n"
"            bortepoengCount: 3\n"
"            bortepoeng:\n"
"            - spiller: 1\n"
"            - spiller: 1\n"
"            - spiller: 0\n"
"\n"
"      - hjemmelag: Tottenham Hotspurs\n"
"        bortelagene:\n"
"\n"
"        - bortelag: Manchester United\n"
"          dato: 2013-03-19\n"
"          resultat: false\n";

	DB::Idrettene idrettene;
    
	if (auto result = Parser::decodeIdrettene(idrettene, encodedIdrettene);
	result != Parser::SUCCESS) {
		Test::printFailed(0, "Parser::decodeIdrettene(idrettene, encodedIdrettene)", "Parser::SUCCESS", "Parser::ERROR");
    }
	else {
		Test::printSuccess(0, "decodeIdrettene(idrettene, encodedIdrettene)", "Parser::SUCCESS");
    }
	// Check if some data is stored correctly in the datastructure

	std::string encodedDecodedIdrettene = Parser::encodeIdrettene(idrettene);

    if (encodedDecodedIdrettene != encodedIdrettene) {
        Test::printFailed(1, "encodeIdrettene(idrettene) -> string", "encodedDecodedIdrettene == encodeIdrettene", "There was a difference betweeen the two strings");
		return false;
	}

    return true;
}

bool test_Parser() 
{

    std::cout << "\nRunning test_ParserDecodeAndEncodeIdrettene()\n";
    bool result = test_ParserDecodeAndEncodeIdrettene();

    std::cout << '\n';
    return result;
}

}