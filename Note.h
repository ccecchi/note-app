
#ifndef NOTE_NOTE_H
#define NOTE_NOTE_H


#include <string>

class Note {
public:
    explicit Note(std::string &name,std::string &text): name(name),text(text){}

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
