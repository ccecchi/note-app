cmake_minimum_required(VERSION 3.26)
project(note)

set(CMAKE_CXX_STANDARD 17)

add_library(note STATIC
        Note.cpp
        Note.h
        Collection.cpp
        Collection.h
        NoteApp.cpp
        NoteApp.h
        Observer.h
        Subject.h
)
