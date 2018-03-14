## Bemerkninger

#### Egne vurderinger

1. Vi navngir klassen *DivAvd* -> *Divisjon* for å tydeliggjøre klassens bruksområde.

2. Vi velger å sette ListTool, samt egne moduler inn i egne *namespaces* for tydeligere sepparering av modulær kode.

3. Vi gjør om de statiske arryene i `Lag` og `Resultat` til dynamiske arrayer, primert for å spare minnnebruk og lagringsbruk.
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


#### C++17 features tatt i bruk

1. Multiple return values/ struct unpacking

```cpp
const auto [key, command] = IO::readCommand(mainCommands);
```

2. Nested namespaces

```cpp
namespace gruppe32::App
```


3. If scoped variable initializer

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
