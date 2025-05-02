#include <sstream>
#include <string>
#include <regex>

#pragma once
using namespace std;

class Task {
    public:
        Task(const string& title, const string& description = "", bool important=false, const string& expirationDate="-");

        void markComplete();

        void markImportant();

        void markNotImportant();

        bool isCompleted() const;

        bool isImportant() const;

        string getDescription() const;

        string getExpirationDate() const;

        string getTitle() const;

        void setTitle(const string& newTitle);

        void setDescription(const string& newDescription);

        void setExpirationDate(const string& newDate);

        // Metodo per convertire la task in stringa per la scrittura su file
        string toString() const;

        // Metodo per ricostruire la task da una stringa letta dal file
        static Task toTask(const string& data);

    private:
        bool isValidDateFormat(const string& date);

        string title;
        string description;
        bool completed;
        bool important;
        string expirationDate;
};
