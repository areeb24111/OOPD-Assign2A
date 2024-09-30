#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Individual {
protected:
    char fullName[50];
    char jobTitle[50];
    char officeNo[100];
    char contactNo[20];
    char emailID[50];

public:
    Individual(const char* n, const char* title, const char* office, const char* phone, const char* email) {
        strncpy(fullName, n, 49);
        strncpy(jobTitle, title, 49);
        strncpy(officeNo, office, 19);
        strncpy(contactNo, phone, 19);
        strncpy(emailID, email, 49);
        fullName[49] = jobTitle[49] = officeNo[19] = contactNo[19] = emailID[49] = '\0';
    }

    const char* getFullName() const { return fullName; }
    const char* getJobTitle() const { return jobTitle; }
    const char* getOfficeNo() const { return officeNo; }
    const char* getContactNo() const { return contactNo; }
    const char* getEmailID() const { return emailID; }

    virtual void showDetails() const {
        cout << "Full Name: " << fullName << endl;
        cout << "Job Title: " << jobTitle << endl;
        cout << "Office No: " << officeNo << endl;
        cout << "Contact No: " << contactNo << endl;
        cout << "Email ID: " << emailID << endl;
    }
};

class HeadRegistrar : public Individual {
public:
    HeadRegistrar(const char* n, const char* office, const char* phone, const char* email)
        : Individual(n, "Registrar", office, phone, email) {}

    void showDetails() const override {
        cout << "--- Registrar Information ---" << endl;
        Individual::showDetails();
    }
};

class AcademicDean : public Individual {
protected:
    char department[50];

public:
    AcademicDean(const char* n, const char* dept, const char* office, const char* phone, const char* email)
        : Individual(n, "Dean", office, phone, email) {
        strncpy(department, dept, 49);
        department[49] = '\0';
    }

    const char* getDepartment() const { return department; }

    void showDetails() const override {
        cout << "--- Dean Information ---" << endl;
        Individual::showDetails();
        cout << "Department: " << department << endl;
    }
};

class AssistantDean : public AcademicDean {
public:
    AssistantDean(const char* n, const char* dept, const char* office, const char* phone, const char* email)
        : AcademicDean(n, dept, office, phone, email) {
        strncpy(jobTitle, "Associate Dean", 49);
    }

    void showDetails() const override {
        cout << "--- Associate Dean Information ---" << endl;
        AcademicDean::showDetails();
    }
};

class StaffMember : public Individual {
protected:
    char department[50];

public:
    StaffMember(const char* n, const char* title, const char* dept, const char* office, const char* phone, const char* email)
        : Individual(n, title, office, phone, email) {
        strncpy(department, dept, 49);
        department[49] = '\0';
    }

    const char* getDepartment() const { return department; }

    void showDetails() const override {
        cout << "--- Staff Information ---" << endl;
        Individual::showDetails();
        cout << "Department: " << department << endl;
    }
};

class Division {
private:
    char name[50];
    AcademicDean* dean;
    AssistantDean* assistantDean;
    StaffMember* staff[10];
    int staffCount;

public:
    Division(const char* n) : dean(nullptr), assistantDean(nullptr), staffCount(0) {
        strncpy(name, n, 49);
        name[49] = '\0';
    }

    void assignDean(AcademicDean* d) { dean = d; }
    void assignAssistantDean(AssistantDean* ad) { assistantDean = ad; }
    void addStaff(StaffMember* s) {
        if (staffCount < 10) {
            staff[staffCount++] = s;
        }
    }

    const char* getDivisionName() const { return name; }
    AcademicDean* getDean() const { return dean; }
    AssistantDean* getAssistantDean() const { return assistantDean; }
    int getStaffCount() const { return staffCount; }
    StaffMember* getStaffMember(int index) const {
        if (index >= 0 && index < staffCount) {
            return staff[index];
        }
        return nullptr;
    }
};

class Administration {
private:
    HeadRegistrar* registrar;
    Division* divisions[5];
    int divisionCount;

public:
    Administration() : registrar(nullptr), divisionCount(0) {}

