#ifndef NOTE_NOTEAPP_H
#define NOTE_NOTEAPP_H


#include <vector>
#include "Note.h"
#include "Collection.h"

class NoteApp {
public:

private:
    std::vector<Note*> notes;
    std::vector<Collection*> collections;
};


#endif //NOTE_NOTEAPP_H
