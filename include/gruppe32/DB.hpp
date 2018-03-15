#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include <array>
#include <frode/ListTool2b.h>


/// <summary> Database definitions </summary>
namespace gruppe32::DB  
{


using std::string;
using std::size_t;

class Spiller 
{
public:
    size_t guid;
    string name;
    string address;

};


using std::size_t;

class Spillerene
{

public:
    std::size_t count;
    listtool::List data{ listtool::Sorted };
};


using std::size_t;
using std::array;
using std::string;

class Lag 
{
public:
    constexpr static size_t MAX_SPILLERE = 50;
    string navn;
    string adresse;
    array<size_t, MAX_SPILLERE> spillere;
};


using std::size_t;
using std::array;

class Resultat
{    
public:
    constexpr static size_t LENGTH_DATE = 9;
    array<char, LENGTH_DATE> dato;
    bool overtid;
    array<size_t, Lag::MAX_SPILLERE> hjemmeScorere;
    array<size_t, Lag::MAX_SPILLERE> borteScorere;
    /*
    size_t hjemmeMål, borteMål;
    */
};


using std::size_t;
using std::string;
using std::array;
using std::vector;

class Divisjon
{
private:
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


using std::string;
using std::vector;

class Idrett
{
public:
    enum Tabell
    {
        SEIER_2_UAVGJORT_1_TAP_0,
        SEIER_3_UAVGJORT_1_TAP_0,
        SEIER_3_OVERTID_2_UAVGJORT_1_TAP_0
    };

private:
    vector<Divisjon> divisjoner;
    Tabell tabell;
    string name;

};


using std::size_t;

class Idrettene 
{
public:
    size_t count;
    listtool::List data { listtool::Sorted };
};

struct Context 
{
    Idrettene idrettene;
	Spillerene spillerene;
};


} // end namespace 
