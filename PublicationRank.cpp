#ifndef PUBLICATIONRANK_H
#define PUBLICATIONRANK_H
#include <iostream>
#include "LibraryItem.cpp"
using namespace std; // Optional: You can remove this and use std:: for string, cout, etc.

class PublicationRank : public LibraryItem
{
private:
    int ID;
    string publication; // Use std::string
    int rank;
    double totalPaid;
    bool borrowed;

public:
    // Constructor
    PublicationRank(int ID, const std::string &publication, int rank, double totalPaid)
        : ID(ID), publication(publication), rank(rank), totalPaid(totalPaid), borrowed(false) {}

    int getID() const
    {
        return ID;
    }

    string getPublication() const // Use std::string
    {
        return publication;
    }

    int getrank() const
    {
        return rank;
    }

    double gettotalPaid() const
    {
        return totalPaid;
    }

    bool isBorrowed() const
    {
        return borrowed;
    }

    void setBorrowed(bool status)
    {
        borrowed = status;
    }

    void printDetails() const override
    {
        cout << "ID: " << ID
             << "\nPublication Name: " << publication
             << "\nRank: " << rank
             << "\nTotal Paid: " << totalPaid
             << "\n";
    }
};
#endif
