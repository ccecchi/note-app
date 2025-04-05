#include "gtest/gtest.h"
#include "Collection.h"

class TestObserver : public Observer {
public:
    void update(const std::string &collectionName) override {
        notified = true;
    }

    void resetNotified() {
        notified = false;
    }

    bool wasNotified() const {
        return notified;
    }

private:
    bool notified = false;
};

TEST(CollectionTest, TestAddNote) {
    TestObserver obs;

    auto n = std::make_shared<Note>("name", "text");
    Collection c("collection");
    c.registerObserver(&obs);
    c.addNote(n);
    auto titles = c.getTitles();
    ASSERT_EQ(titles.size(), 1);
    ASSERT_EQ(titles[0], n->getName());
    ASSERT_TRUE(obs.wasNotified());

    obs.resetNotified();
    c.addNote(nullptr);
    titles = c.getTitles();
    ASSERT_EQ(titles.size(), 1);
    ASSERT_FALSE(obs.wasNotified());
}

TEST(CollectionTest, TestDeleteNoteWithPointer) {
    TestObserver obs;
    auto n1 = std::make_shared<Note>("name1", "text1");
    auto n2 = std::make_shared<Note>("name2", "text2");
    auto n3 = std::make_shared<Note>("NAME", "TEXT");
    Collection c("collection");
    c.registerObserver(&obs);
    c.addNote(n1);
    c.addNote(n2);
    n2->setLocked(true);

    obs.resetNotified();
    ASSERT_EQ(c.deleteNote(n2), false);
    auto titles = c.getTitles();
    ASSERT_EQ(titles.size(), 2);
    ASSERT_FALSE(obs.wasNotified());

    obs.resetNotified();
    ASSERT_EQ(c.deleteNote(n3), false);
    titles = c.getTitles();
    ASSERT_EQ(titles.size(), 2);
    ASSERT_FALSE(obs.wasNotified());

    c.deleteNote(n1);
    titles = c.getTitles();
    ASSERT_EQ(titles.size(), 1);
    ASSERT_EQ(titles[0], "name2");
    ASSERT_TRUE(obs.wasNotified());
}

TEST(CollectionTest, TestDeleteNoteWithTitle) {
    TestObserver obs;
    auto n1 = std::make_shared<Note>("name1", "text1");
    auto n2 = std::make_shared<Note>("name2", "text2");
    auto n3 = std::make_shared<Note>("NAME", "TEXT");
    Collection c("collection");
    c.registerObserver(&obs);
    c.addNote(n1);
    c.addNote(n2);
    n2->setLocked(true);

    obs.resetNotified();
    ASSERT_EQ(c.deleteNote("name2"), false);
    auto titles = c.getTitles();
    ASSERT_EQ(titles.size(), 2);
    ASSERT_FALSE(obs.wasNotified());

    obs.resetNotified();
    ASSERT_EQ(c.deleteNote("NOTE"), false);
    titles = c.getTitles();
    ASSERT_EQ(titles.size(), 2);
    ASSERT_FALSE(obs.wasNotified());

    c.deleteNote("name1");
    titles = c.getTitles();
    ASSERT_EQ(titles.size(), 1);
    ASSERT_EQ(titles[0], "name2");
    ASSERT_TRUE(obs.wasNotified());
}

TEST(CollectionTest, TestDeleteNoteWithPosition) {
    TestObserver obs;
    auto n1 = std::make_shared<Note>("name1", "text1");
    auto n2 = std::make_shared<Note>("name2", "text2");
    auto n3 = std::make_shared<Note>("NAME", "TEXT");
    Collection c("collection");
    c.registerObserver(&obs);
    c.addNote(n1);
    c.addNote(n2);
    n2->setLocked(true);

    obs.resetNotified();
    ASSERT_EQ(c.deleteNote(2), false);
    auto titles = c.getTitles();
    ASSERT_EQ(titles.size(), 2);
    ASSERT_FALSE(obs.wasNotified());

    obs.resetNotified();
    ASSERT_EQ(c.deleteNote(4), false);
    titles = c.getTitles();
    ASSERT_EQ(titles.size(), 2);
    ASSERT_FALSE(obs.wasNotified());

    c.deleteNote(1);
    titles = c.getTitles();
    ASSERT_EQ(titles.size(), 1);
    ASSERT_EQ(titles[0], "name2");
    ASSERT_TRUE(obs.wasNotified());
}


TEST(CollectionTest, TestGetTitles) {
    auto n1 = std::make_shared<Note>("name1", "text1");
    auto n2 = std::make_shared<Note>("name2", "text2");
    Collection c("collection");
    c.addNote(n1);
    c.addNote(n2);

    auto titles = c.getTitles();
    ASSERT_EQ(titles.size(), 2);
    ASSERT_EQ(titles[0], "name1");
    ASSERT_EQ(titles[1], "name2");
}

TEST(CollectionTest, TestSearchNote) {
    auto n1 = std::make_shared<Note>("name1", "text1");
    auto n2 = std::make_shared<Note>("name2", "text2");
    Collection c("collection");
    c.addNote(n1);
    c.addNote(n2);

    auto n = c.searchNote("ABC");
    ASSERT_EQ(n.size(), 0);
    n = c.searchNote("name1");
    ASSERT_EQ(n.size(), 1);
    ASSERT_EQ(n[0], n1);
    n = c.searchNote("name");
    ASSERT_EQ(n.size(), 2);
    ASSERT_EQ(n[0], n1);
    ASSERT_EQ(n[1], n2);
}

TEST(CollectionTest, TestModifyNoteTitle) {
    auto n1 = std::make_shared<Note>("name1", "text1");
    Collection c("collection");
    c.addNote(n1);

    ASSERT_TRUE(c.modifyNoteTitle(n1, "NewName"));
    ASSERT_EQ(c.getTitles()[0], "NewName");
    n1->setLocked(true);
    ASSERT_FALSE(c.modifyNoteTitle(n1, "NAME"));
}

TEST(CollectionTest, TestModifyNoteText) {
    auto n1 = std::make_shared<Note>("name1", "text1");
    Collection c("collection");
    c.addNote(n1);

    ASSERT_TRUE(c.modifyNoteText(n1, "NewText"));
    ASSERT_EQ(n1->getText(), "NewText");
    n1->setLocked(true);
    ASSERT_FALSE(c.modifyNoteTitle(n1, "TEXT"));
}

TEST(CollectionTest, TestGetImportantNotes) {
    auto n1 = std::make_shared<Note>("name1", "text1");
    auto n2 = std::make_shared<Note>("name2", "text2");
    Collection c("collection");
    c.addNote(n1);
    c.addNote(n2);

    ASSERT_EQ(c.getImportantNotes().size(), 0);

    n2->setImportant(true);
    ASSERT_EQ(c.getImportantNotes().size(), 1);
    ASSERT_EQ(c.getImportantNotes()[0], n2);
}