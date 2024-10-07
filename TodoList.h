//
// Created by monet on 07/10/2024.
//

#ifndef LABPROGRAMMAZIONE_TODOLIST_H
#define LABPROGRAMMAZIONE_TODOLIST_H

#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <nlohmann/json.hpp>  // Libreria JSON per la lettura e scrittura dei file

using namespace std;
using json = nlohmann::json;

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

        // Elenca tutte le task
        void listTasks() const {
            for (const auto& task : tasks) {
                cout << task.toString() << endl;
            }
        }

        // Salva le task in un file JSON
        void saveToFile(const string& filename) const {
            ofstream file(filename);
            if (!file.is_open()) {
                cerr << "Errore apertura file per scrittura" << endl;
                return;
            }

            json jsonTasks;
            for (const auto& task : tasks) {
                jsonTasks.push_back({ {"title", task.getTitle()}, {"completed", task.isCompleted} });
            }

            file << jsonTasks.dump(4);  // Scrittura nel file con indentazione
            file.close();
        }

        // Carica le task da un file JSON
        void loadFromFile(const string& filename) {
            ifstream file(filename);
            if (!file.is_open()) {
                cerr << "Errore apertura file per lettura" << endl;
                return;
            }

            json jsonTasks;
            file >> jsonTasks;

            for (const auto& taskData : jsonTasks) {
                Task task(taskData["title"], "", 0);
                if (taskData["completed"]) {
                    task.markComplete();
                }
                addTask(task);
            }
        }

    private:
        vector<Task> tasks;
};


#endif //LABPROGRAMMAZIONE_TODOLIST_H
