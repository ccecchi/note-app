#ifndef NOTE_NOTEAPP_H
#define NOTE_NOTEAPP_H


#include <vector>
#include <algorithm>
#include <stdexcept>
#include "Note.h"
#include "Collection.h"

class NoteApp : public Observer {
public:
    NoteApp();

    void newNote(const std::string &noteName, const std::string &text, Collection &coll);

    void newNote(const std::string &noteName, const std::string &text);

    void newCollection(const std::string &name);

    void addToImportant(const std::shared_ptr<Note> &note);

    void removeFromImportant(const std::shared_ptr<Note> &note);

    void deleteCollection(const std::string &collectionName);

    void deleteNote(std::shared_ptr<Note> &note);

    void moveNote(std::shared_ptr<Note> note, const std::string &collectionName);

    std::shared_ptr<Note> searchNote(const std::string &name) const;

    std::vector<std::string> getCollectionsNames() const;

    void update(const std::string &collectionName) override;

private:
    Collection importantNotes;
    std::vector<Collection> collections;
    std::vector<int> notesPerCollection;

};


#endif //NOTE_NOTEAPP_H