    void assignRegistrar(HeadRegistrar* r) { registrar = r; }
    void addDivision(Division* d) {
        if (divisionCount < 5) {
            divisions[divisionCount++] = d;
        }
    }

    Individual* findIndividual(const char* name) const {
        if (registrar && strcmp(registrar->getFullName(), name) == 0) {
            return registrar;
        }

        for (int i = 0; i < divisionCount; ++i) {
            Division* div = divisions[i];
            if (div->getDean() && strcmp(div->getDean()->getFullName(), name) == 0) {
                return div->getDean();
            }
            if (div->getAssistantDean() && strcmp(div->getAssistantDean()->getFullName(), name) == 0) {
                return div->getAssistantDean();
            }
            for (int j = 0; j < div->getStaffCount(); ++j) {
                StaffMember* staff = div->getStaffMember(j);
                if (staff && strcmp(staff->getFullName(), name) == 0) {
                    return staff;
                }
            }
        }
        return nullptr;
    }

    void loadFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            return;
        }

        string line;
        getline(file, line); 

        while (getline(file, line)) {
            stringstream ss(line);
            string dept, name, title, office, phone, email;

            getline(ss, dept, ',');
            getline(ss, name, ',');
            getline(ss, title, ',');
            getline(ss, office, ',');
            getline(ss, phone, ',');
            getline(ss, email, ',');

            if (title.find("Registrar") != string::npos) {
                HeadRegistrar* registrar = new HeadRegistrar(name.c_str(), office.c_str(), phone.c_str(), email.c_str());
                assignRegistrar(registrar);
            } else if (title.find("Dean") != string::npos) {
                if (title.find("Associate Dean") != string::npos) {
                    AssistantDean* assocDean = new AssistantDean(name.c_str(), dept.c_str(), office.c_str(), phone.c_str(), email.c_str());
                    for (int i = 0; i < divisionCount; ++i) {
                        if (strcmp(divisions[i]->getDivisionName(), dept.c_str()) == 0) {
                            divisions[i]->assignAssistantDean(assocDean);
                        }
                    }
                } else {
                    AcademicDean* dean = new AcademicDean(name.c_str(), dept.c_str(), office.c_str(), phone.c_str(), email.c_str());
                    for (int i = 0; i < divisionCount; ++i) {
                        if (strcmp(divisions[i]->getDivisionName(), dept.c_str()) == 0) {
                            divisions[i]->assignDean(dean);
                        }
                    }
                }
            } else {
                StaffMember* staff = new StaffMember(name.c_str(), title.c_str(), dept.c_str(), office.c_str(), phone.c_str(), email.c_str());
                for (int i = 0; i < divisionCount; ++i) {
                    if (strcmp(divisions[i]->getDivisionName(), dept.c_str()) == 0) {
                        divisions[i]->addStaff(staff);
                    }
                }
            }
        }

        file.close();
    }
};

int main() {
    Administration iiitd;

    Division* ird = new Division("Innovation Research & Development");
    Division* academics = new Division("Academics");
    Division* studentAffairs = new Division("Student Affairs");
    Division* library = new Division("Library");
    Division* storeAndPurchase = new Division("Store and Purchase");

    iiitd.addDivision(ird);
    iiitd.addDivision(academics);
    iiitd.addDivision(studentAffairs);
    iiitd.addDivision(library);
    iiitd.addDivision(storeAndPurchase);

    iiitd.loadFromCSV("IIITD.csv");

    char input[50];
    while (true) {
        cout << "Enter the name of the individual to find (or type 'exit' to quit): ";
        cin.getline(input, 50);

        if (strcmp(input, "exit") == 0) {
            break; 
        }

        Individual* foundIndividual = iiitd.findIndividual(input);
        if (foundIndividual) {
            foundIndividual->showDetails();
            break; 
        } else {
            cout << "Individual not found! Please try again." << endl;
        }
    }

    return 0;
}

