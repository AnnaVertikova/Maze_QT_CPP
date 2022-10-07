# Maze

Implementation of the Maze and Cave generator, Maze solving project.
This is a team educational project developed by me in a company of @tprobius and another student at School 21.

My part was:
- implementation of file parser
- implementation of controller as a part of MVC pattern
- full coverage of the project with Google test


## Here are some requirements we were given for this task:

## Implementation of the Maze project

Implement a Maze program that can generate and render perfect mazes and caves:
- The program must be developed in C++ language of C++17 standard
- Follow the Google style
- The program must be built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, tests. Installation directory could be arbitrary, except the building one
- GUI implementation, based on any GUI library with API for C++17: Qt, SFML, GTK+, Nanogui, Nngui, etc.
- The program has a button to load the maze from a file of particular format

## Generation of a perfect maze

Add the ability to automatically generate a perfect maze. \
A maze is considered perfect if it is possible to get from each point to any other point in exactly one way.
- You must generate the maze according to **Eller's algorithm**
- The generated maze must not have isolations and loops
- Prepare full coverage of the perfect maze generation module with unit-tests
- The user enters only the dimensionality of the maze: the number of rows and columns
- The generated maze must be saved in the file of particular format.

## Solving the maze

Add the ability to show the solution to _any_ maze currently shown on the screen:
- The user sets the starting and ending points
- Full coverage of the maze solving module with unit-tests

## Cave Generation

Add cave generation using a cellular automaton:
- The user selects the file that describes the cave according to the particular format.
- Use a separate window or tab in the user interface to display the caves
- The user sets the limits for "birth" and "death" of a cell, as well as the chance for the starting initialization of the cell
- There should be a step-by-step mode for rendering the results of the algorithm in two variants:
    - Pressing the next step button will lead to rendering the next iteration of the algorithm
    - Pressing the automatic work button starts rendering iterations of the algorithm with a frequency of 1 step in `N` milliseconds, where the number of milliseconds `N` is set through a special field in the user interface
- Full coverage of the cave generation module with unit-tests
# 3D_Viewer_QT_CPP
