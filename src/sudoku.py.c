#include <Python.h>
#include "sudoku.h"

static PyObject *solve(PyObject *self, PyObject *args) {
  char *puzzle, solution[81];

  if (!PyArg_ParseTuple(args, "s", &puzzle)) {
    return NULL;
  }
  sudoku_solve(puzzle, solution, 2);

  return Py_BuildValue("s", solution);
}

static char solve_docs[] = "sudoku.solve(string puzzle)\n";

static PyMethodDef sudoku_funcs[] = {
  {"solve", solve, METH_VARARGS, solve_docs},
  { NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC initsudoku(void) {
  Py_InitModule3("sudoku", sudoku_funcs, "Sudoku extension!");
}