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
const string NAME = "name.txt";


//function decluration starts
int main_menu(const vector<task>& tasks);
void pause_execution();
void load_tasks(vector<task>& tasks);
void add_task(vector<task>& tasks);
void view_tasks(const vector<task>& tasks);
void mark_task_as_completed(vector<task>& tasks);
void delete_task(vector<task>& tasks);
void save_data(const vector<task>& tasks);
void save_name(const string& name);
string get_name();
void settings_menu(string& name);

//function declaration ends

int main(){
    string name = get_name();
    if(name.empty()){
        cout << "welcome! It seems your new here.\n";
        cout << "Please enter your name: ";
        getline(cin, name);
        save_name(name);
    }
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
            settings_menu(name);
            break;
            case 6:
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
    cin.get();
}

int main_menu(const vector<task>& tasks){
    system("cls");
    int choice;
    string header = "=====================\n";
    while(true){// loop infinitly untill we get a valid input
    system("cls");
    cout << header << "     TO DO LIST   \n" << header 
         << "Welcome " << get_name() << '\n'
         << "[1] Add Task \n"
         << "[2] View Tasks \n"
         << "[3] Mark Task as Completed\n"
         << "[4] Delete task \n"
         << "[5] setting \n"
         << "[6] Exit\n"
         << "\nYOU HAVE ["<< tasks.size() << "] TASKS \n";
    cout << "pick an option (1-5): \n";
    cin >> choice;
     if (cin.fail()) {
            cout << "\nInvalid input. Please enter a number.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
            pause_execution();
            system("cls");
        } else if (choice >= 1 && choice <= 6) {
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

            if( status == "1"){//converts the status string to booleon
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
        cout << "Data saved successfully.... ";
    }else{
        cout << "Error: Could not save task." <<endl;
    }
    pause_execution();
}

string get_name(){
    ifstream readFile(NAME);
    string name;
    if(readFile.is_open()){
        getline(readFile, name);
        readFile.close();
    }
    return name;
}

void save_name(const string& name){
    ofstream outFile(NAME);
    if(outFile.is_open()){
        outFile << name ;
        outFile.close();
    }
}

void settings_menu(string& name){
    int choice;
    
    while(true){
        cout << "-------------Settings-------------\n";
        cout << "[1] Change Name\n"
             << "[2] Back to Main Menu\n"
             << "Enter choice: ";
        cin >> choice;
          if (cin.fail()) {
            cout << "\nInvalid input. Please enter a number.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
            pause_execution();
            system("cls");
        } else if (choice >= 1 && choice <= 2) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        } else {
            cout << "\nInvalid choice. Please enter a number.\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause_execution();
            system("cls");
        }

        switch (choice){
        case 1:
            system("cls");
            cout << "Enter your name : ";
            getline(cin, name);
            save_name(name);
            cout << "Name Successfully Saved";
            pause_execution();
            break;
        case 2:
            return;
            break;
        default:
            break;
        }
    }
}