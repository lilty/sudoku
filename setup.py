from distutils.core import setup, Extension

setup(
    name='PackageName',
    version='1.0',
    ext_modules=[Extension('sudoku', ['src/sudoku.c', 'src/sudoku.py.c'])]
)