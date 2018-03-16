#include <gruppe32/Test.hpp>
#include <gruppe32/Parser.hpp>
#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>

#include <cassert>
#include <cstring>

namespace gruppe32
{

void test_ParserDecodeAndEncodeIdrettene() 
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
"      adresse: Trondheim, Norway\n"
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
"            hjemmeScorereneCount: 4\n"
"            hjemmeScorerene:\n"
"            - spiller: 0\n"
"            - spiller: 0\n"
"            - spiller: 0\n"
"            - spiller: 1\n"
"            borteScorereneCount: 2\n"
"            borteScorerene:\n"
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
"      spillereneCount: 2\n"
"      spillerene:\n"
"      - spiller: 4\n"
"      - spiller: 5\n"
"\n"
"    - lag: Tottenham Hotspurs\n"
"      adresse: London, United Kingdom\n"
"      spillereneCount: 2\n"
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
"            hjemmeScorereneCount: 1\n"
"            hjemmeScorerene:\n"
"            - spiller: 1\n"
"            borteScorereneCount: 3\n"
"            borteScorerene:\n"
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
    
    // Test 0: 
    auto err = Parser::decodeIdrettene(idrettene, encodedIdrettene);
    Test::assertNot(err, 0, 
        "auto err = Parser::decodeIdrettene()");


    auto encodedDecodedIdrettene = Parser::encodeIdrettene(idrettene);

	std::cout << "string compare --- > " << strcmp(encodedIdrettene, encodedDecodedIdrettene.c_str()) << '\n';
    std::cout << "STRING COMPARE --- > " << encodedDecodedIdrettene.compare(encodedIdrettene) << "\n";
    

    //
    // Testing character by character
    // 
	for (std::size_t i = 0; i < encodedDecodedIdrettene.size(); ++i) 
	{
		auto c1 = encodedDecodedIdrettene[i];
		auto c2 = encodedIdrettene[i];
		if (c1 != c2) {
			std::cout << "\nc1 = " << ((c1 == '\n')? "\\n":"SOMETHING ELSE") << "  c2 = " << ((c2 == '\n') ? "\\n" : "SOMETHING ELSE") << '\n';
			assert(false);
		}
		std::cout << c1;
	}

    // Test 1:
	Test::assertEqual(encodedDecodedIdrettene, encodedIdrettene, 1, 
                         "(encodedDecodedIdrettene == encodedIdrettene)");
}


void test_ParserDecodeAndEncodeSpillerene() 
{

    constexpr char encodedSpillerene[] = ""
"sisteguid: 7\n"
"\n"
"spillereneCount: 8\n"
"spillerene:\n"
"\n"
"- spiller: Ronny Knarvik\n"
"  guid: 0\n"
"  addresse: Bergen, Norway\n"
"\n"
"- spiller: Erik Huseklepp\n"
"  guid: 1\n"
"  addresse: Bergen, Norway\n"
"\n"
"- spiller: Arild Østebø\n"
"  guid: 2\n"
"  addresse: Trondheim, Norway\n"
"\n"
"- spiller: Andre Hansen\n"
"  guid: 3\n"
"  addresse: Trondheim, Norway\n"
"\n"
"- spiller: Alexis Sanchez\n"
"  guid: 4\n"
"  addresse: Manchester, United Kingdom\n"
"\n"
"- spiller: Paul Pogba\n"
"  guid: 5\n"
"  addresse: Manchester, United Kingdom\n"
"\n"
"- spiller: Harry Kane\n"
"  guid: 6\n"
"  addresse: London, United Kingdom\n"
"\n"
"- spiller: Son Hueng-min\n"
"  guid: 7\n"
"  addresse: London, United Kingdom\n";
    
    DB::Spillerene spillerene;

    // Test 1: 
    auto err = Parser::decodeSpillerene(spillerene, encodedSpillerene);
    Test::assertNot(err, 0, 
        "auto err = Parser::decodeSpillerene()");


    // Test 2:
    auto encodedDecodedSpillerene = Parser::encodeSpillerene(spillerene); 
    Test::assertEqual(encodedDecodedSpillerene, encodedSpillerene, 1, 
                         "(encodedDecodedSpillerene == encodedSpillerene)");
}


