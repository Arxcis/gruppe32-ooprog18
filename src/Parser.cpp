#include <gruppe32/Parser.hpp>

#include <string>
#include <iomanip>
#include <utility>
#include <map>
#include <sstream>

namespace gruppe32::Decode 
{

auto KeyValueGenerator::nextLine() -> std::string
{
    auto endofline = strview.find('\n', startofline);
    auto diff = endofline-startofline;

    // 1. skip empty lines
    while (diff == 0) {
        startofline = endofline+1;
        endofline = strview.find('\n', startofline);
        diff = endofline-startofline;
    }

    auto line = std::string { 
        strview.substr(startofline, endofline-startofline)
    };

    // 2. Trim whitespace
    while(line.front() == ' ') line.erase(0,1);
    if(line.front() == '-') line.erase(0,2);

    /* @debug 
    std::cout << std::setw(40) << std::left << line
              << " | start: "  << startofline
              << " | end: "    << endofline
              << " | DIFF: "   << endofline-startofline << '\n';
    */
    startofline = endofline+1;
    return line;
};

auto KeyValueGenerator::nextStringStringPair() -> pair<string,string>
{
    auto line = nextLine();

    string key = line.substr(0, line.find(":"));
    string valueString = "";

    if (line.find(":")+2 < line.size())
        valueString = line.substr(line.find(":")+2);

    /* @debug
    std::cout << std::setw(35) << std::left 
              << line  

              << " key: " 
              << std::setw(18) << std::left 
              << key
              
              << " val: " 
              << valueString
              << '\n';
    */

    return pair<string,string>{ key, valueString };
};


auto KeyValueGenerator::nextStringUintPair() -> pair<string, size_t>
{
    auto[key, valueString] = nextStringStringPair();
    return pair<string, size_t>{key, std::stoi(valueString)};
};

auto KeyValueGenerator::nextStringBoolPair() -> pair<string,bool>
{
    auto[key, valueString] = nextStringStringPair();
    bool trueFalse;
    if (valueString == "true") {
        trueFalse = true;
    }
    else if (valueString == "false") {
        trueFalse = false;
    }
    // @note special case with resultat: in format-idrettene.yml meaning true
    else if (valueString == "") {  
        trueFalse = true;
    }
    else {
        assert(false && "Boolean not supported");
    }
    return pair<string,bool>{key, trueFalse};
};


auto idrettene(DB::Idrettene& idrettene, string_view strview) -> Decode::Error 
{
    //IO::printline("\n\n------ DEBUG decodeIdrettene ------\n\n");

    auto gen = KeyValueGenerator{strview, 0};

    auto[idretteneCountkey, idretteneCount] = gen.nextStringUintPair();
    //IO::printline("idretteneCount:", idretteneCount);

    gen.nextLine(); // ignore idrettene:

    for (size_t iIdrett = 0; iIdrett < idretteneCount; ++iIdrett)
    {

        auto[idrettKey, idrettNavn] = gen.nextStringStringPair();
        //IO::printline(idrettKey, ":", idrettNavn);

        auto[tabelltypekey, tabelltype] = gen.nextStringUintPair();
        //IO::printline(tabelltypekey, ":", tabelltype);
        
        auto[divisjoneneCountkey, divisjoneneCount] = gen.nextStringUintPair();
        //IO::printline(divisjoneneCountkey, ":", divisjoneneCount);

        // Create Idrett
        auto idrett = new DB::Idrett {
            idrettNavn,
            DB::Idrett::TabellType(tabelltype)
        };

        gen.nextLine(); // ignore divisjonene:

        for (size_t iDivisjon = 0; iDivisjon < divisjoneneCount; ++iDivisjon)
        {
            auto[divisjonkey, divisjonNavn] = gen.nextStringStringPair();
            //IO::printline(divisjonkey, ":", divisjonNavn);

            auto[lageneCountkey, lageneCount] = gen.nextStringUintPair();
            //IO::printline(lageneCountkey, ":", lageneCount);

            // Create Divisjon
            auto divisjon = DB::Divisjon {
                divisjonNavn
            };

            gen.nextLine(); // ignore lagene:

            for (size_t iLag = 0; iLag < lageneCount; ++iLag)
            {
                auto[lagkey, lagName] = gen.nextStringStringPair();
                //IO::printline(lagkey, ":", lagName); 

                auto[adressekey, adresse] = gen.nextStringStringPair();
                //IO::printline(adressekey, ":", adresse); 
            
                auto[spillereneCountkey, spillereneCount] = gen.nextStringUintPair();
                //IO::printline(spillereneCountkey, ":", spillereneCount); 
                
                auto lag = DB::Lag {
                    lagName,
                    adresse
                };

                gen.nextLine(); // ignore spillerene:
                
                for (size_t iSpiller = 0; iSpiller < spillereneCount; ++iSpiller)
                {

                    auto[spillerkey, spiller] = gen.nextStringUintPair();
                    //IO::printline(spillerkey, ":", spiller);

                    lag.spillerene.push_back(spiller);         
                }
                divisjon.lagene.push_back(lag);
            }   

            
            gen.nextLine(); // ignore terminliste:
            gen.nextLine(); // ignore hjemmelagene:

            for (size_t iHjemmelag = 0; iHjemmelag < lageneCount; ++iHjemmelag)
            {

                auto[hjemmelagkey, hjemmelag] = gen.nextStringStringPair();
                //IO::printline(hjemmelagkey, ":", hjemmelag);  


                gen.nextLine(); // ignore bortelagene:

                for (size_t iBortelag = 0; iBortelag < lageneCount-1; ++iBortelag)
                {
                    auto[bortelagkey, bortelag] = gen.nextStringStringPair();
                    //IO::printline(bortelagkey, ":", bortelag);  
                    
                    auto[datokey, dato] = gen.nextStringStringPair();
                    //IO::printline(datokey, ":", dato);  

                    auto[resultkey, isResult] = gen.nextStringBoolPair();
                    //IO::printline(resultkey, ":", isResult);  

                    // Create Resultat
                    auto resultat = DB::Resultat {
                        dato
                    };

                    if (isResult) 
                    {
                        auto[overtidkey, overtid] = gen.nextStringBoolPair();
                        //IO::printline(overtidkey, ":", overtid);  
                    
                        auto[hjemmepoengCountkey, hjemmepoengCount] = gen.nextStringUintPair();
                        //IO::printline(hjemmepoengCountkey, ":", hjemmepoengCount);

                        resultat.spilt = true;
                        resultat.overtid = overtid;

                        gen.nextLine(); // ignore hjemmepoeng:

                        for (size_t iHjemmepoeng = 0; iHjemmepoeng < hjemmepoengCount; ++iHjemmepoeng)
                        {
                            auto[spillerkey, spiller] = gen.nextStringUintPair();
                            //IO::printline(spillerkey, ":", spiller);

                            resultat.hjemmeScorerene.push_back(spiller);
                        }
                        
                        auto[bortepoengCountKey, bortepoengCount] = gen.nextStringUintPair();
                        //IO::printline(bortepoengCountKey, ":", bortepoengCount);

                        gen.nextLine(); // ignore 'bortepoeng:'

                        for (size_t iBortepoeng = 0; iBortepoeng < bortepoengCount; ++iBortepoeng)
                        {
                            auto[spillerkey, spiller] = gen.nextStringUintPair();
                            //IO::printline(spillerkey, ":", spiller);  
                            resultat.borteScorerene.push_back(spiller);
                        }
                    }
                    divisjon.terminListe[hjemmelag][bortelag] = resultat;
                }
            }
            idrett->divisjonene.push_back(divisjon);
        }
        // Pushing idrett into ListTool
        idrettene.data->add(idrett);
    }
    //IO::printline("\n\n------ DEBUG decodeIdrettene ------\n\n");
    return 0;
}


auto spillerene(DB::Spillerene& spillerene, string_view strview) -> Decode::Error
{
    //IO::printline("\n\n------ DEBUG decodeSpillerene ------\n\n");
 
    auto gen = KeyValueGenerator{strview};


    auto[autoIncrementerKey, autoIncrementer] = gen.nextStringUintPair();
    //IO::printline(sisteguidKey, ":", sisteguid);  

    auto[spillereneCountKey, spillereneCount] = gen.nextStringUintPair();
    //IO::printline(spillereneCountKey, ":", spillereneCount);

    spillerene.autoIncrementer = autoIncrementer;

    gen.nextLine(); // ignore 'spillerene:'

    for (size_t iSpiller = 0; iSpiller < spillereneCount; ++iSpiller)
    {
        auto[spillerNameKey, spillerName] = gen.nextStringStringPair();
        //IO::printline(spillerNameKey, ":", spillerName);

        auto[guidKey, guid] = gen.nextStringUintPair();
        //IO::printline(guidKey, ":", guid);

        auto[adresseKey, adresse] = gen.nextStringStringPair();
        //IO::printline(adresseKey, ":", adresse);
    
        auto spiller = new DB::Spiller {
            guid,
            spillerName,
            adresse
        };
        spillerene.data->add(spiller);
    }
    //IO::printline("\n\n------ DEBUG decodeSpillerene ------\n\n");
    return 0;    
}


auto resultatene(vector<DB::ResultatWithKeys>& resultatene, string_view strview) -> Decode::Error
{

   // IO::printline("\n\n------ DEBUG decodeResultatene ------\n\n");
 
    auto gen = KeyValueGenerator{strview};

    auto[resultateneCountKey, resultateneCount] = gen.nextStringUintPair();
   // IO::printline(resultateneCountKey, ":", resultateneCount);

    gen.nextLine(); // ignore 'resultatene:''

    for (size_t iResultat = 0; iResultat < resultateneCount; ++iResultat)
    {

        gen.nextLine(); // ignore '- resultat:'

        auto[idrettKey, idrett] = gen.nextStringStringPair();
       // IO::printline(idrettKey, ":", idrett);   

        auto[divisjonKey, divisjon] = gen.nextStringStringPair();
       // IO::printline(divisjonKey, ":", divisjon);   

        auto[hjemmelagKey, hjemmelag] = gen.nextStringStringPair();
       // IO::printline(hjemmelagKey, ":", hjemmelag);   

        auto[bortelagKey, bortelag] = gen.nextStringStringPair();
       // IO::printline(bortelagKey, ":", bortelag);   

        auto[datoKey, dato] = gen.nextStringStringPair();
       // IO::printline(datoKey, ":", dato);   

        auto[overtidKey, overtid] = gen.nextStringBoolPair();
       // IO::printline(overtidKey, ":", overtid);   

        auto[hjemmepoengCountKey, hjemmepoengCount] = gen.nextStringUintPair();
       // IO::printline(hjemmepoengCountKey, ":", hjemmepoengCount);   

        auto resultat = DB::ResultatWithKeys{
            idrett,
            divisjon,
            hjemmelag,
            bortelag,
            dato,
            true,
            overtid
        };

        gen.nextLine(); // ignore 'hjemmepoeng:'

        for (size_t iHjemmepoeng = 0; iHjemmepoeng < hjemmepoengCount; ++iHjemmepoeng)
        {
            auto[spillerkey, spiller] = gen.nextStringUintPair();
           // IO::printline(spillerkey, ":", spiller);
            resultat.hjemmeScorerene.push_back(spiller);
        }
        
        auto[bortepoengCountKey, bortepoengCount] = gen.nextStringUintPair();
       // IO::printline(bortepoengCountKey, ":", bortepoengCount);

        gen.nextLine(); // ignore 'bortepoeng:'

        for (size_t iBortepoeng = 0; iBortepoeng < bortepoengCount; ++iBortepoeng)
        {
            auto[spillerkey, spiller] = gen.nextStringUintPair();
           // IO::printline(spillerkey, ":", spiller);
            resultat.borteScorerene.push_back(spiller);
        }

        resultatene.push_back(resultat);
    }
   // IO::printline("\n\n------ DEBUG decodeResultatene ------\n\n");
    return 0;
}


auto divisjon(DB::Divisjon& divisjon, string_view strview) -> Decode::Error
{

    //IO::printline("\n\n------ DEBUG decodeDivisjon ------\n\n");


    auto gen = KeyValueGenerator{strview};

    auto[divisjonkey, divisjonName] = gen.nextStringStringPair();
    //IO::printline(divisjonkey, ":", divisjonName);

    auto[lageneCountkey, lageneCount] = gen.nextStringUintPair();
    //IO::printline(lageneCountkey, ":", lageneCount);

    divisjon.navn = divisjonName;

    gen.nextLine(); // ignore lagene:

    for (size_t iLag = 0; iLag < lageneCount; ++iLag) 
    {
        auto[lagkey, lagNavn] = gen.nextStringStringPair();
        //IO::printline(lagkey, ":", lagNavn); 

        auto[adressekey, adresse] = gen.nextStringStringPair();
        //IO::printline(adressekey, ":", adresse); 
    
        auto[spillereneCountkey, spillereneCount] = gen.nextStringUintPair();
        //IO::printline(spillereneCountkey, ":", spillereneCount); 
        
        auto lag = DB::Lag {
            lagNavn,
            adresse
        };

        gen.nextLine(); // ignore spillerene:
            
        for (size_t iSpiller = 0; iSpiller < spillereneCount; ++iSpiller)
        {
            auto[spillerkey, spiller] = gen.nextStringUintPair();
            //IO::printline(spillerkey, ":", spiller);         
            lag.spillerene.push_back(spiller);
        }
        divisjon.lagene.push_back(lag);
    }   
    
    gen.nextLine(); // ignore terminliste:
    gen.nextLine(); // ignore hjemmelagene:

    for (size_t iHjemmelag = 0; iHjemmelag < lageneCount; ++iHjemmelag)
    {
        auto[hjemmelagkey, hjemmelag] = gen.nextStringStringPair();
        //IO::printline(hjemmelagkey, ":", hjemmelag);  

        gen.nextLine(); // ignore bortelagene:

        for (size_t iBortelag = 0; iBortelag < lageneCount-1; ++iBortelag)
        {
            auto[bortelagkey, bortelag] = gen.nextStringStringPair();
            //IO::printline(bortelagkey, ":", bortelag);  
            
            auto[datokey, dato] = gen.nextStringStringPair();
            //IO::printline(datokey, ":", dato);  

            auto resultat = DB::Resultat{
                dato
            };
            divisjon.terminListe[hjemmelag][bortelag] = resultat;
        }
    }
    //IO::printline("\n\n------ DEBUG decodeDivisjon ------\n\n");
    return 0;
}

} // end namespace Decode







