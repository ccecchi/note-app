#include "NoteApp.h"

void NoteApp::newNote(const std::string &name, const std::string &text, Collection &coll) {
    std::shared_ptr<Note> note(new Note(name, text));
    coll.addNote(note);
}

void NoteApp::newNote(const std::string &name, const std::string &text) {
    std::shared_ptr<Note> note(new Note(name, text));
    auto it = collections.begin();
    it->addNote(note);
}

void NoteApp::newCollection(const std::string &name) {
    Collection coll(name);
    collections.push_back(coll);
    notesPerCollection.push_back(0);
}

void NoteApp::addToImportant(const std::shared_ptr<Note> &note) {
    if (importantNotes.searchNote(note->getName()))
        std::cout << "Gia importante";
    importantNotes.addNote(note);
}

std::shared_ptr<Note> NoteApp::searchNote(const std::string &name) {
    for (auto c: collections) {
        if (c.searchNote(name))
            return c.searchNote(name);
    }
    return nullptr;
}

void NoteApp::moveNote(std::shared_ptr<Note> note, const std::string &collectionName) {
    for (auto c: collections) {
        if (c.searchNote(note->getName())) {
            if (c.getName() == collectionName)
                std::cout << "Gia nella collezione";
            c.deleteNote(note);
            break;
        }
    }
    for (auto c: collections) {
        if (c.getName() == collectionName)
            c.addNote(note);
    }
}

void NoteApp::deleteNote(std::shared_ptr<Note> &note) {
    if (note->isLocked()) {
        std::cout << "Nota bloccata";
        return;
    }
    for (auto c: collections) {
        if (c.searchNote(note->getName()))
            c.deleteNote(note);
    }
    importantNotes.deleteNote(note);
}

void NoteApp::deleteCollection(const std::string &collectionName) {
    if (collectionName == importantNotes.getName() || collections[0].getName() == collectionName)
        std::cout << "Non puoi";
    auto it = std::find_if(collections.begin(), collections.end(), [&collectionName](Collection c) {
        return c.getName() == collectionName;
    });
    if (it == collections.end())
        return;

    auto notesNames = it->getTitles();
    for (auto &s: notesNames) {
        auto note = importantNotes.searchNote(s);
        if (note)
            importantNotes.deleteNote(note);
    }

    collections.erase(it);

    int index = std::distance(collections.begin(), it) + 1;
    notesPerCollection.erase(notesPerCollection.begin() + index);
}


void NoteApp::update(const std::string &collectionName) {
    if (collectionName == importantNotes.getName()) {
        notesPerCollection[0] = importantNotes.getNoteCount();
        return;
    }

    auto it = std::find_if(collections.begin(), collections.end(), [&collectionName](Collection c) {
        return c.getName() == collectionName;
    });
    if (it == collections.end())
        return;

    int index = std::distance(collections.begin(), it) + 1;
    notesPerCollection[index] = it->getNoteCount();
}

std::vector<std::string> NoteApp::getCollectionsNames() const {
    std::vector<std::string> titles;
    titles.reserve(collections.size());
    for (auto &c: collections) {
        titles.push_back(c.getName());
    }
    return titles;
}
