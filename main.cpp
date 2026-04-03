#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string n[], string c[]);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    bool again = true;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    list<Goat> trip;

    while (again) {
        int choice = main_menu();

        if (choice == 1) {
            add_goat(trip, names, colors);
        }
        else if (choice == 2) {
            delete_goat(trip);
        }
        else if (choice == 3) {
            display_trip(trip);
        }
        else if (choice == 4) {
            again = false; 
        }
    }

    return 0;
}

int main_menu() {
    int choice;
    string buf;

    cout << "*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Quit" << endl;
    
    cin >> buf; choice = atoi(buf.c_str());
    cin.ignore(1000, 10);

    while (choice < 1 || choice > 4) {
        cout << "Invalid choice. Try again." << endl;
        cin >> buf; choice = atoi(buf.c_str());
        cin.ignore(1000, 10);
    }

    return choice;

}

int select_goat(list<Goat> trip) {
    if (trip.empty()) {
        cout << "No goats to select." << endl;
        return -1;
    }
    
    int count = 1;

    cout << endl;

    for (auto it = trip.begin(); it != trip.end(); it++) {
        cout << "[" << count << "] "
            << it->get_name() << "("
            << it->get_age() << ", "
            << it->get_color() << ")" << endl;
        count++;
    }

    cout << endl; 

    int choice;
    string buf;

    cout << "Choice: ";
    cin >> buf; choice = atoi(buf.c_str());
    cin.ignore(1000, 10);

    cout << endl;

    while (choice < 1 || choice >= count) {
        cout << "Invalid choice. Try again." << endl;
        cin >> buf; choice = atoi(buf.c_str());
        cin.ignore(1000, 10);
    }

    return choice;
    
}
void delete_goat(list<Goat>& trip) {
    if (trip.empty()) {
        cout << "No goats to delete." << endl;
        return;
    }

    int choice = select_goat(trip);

    auto it = trip.begin(); 
    for (int i = 1; i < choice; i++) { //must use i in for loop to compare to choice, cannot compare it pointer and int choice
        it++;                          //also must use because unable to access specific indexes for std::lists
    }

    cout << endl;

    cout << "Deleted goat: "
        << it->get_name() << "("
        << it->get_age() << ", "
        << it->get_color() << ")" << endl;

    trip.erase(it);

    cout << endl;

}


void add_goat(list<Goat>& trip, string n[], string c[]) {
    string name = n[rand() % SZ_NAMES];
    string color = c[rand() % SZ_COLORS];
    int age = rand() % (MAX_AGE + 1);
    Goat g(name, age, color);

    trip.push_back(g);
    trip.sort();

    cout << endl;
    
    cout << "Added goat: " << endl
        << g.get_name() << "(" 
        << g.get_age() << ", "
        << g.get_color() << ")" << endl;

    cout << endl;
}


void display_trip(list<Goat> trip) {
    if (trip.empty()) {
        cout << "No goats" << endl;
        return;
    }

    int count = 1;
   
    cout << endl;

    cout << "Current Trip: " << endl;

    for (auto it = trip.begin(); it != trip.end(); it++) {
        cout << "[" << count << "] "
            << it->get_name() << " ("
            << it->get_age() << ", "
            << it->get_color() << ")" << endl;
        count++;
     }

    cout << endl;
}