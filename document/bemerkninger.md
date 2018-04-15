## Bemerkninger

* En student som ikke var med i gruppe32 gjorde en commit. Dette var fordi vi spurte om han kunne teste at prosjektet kjørte på Linux. Han måtte gjøre noen nødvendige endringer for at det skulle gå bra. Disse endringene fikk han lov til å pushe fra sin egen maskin. Committen det er snakk om kan du finne her --> https://bitbucket.org/account/signin/?next=/jonasjso/gruppe32-ooprog18/commits/4c2c6a0bf39480338f7d5a910e5928bf7e8df033

### Egne vurderinger

#### 1. Navneendring DivAvd -> Divisjon
Vi navngir klassen  for å tydeliggjøre klassens bruksområde.

#### 2. Namespacing av Listtool og egne moduler
Vi velger å sette ListTool, samt egne moduler inn i egne *namespaces* for tydeligere sepparering av modulær kode.

#### 3. Om Dynamiske arrayer (vectorer)
Vi gjør om de fleste statiske arryene til dynamiske arrayer(std::vector):
 * divisjon.lagene,
 * resultat.hjemmescoringer
 * resultat.bortescoringer
 * idrett.divisjonene
 * lag.spillerene

En god årsak til dette er at dette er en enkel måte å spare minnnebruk og spesielt filbruk. Vi trenger ikke å lagre tomme skuffer på fil eller i memory om de ikker er tatt i bruk.

For å tydeligjøre grunnen til denne avgjørelsen så vil jeg nå presentere et eksempel:

La oss si at det ligger 2 lag i systemet, lagene Brann og Ålesund. I tillegg ligger det et resultat etter at de spilte mot hverandre. Stillingen ble 4-2 til Brann.

Hvor mye minne tar de 3 arrayene `uint spillerID[50]`, `uint hjemmemål[50]`, `uint bortemål[50]`?

```cpp
arraySize = sizeof(brann.spillerID)   // 50 * 4 byte = 200 byte
           +sizeof(ål esund.spillerID) // 50 * 4 byte = 200 byte
           +sizeof(resultatBrannÅlesund.hjemmemål); // 50 * 4 byte = 200 byte
           +sizeof(resultatBrannÅlesund.bortemål); // 50 * 4 byte = 200 byte

std::cout << arraySize << " byte";   // 800 byte
```

**Hjemmemål og Bortemål** - Er arrayer som teller opp antall mål hver spiller har scoret i en kamp. De fleste skuffene av de 50 er 0 mål etter en kamp. Håndballkamper er kanskje de eneste typene kamper som tar i bruk en betydelig del av disse arrayene. Mye minne blir kastet bort på skuffer som har verdien 0.

**SpillerID** - Alt etter hvilken idrett så ligger de fleste lag på mellom 3-30 spillere. Er blir altså mye av plassen også sløst bort på å ta vare på verdien 0. Skuffer som ikke er i bruk.

Vi ønsker å skifte ut med dynamiske arrayer i stedet. Det vil også føre til en logisk endring. I stedet for å ta vare på tellere for hver spiller sine mål i en kamp, så tar vi vare på indekser til spillere som har scoret. En spiller som scorer 2 ganger, vil få indeksen sin ført opp to ganger. I de fleste tilfeller vil dette føre til en drastisk reduksjon i minnebruk.

La oss ta for oss vårt lille eksempel igjen. Hvordan ser minnebruken ut nå?
For å regne ut minnebruk så må vi annta at Brann sin spillerstall består av 15 spillere, og Ålesund sin spillerstall er på 20 spillere.

For å gjenta, så ble stillingen 4 -2.

```cpp
vectorsize = sizeof(brann.spillerID)   // 15spillere * 4 byte = 60 byte
            +sizeof(ålesund.spillerID) // 20spillere * 4 byte = 80 byte
            +sizeof(resultatKamp1.hjemmemål); // 4mål * 4 byte = 16 byte
            +sizeof(resultatKamp2.bortemål);  // 2mål * 4 byte = 8 byte
std::cout << vectorsize << " byte";         // 144 byte
```

Vi har altså reduser minnebruken med 656 byte eller 82%.
Merk deg at dersom neste kamp ender med 0-0, så vil minnebruken med array versjonen øke med 400 byte for hver kamp, men vectorversjonen vil øke med 0 byte i en 0-0 kamp, (om en ser på disse 3 arrayen isolert sett).


