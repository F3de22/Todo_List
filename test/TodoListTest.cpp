#include "gtest/gtest.h"
#include "../TodoList.h"
#include "../Task.h"

TEST(TodoListTest, AddTaskAndGetTask) {
    TodoList list("Test");
    Task t("comprare", "comprare il pane", false, "");
    list.addTask(t);

    Task* found = list.getTask("comprare");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->getTitle(), "comprare");
}

TEST(TodoListTest, RemoveTask) {
    TodoList list("Test");
    Task t("comprare", "comprare il pane", false, "");
    list.addTask(t);

    list.removeTask("comprare");
    Task* found = list.getTask("comprare");
    EXPECT_EQ(found, nullptr);
}

TEST(TodoListTest, MarkTaskComplete) {
    TodoList list("Test");
    Task t("studiare", "studiare C++", false, "");
    list.addTask(t);

    EXPECT_EQ(list.getCompletedCount(),0);
    list.markTaskComplete("studiare");
    Task* found = list.getTask("studiare");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(list.getCompletedCount(),1);
    EXPECT_TRUE(found->isCompleted());
}

TEST(TodoListTest, MarkTaskImportant) {
    TodoList list("Test");
    Task t("comprare", "comprare il latte", false, "");
    list.addTask(t);

    list.markTaskImportant("comprare");
    Task* found = list.getTask("comprare");
    ASSERT_NE(found, nullptr);
    EXPECT_TRUE(found->isImportant());
}

TEST(TodoListTest, MarkTaskNotImportant) {
    TodoList list("Test");
    Task t("lavorare", "scrivere report", false, "");
    list.addTask(t);
    list.markTaskImportant("lavorare");

    list.markTaskNotImportant("lavorare");
    Task* found = list.getTask("lavorare");
    ASSERT_NE(found, nullptr);
    EXPECT_FALSE(found->isImportant());
}

TEST(TodoListTest, CountCompletedAndUncompleted) {
    TodoList list("Test");
    list.addTask(Task("task1", "desc", false, ""));
    list.addTask(Task("task2", "desc", true, ""));
    list.addTask(Task("task3", "desc", false, ""));

    Task* t = list.getTask("task2");
    list.markTaskComplete(t->getTitle());

    EXPECT_EQ(list.getCompletedCount(), 1);
    EXPECT_EQ(list.getUncompletedCount(), 2);
}

TEST(TodoListTest, EditTask) {
    TodoList list("Test");
    list.addTask(Task("vecchio", "desc", false, "01-01-2024"));

    list.editTask("vecchio", "nuovo", "nuova desc", "31-12-2025");
    Task* t = list.getTask("nuovo");
    ASSERT_NE(t, nullptr);
    EXPECT_EQ(t->getTitle(), "nuovo");
    EXPECT_EQ(t->getDescription(), "nuova desc");
    EXPECT_EQ(t->getExpirationDate(), "31-12-2025");
}

TEST(TodoListTest, SetAndGetName) {
    TodoList list("Lavoro");
    EXPECT_EQ(list.getName(), "Lavoro");
    list.setName("Casa");
    EXPECT_EQ(list.getName(), "Casa");
}

TEST(TodoListTest, SearchTasks) {
    TodoList list{"SearchTest"};
    list.addTask(Task("comprare latte", "andare al supermercato", false, ""));
    list.addTask(Task("comprare pane", "andare in panetteria", false, ""));
    list.addTask(Task("studiare", "studiare per l'esame", false, ""));

    // Test: keyword che trova più task
    vector<Task> results = list.searchTasks("comprare");
    ASSERT_EQ(results.size(), 2);
    EXPECT_EQ(results[0].getTitle(), "comprare latte");
    EXPECT_EQ(results[1].getTitle(), "comprare pane");

    // Test: keyword che trova una sola task
    results = list.searchTasks("studiare");
    ASSERT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].getTitle(), "studiare");

    // Test: keyword che non trova nulla
    results = list.searchTasks("vacanza");
    EXPECT_TRUE(results.empty());
}

TEST(TodoListTest, SaveAndLoad) {
    TodoList list("TestList");
    list.addTask(Task("task1", "desc1", false, "01-01-2024"));
    list.addTask(Task("task2", "desc2", true, "01-01-2024"));

    std::string filename = "test_save_load.txt";
    list.saveToFile(filename);

    TodoList loaded("vuoto");
    loaded.loadFromFile(filename);

    EXPECT_EQ(loaded.getName(), "TestList");
    EXPECT_EQ(loaded.getAllTasks().size(), 2);
    EXPECT_EQ(loaded.getTask("task1")->getDescription(), "desc1");
    EXPECT_TRUE(loaded.getTask("task2")->isImportant());

    std::remove(filename.c_str());
}

