#include "NoteApp.h"

NoteApp::NoteApp() : importantNotes("Important") {
    notesPerCollection.push_back(0);
    importantNotes.registerObserver(this);
    newCollection("Home");
}

void NoteApp::newNote(const std::string &noteName, const std::string &text) {
    if (searchNote(noteName))
        throw std::invalid_argument("This name has already been used!");
    auto note = std::make_shared<Note>(noteName, text);
    collections[0].addNote(note);
}


void NoteApp::newNote(const std::string &noteName, const std::string &text, const std::string &collectionName) {
    if (searchNote(noteName))
        throw std::invalid_argument("This name has already been used!");
    auto it = std::find_if(collections.begin(), collections.end(), [&collectionName](const Collection &c) {
        return c.getName() == collectionName;
    });
    if (it == collections.end())
        throw std::invalid_argument("This collection doesn't exist!");

    auto note = std::make_shared<Note>(noteName, text);
    collections[it - collections.begin()].addNote(note);
}

void NoteApp::newNote(const std::string &noteName, const std::string &text) {
    if (searchNote(noteName))
        throw std::invalid_argument("This name has already been used!");
    std::shared_ptr<Note> note(new Note(noteName, text));
    collections[0].addNote(note);
}

void NoteApp::newCollection(const std::string &name) {
    auto titles = getCollectionsNames();
    auto it = std::find(titles.begin(), titles.end(), name);
    if (it != titles.end())
        throw std::invalid_argument("Collection with this name already exist!");
    Collection coll(name);
    coll.registerObserver(this);
    collections.push_back(coll);
    notesPerCollection.push_back(0);

}


void NoteApp::addToImportant(const std::string &name) {
    if (importantNotes.searchNote(name))
        throw std::invalid_argument("Note is already important");
    importantNotes.addNote(searchNote(name));
}


void NoteApp::removeFromImportant(const std::string &name) {
    if (!importantNotes.searchNote(name))
        throw std::invalid_argument("The note is not important!");
    importantNotes.deleteNote(searchNote(name));
}


std::shared_ptr<Note> NoteApp::searchNote(const std::string &name) const {
    for (const auto &c: collections) {
        if (c.searchNote(name))
            return c.searchNote(name);
    }
    return nullptr;
}


std::shared_ptr<Collection> NoteApp::searchCollection(const std::string &name) const {
    if (name == importantNotes.getName())
        return std::make_shared<Collection>(importantNotes);
    for (auto &c : collections){
        if(c.getName() == name)
            return std::make_shared<Collection>(c);
    }
    return nullptr;
}

void NoteApp::moveNote(std::shared_ptr<Note> note, const std::string &collectionName) {
    for (auto c: collections) {
        if (c.searchNote(note->getName())) {
            if (c.getName() == collectionName)
                throw std::invalid_argument("The note is already in the collection!");
            c.deleteNote(note);
            break;
        }
    }
    for (auto c: collections) {
        if (c.getName() == collectionName)
            c.addNote(note);
    }
}


void NoteApp::deleteNote(const std::string &name) {
    if (searchNote(name)->isLocked())
        throw std::invalid_argument("The note is locked!");

    for (auto c: collections) {
        if (c.searchNote(name))
            c.deleteNote(c.searchNote(name));
    }
    importantNotes.deleteNote(importantNotes.searchNote(name));
}


void NoteApp::deleteCollection(const std::string &collectionName) {
    if (collectionName == importantNotes.getName() || collections[0].getName() == collectionName)
        throw std::invalid_argument("This collection can't be deleted!");
    auto it = std::find_if(collections.begin(), collections.end(), [&collectionName](Collection c) {
        return c.getName() == collectionName;
    });
    if (it == collections.end())
        throw std::invalid_argument("This collection doesn't exist!");

    auto notesNames = it->getTitles();
    for (auto &s: notesNames) {
        if (importantNotes.searchNote(s))
            importantNotes.deleteNote(importantNotes.searchNote(s));
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
