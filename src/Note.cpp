#include "Note.h"

void Note::setName(const std::string &name) {
    if (locked)
        throw std::logic_error("The note is locked!");
    this->name = name;
}

void Note::setText(const std::string &text) {
    if (locked)
        throw std::logic_error("The note is locked!");
    this->text = text;
}

