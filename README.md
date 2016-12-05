#sudoku
As a learning exercise

[![Build Status](https://travis-ci.org/uael/sudoku.svg?branch=master)](https://travis-ci.org/uael/sudoku)

##Installation
**binary**
```bash
$ make && sudo make install
```
**Python 2.7 extension**
######deps
- python-dev
```bash
$ python setup.py build_ext --inplace --user
```

##Usage
**binary**
```bash
$ sudoku

sudoku - as a learning exercise.
   solve <...>: solve and print a full 9*9 puzzle
```
**Python 2.7**
```bash
$ python sudoku.py easy.txt
```