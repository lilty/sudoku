# sudoku
As a learning exercise

[![Build Status](https://travis-ci.org/lilty/sudoku.svg?branch=master)](https://travis-ci.org/lilty/sudoku)

**Installation**

```bash
$ make && sudo make install
```

**Usage**

```bash
$ sudoku

sudoku - as a learning exercise.
   generate: generate and print a full 9*9 grid
   puzzle:   generate and print a full 9*9 puzzle
   
$ sudoku generate
 7  4  2  8  3  1  5  6  9
 8  3  1  5  6  9  7  4  2
 5  6  9  7  4  2  8  3  1
 4  7  8  2  1  3  6  9  5
 2  1  3  6  9  5  4  7  8
 6  9  5  4  7  8  2  1  3
 3  2  7  1  8  4  9  5  6
 1  8  4  9  5  6  3  2  7
 9  5  6  3  2  7  1  8  4

$ sudoku puzzle
       9        8        4 
    7  8                   
    2              5  7    
    1              2  4    
       7  2     6  3       
 2        3                
       1  8  5             
 8           6        9  1 
    6           1     5    
                           
 1  3  9  5  7  8  6  2  4 
 5  7  8  6  2  4  1  3  9 
 4  2  6  1  3  9  5  7  8 
 6  1  3  9  8  5  2  4  7 
 9  4  7  2  1  6  3  8  5 
 2  8  5  3  4  7  9  1  6 
 7  9  1  8  5  2  4  6  3 
 8  5  2  4  6  3  7  9  1 
 3  6  4  7  9  1  8  5  2 
 
$ sudoku puzzle 5
 3  8  5  6  9  1  7  2  4
 6  9  1  7  2     3  8  5
 7  2  4  3  8  5  6  9  1
 8  3  6  5     9  2  4
 5  1  9  2  4  7  8  3  6
 2  4  7  8  3  6  5  1  9
 9  5  3  1  6  8  4  7  2
 1  6     4  7  2  9     3
 4  7  2  9  5  3  1  6  8

 3  8  5  6  9  1  7  2  4
 6  9  1  7  2  4  3  8  5
 7  2  4  3  8  5  6  9  1
 8  3  6  5  1  9  2  4  7
 5  1  9  2  4  7  8  3  6
 2  4  7  8  3  6  5  1  9
 9  5  3  1  6  8  4  7  2
 1  6  8  4  7  2  9  5  3
 4  7  2  9  5  3  1  6  8
```