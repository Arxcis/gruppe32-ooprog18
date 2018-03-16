#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include <array>
#include <map>

#include <frode/ListTool2b.h>


/// <summary> Database definitions </summary>
namespace gruppe32::DB  
{


using std::string;
using std::size_t;

class Spiller : public listtool::NumElement
{
public:
    size_t guid;
    string name;
    string address;

    Spiller(int _guid, std::string _name, std::string _address)
        :listtool::NumElement(_guid),
        guid(_guid),
        name(_name),
        address(_address){}
};

using std::size_t;

class Spillerene
{
public:
    std::size_t count; //
    listtool::List data;
    Spillerene(std::size_t _count = 0) : count(_count), data(listtool::List(listtool::Sorted)){}
};


using std::size_t;
using std::vector;
using std::string;

class Lag 
{
public:
    string navn;
    string adresse;
    vector<size_t> spillere;
};


using std::size_t;
using std::array;
using std::vector;

class Resultat
{    
public:
    constexpr static size_t LENGTH_DATE = 9;
    array<char, LENGTH_DATE> dato;
    bool overtid;
    vector<size_t> hjemmeScorere;
    vector<size_t> borteScorere;
    /*
    size_t hjemmeMål, borteMål;
    */
};


using std::size_t;
using std::string;
using std::vector;
using std::map;

class Divisjon
{
private:
    string navn;
    vector<Lag> lag;
    map<string, map<string,Resultat>> terminListe;
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
    std::size_t count; //
    listtool::List data;
    Idrettene(std::size_t _count = 0) : count(_count), data(listtool::List(listtool::Sorted)) {}
};

struct Context 
{
    
    Idrettene idrettene;
	Spillerene spillerene;
    Context() {
        spillerene = Spillerene();
        idrettene = Idrettene();
    }
};


} // end namespace 
