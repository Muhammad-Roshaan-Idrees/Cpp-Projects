#include <iostream>
#include <iomanip>
#include <string>
#include <cctype> 
using namespace std;

// Color codes for console styling - Let's make our program colorful and fun!
#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

struct Crop {
    string name; // What crop are we growing today?
    string plantingDate; // When did we plant it?
    bool isHarvested; // Is it ready to harvest yet?
};

struct Animal {
    string type; // What kind of animal is this?
    float weight; // How heavy is our friend?
    string vaccinationDate; // When was the last vet visit?
    string nextDueDate; // When's the next checkup?
    string morningFeedingTime; // Breakfast time!
    string eveningFeedingTime; // Dinner time!
};

struct Seed {
    string type; // Type of seed we're using
    int availableGrams; // How much seed do we have left?
    int usedGrams; // How much have we planted?
};

struct Fertilizer {
    string type; // What fertilizer are we applying?
    int availableKilograms; // How much fertilizer is in stock?
    int usedKilograms; // How much have we used?
};

struct LivestockRecord {
    string operationType; // What task did we do?
    double expenses; // How much did it cost?
    double income; // What did we earn?
};

// Function prototypes - Let's plan our farm management tasks!
void addCrop(Crop crops[], int &count, int maxCrops);
void markHarvested(Crop crops[], int count);
void displayReport(Crop crops[], int count);
bool validateNamecrop(const string &name);
bool validateDatecrop(const string &date);

void addAnimal(Animal animals[], int &count);
void displayAnimals(Animal animals[], int count);
void clearScreen();
void pauseScreen();
bool validateName(string input);
bool validateDate(string input);
bool validateTime(string input);

void addSeed(Seed seeds[], int &seedCount);
void addFertilizer(Fertilizer fertilizers[], int &fertilizerCount);
void editSeed(Seed seeds[], int seedCount);
void editFertilizer(Fertilizer fertilizers[], int fertilizerCount);
void deleteSeed(Seed seeds[], int &seedCount);
void deleteFertilizer(Fertilizer fertilizers[], int &fertilizerCount);
void generateReport(const Seed seeds[], int seedCount, const Fertilizer fertilizers[], int fertilizerCount);
void checkAlerts(const Seed seeds[], int seedCount, const Fertilizer fertilizers[], int fertilizerCount);

void addRecord(LivestockRecord records[], int &count);
void editRecord(LivestockRecord records[], int count);
void deleteRecord(LivestockRecord records[], int &count);
void viewFinancialReport(LivestockRecord records[], int count);
void displayMenu();
int getValidatedInteger();
double getValidatedDouble();

int cropmanagement();
int livestockmanagement();
int inventorymanagement();
int financialmanagement();

const int MAX_USERS = 100; 
string usernames[MAX_USERS]; // Store all our user names here
string passwords[MAX_USERS]; // Keep passwords safe (for now!)
int userCount = 0;

// Crop Management - Let's manage our crops like pros!
int cropmanagement() {
    const int MAX_CROPS = 100;
    Crop crops[MAX_CROPS];
    int cropCount = 0;
    int choice;
    do {
        clearScreen();
        cout << CYAN << "==================================================" << RESET << endl;
        cout << GREEN << "\t\t    Crop Management" << RESET << endl;
        cout << CYAN << "==================================================" << RESET << endl;
        cout << "\t1. Add Crop" << endl;
        cout << "\t2. Mark Crop as Harvested" << endl;
        cout << "\t3. Display Crop Report" << endl;
        cout << "\t4. Exit" << endl;
        cout << "\n\tPlease enter your choice: " << GREEN;
        cin >> choice;
        cout << RESET;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << RED << "Oops! Invalid input. Please enter a number." << RESET << endl;
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
            continue;
        }

        if (choice == 1) {
            addCrop(crops, cropCount, MAX_CROPS);
        } else if (choice == 2) {
            markHarvested(crops, cropCount);
        } else if (choice == 3) {
            displayReport(crops, cropCount);
        } else if (choice == 4) {
            cout << YELLOW << "Leaving Crop Management... See you soon!" << RESET << endl;
        } else {
            cout << RED << "Hmm, that’s not a valid choice. Try again!" << RESET << endl;
        }

        pauseScreen();
    } while (choice != 4);

    return 0;  
}

