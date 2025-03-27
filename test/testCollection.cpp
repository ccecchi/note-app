#include "gtest/gtest.h"
#include "Collection.h"

class MockObserver : public Observer {
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
    MockObserver obs;

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

TEST(CollectionTest, TestDeleteNote) {
    MockObserver obs;
    auto n1 = std::make_shared<Note>("name1", "text1");
    auto n2 = std::make_shared<Note>("name2", "text2");
    Collection c("collection");
    c.registerObserver(&obs);
    c.addNote(n1);
    c.addNote(n2);

    obs.resetNotified();
    c.deleteNote(nullptr);
    auto titles = c.getTitles();
    ASSERT_EQ(titles.size(), 2);
    ASSERT_FALSE(obs.wasNotified());

    c.deleteNote(n1);
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
    ASSERT_EQ(n, nullptr);
    n = c.searchNote("name1");
    ASSERT_EQ(n,n1);
    n = c.searchNote("name2");
    ASSERT_EQ(n,n2);
}