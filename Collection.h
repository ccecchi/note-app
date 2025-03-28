#ifndef NOTE_COLLECTION_H
#define NOTE_COLLECTION_H


#include <string>
#include <vector>
#include <list>
#include <memory>
#include "Note.h"
#include "Subject.h"

class Collection : public Subject{
public:
    explicit Collection(const std::string& name): name(name){}

    ~Collection() override{
        for(auto obs : observers)
            delete obs;
    }
    void registerObserver(Observer* o) override{
        observers.push_back(o);
    }
    void unregisterObserver(Observer* o) override{
        observers.remove(o);
    }
    void notify() override{
        for(auto obs : observers)
            obs->update(name);
    }

    void addNote(const std::shared_ptr<Note> note){
        notes.push_back(note);
        noteCount += 1;
        notify();
    }

    void deleteNote(std::shared_ptr<Note> &note){
        int i = 0;
        for(auto n:notes){
            if(n == note){
                notes.erase(notes.begin() + i);
                break;
            }
            i++;
        }
        noteCount -= 1;
        notify();
    }

    std::shared_ptr<Note> searchNote(const std::string &name){
        for(auto n:notes){
            if(n->getName() == name)
                return n;
        }
        return nullptr;
    }


    const std::string &getName() const {
        return name;
    }
    void setName(const std::string &name) {
        Collection::name = name;
    }

    int getNoteCount() const {
        return noteCount;
    }

private:
    std::string name;
    std::vector<std::shared_ptr<Note>> notes;
    int noteCount = 0;
    std::list<Observer*> observers;
};


#endif //NOTE_COLLECTION_H