void addCrop(Crop crops[], int &count, int maxCrops) {
    clearScreen();
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Add Crops" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    if (count >= maxCrops) {
        cout << RED << "Whoa! We’ve hit the crop limit. No more space!" << RESET << endl;
        return;
    }
    Crop newCrop;
    cin.ignore();

    cout << GREEN << "Enter crop name (letters only): " << RESET;
    getline(cin, newCrop.name);
    if (!validateNamecrop(newCrop.name)) {
        cout << RED << "Oops! Only letters are allowed for crop names." << RESET << endl;
        return;
    }

    cout << GREEN << "Enter planting date (DD/MM/YYYY): " << RESET;
    getline(cin, newCrop.plantingDate);
    if (!validateDatecrop(newCrop.plantingDate)) {
        cout << RED << "Hmm, wrong date format. Use DD/MM/YYYY please!" << RESET << endl;
        return;
    }

    newCrop.isHarvested = false;
    crops[count++] = newCrop;
    cout << GREEN << "Yay! Crop added successfully!" << RESET << endl;
}

void markHarvested(Crop crops[], int count) {
    clearScreen();
    if (count == 0) {
        cout << RED << "No crops yet to harvest. Let’s grow some first!" << RESET << endl;
        return;
    }

    string cropName;
    cin.ignore();
    cout << GREEN << "Enter the name of the crop to mark as harvested: " << RESET;
    getline(cin, cropName);

    for (int i = 0; i < count; i++) {
        if (crops[i].name == cropName) {
            crops[i].isHarvested = true;
            cout << GREEN << "Great! Crop marked as harvested!" << RESET << endl;
            return;
        }
    }

    cout << RED << "Oops! Couldn’t find that crop." << RESET << endl;
}

void displayReport(Crop crops[], int count) {
    clearScreen();
    if (count == 0) {
        cout << RED << "No crops to show yet. Time to plant!" << RESET << endl;
        return;
    }
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Crop Report" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    cout << left << setw(20) << "Crop Name"
         << setw(20) << "Planting Date"
         << setw(15) << "Status" << endl;
    cout << string(55, '-') << endl;

    for (int i = 0; i < count; i++) {
        cout << left << setw(20) << crops[i].name
             << setw(20) << crops[i].plantingDate
             << setw(15) << (crops[i].isHarvested ? "Harvested" : "Growing") << endl;
    }
    cout << string(55, '-') << endl;
}

bool validateNamecrop(const string &name) {
    for (char c : name) {
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    return true;
}

bool validateDatecrop(const string &date) {
    if (date.length() != 10 || date[2] != '/' || date[5] != '/') {
        return false;
    }
    for (int i = 0; i < date.length(); i++) {
        if ((i != 2 && i != 5) && !isdigit(date[i])) {
            return false;
        }
    }
    return true;
}

// Livestock Management - Time to care for our animals!
int livestockmanagement() {
    const int MAX_ANIMALS = 100;
    Animal animals[MAX_ANIMALS];
    int count = 0;
    int choice;

    do {
        clearScreen();
        cout << CYAN << "==================================================" << RESET << endl;
        cout << GREEN << "\t\t    Livestock Management" << RESET << endl;
        cout << CYAN << "==================================================" << RESET << endl;
        cout << "\t1. Add Animal" << endl;
        cout << "\t2. Display Animals" << endl;
        cout << "\t3. Exit" << endl;
        cout << "\n\tPlease enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << RED << "Oops! Please enter a number." << RESET << endl;
            pauseScreen();
            continue;
        }

        if (choice == 1) {
            addAnimal(animals, count);
        } else if (choice == 2) {
            displayAnimals(animals, count);
        } else if (choice == 3) {
            cout << RED << "Exiting Livestock Management... Take care!" << RESET << endl;
        } else {
            cout << YELLOW << "That’s not right. Please try again!" << RESET << endl;
        }
        pauseScreen();
    } while (choice != 3);

    return 0;
}

