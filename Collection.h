#ifndef NOTE_COLLECTION_H
#define NOTE_COLLECTION_H


#include <string>
#include <vector>
#include "Note.h"

class Collection {
public:
    explicit Collection(std::string& name): name(name){}

private:
    std::string name;
    std::vector <Note> notes;
};


#endif //NOTE_COLLECTION_H
