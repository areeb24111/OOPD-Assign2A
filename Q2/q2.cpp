#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int MAX_FAC = 10; 
const int MAX_DEPTS = 10; 

class Person {
protected:
    string name;
    string role;
    string room;
    string phone;
    string email;

public:
    Person(const string& n, const string& r, const string& rm, const string& p, const string& e)
        : name(n), role(r), room(rm), phone(p), email(e) {}

    string getName() const { return name; }
    string getRole() const { return role; }
    string getRoom() const { return room; }
    string getPhone() const { return phone; }
    string getEmail() const { return email; }

    virtual void showInfo() const {
        cout << "Name: " << name << endl;
        cout << "Role: " << role << endl;
        cout << "Room: " << room << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << email << endl;
    }
};

class Faculty : public Person {
public:
    Faculty(const string& n, const string& r, const string& rm, const string& p, const string& e)
        : Person(n, r, rm, p, e) {}

    Faculty() : Person("", "", "", "", "") {}

    void showInfo() const override {
        cout << "--- Faculty Details ---" << endl;
        Person::showInfo();
    }
};

class Department {
private:
    string name;
    Faculty faculty[MAX_FAC];
    int count;

public:
    Department() : name(""), count(0) {}
    Department(const string& n) : name(n), count(0) {}

    void addFaculty(const Faculty& f) {
        if (count < MAX_FAC) {
            faculty[count] = f;
            count++;
        } else {
            cout << "Max faculty limit reached in: " << name << endl;
        }
    }

    string getName() const { return name; }

    void showDeptInfo() const {
        cout << "--- Department: " << name << " ---" << endl;
        for (int i = 0; i < count; ++i) {
            faculty[i].showInfo();
            cout << endl;
        }
    }

    const Faculty* findFaculty(const string& fName) const {
        for (int i = 0; i < count; i++) {
            if (faculty[i].getName() == fName) {
                return &faculty[i];
            }
        }
        return nullptr;
    }
};

class University {
private:
    Department depts[MAX_DEPTS];
public:
    int deptCount;

    University() : deptCount(0) {}

    void addDept(const Department& d) {
        if (deptCount < MAX_DEPTS) {
            depts[deptCount] = d;
            deptCount++;
        } else {
            cout << "Max departments limit reached!" << endl;
        }
    }

    Department* getDepts() {
        return depts; 
    }

    const Faculty* findFaculty(const string& fName) const {
        for (int i = 0; i < deptCount; ++i) {
            const Faculty* found = depts[i].findFaculty(fName);
            if (found) {
                return found;
            }
        }
        return nullptr;
    }
};

void loadUniDataFromCSV(University& uni, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open " << filename << endl;
        return;
    }

    string line;
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        string dept, name, role, room, phone, email;

        getline(ss, dept, ',');
        getline(ss, name, ',');
        getline(ss, role, ',');
        getline(ss, room, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');

        Faculty f(name, role, room, phone, email);

        bool foundDept = false;
        for (int i = 0; i < uni.deptCount; ++i) {
            if (uni.getDepts()[i].getName() == dept) {
                uni.getDepts()[i].addFaculty(f);
                foundDept = true;
                break;
            }
        }

        if (!foundDept) {
            Department newDept(dept);
            newDept.addFaculty(f);
            uni.addDept(newDept);
        }
    }

    file.close();
}

int main() {
    University uni;
    loadUniDataFromCSV(uni, "iiitd_academics.csv");

    string input;
    while (true) {
        cout << "Enter faculty name (or 'quit' to exit): ";
        getline(cin, input);

        if (input == "quit") {
            break;
        }

        const Faculty* f = uni.findFaculty(input);
        if (f) {
            f->showInfo();
        } else {
            cout << "Faculty member not found." << endl;
        }
        cout << endl;
    }

    return 0;
}

