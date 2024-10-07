//
// Created by monet on 07/10/2024.
//

#ifndef LABPROGRAMMAZIONE_TODOAPP_H
#define LABPROGRAMMAZIONE_TODOAPP_H
#include "TodoList.h"
#include "Task.h"
#include <iostream>
using namespace std;

class TodoApp {
    void run() {
        TodoList todoList;
        string command;
        while (true) {
            cout << "Comando (add, list, complete, remove, quit): ";
            cin >> command;

            if (command == "add") {
                string title;
                cout << "Titolo task: ";
                cin.ignore();
                getline(cin, title);
                todoList.addTask(Task(title));
            }
            else if (command == "list") {
                todoList.listTasks();
            }
            else if (command == "complete") {
                string title;
                cout << "Titolo task da completare: ";
                cin.ignore();
                getline(cin, title);
                todoList.markTaskComplete(title);
            }
            else if (command == "remove") {
                string title;
                cout << "Titolo task da rimuovere: ";
                cin.ignore();
                getline(cin, title);
                todoList.removeTask(title);
            }
            else if (command == "quit") {
                break;
            }
        }
    }
};


#endif //LABPROGRAMMAZIONE_TODOAPP_H
