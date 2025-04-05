#ifndef NOTE_COLLECTION_H
#define NOTE_COLLECTION_H


#include <string>
#include <vector>
#include <list>
#include <memory>
#include <algorithm>
#include "Note.h"
#include "Subject.h"

class Collection : public Subject {
public:
    explicit Collection(const std::string &name) : name(name) {}

    void registerObserver(Observer *o) override {
        observers.push_back(o);
    }

    void unregisterObserver(Observer *o) override {
        observers.remove(o);
    }

    void notify() const override {
        for (auto obs: observers)
            obs->update(name);
    }

    void addNote(const std::shared_ptr<Note> &note);

    bool deleteNote(const std::shared_ptr<Note> &note);

    bool deleteNote(int position);

    std::shared_ptr<Note> searchNote(const std::string &noteName) const;
    bool deleteNote(const std::string &title);

    std::vector<std::string> getTitles() const;

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        Collection::name = name;
    }

    int getNoteCount() const {
        return notes.size();
    }

private:
    std::string name;
    std::vector<std::shared_ptr<Note>> notes;
    std::list<Observer *> observers;
};


#endif //NOTE_COLLECTION_H