namespace gruppe32::Encode
{

void LinePrinter::lineEmpty()
{
    outString += "\n";
}

void LinePrinter::lineIndent() 
{
    for (size_t i = 0; i < indent; ++i) {
        outString += "  ";
    }  
}

void LinePrinter::lineString(const string key)
{
    lineIndent();
    outString += key;
    outString += ":\n";
}

void LinePrinter::lineStringString(const string key, const string value)
{
    lineIndent();
    outString += key;
    outString += ": ";
    outString += value;
    outString += "\n";
}

void LinePrinter::lineStringUint(const string key, const size_t value)
{
    stringstream ss;
    ss << value;
    lineStringString(key, ss.str());
}

void LinePrinter::lineStringBool(const string key, const bool value)
{
    string valueBool = (value? "true":"false");
    lineStringString(key, valueBool);
}

void LinePrinter::lineDashString(const string key)
{
    lineIndent();
    outString += "- ";
    outString += key;
    outString += ":\n";
}

void LinePrinter::lineDashStringString(const string key, const string value)
{
    lineIndent();
    outString += "- ";
    outString += key;
    outString += ": ";
    outString += value;
    outString += "\n";
}

void LinePrinter::lineDashStringUint(const string key, const size_t value) 
{
    stringstream ss;
    ss << value;
    lineDashStringString(key, ss.str());
}


void LinePrinter::tabRight() 
{
    indent += 1;
}

void LinePrinter::tabLeft() 
{
    if (indent > 0) indent -= 1;
}


auto LinePrinter::getString() -> string {
    return outString;
}

auto idrettene(DB::Idrettene& idrettene) -> string 
{
 //  // IO::printline("\n\n------ DEBUG encodeIdrettene ------\n\n");

    LinePrinter print;
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
           
            print.tabRight();
           
            print.lineString("hjemmelagene");

            for (const auto& [hjemmelag, bortelagene]: divisjon.terminListe) 
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
            print.tabLeft();
        }
        print.tabLeft();        
        idrettene.data->add(idrett);
    }
 //  // IO::printline("\n\n------ DEBUG encodeIdrettene ------\n\n");

    return print.getString();
}


