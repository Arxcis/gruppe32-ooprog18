#include <gruppe32/Parser.hpp>

#include <string>
#include <iomanip>
#include <utility>
#include <map>
#include <sstream>

namespace gruppe32::Parser 
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


void LinePrinter::lineEmpty()
{
    outString += "\n";
}

void LinePrinter::lineString(const string key, const size_t indentCount)
{
    for (size_t iIndent = 0; iIndent < indentCount; ++iIndent) {
        outString += "  ";
    }
    outString += key;
    outString += ":\n";
}

void LinePrinter::lineStringString(const string key, const string value, const size_t indentCount)
{
    for (size_t iIndent = 0; iIndent < indentCount; ++iIndent) {
        outString += "  ";
    }
    outString += key;
    outString += ": ";
    outString += value;
    outString += "\n";
}

void LinePrinter::lineStringUint(const string key, const size_t value, const size_t indentCount)
{
    stringstream ss;
    ss << value;
    lineStringString(key, ss.str(), indentCount);
}

void LinePrinter::lineStringBool(const string key, const bool value, const size_t indentCount)
{
    string valueBool = (value? "true":"false");
    lineStringString(key, valueBool, indentCount);
}

void LinePrinter::lineDashStringString(const string key, const string value, const size_t indentCount)
{
    for (size_t iIndent = 0; iIndent < indentCount; ++iIndent) {
        outString += "  ";
    }

    outString += "- ";
    outString += key;
    outString += ": ";
    outString += value;
    outString += "\n";
}

void LinePrinter::lineDashStringUint(const string key, const size_t value, const size_t indentCount) 
{
    stringstream ss;
    ss << value;
    lineDashStringString(key, ss.str(), indentCount);
}

auto LinePrinter::getString() -> string {
    return outString;
}

auto encodeIdrettene(DB::Idrettene& idrettene) -> string 
{
    IO::printline("\n\n------ DEBUG encodeIdrettene ------\n\n");

    LinePrinter print;
    auto idretteneCount = idrettene.data.noOfElements();

    print.lineStringUint("idretteneCount", idretteneCount, 0);
    print.lineString(    "idrettene", 0);

    for (auto iIdrett = 1; iIdrett <= idretteneCount; ++iIdrett) 
    {
        auto idrett = (DB::Idrett*)(idrettene.data.removeNo(iIdrett));

        print.lineEmpty();
        print.lineDashStringString("idrett", idrett->name, 0);
        print.lineStringUint(      "tabelltype", idrett->tabell, 1);
        print.lineStringUint(      "divisjoneneCount", idrett->divisjonene.size(), 1);
        print.lineString(         "divisjonene", 1);

        for (const auto& divisjon: idrett->divisjonene) 
        {
            print.lineEmpty();
            print.lineDashStringString("divisjon", divisjon.navn, 1);
            print.lineStringUint(      "lageneCount", divisjon.lagene.size(), 2);
            print.lineString(          "lagene", 2);

            for (const auto& lag: divisjon.lagene) 
            {
                print.lineEmpty();
                print.lineDashStringString("lag", lag.navn, 2);
                print.lineStringString(    "adresse", lag.adresse, 3);
                print.lineStringUint(      "spillereneCount", lag.spillerene.size(), 3);
                print.lineString(          "spillerene", 3);
                
                for (const auto spiller: lag.spillerene) {
                    print.lineDashStringUint("spiller", spiller, 3);
                }
            }

            print.lineEmpty();
            print.lineString("terminliste", 2);
            print.lineString("hjemmelagene", 3);

            for (const auto& [hjemmelag, bortelagene]: divisjon.terminListe) 
            {
                print.lineEmpty();
                print.lineDashStringString("hjemmelag", hjemmelag, 3);
                print.lineString(      "bortelagene", 4);

                for (const auto& [bortelag, resultat]: bortelagene) 
                {
                    print.lineEmpty();
                    print.lineDashStringString("bortelag", bortelag, 4);
                    print.lineStringString("dato", resultat.dato, 5);
                    
                    if (!resultat.spilt) 
                    {
                        print.lineStringBool("resultat", false, 5);
                    }
                    else 
                    {
                        print.lineString("resultat", 5);
                        print.lineStringBool("overtid", resultat.overtid, 6);

                        print.lineStringUint("hjemmeScorereneCount", resultat.hjemmeScorerene.size(), 6);
                        print.lineString("hjemmeScorerene", 6);
                        for (const auto& spiller: resultat.hjemmeScorerene) 
                        {
                            print.lineDashStringUint("spiller", spiller, 6);
                        }
                        
                        print.lineStringUint("borteScorereneCount", resultat.borteScorerene.size(), 6);
                        print.lineString("borteScorerene", 6);
                        for (const auto& spiller: resultat.borteScorerene) 
                        {
                            print.lineDashStringUint("spiller", spiller, 6);
                        }
                    }
                }
            }
        }
        idrettene.data.add(idrett);
    }
    IO::printline("\n\n------ DEBUG encodeIdrettene ------\n\n");

    return print.getString();
}


auto decodeIdrettene(DB::Idrettene& idrettene, string_view strview) -> Parser::Error 
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
            DB::Idrett::Tabell(tabelltype)
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
        idrettene.data.add(idrett);
    }
    //IO::printline("\n\n------ DEBUG decodeIdrettene ------\n\n");
	return 0;
}

