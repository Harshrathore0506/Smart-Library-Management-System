# 📚 Smart Library Management System (C++)

A **console-based Smart Library Management System** built using **C++**, showcasing **Object-Oriented Programming, STL containers, and File Handling**.  
This project manages books, handles issue/return workflows, and tracks borrowing statistics with **persistent storage**.

---

## 🚀 Features

### 📘 Book Management
- Add books with **ID, Title, Author**
- Display all books in a **sorted tabular format**
- Data automatically saved to files

### 🔄 Issue & Return System
- Request book issue using a **queue (FIFO)**
- Process issue requests
- Return books safely
- Prevents issuing already issued books

### 📊 Analytics
- Tracks how many times a book is borrowed
- Displays the **most borrowed book**

### 💾 File Handling (Persistence)
- Books stored in `books.txt`
- Borrow statistics stored in `borrow_count.txt`
- Data loads automatically on program start
- Data saves automatically on exit

---

## 🧠 Data Structures Used

| Purpose | STL Container |
|------|--------------|
| Fast book lookup | `unordered_map` |
| Sorted book display | `set` |
| Issue requests | `queue` |
| Undo operations | `stack` |
| Borrow count tracking | `map` |

---

## 🛠️ Tech Stack

- **Language:** C++
- **Concepts Used:**
  - OOP (Classes & Objects)
  - STL Containers
  - File Handling
  - Queue & Stack
  - Maps & Sets
- **Compiler:** GCC / MinGW / g++

---
