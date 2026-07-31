#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUCTS 100
#define MAX_CUSTOMERS 50
#define MAX_BILLS 200
#define MAX_NAME 50
#define MAX_PASSWORD 20

// Structure Definitions
typedef struct {
    int id;
    char name[MAX_NAME];
    float price;
    int quantity;
    char category[30];
    int reorder_level;
} Product;

typedef struct {
    int bill_no;
    int customer_id;
    char date[20];
    int product_count;
    int product_ids[MAX_PRODUCTS];
    int quantities[MAX_PRODUCTS];
    float total_amount;
    float discount;
    float final_amount;
} Bill;

typedef struct {
    char username[MAX_NAME];
    char password[MAX_PASSWORD];
    char role[20];
} User;

// Global Variables
Product products[MAX_PRODUCTS];
Bill bills[MAX_BILLS];
User current_user;
int product_count = 0;
int bill_count = 0;

// Function Declarations
void adminMenu();
void cashierMenu();
void addProduct();
void viewProducts();
void updateProduct();
void deleteProduct();
void searchProduct();
void generateBill();
void backupData();
void restoreData();
void manageUsers();
void applyDiscount(float *amount, float *discount);
void displayLogo();
int authenticate();
void saveData();
void loadData();

// Utility Functions
void clearScreen() {
    system("cls || clear");
}

void displayLogo() {
    printf("\n");
    printf("  ---Welcome to SUPER SHOP MANAGEMENT SYSTEM---\n");
    printf("\n");
}

void pressAnyKey() {
    printf("\nPress any key to continue...");
    getchar();
    getchar();
}

// Authentication Functions
int authenticate() {
    char username[MAX_NAME], password[MAX_PASSWORD];
    int attempts = 3;
    
    loadData();
    
    while(attempts > 0) {
        clearScreen();
        displayLogo();
        printf("\n\n\t\tLOGIN SYSTEM\n");
        printf("\t\t------------\n");
        printf("\n\tUsername: ");
        fgets(username, MAX_NAME, stdin);
        username[strcspn(username, "\n")] = 0;
        
        printf("\tPassword: ");
        fgets(password, MAX_PASSWORD, stdin);
        password[strcspn(password, "\n")] = 0;
        
        FILE *fp = fopen("users.dat", "rb");
        if(fp == NULL) {
            // Create default admin user
            User admin = {"admin", "admin123", "Admin"};
            fp = fopen("users.dat", "wb");
            fwrite(&admin, sizeof(User), 1, fp);
            fclose(fp);
            fp = fopen("users.dat", "rb");
        }
        
        User u;
        int found = 0;
        while(fread(&u, sizeof(User), 1, fp)) {
            if(strcmp(u.username, username) == 0 && strcmp(u.password, password) == 0) {
                current_user = u;
                found = 1;
                break;
            }
        }
        fclose(fp);
        
        if(found) {
            printf("\n\tLogin Successful!\n");
            printf("\tWelcome, %s!\n", current_user.username);
            printf("\tRole: %s\n", current_user.role);
            pressAnyKey();
            return 1;
        } else {
            attempts--;
            printf("\n\tInvalid credentials! %d attempts left.\n", attempts);
            if(attempts > 0) pressAnyKey();
        }
    }
    return 0;
}

// Product Management
void addProduct() {
    if(product_count >= MAX_PRODUCTS) {
        printf("Product storage full!\n");
        return;
    }
    
    Product p;
    p.id = product_count + 1;
    
    printf("\n--- Add New Product ---\n");
    printf("Product ID: %d\n", p.id);
    printf("Name: ");
    fgets(p.name, MAX_NAME, stdin);
    p.name[strcspn(p.name, "\n")] = 0;
    
    printf("Price: $");
    scanf("%f", &p.price);
    printf("Quantity: ");
    scanf("%d", &p.quantity);
    getchar();
    printf("Category: ");
    fgets(p.category, 30, stdin);
    p.category[strcspn(p.category, "\n")] = 0;
    printf("Reorder Level: ");
    scanf("%d", &p.reorder_level);
    getchar();
    
    products[product_count++] = p;
    printf("\nProduct added successfully!\n");
    saveData();
}

