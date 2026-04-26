#include<iostream>
#include<string>
using namespace std;

// Constants
const int MAX_USERS = 100;
const int MAX_SKILLS = 15;
const int MAX_REQUESTS = 10;
const int MAX_NOTIFICATIONS = 10;

// Global variables
int user_count = 5; // Starting with 5 pre-existing users
int current_user_index = -1; // Index of currently logged in user


// 1. Person: Abstract Base Class
class Person{
protected:
    string name;
    string email;
public:
    Person(){}
    //Getters & Setters
    string getname(){
        return name;
    }
    string getemail(){
        return email;
    }
    void setname(string n){
        name  = n;
    }
    void setemail(string e){
        email = e;
    }
    virtual void displayInfo() = 0; // Pure Virtual Function
    virtual ~Person(){}
};

// 2. Skill: Represents individual skills
class Skill{
protected:
    string skill_name;
    string description;
    string level;
public:
    // Constructor Overloading
    Skill(){}
    Skill(string skilln, string des, string l){
        skill_name = skilln;
        description = des;
        level = l;
    }
    Skill(const Skill &obj){
        skill_name = obj.skill_name;
        description = obj.description;
        level = obj.level;
    }
    // Getters
    string getskillname(){
        return skill_name;
    }
    string getlevel(){
        return level;
    }
    void display(){
        cout<<"Skill Name: "<<skill_name<<endl;
        cout<<"Description: "<<description<<endl;
        cout<<"Level: "<<level<<endl;
    }
    Skill& operator=(const Skill& s){
        skill_name = s.skill_name;
        description = s.description;
        level = s.level;
        return *this;
    }
    bool operator==(const Skill& skill) {
        // Check if both skill names are same
        if (skill_name == skill.skill_name && level == skill.level) {
            return true;
        } else {
            return false;
        }
    }
};

// Abstract Base Class
class Request{
protected:
    string requesterName;
    string skillName;
    string message;
public:
    Request(string rname, string sname, string msg){
        requesterName = rname;
        skillName = sname;
        message = msg;
    }
    // Pure Virtual Functions
    virtual void processRequest() = 0;
    virtual string getStatus() = 0;
    virtual void display() = 0;
    virtual ~Request(){}
};

// Inherited from Request
class SkillRequest: public Request{
private:
    string status;
public:
    SkillRequest(): Request("", "", "") {
        status = "Pending";
    }
    SkillRequest(string rname, string sname, string msg):
    Request(rname, sname, msg){
        status = "Pending";
    }
    // Setter & Getter
    void setStatus(string st){
        status = st;
    }
    // Overriding all virtual functions
    void display() override {
        cout<<"Requester Name: "<<requesterName<<endl;
        cout<<"Skill Name: "<<skillName<<endl;
        cout<<"Message: "<<message<<endl;
        cout<<"Status: "<<status<<endl;
    }
    string getStatus() override {
        return status;
    }
    void processRequest() override {
        int choice;
        cout<<"Request from: "<< requesterName<<" to learn '"<<skillName<<"'\n";
        cout<<"Message: "<<message<<endl;
        do{
            cout<<"1. Approve\n2. Reject\nEnter your preference: ";
            cin >> choice;
            if (choice == 1) {
                status = "Approved";
            }
            else if(choice == 2) {
                status = "Rejected";
            }
            else{
                cout<<"Invalid Choice. Try Again..."<<endl;
            }
        } while(choice != 1 && choice != 2);
        cout<<"Request processed. Status: "<<status<<endl;
    }
};

// Derived from Person (System users with skills and requests)
class User: public Person{
private:
    string username;
    string password;

    Skill skills[MAX_SKILLS];  // Composition (User Has skills)
    int skill_count;

    SkillRequest* receivedRequests[MAX_REQUESTS]; // Aggregation (User references requests)
    int request_count;
public:
    User(){
        skill_count = 0;
        request_count = 0;
    }
    User(string name, string email, string username, string password){
        this->name=name;
        this->email=email;
        this->username=username;
        this->password=password;
        skill_count = 0;
        request_count = 0;
    }
    User(string n, string e){
        setname(n);
        setemail(e);
        skill_count  = 0;
        request_count = 0;
    }
    // Setters & Getters
    void setusername(string uname){
        username = uname;
    }
    void setpassword(string pass){
        password = pass;
    }
    string getusername(){
        return username;
    }
    string getpassword(){
        return password;
    }

