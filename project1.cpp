#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

struct Expense {
    int id;
    double amount;
    string category;
    string date;
    Expense* next;
    Expense* prev;

    // Corrected Constructor
    Expense(int i, double amt, string cat, string dt) {
        id = i;
        amount = amt;
        category = cat;
        date = dt;
        next = nullptr;
        prev = nullptr;
    }
};

class ExpenseManager {
private:
    Expense* head;
    Expense* tail;
    unordered_map<string, double> categoryExpense;
    priority_queue<double, vector<double>, greater<double>> minHeap;
    priority_queue<double> maxHeap;
    int count;

public:
    ExpenseManager() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    //Add Expense
    void addExpense(double amount, string category, string date) {
        Expense* newExpense = new Expense(++count, amount, category, date);

        if (!head) {
            head = tail = newExpense;
        } else {
            tail->next = newExpense;
            newExpense->prev = tail;
            tail = newExpense;
        }

        // Update category-wise expense
        categoryExpense[category] += amount;

        // Insert into Min-Heap & Max-Heap
        minHeap.push(amount);
        maxHeap.push(amount);

        cout << "Expense added successfully!\n";
    }

    //Display Expenses
    void displayExpense() {
        if (!head) {
            cout << "No expenses recorded.\n";
            return;
        }

        cout << "ID | AMOUNT  | CATEGORY  | DATE\n";
        cout << "----------------------------------\n";

        Expense* temp = head;
        while (temp) {
            cout << temp->id << " | $" << temp->amount << " | " << temp->category << " | " << temp->date << endl;
            temp = temp->next;
        }
    }

    //Get Total Expense
    void totalExpense() {
        double total = 0;
        Expense* temp = head;
        while (temp) {
            total += temp->amount;
            temp = temp->next;
        }
        cout << "Total Expense: $" << total << endl;
    }

    //Get Expense by Category
    void categoryWiseExpense(string category) {
        if (categoryExpense.find(category) != categoryExpense.end()) {
            cout << "Total spent on " << category << ": $" << categoryExpense[category] << endl;
        } else {
            cout << "No expenses recorded under this category.\n";
        }
    }

    //Get Min & Max Expense
    void getMinMaxExpense() {
        if (!head) {
            cout << "No expenses recorded.\n";
            return;
        }
        cout << "Lowest Expense: $" << minHeap.top() << endl;
        cout << "Highest Expense: $" << maxHeap.top() << endl;
    }

    //Delete Expense by ID
    void deleteExpense(int id) {
        Expense* temp = head;
        while (temp) {
            if (temp->id == id) {
                // Update category-wise expense
                categoryExpense[temp->category] -= temp->amount;

                // Remove from Linked List
                if (temp == head) {
                    head = temp->next;
                    if (head) head->prev = nullptr;
                } else if (temp == tail) {
                    tail = temp->prev;
                    tail->next = nullptr;
                } else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                }

                delete temp;
                cout << "Expense deleted successfully!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Expense ID not found.\n";
    }
};

//Main Function - Runs the Program
int main() {
    ExpenseManager manager;
    int choice;

    while (true) {
        cout << "\n===== Expense Management System =====\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Total Expense\n";
        cout << "4. Expense by Category\n";
        cout << "5. Min & Max Expense\n";
        cout << "6. Delete Expense\n";
        cout << "7. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            double amount;
            string category, date;
            cout << "Enter Amount: ";
            cin >> amount;
            cout << "Enter Category: ";
            cin >> category;
            cout << "Enter Date (YYYY-MM-DD): ";
            cin >> date;
            manager.addExpense(amount, category, date);
        }
        else if (choice == 2) {
            manager.displayExpense();
        }
        else if (choice == 3) {
            manager.totalExpense();
        }
        else if (choice == 4) {
            string category;
            cout << "Enter Category: ";
            cin >> category;
            manager.categoryWiseExpense(category);
        }
        else if (choice == 5) {
            manager.getMinMaxExpense();
        }
        else if (choice == 6) {
            int id;
            cout << "Enter Expense ID to delete: ";
            cin >> id;
            manager.deleteExpense(id);
        }
        else if (choice == 7) {
            cout << "Exiting... Thank you!\n";
            break;
        }
        else {
            cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
