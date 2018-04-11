# Logg møte 2: onsdag 21.03.2018

### Saksliste
* Status funksjonalitet
* Hva Gjenstår?
* Stats
* Når drar folk?

### Sak 1: Status siste dager

* Hva har Halvor gjort 2 siste dager:
    - Print spillere, idretter
    - Legg til spillere, idretter
    - Fjern spillere, idretter

* Hva har Jonas gjort 2 siste dager:
    - Print/Skriv til fil terminliste idrett | idrett & divisjon
    - Print/Skriv til fil resultatliste idrett | idrett & divisjon
    - Print/Skriv til fil tabell idrett | idrett & divisjon
    - Les og skriv til fil på oppstart og nedstenging av program



### Sak 2: Hva gjenstår? 

* Les resultat fra fil inn i eksisterende idrett, divisjon, hjemmelag og bortelag, og eksterer resultat allerede på denne datoen? ( JONAS )
* Håndter lagspillere ( HALVOR )
* Create divisjon and delete divisjon ( HALVOR )
++++ masse polish , refactoring i App


### Sak 3: Når drar folk?

* Halvor drar mandag
* Jonas drar søndag
* Møtes ekstra dag?
* Ja
* Hvilken dag?
  - torsdag?
  - fredag?
  - lørdag?
* Hvilken igjen?
  - Fredag etter mobile ---->>>>>>>>>>>> 

### Stats

* CLOC
```
cloc include/gruppe32/ src/App.cpp src/IO.cpp src/main.cpp src/Valid.cpp src/DB.cpp src/Terminal.cpp
      13 text files.
      13 unique files.                              
       0 files ignored.

github.com/AlDanial/cloc v 1.74  T=0.06 s (204.2 files/s, 43329.3 lines/s)
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C++                              6            273             96           1414
C/C++ Header                     7            215            162            598
-------------------------------------------------------------------------------
SUM:                            13            488            258           2012
-------------------------------------------------------------------------------
```


* SLOC
```
$ sloc include/gruppe32/ src/ test/ --details --format cli-table  --keys todo,comment,source,total
┌───────────────────────────────┬───────┬─────────┬────────┬──────────┐
│ Path                          │ To Do │ Comment │ Source │ Physical │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ include/gruppe32/App.hpp      │ 0     │ 16      │ 67     │ 103      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ include/gruppe32/DB.hpp       │ 2     │ 38      │ 183    │ 258      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ include/gruppe32/IO.hpp       │ 0     │ 60      │ 71     │ 156      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ include/gruppe32/Parser.hpp   │ 0     │ 44      │ 95     │ 183      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ include/gruppe32/Terminal.hpp │ 0     │ 2       │ 89     │ 111      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ include/gruppe32/Test.hpp     │ 0     │ 2       │ 92     │ 119      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ include/gruppe32/Valid.hpp    │ 0     │ 16      │ 18     │ 45       │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src/App.cpp                   │ 0     │ 84      │ 723    │ 936      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src/DB.cpp                    │ 0     │ 2       │ 5      │ 7        │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src/IO.cpp                    │ 1     │ 6       │ 257    │ 304      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src/ListTool2b.cpp            │ 0     │ 410     │ 392    │ 668      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src/Parser.cpp                │ 1     │ 35      │ 693    │ 949      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src/Terminal.cpp              │ 0     │ 4       │ 277    │ 322      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src/Valid.cpp                 │ 0     │ 1       │ 55     │ 72       │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src/main.cpp                  │ 0     │ 18      │ 100    │ 142      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ test/test.cpp                 │ 0     │ 0       │ 12     │ 17       │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ test/test_Parser.cpp          │ 1     │ 70      │ 776    │ 932      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ test/test_Valid.cpp           │ 0     │ 0       │ 38     │ 50       │
└───────────────────────────────┴───────┴─────────┴────────┴──────────┘
```