auto spillerene(DB::Spillerene& spillerene) -> string 
{

    LinePrinter print;
    size_t spillereneCount = spillerene.data->noOfElements();

    print.lineStringUint("autoIncrementer", spillerene.autoIncrementer);
    print.lineEmpty();
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


void resultatene(LinePrinter& p, const vector<DB::ResultatWithKeys>& resultatene) 
{
    p.lineEmpty();
    p.lineStringUint("resultateneCount", resultatene.size());
    p.lineString("resultatene");
    p.lineEmpty();


    for (const auto& resultat: resultatene) 
    {
        p.lineDashString("resultat");
        
        p.tabRight();

        p.lineStringString("hjemmelag", resultat.hjemmelag);
        p.lineStringString("bortelag", resultat.bortelag);
        p.lineStringString("dato", resultat.dato);
        p.lineStringBool("overtid", resultat.overtid);

        p.lineStringUint("hjemmeScorereneCount", resultat.hjemmeScorerene.size());
        p.lineString("hjemmeScorerene");

        for (const auto& spiller: resultat.hjemmeScorerene)
        { 
            p.lineDashStringUint("spiller", spiller);
        }

        p.lineStringUint("borteScorereneCount", resultat.borteScorerene.size()); 
        p.lineString("borteScorerene");

        for (const auto& spiller: resultat.borteScorerene)
        { 
            p.lineDashStringUint("spiller", spiller);
        }

        p.tabLeft();
    }
}


auto resultateneDivisjon(const vector<DB::ResultatWithKeys>& resultatene,
                               const string divisjon) -> string 
{
    LinePrinter p;

    p.lineStringString("divisjon", divisjon);

    Encode::resultatene(p, resultatene);

    return p.getString();
}


auto resultateneIdrett(const vector<DB::ResultatWithKeys>& resultatene,
                             const string idrett) -> string 
{
    LinePrinter p;
    p.lineStringString("idrett", idrett);

    Encode::resultatene(p, resultatene);
    return p.getString();
}



void tabellLagene(LinePrinter& p, const vector<DB::Tabell::Lag>& lagene) 
{
    p.lineEmpty();
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


auto tabellDivisjon(const DB::Tabell& tabell) -> string 
{
    LinePrinter p;

    p.lineStringString("tabell", tabell.divisjon);
    p.lineStringUint("tabelltype", tabell.tabellType);

    Encode::tabellLagene(p, tabell.lagene);

    return p.getString();
}


auto tabelleneIdrett(const vector<DB::Tabell>& tabellene,
                     const string idrett,
                     const DB::Idrett::TabellType tabelltype) -> string 
{
    LinePrinter p;

    p.lineStringString("idrett", idrett);
    p.lineStringUint("tabelltype", tabelltype);

    p.lineEmpty();
    p.lineStringUint("tabelleneCount", tabellene.size());
    p.lineString(    "tabellene");

    for (const auto& tabell: tabellene) 
    {
        p.lineEmpty();
        p.lineDashStringString("tabell", tabell.divisjon);
        
        p.tabRight();
      
        Encode::tabellLagene(p, tabell.lagene);
       
        p.tabLeft();
    }

    return p.getString();
}


auto terminliste(const DB::Terminliste& terminliste) -> string 
{

    LinePrinter p;

    p.lineStringString("divisjon", terminliste.divisjon);
    p.lineEmpty();
    p.lineString("terminliste");

    p.tabRight();

    p.lineStringUint("lageneCount", terminliste.data.size());
    p.lineString("hjemmelagene");
   
    for (const auto [hjemmelag, bortelagene]: terminliste.data)
    {
        p.lineEmpty();
        p.lineDashStringString("hjemmelag", hjemmelag);
        
        p.tabRight();
        p.lineString("bortelagene");
        p.lineEmpty();


        for (const auto [bortelag, dato]: bortelagene)
        {
            p.lineDashStringString("bortelag", bortelag);
            
            p.tabRight();

            p.lineStringString("dato", dato);

            p.tabLeft();
        }
        p.tabLeft();    
    } 
    return p.getString();
}


auto toppscorerene(LinePrinter& p, const vector<DB::Toppscorer>& toppscorerene) 
{
    p.lineEmpty();

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


auto toppscorereneDivisjon(const vector<DB::Toppscorer>& toppscorerene,
                                 const string divisjon) -> string 
{
    LinePrinter p;
    p.lineStringString("divisjon", divisjon);
    Encode::toppscorerene(p, toppscorerene);
    return p.getString();
}


auto toppscorereneLag(const vector<DB::Toppscorer>& toppscorerene,
                            const string lag) -> string 
{
    LinePrinter p;
    p.lineStringString("lag", lag);
    Encode::toppscorerene(p, toppscorerene);
    return p.getString();
}

} // end namespace Encode