void addAnimal(Animal animals[], int &count) {
    clearScreen();
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Add Animal Detail" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    if (count >= 100) {
        cout << RED << "Whoa! We’ve reached the animal limit!" << RESET << endl;
        return;
    }
    string input;
    cin.ignore();
    do {
        cout << GREEN << "Enter animal type (letters only): " << RESET;
        getline(cin, input);
        if (!validateName(input)) {
            cout << RED << "Oops! Only letters please." << RESET << endl;
        }
    } while (!validateName(input));
    animals[count].type = input;

    cout << GREEN << "Enter weight (kg): " << RESET;
    while (!(cin >> animals[count].weight) || animals[count].weight <= 0) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << RED << "Please enter a positive number!" << RESET << endl;
    }
    cin.ignore();

    do {
        cout << GREEN << "Enter vaccination date (DD/MM/YYYY): " << RESET;
        getline(cin, input);
        if (!validateDate(input)) {
            cout << RED << "Wrong format! Use DD/MM/YYYY." << RESET << endl;
        }
    } while (!validateDate(input));
    animals[count].vaccinationDate = input;

    do {
        cout << GREEN << "Enter next due date (DD/MM/YYYY): " << RESET;
        getline(cin, input);
        if (!validateDate(input)) {
            cout << RED << "Wrong format! Use DD/MM/YYYY." << RESET << endl;
        }
    } while (!validateDate(input));
    animals[count].nextDueDate = input;

    do {
        cout << GREEN << "Enter morning feeding time (HH:MM): " << RESET;
        getline(cin, input);
        if (!validateTime(input)) {
            cout << RED << "Wrong format! Use HH:MM." << RESET << endl;
        }
    } while (!validateTime(input));
    animals[count].morningFeedingTime = input;

    do {
        cout << GREEN << "Enter evening feeding time (HH:MM): " << RESET;
        getline(cin, input);
        if (!validateTime(input)) {
            cout << RED << "Wrong format! Use HH:MM." << RESET << endl;
        }
    } while (!validateTime(input));
    animals[count].eveningFeedingTime = input;

    count++;
    cout << GREEN << "Awesome! Animal added successfully!" << RESET << endl;
}

void displayAnimals(Animal animals[], int count) {
    clearScreen();
    if (count == 0) {
        cout << RED << "No animals to show yet. Let’s add some!" << RESET << endl;
        return;
    }
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Animal Report" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    cout << left << setw(20) << "Animal Type"
         << setw(10) << "Weight"
         << setw(20) << "Vaccination Date"
         << setw(20) << "Next Due Date"
         << setw(20) << "Morning Feed Time"
         << setw(20) << "Evening Feed Time" << endl;
    cout << string(120, '-') << endl;

    for (int i = 0; i < count; i++) {
        cout << left << setw(20) << animals[i].type
             << setw(10) << animals[i].weight
             << setw(20) << animals[i].vaccinationDate
             << setw(20) << animals[i].nextDueDate
             << setw(20) << animals[i].morningFeedingTime
             << setw(20) << animals[i].eveningFeedingTime << endl;
    }
}

