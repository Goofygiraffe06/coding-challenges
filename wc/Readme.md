# Building my very own `wc`

## Introduction

This project involved building a custom version of the Unix command line tool wc, named gwc. The Unix wc (word count) tool is a simple yet powerful utility that counts lines, words, characters, and bytes in text files. This project follows the Unix Philosophy of writing simple, modular tools that can be combined to perform complex tasks.
Motivation

The motivation behind this project was to deepen the understanding of Unix command line tools and the principles that make them effective. By recreating wc, the project demonstrates how simple utilities can be designed and implemented to handle text processing tasks efficiently.
Project Goals

   1. Implement Line, Word, and Character Counting: The primary goal was to implement functionalities to count lines, words, and characters in text files.
   2. Support Command Line Options: Support various command line options (-l, -w, -c) to count lines, words, and characters respectively.
   3. Default Option Handling: Provide default behavior to count lines, words, and characters if no specific option is provided.
   4. Standard Input Support: Implement the ability to read input from standard input if no file is specified.

## Implementation Details

The project was implemented in C using the argp library for command line argument parsing. The key features of the implementation include:

   1. Command Line Parsing: Utilized argp to handle command line options and arguments.
   2. File Processing: Implemented functions to open and process files, counting lines, words, and characters.
   3. Multibyte Support: Ensured correct counting of multibyte characters by using locale-aware functions.
   4. Standard Input Handling: Added functionality to read from standard input when no file is provided.

## Key Functions

   1. `count_file(FILE *file, int *lines, int *words, int *chars)`: Counts the lines, words, and characters in a given file.
   2. `parse_opt(int key, char *arg, struct argp_state *state)`: Parses command line options using argp.

## Usage


### Counting Lines:

```sh
gwc -l test.txt
```
Output:

```sh
7145 test.txt
```

### Counting Words:

```sh
gwc -w test.txt
```
Output:

```sh
58164 test.txt
```
### Counting Characters:

```sh
gwc -m test.txt
```

Output:

```sh
339292 test.txt
```
### Default Counting (Lines, Words, and Bytes):

```sh
gwc test.txt
```

Output:

```sh
7145 58164 342190 test.txt
```

### Reading from Standard Input:

```sh
cat test.txt | gwc -l
```

Output:

```sh
    7145
```
