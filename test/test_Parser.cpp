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
    
    using std::size_t;
    
    DB::Idrettene idrettene;
    size_t testCount = 0;
    // Test 0: 
    auto err = Parser::decodeIdrettene(idrettene, encodedIdrettene);
    Test::assertNot(err, testCount++);

    auto encodedDecodedIdrettene = Parser::encodeIdrettene(idrettene);

    //
    // Testing character by character
    // 
	for (std::size_t i = 0; i < encodedDecodedIdrettene.size(); ++i) 
	{
		auto c1 = encodedDecodedIdrettene[i];
		auto c2 = encodedIdrettene[i];
		if (c1 != c2) {
		//	std::cout << "\nc1 = " << c1 << "  c2 = " << c2 << '\n';
			assert(false);
		}
		//std::cout << c1;
	}

    // Test 1:
	Test::assertEqual(
        encodedDecodedIdrettene, 
        encodedIdrettene, 
        testCount++); 
}


void test_ParserDecodeAndEncodeSpillerene() 
{
    constexpr char encodedSpillerene[] = ""
"autoIncrementer: 7\n"
"\n"
"spillereneCount: 8\n"
"spillerene:\n"
"\n"
"- spiller: Ronny Knarvik\n"
"  guid: 0\n"
"  adresse: Bergen, Norway\n"
"\n"
"- spiller: Erik Huseklepp\n"
"  guid: 1\n"
"  adresse: Bergen, Norway\n"
"\n"
"- spiller: Arild Østebø\n"
"  guid: 2\n"
"  adresse: Trondheim, Norway\n"
"\n"
"- spiller: Andre Hansen\n"
"  guid: 3\n"
"  adresse: Trondheim, Norway\n"
"\n"
"- spiller: Alexis Sanchez\n"
"  guid: 4\n"
"  adresse: Manchester, United Kingdom\n"
"\n"
"- spiller: Paul Pogba\n"
"  guid: 5\n"
"  adresse: Manchester, United Kingdom\n"
"\n"
"- spiller: Harry Kane\n"
"  guid: 6\n"
"  adresse: London, United Kingdom\n"
"\n"
"- spiller: Son Hueng-min\n"
"  guid: 7\n"
"  adresse: London, United Kingdom\n";
    
    DB::Spillerene spillerene;
    std::size_t testCount = 0;

    // Test 1: 
    auto err = Parser::decodeSpillerene(spillerene, encodedSpillerene);
    Test::assertNot(err, testCount++);


    auto encodedDecodedSpillerene = Parser::encodeSpillerene(spillerene); 

    //
    // Testing character by character
    // 
    for (std::size_t i = 0; i < encodedDecodedSpillerene.size(); ++i) 
    {
        auto c1 = encodedDecodedSpillerene[i];
        auto c2 = encodedSpillerene[i];
        if (c1 != c2) {
       //     std::cout << "\nc1 = " << c1 << "  c2 = " << c2 << '\n';
            assert(false);
        }
      //  std::cout << c1;
    }

    // Test 2:
    Test::assertEqual(
        encodedDecodedSpillerene, 
        encodedSpillerene, 
        testCount++);
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


    std::vector<DB::ResultatWithKeys> resultatene;
    std::size_t testCount = 0;
    
    // Test 0: 
    auto err = Parser::decodeResultatene(resultatene, encodedResultatene);
   
    Test::assertNot(err, testCount++); 

    // @TODO - create assert greated than function - JSolsvik 17.03.18
    Test::assertTrue(
        resultatene.size() > 0, 
        testCount++);

    if (!(resultatene.size() > 0 > 0))
        return;

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

    using std::size_t;
    size_t testCount = 0;
    DB::Divisjon divisjon;
    
    // Test 1: 
    auto err = Parser::decodeDivisjon(divisjon, encodedDivisjon);
    Test::assertNot(
        err,
        testCount++);

    Test::assertTrue(
        divisjon.lagene.size() > 0, 
        testCount++);

    if (divisjon.lagene.size() == 0)
        return;

    Test::assertTrue(
        divisjon.terminListe["Brann"]["Rosenborg"].dato == "2012-03-19",
        testCount++);
}

