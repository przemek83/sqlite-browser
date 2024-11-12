[![Build & test](https://github.com/przemek83/sqlite-browser/actions/workflows/buld-and-test.yml/badge.svg)](https://github.com/przemek83/sqlite-browser/actions/workflows/buld-and-test.yml)
[![codecov](https://codecov.io/github/przemek83/sqlite-browser/graph/badge.svg?token=K1SR2JA727)](https://codecov.io/github/przemek83/sqlite-browser)

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=przemek83_sqlite-browser&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=przemek83_sqlite-browser)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=przemek83_sqlite-browser&metric=bugs)](https://sonarcloud.io/summary/new_code?id=przemek83_sqlite-browser)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=przemek83_sqlite-browser&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=przemek83_sqlite-browser)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=przemek83_sqlite-browser&metric=coverage)](https://sonarcloud.io/summary/new_code?id=przemek83_sqlite-browser)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=przemek83_sqlite-browser&metric=duplicated_lines_density)](https://sonarcloud.io/summary/new_code?id=przemek83_sqlite-browser)

## Example screenshot  
![Alt text](Screenshot1.png?raw=true "")
![Alt text](Screenshot2.png?raw=true "")

## Description
Small tool for the creation and edition of SQLite DB files. Created originally as a coding assignment.

## Used tools and libs
| Tool |  Windows | Ubuntu |
| --- | --- | --- |
| OS version | 10 22H2 | 22.04 |
| GCC | 13.1.0 | 13.2.0 |
| CMake | 3.30.2 | 3.28.3 |
| Git | 2.46.0 | 2.43.0 |
| Qt | 6.5.2 | 6.5.2 |
| Qt Creator | 10.0.2 | 10.0.2 |
| VS Code | - | 1.94.2 |

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
