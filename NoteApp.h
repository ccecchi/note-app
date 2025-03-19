#ifndef NOTE_NOTEAPP_H
#define NOTE_NOTEAPP_H


#include <vector>
#include "Note.h"
#include "Collection.h"

class NoteApp {
public:

private:
    Collection baseCollection;
    std::vector<Collection> collections;
    std::vector<std::weak_ptr<Note>> important;
};


#endif //NOTE_NOTEAPP_H