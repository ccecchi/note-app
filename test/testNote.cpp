#include "gtest/gtest.h"
#include "Note.h"

TEST(NoteTest, TestSetName) {
    Note n("Name","Text");
    n.setName("NewName");
    ASSERT_EQ("NewName", n.getName());

    n.setLocked(true);
    ASSERT_THROW(n.setName("ABC"), std::logic_error);
}

TEST(NoteTest, TestSetText) {
    Note n("Name","Text");
    n.setText("NewText");
    ASSERT_EQ("NewText", n.getText());

    n.setLocked(true);
    ASSERT_THROW(n.setText("ABC"), std::logic_error);
}