bool validateName(string input) {
    for (char c : input) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

bool validateDate(string input) {
    if (input.length() != 10 || input[2] != '/' || input[5] != '/') {
        return false;
    }
    for (int i = 0; i < input.length(); i++) {
        if (i != 2 && i != 5 && !isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

bool validateTime(string input) {
    if (input.length() != 5 || input[2] != ':') {
        return false;
    }
    for (int i = 0; i < input.length(); i++) {
        if (i != 2 && !isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

void clearScreen() {
    cout << "\033[2J\033[1;1H"; // Clear the screen with a little magic!
}

void pauseScreen() {
    cin.ignore(1000, '\n');
    cout << "Press Enter to continue...";
    cin.get();
}

// Inventory Management - Let’s keep our supplies in check!
int inventorymanagement() {
    const int MAX_ITEMS = 50;
    Seed seeds[MAX_ITEMS];
    Fertilizer fertilizers[MAX_ITEMS];
    int seedCount = 0, fertilizerCount = 0;
    int choice;
    do {
        clearScreen();
        cout << CYAN << "==================================================" << RESET << endl;
        cout << GREEN << "\t\t    Inventory Management" << RESET << endl;
        cout << CYAN << "==================================================" << RESET << endl;
        cout << "\t1. Seeds" << endl;
        cout << "\t2. Fertilizers" << endl;
        cout << "\t3. Generate Report" << endl;
        cout << "\t4. Exit" << endl;
        cout << "\n\tPlease enter your choice: " << YELLOW;
        cin >> choice;
        cout << RESET;
        switch (choice) {
        case 1:
            int seedChoice;
            do {
                clearScreen();
                cout << CYAN << "==================================================" << RESET << endl;
                cout << GREEN << "\t\t    Seed Management" << RESET << endl;
                cout << CYAN << "==================================================" << RESET << endl;
                cout << "\t1. Add Seed" << endl;
                cout << "\t2. Edit Seed" << endl;
                cout << "\t3. Delete Seed" << endl;
                cout << "\t4. Back to Main Menu" << endl;
                cout << "\n\tPlease enter your choice: " << YELLOW;
                cin >> seedChoice;
                cout << RESET;
                switch (seedChoice) {
                case 1: addSeed(seeds, seedCount); break;
                case 2: editSeed(seeds, seedCount); break;
                case 3: deleteSeed(seeds, seedCount); break;
                case 4: break;
                default: cout << RED << "Oops! Invalid choice. Try again!" << RESET;
                }
                pauseScreen();
            } while (seedChoice != 4);
            break;
        case 2:
            int fertilizerChoice;
            do {
                clearScreen();
                cout << CYAN << "==================================================" << RESET << endl;
                cout << GREEN << "\t\t    Fertilizer Management" << RESET << endl;
                cout << CYAN << "==================================================" << RESET << endl;
                cout << "\t1. Add Fertilizer" << endl;
                cout << "\t2. Edit Fertilizer" << endl;
                cout << "\t3. Delete Fertilizer" << endl;
                cout << "\t4. Back to Main Menu" << endl;
                cout << "\n\tPlease enter your choice: " << YELLOW;
                cin >> fertilizerChoice;
                cout << RESET;
                switch (fertilizerChoice) {
                case 1: addFertilizer(fertilizers, fertilizerCount); break;
                case 2: editFertilizer(fertilizers, fertilizerCount); break;
                case 3: deleteFertilizer(fertilizers, fertilizerCount); break;
                case 4: break;
                default: cout << RED << "Oops! Invalid choice. Try again!" << RESET;
                }
                pauseScreen();
            } while (fertilizerChoice != 4);
            break;
        case 3:
            generateReport(seeds, seedCount, fertilizers, fertilizerCount);
            break;
        case 4:
            cout << GREEN << "Exiting Inventory Management... Bye for now!" << RESET;
            break;
        default:
            cout << RED << "Hmm, that’s not a valid choice. Try again!" << RESET;
        }
        pauseScreen();
    } while (choice != 4);

    return 0;
}

void addSeed(Seed seeds[], int &seedCount) {
    clearScreen();
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Add Seeds" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    if (seedCount >= 50) {
        cout << RED << "Oh no! Seed inventory is full!" << RESET;
        return;
    }
    cin.ignore();
    cout << "Enter seed type: ";
    getline(cin, seeds[seedCount].type);
    cout << "Enter available grams: ";
    seeds[seedCount].availableGrams = getValidatedInteger();
    cout << "Enter used grams: ";
    seeds[seedCount].usedGrams = getValidatedInteger();
    seedCount++;
    cout << GREEN << "Yay! Seed added successfully!" << RESET;
}

void addFertilizer(Fertilizer fertilizers[], int &fertilizerCount) {
    clearScreen();
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Add Fertilizer" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    if (fertilizerCount >= 50) {
        cout << RED << "Oh no! Fertilizer inventory is full!" << RESET;
        return;
    }
    cin.ignore();
    cout << "Enter fertilizer type: ";
    getline(cin, fertilizers[fertilizerCount].type);
    cout << "Enter available kilograms: ";
    fertilizers[fertilizerCount].availableKilograms = getValidatedInteger();
    cout << "Enter used kilograms: ";
    fertilizers[fertilizerCount].usedKilograms = getValidatedInteger();
    fertilizerCount++;
    cout << GREEN << "Yay! Fertilizer added successfully!" << RESET;
}

void editSeed(Seed seeds[], int seedCount) {
    clearScreen();
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Edit Seeds Data" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    if (seedCount == 0) {
        cout << RED << "No seeds to edit yet!" << RESET;
        return;
    }
    int index;
    cout << "Enter seed index to edit (1-" << seedCount << "): ";
    index = getValidatedInteger();
    if (index < 1 || index > seedCount) {
        cout << RED << "Invalid index! Try again." << RESET;
        return;
    }
    index--;
    cout << "Editing seed: " << seeds[index].type << "\n";
    cout << "Enter new available grams: ";
    seeds[index].availableGrams = getValidatedInteger();
    cout << "Enter new used grams: ";
    seeds[index].usedGrams = getValidatedInteger();
    cout << GREEN << "Great! Seed edited successfully!" << RESET;
}

void editFertilizer(Fertilizer fertilizers[], int fertilizerCount) {
    clearScreen();
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Edit Fertilizer" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    if (fertilizerCount == 0) {
        cout << RED << "No fertilizers to edit yet!" << RESET;
        return;
    }
    int index;
    cout << "Enter fertilizer index to edit (1-" << fertilizerCount << "): ";
    index = getValidatedInteger();
    if (index < 1 || index > fertilizerCount) {
        cout << RED << "Invalid index! Try again." << RESET;
        return;
    }
    index--;
    cout << "Editing fertilizer: " << fertilizers[index].type << "\n";
    cout << "Enter new available kilograms: ";
    fertilizers[index].availableKilograms = getValidatedInteger();
    cout << "Enter new used kilograms: ";
    fertilizers[index].usedKilograms = getValidatedInteger();
    cout << GREEN << "Great! Fertilizer edited successfully!" << RESET;
}

void deleteSeed(Seed seeds[], int &seedCount) {
    clearScreen();
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Delete Seeds" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    if (seedCount == 0) {
        cout << RED << "No seeds to delete yet!" << RESET;
        return;
    }
    int index;
    cout << "Enter seed index to delete (1-" << seedCount << "): ";
    index = getValidatedInteger();
    if (index < 1 || index > seedCount) {
        cout << RED << "Invalid index! Try again." << RESET;
        return;
    }
    index--;
    for (int i = index; i < seedCount - 1; i++) {
        seeds[i] = seeds[i + 1];
    }
    seedCount--;
    cout << GREEN << "Seed deleted successfully!" << RESET;
}

void deleteFertilizer(Fertilizer fertilizers[], int &fertilizerCount) {
    clearScreen();
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Delete Fertilizer" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    if (fertilizerCount == 0) {
        cout << RED << "No fertilizers to delete yet!" << RESET;
        return;
    }
    int index;
    cout << "Enter fertilizer index to delete (1-" << fertilizerCount << "): ";
    index = getValidatedInteger();
    if (index < 1 || index > fertilizerCount) {
        cout << RED << "Invalid index! Try again." << RESET;
        return;
    }
    index--;
    for (int i = index; i < fertilizerCount - 1; i++) {
        fertilizers[i] = fertilizers[i + 1];
    }
    fertilizerCount--;
    cout << GREEN << "Fertilizer deleted successfully!" << RESET;
}

void checkAlerts(const Seed seeds[], int seedCount, const Fertilizer fertilizers[], int fertilizerCount) {
    for (int i = 0; i < seedCount; i++) {
        if (seeds[i].availableGrams < 1) {
            cout << RED << "Alert: Seed " << seeds[i].type << " is almost gone!" << RESET << endl;
        }
    }
    for (int i = 0; i < fertilizerCount; i++) {
        if (fertilizers[i].availableKilograms < 2) {
            cout << RED << "Alert: Fertilizer " << fertilizers[i].type << " is running low!" << RESET << endl;
        }
    }
}

void generateReport(const Seed seeds[], int seedCount, const Fertilizer fertilizers[], int fertilizerCount) {
    clearScreen();
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Seed Inventory Report" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    cout << left << setw(15) << "Seed Type" 
         << setw(15) << "Available (grams)" 
         << setw(15) << "Used (grams)" << endl;
    cout << string(45, '-') << endl;
    for (int i = 0; i < seedCount; i++) {
        cout << left << setw(15) << seeds[i].type 
             << setw(15) << seeds[i].availableGrams 
             << setw(15) << seeds[i].usedGrams << endl;
    }
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Fertilizer Inventory Report" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    cout << left << setw(15) << "Fertilizer Type" 
         << setw(15) << "Available (kg)" 
         << setw(15) << "Used (kg)" << endl;
    cout << string(45, '-') << endl;
    for (int i = 0; i < fertilizerCount; i++) {
        cout << left << setw(15) << fertilizers[i].type 
             << setw(15) << fertilizers[i].availableKilograms 
             << setw(15) << fertilizers[i].usedKilograms << endl;
    }
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Inventory Alerts" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    checkAlerts(seeds, seedCount, fertilizers, fertilizerCount);
    cout << RESET;
    pauseScreen();
}

// Financial Management - Let’s handle the money matters!
int financialmanagement() {
    const int MAX_RECORDS = 100;
    LivestockRecord records[MAX_RECORDS];
    int count = 0;
    int choice;
    do {
        displayMenu();
        choice = getValidatedInteger();
        switch (choice) {
            case 1: addRecord(records, count); break;
            case 2: editRecord(records, count); break;
            case 3: deleteRecord(records, count); break;
            case 4: viewFinancialReport(records, count); break;
            case 5: cout << RED << "Exiting Financial Management... Take care!" << RESET << endl; break;
            default: cout << YELLOW << "Oops! Invalid choice. Try again!" << RESET << endl; break;
        }
        pauseScreen();
    } while (choice != 5);
    return 0;
}

void displayMenu() {
    clearScreen();
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Financial Management" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    cout << "\t1. Add Record" << endl;
    cout << "\t2. Edit Record" << endl;
    cout << "\t3. Delete Record" << endl;
    cout << "\t4. View Financial Report" << endl;
    cout << "\t5. Exit" << endl;
    cout << "\n\tPlease enter your choice: ";
}

int getValidatedInteger() {
    string input;
    int value;
    while (true) {
        cin >> input;
        bool isValid = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            value = stoi(input);
            return value;
        } else {
            cout << RED << "Invalid input. " << GREEN << "Please enter a valid integer: " << RESET;
        }
    }
}

