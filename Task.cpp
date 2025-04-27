#include "Task.h"

bool isValidDateFormat(const string& date) {
    // Regex per "DD-MM-AAAA", con giorno 01-31, mese 01-12, anno a 4 cifre
    regex dateRegex(R"(^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-\d{4}$)");
    return regex_match(date, dateRegex);
}

Task::Task(const string& title, const string& description, bool important, const string& expirationDate)
        : title(title), description(description), isCompleted(false), important(important), expirationDate(expirationDate) {
    if (!expirationDate.empty() && expirationDate != "-" && !isValidDateFormat(expirationDate)) {
        throw invalid_argument("Data non valida. Usa il formato DD-MM-AAAA.");
    }
    this->expirationDate = expirationDate.empty() ? "-" : expirationDate;
}

void Task::markComplete() {
    isCompleted = true;
}

void Task::markImportant(){
    important = true;
}

void Task::markNotImportant(){
    important = false;
}

bool Task::getCompleted() const{
    return isCompleted;
}

bool Task::getImportant() const{
    return important;
}

string Task::getDescription() const{
    return description;
}

string Task::getExpirationDate() const {
    return expirationDate;
}

string Task::getTitle() const {
    return title;
}

void Task::setTitle(const string& newTitle) {
    title = newTitle;
}

void Task::setDescription(const string& newDescription) {
    description = newDescription;
}

void Task::setExpirationDate(const string& newDate) {
    if (!newDate.empty() && newDate != "-" && !isValidDateFormat(newDate)) {
        throw invalid_argument("Data non valida. Usa il formato DD-MM-AAAA o lascia vuoto per nessuna scadenza.");
    }
    expirationDate = newDate.empty() ? "-" : newDate;
}

// Metodo per convertire la task in stringa per la scrittura su file
string Task::toString() const {
    string completed = isCompleted ? "completata" : "non completata";
    string imp = important ? "importante" : "non importante";
    return title + "|" + description + "|" + completed + "|" + imp + "|" + expirationDate;
}

// Metodo per ricostruire la task da una stringa letta dal file
Task Task::toTask(const string& data) {
    stringstream ss(data);
    string title, description, expirationDate, completedStr, importantStr;

    getline(ss, title, '|');
    getline(ss, description, '|');
    getline(ss, completedStr, '|');
    getline(ss, importantStr, '|');
    getline(ss, expirationDate, '|');

    bool important = (importantStr == "importante");

    Task task(title, description, important, expirationDate);
    task.isCompleted = (completedStr == "completata");
    return task;
}