#### 4. Bruke GUID på spillere i Resultat objektene.
Vi vurderer det hensiktsmessig å bruke den GUID-en til spillere for å markere hvem som har scoret hvilke mål i en kamp. Vi vurderte en stund å bruke lagindeksen til spilleren, men dette kan bli vanskelig å håndtere over tid.

Hva om spilleren bytter indeks i laget, foreksempel får et nytt draktnummer? Hva om spilleren bytter klubb? Skal alle resultater da også slettes?


#### 5. Nøstet datastruktur på fil
Vi observerer at datastrukturen er ganske nøstet. Et eksempel er om vi ønsker å få tak i hvilken spiller som scoret det første målet i en kamp:
```cpp
uint spillerIDFørsteMåletIEnkamp = idrettene[0].divisjonene[0]
                                               .terminliste
                                               .hjemmelag[0]
                                               .bortelag[0]
                                               .resultat
                                               .hjemmescoringer[0];

```

Vi ønsker å bevare denne nøstingen i filformatet. Vi ønsker også at det skal være enkelt å lese og forstå det som ligger på fil. Det en del standard filformater der ute for dette.

JSON vurderer vi som for vanskelig å parse. Det har mye syntax (verbose), og blir litt for generisk. Det at vi ikke kan lese linje for linje gjør det også vanskeligere å parse JSON.

YAML kan representere det samme som JSON, men har en mye enklere syntax å parse dersom skriver så enkel YAML som mulig.
I tillegg kan YAML i vårt tilfelle leses linje for linje som key-value par.

Om vi hadde snekret sammen en egen datastruktur, så hadde vi uansett endt opp med noe som ligner på en key-value store. Derfor så er steget ganske lite over til YAML.

Om vi bruker YAML så får vi også fordeler med at det er mange andre verktøy og systemer som støtter YAML formatet, og det er enkelt å konvertere YAML over til andre formater.

Det er også en bonus å lære seg standarder som blir mye brukt i profesjonell sammenheng.

#### 6. Menyer som tar imot navn
Vi har valgt å la menyer som tar imot navn, gjøre et oppslag på substrengen <navn\>. Et søk kan derfor returnere flere treff, og vil skrive ut alle treff som matcher substrengen.

#### 7. Legg til ny divisjon
Navnet på den nye divisjon spesifiseres øverst i filen `./data/read/<divisjonfilnavn>.yml`, og IKKE fra kommandolinjen. Grunnen til dette er at det virker mest naturlig å skrive navnet på divisjonen du ønsker å legge til i selve filen, siden du uansett må skrive all annen data som hører til den divisjonen.

**Eksempel**
```

*********************************************************
**  HOME -> Info spiller(e)
*********************************************************
*   A      - Skriv Alle Spillerne
*   B      - Back to last menu
*   <nr>   - Skriv spiller med <nr>
*   Q      - Quit the application
*   <navn> - Skriv spiller med <navn>
*********************************************************
-> ar
---------------------------------------------------------
Spiller som inneholder "ar":

Spiller funnet!
   Gary Newman
   - Nummer: 2
   - Adresse: Orlando, Florida, USA

Spiller funnet!
   Kari Nordmann
   - Nummer: 5
   - Adresse: Trondheim, Norway
```

### C++17 features tatt i bruk

#### 1. Multiple return values/ struct unpacking

```cpp
const auto [key, command] = IO::readCommand(mainCommands);
```

#### 2. Nested namespaces

```cpp
namespace gruppe32::App
```


#### 3. If scoped variable initializer

```cpp

if (auto cmdID = menyFJERN(); cmdID == CMD_BACK)
{
    break;
}
else if (cmdID == CMD_QUIT)
{
    return;
}
```

#### 4. std::string_view
Bruker sdt::string_view til å lese inn fra fil. Her kan vi drive å jobbe på den strengen som ble lest fra fil, uten å gjøre dyrebare kopier inn i temp-strenger. Dette er spesielt nyttig i validering av filformat. std::string_view gjør at vi kan se igjennom hele stringen som kommer fra fil, og validere at strengen er korrekt, før vi faktisk begynner å kopiere data fra strengen og inn i den interne datastrukturen.

#### 5. std::filesystem (Ble vurdert men forkastet)
Denne standard-modulen har støtte i clang og gcc, men ikke i Visual Studio c++17 per 15.03.2018. Vi valgte derfor å skygge unna å bruke std::filesystem