double getValidatedDouble() {
    string input;
    double value;
    while (true) {
        cin >> input;
        bool isValid = true;
        bool decimalPointSeen = false;
        for (char c : input) {
            if (!isdigit(c)) {
                if (c == '.' && !decimalPointSeen) {
                    decimalPointSeen = true;
                } else {
                    isValid = false;
                    break;
                }
            }
        }
        if (isValid) {
            value = stod(input);
            return value;
        } else {
            cout << RED << "Invalid input. " << GREEN << "Please enter a valid number: " << RESET;
        }
    }
}

void addRecord(LivestockRecord records[], int &count) {
    clearScreen();
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Add Record" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    if (count < 100) {
        cin.ignore();
        cout << GREEN << "\tEnter operation type: " << RESET;
        getline(cin, records[count].operationType);
        cout << GREEN << "\tEnter expenses: " << RESET;
        records[count].expenses = getValidatedDouble();
        cout << GREEN << "\tEnter income: " << RESET;
        records[count].income = getValidatedDouble();
        count++;
        cout << GREEN << "\t\tRecord added successfully!" << RESET << endl;
    } else {
        cout << RED << "\t\tRecord limit reached!" << RESET << endl;
    }
}

void editRecord(LivestockRecord records[], int count) {
    clearScreen();
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Edit Record" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    int index;
    if (count == 0) {
        cout << YELLOW << "No records to edit yet." << RESET << endl;
        return;
    }
    cout << GREEN << "Enter record index to edit (0 to " << count - 1 << "): " << RESET;
    index = getValidatedInteger();
    if (index >= 0 && index < count) {
        cin.ignore();
        cout << GREEN << "\tEnter new operation type: " << RESET;
        getline(cin, records[index].operationType);
        cout << GREEN << "\tEnter new expenses: " << RESET;
        records[index].expenses = getValidatedDouble();
        cout << GREEN << "\tEnter new income: " << RESET;
        records[index].income = getValidatedDouble();
        cout << YELLOW << "\t\tRecord updated successfully!" << RESET << endl;
    } else {
        cout << RED << "Invalid index!" << RESET << endl;
    }
}

