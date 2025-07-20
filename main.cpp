#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    string id;
    string phone;

public:
    Person(string n, string i, string p) {
        name = n;
        id = i;
        phone = p;
    }
    
    virtual void display() {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Phone: " << phone << endl;
    }
    
    string getName() { return name; }
    string getId() { return id; }
    string getPhone() { return phone; }
};

class Book {
private:
    string title;
    string author;
    string isbn;
    bool isIssued;

public:
    Book(string t, string a, string i) {
        title = t;
        author = a;
        isbn = i;
        isIssued = false;
    }
    
    void displayBook() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Status: " << (isIssued ? "Issued" : "Available") << endl;
        cout << "------------------------" << endl;
    }
    
    bool issueBook() {
        if (!isIssued) {
            isIssued = true;
            return true;
        }
        return false;
    }
    
    bool returnBook() {
        if (isIssued) {
            isIssued = false;
            return true;
        }
        return false;
    }
    
    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getIsbn() { return isbn; }
    bool getStatus() { return isIssued; }
};

class Student : public Person {
private:
    string course;
    int booksIssued;
    int maxBooks;

public:
    Student(string n, string i, string p, string c) : Person(n, i, p) {
        course = c;
        booksIssued = 0;
        maxBooks = 3;
    }
    
    void display() override {
        cout << "=== STUDENT DETAILS ===" << endl;
        Person::display();
        cout << "Course: " << course << endl;
        cout << "Books Issued: " << booksIssued << "/" << maxBooks << endl;
        cout << "========================" << endl;
    }
    
    bool canIssueBook() {
        return booksIssued < maxBooks;
    }
    
    void issueBook() {
        if (canIssueBook()) {
            booksIssued++;
        }
    }
    
    void returnBook() {
        if (booksIssued > 0) {
            booksIssued--;
        }
    }
    
    int getBooksIssued() { return booksIssued; }
};

class Librarian : public Person {
private:
    string department;

public:
    Librarian(string n, string i, string p, string d) : Person(n, i, p) {
        department = d;
    }
    
    void display() override {
        cout << "=== LIBRARIAN DETAILS ===" << endl;
        Person::display();
        cout << "Department: " << department << endl;
        cout << "==========================" << endl;
    }
};

class Library {
private:
    vector<Book> books;
    vector<Student> students;
    vector<Librarian> librarians;

public:
    void addBook(Book b) {
        books.push_back(b);
        cout << "Book added successfully!" << endl;
    }
    
    void addStudent(Student s) {
        students.push_back(s);
        cout << "Student registered successfully!" << endl;
    }
    
    void addLibrarian(Librarian l) {
        librarians.push_back(l);
        cout << "Librarian added successfully!" << endl;
    }
    
    void displayAllBooks() {
        cout << "\n=== ALL BOOKS ===" << endl;
        for (int i = 0; i < books.size(); i++) {
            books[i].displayBook();
        }
    }
    
    void displayAllStudents() {
        cout << "\n=== ALL STUDENTS ===" << endl;
        for (int i = 0; i < students.size(); i++) {
            students[i].display();
        }
    }
    
    void issueBook(string studentId, string isbn) {
        Student* student = nullptr;
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getId() == studentId) {
                student = &students[i];
                break;
            }
        }
        
        if (student == nullptr) {
            cout << "Student not found!" << endl;
            return;
        }
        
        if (!student->canIssueBook()) {
            cout << "Student has reached maximum book limit!" << endl;
            return;
        }
        
        Book* book = nullptr;
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getIsbn() == isbn) {
                book = &books[i];
                break;
            }
        }
        
        if (book == nullptr) {
            cout << "Book not found!" << endl;
            return;
        }
        
        if (book->getStatus()) {
            cout << "Book is already issued!" << endl;
            return;
        }
        
        book->issueBook();
        student->issueBook();
        cout << "Book issued successfully to " << student->getName() << endl;
    }
    
    void returnBook(string studentId, string isbn) {
        Student* student = nullptr;
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getId() == studentId) {
                student = &students[i];
                break;
            }
        }
        
        if (student == nullptr) {
            cout << "Student not found!" << endl;
            return;
        }
        
        Book* book = nullptr;
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getIsbn() == isbn) {
                book = &books[i];
                break;
            }
        }
        
        if (book == nullptr) {
            cout << "Book not found!" << endl;
            return;
        }
        
        if (!book->getStatus()) {
            cout << "Book is not issued!" << endl;
            return;
        }
        
        book->returnBook();
        student->returnBook();
        cout << "Book returned successfully by " << student->getName() << endl;
    }
    
    void searchBook(string title) {
        cout << "\n=== SEARCH RESULTS ===" << endl;
        bool found = false;
        for (int i = 0; i < books.size(); i++) {
            if (books[i].getTitle().find(title) != string::npos) {
                books[i].displayBook();
                found = true;
            }
        }
        if (!found) {
            cout << "No books found with title: " << title << endl;
        }
    }
};

void showMenu() {
    cout << "\n=== LIBRARY MANAGEMENT SYSTEM ===" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add Student" << endl; 
    cout << "3. Display All Books" << endl;
    cout << "4. Display All Students" << endl;
    cout << "5. Issue Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Search Book" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Library lib;
    int choice;
    
    cout << "=== ADDING SAMPLE DATA ===" << endl;
    lib.addBook(Book("C++ Programming", "Bjarne Stroustrup", "123456"));
    lib.addBook(Book("Data Structures", "Mark Weiss", "789012"));
    lib.addBook(Book("Algorithms", "Robert Sedgewick", "345678"));
    
    lib.addStudent(Student("John Doe", "S001", "9876543210", "Computer Science"));
    lib.addStudent(Student("Jane Smith", "S002", "9876543211", "Information Technology"));
    
    lib.addLibrarian(Librarian("Mr. Anderson", "L001", "9876543212", "Computer Science"));
    
    cout << "\n=== DEMO OPERATIONS ===" << endl;
    
    lib.displayAllBooks();
    
    lib.displayAllStudents();
    
    cout << "\n=== ISSUING BOOK ===" << endl;
    lib.issueBook("S001", "123456");
    
    cout << "\n=== BOOKS AFTER ISSUING ===" << endl;
    lib.displayAllBooks();
    
    cout << "\n=== STUDENTS AFTER ISSUING ===" << endl;
    lib.displayAllStudents();
    
    cout << "\n=== RETURNING BOOK ===" << endl;
    lib.returnBook("S001", "123456");
    
    cout << "\n=== SEARCHING BOOKS ===" << endl;
    lib.searchBook("C++");
    
    cout << "\n=== DEMO COMPLETED ===" << endl;
    cout << "Program executed successfully!" << endl;
    
    return 0;
}