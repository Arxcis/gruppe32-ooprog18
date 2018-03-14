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


### Sak2: Fordeling av App::funksjoner

**Halvor**
    - printspillereAll
    - printspillerbyname
    - printspillerbynumber
    - printidretterall
    - printidretterbyname
    - Legg inn tetstdata i context
    - Add support for choosing context with command-line args, or just default.

**Jonas**
    - Last inn spilllere.dta
    - last inn idretter.dta automatisk inn i context
    - Skriv ut spiller.dta fra context til fil.
    - skrit ut idretter.dta fra context til fil.
    - Lag 4 skriv/les fra fil funksjoner som bruker ikke har tilgang til, men sysystemet bruker til å automatisk lese inn i context.
    - 

### Til neste møte
* Evaluer dokumentasjonsdekning.