void deleteRecord(LivestockRecord records[], int &count) {
    clearScreen();
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    Delete Record" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    int index;
    if (count == 0) {
        cout << YELLOW << "\tNo records to delete yet." << RESET << endl;
        return;
    }
    cout << GREEN << "\tEnter record index to delete (0 to " << count - 1 << "): " << RESET;
    index = getValidatedInteger();
    if (index >= 0 && index < count) {
        for (int i = index; i < count - 1; i++) {
            records[i] = records[i + 1];
        }
        count--;
        cout << GREEN << "\tRecord deleted successfully!" << RESET << endl;
    } else {
        cout << RED << "\tInvalid index!" << RESET << endl;
    }
}

void viewFinancialReport(LivestockRecord records[], int count) {
    clearScreen();
    cout << CYAN << "==================================================" << RESET << endl;
    cout << GREEN << "\t\t    View Financial Report" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    if (count == 0) {
        cout << YELLOW << "No records available yet." << RESET << endl;
        return;
    }
    double totalExpenses = 0, totalIncome = 0;
    cout << left << setw(20) << "Operation Type" 
         << setw(15) << "Expenses: " 
         << setw(15) << "Income: " << endl;
    for (int i = 0; i < count; i++) {
        cout << left << setw(20) << records[i].operationType 
             << setw(15) << records[i].expenses 
             << setw(15) << records[i].income << endl;
        totalExpenses += records[i].expenses;
        totalIncome += records[i].income;
    }
    cout << BLUE << "Total Expenses: " << RESET << totalExpenses << endl;
    cout << BLUE << "Total Income: " << RESET << totalIncome << endl;
    cout << BLUE << "Profit: " << RESET << totalIncome - totalExpenses << endl;
    pauseScreen();
}