    // METHODS TO MANAGE SKILLS
    // 1. Adds skills to user's own skills
    void addskills(Skill s){
        if(skill_count<MAX_SKILLS){
            skills[skill_count++] = s;
        }
        else{
            cout<<"Skills limit reached.\n";
        }
    }
    // 2. Display user's own skills
    void displayOwnSkills(){
        cout<<"Your Skills:\n";
        for(int i=0; i<skill_count; i++){
            skills[i].display();
        }
    }
    // 3. Check whether the user have that particular skill or not
    bool checkskill(string skill_name){
        for(int i=0; i<skill_count; i++){
            if(skills[i].getskillname() == skill_name){
                return true;
            }
        }
        return false;
    }
    // 4. Display Skill by name if it exists in the user's skills
    void displaySkillByName(string name){
        for(int i=0; i< skill_count; i++){
            if(skills[i].getskillname() == name){
                cout<<"Skill found in this user: \n";
                skills[i].display();
            }
        }
    }
    // 5. Searches the list of users and displays those who have the specified skill
    void searchSkillInUser(User users[], int user_count, string skillname){
        bool found = false;
        cout<<"Searching for "<<skillname<<" skill..."<<endl;
        for(int i=0; i<user_count; i++){
            if(users[i].checkskill(skillname)){
                cout<<"This skill is found in user: "<<users[i].getname()<<endl;
                users[i].displaySkillByName(skillname);
                found  = true;
            }
        }
        if(!found){
            cout<<"No user found with this skill!\n";
        }
    }
    // 6. Remove skill by name
    void removeSkill(string sname){
        for(int i=0; i<skill_count; i++){
            if(skills[i].getskillname() == sname){
                // To fill the gap left by the removed skill.
                for(int j=i; j<skill_count-1; j++){
                    skills[j] = skills[j + 1];
                }
                skill_count--;
                cout<<"Skill Removed Successfully!\n";
                return;
            }
        }
        cout<<"Skill not found!\n";
    }
    // Function overriding (from Person class)
    void displayInfo() override{
        cout<<"Name: "<<getname()<<endl;
        cout<<"Email: "<<getemail()<<endl;
        cout<<"Username: "<<username<<endl;
    }

    // METHODS TO MANAGE REQUESTS
    // 1. Add Requests
    void addrequest(SkillRequest* req){
        if (request_count < MAX_REQUESTS) {
            receivedRequests[request_count++] = req;
            cout << "Request added successfully.\n";
        } else {
            cout << "Maximum request limit reached.\n";
        }
    }
    // 2. Display Requests
    void displayrequests(){
        if (request_count == 0) {
            cout << "No requests received.\n";
            return;
        }
        cout << "Received Requests:\n";
        for (int i = 0; i < request_count; ++i) {
            cout << "Request No: " << (i + 1) << ":\n";
            receivedRequests[i]->display();
            cout<<endl;
        }
    }
};

User users[MAX_USERS]; // Global users array declaration
class Authentication{
public:
    Authentication(){}
    static int loginAttempts;
    static int getLoginAttempts(){
        return loginAttempts;
    }
    static bool validateLogin(User users[], int user_count, string uname, string pass){
        for(int i=0;i<user_count;i++){
            if(users[i].getusername()== uname && users[i].getpassword()== pass){
                return true;
            }
        }
        loginAttempts++;
        return false;
    }
    static bool register_user(User users[], int& user_count, string name, string email, string uname, string pass){
        for(int i=0;i<user_count;i++){
            if(users[i].getusername()==uname){
                return false;
            }
        }
        if(user_count<MAX_USERS){
            users[user_count].setname(name);
            users[user_count].setemail(email);
            users[user_count].setusername(uname);
            users[user_count].setpassword(pass);
            user_count++;
            return true;
        }
        return false;
    }
};

int Authentication::loginAttempts = 0;

class SkillManager{
public:
    static int total_skills_managed;

    static int get_totalSearches(){
        return total_skills_managed;
    }
    static void searchSkillInUsers(User users[], int userCount, string skillname) {
        total_skills_managed++;
        bool found = false;
        for (int i=0;i<userCount;i++){
            if (users[i].checkskill(skillname)){
                cout<<"User: "<<users[i].getname()<<" has skill: "<<skillname<<endl;
                users[i].displaySkillByName(skillname);
                found = true;
            }
        }
        if (!found){
            cout<<"Skill not found in any user.\n";
        }
    }
    friend void display_total_skills();
};

int SkillManager::total_skills_managed = 0;

// SkillManager Class's Friend Function Definition
void display_total_skills(){
    cout<<"Total Skill Searches: "<<SkillManager::total_skills_managed<<endl;
}

