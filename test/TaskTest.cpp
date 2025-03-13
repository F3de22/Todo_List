#include "gtest/gtest.h"
#include "../Task.h"
using namespace std;

TEST(TaskTest, taskfunction){
    Task task("leggere", "leggere un libro", false, "01-01-2025");
    task.markComplete();
    task.markImportant();

    string taskasstring = task.toString();
    Task newTask = Task::toTask(taskasstring);

    EXPECT_EQ(task.getTitle(),newTask.getTitle());
    EXPECT_EQ(task.visual(),newTask.visual());
}