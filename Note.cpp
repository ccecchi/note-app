//
// Created by carol on 11/03/2025.
//

#include "Note.h"

void Note::setName(const std::string &name) {
    if (!locked)
        this->name = name;
    else
        std::cout << "Nota Bloccata";
}

void Note::setText(const std::string &text) {
    if (!locked)
        this->text = text;
    else
        std::cout << "Nota Bloccata";
}