void viewProducts() {
    if(product_count == 0) {
        printf("No products available!\n");
        return;
    }
    
    printf("\n%-5s %-30s %-10s %-10s %-20s %-12s\n", 
           "ID", "Name", "Price", "Stock", "Category", "Reorder Level");
    printf("-------------------------------------------------------------------------------\n");
    
    for(int i = 0; i < product_count; i++) {
        printf("%-5d %-30s $%-9.2f %-10d %-20s %-12d\n", 
               products[i].id, products[i].name, products[i].price, 
               products[i].quantity, products[i].category, products[i].reorder_level);
        
        if(products[i].quantity <= products[i].reorder_level) {
            printf("  *** LOW STOCK ALERT! Only %d left ***\n", products[i].quantity);
        }
    }
}

void updateProduct() {
    int id, found = 0;
    printf("Enter Product ID to update: ");
    scanf("%d", &id);
    getchar();
    
    for(int i = 0; i < product_count; i++) {
        if(products[i].id == id) {
            found = 1;
            printf("\nCurrent Details:\n");
            printf("Name: %s\n", products[i].name);
            printf("Price: $%.2f\n", products[i].price);
            printf("Quantity: %d\n", products[i].quantity);
            printf("Category: %s\n", products[i].category);
            
            printf("\nEnter New Details:\n");
            printf("Name: ");
            fgets(products[i].name, MAX_NAME, stdin);
            products[i].name[strcspn(products[i].name, "\n")] = 0;
            
            printf("Price: $");
            scanf("%f", &products[i].price);
            printf("Quantity: ");
            scanf("%d", &products[i].quantity);
            getchar();
            printf("Category: ");
            fgets(products[i].category, 30, stdin);
            products[i].category[strcspn(products[i].category, "\n")] = 0;
            
            printf("\nProduct updated successfully!\n");
            saveData();
            break;
        }
    }
    if(!found) printf("Product not found!\n");
}

void deleteProduct() {
    int id, found = 0;
    printf("Enter Product ID to delete: ");
    scanf("%d", &id);
    getchar();
    
    for(int i = 0; i < product_count; i++) {
        if(products[i].id == id) {
            found = 1;
            for(int j = i; j < product_count - 1; j++) {
                products[j] = products[j + 1];
            }
            product_count--;
            printf("Product deleted successfully!\n");
            saveData();
            break;
        }
    }
    if(!found) printf("Product not found!\n");
}

void searchProduct() {
    int choice;
    char name[MAX_NAME];
    int id;
    
    printf("\nSearch by:\n1. ID\n2. Name\nChoice: ");
    scanf("%d", &choice);
    getchar();
    
    if(choice == 1) {
        printf("Enter Product ID: ");
        scanf("%d", &id);
        for(int i = 0; i < product_count; i++) {
            if(products[i].id == id) {
                printf("\nProduct Found:\n");
                printf("ID: %d\nName: %s\nPrice: $%.2f\nStock: %d\nCategory: %s\n",
                       products[i].id, products[i].name, products[i].price,
                       products[i].quantity, products[i].category);
                return;
            }
        }
    } else if(choice == 2) {
        printf("Enter Product Name: ");
        fgets(name, MAX_NAME, stdin);
        name[strcspn(name, "\n")] = 0;
        
        printf("\nSearch Results:\n");
        for(int i = 0; i < product_count; i++) {
            if(strstr(products[i].name, name)) {
                printf("ID: %d, Name: %s, Price: $%.2f, Stock: %d\n",
                       products[i].id, products[i].name, products[i].price,
                       products[i].quantity);
            }
        }
    }
}

void applyDiscount(float *amount, float *discount) {
    if(*amount > 500) {
        *discount = *amount * 0.10;
        printf("10%% discount applied!\n");
    } else if(*amount > 200) {
        *discount = *amount * 0.05;
        printf("5%% discount applied!\n");
    } else {
        *discount = 0;
    }
}

