cmake_minimum_required(VERSION 3.26)
project(note)

set(CMAKE_CXX_STANDARD 17)

add_executable(note main.cpp
        Note.cpp
        Note.h
        Collection.cpp
        Collection.h
        NoteApp.cpp
        NoteApp.h
        Observer.h
        Subject.h
)
