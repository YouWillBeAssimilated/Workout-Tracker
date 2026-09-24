#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <filesystem>
#include <iomanip>

using namespace std;

struct exercise {
    string exName;
    string muscleGroup;
    string equipment;
    int sets;
    string reps;
    float weight;
};

class User {
public:
    string name;
    vector<vector<exercise>> days = {};
    User(string const& a) { name = a; };
    ~User() {};

private:
    string role;
};

void addNewUser(vector<User>&, string);
void editRoutine(User, string);
void newRoutine(User, string);
void viewRoutine(User, string);
int menu();
void readUsers(vector<User>&, ifstream &);
void loadRoutine(User&, string);
void removeUser(vector<User>&, string);

int main() {

    vector<User> users = {};
    int userChoice;
    string input, name;
    int index = -1;
    bool userFound = false;

    ifstream usersFile("users.txt");
    readUsers(users, usersFile);
    usersFile.close();


    cout << "What is the user's name: ";
    getline(cin, input);
    name = input;
    name += ".txt";
    auto it = find_if(users.begin(), users.end(), [&](const User& u) { return u.name == input; });
    if (it != users.end()) {
        index = distance(users.begin(), it);
        loadRoutine(users[index], name);
    }
    else {
        cout << "User not found! Add new user? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == 'y' || choice == 'Y') {
            addNewUser(users, input);
            cout<<"New user added! Please create a new routine.\n";
            index = users.size() - 1; 
            cout<<index<<endl<<endl;
            loadRoutine(users[index], name);
            
     
            }
    }


    do{
        
        
        //cout << "What is the user's name: ";
        userChoice=menu();
            

        switch (userChoice) {
            case 1: {
                
                    cout << "What is the user's name: ";
                    getline(cin, input);
                    name = input;
                    name += ".txt";
                    
                    auto it = find_if(users.begin(), users.end(), [&](const User& u) { return u.name == input; });
                    if (it != users.end()) {
                        cout<<"\nUser found!\n";
                        index = distance(users.begin(), it);
                        loadRoutine(users[index], name);
                        }
                    else{char choice;
                        cout << "User not found, would you like to create a new user? (y/n): ";
                        cin >> choice;
                        cin.ignore();
                        if (choice == 'y' || choice == 'Y') {
                            addNewUser(users, input);
                            index = users.size() - 1;
                        }}
                        break;
            }
            case 2: {
                    viewRoutine(users[index], name);  
                    break;
            }
            case 3: {
                    newRoutine(users[index], name);
                    break;
            }   
            case 4: {
                    editRoutine(users[index], name);
                    break;
            }
            case 5: {
        
                    cout << "What is the user's name: ";
                    getline(cin, input);
                    name = input;
                    name += ".txt";

                    filesystem::path filepath = name;
                    if (filesystem::exists(filepath)) {
                        filesystem::remove(filepath);
                        cout << "User workout deleted successfully.\n";
                    }
                    else {
                        cout << "User workout file does not exist.\n";
                    }
                    break;
            }
            case 6: {
                    cout << "What is the new user's name: ";
                    getline(cin, input);
                    addNewUser(users, input);
                    index = users.size() - 1;
                    name = input + ".txt";
                    break;
            }
            case 7: {
                    cout << "What is the user's name: ";
                    getline(cin, input);
                    removeUser(users, input);
                    break;
            }
            case 8: {
                    exit(0);
                    break;
            }
            }

    users.clear();
    ifstream usersFile("users.txt");
    readUsers(users, usersFile);
    usersFile.close();

	} while (true);

    
    return 0;
}

void readUsers(vector<User> & users, ifstream &infile){
    string user;
    while(getline(infile, user)){
        users.emplace_back(user);
    }
}

int menu(){
    int choice; 
    bool pass = true;

    do{
    cout<<"What would you like to do? \n\n";
    cout<<"1. Change user\n";
    cout<<"2. View user workout\n";
    cout<<"3. Create new user workout\n";
    cout<<"4. Modify user workout\n";
    cout<<"5. Delete user workout\n";
    cout<<"6. Add new user\n";
    cout<<"7. Remove user\n";
    cout<<"8. Exit\n\n  Choice: ";
    cin>>choice;
    cin.ignore();
    if(choice>8||choice<1){cout<<"Invalid choice, please try again\n"; pass=false;}
    }while(pass!=true);

    return choice;
}

void newRoutine(User user, string name) {
    ofstream file(name, ios::app);
    if (!file.is_open()) {
        cerr << "Error opening routine file!\n";
        return;
    }

    int dayNumber;
    int exerciseCount;
    cout << "Day number: ";
    cin >> dayNumber;
    cout << "Number of exercises: ";
    cin >> exerciseCount;
    cin.ignore();

    file << "Day " << dayNumber << "\n";
    for (int i = 0; i < exerciseCount; i++) {
        exercise currentExercise;
        cout << "Exercise name: ";
        getline(cin, currentExercise.exName);
        cout << "Muscle group: ";
        getline(cin, currentExercise.muscleGroup);
        cout << "Equipment: ";
        getline(cin, currentExercise.equipment);
        cout << "Sets: ";
        cin >> currentExercise.sets;
        cin.ignore();
        cout << "Reps: ";
        getline(cin, currentExercise.reps);
        cout << "Weight: ";
        cin >> currentExercise.weight;
        cin.ignore();
        cout<<endl;

        file << currentExercise.exName << ','
             << currentExercise.muscleGroup << ','
             << currentExercise.equipment << ','
             << currentExercise.sets << ','
             << currentExercise.reps << ','
             << currentExercise.weight << "\n";
    }
}

