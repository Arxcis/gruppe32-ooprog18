# Prosjekt i Ooprog - våren 2018


[TOC]

### Windows instruksjoner
#### 1. Legge inn CMake-modulen i Visual Studio

_NOTE: Sørg for å ha Visual Studio 2017 15.4 eller nyere_

1. åpne _Visual Studio Installer_
    (Fra _Visual Studio_, velg: **Tools->Get Tools And Features...**)
2. Klikk på Boksen **Desktop development with C++**.
3. Under menyen i venstre kollone navngitt **Desktop development with C++**, sjekk av modulen **Visual C++ Tools for CMake**.
4. Klikk **Modify** for å kjøre installasjonen av CMake-modulen.

_Etter installasjonen vil du se en ny fane "CMake" dukke opp i Visual Studio._

#### 2. Bygg og kjør

1. Hent prosjektet fra bitbucket
```shell
git clone git@bitbucket.org:jonasjso/gruppe32-ooprog18.git
```

2. Åpne Visual Studio
3. Velg **File->Open->CMake**
4. I mappen `./gruppe32-ooprog18`, velg _CMakeLists.txt_, så **Open**
    _CMake vil nå generere filene som trengs for å bygge._
5. Velg hva som skal bygges og kjøres: **Select Startup Item** og **Start**.

Du får valgene **gruppe32.exe**, **gruppe32.exe seed**, og **gruppe32.exe test**.
_Disse brukes for å velge kommandolinjeargument du vil kjøre med_

* **gruppe32.exe** - (ingen kommandolinjeargument) kjører programmet på vanlig vis, dvs. leser inn dataer fra `./data/read-write/`

* **gruppe32.exe seed** - vil fylle inn programmet med testdatene spessifisert i oppgaven , dvs. leser inn dataer fra `./data/read/`. _OBS dette vil altså overskrive dataene som tidligere er skrevet ut når programmet lukkes_.

* **gruppe32.exe test** - vil fylle inn programmet med hardkodet data (i grunnen kun for bruk unner testing av for vår egen del). _OBS dette vil altså overskrive dataene som tidligere er skrevet ut når programmet lukkes_.

_NOTE: Om det skulle være nødvendig å kjøre programmet fra kommandolinja manuelt, kan du finne gruppe32.exe ved å velge `CMake->Cache->Open Cache Folder->gruppe32`_

### Linux instruksjoner


* Skjekk hvilken CMake og Clang++ du har installert

    ```bash
    cmake --version
    clang++ --version
    ```

*NOTE: Om du har CMake 3.8 eller nyere og Clang++ 4.0 eller nyere installert, så kan du hoppe direkte til punkt 3.*


#### 1. Installer CMake v3.11


* Avinstaller eksisterende CMake installasjon.
    ```bash
    sudo apt-get remove --purge cmake
    ```

* Last ned nyeste CMake fra https://cmake.org/download/ Eller last ned igjennom commandline

    ```bash
    mkdir ~/temp # lag en temp-mappe
    cd ~/temp

    wget https://cmake.org/files/v3.11/cmake-3.11.0-Linux-x86_64.tar.gz # hent cmake binaries
    ```

* Installer CMake på systemet, slik at du kan kjøre det fra kommandolinjen.

  ```bash
  tar -xzvf cmake-3.11.0-Linux-x86_64.tar.gz
  cd ~/temp/cmake-3.11.0-Linux-x86_64/

  cp -r ./bin     /usr/    # installer binaries
  cp -r ./doc     /usr/share/
  cp -r ./man     /usr/share/
  cp -r ./share   /usr/

  cmake --version         # test om installasjonen var velykket:
      cmake version 3.11.0

  rm -r ~/temp    # rydde opp/fjern temp
  ```

#### 2. Installer Clang++ 5.0 for c++17 support

```bash
sudo apt-get install clang++-5.0
```

#### 3. Bygg og kjør prosjektet

