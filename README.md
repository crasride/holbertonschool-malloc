<h1 align="center">C - malloc</h1>

### Concepts
For this project, we expect you to look at this concept:

* [[EYNTK] Writing your own dynamic allocation library](./EYNTK/README.md)

## Resources
**Read or watch:**

* [Hack the Virtual Memory: malloc, the heap & the program break](https://blog.holbertonschool.com/hack-the-virtual-memory-malloc-the-heap-the-program-break/)
* [Everything you need to know to write your own malloc](./Automatic_allocation.md)

**man or help:**

* `sbrk`
* `brk`
* `malloc`

**Learning Objectives**

At the end of this project, you are expected to be able to explain to anyone, without the help of Google:

### General

<details>
<summary>What is a program break:</summary>
</br>

The program break refers to the end of the data segment in a process's virtual memory address space. It marks the boundary between the dynamically allocated memory (`heap`) and the statically allocated memory (`data segment`). The program break is managed by the operating system kernel and can be adjusted to allocate or deallocate memory dynamically.

</details>

<details>
<summary>How to play with a program break in order to allocate memory dynamically:</summary>
</br>

The `brk()` and `sbrk()` system calls traditionally were used to manipulate the program break. 
However, modern systems and programming languages often use higher-level memory allocation functions like `malloc()` and `free()`.


</details>

<details>
<summary>How the glibc `malloc` and `free` functions work:</summary>
</br>

The GNU C Library `(glibc)` provides the `malloc()` and `free()` functions for dynamic memory allocation in C programs. `malloc()` is used to allocate a specified amount of memory on the heap, and `free()` is used to release previously allocated memory.

</details>

<details>
<summary> What is ASLR:</summary>
</br>

`ASLR` is a security feature that randomizes the memory addresses used by system components and processes, making it more difficult for attackers to predict the location of specific code or data. This helps to mitigate certain types of `security vulnerabilities`, such as buffer overflows.

</details>

<details>
<summary>What is memory alignment:</summary>
</br>

Memory alignment refers to the requirement that `data` be `stored` at particular memory `addresses`. It ensures that data is accessed `efficiently` by the `CPU`, especially when working with data types that require specific alignment, such as integers or floating-point numbers.

</details>

<details>
<summary>What is a memory page:</summary>
</br>

A memory page is a `fixed-length` contiguous block of virtual or physical memory used by the operating system. Pages are typically 4 KB in `size`, but this `can vary`. Memory pages are the basic unit of memory management and are used for tasks like `virtual memory mapping` and paging.

</details>

<details>
<summary>How to encapsulate the memory management in order to hide it from the user:</summary>
</br>
To hide memory management from the user, you can encapsulate it in `higher-level` abstractions. For example, you might define custom data `structures` or `classes` that handle memory allocation and deallocation internally. This encapsulation shields the user from the `low-level` details of memory management, providing a more user-friendly interface.

</details>

<details>
<summary>Note:</summary>
</br>

It's important to note that direct manipulation of the program break and the use of `sbrk()` are considered outdated, and modern memory management is typically done using `higher-level` abstractions like `malloc()` and `free()`. Additionally, in languages like C++, you may use features like smart pointers and classes to handle memory management automatically, reducing the risk of `memory `leaks and improving code safety.

</details>


### Requirements
### General

* Allowed editors: `vi, vim, emacs`
* All your files will be compiled on Ubuntu 14.04 LTS
* Your C programs and functions will be compiled with `gcc 4.8.4` using the flags `-Wall -Werror -Wextra and -pedantic`
* All your files should end with a new line
* A `README.md` file, at the root of the folder of the project, is mandatory
* Your code should use the `Betty` style. It will be checked using [betty-style.pl](https://github.com/hs-hq/Betty/blob/main/betty-style.pl) and [betty-doc.pl](https://github.com/hs-hq/Betty/blob/main/betty-doc.pl)
* You are not allowed to have more than 5 functions per file
* The prototypes of all your functions should be included in your header file called malloc.h
* Don’t forget to push your header files
* All your header files should be include guarded
* You are allowed to use `global` variables
* You are allowed to use `static` variables

### Betty Compliance

* All the C source files in your directory and subdirectories must [Betty-compliant](https://intranet.hbtn.io/rltoken/abbd1E1RWALmHC6flq9S5w)

### Allowed Functions and System Calls

* Unless specified otherwise, you are allowed to use the C standard library
* Of course, you’re not allowed to use the `malloc` family from the C library…

### Tests

* It is strongly advised to test your functions against real programs, like a shell, or your old projects for example.
* To do so, you can name your functions `malloc`, `free`, `realloc` and `calloc` (just like they’re name in the glibc), and compile them into a shared library that you would load when executing a program using {LD_LIBRARY_PATH} and `LD_PRELOAD`
* [Here’s a tutorial on how to do it](https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html)

## More Info

### Important
It is not required that your _malloc, free, calloc and realloc behave exactly like the glibc malloc, free, calloc and realloc:

* You are free to use any data structure that suits you as long as their purpose is well defined
* You are free to handle the heap as it suits you, as long as the returned pointers (for the functions that return a pointer) are aligned as required and that enough space is available
* You are free to extend the program break as it suits you, as long as it is extended by a multiple of the virtual memory page size, and as long as it is reduced when needed
* You decide of your implementation. During the correction, we will mainly focus on the strength and reliability of your functions, so make sure to handle big allocations :)

# Tasks

## [0. Naive malloc](./naive_malloc.c)

Read carefully the [concept page for this project](https://intranet.hbtn.io/concepts/891)

Build the naive malloc that is presented in the concept page.

* Prototype: `void *naive_malloc(size_t size);`
* Where size is the size needed to be allocated for the user
* Your function must return a pointer to the allocated memory that is suitably aligned for any kind of variable
* You naive malloc should be able to:
	* Allocate enough memory to store
		* A size_t as the chunk header
		*	The size requested as parameter
	* Allocate memory pages only

### Repo:

* GitHub repository: `holbertonschool-malloc`
* File: `naive_malloc.c`, `malloc.h`


## [1. malloc](./malloc.c)

Write you own `malloc` function that allocates space in the heap

* Prototype: `void *_malloc(size_t size);`
* Where `size` is the size needed to be allocated for the user
* Your function must return a pointer to the allocated memory that is suitably aligned for any kind of variable

### Repo:

* GitHub repository: `holbertonschool-malloc`
* File: `malloc.c`, `malloc.h`

## [2. free](./free.c)

Write you own free function that frees a memory space

* Prototype: `void _free(void *ptr);`
* Where `ptr` is a pointer to the memory space to be freed

### Repo:

* GitHub repository: `holbertonschool-malloc`
* File: `free.c`, `malloc.c`, `malloc.h`

## [3. calloc](./calloc.c)

Write you own malloc function that allocates space in the heap

* Prototype: `void *_calloc(size_t nmemb, size_t size);`
* Where `nmemb` is the number of elements in the array, and s`size` is the size of each element
* Your function must return a pointer to the allocated memory that is suitably aligned for any kind of variable

### Repo:

* GitHub repository: `holbertonschool-malloc`
* File: `calloc.c`,`free.c`, `malloc.c`, `malloc.h`

## [4. realloc](./realloc.c)

Write you own malloc function that allocates space in the heap

* Prototype: `void *_realloc(void *ptr, size_t size);`
* Where `ptr` is a pointer to the memory space to resize, and `size` is the new size needed to be allocated for the user
* Your function must return a pointer to the allocated memory that is suitably aligned for any kind of variable

### Repo:

* GitHub repository: `holbertonschool-malloc`
* File: `realloc.c`,`free.c`, `malloc.c`, `malloc.h`


## Authors

<sub>_You can contact me_ 📩
* Guenoel Andrieux [Github](https://github.com/guenoel)

<sub>_You can contact me_ 📩
* Jose Fernandez Armas [Github](https://github.com/crasride)


