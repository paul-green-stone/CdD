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
      - [Inserting Elements](#inserting-elements)
        - [Parameters](#parameters)
        - [Return Value](#return-value)
        - [Example Usage](#example-usage)
      - [Printing the Contents of the Dictionary](#printing-the-contents-of-the-dictionary)
        - [Parameters](#parameters-1)
        - [User-Defined `print` Function](#user-defined-print-function)
      - [Removing Values from the Dictionary](#removing-values-from-the-dictionary)
        - [Parameters](#parameters-2)
        - [Return Value](#return-value-1)
        - [Example Usage](#example-usage-1)
      - [Searching Values in the Dictionary](#searching-values-in-the-dictionary)
        - [Parameters](#parameters-3)
        - [Return Value](#return-value-2)
        - [Example Usage](#example-usage-2)
      - [Destroying the Dictionary](#destroying-the-dictionary)
        - [User-Defined `destroy` Function](#user-defined-destroy-function)
      - [Saving and Loading the Dictionary](#saving-and-loading-the-dictionary)
        - [`Dict_save`](#dict_save)
          - [Prameters](#prameters)
          - [User-Defned `save_data` Function](#user-defned-save_data-function)
        - [`Dict_load`](#dict_load)
          - [Parameters](#parameters-4)
          - [User-Defned `load_data` Function](#user-defned-load_data-function)
        - [Example Usage](#example-usage-3)
    - [Working with Complex Data](#working-with-complex-data)
      - [Command Line Interface (CLI) Programs](#command-line-interface-cli-programs)
        - [`radd`](#radd)

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

#### Inserting Elements

To insert a new key-value pair into the dictionary, use the `Dict_insert` function. This function associates a unique string key with a specified value.

```C
ssize_t Dict_insert(const char* key, void* value, Dict_t dict);
```

##### Parameters

- `key` - A pointer to a string that serves as a unique identifier for the value being inserted. This key must be unique within the dictionary; attempting to insert a value with a duplicate key will result in an error

- `value` - A pointer to the data you wish to store in the dictionary. This can point to any data type, but it is essential that the corresponding user-defined functions for handling this data type are properly implemented
  
- `dict` - A `Dict_t` structure representing the dictionary instance where the key-value pair will be inserted

##### Return Value

The `Dict_insert` function returns a non-negative value indicating the index in the internal storage where the value has been successfully inserted. If the insertion fails (for example, due to a duplicate key or insufficient memory), the function returns a negative value to indicate the error.

##### Example Usage

```C
int number_one = 1;

if ((Dict_insert("one", &number_one, dict)) >= 0) {
    printf("The element has been inserted successfully\n");
}
```

#### Printing the Contents of the Dictionary

To print the contents of the dictionary, use the `Dict_print` function. This function iterates through the key-value pairs stored in the dictionary and invokes the user-defined `print` function for each value.

```C
void Dict_print(const Dict_t dict);
```

##### Parameters

- `dict` - A `Dict_t` structure representing the dictionary instance whose contents you want to print

##### User-Defined `print` Function

When creating the dictionary using `Dict_new`, you must provide a function pointer for the `print` parameter. This function will be responsible for printing the values stored in the dictionary.

The signature of the `print` function should match the following:

```C
void (*print)(void* value);
```

Here, `value` is a pointer to the data stored in the dictionary. The print function should handle the appropriate casting and printing of the data based on its type.

```C
void how_to_print_INT(void* value) {
    printf("%d", *((int*) value));
}
```

In this example, we cast the `void*` pointer to an `int*` pointer and then dereference it to access the integer value.

Alternatively, you can define the `print` function to accept an `int*` directly:

```C
void how_to_print_INT(int* value) {
    printf("%d", *value);
}
```

In this case, when passing the function pointer to `Dict_new`, you need to cast it explicitly:

```C
Dict_t dict = Dict_new(10, (void (*)(void*)) how_to_print_INT, ...);
```

Both approaches are valid, and the choice depends on your preference and coding style.

```C
Dict_t dict = Dict_new(10, how_to_print_INT, destroy_int, save_int, load_int);

/* Insert some integer values into the dictionary */

Dict_print(dict);
```

#### Removing Values from the Dictionary

To remove a key-value pair from the dictionary, use the `Dict_remove` function. This function takes a `key` as input and removes the associated value from the dictionary. Here goes its prototype:

```C
void* Dict_remove(const char* key, Dict_t dict);
```

##### Parameters

- `key` - A pointer to a string representing the unique key of the key-value pair you want to remove from the dictionary

- `dict` - A `Dict_t` structure representing the dictionary instance from which you want to remove the value

##### Return Value

The `Dict_remove` function returns a pointer to the data associated with the removed key-value pair. If the specified key is not found in the dictionary, the function returns `NULL`.

❗❗❗ **Important**: It is crucial to properly deallocate the memory of the returned value if it was dynamically allocated. Use the user-defined destroy function provided to `Dict_new` to handle the deallocation process and prevent memory leaks.

##### Example Usage

```C
Dict_t dict = Dict_new(10, print_int, destroy_int, save_int, load_int);

/* Insert some integer values into the dictionary */

void* removed_value = Dict_remove("key_to_remove", dict);

if (removed_value != NULL) {
    /* Deallocate the removed value */
    destroy_int(removed_value);
}
else {
    printf("Key not found in the dictionary.\n");
}
```

In this example, we remove a key-value pair from the dictionary using `Dict_remove`. If the key is found, we obtain a pointer to the removed value and deallocate it using the `destroy_int` function, which is the user-defined destroy function provided to `Dict_new`.

#### Searching Values in the Dictionary

To retrieve a value stored in the dictionary under a specified key, use the `Dict_lookup` function. This function allows you to find the data associated with a given key:

```C
void* Dict_lookup(const char* key, Dict_t dict);
```

##### Parameters

- `key` - A pointer to a string representing the unique key associated with the value you want to retrieve from the dictionary.

- `dict` - A `Dict_t` structure representing the dictionary instance from which you want to look up the value.

##### Return Value

The `Dict_lookup` function returns a pointer to the data associated with the specified key. If the key is found, the function returns a pointer to the corresponding value. If there is no such key in the dictionary, the function returns `NULL`.

##### Example Usage

```C
Dict_t dict = Dict_new(10, print_int, destroy_int, save_int, load_int);

/* Insert some integer values into the dictionary */

int* value = (int*) Dict_lookup("key_to_lookup", dict);

if (value != NULL) {
    printf("Found value: %d\n", *value);
} else {
    printf("Key not found in the dictionary.\n");
}

```

#### Destroying the Dictionary

To safely remove a dictionary and free all associated memory, use the `Dict_destroy` function. This function will delete all elements from the dictionary by calling the user-defined destroy function for each element stored, and it will also free the memory allocated for the dictionary itself. The prototype is the following:

```C
void Dict_destroy(Dict_t dict);
```

##### User-Defined `destroy` Function

When creating a dictionary using `Dict_new`, you must specify a destroy function that will handle the deallocation of the data stored in the dictionary.

- **For Statically Allocated Data**: If you do not intend to store values in a file and/or load them back, you can specify `NULL` for the `destroy` function. However, this means you must ensure that the data does not require manual deallocation.

- **For Dynamically Allocated Data**: If you are dynamically allocating memory for integers (or any other data type) and storing them in the dictionary, you should specify `free` as the ` destroy` function. This allows the dictionary to properly deallocate the memory when the dictionary is destroyed.

❗❗❗ **Important**: If you create a dictionary that contains statically allocated data but plan to save data into a file and load it back, you will need to specify a destroy function that can handle the deallocation of dynamically allocated memory created during the loading process. This ensures that all memory is managed correctly, even if the original data was statically allocated.

#### Saving and Loading the Dictionary

##### `Dict_save`

To save the contents of a dictionary to a file, use the `Dict_save` function. This function writes the key-value pairs stored in the dictionary to a specified file in binary format.

```C
int Dict_save(const Dict_t dict, const char* filename);
```

###### Prameters

- `dict` - A `Dict_t` structure representing the dictionary instance you want to save

- `filename` - A string specifying the name of the file where the dictionary contents will be written

###### User-Defned `save_data` Function

The `Dict_save` function is responsible for writing the keys to the file. It uses the user-defined `save_data` function provided to `Dict_new` to handle the writing of individual values associated with each key. Here's an example of a `save_data` function for integers:

```C
int how_to_save_INT(void* data, FILE* file) {

    /* It's a good practice to check return values, but I just omitted it for simplicity :) */ 

    fwrite(data, sizeof(int), 1, file);

    return 0;
}
```

This function writes an integer value to the file using `fwrite`. It is important to note that the `save_data` function only handles the value, while the `Dict_save` function takes care of writing the corresponding key.

##### `Dict_load`

To load a dictionary from a file, use the `Dict_load` function. This function reads the key-value pairs from a file and reconstructs the dictionary in memory.

```C
Dict_t Dict_load(const char* filename, void (*print)(void* value), void (*destroy)(void* value), int (*save_data)(void* data, FILE* file), int (*load_data)(void** data, FILE* file));
```

###### Parameters

- `filename` - A string specifying the name of the file from which the dictionary contents will be loaded

- `print`, `destroy`, `save_data` - Function pointers for the corresponding operations, as described in the `Dict_new` function

- `load_data` - A function pointer to a user-defined function that loads data from the file. The function should match the following signature:
  
```C
int (*load_data)(void** data, FILE* file);
```

###### User-Defned `load_data` Function

The `load_data` function is responsible for allocating memory and loading the value from the file. The key is read by the `Dict_load` function itself.

It should also return `EXIT_SUCCESS` (0) on success, or `EXIT_FAILURE` (non-zero) if an error occurs. Here’s an example for integers:

```C
int how_to_read_INT(void** data, FILE* file) {

    *data = malloc(sizeof(int));

    if (*data = NULL) {
      return EXIT_FAILURE;
    }

    /* do not forget to check the return value */
    fread(*data, sizeof(int), 1, file);

    return EXIT_SUCCESS;
}
```

##### Example Usage

```C
Dict_t dict = Dict_new(10, print_int, destroy_int, how_to_write_INT, how_to_load_INT);

/* Insert some integer values into the dictionary */

Dict_save(dict, "dictionary.bin");

/* ... some time later ... */

Dict_t loaded_dict = Dict_load("dictionary.bin", print_int, destroy_int, how_to_save_INT, how_to_load_INT);
```

In this example, we save the dictionary to a file named "dictionary.bin" using `Dict_save`. Later, we load the dictionary from the same file using `Dict_load`, specifying the appropriate user-defined functions for handling the data type (in this case, integers).

### Working with Complex Data

In the source code, you will find usage cases (under `test/Records/`) that demonstrate how to manage records using the dictionary. These records function like a fake database, allowing you to store and manipulate information about individuals with different access levels.

#### Command Line Interface (CLI) Programs

Several command line interface (CLI) programs are provided to interact with the improvised database:

##### `radd`

Adds a new record to the database. This command allows you to input the details of a person and store them in the dictionary.

![Usage Statement]("test/Records/screenshots/radd-usage.png")