#ifndef NOTE_NOTEAPP_H
#define NOTE_NOTEAPP_H


#include <vector>
#include "Note.h"
#include "Collection.h"

class NoteApp {
public:
    NoteApp(): baseCollection("Home"){}

    void newNote(const std::string &name,const std::string &text,Collection &coll);
    void newNote(const std::string &name,const std::string &text);

    void newCollection(const std::string &name);

    std::string searchNote(const std::string &name);

private:
    Collection baseCollection;
    std::vector<Collection> collections;
    std::vector<std::weak_ptr<Note>> important;
};


#endif //NOTE_NOTEAPP_H