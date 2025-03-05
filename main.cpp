//Classi che rappresentano attività da svolgere (es. per todo list). Deve essere possibile scrivere e leggere da disco l'elenco delle attività.

#include <iostream>
#include <string>
#include <limits>

#include "Task.h"
#include "TodoList.h"

using namespace std;

int main() {
    TodoList todoList;
    todoList.loadFromFile();

    string command;
    cout << "  / / (_) ___ | |_  __ _    __| |  ___ (_)   ___  ___   _ __ ___    __ _  _ __    __| |(_) \n"
            " / /  | |/ __|| __|/ _` |  / _` | / _ \\| |  / __|/ _ \\ | '_ ` _ \\  / _` || '_ \\  / _` || |\n"
            "/ /___| |\\__ \\| |_| (_| | | (_| ||  __/| | | (__| (_) || | | | | || (_| || | | || (_| || | \n"
            "\\____/|_||___/ \\__|\\__,_|  \\__,_| \\___||_|  \\___|\\___/ |_| |_| |_| \\__,_||_| |_| \\__,_||_|\n"
            "- add-task: per aggiungere un nuovo task\n"
            "- list: per visualizzare la lista completa di task\n"
            "- important: per impostare un task come importante\n"
            "- notimportant: per impostare un task come non importante\n"
            "- completed: per impostare un task come terminato\n"
            "- remove: per rimuovere un task\n"
            "- quit: per interrompere la sessione"<<endl<<endl;
    while (true) {
        cout << "inserisci il comando che vuoi eseguire" << endl;
        cin >> command;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (command == "add-task") {
            string title, description, expirationDate;

            cout << "Titolo task: ";
            getline(cin, title); // Legge intera riga, utile se ci sono spazi

            cout << "Descrizione task: ";
            getline(cin, description);

            cout << "Data di scadenza (formato DD-MM-YYYY, premi INVIO per lasciare vuoto): " << endl;
            getline(cin, expirationDate);

            char importantChoice;
            cout << "Segnare come importante? (s/n): ";
            cin >> importantChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool important = (importantChoice == 's' || importantChoice == 'S');

            todoList.addTask(Task(title, description, important, expirationDate));
            todoList.saveToFile("todolist.txt");
        }
        else if (command == "list") {
            todoList.listTasks();
        }
        else if (command == "important") {
            string title;
            cout << "Titolo task da impostare come importante: " << endl;
            getline(cin, title);
            todoList.markTaskImportant(title);
            todoList.saveToFile("todolist.txt");
        }
        else if (command == "notimportant") {
            string title;
            cout << "Titolo task da impostare come non importante: " << endl;
            getline(cin, title);
            todoList.markTaskNotImportant(title);
            todoList.saveToFile("todolist.txt");
        }
        else if (command == "completed") {
            string title;
            cout << "Titolo task da completare: " << endl;
            getline(cin, title);
            todoList.markTaskComplete(title);
            todoList.saveToFile("todolist.txt");
        }
        else if (command == "remove") {
            string title;
            cout << "Titolo task da rimuovere: " << endl;
            getline(cin, title);
            todoList.removeTask(title);
            todoList.saveToFile("todolist.txt");
        }
        else if (command == "quit") {
            break;
        }
        cout << "\n";
    }

    return 0;
}
