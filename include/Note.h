#ifndef NOTE_NOTE_H
#define NOTE_NOTE_H


#include <string>
#include <stdexcept>

class Note {
public:
    explicit Note(const std::string &name, const std::string &text) : name(name), text(text) {}

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name);

    const std::string &getText() const {
        return text;
    }

    void setText(const std::string &text);

    bool isLocked() const {
        return locked;
    }

    void setLocked(bool locked) {
        this->locked = locked;
    }

    bool isImportant() const {
        return important;
    }

    void setImportant(bool important){
        this->important = important;
    }

private:
    std::string name;
    std::string text = "";
    bool locked = false;
    bool important = false;
};


#endif //NOTE_NOTE_H
