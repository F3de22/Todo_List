#include "gtest/gtest.h"
#include "../Task.h"

TEST(TaskTest, CreationAndGetters) {
    Task task("leggere", "leggere un libro", false, "01-01-2025");

    EXPECT_EQ(task.getTitle(), "leggere");
    EXPECT_EQ(task.getDescription(), "leggere un libro");
    EXPECT_EQ(task.getExpirationDate(), "01-01-2025");
    EXPECT_FALSE(task.isCompleted());
    EXPECT_FALSE(task.isImportant());
}

TEST(TaskTest, MarkCompleteAndImportance) {
    Task task("leggere", "leggere un libro", false, "01-01-2025");

    task.markComplete();
    task.markImportant();

    EXPECT_TRUE(task.isCompleted());
    EXPECT_TRUE(task.isImportant());

    task.markNotImportant();
    EXPECT_FALSE(task.isImportant());
}

TEST(TaskTest, Setters) {
    Task task("vecchio", "desc", false, "01-01-2025");

    task.setTitle("nuovo");
    task.setDescription("descrizione aggiornata");
    task.setExpirationDate("31-12-2025");

    EXPECT_EQ(task.getTitle(), "nuovo");
    EXPECT_EQ(task.getDescription(), "descrizione aggiornata");
    EXPECT_EQ(task.getExpirationDate(), "31-12-2025");
}

TEST(TaskTest, InvalidDateThrows) {
    EXPECT_THROW({
                     Task t("errore", "descrizione", false, "2025/12/31");
                 }, std::invalid_argument);

    Task t("ok", "desc", false, "01-01-2025");
    EXPECT_THROW({
                     t.setExpirationDate("31-02-25");  // formato errato
                 }, std::invalid_argument);
}

TEST(TaskTest, EmptyDateBecomesDash) {
    Task t("vuoto", "desc", false, "");
    EXPECT_EQ(t.getExpirationDate(), "-");

    t.setExpirationDate("");
    EXPECT_EQ(t.getExpirationDate(), "-");
}

TEST(TaskTest, ToStringAndFromString) {
    Task task("leggere", "leggere un libro", false, "01-01-2025");
    task.markComplete();
    task.markImportant();

    std::string serialized = task.toString();
    Task deserialized = Task::toTask(serialized);

    EXPECT_EQ(task.getTitle(), deserialized.getTitle());
    EXPECT_EQ(task.getDescription(), deserialized.getDescription());
    EXPECT_EQ(task.getExpirationDate(), deserialized.getExpirationDate());
    EXPECT_EQ(task.isCompleted(), deserialized.isCompleted());
    EXPECT_EQ(task.isImportant(), deserialized.isImportant());
    EXPECT_EQ(task.toString(), deserialized.toString());
}
