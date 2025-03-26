#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;

class BoxFormatter {
public:
    string content;

    void formatContent(string content) {
        vector<string> lines;
        string line;
        istringstream iss(content);
        while (getline(iss, line)) {
            lines.push_back(line);
        }
        int maxLength = 0;
        string li;
        for (size_t i = 0; i < lines.size(); ++i) {
            //const auto&
            li = lines[i];
            maxLength = max(maxLength, static_cast<int>(li.length()));
        }
        int boxWidth = maxLength + 4; // Account for box edges
        // Top border
        cout << '+' << string(boxWidth, '-') << '+' << endl;
        // Content with borders
        for (size_t i = 0; i < lines.size(); ++i) {
            cout << "| " << lines[i] << string(maxLength - lines[i].length(), ' ') << " |" << endl;
        }
        // Bottom border
        cout << '+' << string(boxWidth, '-') << '+' << endl;
    }
};


class UserProfile {
private:
    string username;
    int questionsAsked;
    int answersGiven;

public:
    UserProfile() : questionsAsked(0), answersGiven(0) {}

    void setUsername(const string& uname) {
        username = uname;
    }

    const string& getUsername() const {
        return username;
    }

    int getQuestionsAsked() const {
        return questionsAsked;
    }

    void incrementQuestionsAsked() {
        questionsAsked++;
    }

    int getAnswersGiven() const {
        return answersGiven;
    }

    void incrementAnswersGiven() {
        answersGiven++;
    }

    void displayProfile() const {
        cout << "Username: " << username << endl;
        cout << "Number of questions asked: " << questionsAsked << endl;
        cout << "Number of answers given: " << answersGiven << endl;
    }
};

class LOGIN {
private:
    string username;

public:
    bool checkentry() {
        cout << "Enter username: ";
        cin >> username;
        string password;
        cout << "Enter password: ";
        cin >> password;

        ifstream file("user_data.txt");
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(' ');
            if (line.substr(0, pos) == username && line.substr(pos + 1) == password) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    const string& getUsername() const {
        return username;
    }
};

class UserSignUp {
public:
    private:
    string filename;

public:

    bool checkUsernameUnique(const string& username) {
        //ifstream file(filename);
        ifstream file("user_data.txt");
        string line;
        while (getline(file, line)) {
            string storedUsername = line.substr(0, line.find(' '));
            if (username == storedUsername) {
                file.close();
                return false; // Username already exists
            }
        }
        file.close();
        return true; // Username is unique
    }

    void signUp() {
        string username, password;
        while (true) {
            cout << "Enter username: ";
            cin >> username;
            if (checkUsernameUnique(username)) {
                cout << "Enter password: ";
                cin >> password;
                ofstream file("user_data.txt", ios_base::app);
                file << endl<<username << " " << password << endl;
                file.close();
                system("CLS");
                cout << "Sign up successful!\n";
                break;
            } 
			else {
                cout << "Username already exists. Please choose another username.\n";
            }
        }
    }
};


class QuestionManager 
{
private:
    string questionFile;
    string answerFile;
    static int lastQuestionId;
    BoxFormatter box;

public:
    void loadlastQuestionId() {
        ifstream file("questions.txt");
        string line;
        while (getline(file, line)) {
            int id;
            if (sscanf(line.c_str(), "Q%d:", &id) == 1 && id > lastQuestionId) 
			{
                lastQuestionId = id;
            }
        }
        file.close();
    }