auto encodeSpillerene(DB::Spillerene& spillerene) -> string 
{
    return "";
}
auto decodeSpillerene(DB::Spillerene& spillerene, string_view strview) -> Parser::Error
{
    //IO::printline("\n\n------ DEBUG decodeSpillerene ------\n\n");
 
    auto gen = KeyValueGenerator{strview};


    auto[sisteguidKey, sisteguid] = gen.nextStringUintPair();
    //IO::printline(sisteguidKey, ":", sisteguid);  

    auto[spillereneCountKey, spillereneCount] = gen.nextStringUintPair();
    //IO::printline(spillereneCountKey, ":", spillereneCount);

    gen.nextLine(); // ignore 'spillerene:'

    for (size_t iSpiller = 0; iSpiller < spillereneCount; ++iSpiller)
    {
        auto[spillereneCountKey, spillereneCount] = gen.nextStringStringPair();
        //IO::printline(spillereneCountKey, ":", spillereneCount);

        auto[guidKey, guid] = gen.nextStringUintPair();
        //IO::printline(guidKey, ":", guid);

        auto[addresseKey, addresse] = gen.nextStringStringPair();
        //IO::printline(addresseKey, ":", addresse);
    }
    //IO::printline("\n\n------ DEBUG decodeSpillerene ------\n\n");
    return 0;    
}


auto decodeResultatene(DB::Idrettene& idrettene, string_view strview) -> Parser::Error
{

    //IO::printline("\n\n------ DEBUG decodeResultatene ------\n\n");
 
    auto gen = KeyValueGenerator{strview};

    auto[resultateneCountKey, resultateneCount] = gen.nextStringUintPair();
    //IO::printline(resultateneCountKey, ":", resultateneCount);

    gen.nextLine(); // ignore 'resultatene:''

    for (size_t iResultat = 0; iResultat < resultateneCount; ++iResultat)
    {

        gen.nextLine(); // ignore '- resultat:'

        auto[idrettKey, idrett] = gen.nextStringStringPair();
        //IO::printline(idrettKey, ":", idrett);   

        auto[divisjonKey, divisjon] = gen.nextStringStringPair();
        //IO::printline(divisjonKey, ":", divisjon);   

        auto[hjemmelagKey, hjemmelag] = gen.nextStringStringPair();
        //IO::printline(hjemmelagKey, ":", hjemmelag);   

        auto[bortelagKey, bortelag] = gen.nextStringStringPair();
        //IO::printline(bortelagKey, ":", bortelag);   

        auto[datoKey, dato] = gen.nextStringStringPair();
        //IO::printline(datoKey, ":", dato);   

        auto[overtidKey, overtid] = gen.nextStringBoolPair();
        //IO::printline(overtidKey, ":", overtid);   

        auto[hjemmepoengCountKey, hjemmepoengCount] = gen.nextStringUintPair();
        //IO::printline(hjemmepoengCountKey, ":", hjemmepoengCount);   


        gen.nextLine(); // ignore 'hjemmepoeng:'

        for (size_t iHjemmepoeng = 0; iHjemmepoeng < hjemmepoengCount; ++iHjemmepoeng)
        {
            auto[spillerkey, spiller] = gen.nextStringUintPair();
            //IO::printline(spillerkey, ":", spiller);  
        }
        
        auto[bortepoengCountKey, bortepoengCount] = gen.nextStringUintPair();
        //IO::printline(bortepoengCountKey, ":", bortepoengCount);

        gen.nextLine(); // ignore 'bortepoeng:'

for (size_t iBortepoeng = 0; iBortepoeng < bortepoengCount; ++iBortepoeng)
{
    auto[spillerkey, spiller] = gen.nextStringUintPair();
    //IO::printline(spillerkey, ":", spiller);  
}

    }
    //IO::printline("\n\n------ DEBUG decodeResultatene ------\n\n");
    return 0;
}

auto decodeDivisjon(DB::Divisjon& divisjon, string_view strview) -> Parser::Error
{

    //IO::printline("\n\n------ DEBUG decodeDivisjon ------\n\n");


    auto gen = KeyValueGenerator{strview};

    auto[divisjonkey, divisjonValue] = gen.nextStringStringPair();
    //IO::printline(divisjonkey, ":", divisjonValue);

    auto[lageneCountkey, lageneCount] = gen.nextStringUintPair();
    //IO::printline(lageneCountkey, ":", lageneCount);

    gen.nextLine(); // ignore lagene:

    for (size_t iLag = 0; iLag < lageneCount; ++iLag) 
    {
        auto[lagkey, lag] = gen.nextStringStringPair();
        //IO::printline(lagkey, ":", lag); 

        auto[adressekey, adresse] = gen.nextStringStringPair();
        //IO::printline(adressekey, ":", adresse); 
    
        auto[spillereneCountkey, spillereneCount] = gen.nextStringUintPair();
        //IO::printline(spillereneCountkey, ":", spillereneCount); 
        
            
        gen.nextLine(); // ignore spillerene:
            
        for (size_t iSpiller = 0; iSpiller < spillereneCount; ++iSpiller)
        {
            auto[spillerkey, spiller] = gen.nextStringUintPair();
            //IO::printline(spillerkey, ":", spiller);         
        }
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

        }
    }
    //IO::printline("\n\n------ DEBUG decodeDivisjon ------\n\n");
    return 0;
}


}