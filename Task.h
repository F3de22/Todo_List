#ifndef LABPROGRAMMAZIONE_TASK_H
#define LABPROGRAMMAZIONE_TASK_H

#include <sstream>
#include <string>
using namespace std;

class Task {
    public:
        Task(const string& title, const string& description = "", bool important=false, const string& expirationDate="")
            : title(title), description(description), isCompleted(false), important(), expirationDate(expirationDate) {}

        void markComplete() {
            isCompleted = true;
        }

        void markImportant(){
            important = true;
        }

        void markNotImportant(){
            important = true;
        }

        // Metodo per convertire la task in stringa per la scrittura su file
        string serialize() const {
            string completionStatus = isCompleted ? "completata" : "non completata";
            string importanceStatus = important ? "importante" : "non importante";
            return title + "|" + description + "|" + completionStatus + "|" + importanceStatus + "|" + expirationDate;

        }

        // Metodo per ricostruire la task da una stringa letta dal file
        static Task deserialize(const string& data) {
            stringstream ss(data);
            string title, description, expirationDate, completedStr, importantStr;

            getline(ss, title, '|');
            getline(ss, description, '|');
            getline(ss, expirationDate, '|');
            getline(ss, completedStr, '|');
            getline(ss, importantStr, '|');

            Task task(title, description, importantStr == "1", expirationDate);
            task.isCompleted = (completedStr == "1");
            return task;
        }

        // Metodo per convertire la task in stringa (per la visualizzazione)
        string toString() const {
            return title + " - " + description + " - Scadenza: " + expirationDate +
            " - Completata: " + (isCompleted ? "✓" : "✗") +
            " - Importante: " + (important ? "Sì" : "No");
        }

        // Getter per il titolo della task
        string getTitle() const {
            return title;
        }

    private:
        string title;
        string description;
        bool isCompleted;
        bool important;
        string expirationDate;
};

#endif //LABPROGRAMMAZIONE_TASK_H
