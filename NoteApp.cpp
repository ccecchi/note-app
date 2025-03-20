#include "NoteApp.h"

std::shared_ptr<Note> NoteApp::searchNote(const std::string &name) {
    for(auto c: collections){
        if(c.searchNote(name) != nullptr)
            return c.searchNote(name);
    }
    return baseCollection.searchNote(name);
}

void NoteApp::moveNote(std::shared_ptr<Note> &note, const std::string &name) {
    for(auto c:collections){
        if(c.searchNote(note->getName()) != nullptr){
            c.deleteNote(note);
            break;
        }
    }
    if(baseCollection.searchNote(note->getName()) != nullptr)
        baseCollection.deleteNote(note);

    for(auto c:collections){
        if(c.getName() == name)
            c.addNote(note);
    }
    if(baseCollection.getName() == name)
        baseCollection.addNote(note);
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




