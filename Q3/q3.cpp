#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const int MAX_PERSONS = 10;  

class EscalationPerson {
public:
    std::string name;
    std::string position;
    std::string room;
    std::string phone;
    std::string email;

    EscalationPerson() : name(""), position(""), room(""), phone(""), email("") {}

    EscalationPerson(std::string name, std::string position, std::string room, std::string phone, std::string email)
        : name(name), position(position), room(room), phone(phone), email(email) {}

    void printInfo(int dayStart, int dayEnd, int level) const {
        std::cout << "--- Till Day " << dayEnd << " ---" << std::endl;
        std::cout << "Escalation Matrix for IRD department:" << std::endl;
        std::cout << "Day " << dayStart << "-" << dayEnd << ": Escalated to " << position << " Level - " << level << std::endl;
        std::cout << position << ": " << name << std::endl;
        std::cout << "Room: " << room << std::endl;
        std::cout << "Phone: " << phone << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "--------------------------------" << std::endl;
    }
};


int loadEscalationData(const std::string& filename, EscalationPerson escalationMatrix[], int maxSize) {
    std::ifstream file(filename);
    std::string line, name, position, room, phone, email;
    int count = 0;

    if (file.is_open()) {
        std::getline(file, line); 
        while (std::getline(file, line) && count < maxSize) {
            std::stringstream ss(line);
            std::getline(ss, name, ',');
            std::getline(ss, position, ',');
            std::getline(ss, room, ',');
            std::getline(ss, phone, ',');
            std::getline(ss, email, ',');

            escalationMatrix[count] = EscalationPerson(name, position, room, phone, email);
            count++;
        }
    } else {
        std::cerr << "Could not open the file!" << std::endl;
    }
    return count; 
}

void simulateEscalation(const EscalationPerson escalationMatrix[], int count) {
    std::cout << "--- Day 0 --- Complaint registered" << std::endl;

    int dayIntervals[] = {3, 6, 9}; 
    int levels[] = {4, 3, 2, 1};   
    int totalDays = 99;            
    
    for (int i = 0; i < 3 && i < count; i++) {
        escalationMatrix[i].printInfo(i * 3 + 1, dayIntervals[i], levels[i]);
    }

    if (count > 3) {
        std::cout << "After --- Day 9 ---" << std::endl;
        escalationMatrix[3].printInfo(10, totalDays, levels[3]);
    }
}

int main() {
    std::string filename = "iiitd_escalation.csv";
    EscalationPerson escalationMatrix[MAX_PERSONS]; 
    int count = loadEscalationData(filename, escalationMatrix, MAX_PERSONS);

    if (count > 0) {
        simulateEscalation(escalationMatrix, count);
    } else {
        std::cerr << "Escalation matrix is empty, no data to process!" << std::endl;
    }

    return 0;
}
