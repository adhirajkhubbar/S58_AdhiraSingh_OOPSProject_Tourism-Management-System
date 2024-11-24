#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Abstract base class for all entities in the tourism system
class TourEntity {
protected:
    string name;

public:
    TourEntity(string n) : name(n) {
        cout << "TourEntity constructor called: " << name << endl;
    }

    virtual void displayInfo() = 0;
    string getName() const { return name; }
    virtual ~TourEntity() {
        cout << "TourEntity destructor called: " << name << endl;
    }
};

// Class representing a tourist attraction
class Attraction : public TourEntity {
private:
    string description;
    string location;
    string operatingHours;

public:
    Attraction(string n, string desc, string loc, string hours)
        : TourEntity(n), description(desc), location(loc), operatingHours(hours) {
        cout << "Attraction constructor called: " << name << endl;
    }

    void displayInfo() override {
        cout << "Attraction Name: " << getName() << endl;
        cout << "Description: " << description << endl;
        cout << "Location: " << location << endl;
        cout << "Operating Hours: " << operatingHours << endl;
    }

    ~Attraction() {
        cout << "Attraction destructor called: " << name << endl;
    }
};

// Class representing a special event (derived from Attraction)
class SpecialEvent : public Attraction {
private:
    string startDate;
    string endDate;

public:
    SpecialEvent(string n, string desc, string loc, string hours, string start, string end)
        : Attraction(n, desc, loc, hours), startDate(start), endDate(end) {
        cout << "SpecialEvent constructor called: " << name << endl;
    }

    void displayInfo() override {
        Attraction::displayInfo();
        cout << "Start Date: " << startDate << endl;
        cout << "End Date: " << endDate << endl;
    }

    ~SpecialEvent() {
        cout << "SpecialEvent destructor called: " << name << endl;
    }
};

// Class representing a booking
class Booking {
private:
    static int bookingCounter;
    string visitorName;
    TourEntity* entity; // Pointer to a base class (can point to either Attraction or SpecialEvent)
    string bookingDate;

public:
    Booking(string name, TourEntity* ent, string date)
        : visitorName(name), entity(ent), bookingDate(date) {
        bookingCounter++;
        cout << "Booking constructor called." << endl;
    }

    void displayBooking() {
        cout << "Visitor: " << visitorName << endl;
        cout << "Entity: " << entity->getName() << endl;
        cout << "Booking Date: " << bookingDate << endl;
        cout << "Booking ID: " << bookingCounter << endl;
    }

    static void displayTotalBookings() {
        cout << "Total Bookings: " << bookingCounter << endl;
    }

    ~Booking() {
        cout << "Booking destructor called: " << visitorName << endl;
    }
};

int Booking::bookingCounter = 0;

// Class representing visitor feedback
class Feedback {
private:
    string visitorName;
    string attractionName;
    string comments;
    int rating;

public:
    Feedback(string name, string attrName, string comm, int rate)
        : visitorName(name), attractionName(attrName), comments(comm), rating(rate) {
        cout << "Feedback constructor called." << endl;
    }

    Feedback(const Booking& booking, string comm, int rate)
        : visitorName(booking.visitorName), attractionName(booking.entity->getName()),
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
    TourPackage(string name, double p) : TourEntity(name), price(p) {
        cout << "TourPackage constructor called: " << name << endl;
    }

    void addAttraction(Attraction* attr) {
        attractions.push_back(attr);
    }

    void displayInfo() override {
        cout << "Tour Package: " << getName() << endl;
        cout << "Price: $" << price << endl;
        cout << "Included Attractions:" << endl;
        for (Attraction* attr : attractions) {
            cout << "- " << attr->getName() << endl;
        }
    }

    ~TourPackage() {
        cout << "TourPackage destructor called: " << name << endl;
        for (Attraction* attr : attractions) {
            delete attr;
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
        cout << "UserProfile constructor called: " << name << endl;
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

    ~UserProfile() {
        cout << "UserProfile destructor called: " << name << endl;
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

    // Create a special event
    SpecialEvent* event1 = new SpecialEvent("New Year's Eve Fireworks", "A spectacular fireworks display", "Times Square, New York", "All Day", "2023-12-31", "2024-01-01");

    // Create a tour package
    TourPackage* package1 = new TourPackage("Adventure Package", 299.99);
    package1->addAttraction(attraction1);
    package1->addAttraction(attraction2);

    // Create user profiles
    UserProfile user1("Alice Johnson", "alice@example.com");

    // Create bookings and feedback
    Booking booking1("Alice Johnson", attraction1, "2024-05-01");
    Booking booking2("Bob Smith", event1, "2023-12-31");
    user1.addBooking(booking1);
    user1.addBooking(booking2);
    BookingManager::incrementBooking(); // Increment booking count twice

    Feedback feedback1(booking1, "Amazing experience!", 5);
    user1.addFeedback(feedback1);

    // Display information
    cout << "=== Attractions ===" << endl;
    attraction1->displayInfo();
    cout << endl;
    attraction2->displayInfo();
    cout << endl;

    cout << "=== Special Event ===" << endl;
    event1->displayInfo();
    cout << endl;

    cout << "=== Tour Package ===" << endl;
    package1->displayInfo();
    cout << endl;

    cout << "=== User Profile ===" << endl;
    user1.displayProfile();
    cout << endl;

    cout << "Total Bookings: " << BookingManager::getTotalBookings() << endl;
    Booking::displayTotalBookings();

    // Free dynamically allocated memory
    delete attraction1;
    delete attraction2;
    delete package1;

    return 0;
}