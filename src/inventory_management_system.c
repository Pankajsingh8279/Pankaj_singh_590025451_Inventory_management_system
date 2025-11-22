#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Product {
    int id;
    char name[50];
    int quantity;
    float price;
};

// Utility safe input functions
int inputInt(char msg[]) {
    char buffer[100];
    int value;

    while (1) {
        printf("%s", msg);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%d", &value) == 1)
            return value;

        printf("Invalid input! Please enter a valid integer.\n");
    }
}

float inputFloat(char msg[]) {
    char buffer[100];
    float value;

    while (1) {
        printf("%s", msg);
        fgets(buffer, sizeof(buffer), stdin);

        if (sscanf(buffer, "%f", &value) == 1)
            return value;

        printf("Invalid input! Please enter a valid number.\n");
    }
}

void inputString(char msg[], char *str) {
    char buffer[100];
    printf("%s", msg);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  // remove newline
    strcpy(str, buffer);
}

// Function Prototypes
void addProduct(struct Product p[], int *n);
void displayProducts(struct Product p[], int n);
void searchProduct(struct Product p[], int n);
void updateProduct(struct Product p[], int n);
void deleteProduct(struct Product p[], int *n);
void saveToFile(struct Product p[], int n);
int loadFromFile(struct Product p[]);

int main() {
    struct Product p[100];
    int n = loadFromFile(p);
    int choice;
    char buffer[50];

    while (1) {
        printf("\n===== Inventory Management System =====\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Search Product\n");
        printf("4. Update Product\n");
        printf("5. Delete Product\n");
        printf("6. Save & Exit\n");

        choice = inputInt("Enter your choice: ");

        switch (choice) {
            case 1: addProduct(p, &n); break;
            case 2: displayProducts(p, n); break;
            case 3: searchProduct(p, n); break;
            case 4: updateProduct(p, n); break;
            case 5: deleteProduct(p, &n); break;
            case 6: saveToFile(p, n); printf("Data saved. Exiting...\n"); exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

// Add Product
void addProduct(struct Product p[], int *n) {
    p[*n].id = inputInt("Enter Product ID: ");
    inputString("Enter Product Name: ", p[*n].name);
    p[*n].quantity = inputInt("Enter Quantity: ");
    p[*n].price = inputFloat("Enter Price: ");

    (*n)++;
    printf("Product Added Successfully!\n");
}

// Display Products
void displayProducts(struct Product p[], int n) {
    if (n == 0) {
        printf("No products in inventory!\n");
        return;
    }

    printf("\n%-10s %-20s %-10s %-10s\n", "ID", "Name", "Qty", "Price");
    for (int i = 0; i < n; i++) {
        printf("%-10d %-20s %-10d %-10.2f\n",
               p[i].id, p[i].name, p[i].quantity, p[i].price);
    }
}

// Search Product
void searchProduct(struct Product p[], int n) {
    int id = inputInt("Enter Product ID to search: ");
    int found = 0;

    for (int i = 0; i < n; i++) {
        if (p[i].id == id) {
            printf("Product Found:\n");
            printf("ID: %d\nName: %s\nQuantity: %d\nPrice: %.2f\n",
                   p[i].id, p[i].name, p[i].quantity, p[i].price);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Product Not Found!\n");
}

// Update Product
void updateProduct(struct Product p[], int n) {
    int id = inputInt("Enter Product ID to update: ");
    int found = 0;

    for (int i = 0; i < n; i++) {
        if (p[i].id == id) {
            p[i].quantity = inputInt("Enter New Quantity: ");
            p[i].price = inputFloat("Enter New Price: ");
            printf("Product Updated Successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Product Not Found!\n");
}

// Delete Product
void deleteProduct(struct Product p[], int *n) {
    int id = inputInt("Enter Product ID to delete: ");
    int found = 0;

    for (int i = 0; i < *n; i++) {
        if (p[i].id == id) {
            for (int j = i; j < *n - 1; j++) {
                p[j] = p[j + 1];
            }

            (*n)--;
            printf("Product Deleted Successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Product Not Found!\n");
}

// Save Data to File
void saveToFile(struct Product p[], int n) {
    FILE *fp = fopen("inventory.txt", "w");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d %s %d %.2f\n",
                p[i].id, p[i].name, p[i].quantity, p[i].price);
    }
    fclose(fp);
}

// Load Data from File
int loadFromFile(struct Product p[]) {
    FILE *fp = fopen("inventory.txt", "r");
    if (!fp) return 0;

    int i = 0;
    while (fscanf(fp, "%d %s %d %f",
                  &p[i].id, p[i].name, &p[i].quantity, &p[i].price) != EOF) {
        i++;
    }

    fclose(fp);
    return i;
}
