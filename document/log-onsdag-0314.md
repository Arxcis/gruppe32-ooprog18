# Logg møte1: onsdag 14.03.2018

### Saksliste
* Hva har vi gjort? Hvor mange prosent er vi ferdig?
* Fordele App::funksjoner som skal implementeres til mandag.


### Sak1: Hva har vi gjort?

* Meny/navigasjon-systemet er fullstendig. Ferdig. Komplett.
    - Dette gjelder altså funksjonaliteten i Terminal.cpp og IO.cpp.
* Alle App - endpoints er tilgjengelig fra menyen.
* Sette opp datastruktur:
    - Diskutert å endre arrayer til vector, men ikke implementert.
    - Diskutert å gjøre terminliste til map av maps, men ikke implementert.
* Gjøre alle frode-boilerplate oppgaver. Er klart og signert og kan leveres i morgen torsdag 15.03.
* Dokumentere alle filformater, idrettene, spillerene, divisjon og resultatene.
    - Men ikke implementert funksjoner som håndhever filformatene.
    - Vurdere å lage egen modul for fillesning.

* Fullføringsgrad av moduler:
    - Terminal 95/100
    - App 10/100
    - IO 40/100
    - File 0/100
    - Datastruktur 85/100
    - Valid 90/100
    - (Test 2/100) optional

* Dokumentasjon
    - Referanseliste har mye bra
    - Bemerkninger er godt brukt
    - Gjenstår en del på doxygen metainformasjon oppå toppen av funksjoner og klasser, men er sikkert fort gjort.

* Lines of documentation
```
$ cloc document/
       9 text files.
       9 unique files.
       1 file ignored.

github.com/AlDanial/cloc v 1.72  T=0.50 s (18.0 files/s, 700.0 lines/s)
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
Markdown                         5             47              0            155
YAML                             4             34              1            113
-------------------------------------------------------------------------------
SUM:                             9             81              1            268
-------------------------------------------------------------------------------

```

* cloc - Lines of code
```
$ cloc.exe include/gruppe32/ src/App.cpp src/IO.cpp src/main.cpp src/Valid.cpp src/DB.cpp src/Terminal.cpp
      11 text files.
      11 unique files.
       1 file ignored.

github.com/AlDanial/cloc v 1.72  T=0.50 s (22.0 files/s, 2574.0 lines/s)
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C++                              6            122             10            721
C/C++ Header                     5            105             77            252
-------------------------------------------------------------------------------
SUM:                            11            227             87            973
-------------------------------------------------------------------------------
```

* sloc - lines of code
```
$ sloc include/gruppe32/ src/ test/ --details --format cli-table  --keys todo,comment,source,total
┌───────────────────────────────┬───────┬─────────┬────────┬──────────┐
│ Path                          │ To Do │ Comment │ Source │ Physical │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ include\gruppe32\App.hpp      │ 0     │ 5       │ 40     │ 61       │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ include\gruppe32\DB.hpp       │ 0     │ 10      │ 88     │ 128      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ include\gruppe32\IO.hpp       │ 0     │ 48      │ 52     │ 117      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ include\gruppe32\Terminal.hpp │ 0     │ 2       │ 62     │ 81       │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ include\gruppe32\Valid.hpp    │ 0     │ 16      │ 19     │ 47       │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src\App.cpp                   │ 0     │ 9       │ 127    │ 153      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src\DB.cpp                    │ 0     │ 0       │ 1      │ 1        │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src\IO.cpp                    │ 1     │ 6       │ 137    │ 156      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src\ListTool2b.cpp            │ 0     │ 410     │ 392    │ 668      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src\Terminal.cpp              │ 0     │ 4       │ 381    │ 449      │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src\Valid.cpp                 │ 0     │ 1       │ 61     │ 75       │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ src\main.cpp                  │ 0     │ 0       │ 15     │ 19       │
├───────────────────────────────┼───────┼─────────┼────────┼──────────┤
│ test\test_Valid.cpp           │ 0     │ 1       │ 68     │ 79       │
└───────────────────────────────┴───────┴─────────┴────────┴──────────┘
```


### Sak2: Fordeling av App::funksjoner

**Halvor**

* printspillereAll 
* printspillerbyname
* printspillerbynumber
* printidretterall
* printidretterbyname
* Legg inn tetstdata i context
* Add support for choosing context with command-line args, or just default.

**Jonas**

* Last inn spilllere.dta
* last inn idretter.dta automatisk inn i context
* Skriv ut spiller.dta fra context til fil.
* skrit ut idretter.dta fra context til fil.
* Lag 4 skriv/les fra fil funksjoner som bruker ikke har tilgang til, men sysystemet bruker til å automatisk lese inn i context.
* 


### Til neste møte
* Evaluer dokumentasjonsdekning.
