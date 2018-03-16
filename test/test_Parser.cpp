#include <gruppe32/Test.hpp>
#include <gruppe32/Parser.hpp>
#include <gruppe32/DB.hpp>

namespace gruppe32
{


bool test_ParserDecodeAndEncodeIdrettene() 
{
    constexpr char encodedIdrettene[] = ""
"idretteneCount: 1"
"idrettene:"
""
"- idrett: Fotball"
"  tabelltype: 310"
"  divisjoneneCount: 2"
"  divisjonene:"
""
"  - divisjon: Eliteserien"
"    lageneCount: 2"
"    lagene:"
""
"    - lag: Brann"
"      adresse: Bergen, Norway"
"      spillereneCount: 2"
"      spillerene:"
"      - spiller: 0"
"      - spiller: 1"
""
"    - lag: Rosenborg"
"      adresse: Trondheim, Norway "
"      spillereneCount: 2"
"      spillerene:"
"      - spiller: 2"
"      - spiller: 3"
""
"    terminliste:"
"      hjemmelagene:"
""
"      - hjemmelag: Brann"
"        bortelagene:"
""
"        - bortelag: Rosenborg"
"          dato: 2012-03-19"
"          resultat:"
"            overtid: true"
"            hjemmepoengCount: 4"
"            hjemmepoeng:"
"            - spiller: 0"
"            - spiller: 0"
"            - spiller: 0"
"            - spiller: 1"
"            bortepoengCount: 2"
"            bortepoeng:"
"            - spiller: 0"
"            - spiller: 0"
""
"      - hjemmelag: Rosenborg"
"        bortelagene:"
""
"        - bortelag: Brann"
"          dato: 2013-03-19"
"          resultat: false"
""
"  - divisjon: Premier League 2017/2018"
"    lageneCount: 2"
"    lagene:"
""
"    - lag: Manchester United"
"      adresse: Machester, United Kingdom"
"      spillereneCount: 2 "
"      spillerene: "
"      - spiller: 4"
"      - spiller: 5"
""
"    - lag: Tottenham Hotspurs"
"      adresse: London, United Kingdom"
"      spillereneCount: 2 "
"      spillerene:"
"      - spiller: 6"
"      - spiller: 7"
""
"    terminliste:"
"      hjemmelagene:"
""
"      - hjemmelag: Manchester United"
"        bortelagene:"
""
"        - bortelag: Tottenham Hotspurs"
"          dato: 2012-03-19"
"          resultat:"
"            overtid: false"
"            hjemmepoengCount: 1"
"            hjemmepoeng:"
"            - spiller: 1"
"            bortepoengCount: 3"
"            bortepoeng:"
"            - spiller: 1"
"            - spiller: 1"
"            - spiller: 0"
""
"      - hjemmelag: Tottenham Hotspurs"
"        bortelagene:"
""
"        - bortelag: Manchester United"
"          dato: 2013-03-19"
"          resultat: false";

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