// Register a new user - Welcome a new farmer to our team!
void registerUser() {
    if (userCount >= MAX_USERS) {
        cout << RED << "Sorry, we’ve reached the user limit!" << RESET;
        return;
    }
    clearScreen();
    string username, password;
    cout << CYAN << "==================================================" << RESET << endl;
    cout << BOLD << "\t\t    REGISTER BELOW:" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    cout << "\tEnter username: ";
    cin >> username;
    for (int i = 0; i < userCount; i++) {
        if (usernames[i] == username) {
            cout << RED << "Oops! That username is taken. Try another!" << RESET;
            return;
        }
    }
    cout << "\tEnter password: ";
    cin >> password;

    usernames[userCount] = username;
    passwords[userCount] = password;
    userCount++;
    cout << GREEN << "\nWelcome! User registered successfully!" << RESET << endl;
}

// Login with up to 3 attempts - Let’s get you in!
bool loginUser() { 
    clearScreen();
    string username, password;
    int attempts = 0;
    cout << CYAN << "==================================================" << RESET << endl;
    cout << BOLD << "\t\t    LOGIN HERE:" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    while (attempts < 3) {
        cout << "\tEnter username: ";
        cin >> username;
        cout << "\tEnter password: ";
        cin >> password;
        for (int i = 0; i < userCount; i++) {
            if (usernames[i] == username && passwords[i] == password) {
                cout << GREEN << "\t\tLogin successful! Welcome back!" << RESET << endl;
                return true;
            }
        }
        attempts++;
        cout << YELLOW << "Wrong credentials! " << 3 - attempts << " attempts left." << RESET << endl;
    }
    cout << RED << "Too many tries! Please come back later." << RESET;
    return false;
}

