# CPP Tutorial Examples

A set of examples on my path to learn C++.

## Introduction

The goal is to include all the example code proposed by Google's Gemini AI to teach me C++.\
The examples are enabled/disabled at compile time using prepocessor #defines. For example, `#define _TEMPLATES_ 1` turn on Templates examples.
Everything, including the CMakeLists.txt files, was generated with the help of the AI.

## Setup 

Checkout repository.
```console
git clone <url>
```

## Building

```console
cmake -Bbuild -G 'Ninja Multi-Config'    // necesary to support Release and Debug build
cmake --build build/ --config Debug      // for binary Release build
cmake --build build/ --config Release    // for binary Debug build
```

## Contributing
Share and contribute with Pull requests

## License

This project itself is licensed under the [MIT License](https://opensource.org/licenses/MIT).