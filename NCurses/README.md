# CPP Terminal Interface (TUI) Examples

A set of examples of Terminal User Interfaces (TUI) written in C++.

## Introduction

The goal is to place characters in the console window to create a User Interface.  
The approaches utilized in `NCursesMain.cpp` are:
* Windows Console API (windows.h)
* Linux (ANSI escape sequences)
* Multiplatform ([NCurses](https://invisible-island.net/ncurses/) library) predominantly used on Unix-like operating systems such
as Linux, macOS, and various BSD derivatives.

Also I included a set of examples taken from [NCurses Programming HowTo](https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/):  
* 3-SimplePrintwExample
* 4-SimpleScanwExample
* 5-SimpleAttributesExample
* 6-ChgatUsageExample
* 7-WindowBorderExample
* 8-WindowBorderExample2
* 9-ColorsExample
* 10-SimpleKeyUsageExample
* 11-SimpleKeyMouseUsageExample
* 12-TemporarilyLeavingCursesModeExample
* 13-ACSVariablesExample

## Setup 

Checkout repository.
```console
git clone <url>
```

## Building

```console
cmake -Bbuild
cmake --build build/
```

## Contributing

Share and contribute with Pull requests

## License

This project itself is licensed under the [MIT License](https://opensource.org/licenses/MIT).