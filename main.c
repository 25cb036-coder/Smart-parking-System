#include <stdio.h>
#include <string.h>

#define MAX 5
#define NAME 30

char parking[MAX][NAME];
char waiting[MAX][NAME];

int top = -1;
int front = 0, rear = -1, waitingCount = 0;

void parkVehicle() {
    char vehicle[NAME];

    printf("Enter vehicle number: ");
    scanf("%29s", vehicle);

    if (top < MAX - 1) {
        strcpy(parking[++top], vehicle);
        printf("Vehicle %s parked successfully.\n", vehicle);
    } else if (waitingCount < MAX) {
        rear = (rear + 1) % MAX;
        strcpy(waiting[rear], vehicle);
        waitingCount++;
        printf("Parking full! Vehicle added to waiting queue.\n");
    } else {
        printf("Parking and waiting queue are full!\n");
    }
}

void removeVehicle() {
    char vehicle[NAME];
    int i, found = -1;

    if (top == -1) {
        printf("Parking lot is empty.\n");
        return;
    }

    printf("Enter vehicle number to remove: ");
    scanf("%29s", vehicle);

    for (i = 0; i <= top; i++) {
        if (strcmp(parking[i], vehicle) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Vehicle not found in parking lot.\n");
        return;
    }

    for (i = found; i < top; i++) {
        strcpy(parking[i], parking[i + 1]);
    }

    top--;
    printf("Vehicle %s removed successfully.\n", vehicle);

    if (waitingCount > 0) {
        top++;
        strcpy(parking[top], waiting[front]);
        printf("Waiting vehicle %s entered the parking lot.\n",
               waiting[front]);

        front = (front + 1) % MAX;
        waitingCount--;
    }
}

void displayParking() {
    int i;

    printf("\n--- Parking Lot Status ---\n");

    if (top == -1) {
        printf("No vehicles parked.\n");
    } else {
        for (i = 0; i <= top; i++) {
            printf("Slot %d: %s\n", i + 1, parking[i]);
        }
    }

    printf("Available spaces: %d\n", MAX - top - 1);

    printf("\n--- Waiting Queue ---\n");

    if (waitingCount == 0) {
        printf("No vehicles waiting.\n");
    } else {
        for (i = 0; i < waitingCount; i++) {
            printf("%s\n", waiting[(front + i) % MAX]);
        }
    }
}

int main() {
    int choice;

    do {
        printf("\n=== Smart Parking Management ===\n");
        printf("1. Park Vehicle\n");
        printf("2. Remove Vehicle\n");
        printf("3. Display Status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                parkVehicle();
                break;
            case 2:
                removeVehicle();
                break;
            case 3:
                displayParking();
                break;
            case 4:
                printf("Program terminated.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
