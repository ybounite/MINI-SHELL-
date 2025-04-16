
# Libft 42

Libft is a project at 42 School that requires you to implement a library of standard C functions. The goal is to re-create commonly used functions from <string.h>, <ctype.h>, <stdlib.h>, and <unistd.h> while also adding additional utility functions.

## Requirements
 * A Unix-based operating system (Linux/MacOS)
 * C programming language

## Setup
Clone the repository :
```
  git clone https://github.com/BouhcineAmezouar7/Libft.git
  cd Libft
```

Compile the project:
```
 make
```
This will generate the libft.a static library.

## Usage
Using Libft in Your Project

Include libft.h in your project and link the library:
```
#include "libft.h"

int main()
{
    char *str = ft_strdup("Hello, Libft!");
    ft_putstr_fd(str, 1);
    free(str);
    return 0;
}
```

Compile and run:
```
gcc -Wall -Wextra -Werror main.c libft.a -o test_libft
./test_libft
```

# Function Categories

* Libc Functions: Reimplementation of standard functions like memset, bzero, memcpy, strdup, etc.

* String Manipulation: Custom string-handling functions like ft_substr, ft_strjoin, ft_split, etc.

* Memory Management: Functions like ft_calloc and ft_realloc.

* Linked List Functions: Utility functions for linked lists such as ft_lstnew, ft_lstadd_front, ft_lstsize, etc.


## Features
* Custom implementations of standard C functions.

* Additional helper functions to aid in C programming.

* Supports linked list operations.

