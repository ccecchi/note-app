#include "gtest/gtest.h"
#include "NoteApp.h"

TEST(NoteAppTest, TestNoteAppConstructor) {
    NoteApp n;
    auto titles = n.getCollectionsNames();
    ASSERT_EQ(titles.size(), 1);
    ASSERT_EQ(titles[0], "Home");
    auto npc = n.getNotesPerCollection();
    ASSERT_EQ(npc.size(), 2);
}


TEST(NoteAppTest, TestNewCollection) {
    NoteApp n;
    n.newCollection("name1");

    auto titles = n.getCollectionsNames();
    ASSERT_EQ(titles.size(), 2);
    ASSERT_EQ(titles[1], "name1");
    ASSERT_EQ(n.getNotesPerCollection().size(), 3);

    ASSERT_THROW(n.newCollection("name1"), std::invalid_argument);
}


TEST(NoteAppTest, TestNewNoteWithoutCollection) {
    NoteApp n;
    n.newNote("note1", "text1");
    auto note = n.searchNote("note1");

    ASSERT_NE(note, nullptr);
    ASSERT_EQ(note->getName(), "note1");
    ASSERT_EQ(note->getText(), "text1");
    ASSERT_EQ(n.getNotesPerCollection()[1], 1);

    ASSERT_THROW(n.newNote("note1", "text2"), std::invalid_argument);
}


TEST(NoteAppTest, TestNewNoteWithCollection) {
    NoteApp n;
    n.newCollection("coll1");
    n.newNote("note1", "text1", "coll1");
    auto note = n.searchNote("note1");

    ASSERT_NE(note, nullptr);
    ASSERT_EQ(note->getName(), "note1");
    ASSERT_EQ(note->getText(), "text1");
    ASSERT_EQ(n.getNotesPerCollection()[2], 1);

    ASSERT_THROW(n.newNote("note1", "text2", "coll1"), std::invalid_argument);
    ASSERT_THROW(n.newNote("note2", "text2", "COLL"), std::invalid_argument);
}


TEST(NoteAppTest, TestAddToImportant) {
    NoteApp n;
    n.newNote("note1", "text1");
    n.addToImportant("note1");
    auto imp = n.searchCollection("Important");
    auto coll = n.searchCollection("Home");

    ASSERT_EQ(n.getNotesPerCollection()[0], 1);
    ASSERT_EQ(n.getNotesPerCollection()[1], 1);
    ASSERT_EQ(coll->getTitles()[0], imp->getTitles()[0]);
    ASSERT_TRUE(n.searchNote("note1")->isImportant());
    ASSERT_EQ(coll->getImportantNotes().size(), 1);

    ASSERT_THROW(n.addToImportant("note1"), std::invalid_argument);
    ASSERT_THROW(n.addToImportant("NOTE"), std::invalid_argument);
}

TEST(NoteAppTest, TestRemoveFromImportant) {
    NoteApp n;
    n.newNote("note1", "text1");
    auto coll = n.searchCollection("Home");
    n.addToImportant("note1");
    n.removeFromImportant("note1");

    ASSERT_EQ(n.getNotesPerCollection()[0], 0);
    ASSERT_EQ(n.getNotesPerCollection()[1], 1);
    ASSERT_FALSE(n.searchNote("note1")->isLocked());
    ASSERT_EQ(coll->getImportantNotes().size(), 0);

    ASSERT_THROW(n.removeFromImportant("note1"), std::invalid_argument);
    ASSERT_THROW(n.removeFromImportant("NOTE"), std::invalid_argument);
}

TEST(NoteAppTest, TestSearchNote) {
    NoteApp n;
    n.newNote("note1", "text1");

    ASSERT_NE(n.searchNote("note1"), nullptr);
    ASSERT_EQ(n.searchNote("note1")->getName(), "note1");
    ASSERT_EQ(n.searchNote("note1")->getText(), "text1");
    ASSERT_EQ(n.searchNote("NOTE"), nullptr);
}

TEST(NoteAppTest, TestSearchCollection) {
    NoteApp n;
    n.newCollection("coll");

    ASSERT_NE(n.searchCollection("coll"), nullptr);
    ASSERT_EQ(n.searchCollection("coll")->getName(), "coll");
    ASSERT_EQ(n.searchCollection("COLL"), nullptr);
}


TEST(NoteAppTest, TestMoveNote) {
    NoteApp n;
    n.newCollection("coll1");
    n.newCollection("coll2");
    n.newNote("note1", "text1", "coll1");
    auto c1 = n.searchCollection("coll1");
    auto c2 = n.searchCollection("coll2");
    n.moveNote("note1", "coll2");

    ASSERT_EQ(n.getNotesPerCollection()[2], 0);
    ASSERT_EQ(n.getNotesPerCollection()[3], 1);
    ASSERT_EQ(c2->getTitles()[0], "note1");

    n.addToImportant("note1");
    n.moveNote("note1", "Home");
    ASSERT_EQ(n.getNotesPerCollection()[0], 1);
    ASSERT_EQ(n.getNotesPerCollection()[1], 1);
    ASSERT_EQ(n.getNotesPerCollection()[2], 0);

    ASSERT_THROW(n.moveNote("NOTE", "coll"), std::invalid_argument);
    ASSERT_THROW(n.moveNote("note1", "COLL"), std::invalid_argument);
    ASSERT_THROW(n.moveNote("note1", "Home"), std::invalid_argument);
}

TEST(NoteAppTest, TestDeleteNote) {
    NoteApp n;
    n.newNote("note1", "text1");
    n.newNote("note2", "text2");
    auto c = n.searchCollection("Home");
    n.deleteNote("note1");

    ASSERT_EQ(n.searchNote("note1"), nullptr);
    ASSERT_EQ(n.getNotesPerCollection()[1], 1);
    ASSERT_EQ(c->getTitles()[0], "note2");

    n.addToImportant("note2");
    n.deleteNote("note2");
    ASSERT_EQ(n.getNotesPerCollection()[0], 0);
}

TEST(NoteApptest, TestDeleteCollection) {
    NoteApp n;
    n.newCollection("coll");
    n.newNote("note1", "text1", "coll");
    n.addToImportant("note1");
    n.deleteCollection("coll");

    ASSERT_EQ(n.getCollectionsNames().size(), 1);
    ASSERT_EQ(n.searchCollection("coll"), nullptr);
    ASSERT_EQ(n.searchNote("note1"), nullptr);
    ASSERT_EQ(n.getNotesPerCollection()[0], 0);
    ASSERT_THROW(n.deleteCollection("COLL"), std::invalid_argument);
    ASSERT_THROW(n.deleteCollection("Important"), std::invalid_argument);
    ASSERT_THROW(n.deleteCollection("Home"), std::invalid_argument);
}

TEST(NoteAppTest, TestGetCollectionNames) {
    NoteApp n;
    n.newCollection("coll1");
    n.newCollection("coll2");
    auto collNames = n.getCollectionsNames();

    ASSERT_EQ(collNames.size(), 3);
    ASSERT_EQ(collNames[0], "Home");
    ASSERT_EQ(collNames[1], "coll1");
    ASSERT_EQ(collNames[2], "coll2");
    n.deleteCollection("coll1");
    collNames = n.getCollectionsNames();
    ASSERT_EQ(collNames.size(), 2);
    ASSERT_EQ(collNames[1], "coll2");
}
