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
    string name; // @TODO name or navn ? - jsolsvik 17.03.2018
    string address;

    Spiller(size_t _guid, std::string _name, std::string _address)
        :listtool::NumElement(_guid),
        guid(_guid),
        name(_name),
        address(_address){} // @TODO address or adresse ? - jsolsvik 17.03.2018
};

using std::size_t;

class Spillerene
{
public:
    std::size_t autoIncrementer; //
    listtool::List* data;
    Spillerene(std::size_t _autoIncrementer = 0)
    {
        autoIncrementer = _autoIncrementer;
        data = new listtool::List(listtool::Sorted); 
    }
};


using std::size_t;
using std::vector;
using std::string;

class Lag 
{
public:
    string navn;
    string adresse;
    vector<size_t> spillerene;
};


using std::size_t;
using std::vector;
using std::string;

class Resultat
{    
public:
    // constexpr static size_t LENGTH_DATE = 9;
    // array<char, LENGTH_DATE> dato;
    string dato; // @TODO Discuss how critical it is to use a char array here.
                 //   It is difficult to copy a string into the char array.
                 //   Using a string as convencience for now - JSolsvik 16.03.18
    bool spilt = false;
    bool overtid = false;
    vector<size_t> hjemmeScorerene{};
    vector<size_t> borteScorerene{};
    /*
    size_t hjemmeMål, borteMål;
    */
};

class ResultatWithKeys : public Resultat 
{
public:
    string idrett;
    string divisjon;
    string hjemmelag;
    string bortelag;

    ResultatWithKeys(
        string _idrett,
        string _divisjon,
        string _hjemmelag,
        string _bortelag,
        string _dato, 
        bool _spilt,
        bool _overtid) 
    :idrett(_idrett)
    ,divisjon(_divisjon)
    ,hjemmelag(_hjemmelag)
    ,bortelag(_bortelag)
    {
        dato = _dato;
        spilt = _spilt;
        overtid = overtid;
    }
};


using std::size_t;
using std::string;
using std::vector;
using std::map;

class Divisjon
{
public:
    string navn;
    vector<Lag> lagene;
    map<string, map<string,Resultat>> terminListe;
    /*
    size_t lagCount() {
        return lag.size();
    }
    */
};


using std::size_t;
using std::string;
using std::vector;

class Idrett : public listtool::TextElement
{
public:
    enum Tabell : size_t
    {
        SEIER_2_UAVGJORT_1_TAP_0 = 210,
        SEIER_3_UAVGJORT_1_TAP_0 = 310, 
        SEIER_3_OVERTID_2_UAVGJORT_1_TAP_0 = 320
    };

    string name; // @todo discuss - name or navn? jsolsvik 16.03.18
    Tabell tabell;
    vector<Divisjon> divisjonene;

    Idrett(std::string _name, Tabell _tabell)
        :listtool::TextElement(_name.c_str()),
        name(_name),
        tabell(_tabell)
        {}
};


using std::size_t;

class Idrettene 
{
public:
    std::size_t count; //
    listtool::List* data;
    Idrettene(std::size_t _count = 0) 
    {
        count = _count;
        data = new listtool::List(listtool::Sorted); 
    }
};

struct Context 
{
    
    Idrettene idrettene;
	Spillerene spillerene;
    Context() {
        spillerene = Spillerene(0);
        idrettene = Idrettene(0);
    }
};


} // end namespace 
