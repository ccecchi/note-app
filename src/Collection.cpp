#include "Collection.h"

void Collection::addNote(const std::shared_ptr<Note> &note) {
    if (note) {
        notes.push_back(note);
        notify();
    }
}

bool Collection::deleteNote(const std::shared_ptr<Note> &note) {
    if (note->isLocked())
        return false;
    auto it = std::find(notes.begin(), notes.end(), note);
    if (it != notes.end()) {
        notes.erase(it);
        notify();
        return true;
    }
    return false;
}

bool Collection::deleteNote(int position) {
    if (position > notes.size())
        return false;
    auto it = notes.begin() + position - 1;
    if ((*it)->isLocked())
        return false;
    notes.erase(it);
    notify();
    return true;
}

bool Collection::deleteNote(const std::string &title) {
    auto it = std::find_if(notes.begin(), notes.end(), [&title](auto &n) {
        return n->getName() == title;
    });
    if (it == notes.end())
        return false;
    if((*it)->isLocked())
        return false;
    notes.erase(it);
    notify();
    return true;
}

std::vector<std::shared_ptr<Note>> Collection::searchNote(const std::string &s) const {
    std::vector<std::shared_ptr<Note>> vector;
    for (auto &n: notes) {
        if (n->getName().find(s) != std::string::npos)
            vector.push_back(n);
    }
    return vector;
}

std::vector<std::string> Collection::getTitles() const {
    std::vector<std::string> titles;
    titles.reserve(notes.size());
    for (auto &n: notes) {
        titles.push_back(n->getName());
    }
    return titles;
}
