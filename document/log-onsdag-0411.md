# Log onsdag 11.04.18

#### Saksliste

1. Kompabilitet med Linux(Jonas og Jone adventures)
2. Oversikt hva gjenstår.
3. Hva gjør vi i dag.


#### 1. Linux kompabilitet

* Cmake måtte hentes manuelt fra cmake.com
* apt-get installerer bare 3.5.
* Jone måke binaryes rett inn /usr/local/bin
* For å kompilere med g++ på linux,
```shell
apt-get install g++-7
cmake .. -DCMAKE_CXX_COMPILER=g++-7
```

```shell
apt-get install clang-5.0
cmake .. -DCMAKE_CXX_COMPILER=clang-5.0
```


#### 2. Oversikt hva gjenstår

* Fullfør lesResultatene() - halveis ferdig
* Fullfør leggTilDivisjon fra fil () - ingen ferdig
* Skriv manuelle tester for alt
* Skjekk at korrekt testdata ligger i prosjektet.
* Sørg for at prosjekt kompilerer på fagass-maskin.
* FERDIG!


#### 3. Hva skal vi gjøre i dag?

* Skriv manuelle tester

##### Test files
- [x] FromFiles
- [x] ToFiles
- [x] [I]drett - Skriv data om en/flere idretter
- [x] [S]piller - Skriv data om en/flere spillere
- [x] Termin[L]iste - 
- [x] Resultat[K]amp - Skriv (resultatet av) alle Kampene en gitt dato for en hel idrett eller en divisjon/avdeling til skjerm eller fil.
- [x] [T]abell -
- [x] Lag[D]ata
- [x] [N]y
- [x] [F]jern
- [ ] Lag[E]ndre - Legg til/fjern spillere fra lag
- [x] [R]esultat - Les resultat fra fil

