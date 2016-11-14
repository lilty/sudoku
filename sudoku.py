import sys
import os

import time

try:
  from sudoku import solve
except ImportError:
  os.system("python setup.py build_ext --inplace --user")
  from sudoku import solve

nb_methodes=1

class SudokuError(Exception):
  pass

def resolution(puzzle, methode=0):
  puzzle = ''.join(puzzle)


def do_solve(puzzle):
  print "\nSolving..."
  a = time.time()
  ret = solve(puzzle)
  print "Solved in "+str(time.time() - a)+"s !\n"+puzzle+"\n"+ret
  return 0

def sudoku_main(args):
  if not args:
    raise SudokuError("todo: show help")
  if args[0] == '-h':
    if not args[1]:
      raise SudokuError("File argument or input puzzle is required")
    if not os.path.isfile(args[1]):
      a = time.time()
      solve(args[1])
      print "\nSolved in " + str(time.time() - a) + "s !"
      return 0
    puzzles = file(args[1]).read().strip().split("\n")
    a = time.time()
    for puzzle in puzzles:
      solve(puzzle)
    print "\nAll solved in " + str(time.time() - a) + "s !"
    return 0
  if not args[0]:
    raise SudokuError("File argument or input puzzle is required")
  if not os.path.isfile(args[0]):
    return do_solve(args[0])
  puzzles = file(args[0]).read().strip().split("\n")
  a = time.time()
  for puzzle in puzzles:
    do_solve(puzzle)
  print "\nAll solved in " + str(time.time() - a) + "s !"
  return 0

def main(args):
  try:
    return sudoku_main(args)
  except SudokuError, e:
    sys.stderr.write("sudoku: %s\n" % e)
    return 1

def script_main():
  return main(sys.argv[1:])

if __name__ == '__main__':
  sys.exit(script_main())
