//
// Created by carol on 11/03/2025.
//

#include "Note.h"

void Note::setName(const std::string &name) {
    if (locked)
        throw std::logic_error("The note is locke!");
    this->name = name;
}

void Note::setText(const std::string &text) {
    if (locked)
        throw std::logic_error("The note is locke!");
    this->text = text;

}

