#include <gruppe32/Test.hpp>
#include <gruppe32/Parser.hpp>
#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>

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
    
    // Test 1: 
    auto err = Parser::decodeIdrettene(idrettene, encodedIdrettene);
    Test::assertNot(err, 0, 
        "auto err = Parser::decodeIdrettene()");


    // Test 2:
	auto encodedDecodedIdrettene = Parser::encodeIdrettene(idrettene); 
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

void test_Parser() 
{
    std::cout << "\n\nRunning test_ParserDecodeAndEncodeIdrettene()\n\n";    
    test_ParserDecodeAndEncodeIdrettene();

    
    std::cout << "\n\nRunning test_ParserDecodeAndEncodeSpillerene()\n\n";    
    test_ParserDecodeAndEncodeSpillerene();
}

}