#ifndef BOOK_H
#define BOOK_H
#include "LibraryItem.cpp"
#include <string>      // Ensure you include <string> for std::string
#include <iostream>    // Include this to use std::cout

using namespace std;

class Book : public LibraryItem
{
private:
    int ID;
    int book_id;
    int isbn;
    std::string title;   // Use std::string
    std::string authors; // Use std::string
    int original_publication_year;
    bool borrowed;

public:
    // Constructor
    Book() : book_id(0), isbn(0), title(""), authors(""), original_publication_year(0), borrowed(false) {}
    
    Book(int ID, int book_id, int isbn, const std::string &title, const std::string &authors, int original_publication_year)
        : ID(ID), book_id(book_id), isbn(isbn), title(title), authors(authors), original_publication_year(original_publication_year), borrowed(false)
    {
    }

    // Getter and setter functions
    int getID() const { return ID; }
    void setID(int id) { ID = id; }

    int getBookID() const { return book_id; }
    void setBookID(int bookid) { book_id = bookid; }

    int getISBN() const { return isbn; }
    void setISBN(int Isbn) { isbn = Isbn; }

    std::string getTitle() const { return title; }
    void setTitle(const std::string &newTitle) { title = newTitle; }

    std::string getAuthors() const { return authors; }
    void setAuthors(const std::string &newAuthor) { authors = newAuthor; }

    int getPublicationYear() const { return original_publication_year; }
    void setPublicationYear(int year) { original_publication_year = year; }

    bool isBorrowed() const { return borrowed; }
    void setBorrowed(bool status) { borrowed = status; }

    void printDetails() const override
    {
        cout << "ID: " << ID
             << "\nBook_id: " << book_id
             << "\nISBN: " << isbn
             << "\nTitle: " << title
             << "\nAuthors: " << authors
             << "\nPublication Year: " << original_publication_year
             << "\n";
    }
};
#endif
