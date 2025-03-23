#ifndef NOTE_NOTEAPP_H
#define NOTE_NOTEAPP_H


#include <vector>
#include "Note.h"
#include "Collection.h"

class NoteApp : public Observer{
public:
    NoteApp(): important("Important"){
        notesPerCollection.push_back(0);
        newCollection("Home");
    }

    void newNote(const std::string &name,const std::string &text,Collection &coll){
        std::shared_ptr<Note> note(new Note(name,text));
        coll.addNote(note);
    }
    void newNote(const std::string &name,const std::string &text){
        std::shared_ptr<Note> note(new Note(name,text));
        auto it = collections.begin();
        it->addNote(note);
    }

    void newCollection(const std::string &name){
        Collection coll(name);
        collections.push_back(coll);
        notesPerCollection.push_back(0);
    }

    void addToImportant(const std::shared_ptr<Note> &note){
        if(important.searchNote(note->getName()))
            std::cout << "Gia importante";
        important.addNote(note);
    }

    bool deleteCollection(const std::string &name);
    void deleteNote(std::shared_ptr<Note> &note);

    void moveNote(std::shared_ptr<Note> &note, const std::string &name);

    std::shared_ptr<Note> searchNote(const std::string &name);

    void lockNote(std::shared_ptr<Note> &note){
        note->setLocked(true);
    }
    void unlockNote(std::shared_ptr<Note> &note){
        note->setLocked(false);
    }

    int collectionIndex(std::string &name);


private:
    Collection important;
    std::vector<Collection> collections;
    std::vector<int> notesPerCollection;

};


#endif //NOTE_NOTEAPP_H