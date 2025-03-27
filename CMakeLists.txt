cmake_minimum_required(VERSION 3.26)
project(note)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(note STATIC
        Note.cpp
        include/Note.h
        Collection.cpp
        include/Collection.h
        NoteApp.cpp
        include/NoteApp.h
        include/Observer.h
        include/Subject.h
)
