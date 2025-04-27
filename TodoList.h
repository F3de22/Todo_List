#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Task.h"

using namespace std;

class TodoList {
    public:
        TodoList(const string& name) : name(name) {}

        //ritorna il nome della todolist
        string getName() const;

        //set nome della todolist
        void setName(const string& newName);

        // Aggiunge una task alla lista
        void addTask(const Task& task);

        // Rimuove una task dalla lista in base al titolo
        void removeTask(const string& taskTitle);

        // Trova una task basata sul titolo
        Task* getTask(const string& taskTitle);

        //Trova le task che contengono una certa parola
        vector<Task> searchTasks(const string& keyword);

        // Segna una task come completata
        void markTaskComplete(const string& taskTitle);

        // Segna una task come importante
        void markTaskImportant(const string& taskTitle);

        // Segna una task come non importante
        void markTaskNotImportant(const string& taskTitle);

        //ritorna il numero di task completate
        int getCompletedCount() const;

        //ritorna il numero di task non completate
        int getUncompletedCount() const;

        //get di tutte le task
        const vector<Task>& getAllTasks() const;

        //modifica una task
        void editTask(const string& oldTitle, const string& newTitle, const string& newDescription, const string& newDate);

        // Salva le task in nel file
        void saveToFile(const string& filename) const;

        // Carica le task da un file di testo
        void loadFromFile(const string& filename);

    private:
        vector<Task> tasks;
        string name;
};

