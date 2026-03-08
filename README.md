# 🍽️ Food Management System (C++)

A menu-driven console-based Food Management System developed in C++ that manages cafeteria food operations including food inventory, user accounts, wallet payments, and purchase tracking.
This project demonstrates proficiency in **Object-Oriented Programming (OOP)**, **C++ Standard Template Library (STL)** , and **File Handling** for persistent data storage and efficient data management.

## 🚀 Features

- Admin and User Login System
- **Full CRUD Operations:** Add, View, Update, Search, and Delete food records.
- **Data Persistence:** Uses File Handling to store records in a `.txt` file, ensuring data is retained after the program closes.
- **Advanced Filtering:**
  - Search by name or category (Sweet/Spice).
  - Filter items within specific calorie ranges.
  - Identify items with above-average calorie counts.
  - Track Food Calories, Price, and Category
  - Wallet System for users to add money and purchase food
  - Purchase History Tracking
  - Daily Sales Reporting
- **Data Analytics:**
  - Calculate average calories across all items.
  - Find the highest and lowest calorie food items.
- **Sorting:** Efficiently sort data by Calories or Name using STL algorithms.
- **Error Handling:** Robust custom exception handling for "Item Not Found" or "Empty Database" scenarios.

## 📺 Project Walkthrough

[![Watch the Demo Video](https://img.icons8.com/?size=100&id=HUndmeQRiULI&format=png&color=000000)](https://drive.google.com/file/d/1Cni3126hZAF6OflI60B8tF0IlRVFDMNr/view?usp=sharing)

_Click the icon above to watch the project demo on Google Drive._

📂 Project Structure

FoodManagementSystem
│
├── FoodManagementSystem.cpp
│
└── FoodFile/
  ├── food.txt
  ├── wallet.txt
  ├── purchaseHistory.txt
  └── users.txt

📌 Learning Outcomes

- Applied OOP principles such as encapsulation and modular design
- Implemented file-based data persistence using File I/O
- Utilized STL containers for efficient data manipulation
- Built a complete console-based management system

## 🛠️ Technical Stack

- **Language:** C++
- **Concepts:** Classes & Objects, Encapsulation, Constructors, Exception Handling.
- **Data Structures:** `std::vector` (Dynamic Array).
- **Libraries:** `<algorithm>` (Sorting/Searching), `<fstream>` (File handling), `<iomanip>` (UI Formatting).

## 📋 How to Run

1. **Prerequisites:** Ensure you have a C++ compiler installed (GCC/MinGW).
2. **Clone the repo:**
   ```bash
   git clone https://github.com
   ```

📜 License

This project is for learning and educational purposes.
