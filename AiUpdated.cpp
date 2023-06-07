#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct node {
    int NID;
    string Name;
    string Phone;
    int Members;
    int Rooms;
    int Cars;
    node* next;
};

node* head = nullptr;
node* temp = nullptr;
node* current = nullptr;
node* newnode = nullptr;

int room_quantity;
int car_quantity;
int customer_required_car;

void customerCheckOut();
void customerData();
void roomManagement();
void carManagement();
void customerNeedsCar();
void searchCustomerByNID();

void displayMenu();
bool isAdminPasswordCorrect(const string& password);
void saveRoomQuantity(int quantity);
int loadRoomQuantity();
void saveCarQuantity(int quantity);
int loadCarQuantity();
void saveCustomerData(const node* customer);
void readCustomerData();

int main() {
    string password;
    const string adminPassword = "admin";
    
    cout << "Enter Admin Password: " << endl;
    getline(cin, password);
    
    if (isAdminPasswordCorrect(password)) {
        while (true) {
            displayMenu();
            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    customerData();
                    break;
                case 2:
                    customerCheckOut();
                    break;
                case 3:
                    roomManagement();
                    break;
                case 4:
                    carManagement();
                    break;
                case 5:
                    searchCustomerByNID();
                    break;
                case 0:
                    exit(0);
                default:
                    cout << "Invalid choice!" << endl;
                    break;
            }
        }
    } else {
        cout << "Invalid password" << endl;
    }
    
    return 0;
}

void displayMenu() {
    cout << ".........Menu........" << endl;
    cout << "1: Customer check in" << endl;
    cout << "2: Customer check out" << endl;
    cout << "3: Room management" << endl;
    cout << "4: Car management" << endl;
    cout << "5: Search a customer by NID" << endl;
    cout << "0: Exit" << endl;
    cout << "Enter your choice: ";
}

bool isAdminPasswordCorrect(const string& password) {
    const string adminPassword = "admin";
    return password == adminPassword;
}

void customerData() {
    newnode = new node;
    cin.ignore();

    cout << "Customer full name: ";
    getline(cin, newnode->Name);
    
    cout << "Customer NID: ";
    cin >> newnode->NID;
    
    cout << "Phone number: ";
    cin.ignore();
    getline(cin, newnode->Phone);

    int availableRooms = loadRoomQuantity();
    cout << "Total available rooms: " << availableRooms << endl;
    
    cout << "Quantity of room: ";
    cin >> newnode->Rooms;
    
    if (newnode->Rooms > availableRooms) {
        cout << "Available rooms are less than customer's requirement." << endl;
        cout << "Want to cancel this operation?\n1: YES\n2: NO" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
            return;
        else {
            cout << "Quantity of room: ";
            cin >> newnode->Rooms;
            saveRoomQuantity(availableRooms - newnode->Rooms);
        }
    } else {
        saveRoomQuantity(availableRooms - newnode->Rooms);
    }
    
    cout << "How many members? : ";
    cin >> newnode->Members;
    
    cout << "Need cars? \n1: YES\n2: NO" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        customerNeedsCar();
    } else {
        newnode->Cars = 0;
    }
    
    saveCustomerData(newnode);
}

void customerCheckOut() {
    cout << "Enter NID: ";
    int n;
    cin >> n;
    
    string name;
    int nid, phone, room, members, car;
    
    ifstream file("customer.txt");
    ofstream tempFile("temp.txt");

    if (!file || !tempFile) {
        cout << "Error opening customer file." << endl;
        return;
    }
    
    while (file >> name >> nid >> phone >> room >> members >> car) {
        if (nid == n) {
            int availableRooms = loadRoomQuantity();
            saveRoomQuantity(availableRooms + room);
            
            int availableCars = loadCarQuantity();
            saveCarQuantity(availableCars + car);
        } else {
            tempFile << name << " " << nid << " " << phone << " " << room << " " << members << " " << car << endl;
        }
    }

    file.close();
    tempFile.close();
    
    remove("customer.txt");
    rename("temp.txt", "customer.txt");
}

