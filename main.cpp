#include <iostream>
#include <vector>
#include <string>
#include <limits>

// Useful for cross-platform
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    // Assume POSIX
    std::cout << "\033[2J\033[1;1H";
#endif
}

bool readInteger(int& num) {
    std::cout << "Please enter an integer: ";
    std::cin >> num;

    if (std::cin.fail()) {
        clearScreen();
        std::cout << "Invalid input type\n\n";
        std::cin.clear(); // Clear the fail state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any remaining characters in the input buffer
        return false;
    }

    return true;
}


class todoList{
private:
    std::vector<std::string> taskList;
public:
    todoList(){
        taskList = {};
    }

    void addTask(const std::string& task){
        clearScreen();
        std::cout << "Task added: " << task << "\n\n";
        taskList.push_back(task);
    }

    void removeTask(int index){
        clearScreen();
        if(taskList.empty()){
            std::cout << "Todo list empty\n\n";
        } else {
            if(index < 0 || index >= taskList.size()){
                std::cout << "Invalid index\n\n";
            } else {
                std::cout << "Task removed: " << taskList[index] << "\n\n";
                taskList.erase(taskList.begin() + index);
            }
        }
    }

    std::string toString(){
        std::string output;
        if(taskList.empty()){
            output = "Todo list empty\n";
        } else {
            for(int i = 0; i < taskList.size(); i++){
                output += std::to_string(i) + ": " + taskList[i] + "\n";
            }
        }
        return output;
    }

    void printMenu(){
        std::cout << "=== Menu ===\n";
        std::cout << "1: Add Task\n";
        std::cout << "2: Remove Task\n";
        std::cout << "3. Quit\n";
        std::cout << "\n";
        std::cout << "=== Current List ===\n";
        std::cout << toString() << "\n";
    }
};

int main() {
    todoList todoList;
    std::string task;
    int input;

    clearScreen(); // clear screen before starting

    do {
        todoList.printMenu();

        // Loop menu until valid input.
        while (!readInteger(input)) {todoList.printMenu();}

        switch(input){
            case 1:
                clearScreen();
                std::cout << "Input task: ";
                std::getline(std::cin >> std::ws, task); // Read the whole line including spaces
                todoList.addTask(task);
                break;
            case 2:
                clearScreen();
                // kind of redundant
                if(todoList.toString() == "Todo list empty\n"){
                    std::cout << "Todo list empty\n\n";
                    break;
                } else {
                    std::cout << todoList.toString() << std::endl;

                    int index;
                    // Loop until valid input
                    while (!readInteger(index)) {
                        std::cout << todoList.toString() << std::endl;
                    }
                    todoList.removeTask(index);
                    break;
                }
            case 3:
                std::cout << "Exiting...\n\n";
                return 0;
            default:
                clearScreen();
                std::cout << "Invalid Choice\n\n";
                break;
            }
        }
    while(true);
}