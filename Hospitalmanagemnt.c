#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int id;
    char name[100];
    char encryptedPhone[100];
    char encryptedProblem[100];
    char encryptedBill[100];
    struct Node* next;
};

void encrypt(char* data, char* encrypted) {
    for (int i = 0; data[i] != '\0'; i++) {
        encrypted[i] = data[i] + 3;
    }
    encrypted[strlen(data)] = '\0';
}

void decrypt(char* encrypted, char* decrypted) {
    for (int i = 0; encrypted[i] != '\0'; i++) {
        decrypted[i] = encrypted[i] - 3;
    }
    decrypted[strlen(encrypted)] = '\0';
}


void addPatient(struct Node** head) {
    int id;
    char name[100], phone[20], problem[100], bill[20];
    struct Node* temp = *head;

    printf("Enter Patient ID: ");
    scanf("%d", &id);

    while (temp != NULL) {
        if (temp->id == id) {
            printf("Error: Patient with the same ID already exists.\n");
            return;
        }
        temp = temp->next;
    }

    printf("Enter Patient Name: ");
    scanf("%s", name);
    printf("Enter Phone Number: ");
    scanf("%s", phone);
    printf("Enter Problem: ");
    scanf("%s", problem);
    printf("Enter Bill Amount: ");
    scanf("%s", bill);

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = id;
    strcpy(newNode->name, name);
    encrypt(phone, newNode->encryptedPhone);
    encrypt(problem, newNode->encryptedProblem);
    encrypt(bill, newNode->encryptedBill);
    newNode->next = *head;
    *head = newNode;

    printf("Patient %s added successfully.\n", name);
}


void searchByName(struct Node* head, char* name) {
    struct Node* temp = head;
    char phone[20], problem[100], bill[20];
    int found = 0;

    printf("\nSearching for patients named \"%s\"...\n", name);
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            decrypt(temp->encryptedPhone, phone);
            decrypt(temp->encryptedProblem, problem);
            decrypt(temp->encryptedBill, bill);

            printf("\nPatient Found:\n");
            printf("ID: %d | Name: %s | Phone: %s | Problem: %s | Bill: ₹%s\n",
                   temp->id, temp->name, phone, problem, bill);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found)
        printf("No patients found with name %s.\n", name);
}


void displayAll(struct Node* head) {
    struct Node* temp = head;
    char phone[20], problem[100], bill[20];
    printf("\n--- All Patient Records ---\n");
    while (temp != NULL) {
        decrypt(temp->encryptedPhone, phone);
        decrypt(temp->encryptedProblem, problem);
        decrypt(temp->encryptedBill, bill);
        printf("ID: %d | Name: %s | Phone: %s | Problem: %s | Bill: ₹%s\n",
               temp->id, temp->name, phone, problem, bill);
        temp = temp->next;
    }
}


int authenticate(char* role) {
    char username[100], password[100], pin[10];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    printf("Enter MFA Code (PIN): ");
    scanf("%s", pin);

    
    if (strcmp(username, "admin") == 0 && strcmp(password, "admin0202") == 0 && strcmp(pin, "1234") == 0) {
        strcpy(role, "admin");
        return 1;
    } else if (strcmp(username, "reception") == 0 && strcmp(password, "recep1607") == 0 && strcmp(pin, "5678") == 0) {
        strcpy(role, "reception");
        return 1;
    } else if (strcmp(username, "doctor") == 0 && strcmp(password, "doc567") == 0 && strcmp(pin, "9012") == 0) {
        strcpy(role, "doctor");
        return 1;
    } else {
        printf("Authentication Failed.\n");
        return 0;
    }
}

int main() {
    struct Node* head = NULL;
    int choice;
    char role[20], searchName[100];

    if (!authenticate(role)) {
        return 0;
    }

    printf("Login successful! Role: %s\n", role);

    while (1) {
        printf("\n--- Hospital Management Menu ---\n");
        printf("1. Add Patient\n");
        printf("2. Search by Name\n");
        printf("3. Display All Patients\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            if (strcmp(role, "admin") == 0 || strcmp(role, "reception") == 0)
                addPatient(&head);
            else
                printf("Access Denied: Only Admin/Receptionist can add patients.\n");
        } else if (choice == 2) {
            printf("Enter name to search: ");
            scanf("%s", searchName);
            searchByName(head, searchName);
        } else if (choice == 3) {
            if (strcmp(role, "admin") == 0)
                displayAll(head);
            else
                printf("Access Denied: Only Admin can view all patients.\n");
        } else if (choice == 4) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

return 0;
}