void searchCustomerByNID() {
    int searchNID;
    cout << "Enter customer NID to search: ";
    cin >> searchNID;

    ifstream file("customer.txt");
    if (!file) {
        cout << "Error opening customer file." << endl;
        return;
    }

    bool found = false;
    string name;
    int nid, phone, room, members, car;
    
    while (file >> name >> nid >> phone >> room >> members >> car) {
        if (nid == searchNID) {
            cout << "Name: " << name << endl;
            cout << "NID: " << nid << endl;
            cout << "Phone: " << phone << endl;
            cout << "Room: " << room << endl;
            cout << "Members: " << members << endl;
            cout << "Cars: " << car << endl;
            cout << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Customer with NID " << searchNID << " not found." << endl;
    }
}

void roomManagement() {
    int availableRooms = loadRoomQuantity();
    cout << "Want to add room?\n1: YES\n2: NO" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        cout << "How many rooms to add?: ";
        int quantity;
        cin >> quantity;
        saveRoomQuantity(availableRooms + quantity);
        cout << "Updated successfully.\nTotal rooms: " << availableRooms + quantity << endl;
    }
}

void carManagement() {
    int availableCars = loadCarQuantity();
    cout << "1: Want to add cars to the update list?" << endl;
    cout << "2: Exit" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        cout << "How many cars to add?: ";
        int quantity;
        cin >> quantity;
        saveCarQuantity(availableCars + quantity);
        cout << "Updated successfully.\nTotal cars: " << availableCars + quantity << endl;
    }
}

void customerNeedsCar() {
    int availableCars = loadCarQuantity();
    cout << "Total available cars: " << availableCars << endl;
    
    cout << "Quantity of car: ";
    cin >> newnode->Cars;
    
    if (newnode->Cars > availableCars) {
        cout << "Available cars are less than customer's requirement." << endl;
        cout << "Want to cancel this operation?\n1: YES\n2: NO" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
            return;
        else {
            cout << "Quantity of car: ";
            cin >> newnode->Cars;
            saveCarQuantity(availableCars - newnode->Cars);
        }
    } else {
        saveCarQuantity(availableCars - newnode->Cars);
    }
}

void saveRoomQuantity(int quantity) {
    ofstream file("room.txt");
    if (!file) {
        cout << "Error opening room file." << endl;
        return;
    }
    file << quantity;
    file.close();
}

int loadRoomQuantity() {
    ifstream file("room.txt");
    if (!file) {
        cout << "Error opening room file." << endl;
        return 0;
    }
    int quantity;
    file >> quantity;
    file.close();
    return quantity;
}

void saveCarQuantity(int quantity) {
    ofstream file("car.txt");
    if (!file) {
        cout << "Error opening car file." << endl;
        return;
    }
    file << quantity;
    file.close();
}

int loadCarQuantity() {
    ifstream file("car.txt");
    if (!file) {
        cout << "Error opening car file." << endl;
        return 0;
    }
    int quantity;
    file >> quantity;
    file.close();
    return quantity;
}

void saveCustomerData(const node* customer) {
    ofstream file("customer.txt", ios_base::app);
    if (!file) {
        cout << "Error opening customer file." << endl;
        return;
    }
    file << customer->Name << " " << customer->NID << " " << customer->Phone << " "
         << customer->Rooms << " " << customer->Members << " " << customer->Cars << endl;
    file.close();
}

void readCustomerData() {
    ifstream file("customer.txt");
    if (!file) {
        cout << "Error opening customer file." << endl;
        return;
    }
    
    string name;
    int nid, phone, room, members, car;
    
    while (file >> name >> nid >> phone >> room >> members >> car) {
        cout << "Name: " << name << endl;
        cout << "NID: " << nid << endl;
        cout << "Phone: " << phone << endl;
        cout << "Room: " << room << endl;
        cout << "Members: " << members << endl;
        cout << "Cars: " << car << endl;
        cout << endl;
    }

    file.close();
}
