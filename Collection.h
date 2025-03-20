#ifndef NOTE_COLLECTION_H
#define NOTE_COLLECTION_H


#include <string>
#include <vector>
#include <memory>
#include "Note.h"

class Collection{
public:
    explicit Collection(const std::string& name): name(name){}

    void addNote(const std::shared_ptr<Note> note){
        notes.push_back(note);
    }
    std::shared_ptr<Note> searchNote(const std::string &name){
        for(auto n:notes){
            if(n->getName() == name)
                return n;
        }
        return nullptr;
    }

    void deleteNote(std::shared_ptr<Note> &note){
        int i = 0;
        for(auto n:notes){
            if(n == note){
                notes.erase(notes.begin() + i);
                return;
            }
            i++;
        }
    }
    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        Collection::name = name;
    }

private:
    std::string name;
    std::vector<std::shared_ptr<Note>> notes;
};


#endif //NOTE_COLLECTION_H
