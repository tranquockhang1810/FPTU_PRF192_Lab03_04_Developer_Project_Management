#include <stdio.h>
#include <string.h>

#define MAX_DEVELOPERS 100

// ============================
// Struct
// ============================

typedef struct {
	char id[20];
	char name[50];
	char birthDate[20];
	char programmingLanguages[100];
	float monthlySalary;
} Developer;

// ============================
// Global Data
// ============================

Developer developerList[MAX_DEVELOPERS];
int developerCount = 0;

// ============================
// Utility
// ============================

void printDeveloperTableHeader() {
	printf("--------------------------------------------------------------------------\n");
	printf("%-10s %-20s %-12s %-20s %-10s\n",
	       "ID", "Name", "BirthDate", "Languages", "Salary");
	printf("--------------------------------------------------------------------------\n");
}

void printDeveloperRow(Developer d) {
	printf("%-10s %-20s %-12s %-20s %-10.2f\n",
	       d.id, d.name, d.birthDate, d.programmingLanguages, d.monthlySalary);
}

// ============================
// Functions
// ============================

void addDeveloper() {
	if (developerCount >= MAX_DEVELOPERS) {
		printf("Developer list is full!\n");
		return;
	}

	printf("Add new developer\n--------------------------\n");
	Developer d;

	printf("Enter ID: ");
	scanf("%s", d.id);

	printf("Enter name: ");
	scanf(" %[^\n]", d.name);

	printf("Enter birth date: ");
	scanf("%s", d.birthDate);

	printf("Enter programming languages: ");
	scanf(" %[^\n]", d.programmingLanguages);

	printf("Enter monthly salary: ");
	scanf("%f", &d.monthlySalary);

	developerList[developerCount++] = d;

	printf("Developer added successfully!\n");
}

void printDeveloperList() {
	if (developerCount == 0) {
		printf("No developers available.\n");
		return;
	}

	printDeveloperTableHeader();

	for (int i = 0; i < developerCount; i++) {
		printDeveloperRow(developerList[i]);
	}
}

int findDeveloperById(char id[]) {
	for (int i = 0; i < developerCount; i++) {
		if (strcmp(developerList[i].id, id) == 0) {
			return i;
		}
	}
	return -1;
}

void findDeveloperByName() {
    char name[50];
    int found = 0;

    printf("Find developer by name\n--------------------------\n");
    printf("Enter developer name: ");
    scanf(" %[^\n]", name);

    if (developerCount == 0) {
        printf("No developers available.\n");
        return;
    }

    printDeveloperTableHeader();

    for (int i = 0; i < developerCount; i++) {
        if (strstr(developerList[i].name, name) != NULL) {
            printDeveloperRow(developerList[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("No developer found with that name.\n");
    }
}

void updateDeveloper() {
	char id[20];

	printf("Update developer\n--------------------------\n");

	printf("Enter developer ID to update: ");
	scanf("%s", id);

	int index = findDeveloperById(id);

	if (index == -1) {
		printf("Developer not found!\n");
		return;
	}

	Developer *d = &developerList[index];

	printf("Enter new name: ");
	scanf(" %[^\n]", d->name);

	printf("Enter new birth date: ");
	scanf("%s", d->birthDate);

	printf("Enter new languages: ");
	scanf(" %[^\n]", d->programmingLanguages);

	printf("Enter new salary: ");
	scanf("%f", &d->monthlySalary);

	printf("Developer updated successfully!\n");
}

// demo function theo requirement
void calculateTotalExperience() {
	printf("Feature placeholder: calculateTotalExperience()\n");
}

// ============================
// Menu
// ============================

void developerMenu() {
	int choice;

	do {
		printf("\n===== DEVELOPER MENU =====\n");
		printf("1. Add Developer\n");
		printf("2. Show Developer List\n");
		printf("3. Update Developer\n");
		printf("4. Find Developer By Name\n");
		printf("5. Calculate Total Experience\n");
		printf("0. Back\n");
		printf("Choose: ");
		scanf("%d", &choice);

		system("cls");

		switch (choice) {
			case 1:
				addDeveloper();
				break;

			case 2:
				printDeveloperList();
				break;

			case 3:
				updateDeveloper();
				break;

			case 4:
				findDeveloperByName();
				break;

			case 5:
				calculateTotalExperience();
				break;

			case 0:
				printf("Back to main menu...\n");
				break;

			default:
				printf("Invalid choice!\n");
		}

	} while (choice != 0);
}