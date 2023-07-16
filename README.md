## Example screenshot  
![Alt text](Screenshot1.png?raw=true "")
![Alt text](Screenshot2.png?raw=true "")

## Description
Small tool for the creation and edition of SQLite DB files. Created originally as a coding assignment.

## Used tools and libs
| Tool |  Windows | Lubuntu |
| --- | --- | --- |
| OS version | 10 22H2 | 22.04 |
| GCC | 11.2.0 | ? |
| CMake | 3.25.0 | 3.25.0 |
| Git | 2.38.1 | 2.34.1 |
| Qt | 6.5.1 | ? |
| Qt Creator | 9.0.0 | 9.0.0 |
| VS Code | 1.80 | ? |

## Compilation and installation
Use CMake directly or any IDE supporting CMake projects. CMake **should**:
- configure everything automatically, 
- compile sqlite-browser and link binaries.  

This is, of course, a happy path... 

## Licensing
Tankble is published under an MIT license. 

## Potential further improvements
1) Make the creation and usage of database structures fully generic.  
2) Use a JSON file as a DB structure definition, which would fill the DatabaseConfig class.  
3) Fix problems with focus. There are still scenarios when the current item is set on table view, but a row is not selected. It results in the delete row action being active.  
