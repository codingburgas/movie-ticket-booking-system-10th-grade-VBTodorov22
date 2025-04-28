#include <iostream>
#include <fstream>
#include <string>

using namespace std;



class Hall {
public:
    int hallId;
    int totalSeats;

    Hall(int id, int seats) : hallId(id), totalSeats(seats) {}
};

class Movie {
public:
    string title;
    string language;
    string genre;
    string releaseDate;

    Movie(string t, string l, string g, string r)
        : title(t), language(l), genre(g), releaseDate(r) {
    }
};

class MovieTicketSystem {
private:
    bool isAdmin;

public:
    MovieTicketSystem() : isAdmin(false) {}

    bool registerUser() {
        string username, password, role;
        cout << "Choose role (admin/user): ";
        cin >> role;

        if (role != "admin" && role != "user") {
            return false;
        }

        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        ofstream outFile("users.txt", ios::app);
        if (outFile.is_open()) {
            outFile << role << " " << username << " " << password << endl;
            outFile.close();
            return true;
        }
        else {
            return false;
        }
    }

    bool login() {
        int choice;
        cout << "1. Login\n2. Register\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 2) {
            return registerUser();
        }

        string username, password;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        ifstream inFile("users.txt");
        if (inFile.is_open()) {
            string fileRole, fileUsername, filePassword;
            while (inFile >> fileRole >> fileUsername >> filePassword) {
                if (username == fileUsername && password == filePassword) {
                    isAdmin = (fileRole == "admin");
                    inFile.close();
                    return true;
                }
            }
            inFile.close();
        }
        return false;
    }

    void runMenu() {
        login();
    }
};

int main() {
    MovieTicketSystem system;
    system.runMenu();
    return 0;
}