// Post-login menu - What would you like to do next?
void postLoginMenu() {
    int choice;
    do {
        clearScreen();
        cout << CYAN << "==================================================" << RESET << endl;
        cout << BOLD << "\t\t    POST LOGIN MENU" << RESET << endl;
        cout << CYAN << "==================================================" << RESET << endl;
        cout << "\t1. Crop Management" << endl;
        cout << "\t2. Livestock Management" << endl;
        cout << "\t3. Inventory Management" << endl;
        cout << "\t4. Financial Management" << endl;
        cout << "\t5. Logout" << endl;
        cout << "\n\tPlease enter your choice: ";
        choice = getValidatedInteger();
        switch (choice) {
            case 1:
                cropmanagement();
                break;
            case 2:
                livestockmanagement();
                break;
            case 3:
                inventorymanagement();
                break;
            case 4:
                financialmanagement();
                break;
            case 5:
                cout << RED << "Logging out... See you next time!" << RESET;
                return;
            default:
                cout << RED << "Oops! Invalid choice. Try again!" << RESET;
        }
        pauseScreen();
    } while (choice != 5);
}

// Change password - Time to update your secret code!
void changePassword() {
    clearScreen();
    string username, oldPassword, newPassword;
    cout << CYAN << "==================================================" << RESET << endl;
    cout << BOLD << "\t\t    CHANGE PASSWORD" << RESET << endl;
    cout << CYAN << "==================================================" << RESET << endl;
    cout << "\nEnter username: ";
    cin >> username;
    cout << "Enter old password: ";
    cin >> oldPassword;
    for (int i = 0; i < userCount; i++) {
        if (usernames[i] == username && passwords[i] == oldPassword) {
            cout << "Enter new password: ";
            cin >> newPassword;
            passwords[i] = newPassword;
            cout << GREEN << "\nPassword changed! You’re all set!" << RESET << endl;
            return;
        }
    }
    cout << RED << "\nWrong credentials! Couldn’t change password." << RESET;
}

int main() {
    int choice;
    do {    
        clearScreen();
        cout << CYAN << "==================================================" << RESET << endl;
        cout << BOLD << "\t\t    WELCOME DEAR USER!" << RESET << endl;
        cout << CYAN << "==================================================" << RESET << endl;
        cout << "\t1. Register" << endl;
        cout << "\t2. Login" << endl;
        cout << "\t3. Change Password" << endl;
        cout << "\t4. Exit" << endl;
        cout << "\n\tPlease enter your choice: ";
        choice = getValidatedInteger();
        switch (choice) {
            case 1: registerUser(); break;
            case 2: 
                if (loginUser()) {
                    postLoginMenu();
                }
                break;
            case 3: changePassword(); break;
            case 4: cout << RED << "Exiting... Goodbye for now!" << RESET; break;
            default: cout << RED << "Oops! Invalid choice. Try again!" << RESET;
        }
        pauseScreen();
    } while (choice != 4);

    return 0;
}