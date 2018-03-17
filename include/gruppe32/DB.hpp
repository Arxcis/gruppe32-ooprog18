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
    size_t hjemmeM�l, borteM�l;
    */
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


//
// INTERMEDIATE TYPES - IMPORT/EXPORT types
//  Types which are not stored internally, but used for exporting/importing to console and files.
//


using std::string;
///
/// <summary> Used for importing new Resultat's from a user provided file.
///           File format specified in format-resultatene.yml </summary>
///
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
using std::vector;
///
/// <summary> Used for exporting a representation of the current table of a given Divisjon.
///           Can be exported to console or file. 
///           File format specified in format-tabell.yml files </summary>
///
class TabellDivisjon 
{
public:
    struct TabellLag 
    {
        size_t plassering;
        size_t poeng;
        size_t hjemmeScoringer;
        size_t hjemmeBaklengs;
        size_t borteScoringer;
        size_t borteBaklengs;
        size_t seier;
        size_t uavgjort;
        size_t tap;
    };

    string idrett;
    string divisjon;    
    Idrett::Tabell tabellPoengType;
    vector<TabellLag> lagene;
};


using std::string;
using std::map;
///
/// <summary> Used for exporting only the dates on which matches are held. 
///           Used like this: terminListe.data[hjemmelag][bortelag] = "2018-03-27"; 
///           File format specified in format-terminliste.yml </summary>
///
class Terminliste 
{ 
public:
    string idrett;
    string divisjon;
    map<string, map<string,string>> data;
};


using std::string;
using std::size_t;
using std::vector;
///
/// <summary> Used for exporting tables with topp 10 players. Exports to console of file.
///           File formate specified in format-toppscorerene.yml </summary>
///
class Toppscorerene
{
public:
    struct ToppScorer 
    {
        size_t score;
        string navn;
        string lag;
    };
    string idrett;
    string divisjon;
    vector<ToppScorer> data;
};


} // end namespace 