void viewRoutine(User user, string name) {
    loadRoutine(user, name);
	
	for (int i = 0; i < user.days.size(); i++) {
		cout << "\nDay " << i + 1 << ":" << endl;
        cout<<setw(40)<<left<<"Name: " << setw(30)<<left<<"Muscle Group: " << setw(20)<<left<< "Equipment: " << setw(10)<<left<<"Sets: " <<setw(10)<<left<<"Reps: " << setw(5)<<left<<"Weight: " << endl;
		for (const auto& ex : user.days[i]) {
            
			cout << setw(40)<<left<<ex.exName << setw(30)<<left<<ex.muscleGroup << setw(20)<<left<< ex.equipment <<setw(10)<<left<< ex.sets << setw(10)<<left<<ex.reps  << setw(5)<<left<<ex.weight << endl;
		}
	}
    
}

void editRoutine(User user, string name) {
    auto daySize = user.days.size();
    

    cout<<"Which day would you like to edit? (1-"<<daySize<<"): ";
    int dayChoice;
    cin>>dayChoice;
    cin.ignore();
    auto exSize = user.days[dayChoice-1].size();
    cout<<"Which exercise would you like to edit? (1-"<<exSize<<"): ";
    int exChoice;
    cin>>exChoice;
    cin.ignore();
    cout<<"What would you like to change?\n";
    cout<<"1. Name\n";
    cout<<"2. Muscle Group\n";
    cout<<"3. Equipment\n";
    cout<<"4. Sets\n";
    cout<<"5. Reps\n";
    cout<<"6. Weight\n";
    int changeChoice;
    cin>>changeChoice;
    cin.ignore();
    switch(changeChoice){
        case 1:
            cout<<"Enter new name: ";
            getline(cin, user.days[dayChoice-1][exChoice-1].exName);
            break;
        case 2:
            cout<<"Enter new muscle group: ";
            getline(cin, user.days[dayChoice-1][exChoice-1].muscleGroup);
            break;
        case 3:
            cout<<"Enter new equipment: ";
            getline(cin, user.days[dayChoice-1][exChoice-1].equipment);
            break;
        case 4:
            cout<<"Enter new sets: ";
            cin>>user.days[dayChoice-1][exChoice-1].sets;
            cin.ignore();
            break;
        case 5: 
            cout<<"Enter new reps: ";
            getline(cin, user.days[dayChoice-1][exChoice-1].reps);
            break;
        case 6:
            cout<<"Enter new weight: ";
            cin>>user.days[dayChoice-1][exChoice-1].weight;
            cin.ignore();
            break;

}
}

void loadRoutine(User &user, string name) {
    ifstream file(name);
	if (!file.is_open()) {
        ofstream file(name);
        file.close();
        cout<<"New user file created, please create routine.\n";
        newRoutine(user, name);
		return;
	}

    user.days.clear();
    vector<exercise> currentDay;
    bool hasDayHeader = false;
    string line;
    while (getline(file, line)) {
        if (line.empty() || line==" "||line=="\n"||line=="\r\n"||line=="\r") {
            cout << "Empty Workout file, please create a new routine.\n";
            break;
        }

        // A header such as "DAY 1" starts a new workout day.
        if (line.rfind("DAY ", 0) == 0 || line.rfind("Day ", 0) == 0 || line.rfind("day ", 0) == 0) {
            if (hasDayHeader) {
                user.days.push_back(currentDay);
                currentDay.clear();
            }
            hasDayHeader = true;
            continue;
        }

        exercise tempEx{};
        stringstream ss(line);
        int index = 0;
        string item;
        while (getline(ss, item, ',')) {
            switch (index) {
            case 0: tempEx.exName = item; break;
            case 1: tempEx.muscleGroup = item; break;
            case 2: tempEx.equipment = item; break;
            case 3: tempEx.sets = stoi(item); break;
            case 4: tempEx.reps = item; break;
            case 5: tempEx.weight = stoi(item); break;
            }
            index++;
        }

        if (index == 6) {
            currentDay.push_back(tempEx);
        }
    }

    if (!currentDay.empty() || hasDayHeader) {
        user.days.push_back(currentDay);
    }
    file.close();
}

void addNewUser(vector<User> &users, string name) {
    users.emplace_back(name);
    ofstream outfile("users.txt", ios::app);
    if (outfile.is_open()) {
        outfile << name << endl;
        outfile.close();
    } else {
        cerr << "Error opening users file for writing!" << endl;
    }
    
}

void removeUser(vector<User> &users, string name) {
    auto it = find_if(users.begin(), users.end(), [&](const User& u) { return u.name == name; });
    if (it != users.end()) {
        users.erase(it);
        ofstream outfile("users.txt");
        if (outfile.is_open()) {
            for (const auto& user : users) {
                outfile << user.name << endl;
            }
            outfile.close();
        } else {
            cerr << "Error opening users file for writing!" << endl;
        }
        cout << "User removed successfully." << endl;
    } else {
        cout << "User not found." << endl;
    }
}
