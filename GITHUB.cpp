#include <iostream>
#include <string>
using namespace std;

class Room {
protected:
    int roomNumber;
    double pricePerNight;
    bool wifi, breakfast, roomService;
    static int roomCount;

public:
    Room() : roomNumber(0), pricePerNight(100.0), wifi(false), breakfast(false), roomService(false) { roomCount++; }
    Room(int number, double price, bool wifi = false, bool breakfast = false, bool roomService = false)
        : roomNumber(number), pricePerNight(price), wifi(wifi), breakfast(breakfast), roomService(roomService) { roomCount++; }
    virtual ~Room() { roomCount--; }
    
    static int getRoomCount() { return roomCount; }
    int getRoomNumber() const { return roomNumber; }
    double getPricePerNight() const { return pricePerNight; }
    bool hasWifi() const { return wifi; }
    bool hasBreakfast() const { return breakfast; }
    bool hasRoomService() const { return roomService; }

    virtual double calculateCost(int days) const {
        double cost = days * pricePerNight;
        if (wifi) cost += days * 10.0;
        if (breakfast) cost += days * 15.0;
        if (roomService) cost += days * 20.0;
        return cost;
    }

    virtual void displayInfo() const {
        cout << "Room Number: " << roomNumber << ", Price Per Night: $" << pricePerNight;
        cout << ", Wi-Fi: " << (wifi ? "Yes" : "No") << ", Breakfast: " << (breakfast ? "Yes" : "No");
        cout << ", Room Service: " << (roomService ? "Yes" : "No") << endl;
    }
};

int Room::roomCount = 0;

class StandardRoom : public Room {
public:
    StandardRoom(int number, double price, bool wifi = false, bool breakfast = false, bool roomService = false)
        : Room(number, price, wifi, breakfast, roomService) {}
    
    void displayInfo() 
	const override {
        cout << "Standard Room - ";
        Room::displayInfo();
    }
};

class DeluxeRoom : public Room {
public:
    DeluxeRoom(int number, double price, bool wifi = true, bool breakfast = true, bool roomService = false)
        : Room(number, price * 1.25, wifi, breakfast, roomService) {}
    
    void displayInfo() const override {
        cout << "Deluxe Room - ";
        Room::displayInfo();
    }
};

class SuiteRoom : public Room {
public:
    SuiteRoom(int number, double price, bool wifi = true, bool breakfast = true, bool roomService = true)
        : Room(number, price * 1.5, wifi, breakfast, roomService) {}

    void displayInfo() const override {
        cout << "Suite Room - ";
        Room::displayInfo();
    }
};

class Customer {
protected:
    string name;
    int stayDuration;

public:
    Customer() : name("Unknown"), stayDuration(1) {}
    Customer(const string &name, int stay) : name(name), stayDuration(stay) {}

    virtual void displayInfo() const {
        cout << "Customer Name: " << name << ", Stay Duration: " << stayDuration << " days" << endl;
    }
};

class Booking : public Customer {
private:
    Room *room;
    double totalCost;
    bool foodService, housekeeping;

public:
    Booking(const string &name, int stay, Room *r, bool food = false, bool housekeeping = false)
        : Customer(name, stay), room(r), foodService(food), housekeeping(housekeeping) {
        totalCost = room->calculateCost(stay);
        if (foodService) totalCost += stay * 30.0;
        if (housekeeping) totalCost += stay * 25.0;
    }

    void displayInfo() const override {
        cout << "Booking Info - Customer Name: " << name << ", Stay Duration: " << stayDuration << " days" << endl;
        if (room) room->displayInfo();
        cout << "Food Service: " << (foodService ? "Yes" : "No") << ", Housekeeping: " << (housekeeping ? "Yes" : "No") << endl;
        cout << "Total Cost: $" << totalCost << endl;
    }
};

int main() {
    int roomNumber;
    double roomPrice;
    string customerName;
    int stayDuration;
    char roomType, wifiOption, breakfastOption, roomServiceOption, foodOption, housekeepingOption;

start:
    cout << "Enter Room Number: ";
    cin >> roomNumber;
    cout << "Enter Price per Night for Room: ";
    cin >> roomPrice;

    cout << "Select Room Type - (S)tandard, (D)eluxe, (U)ite: ";
    cin >> roomType;
    cout << "Is Wi-Fi available (y/n)? ";
    cin >> wifiOption;
    cout << "Is Breakfast available (y/n)? ";
    cin >> breakfastOption;
    cout << "Is Room Service available (y/n)? ";
    cin >> roomServiceOption;

    Room *room;
    switch (roomType) {
        case 'S': room = new StandardRoom(roomNumber, roomPrice, wifiOption == 'y', breakfastOption == 'y', roomServiceOption == 'y'); break;
        case 'D': room = new DeluxeRoom(roomNumber, roomPrice, wifiOption == 'y', breakfastOption == 'y', roomServiceOption == 'y'); break;
        case 'U': room = new SuiteRoom(roomNumber, roomPrice, wifiOption == 'y', breakfastOption == 'y', roomServiceOption == 'y'); break;
        default: room = new StandardRoom(roomNumber, roomPrice); break;
    }

    cout << "\nEnter Customer Name: ";
    cin.ignore();
    getline(cin, customerName);
    cout << "Enter Stay Duration (days): ";
    cin >> stayDuration;

    cout << "Include Food Service (y/n)? ";
    cin >> foodOption;
    cout << "Include Housekeeping (y/n)? ";
    cin >> housekeepingOption;

    Booking booking(customerName, stayDuration, room, foodOption == 'y', housekeepingOption == 'y');

    cout << "\nBooking Details:" << endl;
    booking.displayInfo();

    cout << "\nTotal Rooms: " << Room::getRoomCount() << endl;

    delete room;
    char choice;
    cout<<"Do u want to enter another room deatails(Y/N)?"<<endl;
    cin>>choice;
    if(choice=='y' || choice=='Y')
    {
    	goto start;
	}
    return 0;
}