class RequestManager {
    SkillRequest total_requests[MAX_REQUESTS];
    int requests_count;
public:
    RequestManager(){
        requests_count=0;
    }
    void createRequest(string rname, string sname, string msg) {
        if (requests_count<MAX_REQUESTS) {
            total_requests[requests_count++]= SkillRequest(rname,sname,msg);
            cout<<"Request created.\n";
        }
        else{
            cout<<"Request limit reached.\n";
        }
    }
    // Method to Process Request
    void processRequest(int index) {
        if (index >= 0 && index<requests_count) {
            total_requests[index].processRequest(); // Calls the function "proceedRequest" defined in SkillRequest class
        } else {
            cout << "Invalid index.\n";
        }
    }
    // Method to display All requests
    void display_all_requests() {
        for (int i=0;i<requests_count;i++) {
            cout<<"Request "<<i+1<<":\n";
            total_requests[i].display();
            cout<<endl;
        }
    }
};

// Function to initialize sample data
void initializeSampleData() {
    // Initialize 5 sample users with skills
    users[0].setname("Aima Noor");
    users[0].setemail("aima@email.com");
    users[0].setusername("aima123");
    users[0].setpassword("pass123");
    users[0].addskills(Skill("Python Programming", "Advanced Python development", "Expert"));
    users[0].addskills(Skill("Data Analysis", "Statistical analysis and visualization", "Intermediate"));

    users[1].setname("Raniya Zubair");
    users[1].setemail("raniya@email.com");
    users[1].setusername("rania456");
    users[1].setpassword("pass456");
    users[1].addskills(Skill("Web Development", "Full-stack web development", "Advanced"));
    users[1].addskills(Skill("JavaScript", "Frontend and backend JavaScript", "Expert"));

    users[2].setname("Ahmad Ali");
    users[2].setemail("ahmad@email.com");
    users[2].setusername("ahmadl789");
    users[2].setpassword("pass789");
    users[2].addskills(Skill("Machine Learning", "ML algorithms and implementation", "Advanced"));
    users[2].addskills(Skill("Python Programming", "Python for ML and data science", "Expert"));

    users[3].setname("Rayyan Amjad");
    users[3].setemail("rayyan@email.com");
    users[3].setusername("amjad101");
    users[3].setpassword("pass101");
    users[3].addskills(Skill("Database Design", "SQL and NoSQL database design", "Expert"));
    users[3].addskills(Skill("System Administration", "Linux system administration", "Intermediate"));

    users[4].setname("Emama Khaliq");
    users[4].setemail("emama@email.com");
    users[4].setusername("emama202");
    users[4].setpassword("pass202");
    users[4].addskills(Skill("UI/UX Design", "User interface and experience design", "Advanced"));
    users[4].addskills(Skill("Graphic Design", "Visual design and branding", "Expert"));
}

// Function to display main menu
void displayMainMenu() {
    cout<<"\n*******SKILLSWAP SYSTEM*******\n";
    cout<<"MAIN MENU:"<<endl;
    cout<<"1. Login\n";
    cout<<"2. Register\n";
    cout<<"3. Exit\n";
    cout<<"Enter your choice: ";
}

// Function to display user menu after login
void displayUserMenu() {
    cout<<"\nMENU:\n";
    cout<<"1. View Profile\n";
    cout<<"2. Manage Skills\n";
    cout<<"3. View Notifications\n";
    cout<<"4. Search for a Skill\n";
    cout<<"5. Logout\n";
    cout<<"Enter your choice: ";
}

// Function to display manage skills menu
void displayManageSkillsMenu() {
    cout<<"\n***MANAGE SKILLS***\n";
    cout<<"1. View Skills\n";
    cout<<"2. Add Skill\n";
    cout<<"3. Remove Skill\n";
    cout<<"4. Back to Main Menu\n";
    cout<<"Enter your choice: ";
}

// Function to handle login
bool handleLogin() {
    string username, password;
    bool loginSuccess = false;
    
    do {
        cout << "\nLOGIN:\n";
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        
        if (Authentication::validateLogin(users, user_count, username, password)) {
            // Find the logged-in user's index
            for (int i = 0; i < user_count; i++) {
                if (users[i].getusername() == username) {
                    current_user_index = i;
                    break;
                }
            }
            cout << "Login successful! Welcome " << users[current_user_index].getname() << "!\n";
            loginSuccess = true;
        } else {
            cout << "Invalid credentials! Login attempts: " << Authentication::getLoginAttempts() << "\n";
            char retry;
            cout << "Do you want to try again? (y/n): ";
            cin >> retry;
            if (retry != 'y' && retry != 'Y') {
                break;
            }
        }
    } while (!loginSuccess);
    
    return loginSuccess;
}

// Function to handle registration
bool handleRegistration() {
    string name, email, username, password;
    
    cout << "\nREGISTRATION:\n";
    cout << "Enter full name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    
    if (Authentication::register_user(users, user_count, name, email, username, password)) {
        cout << "Registration successful! You can now login.\n";
        return true;
    } else {
        cout << "Registration failed! Username might already exist or user limit reached.\n";
        return false;
    }
}

