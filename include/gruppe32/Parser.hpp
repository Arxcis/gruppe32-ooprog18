#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <experimental/string_view>

#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>

namespace gruppe32
{

using std::size_t;
using std::string;
using std::pair;
using std::experimental::string_view;

/// <summary> Translates files into internal datastructure </summary>
class Parser
{
public:
    string_view strview;
    int startofline =  0;
    int endofline = 9999999;
    int linecount = 0;
    const string whitelistedCharacters = "0123456789abcdefghijklmnopqrstuvwxyzæøåABCDEFGHIJKLMNOPQRSTUVWXYZÆØÅ-:";

    auto nextLine() -> string;
    auto nextStringString() -> pair<string,string>;
    auto nextStringUint() -> pair<string, size_t>;
    auto nextStringBool() -> pair<string, bool>;
};

/// <summary> Decoding strings to the internal datastructure </summary>
namespace Decode
{

using std::string;
using std::size_t;
using std::vector;
using std::experimental::string_view;
using Error = std::size_t;
constexpr Decode::Error ERROR = 1;


/// <summary> Decoding the data format for the internal datastructure Idrettene. </summary>
/// <param name="strview"> example found in format-data-idrettene.yml </param>
auto dataIdrettene(DB::Idrettene& idrettene, string_view strview) -> Decode::Error;

/// <summary> Decoding the data format for the internal datastructure Spillerene. </summary>
/// <param name="strview"> example found in format-data-spillerene.yml </param>
auto dataSpillerene(DB::Spillerene& spillerene, string_view strview) -> Decode::Error;

/// <summary> Decoding the input format Resultatene.  </summary>
/// <param name="resultatene"> Resultat with additional keys representing hierarchy </param>
/// <param name="strview"> example found in format-input-resultatene.yml </param>
auto inputResultatene(vector<DB::InputResultat>& resultatene, string_view strview) -> Decode::Error;

/// <summary> Decode-only. </summary>
/// <param name="strview"> example found in format-input-divisjon.yml </param>
auto inputDivisjon(DB::Divisjon& divisjon, string_view strview) -> Decode::Error;


} // ::Decode



using std::string;
using std::stringstream;
using std::size_t;

/// <summary> Translates internal datastructure to file format </summary>
class Printer
{
public:
    string outString = "";
    size_t indent = 0;

    void lineEmpty();
    void lineIndent();
    void lineString(const string key);
    void lineStringString(const string key, const string value);
    void lineStringUint(const string key, const size_t value);
    void lineStringBool(const string key, const bool value);
    void lineDashString(const string key);
    void lineDashStringString(const string key, const string value);
    void lineDashStringUint(const string key, const size_t value);
    void tabRight();
    void tabLeft();
    auto getString() -> string;
};



/// <summary> Encoding internal datastructure into strings,
///           which can be shipped to console or file. </summary>
namespace Encode
{
using std::size_t;
using std::string;
using std::experimental::string_view;
using std::vector;


auto viewTabelltype(DB::Idrett::TabellType tabellType) -> string;

/// <summary> Encode entire 'Idrettene' to string as yaml. Lossless encoding.
//              Use case: Store internal datastructure 'idrettene' to file. /summary>
/// <returns> string - example found in format-data-idrettene.yml </returns>
auto dataIdrettene(DB::Idrettene& idrettene) -> string;


/// <summary> Encode entire 'Spillerene' to string yaml format. Lossless encoding.
//               Use case: Save internal datastructure 'spillerene' to file. </summary>
/// <returns> string - example found in format-data-spillerene.yml </returns>
auto dataSpillerene(DB::Spillerene& spillerene) -> string;


auto dataDato(const size_t year, const size_t month, const size_t day) -> string;


/// <summary> Encode a single Idrett to a viewable format.
//            Not showing details about spillerene.  </summary>
/// <returns> string - example found in format-view-idrett.yml </returns>
auto viewIdrett(const DB::Idrett& idrett) -> string;

/// <summary> Encode idrettene to a viewable format.
///            Not showing any details about divisjonene, lagene and spillerene. </summary>
/// <returns> string - example found in format-view-idrettene.yml </returns>
auto viewIdrettene(DB::Idrettene& idrettene) -> string;


auto viewIdretteneCompact(DB::Idrettene& idrettene, bool divisjon=false, bool lag=false, bool spillere=false) -> string;


/// <summary> Helper function for encodeResultateneDivisjon and encodeResultateneIdrett </summary>
auto viewResultatene(const vector<DB::ViewResultat>& resultatene) -> string;


/// <summary> Encode a collection of spillere to a viewable format. </summary>
/// <returns> string - example found in format-view-spillerene.yml </returns>
auto viewSpillerene(DB::Spillerene& spiller) -> string;



/// <summary> Helper function for encodeTabellDivisjon and encodeTabelleneIdrett </summary>
auto viewTabellene(const std::vector<DB::Tabell>& tabellene) -> string;


/// <summary> Helper function for encodeToppscorereneDivisjon and encodeToppscorereneLag </summary>
void viewToppscorerene(Printer& p, const vector<DB::Toppscorer>& toppscorerene);

/// <summary> Encode a collection of Toppscorere for a given divisjon to a viewable format.  </summary>
/// <returns> string - example found in format-view-toppscorerene-divisjon.yml </returns>
auto viewToppscorereneDivisjon(const vector<DB::Toppscorer>& toppscorerene,
                               const string divisjon) -> string;

/// <summary> Encode a collection of Toppscorere for a given divisjon to a viewable format. </summary>
/// <returns> string - example found in format-view-toppscorerene-lag.yml </returns>
auto viewToppscorereneLag(const vector<DB::Toppscorer>& toppscorerene,
                          const string lag) -> string;



/// <summary> Encode-only. Output example:  </summary>
/// <returns> string - example found in format-view-divisjon.yml </returns>
auto viewTerminliste(const DB::Terminliste& terminliste) -> string;


} // ::Encode
} // ::gruppe32