void test_ParserDecodeResultatene() 
{
    constexpr char encodedResultatene[] = ""
"resultateneCount: 2\n"
"resultatene:\n"
"\n"
"- resultat:\n"
"  idrett: Fotball\n"
"  divisjon: Eliteserien 2018\n"
"  hjemmelag: Brann\n"
"  bortelag: Rosenborg\n"
"  dato: 2012-03-19\n"
"  overtid: true\n"
"  hjemmepoengCount: 4\n"
"  hjemmepoeng:\n"
"  - spiller: 0\n"
"  - spiller: 0\n"
"  - spiller: 0\n"
"  - spiller: 1\n"
"  bortepoengCount: 2\n"
"  bortepoeng:\n"
"  - spiller: 0\n"
"  - spiller: 0\n"
"\n"
"- resultat:\n"
"  idrett: Fotball\n"
"  divisjon: Premier League 2017/2018\n"
"  hjemmelag: Manchester United\n"
"  bortelag: Tottenham\n"
"  dato: 2012-03-19\n"
"  overtid: false\n"
"  hjemmepoengCount: 1\n"
"  hjemmepoeng:\n"
"  - spiller: 1\n"
"  bortepoengCount: 3\n"
"  bortepoeng:\n"
"  - spiller: 1\n"
"  - spiller: 1\n"
"  - spiller: 0\n";


    DB::Idrettene idrettene;
    
    // Test 1: 
    auto err = Parser::decodeResultatene(idrettene, encodedResultatene);
    Test::assertNot(err, 0, 
        "auto err = Parser::decodeResultatene()");


}
void test_ParserDecodeDivisjon() 
{

    constexpr char encodedDivisjon[] = ""
"divisjon: Eliteserien\n"
"\n"
"lageneCount: 2\n"
"lagene:\n"
"\n"
"- lag: Brann\n"
"  adresse: Bergen, Norway\n"
"  spillereneCount: 2\n"
"  spillerene:\n"
"  - spiller: 0\n"
"  - spiller: 1\n"
"\n"
"- lag: Rosenborg\n"
"  adresse: Trondheim, Norway \n"
"  spillereneCount: 2\n"
"  spillerene: \n"
"  - spiller: 2\n"
"  - spiller: 3\n"
"\n"
"terminliste:\n"
"  hjemmelagene:\n"
"\n"
"  - hjemmelag: Brann\n"
"    bortelagene:\n"
"\n"
"    - bortelag: Rosenborg\n"
"      dato: 2012-03-19\n"
"\n"
"  - hjemmelag: Rosenborg\n"
"    bortelagene:\n"
"\n"
"    - bortelag: Brann\n"
"      dato: 2012-03-19\n";


    DB::Divisjon divisjon;
    
    // Test 1: 
    auto err = Parser::decodeDivisjon(divisjon, encodedDivisjon);
    Test::assertNot(err, 0, 
        "auto err = Parser::decodeDivisjon()");

}

void test_Parser() 
{
    std::cout << "\n\nRunning test_ParserDecodeAndEncodeIdrettene()\n\n";    
    test_ParserDecodeAndEncodeIdrettene();

    
    std::cout << "\n\nRunning test_ParserDecodeAndEncodeSpillerene()\n\n";    
    test_ParserDecodeAndEncodeSpillerene();


    std::cout << "\n\nRunning test_ParserDecodeResultatene()\n\n";    
    test_ParserDecodeResultatene();


    std::cout << "\n\nRunning test_ParserDecodeDivisjon()\n\n";    
    test_ParserDecodeDivisjon();

}

}