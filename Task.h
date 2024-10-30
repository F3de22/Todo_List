#ifndef LABPROGRAMMAZIONE_TASK_H
#define LABPROGRAMMAZIONE_TASK_H

#include <string>
using namespace std;

class Task {
    public:
        Task(const string& title, const string& description = "", time_t dueDate = 0)
            : title(title), description(description), isCompleted(false), expirationDate(expirationDate) {}

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
            return title + ";" + description + ";" + (isCompleted ? "1" : "0");
        }

        // Metodo per ricostruire la task da una stringa letta dal file
        static Task deserialize(const string& data) {
            size_t pos1 = data.find(";");
            size_t pos2 = data.find(";", pos1 + 1);

            string title = data.substr(0, pos1);
            string description = data.substr(pos1 + 1, pos2 - pos1 - 1);
            bool completed = data.substr(pos2 + 1) == "1";

            return Task(title, description, completed);
        }

        // Metodo per convertire la task in stringa (per la visualizzazione)
        string toString() const {
            string status = isCompleted ? "✓" : "✗";
            string dateStr = expirationDate == 0 ? "No deadline" : ctime(&expirationDate);
            return status + " " + title + " (Due: " + dateStr + ")";
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
        time_t expirationDate;  // Timestamp per la data di scadenza
};

#endif //LABPROGRAMMAZIONE_TASK_H
