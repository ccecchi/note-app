#include "NoteApp.h"

std::shared_ptr<Note> NoteApp::searchNote(const std::string &name) {
    for(auto c: collections){
        if(c.searchNote(name))
            return c.searchNote(name);
    }
    return nullptr;
}

void NoteApp::moveNote(std::shared_ptr<Note> &note, const std::string &name) {
    for(auto c:collections){
        if(c.searchNote(note->getName())){
            if(c.getName() == name)
                std::cout << "Gia nella collezione";
            c.deleteNote(note);
            break;
        }
    }
    for(auto c:collections){
        if(c.getName() == name)
            c.addNote(note);
    }
}

void NoteApp::deleteNote(std::shared_ptr<Note> &note) {
    if(note->isLocked())
        std::cout<<"Nota bloccata";

    for(auto c:collections){
        if(c.searchNote(note->getName()))
            c.deleteNote(note);
    }
    important.deleteNote(note);
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



