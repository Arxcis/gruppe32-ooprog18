#include <gruppe32/Parser.hpp>

#include <string>
#include <iomanip>
#include <utility>
#include <map>
#include <sstream>

namespace gruppe32 
{

auto Parser::nextLine() -> std::string
{
    endofline   = strview.find('\n', startofline);
    startofline = strview.find_first_of(whitelistedCharacters, startofline);

    if (startofline == std::string::npos) {
        std::cout << "\nPARSER ERROR ---->>> (startofline == std::string::npos)\n\n"
                  << "Line: " << linecount;
        assert(false && "No whitelisted characters found after new-line character!! Line:");
    }
    if (endofline == std::string::npos) {
        std::cout << "\nPARSER ERROR ---->>> (endofline == std::string::npos)\n\n"
                  << "Line: " << linecount;
        assert(false && "No end of file (new-line) character found! Line:");
    }

    linecount++;
    // Skip empty lines in between and eat whitespace
    while (endofline-startofline <= 0) {

        startofline = endofline+1;
        endofline   = strview.find('\n', startofline);
        startofline = strview.find_first_of(whitelistedCharacters, startofline);

        if (startofline == std::string::npos) {
            std::cout << "\nPARSER ERROR ---->>> (startofline == std::string::npos)\n\n"
                      << "Line: " << linecount;
            assert(false && "No whitelisted characters found after new-line character!! Line:");
        }
        if (endofline == std::string::npos) {
            std::cout << "PARSER ERROR ---->>> (endofline == std::string::npos)"
                      << "Line: " << linecount;
            assert(false && "No end of file (new-line) character found! Line:");
        }
        linecount++;
    }

    auto line = std::string { 
        strview.substr(startofline, endofline-startofline)
    };        
    auto lastCharacter = (endofline-startofline)-1;
    auto lastValidCharacter = line.find_last_of(whitelistedCharacters);
    if (lastValidCharacter != lastCharacter) {

        std::cout << "\nPARSER ERROR ---->>> (lastValidCharacter != lastCharacter)\n\n"
                  << "Line: "                          << linecount << '\n'
                  << "Linetext: "                      << line << '\n'
                  << "index lastValidCharacter: "      << lastValidCharacter <<'\n'
                  << "index lastCharacter: "           << lastCharacter << '\n'
                  << "line[lastValidCharacter]: "      << line[lastValidCharacter] <<'\n'
                  << "line[lastCharacter]: "           << line[lastCharacter] << '\n'
                  << "int(line[lastValidCharacter]): " << int(line[lastValidCharacter]) <<'\n'
                  << "int(line[lastCharacter]): "      << int(line[lastCharacter]) << '\n';
        assert(false && "Empty space not allowed after the last character on a line!! Line:");
    }

/*   std::cout << std::setw(40) << std::left << line
              << " | start: "  << startofline
              << " | end: "    << endofline
              << " | DIFF: "   << endofline-startofline << '\n';
*/

    startofline = endofline+1;
    return line;
};

auto Parser::nextStringString() -> pair<string,string>
{
    auto line = nextLine();

    string key = line.substr(0, line.find(":"));
    string valueString = "";

    if (line.find(":")+2 < line.size())
        valueString = line.substr(line.find(":")+2);

    // @debug
    std::cout << std::setw(35) << std::left 
              << line  

              << " key: " 
              << std::setw(18) << std::left 
              << key
              
              << " val: " 
              << valueString
              << '\n';

    return pair<string,string>{ key, valueString };
};


auto Parser::nextStringUint() -> pair<string, size_t>
{
    auto[key, valueString] = nextStringString();
    return pair<string, size_t>{key, std::stoi(valueString)};
};

auto Parser::nextStringBool() -> pair<string,bool>
{
    auto[key, valueString] = nextStringString();
    bool trueFalse;
    if (valueString == "true") {
        trueFalse = true;
    }
    else if (valueString == "false") {
        trueFalse = false;
    }
    else {
       assert(false && "Boolean have to be either true or false");
    }
    return pair<string,bool>{key, trueFalse};
};


auto Decode::dataIdrettene(DB::Idrettene& idrettene, string_view strview) -> Decode::Error 
{
    auto gen = Parser{strview, 0};

    auto[idretteneCountkey, idretteneCount] = gen.nextStringUint();

    gen.nextLine(); // ignore idrettene:

    for (size_t iIdrett = 0; iIdrett < idretteneCount; ++iIdrett)
    {

        auto[idrettKey, idrettNavn]     = gen.nextStringString();
        auto[tabelltypekey, tabelltype] = gen.nextStringUint();
        auto[divisjoneneCountkey, divisjoneneCount] = gen.nextStringUint();

        // Create Idrett
        auto idrett = new DB::Idrett {
            idrettNavn,
            DB::Idrett::TabellType(tabelltype)
        };

        gen.nextLine(); // ignore divisjonene:

        for (size_t iDivisjon = 0; iDivisjon < divisjoneneCount; ++iDivisjon)
        {
            auto[divisjonkey, divisjonNavn] = gen.nextStringString();
            auto[lageneCountkey, lageneCount] = gen.nextStringUint();

            // Create Divisjon
            auto divisjon = DB::Divisjon {
                divisjonNavn
            };

            gen.nextLine(); // ignore lagene:

            for (size_t iLag = 0; iLag < lageneCount; ++iLag)
            {
                auto[lagkey, lagName]     = gen.nextStringString();
                auto[adressekey, adresse] = gen.nextStringString();
                auto[spillereneCountkey, spillereneCount] = gen.nextStringUint();
                
                auto lag = DB::Lag {
                    lagName,
                    adresse
                };

                gen.nextLine(); // ignore spillerene:
                
                for (size_t iSpiller = 0; iSpiller < spillereneCount; ++iSpiller)
                {

                    auto[spillerkey, spiller] = gen.nextStringUint();
                    lag.spillerene.push_back(spiller);         
                }
                divisjon.lagene.push_back(lag);
            }   

            
            auto whoareouy = gen.nextLine(); // ignore terminliste:

            for (size_t iHjemmelag = 0; iHjemmelag < lageneCount; ++iHjemmelag)
            {

                auto[hjemmelagkey, hjemmelag] = gen.nextStringString();

                gen.nextLine(); // ignore bortelagene:

                for (size_t iBortelag = 0; iBortelag < lageneCount-1; ++iBortelag)
                {
                    auto[bortelagkey, bortelag] = gen.nextStringString();
                    auto[datokey, dato]         = gen.nextStringString();
                    auto[resultkey, isResult]   = gen.nextStringBool();

                    // Create Resultat
                    auto resultat = DB::Resultat {
                        dato
                    };

                    if (isResult) 
                    {
                        auto[overtidkey, overtid] = gen.nextStringBool();
                        auto[hjemmepoengCountkey, hjemmepoengCount] = gen.nextStringUint();

                        resultat.spilt = true;
                        resultat.overtid = overtid;

                        gen.nextLine(); // ignore hjemmepoeng:

                        for (size_t iHjemmepoeng = 0; iHjemmepoeng < hjemmepoengCount; ++iHjemmepoeng)
                        {
                            auto[spillerkey, spiller] = gen.nextStringUint();
                            resultat.hjemmeScorerene.push_back(spiller);
                        }
                        
                        auto[bortepoengCountKey, bortepoengCount] = gen.nextStringUint();

                        gen.nextLine(); // ignore 'bortepoeng:'

                        for (size_t iBortepoeng = 0; iBortepoeng < bortepoengCount; ++iBortepoeng)
                        {
                            auto[spillerkey, spiller] = gen.nextStringUint();
                            resultat.borteScorerene.push_back(spiller);
                        }
                    }
                    divisjon.terminliste[hjemmelag][bortelag] = resultat;
                }
            }
            idrett->divisjonene.push_back(divisjon);
        }
        // Pushing idrett into ListTool
        idrettene.data->add(idrett);
    }
    return 0;
}


auto Decode::dataSpillerene(DB::Spillerene& spillerene, string_view strview) -> Decode::Error
{
 
    auto gen = Parser{strview};

    auto[autoIncrementerKey, autoIncrementer] = gen.nextStringUint();
    auto[spillereneCountKey, spillereneCount] = gen.nextStringUint();

    spillerene.autoIncrementer = autoIncrementer;

    gen.nextLine(); // ignore 'spillerene:'

    for (size_t iSpiller = 0; iSpiller < spillereneCount; ++iSpiller)
    {
        auto[spillerNameKey, spillerName] = gen.nextStringString();
        auto[guidKey, guid]               = gen.nextStringUint();
        auto[adresseKey, adresse]         = gen.nextStringString();
    
        auto spiller = new DB::Spiller {
            guid,
            spillerName,
            adresse
        };
        spillerene.data->add(spiller);
    }
    return 0;    
}


auto Decode::inputResultatene(vector<DB::InputResultat>& resultatene, string_view strview) -> Decode::Error
{
    auto gen = Parser{strview};

    auto[resultateneCountKey, resultateneCount] = gen.nextStringUint();

    gen.nextLine(); // ignore 'resultatene:''

    for (size_t iResultat = 0; iResultat < resultateneCount; ++iResultat)
    {

        gen.nextLine(); // ignore '- resultat:'

        auto[idrettKey, idrett]       = gen.nextStringString();
        auto[divisjonKey, divisjon]   = gen.nextStringString();
        auto[hjemmelagKey, hjemmelag] = gen.nextStringString();
        auto[bortelagKey, bortelag]   = gen.nextStringString();
        auto[datoKey, dato]           = gen.nextStringString();
        auto[overtidKey, overtid]     = gen.nextStringBool();
        auto[hjemmepoengCountKey, hjemmepoengCount] = gen.nextStringUint();

        bool harSpiltKamp = false;
        auto resultat = DB::InputResultat {
            idrett,
            divisjon,
            hjemmelag,
            bortelag,
            dato,
            harSpiltKamp,
            overtid
        };

        gen.nextLine(); // ignore 'hjemmepoeng:'

        for (size_t iHjemmepoeng = 0; iHjemmepoeng < hjemmepoengCount; ++iHjemmepoeng)
        {
            auto[spillerkey, spiller] = gen.nextStringUint();
            resultat.hjemmeScorerene.push_back(spiller);
        }
        auto[bortepoengCountKey, bortepoengCount] = gen.nextStringUint();

        gen.nextLine(); // ignore 'bortepoeng:'

        for (size_t iBortepoeng = 0; iBortepoeng < bortepoengCount; ++iBortepoeng)
        {
            auto[spillerkey, spiller] = gen.nextStringUint();
            resultat.borteScorerene.push_back(spiller);
        }

        resultatene.push_back(resultat);
    }
    return 0;
}


auto Decode::inputDivisjon(DB::Divisjon& divisjon, string_view strview) -> Decode::Error
{
    auto gen = Parser{strview};

    auto[divisjonkey, divisjonName] = gen.nextStringString();
    auto[lageneCountkey, lageneCount] = gen.nextStringUint();

    divisjon.navn = divisjonName;

    gen.nextLine(); // ignore lagene:

    for (size_t iLag = 0; iLag < lageneCount; ++iLag) 
    {
        auto[lagkey, lagNavn]     = gen.nextStringString();
        auto[adressekey, adresse] = gen.nextStringString();
        auto[spillereneCountkey, spillereneCount] = gen.nextStringUint();
        
        auto lag = DB::Lag {
            lagNavn,
            adresse
        };

        gen.nextLine(); // ignore spillerene:
            
        for (size_t iSpiller = 0; iSpiller < spillereneCount; ++iSpiller)
        {
            auto[spillerkey, spiller] = gen.nextStringUint();
            lag.spillerene.push_back(spiller);
        }
        divisjon.lagene.push_back(lag);
    }   
    
    gen.nextLine(); // ignore terminliste:

    for (size_t iHjemmelag = 0; iHjemmelag < lageneCount; ++iHjemmelag)
    {
        auto[hjemmelagkey, hjemmelag] = gen.nextStringString();

        gen.nextLine(); // ignore bortelagene:

        for (size_t iBortelag = 0; iBortelag < lageneCount-1; ++iBortelag)
        {
            auto[bortelagkey, bortelag] = gen.nextStringString();
            auto[datokey, dato] = gen.nextStringString();

            auto resultat = DB::Resultat{
                dato
            };
            divisjon.terminliste[hjemmelag][bortelag] = resultat;
        }
    }
    return 0;
}




void Printer::lineEmpty()
{
    outString += "\n";
}

void Printer::lineIndent() 
{
    for (size_t i = 0; i < indent; ++i) {
        outString += "  ";
    }  
}

void Printer::lineString(const string key)
{
    lineIndent();
    outString += key;
    outString += ":\n";
}

void Printer::lineStringString(const string key, const string value)
{
    lineIndent();
    outString += key;
    outString += ": ";
    outString += value;
    outString += "\n";
}

void Printer::lineStringUint(const string key, const size_t value)
{
    stringstream ss;
    ss << value;
    lineStringString(key, ss.str());
}

void Printer::lineStringBool(const string key, const bool value)
{
    string valueBool = (value? "true":"false");
    lineStringString(key, valueBool);
}

void Printer::lineDashString(const string key)
{
    lineIndent();
    outString += "- ";
    outString += key;
    outString += ":\n";
}

void Printer::lineDashStringString(const string key, const string value)
{
    lineIndent();
    outString += "- ";
    outString += key;
    outString += ": ";
    outString += value;
    outString += "\n";
}

void Printer::lineDashStringUint(const string key, const size_t value) 
{
    stringstream ss;
    ss << value;
    lineDashStringString(key, ss.str());
}


void Printer::tabRight() 
{
    indent += 1;
}

void Printer::tabLeft() 
{
    if (indent > 0) indent -= 1;
}


auto Printer::getString() -> string {
    return outString;
}


auto Encode::viewIdretteneCompact(DB::Idrettene& idrettene, bool divisjon, bool lag, bool spiller) -> string 
{
    Printer print;
    auto idretteneCount = idrettene.data->noOfElements();
            
            print.lineString(    "idrettene");

    for (auto iIdrett = 1; iIdrett <= idretteneCount; ++iIdrett)
    {
        auto idrett = (DB::Idrett*)(idrettene.data->removeNo(iIdrett));
    
            print.lineDashString(idrett->name);

        if (divisjon && idrett->divisjonene.size()) 
        { // bool divisjon
            print.tabRight();

            print.lineString(    "divisjonene");

            for (const auto& divisjon: idrett->divisjonene) 
            {

            print.lineDashString(divisjon.navn);

                if (lag && divisjon.lagene.size()) 
                { // bool divisjon
                    print.tabRight();
            print.lineString(    "lagene");

                    for(const auto& lag: divisjon.lagene) 
                    {

            print.lineDashString(lag.navn);

                        if (spiller && lag.spillerene.size()) 
                        { // bool spiller
            print.lineString(    "spillerene");

                            print.tabRight();
                            for (const auto& spiller: lag.spillerene) 
                            {
        
            print.lineDashString(std::to_string(spiller));

                            }
                            print.tabLeft();
                        }
                    }
                    print.tabLeft();
                }    
            }
            print.tabLeft();
        }

        idrettene.data->add(idrett);
    }
    return print.getString();
}


auto Encode::dataIdrettene(DB::Idrettene& idrettene) -> string 
{
 //  // IO::printline("\n\n------ DEBUG encodeIdrettene ------\n\n");

    Printer print;
    auto idretteneCount = idrettene.data->noOfElements();

    print.lineStringUint("idretteneCount", idretteneCount);
    print.lineString(    "idrettene");

    for (auto iIdrett = 1; iIdrett <= idretteneCount; ++iIdrett) 
    {
        auto idrett = (DB::Idrett*)(idrettene.data->removeNo(iIdrett));

        print.lineEmpty();
        print.lineDashStringString("idrett", idrett->name);
       
        print.tabRight();
      
        print.lineStringUint(      "tabelltype", idrett->tabell);
        print.lineStringUint(      "divisjoneneCount", idrett->divisjonene.size());
        print.lineString(         "divisjonene");

        for (const auto& divisjon: idrett->divisjonene) 
        {
            print.lineEmpty();
            print.lineDashStringString("divisjon", divisjon.navn);
           
            print.tabRight();
            
            print.lineStringUint(      "lageneCount", divisjon.lagene.size());
            print.lineString(          "lagene");

            for (const auto& lag: divisjon.lagene) 
            {
                print.lineEmpty();
                print.lineDashStringString("lag", lag.navn);
              
                print.tabRight();
              
                print.lineStringString(    "adresse", lag.adresse);
                print.lineStringUint(      "spillereneCount", lag.spillerene.size());
                print.lineString(          "spillerene");
                
                for (const auto spiller: lag.spillerene) {
                    print.lineDashStringUint("spiller", spiller);
                }

                print.tabLeft();
            }

            print.lineEmpty();
           
            print.lineString("terminliste");

            for (const auto& [hjemmelag, bortelagene]: divisjon.terminliste) 
            {
                print.lineEmpty();
                print.lineDashStringString("hjemmelag", hjemmelag);
              
                print.tabRight();
              
                print.lineString(      "bortelagene");

                for (const auto& [bortelag, resultat]: bortelagene) 
                {
                    print.lineEmpty();
                    print.lineDashStringString("bortelag", bortelag);
                
                    print.tabRight();
                
                    print.lineStringString("dato", resultat.dato);
                    
                    if (!resultat.spilt) 
                    {
                        print.lineStringBool("resultat", false);
                    }
                    else 
                    {
                        print.lineString("resultat");
                       
                        print.tabRight();

                        print.lineStringBool("overtid", resultat.overtid);

                        print.lineStringUint("hjemmeScorereneCount", resultat.hjemmeScorerene.size());
                        print.lineString("hjemmeScorerene");
                        for (const auto& spiller: resultat.hjemmeScorerene) 
                        {
                            print.lineDashStringUint("spiller", spiller);
                        }
                        
                        print.lineStringUint("borteScorereneCount", resultat.borteScorerene.size());
                        print.lineString("borteScorerene");
                        for (const auto& spiller: resultat.borteScorerene) 
                        {
                            print.lineDashStringUint("spiller", spiller);
                        }
                        print.tabLeft();
                    }
                    print.tabLeft();
                }
                print.tabLeft();    
            }
            print.tabLeft();
        }
        print.tabLeft();        
        idrettene.data->add(idrett);
    }
 //  // IO::printline("\n\n------ DEBUG encodeIdrettene ------\n\n");

    return print.getString();
}


auto Encode::dataSpillerene(DB::Spillerene& spillerene) -> string 
{

    Printer print;
    size_t spillereneCount = spillerene.data->noOfElements();

    print.lineStringUint("autoIncrementer", spillerene.autoIncrementer);
    print.lineStringUint("spillereneCount", spillereneCount);
    print.lineString("spillerene");

    for (size_t iSpiller = 1; iSpiller <= spillereneCount; ++iSpiller)
    {
        auto spiller = (DB::Spiller* )(spillerene.data->removeNo(iSpiller));

        print.lineEmpty();
        print.lineDashStringString("spiller", spiller->name);

        print.tabRight();

        print.lineStringUint(      "guid", spiller->guid);
        print.lineStringString(    "adresse", spiller->address);

        spillerene.data->add(spiller);

        print.tabLeft();
    }

    return print.getString();
}


auto Encode::viewResultatene(const vector<DB::ViewResultat>& resultatene) -> string
{
    Printer p;

    p.lineStringUint("resultateneCount", resultatene.size());
    p.lineString("resultatene");

    for (const auto& resultat: resultatene) 
    {
        p.lineEmpty();
        p.lineDashString("resultat");
        
        p.tabRight();

        p.lineStringString("hjemmelag", resultat.hjemmelag);
        p.lineStringString("bortelag", resultat.bortelag);
        p.lineStringString("dato", resultat.dato);

        p.lineStringUint("hjemmescoringer", resultat.hjemmescoringer);

        p.lineStringUint("bortescoringer", resultat.bortescoringer);

        p.tabLeft();
    }

    return p.getString();
}


void Encode::viewTabellLagene(Printer& p, const vector<DB::Tabell::Lag>& lagene) 
{
    p.lineStringUint("tabellLageneCount", lagene.size());
    p.lineString("tabellLagene");

    for (const auto& lag: lagene) 
    {
        p.lineEmpty();
        p.lineDashStringString("lag", lag.navn);
       
        p.tabRight();
    
        p.lineStringUint("plassering", lag.plassering);
        p.lineStringUint("poeng", lag.poeng);
        p.lineStringUint("hjemmeScoringer", lag.hjemmeScoringer);
        p.lineStringUint("hjemmeBaklengs", lag.hjemmeBaklengs);
        p.lineStringUint("borteScoringer", lag.borteScoringer);
        p.lineStringUint("borteBaklengs", lag.borteBaklengs);
        p.lineStringUint("seier", lag.seier);
        p.lineStringUint("uavgjort", lag.uavgjort);
        p.lineStringUint("tap", lag.tap);
      
        p.tabLeft();
    }
}


auto Encode::viewTabellDivisjon(const DB::Tabell& tabell) -> string 
{
    Printer p;

    p.lineStringString("tabell", tabell.divisjon);

    Encode::viewTabellLagene(p, tabell.lagene);

    return p.getString();
}


auto Encode::viewTabelleneIdrett(const vector<DB::Tabell>& tabellene,
                                 const string idrett) -> string 
{
    Printer p;

    p.lineStringString("idrett", idrett);

    p.lineStringUint("tabelleneCount", tabellene.size());
    p.lineString(    "tabellene");

    for (const auto& tabell: tabellene) 
    {
        p.lineEmpty();
        p.lineDashStringString("tabell", tabell.divisjon);
        
        p.tabRight();
      
        Encode::viewTabellLagene(p, tabell.lagene);
       
        p.tabLeft();
    }

    return p.getString();
}


auto Encode::viewTerminliste(const DB::Terminliste& terminliste) -> string 
{

    Printer p;

    p.lineStringString("divisjon", terminliste.divisjon);
    p.lineStringUint("lageneCount", terminliste.data.size());
    p.lineString("terminliste");

    for (const auto [hjemmelag, bortelagene]: terminliste.data)
    {
        p.lineEmpty();
        p.lineDashStringString("hjemmelag", hjemmelag);
        
        p.tabRight();
        p.lineString("bortelagene");
        p.lineEmpty();


        for (const auto [bortelag, resultat]: bortelagene)
        {
            p.lineDashStringString("bortelag", bortelag);
            
            p.tabRight();

            p.lineStringString("dato", resultat.dato);

            p.tabLeft();
        }
        p.tabLeft();    
    } 
    return p.getString();
}


void Encode::viewToppscorerene(Printer& p, const vector<DB::Toppscorer>& toppscorerene) 
{
    p.lineStringUint("toppscorereneCount", toppscorerene.size());
    p.lineString("toppscorerene");

    for (const auto& spiller: toppscorerene)
    {
        p.lineEmpty();
        p.lineDashStringString("spiller", spiller.name);
        
        p.tabRight();
        
        p.lineStringUint("score", spiller.score);

        p.tabLeft();
    }
}


auto Encode::viewToppscorereneDivisjon(const vector<DB::Toppscorer>& toppscorerene,
                                       const string divisjon) -> string 
{
    Printer p;
    p.lineStringString("divisjon", divisjon);
    Encode::viewToppscorerene(p, toppscorerene);
    return p.getString();
}


auto Encode::viewToppscorereneLag(const vector<DB::Toppscorer>& toppscorerene,
                            const string lag) -> string 
{
    Printer p;
    p.lineStringString("lag", lag);
    Encode::viewToppscorerene(p, toppscorerene);
    return p.getString();
}


auto Encode::viewTabelltype(DB::Idrett::TabellType tabellType) -> string 
{
    switch(tabellType) 
    {
    case DB::Idrett::SEIER_2_UAVGJORT_1_TAP_0:
        return "Seier 2, Uavgjort 1, Tap 0";
    case DB::Idrett::SEIER_3_UAVGJORT_1_TAP_0:
        return "Seier 3, Uavgjort 1, Tap 0";
    case DB::Idrett::SEIER_3_OVERTID_2_UAVGJORT_1_TAP_0:
        return "Seier 3, Overtid 2, Uavgjort 1, Tap 0";
    default:
        std::cout << "\n\n\n!!!!tabellType: " << tabellType << "\n\n\n";
        assert(false && "Unknown tabelltype!!!");
    }
    return "";
};

auto Encode::viewIdrett(const DB::Idrett& idrett) -> string 
{
    Printer p;

    p.lineStringString("idrett", idrett.name);
    
    p.tabRight();

    p.lineStringString("tabelltype", Encode::viewTabelltype(idrett.tabell));
    p.lineStringUint(  "divisjoneneCount", idrett.divisjonene.size());
    p.lineString("divisjonene");

    for (const auto& divisjon : idrett.divisjonene) 
    {
        p.lineEmpty();
        p.lineDashStringString("divisjon", divisjon.navn);
        
        p.tabRight();

        p.lineStringUint("lageneCount", divisjon.lagene.size());
        p.lineString("lagene");

        for (const auto& lag : divisjon.lagene) 
        {
            p.lineEmpty();
            p.lineDashStringString("lag", lag.navn);

            p.tabRight();

            p.lineStringString("adresse", lag.adresse);
            p.lineStringUint(  "spillereneCount", lag.spillerene.size());

            p.tabLeft();
        }
        p.tabLeft();
    }
    return p.getString();
}


auto Encode::viewIdrettene(DB::Idrettene& idrettene) -> string 
{

    Printer p;

    p.lineStringUint("idretteneCount", idrettene.data->noOfElements());
    p.lineString(    "idrettene");

    for (size_t i = 1; i <= idrettene.data->noOfElements(); ++i) 
    {
        auto idrett = (DB::Idrett* ) idrettene.data->removeNo(i);

        p.lineEmpty();
        p.lineDashStringString("idrett", idrett->name);

        p.tabRight();

        p.lineStringString("tabelltype", Encode::viewTabelltype(idrett->tabell));
        p.lineStringUint(  "divisjoneneCount", idrett->divisjonene.size());

        p.tabLeft();
        idrettene.data->add(idrett);
    }
    return p.getString();
}


auto Encode::viewSpillerene(DB::Spillerene& spillerene) -> string 
{
    Printer p;

    p.lineStringUint("spillereneCount", spillerene.data->noOfElements());
    p.lineString(    "spillerene");

    for (size_t i = 1; i <= spillerene.data->noOfElements(); ++i) 
    {
        auto spiller = (DB::Spiller* ) spillerene.data->removeNo(i); //TODO - remove elements in order to print out in order

        p.lineEmpty();
        p.lineDashStringString("spiller", spiller->name);
        
        p.tabRight();

        p.lineStringUint("nummer", spiller->guid);
        p.lineStringString("adresse", spiller->address);
        p.tabLeft();

        spillerene.data->add(spiller);
    }

    return p.getString();
}


} // ::gruppe32
