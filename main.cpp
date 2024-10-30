#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Class representing a tourist attraction
class Attraction {
private:
    string name;
    string description;
    string location;
    string operatingHours;

public:
    // Constructor
    Attraction(string n, string desc, string loc, string hours) 
        : name(n), description(desc), location(loc), operatingHours(hours) {}

    // Member function to display information
    void displayInfo() {
        cout << "Attraction Name: " << name << endl;
        cout << "Description: " << description << endl;
        cout << "Location: " << location << endl;
        cout << "Operating Hours: " << operatingHours << endl;
    }
};

// Class representing a user profile
class UserProfile {
private:
    string name;
    string email;

public:
    // Constructor
    UserProfile(string n, string e) : name(n), email(e) {}

    // Member function to display user profile
    void displayProfile() {
        cout << "User Profile: " << name << " (" << email << ")" << endl;
    }
};

// Main function to demonstrate the system
int main() {
    // Create objects using the classes
    Attraction attraction1("Grand Canyon", "A stunning natural wonder.", "Arizona, USA", "6 AM - 6 PM");
    UserProfile user1("Alice Johnson", "alice@example.com");

    // Call member functions to display information
    cout << "=== Attractions ===" << endl;
    attraction1.displayInfo();
    cout << endl;

    cout << "=== User Profile ===" << endl;
    user1.displayProfile();
    cout << endl;

    return 0;
}
