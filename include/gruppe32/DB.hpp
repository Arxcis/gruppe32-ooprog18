#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include <array>
#include <frode/ListTool2b.h>

namespace gruppe32::DB  
{
//Using directives:
using std::size_t;
using std::vector;
using std::array;

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

class Resultat
{
	const size_t LENGTH_DATE = 9;
	const size_t MAX_SPILLERE = 50;

	array<char, DATE_LENGTH> dato;
	bool overtid;
	array<size_t, MAX_SPILLERE> hjemmeScorere;
	array<size_t, MAX_SPILLERE> borteScorere;
private:
	/*

	size_t hjemmeMål, borteMål;
	*/
};

class Divisjon
{
	const size_t MAX_LAG = 30;

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
