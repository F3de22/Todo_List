#ifndef LABPROGRAMMAZIONE_TODOLIST_H
#define LABPROGRAMMAZIONE_TODOLIST_H

#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class TodoList {
    public:
        // Aggiunge una task alla lista
        void addTask(const Task& task) {
            tasks.push_back(task);
        }

        // Rimuove una task dalla lista in base al titolo
        void removeTask(const string& taskTitle) {
            tasks.erase(remove_if(tasks.begin(), tasks.end(),
                                  [&taskTitle](const Task& task) {
                                      return task.getTitle() == taskTitle;
                                  }), tasks.end());
        }

        // Trova una task basata sul titolo
        Task* getTask(const string& taskTitle) {
            for (auto& task : tasks) {
                if (task.getTitle() == taskTitle) {
                    return &task;
                }
            }
            return nullptr;
        }

        // Segna una task come completata
        void markTaskComplete(const string& taskTitle) {
            Task* task = getTask(taskTitle);
            if (task) {
                task->markComplete();
            }
        }

        void markTaskImportant(const string& taskTitle) {
            Task* task = getTask(taskTitle);
            if (task) {
                task->markImportant();
            }
        }

        // Elenca tutte le task
        void listTasks() const {
            for (const auto& task : tasks) {
                cout << task.toString() << endl;
            }
        }

        // Salva le task in un file JSON
        void saveToFile() const {
            ofstream file("todolist.txt");
            if (!file.is_open()) {
                cerr << "Errore apertura file per scrittura" << endl;
                return;
            }
            for (const auto& task : tasks) {
                file << task.serialize() << endl;
            }
            file.close();
        }

        // Carica le task da un file JSON
        void loadFromFile() {
            ifstream file("todolist.txt");
            if (!file.is_open()) {
                cerr << "Errore apertura file per lettura" << endl;
                return;
            }

            tasks.clear();
            string line;
            while (getline(file, line)) {
                tasks.push_back(Task::deserialize(line));
            }
            file.close();
        }

    private:
        vector<Task> tasks;
};


#endif //LABPROGRAMMAZIONE_TODOLIST_H