```bash
git clone git@bitbucket.org:jonasjso/gruppe32-ooprog18.git
cd ./gruppe32-ooprog18

mkdir build
cd build/
cmake .. -DCMAKE_CXX_COMPILER=clang++-5.0    
make
cd ../
./build/gruppe32

    **********************************************************************
    **  HOME
    **********************************************************************
    *   [S]piller        - Skriv informasjon om spillere
    *   [I]drett         - Skriv informasjon om idretter
    *   Termin[L]iste    - Skriv terminliste til skjerm eller fil
    *   Resultat[K]amp   - Skriv resultater til skjerm eller fil
    *   [T]abell         - Skriv tabeller til skjerm eller fil
    *   Lag[D]ata        - Skriv data om spillerene på et lag
    *   [N]y             - Ny Spiller, Idrett eller Divisjon/avdeling
    *   [F]jern          - Fjern Spiller, Idrett eller Divisjon/avdeling
    *   Lag[E]ndre       - Endre data om spillerene på et lag
    *   [R]esultat       - Les resultater fra fil
    *   [Q]uit           - Quit application
    **********************************************************************

```



### Mac instruksjoner

#### 1. Installer CMake.

*  Sørg for at **brew** er installert (https://brew.sh) og kjør
```bash
brew install cmake
```

#### 2. Bygg og kjør prosjekt
```bash
git clone git@bitbucket.org:jonasjso/gruppe32-ooprog18.git
cd ./gruppe32-ooprog18

mkdir build/
cd build/
cmake ..
make
cd ..
./build/gruppe32

    **********************************************************************
    **  HOME
    **********************************************************************
    *   [S]piller        - Skriv informasjon om spillere
    *   [I]drett         - Skriv informasjon om idretter
    *   Termin[L]iste    - Skriv terminliste til skjerm eller fil
    *   Resultat[K]amp   - Skriv resultater til skjerm eller fil
    *   [T]abell         - Skriv tabeller til skjerm eller fil
    *   Lag[D]ata        - Skriv data om spillerene på et lag
    *   [N]y             - Ny Spiller, Idrett eller Divisjon/avdeling
    *   [F]jern          - Fjern Spiller, Idrett eller Divisjon/avdeling
    *   Lag[E]ndre       - Endre data om spillerene på et lag
    *   [R]esultat       - Les resultater fra fil
    *   [Q]uit           - Quit application
    **********************************************************************

```

### Forklaring kommandolinjeargumenter

Programmet kan kjøres med 3 forskjellige kommandlinjeargumenter. Hvert av disse 3 argumentene åpner programmet i 3 ulike tilstander (internt navngitt som contexter).

* **./build/gruppe32** - (ingen kommandolinjeargument) kjører programmet på vanlig vis, dvs. leser inn dataer fra ./data/read-write/

* **./build/gruppe32 file** - samme som over

* **./build/gruppe32 seed** - vil fylle inn programmet med testdatene spessifisert i oppgaven , dvs. leser inn dataer fra `./data/read/`. _OBS dette vil altså overskrive dataene som tidligere er skrevet ut når programmet lukkes_.

* **./build/gruppe32 test** - vil fylle inn programmet med hardkodet data (i grunnen kun for bruk unner testing av for vår egen del). _OBS dette vil altså overskrive dataene som tidligere er skrevet ut når programmet lukkes_.



### Andre dokumenter
* Dokumentasjonskatalog - [document/](document/)
* Bemerkninger - [document/bemerkninger.md](document/bemerkninger.md)
* Kontaktinformasjon - [document/contact.md](document/contact.md)
* Referanseliste - [document/reference.md](document/reference.md)
* Progress report - https://hackmd.io/s/S1aMvBVPz
* Progress report edit - https://hackmd.io/KwFgRuIAwgtAJgQwBz1iYBjAbLRIQBGWbAMwFNhzSxhDlzCg
