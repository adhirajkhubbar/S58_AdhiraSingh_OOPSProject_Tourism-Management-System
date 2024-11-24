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
    // Default constructor
    TourEntity() : name("") {
        cout << "Default constructor called for TourEntity." << endl;
    }

    // Constructor with name parameter
    TourEntity(string n) : name(n) {
        cout << "Constructor called for TourEntity with name: " << n << endl;
    }

    virtual void displayInfo() = 0; // Pure virtual function for polymorphism
    string getName() const { return name; } // Accessor
    virtual ~TourEntity() {
        cout << "Destructor called for TourEntity: " << name << endl;
    }
};

// Class representing a tourist attraction
class Attraction : public TourEntity {
private:
    string description;
    string location;
    string operatingHours;

public:
    // Default constructor (not recommended)
    Attraction() : TourEntity() {} // Inherits default constructor from TourEntity

    // Constructor with all parameters
    Attraction(string n, string desc, string loc, string hours)
        : TourEntity(n), description(desc), location(loc), operatingHours(hours) {
        cout << "Constructor called for Attraction with all parameters." << endl;
        // Input validation
        if (n.empty() || desc.empty() || loc.empty() || hours.empty()) {
            throw invalid_argument("Invalid input: All fields must be non-empty.");
        }
    }

    void displayInfo() override { // Polymorphism
        cout << "Attraction Name: " << getName() << endl; // Using accessor
        cout << "Description: " << description << endl;
        cout << "Location: " << location << endl;
        cout << "Operating Hours: " << operatingHours << endl;
    }

    ~Attraction() { // Destructor to release memory
        cout << "Deallocating memory for Attraction: " << getName() << endl;
    }
};

// Class representing a booking
class Booking {
private:
    static int bookingCounter; // Static variable to keep track of booking count
    string visitorName;
    Attraction* attraction; // Pointer to dynamically allocated Attraction object
    string bookingDate;

public:
    // Constructor with all parameters
    Booking(string name, Attraction* attr, string date)
        : visitorName(name), attraction(attr), bookingDate(date) {
        bookingCounter++; // Increment booking count
        cout << "Constructor called for Booking." << endl;
    }

    void displayBooking() {
        cout << "Visitor: " << visitorName << endl;
        cout << "Attraction: " << attraction->getName() << endl; // Using accessor
        cout << "Booking Date: " << bookingDate << endl;
        cout << "Booking ID: " << bookingCounter << endl; // Access static variable
    }

    static void displayTotalBookings() { // Static member function
        cout << "Total Bookings: " << bookingCounter << endl;
    }

    ~Booking() { // Destructor to release memory (optional)
        cout << "Deallocating memory for Booking of " << visitorName << endl;
    }
};

int Booking::bookingCounter = 0; // Initialize static variable outside the class

// Class representing visitor feedback
class Feedback {
private:
    string visitorName;
    string attractionName;
    string comments;
    int rating;

public:
    // Constructor with all parameters
    Feedback(string name, string attrName, string comm, int rate)
        : visitorName(name), attractionName(attrName), comments(comm), rating(rate) {
        cout << "Constructor called for Feedback." << endl;
    }

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
    vector<Attraction*> attractions; // Vector of pointers to dynamically allocated Attraction objects
    double price;

public:
    // Constructor with name and price
    TourPackage(string name, double p) : TourEntity(name), price(p) {
        cout << "Constructor called for TourPackage." << endl;
    }

    void addAttraction(Attraction* attr) {
        attractions.push_back(attr);
    }

    void displayInfo() override { // Polymorphism
        cout << "Tour Package: " << getName() << endl; // Using accessor
        cout << "Price: $" << price << endl;
        cout << "Included Attractions:" << endl;
        for (Attraction* attr : attractions) {
            cout << "- " << attr->getName() << endl;
        }
    }

    ~TourPackage() { // Destructor to release memory for attractions
        cout << "Deallocating memory for attractions in Tour Package: " << getName() << endl;
        for (Attraction* attr : attractions) {
            delete attr; // Release memory for each Attraction object
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
    UserProfile(string n, string e) : name(n), email(e) {
        cout << "Constructor called for UserProfile." << endl;
    }

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
    // Create attractions using dynamic memory allocation
    Attraction* attraction1 = new Attraction("Grand Canyon", "A stunning natural wonder.", "Arizona, USA", "6 AM - 6 PM");
    Attraction* attraction2 = new Attraction("Eiffel Tower", "Iconic symbol of Paris.", "Paris, France", "9 AM - 11 PM");

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
    Booking::displayTotalBookings(); // Using the static member function

    // Free dynamically allocated memory
    delete attraction1;
    delete attraction2;
    delete package1;

    return 0;
}