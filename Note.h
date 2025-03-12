
#ifndef NOTE_NOTE_H
#define NOTE_NOTE_H


#include <string>
#include "Collection.h"

class Note {
public:
    explicit Note(const std::string &name,const std::string &text): name(name),text(text){}

    void addToCollection(Collection& collection){
        collection.addNote(this);
    }
    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        Note::name = name;
    }

    const std::string &getText() const {
        return text;
    }

    void setText(const std::string &text) {
        Note::text = text;
    }

private:
    std::string name;
    std::string text = " ";
};


#endif //NOTE_NOTE_H
