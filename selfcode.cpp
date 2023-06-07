#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

struct node
{
    int NID;
    string Name;
    int Phone;
    int Members;
    int Rooms;
    int Cars;
    node *next;
};

node *head = NULL, *temp = NULL, *current = NULL, *newnode = NULL;

int room_quantity;
int car_quantity;
int customer_required_car;
void customerCheckOut();

void customerData();
void roomManagement();
void carManagement();
void customerNeedsCar();
void searchCustomerByNID();

int main()
{
    string password;
    string pass = "admin";
    cout << "Enter Admin Password: " << endl;
    getline(cin, password);
    if (pass == password)
    {
        while (true)
        {
            int choice;
            cout << ".........Menu........" << endl;
            cout << "1: Customer check in" << endl;
            cout << "2: Customer check out" << endl;
            cout << "3: Room management" << endl;
            cout << "4: Car management" << endl;
            cout << "5: Search a customer by NID :" << endl;
            cout << "0: Exit" << endl;
            cout << "Enter your choice: " << endl;
            cin >> choice;
            switch (choice)
            {
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
    }

    else
        cout << "Invalid password" << endl;
}

void customerData()
{
    newnode = new node;
    cout << "Customer full name: " << endl;
    cin.ignore();
    getline(cin, newnode->Name);
    cout << "Customer NID: " << endl;
    cin >> newnode->NID;
    cout << "Phone number: " << endl;
    cin >> newnode->Phone;

    int x = 0;
    int c = 0;
    ifstream file("room.txt");
    if (file.is_open())
    {

        file >> x;
        cout << "Total available room: " << x << endl;
        file.close();
    }
    cout << "Quantity of room: " << endl;
    cin >> newnode->Rooms;
    if (newnode->Rooms > x)
    {
        cout << "Availble rooms are less than customer requirment" << endl;
        cout << "Want to break this operation?\n1: YES\n2: NO" << endl;
        cin >> c;
        if (c == 1)
            return;
        else
        {
            cout << "Quantity of room: " << endl;
            cin >> newnode->Rooms;
            ofstream file1("room.txt");
            cout << "Available room: " << x - newnode->Rooms << endl;
            file1 << (x - newnode->Rooms);
            file1.close();
        }
    }
    else
    {
        ofstream file1("room.txt");
        cout << "Available room: " << x - newnode->Rooms << endl;
        file1 << (x - newnode->Rooms);
        file1.close();
    }
    cout << "How many members? :" << endl;
    cin >> newnode->Members;
    cout << "Need cars? \n1: YES\n2: NO" << endl;
    cin >> c;
    if (c == 1)
    {
        customerNeedsCar();
    }
    else
    {
        newnode->Cars = 0;
    }
    ofstream file2("customer.txt", ios::out | ios::app);
    if (file2.is_open())
    {
        file2 << newnode->Name << " " << newnode->NID << " " << newnode->Phone << " " << newnode->Rooms << " "
              << newnode->Members << " " << newnode->Cars << endl;
    }
    file2.close();
}

// check out
void customerCheckOut()
{
    cout << "Enter NID : " << endl;
    int n, x;
    cin >> n;
    string name;
    int nid, phone, room, members, car;
    ifstream file3("customer.txt");
    while (file3 >> name >> nid >> phone >> room >> members >> car)
    {
        if (nid == n) // Change int to match the type of nid in the struct
        {
            ifstream fileRoom("room.txt");
            if (fileRoom.is_open())
            {
                fileRoom >> x;
                fileRoom.close();
            }

            ofstream fileRoom1("room.txt");
            fileRoom1 << (x + room);
            fileRoom1.close();

            ifstream fileCar("car.txt");

            if (fileCar.is_open())
            {
                fileCar >> x;
                fileCar.close();
            }

            ofstream fileCar1("car.txt");
            fileCar1 << (x + car);
            fileCar1.close();
        }
        file3.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void searchCustomerByNID()
{
    int searchNID;
    string name;
    int nid, phone, room, members, car;
    cout << "Enter customer NID to search: " << endl;
    cin >> searchNID;

    ifstream file("customer.txt");
    if (!file)
    {
        cout << "Error opening customer file." << endl;
        return;
    }

    bool found = false;
    while (file >> name >> nid >> phone >> room >> members >> car)
    {
        if (nid == searchNID)
        {
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

    if (!found)
    {
        cout << "Customer with NID " << searchNID << " not found." << endl;
    }
}

// Room management system
void roomManagement()
{
    int x = 0;
    cout << "Want to add room?\n1: YES\n2: NO" << endl;

    int c;
    cin >> c;
    if (c == 1)
    {
        ifstream file("room.txt");
        if (file.is_open())
        {

            file >> x;
            cout << "Total room: " << x << endl;
            file.close();
        }
        cout << "How much room available?: " << endl;
        cin >> room_quantity;
        ofstream file1("room.txt");
        cout << "Updated successfully\nTotal room: " << x + room_quantity << endl;
        file1 << (x + room_quantity);
        file1.close();
    }
    else
        return;
}

// Car management system
void carManagement()
{
    int x = 0;
    cout << "1: Want to add car to the update list?" << endl;
    cout << "2: exit" << endl;
    int c;
    cin >> c;
    if (c == 1)
    {
        ifstream file("car.txt");
        if (file.is_open())
        {

            file >> x;
            cout << "Total car: " << x << endl;
            file.close();
        }
        cout << "How much room available?: " << endl;
        cin >> car_quantity;
        ofstream file1("car.txt");
        cout << "Updated successfully\nTotal car: " << x + car_quantity << endl;
        file1 << (x + car_quantity);
        file1.close();
    }

    else
        return;
}

void customerNeedsCar()
{
    int x;
    ifstream file("car.txt");
    if (file.is_open())
    {

        file >> x;
        cout << "Total available car: " << x << endl;
        file.close();
    }
    cout << "How many cars?: " << endl;

    cin >> customer_required_car;
    if (customer_required_car > x)
    {
        cout << "Sorry" << endl;
    }
    else
    {
        ofstream file1("car.txt");
        newnode->Cars = customer_required_car;
        cout << "Total available car: " << x - customer_required_car << endl;
        file1 << (x - customer_required_car);
        file1.close();
    }
}