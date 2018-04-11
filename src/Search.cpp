#include <gruppe32/Search.hpp>

namespace gruppe32
{

//======================================
// SEARCH FUNCTIONS
//======================================
using std::vector;
using std::string;
using std::size_t;
using std::pair;

auto Search::filterLag(
    DB::Context& ctx,
    const string& navnIdrett,
    const string& navnDivisjon,
    const string& navnLag
) ->filterResult<DB::Lag>
{
    vector<pair<DB::Lag, vector<string>>> result{};
    string resultTreeString = "";
    string statusMsg = "";

    const size_t count = ctx.idrettene.data->noOfElements();
    for (size_t i = 1; i <= count; i++)
    {
        const auto idrett = (DB::Idrett*)ctx.idrettene.data->removeNo(i);
        resultTreeString += "|-" + idrett->name + "\n";
        for (const auto& divisjon : idrett->divisjonene)
        {
            resultTreeString += "  |-" + divisjon.navn + "\n";
            for (const auto& lag : divisjon.lagene)
            {
                if ((navnIdrett.empty() || (IO::toUpper(idrett->name).find(navnIdrett) != string::npos)) &&
                    (navnDivisjon.empty() || (IO::toUpper(divisjon.navn).find(navnDivisjon) != string::npos)) &&
                    (navnLag.empty() || (IO::toUpper(lag.navn).find(navnLag) != string::npos)))
                {
                    resultTreeString += "    |=>[ " + IO::toUpper(lag.navn) + " ]\n";
                    result.push_back(std::pair<DB::Lag,vector<string>>{ lag, {idrett->name, divisjon.navn, lag.navn} });
                }
                else
                {
                    resultTreeString += "    |-" + lag.navn + "\n";
                }
            }
        }
        ctx.idrettene.data->add(idrett);
    }
    if (result.size() > 1)
    {
        statusMsg = "Filteret er tvetydig, venligst pressiser...";
    }
    else if (result.size() == 1)
    {
        statusMsg = "Idretten: " + result[0].second[0] + ", Divisjonen: " + result[0].second[1] + ", Laget: " + result[0].second[2];
    }
    else
    {
        statusMsg = "Ingen lag i filteret, venligst ompresiser";
    }

    return filterResult<DB::Lag>{ result, resultTreeString, statusMsg };
}

auto Search::findAndPrintIdrettDivisjon(DB::Context & ctx, const string & navnIdrett, const string & navnDivisjon) -> Search::returnDivisjoneneMedIdrettNavn
{
    vector<pair<DB::Divisjon, string>> result{};
    string printout = "";
        const std::size_t count = ctx.idrettene.data->noOfElements();
        for (std::size_t i = 1; i <= count; i++)
        {
            const auto idrett = (DB::Idrett*)ctx.idrettene.data->removeNo(i);
            if (navnIdrett.empty())
            {
                printout += "  " + idrett->name + "\n";
                for (const auto& div : idrett->divisjonene)
                {
                    auto divPair = pair<DB::Divisjon, string>{ div, idrett->name };
                    if (navnDivisjon.empty())
                    {
                        printout += "  - " + div.navn + "\n";
                        result.push_back(divPair);
                    }
                    else if (div.navn.find(navnDivisjon) != std::string::npos)
                    {
                        printout += "  - " + div.navn + "\n";
                        result.push_back(divPair);
                    }
                }
            }
            else if (idrett->name.find(navnIdrett) != std::string::npos)
            {
                printout += "  " + idrett->name + "\n";
                for (const auto& div : idrett->divisjonene)
                {
                    auto divPair = pair<DB::Divisjon, string>{ div, idrett->name };
                    if (navnDivisjon.empty())
                    {
                        printout += "  - " + div.navn + "\n";
                        result.push_back(divPair);
                    }
                    else if (div.navn.find(navnDivisjon) != std::string::npos)
                    {
                        printout += "  - " + div.navn + "\n";
                        result.push_back(divPair);
                    }
                }
            }
            ctx.idrettene.data->add(idrett);
        }
        if (result.size() == 0)
        {
            printout = "Ingen divisjoner funnet!";
        }
    return Search::returnDivisjoneneMedIdrettNavn{ result, printout };
}


auto Search::divisjonene(DB::Context& ctx, const string& navnIdrett, const string& navnDivisjon)
    -> Search::returnDivisjonene
{
    vector<DB::Divisjon> result{};
    string statusmsg = "";

    DB::Idrett* idrett = (DB::Idrett* ) ctx.idrettene.data->remove(navnIdrett.c_str());

    // Error 1
    if (!idrett) {
        statusmsg =  "Idrett " + navnIdrett + " not found...";
        return Search::returnDivisjonene{result, statusmsg};
    }
    // Error 2
    if (idrett->divisjonene.size() == 0) {
        statusmsg = "Idrett " + navnIdrett + " has no divisjoner...";

        ctx.idrettene.data->add(idrett);   // because why no
        return Search::returnDivisjonene{result, statusmsg};
    }

    // Success 1
    if (navnDivisjon.empty())
    {
        for (const auto& divisjon : idrett->divisjonene)
        {
            result.push_back(divisjon);
        }

        ctx.idrettene.data->add(idrett);   // because why no
        return Search::returnDivisjonene{result, statusmsg};
    }

    for (const auto& divisjon : idrett->divisjonene)
    {
        // Success 2
        if (divisjon.navn.find(navnDivisjon) != std::string::npos)
        {
            result.push_back(divisjon);
        }
    }
    // Error 4
    if (result.empty()) {
        statusmsg = "Idrett " + navnIdrett + " has no divisjon matching " + navnDivisjon + "...";

        ctx.idrettene.data->add(idrett);   // because why no
        return Search::returnDivisjonene{result, statusmsg};
    }

    ctx.idrettene.data->add(idrett);   // because why no
    return Search::returnDivisjonene{result, statusmsg};
}

auto Search::resultatene(
    DB::Context& ctx,
    const DB::Divisjon& divisjon,
    const size_t year,
    const size_t month,
    const size_t day)
    -> Search::returnResultatene
{
    string statusmsg = "";
    std::stringstream ss;

    // Encode date
    string encodedDato = Encode::dataDato(year, month, day);

    vector<DB::ViewResultat> resultatene;

    for (const auto [hjemmelag, bortelagene] : divisjon.terminliste) // map
    {
        for (const auto [bortelag, resultat] : bortelagene)    // map
        {
            if (resultat.dato == encodedDato)
            {
                resultatene.push_back(DB::ViewResultat {
                    divisjon.navn,
                    hjemmelag,
                    bortelag,
                    encodedDato,
                    resultat.hjemmeScorerene.size(),
                    resultat.borteScorerene.size()
                });
            }
        }
    }
    // Error 4
    if (resultatene.empty()) {
        statusmsg = "No results on current dato: " + encodedDato + "...";
        return Search::returnResultatene {resultatene, statusmsg};
    }

    return Search::returnResultatene {resultatene, statusmsg};
}

} // ::gruppe32
