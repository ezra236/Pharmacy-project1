#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Pharmacy {
private:
    double total = 0.0;
    string productDetails;
    int productQuantities[8] = {10, 10, 10, 10, 10, 10, 10, 10}; // Initial quantity for each product
    string adminPassword = "123"; // Administrator password

public:
    void processOrder(const string& productName, double productPrice) {
        int productIndex = getProductIndex(productName);
        if (productIndex >= 0) {
            if (productQuantities[productIndex] > 0) {
                total += productPrice;
                productDetails += productName + "\t\t$" + to_string(productPrice) + "\n";
                productQuantities[productIndex]--;
                cout << "Adding " << productName << " to the order. Price: $" << productPrice << endl;
            } else {
                cout << "Product " << productName << " is out of stock." << endl;
            }
        } else {
            cout << "Invalid product name. Please try again." << endl;
        }
    }

    void addProductQuantity(const string& productName, int quantity, const string& password) {
        if (adminPassword == password) {
            int productIndex = getProductIndex(productName);
            if (productIndex >= 0) {
                productQuantities[productIndex] += quantity;
                cout << "--------------------------------------------------------------------------\n";
                cout << "Added " << quantity << " packets of " << productName << " to the stock." << endl;
                cout << "\nNEW QUANTITY OF " << productName << ": " << productQuantities[productIndex] << " packets\n" << endl;
            } else {
                cout << "Invalid product name. Please try again." << endl;
            }
        } else {
            cout << "Incorrect password. Only the administrator can add product quantity." << endl;
        }
    }

    void printReceipt() {
        ofstream file("receipt.txt");
        if (file.is_open()) {
            file << "------ Receipt ------" << endl;
            file << "Product\t\tPrice" << endl;
            file << productDetails;
            file << "---------------------" << endl;
            file << "Total:\t\t$" << total << endl;
            file.close();

            cout << "\n\nReceipt has been stored in receipt.txt" << endl;
        } else {
            cout << "Unable to create the receipt file." << endl;
        }
    }

    void printtheReceipt() {
        cout << "" << endl;
        cout << "" << endl;
        cout << "----------------------- RECEIPT -----------------------" << endl;
        cout << "Product\t\t\tPrice" << endl;
        cout << productDetails;
        cout << "--------------------------------------------" << endl;
        cout << "Total:\t\t\t$" << total << endl;
    }

private:
    int getProductIndex(const string& productName) {
        if (productName == "ventrolin") {
            return 0;
        } else if (productName == "lucozade") {
            return 1;
        } else if (productName == "p-Alaxin") {
            return 2;
        } else if (productName == "paracetamol") {
            return 3;
        } else if (productName == "penicilin") {
            return 4;
        } else if (productName == "aspirin") {
            return 5;
        } else if (productName == "mara moja") {
            return 6;
        } else if (productName == "panadol") {
            return 7;
        } else {
            return -1; // Invalid product name
        }
    }
};

class Customer {
private:
    string name;
    string address;
    string contact;

public:
    Customer(const string& name, const string& address, const string& contact)
        : name(name), address(address), contact(contact) {}

    void order(Pharmacy& pharmacy) {
        string productName;
        cout << "-----------------------------------------------------------------------------\n ";
        cout << "Enter the name of the product (or 'done' to finish): ";
        cin >> productName;

        while (productName != "done") {
            double productPrice = 0;

            if (productName == "ventrolin") {
                productPrice = 2.0;
            } else if (productName == "lucozade") {
                productPrice = 3.0;
            } else if (productName == "p-Alaxin") {
                productPrice = 1.5;
            } else if (productName == "paracetamol") {
                productPrice = 1.0;
            } else if (productName == "penicilin") {
                productPrice = 1.0;
            } else if (productName == "aspirin") {
                productPrice = 1.0;
            } else if (productName == "mara moja") {
                productPrice = 1.0;
            } else if (productName == "panadol") {
                productPrice = 1.0;
            } else {
                cout << "Invalid product name. Please try again." << endl;
            }

            if (productPrice > 0) {
                pharmacy.processOrder(productName, productPrice);
            }

            cout << "Enter the name of the product (or 'done' to finish): ";
            cin >> productName;
        }

        pharmacy.printReceipt();
        pharmacy.printtheReceipt();
    }
};

class Administrator {
public:
    void addProductQuantity(Pharmacy& pharmacy) {
        string password;
        cout << "\n-----------------------------------------------------------------------------\n ";
        cout << "------------------------------------------------------------------------------\n";
        cout << "Enter the password ****: ";
        cin >> password;

        if (password == "123") {
            cout << "\tAdministrator access granted." << endl;
            cout << "-----------------------------------------------------------------------------\n ";
            string productName;
            cout << "Enter the name of the product to add quantity (or 'done' to finish): ";
            cin >> productName;

            while (productName != "done") {
                int quantity;
                cout << "Enter the quantity to add for " << productName << ": ";
                cin >> quantity;

                pharmacy.addProductQuantity(productName, quantity, password);

                cout << "Enter the name of the product to add quantity (or 'done' to finish): ";
                cin >> productName;
            }
        } else {
            cout << "Incorrect password. Exiting." << endl;
        }
    }
};

int main() {
    Pharmacy pharmacy;
    string role;

    cout << "-------------------------------------WELCOME TO THE PHARMACY---------------------------------------------" << endl;
    cout << "\t--------------------------------------------------------------------\n";
    cout << "ENTER AS:\n";
    cout << "1.'admin' for administrator:\n2.'customer' for customer:\n3.'view' to see available products: ";
    cin >> role;

    if (role == "admin") {
        Administrator administrator;
        administrator.addProductQuantity(pharmacy);
    } else if (role == "customer") {
        cout << "-----------------------------------------------------------------------------------\n ";
        string name, address, contact;
        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your address: ";
        cin >> address;
        cout << "Enter your contact number: ";
        cin >> contact;

        Customer customer(name, address, contact);
        customer.order(pharmacy);
    } else if (role == "view") {
        cout << "-------------------------------------------------------------" << endl;
        cout << "Available products: " << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "ventrolin\t\t$2.0" << endl;
        cout << "lucozade\t\t$3.0" << endl;
        cout << "p-Alaxin\t\t$1.5" << endl;
        cout << "paracetamol\t\t$1.0" << endl;
        cout << "penicilin\t\t$1.0" << endl;
        cout << "aspirin\t\t\t$1.0" << endl;
        cout << "mara moja\t\t$1.0" << endl;
        cout << "panadol\t\t\t$1.0" << endl;
    } else {
        cout << "Invalid role. Exiting." << endl;
    }

    return 0;
}

