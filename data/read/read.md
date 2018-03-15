## Read-only files

* There can 0 or many files in this folder
* These files are created by users as input to the application when creating new `Divisjon` objects during run-time.
* format of the file names are like this:
    - divisjon-\<divisjonname\>.yml

* An example of the file format is documented in:
    - document/format-divsjon.yml

* These files are used to seed the divsjon objekts
* Example: `divisjon-eliteserien-2018.yml`.
* Once the files are read into the program, the data from them will be stored in the `read-write/idrettene.yml` file.