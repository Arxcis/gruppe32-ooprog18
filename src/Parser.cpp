#include <gruppe32/Parser.hpp>

#include <string>
#include <iomanip>
#include <utility>

namespace gruppe32::Parser 
{

auto LineGenerator::nextLine() -> std::string
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

auto LineGenerator::nextStringStringPair() -> pair<string,string>
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

auto LineGenerator::nextStringIntPair() -> pair<string,int>
{
    auto[key, valueString] = nextStringStringPair();
    return pair<string,int>{key, std::stoi(valueString)};
};

auto LineGenerator::nextStringBoolPair() -> pair<string,bool>
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


auto encodeIdrettene(const DB::Idrettene& idrettene) -> string 
{
    return "";
}


auto decodeIdrettene(DB::Idrettene& idrettene, string_view strview) -> Parser::Error 
{
    std::cout << "\n\n------ DEBUG decodeIdrettene ------\n\n";

    auto gen = LineGenerator{strview, 0};

    auto[idretteneCountkey, idretteneCount] = gen.nextStringIntPair();
    IO::printline("idretteneCount:", idretteneCount);

    gen.nextLine(); // ignore idrettene:

    for (auto iIdrett = 0; iIdrett < idretteneCount; ++iIdrett) 
    {
        auto[idrettKey, idrett] = gen.nextStringStringPair();
        IO::printline(idrettKey, ":", idrett);

        auto[tabelltypekey, tabelltype] = gen.nextStringIntPair();
        IO::printline(tabelltypekey, ":", tabelltype);
        
        auto[divisjoneneCountkey, divisjoneneCount] = gen.nextStringIntPair();
        IO::printline(divisjoneneCountkey, ":", divisjoneneCount);
    
        gen.nextLine(); // ignore divisjonene:

        for (auto iDivisjon = 0; iDivisjon < divisjoneneCount; ++iDivisjon) 
        {
            auto[divisjonkey, divisjon] = gen.nextStringStringPair();
            IO::printline(divisjonkey, ":", divisjon);

            auto[lageneCountkey, lageneCount] = gen.nextStringIntPair();
            IO::printline(lageneCountkey, ":", lageneCount);

            gen.nextLine(); // ignore lagene:

            for (auto iLag = 0; iLag < lageneCount; ++iLag) 
            {
                auto[lagkey, lag] = gen.nextStringStringPair();
                IO::printline(lagkey, ":", lag); 

                auto[adressekey, adresse] = gen.nextStringStringPair();
                IO::printline(adressekey, ":", adresse); 
            
                auto[spillereneCountkey, spillereneCount] = gen.nextStringIntPair();
                IO::printline(spillereneCountkey, ":", spillereneCount); 
            
                
                gen.nextLine(); // ignore spillerene:
                
                for (auto iSpiller = 0; iSpiller < spillereneCount; ++iSpiller) 
                {
    
                    auto[spillerkey, spiller] = gen.nextStringIntPair();
                    IO::printline(spillerkey, ":", spiller);         
                }
            }   
            
            gen.nextLine(); // ignore terminliste:
            gen.nextLine(); // ignore hjemmelagene:

            for (auto iHjemmelag = 0; iHjemmelag < lageneCount; ++iHjemmelag) 
            {

                auto[hjemmelagkey, hjemmelag] = gen.nextStringStringPair();
                IO::printline(hjemmelagkey, ":", hjemmelag);  


                gen.nextLine(); // ignore bortelagene:

                for (auto iBortelag = 0; iBortelag < lageneCount-1; ++iBortelag) 
                {
                    auto[bortelagkey, bortelag] = gen.nextStringStringPair();
                    IO::printline(bortelagkey, ":", bortelag);  
                    
                    auto[datokey, dato] = gen.nextStringStringPair();
                    IO::printline(datokey, ":", dato);  

                    auto[resultkey, result] = gen.nextStringBoolPair();
                    IO::printline(resultkey, ":", result);  

                    if (result) 
                    {
                        auto[overtidkey, overtid] = gen.nextStringBoolPair();
                        IO::printline(overtidkey, ":", overtid);  
                    
                        auto[hjemmepoengCountkey, hjemmepoengCount] = gen.nextStringIntPair();
                        IO::printline(hjemmepoengCountkey, ":", hjemmepoengCount);

                        gen.nextLine(); // ignore hjemmepoeng:

                        for (auto iHjemmepoeng = 0; iHjemmepoeng < hjemmepoengCount; ++iHjemmepoeng) 
                        {
                            auto[spillerkey, spiller] = gen.nextStringIntPair();
                            IO::printline(spillerkey, ":", spiller);  
                        }
                        
                        auto[bortepoengCountKey, bortepoengCount] = gen.nextStringIntPair();
                        IO::printline(bortepoengCountKey, ":", bortepoengCount);

                        gen.nextLine(); // ignore 'bortepoeng:'

                        for (auto iBortepoeng = 0; iBortepoeng < bortepoengCount; ++iBortepoeng) 
                        {
                            auto[spillerkey, spiller] = gen.nextStringIntPair();
                            IO::printline(spillerkey, ":", spiller);  
                        }
                    }
                }
            }
        }
    }

    std::cout << "\n\n------ DEBUG decodeIdrettene ------\n\n";

	return 0;
}

auto encodeSpillerene(const DB::Spillerene& spillerene) -> string 
{
    return "";
}
auto decodeSpillerene(DB::Spillerene& spillerene, string_view strview) -> Parser::Error
{
    std::cout << "\n\n------ DEBUG decodeSpillerene ------\n\n";
 
    auto gen = LineGenerator{strview};


    auto[sisteguidKey, sisteguid] = gen.nextStringIntPair();
    IO::printline(sisteguidKey, ":", sisteguid);  

    auto[spillereneCountKey, spillereneCount] = gen.nextStringIntPair();
    IO::printline(spillereneCountKey, ":", spillereneCount);

    gen.nextLine(); // ignore 'spillerene:'

    for (auto iSpiller = 0; iSpiller < spillereneCount; ++iSpiller) 
    {
        auto[spillereneCountKey, spillereneCount] = gen.nextStringStringPair();
        IO::printline(spillereneCountKey, ":", spillereneCount);

        auto[guidKey, guid] = gen.nextStringIntPair();
        IO::printline(guidKey, ":", guid);

        auto[addresseKey, addresse] = gen.nextStringStringPair();
        IO::printline(addresseKey, ":", addresse);
    }

    std::cout << "\n\n------ DEBUG decodeSpillerene ------\n\n";
    
    return 0;    
}


auto decodeResultatene(DB::Idrettene& idrettene, string_view strview) -> Parser::Error
{

    std::cout << "\n\n------ DEBUG decodeResultatene ------\n\n";
 

    auto gen = LineGenerator{strview};

    auto[resultateneCountKey, resultateneCount] = gen.nextStringIntPair();
    IO::printline(resultateneCountKey, ":", resultateneCount);

    gen.nextLine(); // ignore 'resultatene:''

    for (auto iResultat = 0; iResultat < resultateneCount; ++iResultat) 
    {

        gen.nextLine(); // ignore '- resultat:'

        auto[idrettKey, idrett] = gen.nextStringStringPair();
        IO::printline(idrettKey, ":", idrett);   

        auto[divisjonKey, divisjon] = gen.nextStringStringPair();
        IO::printline(divisjonKey, ":", divisjon);   

        auto[hjemmelagKey, hjemmelag] = gen.nextStringStringPair();
        IO::printline(hjemmelagKey, ":", hjemmelag);   

        auto[bortelagKey, bortelag] = gen.nextStringStringPair();
        IO::printline(bortelagKey, ":", bortelag);   

        auto[datoKey, dato] = gen.nextStringStringPair();
        IO::printline(datoKey, ":", dato);   

        auto[overtidKey, overtid] = gen.nextStringBoolPair();
        IO::printline(overtidKey, ":", overtid);   

        auto[hjemmepoengCountKey, hjemmepoengCount] = gen.nextStringIntPair();
        IO::printline(hjemmepoengCountKey, ":", hjemmepoengCount);   


        gen.nextLine(); // ignore 'hjemmepoeng:'

        for (auto iHjemmepoeng = 0; iHjemmepoeng < hjemmepoengCount; ++iHjemmepoeng) 
        {
            auto[spillerkey, spiller] = gen.nextStringIntPair();
            IO::printline(spillerkey, ":", spiller);  
        }
        
        auto[bortepoengCountKey, bortepoengCount] = gen.nextStringIntPair();
        IO::printline(bortepoengCountKey, ":", bortepoengCount);

        gen.nextLine(); // ignore 'bortepoeng:'

        for (auto iBortepoeng = 0; iBortepoeng < bortepoengCount; ++iBortepoeng) 
        {
            auto[spillerkey, spiller] = gen.nextStringIntPair();
            IO::printline(spillerkey, ":", spiller);  
        }

    }


    std::cout << "\n\n------ DEBUG decodeResultatene ------\n\n";


    return 0;
}

auto decodeDivisjon(DB::Divisjon& divisjon, string_view strview) -> Parser::Error
{

    std::cout << "\n\n------ DEBUG decodeDivisjon ------\n\n";


    auto gen = LineGenerator{strview};

    auto[divisjonkey, divisjonValue] = gen.nextStringStringPair();
    IO::printline(divisjonkey, ":", divisjonValue);

    auto[lageneCountkey, lageneCount] = gen.nextStringIntPair();
    IO::printline(lageneCountkey, ":", lageneCount);

    gen.nextLine(); // ignore lagene:

    for (auto iLag = 0; iLag < lageneCount; ++iLag) 
    {
        auto[lagkey, lag] = gen.nextStringStringPair();
        IO::printline(lagkey, ":", lag); 

        auto[adressekey, adresse] = gen.nextStringStringPair();
        IO::printline(adressekey, ":", adresse); 
    
        auto[spillereneCountkey, spillereneCount] = gen.nextStringIntPair();
        IO::printline(spillereneCountkey, ":", spillereneCount); 
        
            
        gen.nextLine(); // ignore spillerene:
            
        for (auto iSpiller = 0; iSpiller < spillereneCount; ++iSpiller) 
        {

            auto[spillerkey, spiller] = gen.nextStringIntPair();
            IO::printline(spillerkey, ":", spiller);         
        }
    }   
    
    gen.nextLine(); // ignore terminliste:
    gen.nextLine(); // ignore hjemmelagene:

    for (auto iHjemmelag = 0; iHjemmelag < lageneCount; ++iHjemmelag) 
    {

        auto[hjemmelagkey, hjemmelag] = gen.nextStringStringPair();
        IO::printline(hjemmelagkey, ":", hjemmelag);  


        gen.nextLine(); // ignore bortelagene:

        for (auto iBortelag = 0; iBortelag < lageneCount-1; ++iBortelag) 
        {
            auto[bortelagkey, bortelag] = gen.nextStringStringPair();
            IO::printline(bortelagkey, ":", bortelag);  
            
            auto[datokey, dato] = gen.nextStringStringPair();
            IO::printline(datokey, ":", dato);  

        }

    }

    std::cout << "\n\n------ DEBUG decodeDivisjon ------\n\n";

    return 0;
}


}