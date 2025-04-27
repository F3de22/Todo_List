#include "TodoList.h"

string TodoList::getName() const{
    return name;
}

void TodoList::setName(const string& newName) {
    name = newName;
}

void TodoList::addTask(const Task& task) {
    tasks.push_back(task);
}

void TodoList::removeTask(const string& taskTitle) {
    tasks.erase(remove_if(tasks.begin(), tasks.end(),
                          [&taskTitle](const Task& task)
                          {return task.getTitle() == taskTitle;}), tasks.end());
}

Task* TodoList::getTask(const string& taskTitle) {
    for (auto& task : tasks) {
        if (task.getTitle() == taskTitle) {
            return &task;
        }
    }
    return nullptr;
}

vector<Task> TodoList::searchTasks(const string &keyword) {
    vector<Task> foundTasks;
    for (const auto& task : tasks) {
        if (task.getTitle().find(keyword) != string::npos || task.getDescription().find(keyword) != string::npos) {
            foundTasks.push_back(task);
        }
    }
    return foundTasks;
}

void TodoList::markTaskComplete(const string& taskTitle) {
    Task* task = getTask(taskTitle);
    if (task) {
        task->markComplete();
    }
}

void TodoList::markTaskImportant(const string& taskTitle) {
    Task* task = getTask(taskTitle);
    if (task) {
        task->markImportant();
    }
}

void TodoList::markTaskNotImportant(const string& taskTitle) {
    Task* task = getTask(taskTitle);
    if (task) {
        task->markNotImportant();
    }
}

int TodoList::getCompletedCount() const {
    int count = 0;
    for (const auto& task : tasks) {
        if (task.isCompleted()) {
            ++count;
        }
    }
    return count;
}

int TodoList::getUncompletedCount() const {
    int count = 0;
    for (const auto &task: tasks) {
        if (!task.isCompleted()) {
            ++count;
        }
    }
    return count;
}

const vector<Task>& TodoList::getAllTasks() const {
    return tasks;
}

void TodoList::editTask(const string& oldTitle, const string& newTitle, const string& newDescription, const string& newDate) {
    Task* task = getTask(oldTitle);
    if (!task) {
        cerr << "Task non trovata con titolo: " << oldTitle << endl;
        return;
    }
    try {
        task->setTitle(newTitle);
        task->setDescription(newDescription);
        task->setExpirationDate(newDate);
    } catch (const invalid_argument& e) {
        cerr << "Errore durante la modifica: " << e.what() << endl;
    }
}

void TodoList::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Errore apertura file per scrittura" << endl;
        return;
    }

    file << "# " << name << endl;
    for (const auto& task : tasks) {
        file << task.toString() << endl;
    }

    file.close();
}

void TodoList::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "File non trovato. Verra' creata una nuova lista vuota." << endl;
        return;
    }

    tasks.clear();
    string line;

    if (getline(file, line) && line.rfind("# ", 0) == 0) {
        name = line.substr(2);
    }

    while (getline(file, line)) {
        tasks.push_back(Task::toTask(line));
    }

    file.close();
}


