//
// Created by monet on 07/10/2024.
//

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

        void markIncomplete() {
            isCompleted = false;
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
        time_t expirationDate;  // Timestamp per la data di scadenza
};

#endif //LABPROGRAMMAZIONE_TASK_H
