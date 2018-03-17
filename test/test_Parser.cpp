#include <gruppe32/Test.hpp>
#include <gruppe32/Parser.hpp>
#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>

#include <cassert>
#include <cstring>

namespace gruppe32
{

void test_DecodeAndEncodeIdrettene() 
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
    auto err = Decode::idrettene(idrettene, encodedIdrettene);
    Test::assertNot(err, testCount++);

    auto encodedDecodedIdrettene = Encode::idrettene(idrettene);

    //
    // Testing character by character
    // 
	for (std::size_t i = 0; i < encodedDecodedIdrettene.size(); ++i) 
	{
		auto c1 = encodedDecodedIdrettene[i];
		auto c2 = encodedIdrettene[i];
		if (c1 != c2) {
		//	std::cout << "\nc1 = " << c1 << "  c2 = " << c2 << '\n';
		//	assert(false);
		}
		//std::cout << c1;
	}

    // Test 1:
	Test::assertEqual(
        encodedDecodedIdrettene, 
        encodedIdrettene, 
        testCount++); 
}


void test_DecodeAndEncodeSpillerene() 
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
    auto err = Decode::spillerene(spillerene, encodedSpillerene);
    Test::assertNot(err, testCount++);


    auto encodedDecodedSpillerene = Encode::spillerene(spillerene); 

    //
    // Testing character by character
    // 
    for (std::size_t i = 0; i < encodedDecodedSpillerene.size(); ++i) 
    {
        auto c1 = encodedDecodedSpillerene[i];
        auto c2 = encodedSpillerene[i];
        if (c1 != c2) {
       //     std::cout << "\nc1 = " << c1 << "  c2 = " << c2 << '\n';
    //        assert(false);
        }
      //  std::cout << c1;
    }

    // Test 2:
    Test::assertEqual(
        encodedDecodedSpillerene, 
        encodedSpillerene, 
        testCount++);
}


void test_DecodeResultatene() 
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
"  hjemmeScorereneCount: 4\n"
"  hjemmeScorerene:\n"
"  - spiller: 0\n"
"  - spiller: 0\n"
"  - spiller: 0\n"
"  - spiller: 1\n"
"  borteScorereneCount: 2\n"
"  borteScorerene:\n"
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
"  hjemmeScorereneCount: 1\n"
"  hjemmeScorerene:\n"
"  - spiller: 1\n"
"  borteScorereneCount: 3\n"
"  borteScorerene:\n"
"  - spiller: 1\n"
"  - spiller: 1\n"
"  - spiller: 0\n";


    std::vector<DB::ResultatWithKeys> resultatene;
    std::size_t testCount = 0;
    
    // Test 0: 
    auto err = Decode::resultatene(resultatene, encodedResultatene);
   
    Test::assertNot(err, testCount++); 

    // @TODO - create assert greated than function - JSolsvik 17.03.18
    Test::assertTrue(
        resultatene.size() > 0, 
        testCount++);

    if (!(resultatene.size() > 0 > 0))
        return;

}
void test_DecodeDivisjon() 
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
    auto err = Decode::divisjon(divisjon, encodedDivisjon);
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

void test_EncodeResultateneDivisjon() 
{   

    
    size_t testCount = 0;
    auto resultateneDivisjon = vector<DB::ResultatWithKeys> {
        DB::ResultatWithKeys{
            "Fotball",
            "Eliteserien 2018",
            "Brann",
            "Rosenborg",
            "2012-03-19",
            true,
            true
        },
    };
    resultateneDivisjon[0].hjemmeScorerene = vector<size_t> {
        0,
        0,
        0,
        1
    };
    resultateneDivisjon[0].borteScorerene = vector<size_t> {
        0,
        0
    };

    constexpr char encodedResultateneDivisjon[] = ""
"divisjon: Eliteserien 2018\n"
"\n"
"resultateneCount: 1\n"
"resultatene:\n"
"\n"
"- resultat:\n"
"  hjemmelag: Brann\n"
"  bortelag: Rosenborg\n"
"  dato: 2012-03-19\n"
"  overtid: true\n"
"  hjemmeScorereneCount: 4\n"
"  hjemmeScorerene:\n"
"  - spiller: 0\n"
"  - spiller: 0\n"
"  - spiller: 0\n"
"  - spiller: 1\n"
"  borteScorereneCount: 2\n"
"  borteScorerene:\n"
"  - spiller: 0\n"
"  - spiller: 0\n";

    string encodedResultatene = Encode::resultateneDivisjon(resultateneDivisjon, "Eliteserien 2018");

    Test::assertEqual(
        encodedResultatene, 
        encodedResultateneDivisjon, 
        testCount++);
}

