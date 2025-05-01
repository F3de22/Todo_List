//Classi che rappresentano attività da svolgere (es. per todo list). Deve essere possibile scrivere e leggere da disco l'elenco delle attività.

#include <iostream>
#include <string>
#include <limits>
#include <filesystem>
namespace fs = std::filesystem;

#include "Task.h"
#include "TodoList.h"

using namespace std;

int main() {
    string basePath = "../liste/";
    string listName;
    cout << "Nome della tua TodoList: ";
    getline(cin, listName);

    string fileName = basePath + listName + ".txt";

    TodoList todoList(listName);
    todoList.loadFromFile(fileName);

    cout << "Hai aperto la lista: " << todoList.getName() << endl;

    string command;
    cout << "  / / (_) ___ | |_  __ _    __| |  ___ (_)   ___  ___   _ __ ___    __ _  _ __    __| |(_) \n"
            " / /  | |/ __|| __|/ _` |  / _` | / _ \\| |  / __|/ _ \\ | '_ ` _ \\  / _` || '_ \\  / _` || |\n"
            "/ /___| |\\__ \\| |_| (_| | | (_| ||  __/| | | (__| (_) || | | | | || (_| || | | || (_| || | \n"
            "\\____/|_||___/ \\__|\\__,_|  \\__,_| \\___||_|  \\___|\\___/ |_| |_| |_| \\__,_||_| |_| \\__,_||_|\n"
            "- add-task: per aggiungere un nuovo task\n"
            "- list: per visualizzare la lista completa di task\n"
            "- listcompleted: per visualizzare la lista delle task completate\n"
            "- listuncompleted: per visualizzare la lista delle task non completate\n"
            "- important: per impostare un task come importante\n"
            "- notimportant: per impostare un task come non importante\n"
            "- completed: per impostare un task come terminato\n"
            "- remove: per rimuovere un task\n"
            "- search: cerca le task che contengono nel titolo o nella descrizione una certa parola\n"
            "- edit: per modificare titolo, descrizione e scadenza di un task\n"
            "- renamelist: per modificare il nome della todolist\n"
            "- switch: per passare da una todolist ad un'altra\n"
            "- quit: per interrompere la sessione"<<endl<<endl;
    while (true) {
        const auto& tasks = todoList.getAllTasks();
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
            todoList.saveToFile(fileName);
        }
        else if (command == "list") {
            bool found = false;
            for (const auto& task : tasks) {
                cout << task.toString() << endl;
                found = true;
            }
            if(found) {
                cout << "Task completate: " << todoList.getCompletedCount() << endl;
                cout << "Task non completate: " << todoList.getUncompletedCount() << endl;
            }
            else
                cout << "Nessuna task presente. Digita add-task per aggiungerne una nuova" << endl;
        }
        else if(command == "listcompleted") {
            vector<Task> completed = todoList.getCompletedTasks();
            if (!completed.empty()) {
                cout << "task completate:" << endl;
                for (const auto &task: completed) {
                    cout << "- " << task.toString() << endl;
                }
            }
            else{
                cout<<"non ci sono task completate"<<endl;
            }
        }
        else if(command == "listuncompleted"){
            vector<Task> uncompleted = todoList.getUncompletedTasks();
            if (!uncompleted.empty()) {
                cout << "task non completate:" << endl;
                for (const auto &task: uncompleted) {
                    cout << "- " << task.toString() << endl;
                }
            }
            else{
                cout<<"non ci sono task non completate"<<endl;
            }
        }
        else if (command == "important") {
            string title;
            cout << "Titolo task da impostare come importante: " << endl;
            getline(cin, title);
            todoList.markTaskImportant(title);
            todoList.saveToFile(fileName);
        }
        else if (command == "notimportant") {
            string title;
            cout << "Titolo task da impostare come non importante: " << endl;
            getline(cin, title);
            todoList.markTaskNotImportant(title);
            todoList.saveToFile(fileName);
        }
        else if (command == "completed") {
            string title;
            cout << "Titolo task da completare: " << endl;
            getline(cin, title);
            todoList.markTaskComplete(title);
            todoList.saveToFile(fileName);
        }
        else if (command == "remove") {
            string title;
            cout << "Titolo task da rimuovere: " << endl;
            getline(cin, title);
            todoList.removeTask(title);
            todoList.saveToFile(fileName);
        }
        else if (command == "edit") {
            string oldTitle;
            cout << "Titolo della task da modificare: ";
            getline(cin, oldTitle);

            Task* taskToEdit = todoList.getTask(oldTitle);
            if (!taskToEdit) {
                cout << "Nessuna task trovata con questo titolo." << endl;
            } else {
                string newTitle, newDescription, newDate;

                cout << "Nuovo titolo: ";
                getline(cin, newTitle);

                cout << "Nuova descrizione: ";
                getline(cin, newDescription);

                cout << "Nuova data di scadenza (DD-MM-AAAA, o premi INVIO per lasciare vuoto): ";
                getline(cin, newDate);

                try {
                    todoList.editTask(oldTitle, newTitle, newDescription, newDate);
                    todoList.saveToFile(fileName);
                    cout << "Task modificata con successo!" << endl;
                } catch (const invalid_argument& e) {
                    cout << "Errore: " << e.what() << endl;
                }
            }
        }
        else if (command == "search") {
            cout << "Inserisci parola chiave: ";
            string keyword;
            getline(cin, keyword);

            vector<Task> risultati = todoList.searchTasks(keyword);
            if (risultati.empty()) {
                cout << "Nessuna task trovata con la parola chiave: " << keyword << endl;
            } else {
                cout << "Task trovate:" << endl;
                for (const auto &task: risultati) {
                    cout << "- " << task.getTitle() << " (" << task.getDescription() << ")" << endl;
                }
            }
        }
        else if (command == "rename") {
            string newName;
            cout << "Nuovo nome per la lista: ";
            getline(cin, newName);

            if (fs::exists(fileName)) {
                string newFileName = basePath + newName + ".txt";
                fs::rename(fileName, newFileName);  // <-- Rinomina il file
                cout << "Lista rinominata da \"" << listName << "\" a \"" << newName << "\"" << endl;

                listName = newName;
                fileName = newFileName;
                todoList.setName(newName);
            } else {
                cout << "Errore: il file originale non esiste, impossibile rinominare." << endl;
            }
        }
        else if (command == "switch") {
            string newListName;
            cout << "Inserisci il nome della lista a cui passare: ";
            getline(cin, newListName);

            string newFileName = basePath + newListName + ".txt";

            todoList.saveToFile(fileName);

            listName = newListName;
            fileName = newFileName;

            todoList = TodoList(newListName);
            todoList.loadFromFile(fileName);

            cout << "Sei passato alla lista: " << listName << endl;
        }
        else if (command == "quit") {
            break;
        }
        cout << "\n";
    }

    return 0;
}
