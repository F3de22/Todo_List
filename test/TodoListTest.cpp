#include "gtest/gtest.h"
#include "../TodoList.h"
#include "../Task.h"

TEST(TodoListTest, AddTaskAndGetTask) {
    TodoList list;
    Task t("comprare", "comprare il pane", false, "");
    list.addTask(t);

    Task* found = list.getTask("comprare");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getTitle(), "comprare");
}

TEST(TodoListTest, RemoveTask) {
    TodoList list;
    Task t("comprare", "comprare il pane", false, "");
    list.addTask(t);

    list.removeTask("comprare");
    Task* found = list.getTask("comprare");
    EXPECT_EQ(found, nullptr);
}

TEST(TodoListTest, MarkTaskComplete) {
    TodoList list;
    Task t("studiare", "studiare C++", false, "");
    list.addTask(t);

    list.markTaskComplete("studiare");
    Task* found = list.getTask("studiare");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getCompleted(), true);
}

TEST(TodoListTest, MarkTaskImportant) {
    TodoList list;
    Task t("comprare", "comprare il latte", false, "");
    list.addTask(t);

    list.markTaskImportant("comprare");
    Task* found = list.getTask("comprare");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getImportant(), true);
}