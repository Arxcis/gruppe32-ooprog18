## Read-write files

* The first time the program runs on machine 2 files will be generated in this folder.
* It should never be more or less than 2 files in this folder after the first run.

* The 2 files in this folder should be named:
    - idrettene.yml
    - spillerene.yml

* An example of the file formats is documented in:
    - document/format-idretttene.yml
    - document/format-spillerene.yml

* They are all read when the program loads.
* They are all written to when the program shuts down.
* These files represent the complete persistent state of the program.
 
