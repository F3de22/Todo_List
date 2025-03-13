#include "gtest/gtest.h"
#include "../TodoList.h"
#include "../Task.h"

class TodoListTestFixture : public ::testing::Test {
protected:
    TodoList list;
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
    EXPECT_NE(t->getCompleted(), true);
}