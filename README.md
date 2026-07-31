# 🛒 Super Shop Management System

A console-based **Super Shop Management System** developed in **C**. This project demonstrates the fundamentals of C programming, including **structures, file handling, functions, arrays, authentication, and menu-driven programming**. It is designed as a first-year university project for managing products, users, and billing in a supermarket.

---

## 📌 Features

### 🔐 User Authentication
- Login system with username and password
- Role-based access (Admin & Cashier)
- Automatically creates a default admin account if no users exist

### 📦 Product Management (Admin)
- Add new products
- View all products
- Update product details
- Delete products
- Search products by ID or Name
- Low stock alert based on reorder level

### 🧾 Billing System
- Generate customer bills
- Automatic stock update after purchase
- Automatic subtotal calculation
- Discount calculation
- Final bill generation with date and bill number

### 👥 User Management (Admin)
- Add new users
- View all users
- Delete users

### 💾 Data Management
- Save product and billing data using binary files
- Backup data
- Restore data from backup

---

## 🛠️ Technologies Used

- **Language:** C
- **Compiler:** GCC / MinGW GCC
- **IDE:** Visual Studio Code
- **Concepts Used:**
  - Structures
  - Arrays
  - Functions
  - File Handling
  - String Manipulation
  - Date & Time

---

## 📂 Project Structure

```
Super-Shop-Management-System/
│
├── project.c
└── README.md
```

---

## 📋 Default Login

When running the program for the first time, a default administrator account is automatically created.

| Username | Password | Role |
|----------|----------|------|
| admin | admin123 | Admin |

---

## 📖 Admin Features

- Product Management
- Billing System
- User Management
- Backup & Restore Data

---

## 📖 Cashier Features

- View Products
- Search Products
- Generate Bills

---


## 💾 Data Storage

The project uses binary files for persistent storage.

- `products.dat` → Stores product information
- `bills.dat` → Stores billing records
- `users.dat` → Stores user credentials
- `products_backup.dat` → Product backup
- `bills_backup.dat` → Bill backup

---

## ▶️ How to Compile

Using GCC:

```bash
gcc main.c -o shop
```

Run:

**Windows**
```bash
shop.exe
```

**Linux**
```bash
./shop
```

---

## 📚 Concepts Demonstrated

- Structures (`struct`)
- Arrays
- Functions
- File Handling (`fopen`, `fread`, `fwrite`)
- User Authentication
- Menu-Driven Programming
- String Functions
- Date & Time Handling
- Inventory Management
- Billing System

---

## 🚀 Future Improvements

- Customer Management
- Sales Reports
- Invoice Printing
- Password Encryption
- Barcode Scanner Support
- Database Integration (MySQL/SQLite)
- GUI Version
- Sales Analytics Dashboard

---

## ⚠️ Known Limitations

- Maximum of 100 products
- Maximum of 200 bills
- Passwords are stored in plain text
- Uses linear search for product lookup
- Console-based interface only

---

## 👨‍💻 Author

**Maruf Hussain Mahi,**
**Taqi Tahmid,**
**Bashir Shahrier Nahid,**
**Jaber Bin Huda**
Computer Science & Engineering (CSE)  
Sylhet Engineering College

---

## ⭐ Support

If you found this project helpful, consider giving it a **⭐ Star** on GitHub!
