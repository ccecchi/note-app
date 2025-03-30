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

    void newNote(const std::string &noteName, const std::string &text);

    void newNote(const std::string &noteName, const std::string &text, const std::string &collectionName);

    void newCollection(const std::string &name);

    void addToImportant(const std::string &name);

    void removeFromImportant(const std::string &note);

    std::shared_ptr<Note> searchNote(const std::string &name) const;

    std::shared_ptr<Collection> searchCollection(const std::string &name) const;

    void moveNote(std::string &noteName, const std::string &collectionName);

    void deleteNote(const std::string &name);

    void deleteCollection(const std::string &collectionName);

    std::vector<std::string> getCollectionsNames() const;

    void update(const std::string &collectionName) override;

private:
    Collection importantNotes;
    std::vector<Collection> collections;
    std::vector<int> notesPerCollection;

};


#endif //NOTE_NOTEAPP_H