    bool questionExists(const string& question) const {
        ifstream file("questions.txt");
        string line;
        while (getline(file, line)) {
            if (line.find(question) != string::npos) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    void addQuestion(const string& question, UserProfile& user) {
        loadlastQuestionId();
        if (questionExists(question)) {
            // cout << "The question already exists.\n";
            displayExistingAnswer(question);
            return;
        }

        lastQuestionId++; // Increment the ID
        ofstream outFile("questions.txt", ios::app);
        outFile << "Q" << lastQuestionId << ": " << question << endl;
        outFile.close();

        user.incrementQuestionsAsked();
    }
    void displayExistingAnswer(const string& question) 
	{
    ifstream readQuestion("questions.txt");
    string line;
    string qid;
    bool found = false;

    // Find the question ID corresponding to the given question
    while (getline(readQuestion, line)) 
	{
        string quest, id;
        size_t posq = line.find(' ');
        id = line.substr(0, posq);
        quest = line.substr(posq + 1);
        if (quest == question) {
            qid = id;
            found = true;
            break;
        }
    }
    readQuestion.close();

    if (!found) {
        cout << "Question not found." << endl;
        return;
    }

    ifstream readAnswer("answers.txt");
    while (getline(readAnswer, line)) {
        string Aid, answer;
        size_t posa = line.find(' ');
        Aid = line.substr(0, posa);
        if (Aid == qid) {
            size_t lastSpace = string::npos;
            for (size_t i = line.length() - 1; i >= posa; --i) {
                if (line[i] == ' ') {
                    lastSpace = i;
                    break;
                }
            }
            if (lastSpace != string::npos) {
                answer = line.substr(posa + 1, lastSpace - posa - 1); // Extract the answer portion
            } else {
                answer = line.substr(posa + 1); // If no space found after the question ID, take the whole line as the answer
            }
            /*cout << "Answer is:" << endl;
            box.formatContent(answer);*/
            // UPVOTE HERE
            displayAnswers(qid);
            break;
        }
    }

    readAnswer.close();

    if (!found) {
        cout << "No answers yet." << endl;
    }
}


    
    int stringToInt(const string& str) 
	    {
    		stringstream ss(str);
    		int result;
    		ss >> result;
    		return result;
		}
        
        
    string intToString(int num) 
	{
    	stringstream ss;
    	ss << num;
    	return ss.str();
	}
    

    void displayAnswers(const string& questionID) 
	{
    ifstream file("answers.txt");
    string line;
    vector<pair<int, string> > answers; // Store answers along with upvotes
    bool answerFound;
    while (getline(file, line)) {
        istringstream iss(line);
        string qid, answer;
        int upvotes;
        if (getline(iss, qid, ' ') && getline(iss, answer)) 
		{
            if (qid == questionID) {
                answerFound = true;
                answers.push_back(make_pair(upvotes, answer));
            }
        }
    }
    file.close();

    if (answers.empty()) {
        cout << "No answers yet." << endl;
        return;
    }

    cout << "Available Answers:" << endl;
    for (size_t i = 0; i < answers.size(); ++i) {
        cout << i + 1 << ". ";
		box.formatContent(answers[i].second);
		//cout<<" (Upvotes: " << answers[i].first << ")" << endl;
    }

    cout << "Enter the number of the answer you want to upvote (0 to cancel): ";
    int choice;
    cin >> choice;

    if (choice > 0 && choice <= answers.size()) {
        upvoteAnswer(answers[choice - 1].second);
    } else {
        cout << "Invalid choice or canceled." << endl;
    }
}

    void upvoteAnswer(const string& answer) {
    ifstream answersFile("answers.txt");
    ofstream tempFile("temp.txt");

    if (!answersFile.is_open() || !tempFile.is_open()) {
        cerr << "Error: Unable to open files." << endl;
        return;
    }

    string line;
    while (getline(answersFile, line)) 
	{
        if (line.find(answer) != string::npos) 
		{
            size_t pos = line.rfind(' '); // Find the position of the last space
            string upvoteStr = line.substr(pos + 1); // Extract upvote string
            int upvotes = stringToInt(upvoteStr); // Convert to integer
            upvotes++; // Increment upvotes
            line = line.substr(0, pos + 1) + intToString(upvotes); // Update the line with new upvotes
        }
        tempFile << line << endl;
    }
    

    answersFile.close();
    tempFile.close();

    // Copy and Replace
ofstream AnswersFile("answers.txt");
ifstream TempFile("temp.txt");
AnswersFile << TempFile.rdbuf(); // Copy contents of tempFile to answersFile
AnswersFile.close();
TempFile.close();
remove("temp.txt");

}
};

int QuestionManager::lastQuestionId = 0;

class AnswerClass {
public:
    void answerQuestionByID(const string& questionID, UserProfile& user) {
        ifstream questionsFile("questions.txt");
        ofstream answersFile("answers.txt", ios::app); // Append mode

        if (!questionsFile.is_open()) {
            cerr << "Error: Unable to open questions file." << endl;
            return;
        }

        if (!answersFile.is_open()) {
            cerr << "Error: Unable to open answers file." << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(questionsFile, line)) {
            string id, question;
            size_t pos = line.find(' ');
            id = line.substr(0, pos);
            question = line.substr(pos + 1);
            if (id == questionID) {
                found = true;
                cout << "Question is: " << question << endl;
                string answer;
                cout << "Your answer:";
                fflush(stdin);
                getline(cin, answer);
                answersFile << id << " ";
                answersFile << answer <<" "<<"0"<< endl;
                cout << "Answer recorded successfully." << endl;
                user.incrementAnswersGiven();
                break;
            }
        }

        if (!found) {
            cout << "Question with ID '" << questionID << "not found." << endl;
        }

        questionsFile.close();
        answersFile.close();
    }
};



int main() {
    int choice;
    LOGIN n;
    UserSignUp u;
    QuestionManager manager;
    AnswerClass answerClass;
    UserProfile user;
    string userInput;
    string questionID;
    
    do {
        cout << endl << "1.SIGN UP" << endl << "2.SIGN IN" << endl << "3.EXIT" << endl;
        cout << "Enter your choice:";
        cin >> choice;
        switch (choice) {
            case 1:
                u.signUp();
                break;
            case 2:
                if (n.checkentry()) {
                	system("CLS");
                    cout << "VERIFIED" << endl;
                    user.setUsername(n.getUsername());

                    // Nested switch for asking question or providing answer
                    int ch;
                    do {
                        cout << "1.ASK QUESTION" << endl << "2.ENTER ANSWER" << endl << "3.VIEW PROFILE" <<endl<< "4.LOG OUT" << endl;
                        cout << "Enter choice:";
                        cin >> ch;
                        ifstream answersFile;
                        ifstream questionFile;
                        switch (ch) {
                            case 1:
                                char c;
                                cout << "Enter your question: ";
                                fflush(stdin);
                                getline(cin, userInput);
                                manager.addQuestion(userInput, user);
                                break;
                            case 2:
                            	questionFile.open("questions.txt");
    							while(!questionFile.eof())
    							{
    								string line;
    								getline(questionFile,line);
    								cout<<line<<endl;
								}
								questionFile.close();
                                cout << "Enter the question ID: ";
                                cin >> questionID;
                                answerClass.answerQuestionByID(questionID, user);
                                break;
                            case 3:
                                user.displayProfile();
                                break;
                            /*case 4:
                                exit(0);
                            default:
                                cout << "Invalid choice. Please try again." << endl;*/
                        }
                    } while (ch<=3);
                } else {
                    cout << "RE-ENTER" << endl;
                }
                break;
            case 3:
                exit(0);
        }
    } while (1);
    return 0;
}
