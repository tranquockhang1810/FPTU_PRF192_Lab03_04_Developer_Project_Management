#include <stdio.h>

void developerMenu();
void projectMenu();

void mainMenu() {
    int choice;

    do {
        printf("\n===== MAIN MENU =====\n");
        printf("1. Developer Management\n");
        printf("2. Project Management\n");
        printf("0. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
            case 1:
                developerMenu();
                break;

            case 2:
                projectMenu();
                break;

            case 0:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 0);
}

int main() {
    mainMenu();
    return 0;
}