// Function to handle skill management
void handleManageSkills() {
    int choice;
    do {
        displayManageSkillsMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                cout << "\nYOUR SKILLS:\n";
                users[current_user_index].displayOwnSkills();
                break;
            }
            case 2: {
                cout << "\nADD SKILL:\n";
                string skillName, description, level;
                cout << "Enter skill name: ";
                cin.ignore();
                getline(cin, skillName);
                cout << "Enter description: ";
                getline(cin, description);
                cout << "Enter level (Beginner/Intermediate/Advanced/Expert): ";
                getline(cin, level);
                
                Skill newSkill(skillName, description, level);
                users[current_user_index].addskills(newSkill);
                cout << "Skill added successfully!\n";
                break;
            }
            case 3: {
                cout << "\nREMOVE SKILL:\n";
                string skillName;
                cout << "Enter skill name to remove: ";
                cin.ignore();
                getline(cin, skillName);
                users[current_user_index].removeSkill(skillName);
                break;
            }
            case 4:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);
}

// Function to handle notifications
void handleNotifications() {
    int choice;
    cout << "\nView Notifications:\n";
    cout << "1. Sent Request Replies\n";
    cout << "2. Received Requests for Skill Swap\n";
    cout << "Enter your choice: ";
    cin >> choice;
    
    switch (choice) {
        case 1:
            cout << "\nSENT REQUEST REPLIES\n";
            cout << "Feature coming soon! Currently showing placeholder.\n";
            cout << "Your sent requests and their status will appear here.\n";
            break;
        case 2:
            cout << "\nRECIEVED SKILLSWAP REQUESTS\n";
            users[current_user_index].displayrequests();
            
            // Process requests if any exist
            int requestChoice;
            cout << "Enter request number to process (0 to skip): ";
            cin >> requestChoice;
            if (requestChoice > 0) {
                cout << "1. Accept\n2. Reject\nEnter choice: ";
                int action;
                cin >> action;
                if (action == 1) {
                    cout << "Request accepted! Skills will be exchanged.\n";
                } else if (action == 2) {
                    cout << "Request rejected.\n";
                }
            }
            break;
        default:
            cout << "Invalid choice!\n";
    }
}

// Function to handle skill search
void handleSkillSearch() {
    string skillName;
    cout << "\nSEARCH FOR A SKILL\n";
    cout << "Enter skill name to search: ";
    cin.ignore();
    getline(cin, skillName);
    
    // Use SkillManager to search for the skill
    SkillManager::searchSkillInUsers(users, user_count, skillName);
    
    // Ask if user wants to send a request
    char sendRequest;
    cout << "Do you want to send a skill swap request to any of these users? (y/n): ";
    cin >> sendRequest;
    
    if (sendRequest == 'y' || sendRequest == 'Y') {
        string targetUsername, message;
        cout << "Enter username of the person you want to send request to: ";
        cin >> targetUsername;
        cout << "Enter your message: ";
        cin.ignore();
        getline(cin, message);
        
        // Find target user and add request
        for (int i = 0; i < user_count; i++) {
            if (users[i].getusername() == targetUsername) {
                SkillRequest* newRequest = new SkillRequest(
                    users[current_user_index].getname(), 
                    skillName, 
                    message
                );
                users[i].addrequest(newRequest);
                cout << "Request sent successfully to " << users[i].getname() << "!\n";
                break;
            }
        }
    }
}

// Main function
int main() {
    // Initialize sample data
    initializeSampleData();
    
    int mainChoice;
    bool systemRunning = true;
    
    while (systemRunning) {
        displayMainMenu();
        cin >> mainChoice;
        
        switch (mainChoice) {
            case 1: {
                // Login
                if (handleLogin()) {
                    // User menu loop
                    int userChoice;
                    bool userLoggedIn = true;
                    
                    while (userLoggedIn) {
                        displayUserMenu();
                        cin >> userChoice;
                        
                        switch (userChoice) {
                            case 1:
                                cout << "\n****YOUR PROFILE****\n";
                                users[current_user_index].displayInfo();
                                break;
                                
                            case 2:
                                handleManageSkills();
                                break;
                                
                            case 3:
                                handleNotifications();
                                break;
                                
                            case 4:
                                handleSkillSearch();
                                break;
                                
                            case 5:
                                cout << "Logging out...\n";
                                current_user_index = -1;
                                userLoggedIn = false;
                                break;
                                
                            default:
                                cout << "Invalid choice! Please try again.\n";
                        }
                    }
                }
                break;
            }
            
            case 2:
                // Register
                handleRegistration();
                break;
                
            case 3:
                // Exit
                cout << "Thank you for using our SkillSwap System!\n";
                cout << "Total skill searches performed: ";
                display_total_skills();
                cout << "Total login attempts: " << Authentication::getLoginAttempts() << "\n";
                systemRunning = false;
                break;
                
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}