void generateBill() {
    if(bill_count >= MAX_BILLS) {
        printf("Bill storage full!\n");
        return;
    }
    
    Bill b;
    b.bill_no = bill_count + 1000;
    
    // Get current date
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(b.date, 20, "%Y-%m-%d %H:%M:%S", tm_info);
    
    printf("\n--- Generate Bill ---\n");
    // Add products to bill
    b.product_count = 0;
    b.total_amount = 0;
    
    while(1) {
        int prod_id, quantity;
        printf("\nEnter Product ID (0 to finish): ");
        scanf("%d", &prod_id);
        
        if(prod_id == 0) break;
        
        int found = 0;
        for(int i = 0; i < product_count; i++) {
            if(products[i].id == prod_id) {
                found = 1;
                printf("Product: %s, Price: $%.2f, Available: %d\n", 
                       products[i].name, products[i].price, products[i].quantity);
                printf("Enter Quantity: ");
                scanf("%d", &quantity);
                
                if(quantity > products[i].quantity) {
                    printf("Insufficient stock! Only %d available.\n", products[i].quantity);
                } else {
                    b.product_ids[b.product_count] = prod_id;
                    b.quantities[b.product_count] = quantity;
                    b.total_amount += products[i].price * quantity;
                    products[i].quantity -= quantity;
                    b.product_count++;
                    printf("Product added!\n");
                }
                break;
            }
        }
        if(!found) printf("Product not found!\n");
    }
    
    if(b.product_count > 0) {
        // Apply discount
        applyDiscount(&b.total_amount, &b.discount);
        b.final_amount = b.total_amount - b.discount;
        
        // Display bill
        printf("\n" "=============================================================\n");
        printf("                      SUPER SHOP BILL\n");
        printf("=============================================================\n");
        printf("Bill No: %d                    Date: %s\n", b.bill_no, b.date);
        printf("-------------------------------------------------------------\n");
        printf("%-5s %-30s %-10s %-10s %-10s\n", "No.", "Product", "Price", "Qty", "Total");
        printf("-------------------------------------------------------------\n");
        
        for(int i = 0; i < b.product_count; i++) {
            for(int j = 0; j < product_count; j++) {
                if(products[j].id == b.product_ids[i]) {
                    float subtotal = products[j].price * b.quantities[i];
                    printf("%-5d %-30s $%-9.2f %-10d $%-9.2f\n", 
                           i+1, products[j].name, products[j].price, 
                           b.quantities[i], subtotal);
                    break;
                }
            }
        }
        
        printf("-------------------------------------------------------------\n");
        printf("%-55s $%10.2f\n", "Subtotal:", b.total_amount);
        printf("%-55s $%10.2f\n", "Discount:", b.discount);
        printf("%-55s $%10.2f\n", "Total Amount:", b.final_amount);
        printf("=============================================================\n");
        
        bills[bill_count++] = b;
        saveData();
        printf("\nBill generated successfully!\n");
    } else {
        printf("\nNo products added. Bill cancelled!\n");
    }
}

// Data Persistence
void saveData() {
    FILE *fp;
    
    fp = fopen("products.dat", "wb");
    fwrite(&product_count, sizeof(int), 1, fp);
    fwrite(products, sizeof(Product), product_count, fp);
    fclose(fp);
    
    fp = fopen("bills.dat", "wb");
    fwrite(&bill_count, sizeof(int), 1, fp);
    fwrite(bills, sizeof(Bill), bill_count, fp);
    fclose(fp);
}

void loadData() {
    FILE *fp;
    
    fp = fopen("products.dat", "rb");
    if(fp != NULL) {
        fread(&product_count, sizeof(int), 1, fp);
        fread(products, sizeof(Product), product_count, fp);
        fclose(fp);
    }
    
    fp = fopen("bills.dat", "rb");
    if(fp != NULL) {
        fread(&bill_count, sizeof(int), 1, fp);
        fread(bills, sizeof(Bill), bill_count, fp);
        fclose(fp);
    }
}

void backupData() {
    system("copy products.dat products_backup.dat");
    system("copy bills.dat bills_backup.dat");
    printf("Data backup completed successfully!\n");
}

void restoreData() {
    system("copy products_backup.dat products.dat");
    system("copy bills_backup.dat bills.dat");
    loadData();
    printf("Data restored successfully!\n");
}


