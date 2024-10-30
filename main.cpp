//Classi che rappresentano attività da svolgere (es. per todo list). Deve essere possibile scrivere e leggere da disco l'elenco delle attività.

#include <iostream>
#include <string>
#include <ctime>
#include <filesystem>

#include "Task.h"
#include "TodoList.h"

using namespace std;

int main() {
    TodoList todoList;
    todoList.loadFromFile();

    string command;
    while (true) {
        cout << "Comando (add-task, full-list, important, completed, remove, save): ";
        cin >> command;

        if (command == "add-task") {
            string title, description, expirationDate;

            cout << "Titolo task: ";
            cin.ignore(); // Ignora il newline rimasto nel buffer
            getline(cin, title);

            cout << "Descrizione task: ";
            getline(cin, description);

            cout << "Data di scadenza (formato YYYY-MM-DD): ";
            getline(cin, expirationDate);

            char importantChoice;
            cout << "Segnare come importante? (s/n): ";
            cin >> importantChoice;

            bool important = (importantChoice == 's' || importantChoice == 'S');
            todoList.addTask(Task(title, description));
            cout <<"remember to save!"<<endl;
        }
        else if (command == "full-list") {
            todoList.listTasks();
        }
        else if (command == "important") {
            string title;
            cout << "Titolo task da impostare come importante: "<<endl;
            getline(cin, title);
            todoList.markTaskImportant(title);
            cout <<"remember to save!"<<endl;
        }
        else if (command == "completed") {
            string title;
            cout << "Titolo task da completare: "<<endl;
            getline(cin, title);
            todoList.markTaskComplete(title);
            cout <<"remember to save!"<<endl;
        }
        else if (command == "remove") {
            string title;
            cout << "Titolo task da rimuovere: "<<endl;
            cin.ignore();
            getline(cin, title);
            todoList.removeTask(title);
            cout <<"remember to save!"<<endl;
        }
        else if (command == "save") {
            todoList.saveToFile("todolist.txt");
            break;
        }
    }
    return 0;
}
