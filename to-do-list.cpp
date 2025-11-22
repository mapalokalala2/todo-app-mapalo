#include <iostream>
#include <vector>// gives us access to the vectors library
#include <string>
#include <fstream>
#include <limits>

using namespace std;
struct task{
    string task_description;
    bool is_completed;
};
// this is a global constant for the name of the file.
//this is so we dont write it wrong in any point of the program.
const string FILENAME = "task.txt";


//function decluration starts
int main_menu(const vector<task>& tasks);
void pause_execution();
void load_tasks(vector<task>& tasks);
void add_task(vector<task>& tasks);
void view_tasks(const vector<task>& tasks);
void mark_task_as_completed(vector<task>& tasks);
void delete_task(vector<task>& tasks);
void save_data(const vector<task>& tasks);
//function declaration ends

int main(){

    vector<task> tasks;// this will be our list of tasks. i have used vectors because vectors are easy to manipulate
    load_tasks(tasks);
    int choice = 0;
    while (true){
        choice = main_menu(tasks);

        switch (choice){
            case 1:
            system("cls");
            add_task(tasks);
            break;
            case 2:
            system("cls");
            view_tasks(tasks);
            break;
            case 3:
            system("cls");
            mark_task_as_completed(tasks);
            break;
            case 4:
            system("cls");
            delete_task(tasks);
            break;
            case 5:
            system("cls");
            save_data(tasks);
            system("cls");
            cout << "THANK YOU FOR USING YOUR TO DO LIST";
            exit(0);
            break;
        }
    }
    return 0;
}
void pause_execution(){
    cout << "\n\nPress Enter to continue \n ";
    if(cin.fail()){
        cin.clear();
    }
    cin.get();
}

int main_menu(const vector<task>& tasks){
    system("cls");
    int choice;
    string header = "=====================\n";
    while(true){// loop infinitly untill we get a valid input
    system("cls");
    cout << header << "     TO DO LIST   \n" << header
         << "[1] Add Task \n"
         << "[2] View Tasks \n"
         << "[3] Mark Task as Completed\n"
         << "[4] Delete task \n"
         << "[5] Exit \n"
         << "\nYOU HAVE ["<< tasks.size() << "] TASKS \n";
    cout << "pick an option (1-5): \n";
    cin >> choice;
     if (cin.fail()) {
            cout << "\nInvalid input. Please enter a number.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
            pause_execution();
            system("cls");
        } else if (choice >= 1 && choice <= 5) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice; // Valid input, return it

        } else {
            cout << "\nInvalid choice. Please enter a number between 1 and 5.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause_execution();
            system("cls");
        }
    }
}

void load_tasks(vector<task>& tasks){
    ifstream readFile(FILENAME); //opens the file if it exist. if it does not, it creats
    if(readFile.is_open()){
        string description;
        string status;
        while(getline(readFile, description, '|')){// the '|' is a delimiter. it is used to pause or stop reading
            getline(readFile,status);

            task task_obj;
            task_obj.task_description = description;

            if( status == "1"){//converts the status string ti booleon
                task_obj.is_completed = true;
            }else{
                task_obj.is_completed = false;
            }
            tasks.push_back(task_obj);
        }
        readFile.close();
    }
}

void add_task(vector<task>& tasks){
    system("cls");
    string description;
    cout << "Enter the task description: \n";
    getline(cin >> ws, description);

    task new_task;
    new_task.task_description = description;
    new_task.is_completed = false;

    tasks.push_back(new_task);
    cout << "Task added successfully!";
    pause_execution();
}

void view_tasks(const vector<task>& tasks){
    if(tasks.empty()){
        cout << "You do not have any tasks. \n";
        return;//closes the function
    }

    cout<<"----------YOUR TASKS-----------\n";
    for(int i = 0; i < tasks.size(); i++){
        string status = tasks[i].is_completed ? " |Done" : " | Not Done";
        cout << i + 1 << ". " << tasks[i].task_description<<" "<< status << endl;
    }
    pause_execution();
}

void mark_task_as_completed(vector<task>& tasks){

    view_tasks(tasks);
    int task_number;
    while(true){
        //clearing the input buffer just incase
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nWHICH TASK WOULD YOU LIKE TO MARK AS COMPLETED? \n";
        cin >> task_number;
        if(task_number >= 1 && task_number <= tasks.size()){
            tasks[task_number - 1].is_completed = true;
            cout << "Task marked as completed! \n";
            break;
        }else{
            cout << "Invalid task number. \n";
        }
    }
}

void delete_task(vector<task>& tasks){
    view_tasks(tasks);
    int task_number;
    while(true){
        cout << "\nWHICH TASK WOULD YOU LIKE TO DELETE? \n";
        cin >> task_number;
        if(task_number >= 1 && task_number <= tasks.size()){
            tasks.erase(tasks.begin() + (task_number - 1));
            cout << "Task deleted successfully! \n";
        break;
        }else{
            cout << "Invalid task number. Try again. \n";
        }
    }
}

void save_data(const vector<task>& tasks){
    ofstream outFile(FILENAME); // Open file for writing
    if (outFile.is_open()) {
        for(int i = 0; i < tasks.size(); i++){
            outFile << tasks[i].task_description << "|" << tasks[i].is_completed << endl;
        }
        outFile.close();
    }else{
        cout << "Error: Could not save task." <<endl;
    }
    cout << "Data saved successfully.... ";
    pause_execution();
}

