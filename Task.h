#include <sstream>
#include <string>
using namespace std;

class Task {
    public:
        Task(const string& title, const string& description = "", bool important=false, const string& expirationDate="-")
            : title(title), description(description), isCompleted(false), important(important), expirationDate(expirationDate) {}

        void markComplete() {
            isCompleted = true;
        }

        void markImportant(){
            important = true;
        }

        void markNotImportant(){
            important = false;
        }

        // Metodo per convertire la task in stringa per la scrittura su file
        string toString() const {
            string completed = isCompleted ? "completata" : "non completata";
            string imp = important ? "importante" : "non importante";
            return title + "|" + description + "|" + completed + "|" + imp + "|" + expirationDate;
        }

        // Metodo per ricostruire la task da una stringa letta dal file
        static Task toTask(const string& data) {
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

        // Metodo per convertire la task in stringa (per la visualizzazione)
        string visual() const {
            return title + " - " + description + " - Scadenza: " + expirationDate +
            " - Completata: " + (isCompleted ? "Si" : "No") +
            " - Importante: " + (important ? "Si" : "No");
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
