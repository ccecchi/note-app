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

std::shared_ptr<Note> NoteApp::searchNote(const std::string &name) {
    for(auto c: collections){
        if(c.searchNote(name) != nullptr)
            return c.searchNote(name);
    }
    return baseCollection.searchNote(name);
}

bool NoteApp::deleteCollection(const std::string &name) {
    int i = 0;
    for(auto c:collections){
        if(c.getName() == name){
            collections.erase(collections.begin() + i);
            return true;
        }
        i++;
    }
    return false;
}

void NoteApp::deleteNote(std::shared_ptr<Note> &note) {
    if(note->isLocked())
        std::cout<<"Nota bloccata";
    for(auto c:collections){
        if(c.searchNote(note->getName()) == note){
            c.deleteNote(note);
            return;
        }
    baseCollection.deleteNote(note);
    }
}