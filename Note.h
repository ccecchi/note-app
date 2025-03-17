#ifndef NOTE_NOTE_H
#define NOTE_NOTE_H


#include <string>
#include <iostream>

class Note{
public:
    explicit Note(const std::string &name,const std::string &text,bool star): name(name),text(text){}

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        if(!locked)
            this->name = name;
        else
            std::cout<<"Nota Bloccata";
    }

    const std::string &getText() const {
        return text;
    }

    void setText(const std::string &text) {
        if(!locked)
            this->text = text;
        else
            std::cout<<"Nota Bloccata";
    }

    bool isLocked() const {
        return locked;
    }

    void setLocked(bool locked) {
        this->locked = locked;
    }


private:
    std::string name;
    std::string text = "";
    bool locked = false;
};


#endif //NOTE_NOTE_H
