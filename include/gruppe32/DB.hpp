#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include <array>
#include <frode/ListTool2b.h>


/// <summary> DB database </summary>
namespace gruppe32::DB  
{
//Using directives:
using std::size_t;
using std::vector;
using std::array;
using std::string;

/**
 *
 */
class Spiller 
{
	size_t id;
	string name;
	string address;
public:

};


class Spillerne
{
    size_t count;
public:
    frode::List data{ frode::Sorted };
};


class Lag 
{
public:
	constexpr static size_t MAX_SPILLERE = 50;
private:
	string navn;
	string adresse;
	array<size_t, MAX_SPILLERE> spillere;
};


class Resultat
{
	constexpr static size_t LENGTH_DATE = 9;

	array<char, LENGTH_DATE> dato;
	bool overtid;
	array<size_t, Lag::MAX_SPILLERE> hjemmeScorere;
	array<size_t, Lag::MAX_SPILLERE> borteScorere;
public:
	/*

	size_t hjemmeMål, borteMål;
	*/
};



class Divisjon
{
	constexpr static size_t MAX_LAG = 30;

	string navn;
	array<Lag, MAX_LAG> lag;
	array<vector<Resultat>, MAX_LAG> terminListe;
public:
	/*
	size_t lagCount() {
		return lag.size();
	}
	*/
};

class Idrett
{
	enum Tabell
	{
		SEIER_2_UAVGJORT_1_TAP_0,
		SEIER_3_UAVGJORT_1_TAP_0,
		SEIER_3_OVERTID_2_UAVGJORT_1_TAP_0
	};

	vector<Divisjon> divisjoner;
	Tabell tabell;
	string name;
public:

};
class Idrettene 
{
    size_t count;
public:
    frode::List data { frode::Sorted };
};

struct Context 
{
    Idrettene idrettene;
    Spillerne spillerne;
};


} // end namespace 
