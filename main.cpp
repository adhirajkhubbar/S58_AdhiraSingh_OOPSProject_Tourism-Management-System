#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Abstract base class for all entities in the tourism system
class TourEntity {
protected:
    string name; // Encapsulation: name is protected to restrict direct access
public:
    TourEntity(string n) : name(n) {} // Constructor
    virtual void displayInfo() = 0; // Pure virtual function for polymorphism
    string getName() { return name; } // Accessor
    virtual ~TourEntity() {} // Destructor
};

// Class representing a tourist attraction
class Attraction : public TourEntity {
private:
    string description;
    string location;
    string operatingHours;

public:
    Attraction(string n, string desc, string loc, string hours) 
        : TourEntity(n), description(desc), location(loc), operatingHours(hours) {}

    void displayInfo() override { // Polymorphism
        cout << "Attraction Name: " << name << endl;
        cout << "Description: " << description << endl;
        cout << "Location: " << location << endl;
        cout << "Operating Hours: " << operatingHours << endl;
    }
};

// Class representing a booking
class Booking {
private:
    string visitorName;
    Attraction* attraction;
    string bookingDate;

public:
    Booking(string name, Attraction* attr, string date) 
        : visitorName(name), attraction(attr), bookingDate(date) {}

    void displayBooking() {
        cout << "Visitor: " << visitorName << endl;
        cout << "Attraction: " << attraction->getName() << endl; // Using this pointer
        cout << "Booking Date: " << bookingDate << endl;
    }
};

// Class representing visitor feedback
class Feedback {
private:
    string visitorName;
    string attractionName;
    string comments;
    int rating;

public:
    Feedback(string name, string attrName, string comm, int rate) 
        : visitorName(name), attractionName(attrName), comments(comm), rating(rate) {}

    Feedback(const Booking& booking, string comm, int rate) 
        : visitorName(booking.visitorName), attractionName(booking.attraction->getName()), 
          comments(comm), rating(rate) {}

    void displayFeedback() {
        cout << "Visitor: " << visitorName << endl;
        cout << "Attraction: " << attractionName << endl;
        cout << "Comments: " << comments << endl;
        cout << "Rating: " << rating << "/5" << endl;
    }
};

// Class representing a tour package
class TourPackage : public TourEntity {
private:
    vector<Attraction*> attractions;
    double price;

public:
    TourPackage(string name, double p) : TourEntity(name), price(p) {}

    void addAttraction(Attraction* attr) {
        attractions.push_back(attr);
    }

    void displayInfo() override { // Polymorphism
        cout << "Tour Package: " << name << endl;
        cout << "Price: $" << price << endl;
        cout << "Included Attractions:" << endl;
        for (Attraction* attr : attractions) {
            cout << "- " << attr->getName() << endl;
        }
    }
};

// Class representing a user profile
class UserProfile {
private:
    string name;
    string email;
    vector<Booking> bookings;
    vector<Feedback> feedbacks;

public:
    UserProfile(string n, string e) : name(n), email(e) {}

    void addBooking(Booking booking) {
        bookings.push_back(booking);
    }

    void addFeedback(Feedback feedback) {
        feedbacks.push_back(feedback);
    }

    void displayProfile() {
        cout << "User Profile: " << name << " (" << email << ")" << endl;
        cout << "Bookings:" << endl;
        for (const Booking& b : bookings) {
            b.displayBooking();
        }
        cout << "Feedbacks:" << endl;
        for (const Feedback& f : feedbacks) {
            f.displayFeedback();
        }
    }
};

// Static member variable to track the number of bookings
static int totalBookings = 0;

// Class to manage booking count with static member function
class BookingManager {
public:
    static void incrementBooking() { totalBookings++; }
    static int getTotalBookings() { return totalBookings; }
};

// Main function to demonstrate the system
int main() {
    // Create an array of attractions
    Attraction attractions[3] = {
        Attraction("Grand Canyon", "A stunning natural wonder.", "Arizona, USA", "6 AM - 6 PM"),
        Attraction("Eiffel Tower", "Iconic symbol of Paris.", "Paris, France", "9 AM - 11 PM"),
        Attraction("Colosseum", "Ancient Roman amphitheater.", "Rome, Italy", "9 AM - 7 PM")
    };

    // ... rest of your code ...

    // Iterate through the array and display information
    for (int i = 0; i < 3; ++i) {
        attractions[i].displayInfo();
        cout << endl;
    }

    // ... rest of your code ...

    // Create a tour package
    TourPackage* package1 = new TourPackage("Adventure Package", 299.99);
    package1->addAttraction(attraction1);
    package1->addAttraction(attraction2);

    // Create user profiles
    UserProfile user1("Alice Johnson", "alice@example.com");

    // Create bookings and feedback
    Booking booking1("Alice Johnson", attraction1, "2024-05-01");
    user1.addBooking(booking1);
    BookingManager::incrementBooking(); // Increment booking count

    Feedback feedback1(booking1, "Amazing experience!", 5);
    user1.addFeedback(feedback1);

    // Display information
    cout << "=== Attractions ===" << endl;
    attraction1->displayInfo();
    cout << endl;
    attraction2->displayInfo();
    cout << endl;

    cout << "=== Tour Package ===" << endl;
    package1->displayInfo();
    cout << endl;

    cout << "=== User Profile ===" << endl;
    user1.displayProfile();
    cout << endl;

    cout << "Total Bookings: " << BookingManager::getTotalBookings() << endl;

    // Free dynamically allocated memory
    delete attraction1;
    delete attraction2;
    delete package1;

    return 0;
}