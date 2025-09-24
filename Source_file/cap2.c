#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define URGENT_LIMIT 4

char urgentStack[MAX][100];
int top = -1;
int urgentCount = 0;

char normalQueue[MAX][100];
int front = -1, rear = -1;

/* Push urgent complaint into stack */
void pushUrgent(char complaint[]) {
    if (top >= MAX - 1) {
        printf("[ERROR] Urgent complaint section is full!\n");
        return;
    }
    strcpy(urgentStack[++top], complaint);
    urgentCount++;
    printf("[OK] Urgent complaint added! (%d/%d used today)\n", urgentCount, URGENT_LIMIT);
    printf("[MSG] Message to Customer: Your work will be finished within an hour or five.\n");
}

/* Enqueue normal complaint into queue */
void enqueueNormal(char complaint[]) {
    if (rear >= MAX - 1) {
        printf("[ERROR] Normal complaint section is full!\n");
        return;
    }
    if (front == -1) front = 0;
    strcpy(normalQueue[++rear], complaint);
    printf("[OK] Normal complaint added!\n");
    printf("[MSG] Message to Customer: Your work will be finished within a day or two.\n");
}

/* Resolve complaint (urgent first, then normal) */
void resolveComplaint() {
    if (top != -1) {
        printf("[RESOLVED] Urgent Complaint: %s\n", urgentStack[top--]);
    } else if (front != -1 && front <= rear) {
        printf("[RESOLVED] Normal Complaint: %s\n", normalQueue[front++]);
        if (front > rear) {
            front = rear = -1; /* reset queue when empty */
        }
    } else {
        printf("[INFO] No complaints to resolve!\n");
    }
}

/* Display pending complaints */
void displayComplaints() {
    int i;
    printf("\n--- Pending Urgent Complaints ---\n");
    if (top == -1) {
        printf("None\n");
    } else {
        for (i = top; i >= 0; --i)
            printf("%s\n", urgentStack[i]);
    }

    printf("\n--- Pending Normal Complaints ---\n");
    if (front == -1 || front > rear) {
        printf("None\n");
    } else {
        for (i = front; i <= rear; ++i)
            printf("%s\n", normalQueue[i]);
    }
    printf("\n");
}

/* Main menu */
int main() {
    printf("Harish.r CH.SC.U4cse24163\n");

    int choice;
    char complaint[100];

    while (1) {
        printf("\nComplaint Manager:\n");
        printf("1. Add Urgent Complaint\n");
        printf("2. Add Normal Complaint\n");
        printf("3. Resolve Complaint\n");
        printf("4. Display Complaints\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF); /* clear invalid input */
            printf("[ERROR] Please enter a number (1-5).\n");
            continue;
        }
        getchar(); /* consume newline */

        switch (choice) {
            case 1:
                if (urgentCount >= URGENT_LIMIT) {
                    printf("[LIMIT] Daily urgent complaint limit (%d) reached! Try again tomorrow.\n", URGENT_LIMIT);
                    break;
                }
                printf("Enter urgent complaint: ");
                if (!fgets(complaint, sizeof(complaint), stdin)) complaint[0] = '\0';
                complaint[strcspn(complaint, "\n")] = '\0';
                pushUrgent(complaint);
                break;

            case 2:
                printf("Enter normal complaint: ");
                if (!fgets(complaint, sizeof(complaint), stdin)) complaint[0] = '\0';
                complaint[strcspn(complaint, "\n")] = '\0';
                enqueueNormal(complaint);
                break;

            case 3:
                resolveComplaint();
                break;

            case 4:
                displayComplaints();
                break;

            case 5:
                printf("Exiting Complaint Manager. Goodbye!\n");
                return 0;

            default:
                printf("[ERROR] Invalid choice! Enter 1-5.\n");
        }
    }
    return 0;
}
