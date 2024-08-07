# C data Dictionary (CdD) 📚

This is an implementation of a dictionary or associative array data structure in C. It uses an open-addressed hash table to store key-value pairs.

## Table of Contents

- [C data Dictionary (CdD) 📚](#c-data-dictionary-cdd-)
  - [Table of Contents](#table-of-contents)
  - [License](#license)
  - [Description](#description)
    - [Features](#features)
  - [Building](#building)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
  - [Usage](#usage)
    - [Data Structure](#data-structure)
      - [Components](#components)
      - [Encapsulation and Separation of Concerns](#encapsulation-and-separation-of-concerns)
    - [Working with Built-in Types](#working-with-built-in-types)
      - [Creating a Dictionary](#creating-a-dictionary)

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

- 4️⃣ **Include the header file**:

In your C project, include the `dictionary.h` header file to access the *CdD* API:

```C
#include "dictionary.h"
```

- 5️⃣ **Link against the library**:

When compiling your project, link against the *CdD* library. If you're using the static library, link against `libCdD.a`. For the dynamic library, link against `libCdD.so` or `libCdD.dylib`. For example:

- Static library:

```bash
gcc -o your_program your_program.c /path/to/CdD/CdD.a
```

- Dynamic library:
  
```bash
gcc -o your_program your_program.c -L=path/to/CdD -lCdD
```

Replace *path/to/CdD* with the actual path to the *CdD* project directory.

❗ **Note**: When using the dynamic library, ensure that the system can locate `libCdD.so` or `libCdD.dylib` at runtime. The library must be in a standard library location (e.g., */usr/lib*, */usr/local/lib*) or any other location known to the system. You can also specify the library path at runtime using the `-Wl,-rpath` option:

```bash
gcc -o your_program your_program.c -L/path/to/CdD -CdD -Wl,-rpath=/path/to/CdD
```

## Usage

### Data Structure

*CdD* represents a dictionary data using `dictionary` struct data type:

```C
static struct dictionary {
    
    size_t logical_size;
    size_t actual_size;
    
    void (*print)(void* data);
    void (*destroy)(void* data);
    int (*save_data)(void* data, FILE* file);
    int (*load_data)(void** data, FILE* file);
    
    struct mapping** mappings;
};
```

#### Components

- `logical_size` - This member indicates the capacity of the dictionary, representing the maximum number of key-value pairs that the dictionary can hold
- `actual_size` - This member tracks the current number of key-value pairs stored in the dictionary. It provides a real-time count of how many elements are present
- `print` - A pointer to a user-defined function that handles the printing of data items. This allows for customizable output formats when displaying the contents of the dictionary
- `destroy` -  A pointer to a user-defined function responsible for properly deallocating memory associated with data items. This is crucial for preventing memory leaks and ensuring efficient memory management
- `save_data` - A pointer to a user-defined function that facilitates saving a data item to a specified file. This enables persistence of data, allowing users to store their dictionary contents for later retrieval
- `load_data` - A pointer to a user-defined function that loads a data item from a specified file into the dictionary. This function aids in restoring previously saved data
- `mapping` - This member is an array of pointers to `mapping` structures, which represent the individual key-value pairs stored in the dictionary. Each mapping contains the necessary information to associate keys with their corresponding values

#### Encapsulation and Separation of Concerns

It is important to note that direct access to the fields of the `dictionary` structure is not permitted. The dictionary is implemented as a pointer to an incomplete type, meaning that the actual definition of the data structure resides in the implementation file. This design choice enforces encapsulation, preventing users from modifying the dictionary data directly.

You interact with the dictionary exclusively through the provided API, which exposes a well-defined interface for performing operations such as adding, retrieving, and managing key-value pairs. By adhering to the principle of separation of concerns, *CdD* ensures that the internal implementation details remain hidden, allowing you to focus on utilizing the dictionary without needing to understand its inner workings.

### Working with Built-in Types

#### Creating a Dictionary

Let's consider a scenario in which you need to store integer values under unique names (keys). To create a new instance of the dictionary, use the `Dict_new` function. It's prototype is the following:

```C
Dict_t Dict_new(size_t size, void (*print)(void* data), void (*destroy)(void* data), int (*save_data)(void* data, FILE* file), int (*load_data)(void** data, FILE* file))
```

❗❗❗ **Important**: Passing a negative number to `size` will result in an overflow, as the value will be cast to `size_t`, leading to an extremely large positive number. This may cause issues when allocating memory for the dictionary, potentially causing the program to crash or behave unexpectedly.

```C
Dict_t dict = NULL;

if ((dict = Dict_new(10, print_int, destroy_int, save_int, load_int)) == NULL) {
    fprintf(stderr, "Error has occured: %s\n", strerror(errno));

    return EXIT_FAILURE;
}
```

In this example, we create a dictionary with an initial capacity of 10 key-value pairs, specifically for storing integers. The function pointers `print_int`, `destroy_int`, `save_int`, and `load_int` should be user-defined functions that handle the respective operations for integers. We'll consider them in a short while.
