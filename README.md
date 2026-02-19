[![Build & test](https://github.com/przemek83/sqlite-browser/actions/workflows/buld-and-test.yml/badge.svg)](https://github.com/przemek83/sqlite-browser/actions/workflows/buld-and-test.yml)
[![CodeQL](https://github.com/przemek83/sqlite-browser/actions/workflows/codeql.yml/badge.svg)](https://github.com/przemek83/sqlite-browser/actions/workflows/codeql.yml)
[![codecov](https://codecov.io/github/przemek83/sqlite-browser/graph/badge.svg?token=K1SR2JA727)](https://codecov.io/github/przemek83/sqlite-browser)

[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=przemek83_sqlite-browser&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=przemek83_sqlite-browser)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=przemek83_sqlite-browser&metric=bugs)](https://sonarcloud.io/summary/new_code?id=przemek83_sqlite-browser)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=przemek83_sqlite-browser&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=przemek83_sqlite-browser)
[![Coverage](https://sonarcloud.io/api/project_badges/measure?project=przemek83_sqlite-browser&metric=coverage)](https://sonarcloud.io/summary/new_code?id=przemek83_sqlite-browser)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=przemek83_sqlite-browser&metric=duplicated_lines_density)](https://sonarcloud.io/summary/new_code?id=przemek83_sqlite-browser)

## Table of contents
- [Description](#description)
- [Getting Started](#getting-started)
   * [Prerequisites](#prerequisites)
   * [Building](#building)
- [Built with](#built-with)
- [Testing](#testing)
- [Licensing](#licensing)
- [Potential further improvements](#potential-further-improvements)

## Example screenshot  
![Alt text](Screenshot1.png?raw=true "")
![Alt text](Screenshot2.png?raw=true "")

## Description
Small tool for the creation and edition of SQLite database files. Created originally as a coding assignment in one of recruitment processes.

## Getting Started
This section describes briefly how to setup the environment and build the project.

### Prerequisites
Qt in version 6.5 or greater, C++ compiler with C++17 support as a minimum and CMake 3.16+. 

### Building
Clone and use CMake directly or via any IDE supporting it. CMake should:
- configure everything automatically,
- compile and create binaries.

As a result of compilation, binary for simulations and binary for testing should be created.

## Built with
| Tool |  Windows | Ubuntu |
| --- | --- | --- |
| OS version | 10 22H2 | 24.04 |
| GCC | 13.1.0 | 13.2.0 |
| CMake | 3.30.2 | 3.28.3 |
| Git | 2.46.0 | 2.43.0 |
| Qt | 6.5.2 | 6.5.2 |
| Qt Creator | 10.0.2 | 10.0.2 |
| VS Code | 1.92.0 | 1.95.3 |

## Testing
For testing purposes, the QtTest framework is used. Build the project first. Make sure that the `sqlite-browser-tests` target is built. Modern IDEs supporting CMake also support running tests with monitoring of failures. But in case you would like to run it manually, go to the `build/tests` directory, where the⁣ binary `sqlite-browser-tests` should be available. Launching it should produce the following output on Linux:
Example run:
```
$ ./sqlite-browser-tests
********* Start testing of DatabaseConfigTest *********
Config: Using QtTest library 6.5.2, Qt 6.5.2 (x86_64-little_endian-lp64 shared (dynamic) release build; by GCC 10.3.1 20210422 (Red Hat 10.3.1-1)), ubuntu 24.04
PASS   : DatabaseConfigTest::initTestCase()
PASS   : DatabaseConfigTest::testTableName()
PASS   : DatabaseConfigTest::testCreateTableSql()
PASS   : DatabaseConfigTest::testCheckTableSql()
PASS   : DatabaseConfigTest::testColumnNames()
PASS   : DatabaseConfigTest::testUserFriendlyColumnNames()
PASS   : DatabaseConfigTest::cleanupTestCase()
Totals: 7 passed, 0 failed, 0 skipped, 0 blacklisted, 1ms
********* Finished testing of DatabaseConfigTest *********

```
As an alternative, CTest can be used to run tests from the `build/tests` directory:
```
$ ctest
Test project <path>/sqlite-browser/build/tests
    Start 1: sqlite-browser-tests
1/1 Test #1: sqlite-browser-tests ..............   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
```

## Licensing
SQLite Browser is published under an MIT license.

The project uses the following software:
| Name | License | Home | Description |
| --- | --- | --- | --- |
| Qt | LGPLv3 | https://www.qt.io/| cross-platform application development framework |

## Potential further improvements
1) Make the creation and usage of database structures fully generic.  
2) Use a JSON file as a DB structure definition, which would fill the DatabaseConfig class.  
3) Fix problems with focus. There are still scenarios when the current item is set on table view, but a row is not selected. It results in the delete row action being active.  
