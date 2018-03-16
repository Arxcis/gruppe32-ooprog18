#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <string_view>

#include <gruppe32/DB.hpp>
#include <gruppe32/IO.hpp>

/// <summary> Parsing strings to internal datastructure and vice versa </summary>
namespace gruppe32::Parser
{


using std::size_t;
using std::string;
using std::make_pair;
using std::pair;
using std::string_view;

struct LineGenerator 
{
    std::string_view strview;
    std::size_t startofline =  0;
    
    auto nextLine() -> std::string;
    auto nextStringStringPair() -> pair<string,string>;
    auto nextStringIntPair() -> pair<string,int>;
    auto nextStringBoolPair() -> pair<string,bool>;
};


using std::size_t;
using std::string;
using std::string_view;
using DB::Idrettene;
using DB::Spillerene;
using Error = std::size_t;

constexpr Parser::Error ERROR = 1;


/// <summary> Encode. Has a corresponding decode function. </summary>
/// <returns> string - example found in format-idrettene.yml </returns>
auto encodeIdrettene(const DB::Idrettene& idrettene) -> string;

/// <summary> Encode. Has a corresponding decode function. </summary>
/// <returns> string - example found in format-spillerene.yml </returns>
auto encodeSpillerene(const DB::Spillerene& spillerene) -> string;

/// <summary> Decode. Has a corresponding encode function. </summary>
/// <param name="strview"> example found in format-idrettene.yml </param name="strview">
auto decodeIdrettene(DB::Idrettene& idrettene, string_view strview) -> Parser::Error;

/// <summary> Decode. Has a corresponding encode function. </summary>
/// <param name="strview"> example found in format-spillerene.yml </param name="strview">
auto decodeSpillerene(DB::Spillerene& spillerene, string_view strview) -> Parser::Error;



/// <summary> Encode-only. </summary>
/// <returns> string - example found in format-resultatene-divisjon.yml </returns>
auto encodeResultateneDivisjon(const DB::Divisjon& divisjon) -> string;

/// <summary> Encode-only.</summary>
/// <returns> string - example found in format-resultatene-idrett.yml </returns>
auto encodeResultateneIdrett(const DB::Idrett& idrett) -> string;

/// <summary> Encode-only. </summary>
/// <returns> string - example found in format-tabell-divisjon.yml </returns>
auto encodeTabellDivisjon(const DB::Divisjon& divisjon) -> string;

/// <summary> Encode-only. Output example:  </summary>
/// <returns> string - example found in format-tabellene-idrett.yml </returns>
auto encodeTabelleneIdrett(const DB::Idrett& idrett) -> string;

/// <summary> Encode-only. Output example:  </summary>
/// <returns> string - example found in format-terminliste-divisjon.yml </returns>
auto encodeTerminlisteDivisjon(const DB::Divisjon& divisjon) -> string;

/// <summary> Encode-only. Output example:  </summary>
/// <returns> string - example found in format-toppscorerene-divisjon.yml </returns>
auto encodeToppscorereneDivisjon(const DB::Divisjon& divisjon) -> string;

/// <summary> Encode-only. Output example:  </summary>
/// <returns> string - example found in format-toppscorerene-lag.yml </returns>
auto encodeToppscorereneLag(const DB::Divisjon& divisjon, const string lagnavn) -> string;



/// <summary> Decode-only. </summary>
/// <param name="strview"> example found in format-resultatene.yml </param name="strview">
auto decodeResultatene(DB::Idrettene& idrettene, string_view strview) -> Parser::Error;

/// <summary> Decode-only. </summary>
/// <param name="strview"> example found in format-divisjon.yml </param name="strview">
auto decodeDivisjon(DB::Divisjon& divisjon, string_view strview) -> Parser::Error; 



} // end namespace Parse