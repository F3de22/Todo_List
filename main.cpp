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
        cout << "Comando (add-task, list, important, notimportant, completed, remove, quit): ";
        cin >> command;

        if (command == "add-task") {
            string title, description, expirationDate;

            cout << "Titolo task: ";
            cin.ignore(); // Ignora il newline rimasto nel buffer
            getline(cin, title);

            cout << "Descrizione task: ";
            getline(cin, description);

            cout << "Data di scadenza (formato DD-MM-YYYY, premere INVIO per lasciare vuoto): ";
            getline(cin, expirationDate);

            char importantChoice;
            cout << "Segnare come importante? (s/n): ";
            cin >> importantChoice;
            bool important = (importantChoice == 's');
            todoList.addTask(Task(title, description,important,expirationDate));

            todoList.saveToFile("todolist.txt");
        }
        else if (command == "list") {
            todoList.listTasks();
        }
        else if (command == "important") {
            string title;
            cout << "Titolo task da impostare come importante: "<<endl;
            getline(cin, title);
            todoList.markTaskImportant(title);

            todoList.saveToFile("todolist.txt");
        }
        else if(command == "notimportant"){
            string title;
            cout << "Titolo task da impostare come non importante: "<<endl;
            getline(cin, title);
            todoList.markTaskNotImportant(title);

            todoList.saveToFile("todolist.txt");
        }
        else if (command == "completed") {
            string title;
            cout << "Titolo task completata: "<<endl;
            getline(cin, title);
            todoList.markTaskComplete(title);

            todoList.saveToFile("todolist.txt");
        }
        else if (command == "remove") {
            string title;
            cout << "Titolo task da rimuovere: "<<endl;
            cin.ignore();
            getline(cin, title);
            todoList.removeTask(title);
            todoList.saveToFile("todolist.txt");
        }
        else if(command =="quit"){
            break;
        }
    }
    return 0;
}