void manageUsers() {
    if(strcmp(current_user.role, "Admin") != 0) {
        printf("Access denied! Admin only.\n");
        return;
    }
    
    int choice;
    do {
        clearScreen();
        printf("\n--- USER MANAGEMENT ---\n");
        printf("1. Add New User\n");
        printf("2. View All Users\n");
        printf("3. Delete User\n");
        printf("0. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: {
                User new_user;
                printf("Enter username: ");
                fgets(new_user.username, MAX_NAME, stdin);
                new_user.username[strcspn(new_user.username, "\n")] = 0;
                
                printf("Enter password: ");
                fgets(new_user.password, MAX_PASSWORD, stdin);
                new_user.password[strcspn(new_user.password, "\n")] = 0;
                
                printf("Enter role (Admin/Cashier): ");
                fgets(new_user.role, 20, stdin);
                new_user.role[strcspn(new_user.role, "\n")] = 0;
                
                FILE *fp = fopen("users.dat", "ab");
                fwrite(&new_user, sizeof(User), 1, fp);
                fclose(fp);
                printf("User added successfully!\n");
                break;
            }
            case 2: {
                FILE *fp = fopen("users.dat", "rb");
                User u;
                printf("\n%-20s %-15s\n", "Username", "Role");
                printf("-----------------------------\n");
                while(fread(&u, sizeof(User), 1, fp)) {
                    printf("%-20s %-15s\n", u.username, u.role);
                }
                fclose(fp);
                break;
            }
            case 3: {
                char username[MAX_NAME];
                printf("Enter username to delete: ");
                fgets(username, MAX_NAME, stdin);
                username[strcspn(username, "\n")] = 0;
                
                FILE *fp = fopen("users.dat", "rb");
                FILE *temp = fopen("temp.dat", "wb");
                User u;
                while(fread(&u, sizeof(User), 1, fp)) {
                    if(strcmp(u.username, username) != 0) {
                        fwrite(&u, sizeof(User), 1, temp);
                    }
                }
                fclose(fp);
                fclose(temp);
                remove("users.dat");
                rename("temp.dat", "users.dat");
                printf("User deleted if existed!\n");
                break;
            }
        }
        if(choice != 0) pressAnyKey();
    } while(choice != 0);
}

// Menu Systems
void adminMenu() {
    int choice;
    do {
        clearScreen();
        displayLogo();
        printf("\n--- ADMIN MENU ---\n");
        printf("1. Product Management\n");
        printf("2. Billing System\n");
        printf("3. User Management\n");
        printf("4. Backup/Restore Data\n");
        printf("5. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: {
                int sub_choice;
                do {
                    printf("\n--- Product Management ---\n");
                    printf("1. Add Product\n2. View Products\n3. Update Product\n4. Delete Product\n5. Search Product\n0. Back\nChoice: ");
                    scanf("%d", &sub_choice);
                    getchar();
                    switch(sub_choice) {
                        case 1: addProduct(); break;
                        case 2: viewProducts(); break;
                        case 3: updateProduct(); break;
                        case 4: deleteProduct(); break;
                        case 5: searchProduct(); break;
                    }
                    if(sub_choice != 0) pressAnyKey();
                } while(sub_choice != 0);
                break;
            }
            case 2: generateBill(); pressAnyKey(); break;
            case 3: manageUsers(); break;
            case 4: {
                int sub_choice;
                printf("\n1. Backup Data\n2. Restore Data\nChoice: ");
                scanf("%d", &sub_choice);
                getchar();
                if(sub_choice == 1) backupData();
                else if(sub_choice == 2) restoreData();
                pressAnyKey();
                break;
            }
            case 0: printf("Logging out...\n"); break;
            default: printf("Invalid choice!\n"); pressAnyKey();
        }
    } while(choice != 0);
}

void cashierMenu() {
    int choice;
    do {
        clearScreen();
        displayLogo();
        printf("\n--- CASHIER MENU ---\n");
        printf("1. View Products\n");
        printf("2. Search Product\n");
        printf("3. Generate Bill\n");
        printf("0. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch(choice) {
            case 1: viewProducts(); pressAnyKey(); break;
            case 2: searchProduct(); pressAnyKey(); break;
            case 3: generateBill(); pressAnyKey(); break;
            case 0: printf("Logging out...\n"); break;
            default: printf("Invalid choice!\n"); pressAnyKey();
        }
    } while(choice != 0);
}

// Main Function
int main() {
    loadData();
    
    if(!authenticate()) {
        printf("Login failed! Exiting...\n");
        return 0;
    }
    
    if(strcmp(current_user.role, "Admin") == 0) {
        adminMenu();
    } else {
        cashierMenu();
    }
    
    saveData();
    printf("\nThank you for using SuperShop Management System!\n");
    return 0;
}
