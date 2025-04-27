#include "gtest/gtest.h"
#include "../TodoList.h"
#include "../Task.h"

class TodoListTestFixture : public ::testing::Test {
protected:
    TodoList list{"test_list"};
    virtual void SetUp() override{
        list.addTask(Task("comprare", "comprare latte", false, ""));
        list.addTask(Task("studiare", "studiare Google Test", false, "01-01-2026"));
    }
};

TEST_F(TodoListTestFixture, ContainsInitialTasks) {
    EXPECT_NE(list.getTask("comprare"), nullptr);
    EXPECT_NE(list.getTask("studiare"), nullptr);
}

TEST_F(TodoListTestFixture, MarkTaskComplete) {
    list.markTaskComplete("comprare");
    Task* t = list.getTask("comprare");
    EXPECT_EQ(t->isCompleted(), true);
}

TEST_F(TodoListTestFixture, RemoveTask) {
    list.removeTask("comprare");
    EXPECT_EQ(list.getTask("comprare"), nullptr);
    EXPECT_NE(list.getTask("studiare"), nullptr);  // L'altra task deve rimanere
}

TEST_F(TodoListTestFixture, MarkTaskImportant) {
    list.markTaskImportant("studiare");
    Task* t = list.getTask("studiare");
    ASSERT_NE(t, nullptr);
    EXPECT_TRUE(t->isImportant());
}

TEST_F(TodoListTestFixture, EditTaskDetails) {
    list.editTask("studiare", "programmare", "programmare in C++", "31-12-2025");
    Task* t = list.getTask("programmare");
    ASSERT_NE(t, nullptr);
    EXPECT_EQ(t->getTitle(), "programmare");
    EXPECT_EQ(t->getDescription(), "programmare in C++");
    EXPECT_EQ(t->getExpirationDate(), "31-12-2025");
}
