## Read-only files

* There can 0 or many files in this folder
* These files are created by users.
* The user references these files with their filepath during run-time.
* The files is used to upload ekstra data to the program during run-time.

* format of the file-names are like this:
    - divisjon-\<divisjonname\>.yml  // can be many files
    - resultatene.yml                // only one file
    - seed-idrettene.yml  // file which is used to seed/reset the database
    - seed-spillerene.yml // ------------ // ----------------

* An example of the file format is documented in:
    - document/format-divsjon.yml
    - document/format-resultatene.yml

* These files are used to input data into the program during run/time.
* Example: `divisjon-eliteserien-2018.yml`.
* Once the files are read into the program, the data from them will be stored in the `read-write/idrettene.yml` file.