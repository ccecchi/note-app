#ifndef NOTE_NOTEAPP_H
#define NOTE_NOTEAPP_H


#include <vector>
#include "Note.h"
#include "Collection.h"

class NoteApp {
public:
    NoteApp(): baseCollection("Home"){}

    void newNote(const std::string &name,const std::string &text,Collection &coll){
        std::shared_ptr<Note> note(new Note(name,text));
        coll.addNote(note);
    }
    void newNote(const std::string &name,const std::string &text){
        std::shared_ptr<Note> note(new Note(name,text));
        baseCollection.addNote(note);
    }

    void newCollection(const std::string &name){
        Collection coll(name);
        collections.push_back(coll);
    }

    void moveNote(std::shared_ptr<Note> &note, const std::string &name);

    bool deleteCollection(const std::string &name);
    void deleteNote(std::shared_ptr<Note> &note);

    std::shared_ptr<Note> searchNote(const std::string &name);

    void lockNote(std::shared_ptr<Note> &note){
        note->setLocked(true);
    }
    void unlockNote(std::shared_ptr<Note> &note){
        note->setLocked(false);
    }

private:
    Collection baseCollection;
    std::vector<Collection> collections;
    std::vector<std::weak_ptr<Note>> important;
};


#endif //NOTE_NOTEAPP_H