void test_EncodeResultateneIdrett() 
{
    size_t testCount = 0;
    auto resultateneIdrett = vector<DB::ResultatWithKeys> {
        DB::ResultatWithKeys{
            "Fotball",
            "Eliteserien 2018",
            "Brann",
            "Rosenborg",
            "2012-03-19",
            true,
            true
        },
    };
    resultateneIdrett[0].hjemmeScorerene = vector<size_t> {
        1,
        0,
        0,
        1
    };
    resultateneIdrett[0].borteScorerene = vector<size_t> {
        0,
        2
    };


    constexpr char encodedResultateneIdrett[] = ""
"idrett: Fotball\n"
"\n"
"resultateneCount: 1\n"
"resultatene:\n"
"\n"
"- resultat:\n"
"  hjemmelag: Brann\n"
"  bortelag: Rosenborg\n"
"  dato: 2012-03-19\n"
"  overtid: true\n"
"  hjemmeScorereneCount: 4\n"
"  hjemmeScorerene:\n"
"  - spiller: 1\n"
"  - spiller: 0\n"
"  - spiller: 0\n"
"  - spiller: 1\n"
"  borteScorereneCount: 2\n"
"  borteScorerene:\n"
"  - spiller: 0\n"
"  - spiller: 2\n";

    string encodedResultatene = Encode::resultateneIdrett(resultateneIdrett, "Fotball");

    Test::assertEqual(
        encodedResultatene, 
        encodedResultateneIdrett, 
        testCount++);
}

void test_EncodeTabellDivisjon() 
{
    using std::vector;

    size_t testCount = 0;
    const auto tabellDivisjon = DB::Tabell {
        "Fotball",
        "Eliteserien 2018",
        DB::Idrett::SEIER_3_UAVGJORT_1_TAP_0,
        vector<DB::Tabell::Lag> {
            DB::Tabell::Lag{
                "Brann",
                1,
                16,
                18,
                2,
                12,
                7,
                5,
                1,
                2
            },
            DB::Tabell::Lag {
                "Rosenborg",
                2,
                7,
                7,
                12,
                2,
                18,
                2,
                1,
                5
            }
        }
    };
    constexpr char encodedTabellDivisjon[] = ""
"tabell: Eliteserien 2018\n"
"tabelltype: 310\n"
"\n"
"tabellLageneCount: 2\n"
"tabellLagene:\n"
"\n"
"- lag: Brann\n"
"  plassering: 1\n"
"  poeng: 16\n"
"  hjemmeScoringer: 18\n"
"  hjemmeBaklengs: 2\n"
"  borteScoringer: 12\n"
"  borteBaklengs: 7\n"
"  seier: 5\n"
"  uavgjort: 1\n"
"  tap: 2\n"
"\n"
"- lag: Rosenborg\n"
"  plassering: 2\n"
"  poeng: 7\n"
"  hjemmeScoringer: 7\n"
"  hjemmeBaklengs: 12\n"
"  borteScoringer: 2\n"
"  borteBaklengs: 18\n"
"  seier: 2\n"
"  uavgjort: 1\n"
"  tap: 5\n";

    string _encodedTabellDivisjon = Encode::tabellDivisjon(tabellDivisjon);

    Test::assertEqual(
        _encodedTabellDivisjon, 
        encodedTabellDivisjon, 
        testCount++);
}

void test_EncodeTabelleneIdrett() 
{   
    using std::vector;
    
    size_t testCount = 0;
    const auto tabelleneIdrett = vector<DB::Tabell> {
        DB::Tabell {
            "Fotball",
            "Eliteserien 2018",
            DB::Idrett::SEIER_3_UAVGJORT_1_TAP_0,
            vector<DB::Tabell::Lag> {
                DB::Tabell::Lag{
                    "Brann",
                    1,
                    16,
                    18,
                    2,
                    12,
                    7,
                    5,
                    1,
                    2
                },
                DB::Tabell::Lag {
                    "Rosenborg",
                    2,
                    7,
                    7,
                    12,
                    2,
                    18,
                    2,
                    1,
                    5
                }
            }
        },
    };
    constexpr char encodedTabelleneIdrett[] = ""
"idrett: Fotball\n"
"tabelltype: 310\n"
"\n"
"tabelleneCount: 1\n"
"tabellene:\n"
"\n"
"- tabell: Eliteserien 2018\n"
"\n"
"  tabellLageneCount: 2\n"
"  tabellLagene:\n"
"\n"
"  - lag: Brann\n"
"    plassering: 1\n"
"    poeng: 16\n"
"    hjemmeScoringer: 18\n"
"    hjemmeBaklengs: 2\n"
"    borteScoringer: 12\n"
"    borteBaklengs: 7\n"
"    seier: 5\n"
"    uavgjort: 1\n"
"    tap: 2\n"
"\n"
"  - lag: Rosenborg\n"
"    plassering: 2\n"
"    poeng: 7\n"
"    hjemmeScoringer: 7\n"
"    hjemmeBaklengs: 12\n"
"    borteScoringer: 2\n"
"    borteBaklengs: 18\n"
"    seier: 2\n"
"    uavgjort: 1\n"
"    tap: 5\n";

    string _encodedTabelleneIdrett = Encode::tabelleneIdrett(
        tabelleneIdrett, 
        "Fotball", 
        DB::Idrett::SEIER_3_UAVGJORT_1_TAP_0);


    //
    // Testing character by character
    // 
   /* for (std::size_t i = 0; i < _encodedTabelleneIdrett.size(); ++i)
    {
        auto c1 = _encodedTabelleneIdrett[i];
        auto c2 = encodedTabelleneIdrett[i];
        if (c1 != c2) {
          //  std::cout << "\nc1 = " << ((c1=='\n')?"newline":"somethingelse") 
            //                      << "  c2 = " << ((c2=='\n')?"newline":"somethingelse") << '\n';
        //    assert(false);
        }
      //  std::cout << c1;
    }*/

    Test::assertEqual(
        _encodedTabelleneIdrett, 
        encodedTabelleneIdrett, 
        testCount++);
}

