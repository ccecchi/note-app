#include "NoteApp.h"

void NoteApp::newNote(const std::string &name, const std::string &text, Collection &coll) {
    std::shared_ptr<Note> note(new Note(name,text));
    coll.addNote(note);
}

void NoteApp::newNote(const std::string &name, const std::string &text) {
    std::shared_ptr<Note> note(new Note(name,text));
    baseCollection.addNote(note);
}

void NoteApp::newCollection(const std::string &name) {
    Collection coll(name);
    collections.push_back(coll);
}
