# C data Dictionary (CdD) 📚

This is an implementation of a dictionary or associative array data structure in C. It uses an open-addressed hash table to store key-value pairs.

## Table of Contents

* [License](#license)
* [Description](#description)
    * [Features](#features)
* [Building](#building)
    * [Prerequisites](#prerequisites)
    * [Instllation](#installation)

## License

MIT License

> Copyright (c) 2024 Paul Stone
>
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all
> copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
> SOFTWARE.

## Description

*CdD* is a dictionary data structure implemented in C, designed to facilitate quick access and management of key-value pairs. Leveraging a hash table under the hood, *CdD* offers constant-time complexity for lookups, insertions, and deletions, making it an ideal choice for applications that require fast data retrieval. 

It's designed to work seamlessly on *\*nix* operating systems, including Linux and Unix. While *CdD* is not explicitly limited to these platforms, it has been developed and tested primarily in these environments.

### Features

- 1️⃣ **Framework for Custom Data Handling**: *CdD* provides a skeleton framework that requires users to define their own functions for handling the data stored in the dictionary. This allows for maximum flexibility and customization, enabling users to tailor the dictionary’s behavior to their specific application needs

- 2️⃣ **Fast Performance**: Utilizing a hash table under the hood, *CdD* provides constant-time complexity for lookups, insertions, and deletions, making it an ideal choice for applications that demand quick data retrieval

- 3️⃣ **Memory Management**: While *CdD* efficiently manages its internal memory allocation and deallocation, users are responsible for implementing their own memory allocation and deallocation functions for the data types they store. Properly managing memory in these functions is crucial to prevent memory leaks


## Building

### Prerequisites

 To install and use *CdD*, you'll need the following:
 
 - A C compiler (e.g., GCC or Clang)
 - GNU Make utility
 - Git (for cloning the repository)

### Installation

 Follow these steps to install and set up *CdD* on your system:
 
 - 1️⃣ **Clone the repository**:
 
 ```bash
 git clone https://github.com/paul-green-stone/CdD.git
 ```
 
 - 2️⃣ **Navigate to the project directory**:
 
 ```bash
 cd CdD
 ```
 
 - 3️⃣ **Build the libraries**:
 
Run make to compile the *CdD* library. This will generate both static and dynamic versions:

```bash
make
```

The make command will create the following libraries:

* `libCdD.a`: Static library
* `libCdD.so` or `libCdD.dylib`: Dynamic (shared) library

- **Include the header file**:

In your C project, include the `dictionary.h` header file to access the *CdD* API:

```C
#include "dictionary.h"
```

- **Link against the library**:

When compiling your project, link against the *CdD* library. If you're using the static library, link against `libCdD.a`. For the dynamic library, link against `libCdD.so` or `libCdD.dylib`. For example:

- Static library:

```bash
gcc -o your_program your_program.c /path/to/CdD/CdD.a
```