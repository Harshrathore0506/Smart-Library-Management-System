#include <iostream>
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>
#include <map>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    Book() : id(0), issued(false) {}
    Book(int i, string t, string a, bool is)
        : id(i), title(t), author(a), issued(is) {}
};

class Library {
private:
    unordered_map<int, Book> books;
    set<int> sortedIds;
    queue<int> issueQueue;
    stack<string> undoStack;
    map<int, int> borrowCount;

public:
    Library() {
        loadBooks();
        loadBorrowCount();
    }

    ~Library() {
        saveBooks();
        saveBorrowCount();
    }

    void loadBooks() {
        ifstream file("books.txt");
        if (!file) return;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, title, author, issued;

            getline(ss, id, '|');
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, issued, '|');

            Book b(stoi(id), title, author, stoi(issued));
            books[b.id] = b;
            sortedIds.insert(b.id);
        }
        file.close();
    }

    void saveBooks() {
        ofstream file("books.txt");
        for (int id : sortedIds) {
            Book b = books[id];
            file << b.id << "|"
                 << b.title << "|"
                 << b.author << "|"
                 << b.issued << "\n";
        }
        file.close();
    }

    void loadBorrowCount() {
        ifstream file("borrow_count.txt");
        if (!file) return;

        int id, count;
        while (file >> id >> count) {
            borrowCount[id] = count;
        }
        file.close();
    }

    void saveBorrowCount() {
        ofstream file("borrow_count.txt");
        for (auto &p : borrowCount) {
            file << p.first << " " << p.second << "\n";
        }
        file.close();
    }

    void addBook() {
        int id;
        string title, author;

        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        books[id] = Book(id, title, author, false);
        sortedIds.insert(id);
        undoStack.push("ADD " + to_string(id));

        saveBooks();
        cout << "Book added & saved\n";
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "Library is empty\n";
            return;
        }

        cout << "\n------------------------------------------------------------\n";
        cout << left << setw(8) << "ID"
             << setw(20) << "TITLE"
             << setw(15) << "AUTHOR"
             << setw(12) << "STATUS\n";
        cout << "------------------------------------------------------------\n";

        for (int id : sortedIds) {
            Book b = books[id];
            cout << left << setw(8) << b.id
                 << setw(20) << b.title
                 << setw(15) << b.author
                 << setw(12) << (b.issued ? "Issued" : "Available") << "\n";
        }
    }

    void requestIssue() {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;

        if (!books.count(id)) {
            cout << "Book not found\n";
            return;
        }

        issueQueue.push(id);
        cout << "Issue request added\n";
    }

    void processIssue() {
        if (issueQueue.empty()) {
            cout << "No issue requests\n";
            return;
        }

        int id = issueQueue.front();
        issueQueue.pop();

        if (!books[id].issued) {
            books[id].issued = true;
            borrowCount[id]++;
            undoStack.push("ISSUE " + to_string(id));
            saveBooks();
            saveBorrowCount();
            cout << "Book issued\n";
        } else {
            cout << "Already issued\n";
        }
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        if (books.count(id) && books[id].issued) {
            books[id].issued = false;
            undoStack.push("RETURN " + to_string(id));
            saveBooks();
            cout << "Book returned\n";
        } else {
            cout << "Invalid return\n";
        }
    }

    void mostBorrowed() {
        if (borrowCount.empty()) {
            cout << "No borrow data\n";
            return;
        }

        int maxId = -1, maxCount = 0;
        for (auto &p : borrowCount) {
            if (p.second > maxCount) {
                maxCount = p.second;
                maxId = p.first;
            }
        }

        cout << "Most Borrowed Book:\n";
        cout << "ID: " << maxId
             << " | Title: " << books[maxId].title
             << " | Times: " << maxCount << "\n";
    }
};

int main() {
    Library lib;
    int choice;

    do {
        cout << "\n===== SMART LIBRARY (FILE HANDLING) =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Request Issue\n";
        cout << "4. Process Issue\n";
        cout << "5. Return Book\n";
        cout << "6. Most Borrowed Book\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: lib.addBook(); break;
        case 2: lib.displayBooks(); break;
        case 3: lib.requestIssue(); break;
        case 4: lib.processIssue(); break;
        case 5: lib.returnBook(); break;
        case 6: lib.mostBorrowed(); break;
        case 0: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice\n";
        }
    } while (choice != 0);

    return 0;
}
