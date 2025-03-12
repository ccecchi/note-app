#ifndef NOTE_COLLECTION_H
#define NOTE_COLLECTION_H


#include <string>
#include <vector>
#include "Note.h"

class Collection{
public:
    explicit Collection(const std::string& name): name(name){}

    void addNote(const Note &note){
        notes.push_back(note);
    }

    void showCollection(){
        std::cout << name << ":" << std::endl;
        for(auto note:notes)
           std::cout<< "-" << note.getName() << std::endl;
    }
    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        Collection::name = name;
    }

    const std::vector<Note> &getNotes() const {
        return notes;
    }

    void setNotes(const std::vector<Note> &notes) {
        Collection::notes = notes;
    }

private:
    std::string name;
    std::vector<Note> notes;
};


#endif //NOTE_COLLECTION_H
