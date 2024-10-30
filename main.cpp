//Classi che rappresentano attività da svolgere (es. per todo list). Deve essere possibile scrivere e leggere da disco l'elenco delle attività.

#include <iostream>
#include <string>
#include <ctime>

#include "Task.h"
#include "TodoList.h"

using namespace std;

int main() {
    TodoList todoList;
    todoList.loadFromFile("todolist.txt");
    string command;
    while (true) {
        cout << "Comando (add-task, full-list, important, completed, remove, save): ";
        cin >> command;

        if (command == "add-task") {
            string title, description;
            cout << "Titolo task: "<<endl;
            getline(cin, title);
            cout << "Descrizione task: "<<endl;
            getline(cin, description);
            todoList.addTask(Task(title, description));
            cout <<"remember to save!";
        }
        else if (command == "full-list") {
            todoList.listTasks();
        }
        else if (command == "important") {
            string title;
            cout << "Titolo task da impostare come importante: "<<endl;
            getline(cin, title);
            todoList.markTaskImportant(title);
            cout <<"remember to save!";
        }
        else if (command == "completed") {
            string title;
            cout << "Titolo task da completare: "<<endl;
            getline(cin, title);
            todoList.markTaskComplete(title);
            cout <<"remember to save!";
        }
        else if (command == "remove") {
            string title;
            cout << "Titolo task da rimuovere: "<<endl;
            getline(cin, title);
            todoList.removeTask(title);
            cout <<"remember to save!";
        }
        else if (command == "save") {
            todoList.saveToFile("tasks.txt");
            break;
        }
    }
    return 0;
}
