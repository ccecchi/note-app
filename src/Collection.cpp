#include "Collection.h"

void Collection::addNote(const std::shared_ptr<Note> &note) {
    if (note) {
        notes.push_back(note);
        notify();
    }
}

void Collection::deleteNote(const std::shared_ptr<Note> &note) {
    auto it = std::find(notes.begin(), notes.end(), note);
    if (it != notes.end()) {
        notes.erase(it);
        notify();
    }
}

std::shared_ptr<Note> Collection::searchNote(const std::string &name) const {
    for (auto n: notes) {
        if (n->getName() == name)
            return n;
    }
    return nullptr;
}

std::vector<std::string> Collection::getTitles() const {
    std::vector<std::string> titles;
    titles.reserve(notes.size());
    for (auto &n: notes) {
        titles.push_back(n->getName());
    }
    return titles;
}
