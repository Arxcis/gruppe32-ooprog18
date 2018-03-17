#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <string_view>

#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>

/// <summary> Decoding strings to the internal datastructure </summary>
namespace gruppe32::Decode
{


using std::size_t;
using std::string;
using std::pair;
using std::string_view;
using std::vector;
using Error = std::size_t;
constexpr Decode::Error ERROR = 1;

class KeyValueGenerator 
{
public:
    string_view strview;
    size_t startofline =  0;
    
    auto nextLine() -> string;
    auto nextStringStringPair() -> pair<string,string>;
    auto nextStringUintPair() -> pair<string, size_t>;
    auto nextStringBoolPair() -> pair<string, bool>;
};


/// <summary> Decode. Has a corresponding encode function. </summary>
/// <param name="strview"> example found in format-idrettene.yml </param>
auto idrettene(DB::Idrettene& idrettene, string_view strview) -> Decode::Error;

/// <summary> Decode. Has a corresponding encode function. </summary>
/// <param name="strview"> example found in format-spillerene.yml </param>
auto spillerene(DB::Spillerene& spillerene, string_view strview) -> Decode::Error;

/// <summary> Decode-only. </summary>
/// <param name="resultatene"> Resultat with additional keys representing hierarchy </param>
/// <param name="strview"> example found in format-resultatene.yml </param>
auto resultatene(vector<DB::ResultatWithKeys>& resultatene, string_view strview) -> Decode::Error;

/// <summary> Decode-only. </summary>
/// <param name="strview"> example found in format-divisjon.yml </param>
auto divisjon(DB::Divisjon& divisjon, string_view strview) -> Decode::Error; 


} // end namespace decode


namespace gruppe32::Encode 
{

using std::string;
using std::stringstream;
using std::size_t;

class LinePrinter 
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


using std::size_t;
using std::string;
using std::string_view;
using std::vector;


/// <summary> Encode. Has a corresponding decode function. </summary>
/// <returns> string - example found in format-idrettene.yml </returns>
auto idrettene(DB::Idrettene& idrettene) -> string;

/// <summary> Encode. Has a corresponding decode function. </summary>
/// <returns> string - example found in format-spillerene.yml </returns>
auto spillerene(DB::Spillerene& spillerene) -> string;



/// <summary> Encode-only. 
///          Helper function for encodeResultateneDivisjon and encodeResultateneIdrett </summary>
void resultatene(LinePrinter& p, const vector<DB::ResultatWithKeys>& resultatene);

/// <summary> Encode-only. </summary>
/// <returns> string - example found in format-resultatene-divisjon.yml </returns>
auto resultateneDivisjon(const vector<DB::ResultatWithKeys>& resultatene,
                               const string divisjon) -> string;

/// <summary> Encode-only.</summary>
/// <returns> string - example found in format-resultatene-idrett.yml </returns>
auto resultateneIdrett(const vector<DB::ResultatWithKeys>& resultatene,
                             const string idrett) -> string;



/// <summary> Encode-only. 
///          Helper function for encodeTabellDivisjon and encodeTabelleneIdrett </summary>
void tabellLagene(LinePrinter& p, const vector<DB::Tabell::Lag>& lagene);

/// <summary> Encode-only. </summary>
/// <returns> string - example found in format-tabell-divisjon.yml </returns>
auto tabellDivisjon(const DB::Tabell& tabellDivisjon) -> string;

/// <summary> Encode-only. Output example:  </summary>
/// <returns> string - example found in format-tabellene-idrett.yml </returns>
auto tabelleneIdrett(const vector<DB::Tabell>& tabellene,
                           const string idrett,
                           const DB::Idrett::TabellType tabellType) -> string;



/// <summary> Encode-only. 
///          Helper function for encodeToppscorereneDivisjon and encodeToppscorereneLag </summary>
auto toppscorerene(LinePrinter& p, const vector<DB::Toppscorer>& toppscorerene);

/// <summary> encode-only. Output example:  </summary>
/// <returns> string - example found in format-toppscorerene-divisjon.yml </returns>
auto toppscorereneDivisjon(const vector<DB::Toppscorer>& toppscorerene,
                           const string divisjon) -> string;

/// <summary> Encode-only. Output example:  </summary>
/// <returns> string - example found in format-toppscorerene-lag.yml </returns>
auto toppscorereneLag(const vector<DB::Toppscorer>& toppscorerene,
                      const string lag) -> string;



/// <summary> Encode-only. Output example:  </summary>
/// <returns> string - example found in format-terminliste-divisjon.yml </returns>
auto terminliste(const DB::Terminliste& terminliste) -> string;


} // end namespace Encode