using std::string;
using std::vector;
using std::size_t;

void test_ParserEncodeResultateneDivisjon() 
{   

    
    size_t testCount = 0;
    vector<DB::ResultatWithKeys> resultateneDivisjon;
    constexpr char encodedResultateneDivisjon[] = "test_ParserEncodeResultateneDivisjon";
    string encodedResultatene = Parser::encodeResultateneDivisjon(resultateneDivisjon);

    Test::assertEqual(
        encodedResultatene, 
        encodedResultateneDivisjon, 
        testCount++);
}

void test_ParserEncodeResultateneIdrett() 
{
    size_t testCount = 0;
    vector<DB::ResultatWithKeys> resultateneIdrett;
    constexpr char encodedResultateneIdrett[] = "test_ParserEncodeResultateneIdrett";
    string encodedResultatene = Parser::encodeResultateneIdrett(resultateneIdrett);

    Test::assertEqual(
        encodedResultatene, 
        encodedResultateneIdrett, 
        testCount++);
}

void test_ParserTabellDivisjon() 
{
    size_t testCount = 0;
    DB::Tabell tabellDivisjon;
    constexpr char encodedTabellDivisjon[] = "test_ParserTabellDivisjon";
    string _encodedTabellDivisjon = Parser::encodeTabellDivisjon(tabellDivisjon);

    Test::assertEqual(
        _encodedTabellDivisjon, 
        encodedTabellDivisjon, 
        testCount++);
}

void test_ParserTabellIdrett() 
{   
    size_t testCount = 0;
    vector<DB::Tabell> tabellIdrett;
    constexpr char encodedTabellIdrett[] = "test_ParserTabellIdrett";
    string _encodedTabellIdrett = Parser::encodeTabelleneIdrett(tabellIdrett);

    Test::assertEqual(
        _encodedTabellIdrett, 
        encodedTabellIdrett, 
        testCount++);
}

void test_ParserTerminliste() 
{
    size_t testCount = 0;
    DB::Terminliste terminliste;
    constexpr char encodedTerminliste[] = "test_ParserTerminliste";
    string _encodedTerminliste = Parser::encodeTerminliste(terminliste);

    Test::assertEqual(
        _encodedTerminliste, 
        encodedTerminliste, 
        testCount++);
}

void test_ParserToppscorereneDivisjon() 
{
    size_t testCount = 0;
    DB::Toppscorerene toppscorerene;
    constexpr char encodedToppscorerene[] = "test_ParserToppscorereneDivisjon";
    string _encodedToppscorerene = Parser::encodeToppscorereneDivisjon(toppscorerene);

    Test::assertEqual(
        _encodedToppscorerene, 
        encodedToppscorerene, 
        testCount++);
}

void test_ParserToppscorereneLag() 
{
    size_t testCount = 0;
    DB::Toppscorerene toppscorerene;
    constexpr char encodedToppscorerene[] = "test_ParserToppscorereneLag";
    string _encodedToppscorerene = Parser::encodeToppscorereneLag(toppscorerene);

    Test::assertEqual(
        _encodedToppscorerene, 
        encodedToppscorerene, 
        testCount++);
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


    std::cout << "\n\nRunning test_ParserEncodeResultateneDivisjon()\n\n";    
    test_ParserEncodeResultateneDivisjon();

    std::cout << "\n\nRunning test_ParserEncodeResultateneIdrett()\n\n";    
    test_ParserEncodeResultateneIdrett();

    std::cout << "\n\nRunning test_ParserTabellDivisjon()\n\n";    
    test_ParserTabellDivisjon();

    std::cout << "\n\nRunning test_ParserTabellIdrett()\n\n";    
    test_ParserTabellIdrett();

    std::cout << "\n\nRunning test_ParserTerminliste()\n\n";    
    test_ParserTerminliste();

    std::cout << "\n\nRunning test_ParserToppscorereneDivisjon()\n\n";    
    test_ParserToppscorereneDivisjon();

    std::cout << "\n\nRunning test_ParserToppscorereneLag()\n\n";    
    test_ParserToppscorereneLag();

}

}