void test_EncodeTerminliste() 
{
    using std::map;
    
    size_t testCount = 0;
    const auto terminliste = DB::Terminliste {
        "Eliteserien 2018", 
        map<string, map<string,string>> {
            { "Brann", map<string, string> {
                    { "Rosenborg", "2012-03-19" } 
                }
            },
            { "Rosenborg", map<string, string> {
                    { "Brann", "2012-03-19" }
                }
            },
        }
    };
    constexpr char encodedTerminliste[] = ""
"divisjon: Eliteserien 2018\n"
"\n"
"terminliste:\n"
"  lageneCount: 2\n"
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

    string _encodedTerminliste = Encode::terminliste(terminliste);

    Test::assertEqual(
        _encodedTerminliste, 
        encodedTerminliste, 
        testCount++);
}

void test_EncodeToppscorereneDivisjon() 
{
    using std::vector;

    size_t testCount = 0;
    const auto toppscorerene = vector<DB::Toppscorer> {
        DB::Toppscorer{"Ronny Knarvik", 20},
        DB::Toppscorer{"Erik Huseklepp", 18},
        DB::Toppscorer{"Arild Østebø", 9},
        DB::Toppscorer{"Andre Hansen", 8}
    };
    constexpr char encodedToppscorerene[] = ""
"divisjon: Eliteserien 2018\n"
"\n"
"toppscorereneCount: 4\n"
"toppscorerene:\n"
"\n"
"- spiller: Ronny Knarvik\n"
"  score: 20\n"
"\n"
"- spiller: Erik Huseklepp\n"
"  score: 18\n"
"\n"
"- spiller: Arild Østebø\n"
"  score: 9\n"
"\n"
"- spiller: Andre Hansen\n"
"  score: 8\n";

    string _encodedToppscorerene = Encode::toppscorereneDivisjon(toppscorerene, "Eliteserien 2018");

    Test::assertEqual(
        _encodedToppscorerene, 
        encodedToppscorerene, 
        testCount++);
}

void test_EncodeToppscorereneLag() 
{
    using std::vector;

    size_t testCount = 0;
    const auto toppscorerene = vector<DB::Toppscorer> {
        DB::Toppscorer{"Ronny Knarvik", 20},
        DB::Toppscorer{"Erik Huseklepp", 18}
    };
    constexpr char encodedToppscorerene[] = ""
"lag: Brann\n"
"\n"
"toppscorereneCount: 2\n"
"toppscorerene:\n"
"\n"
"- spiller: Ronny Knarvik\n"
"  score: 20\n"
"\n"
"- spiller: Erik Huseklepp\n"
"  score: 18\n";


    string _encodedToppscorerene = Encode::toppscorereneLag(toppscorerene, "Brann");

    Test::assertEqual(
        _encodedToppscorerene, 
        encodedToppscorerene, 
        testCount++);
}


void test_Parser() 
{
    std::cout << "\n\nRunning test_DecodeAndEncodeIdrettene()\n\n";    
    test_DecodeAndEncodeIdrettene();

    
    std::cout << "\n\nRunning test_DecodeAndEncodeSpillerene()\n\n";    
    test_DecodeAndEncodeSpillerene();


    std::cout << "\n\nRunning test_DecodeResultatene()\n\n";    
    test_DecodeResultatene();


    std::cout << "\n\nRunning test_DecodeDivisjon()\n\n";    
    test_DecodeDivisjon();


    std::cout << "\n\nRunning test_EncodeResultateneDivisjon()\n\n";    
    test_EncodeResultateneDivisjon();

    std::cout << "\n\nRunning test_EncodeResultateneIdrett()\n\n";    
    test_EncodeResultateneIdrett();

    std::cout << "\n\nRunning test_EncodeTabellDivisjon()\n\n";    
    test_EncodeTabellDivisjon();

    std::cout << "\n\nRunning test_EncodeTabelleneIdrett()\n\n";    
    test_EncodeTabelleneIdrett();

    std::cout << "\n\nRunning test_EncodeTerminliste()\n\n";    
    test_EncodeTerminliste();

    std::cout << "\n\nRunning test_EncodeToppscorereneDivisjon()\n\n";    
    test_EncodeToppscorereneDivisjon();

    std::cout << "\n\nRunning test_EncodeToppscorereneLag()\n\n";    
    test_EncodeToppscorereneLag();

}

}