cmake_minimum_required(VERSION 3.26)
project(note)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(note STATIC
        src/Note.cpp
        include/Note.h
        src/Collection.cpp
        include/Collection.h
        src/NoteApp.cpp
        include/NoteApp.h
        include/Observer.h
        include/Subject.h
)
