#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DEVELOPERS 100
#define DEVELOPER_FILE "database/developers.txt"

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
// FILE HANDLING
// ============================

void saveDevelopersToFile() {
	FILE *fp = fopen(DEVELOPER_FILE, "w");
	if (fp == NULL) {
		printf("Cannot open file to save data!\n");
		return;
	}

	for (int i = 0; i < developerCount; i++) {
		fprintf(fp, "%s|%s|%s|%s|%.2f\n",
				developerList[i].id,
				developerList[i].name,
				developerList[i].birthDate,
				developerList[i].programmingLanguages,
				developerList[i].monthlySalary);
	}

	fclose(fp);
}

void loadDevelopersFromFile() {
	FILE *fp = fopen(DEVELOPER_FILE, "r");
	if (fp == NULL) {
		return;
	}

	developerCount = 0;

	while (!feof(fp)) {
		Developer d;

		if (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%f\n",
				   d.id,
				   d.name,
				   d.birthDate,
				   d.programmingLanguages,
				   &d.monthlySalary) == 5) {

			developerList[developerCount++] = d;
		}
	}

	fclose(fp);
}

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

int findDeveloperById(char id[]) {
	for (int i = 0; i < developerCount; i++) {
		if (strcmp(developerList[i].id, id) == 0) {
			return i;
		}
	}
	return -1;
}

void addDeveloper() {
	if (developerCount >= MAX_DEVELOPERS) {
		printf("Developer list is full!\n");
		return;
	}

	printf("Add new developer\n--------------------------\n");
	Developer d;

	printf("Enter ID: ");
	scanf("%s", d.id);

	if (findDeveloperById(d.id) != -1) {
		printf("Developer ID already exists!\n");
		return;
	}

	printf("Enter name: ");
	scanf(" %[^\n]", d.name);

	printf("Enter birth date: ");
	scanf("%s", d.birthDate);

	printf("Enter programming languages: ");
	scanf(" %[^\n]", d.programmingLanguages);

	printf("Enter monthly salary: ");
	scanf("%f", &d.monthlySalary);

	developerList[developerCount++] = d;

	saveDevelopersToFile();

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

void findDeveloperByName() {
	char name[50];
	int found = 0;

	printf("Find developer by name\n--------------------------\n");
	printf("Enter developer name: ");
	scanf(" %[^\n]", name);

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

	saveDevelopersToFile();

	printf("Developer updated successfully!\n");
}

void deleteDeveloper() {
	char id[20];

	printf("Delete developer\n--------------------------\n");

	printf("Enter developer ID to delete: ");
	scanf("%s", id);

	int index = findDeveloperById(id);

	if (index == -1) {
		printf("Developer not found!\n");
		return;
	}

	for (int i = index; i < developerCount - 1; i++) {
		developerList[i] = developerList[i + 1];
	}

	developerCount--;

	saveDevelopersToFile();

	printf("Developer deleted successfully!\n");
}

void sortDeveloperByName() {
	if (developerCount <= 1) {
		printf("Not enough developers to sort.\n");
		return;
	}

	for (int i = 0; i < developerCount - 1; i++) {
		for (int j = i + 1; j < developerCount; j++) {
			if (strcmp(developerList[i].name, developerList[j].name) > 0) {
				Developer temp = developerList[i];
				developerList[i] = developerList[j];
				developerList[j] = temp;
			}
		}
	}

	saveDevelopersToFile();

	printf("Developers sorted by Name successfully!\n");
	printDeveloperList();
}

// ============================
// Menu
// ============================

void developerMenu() {
	int choice;

	loadDevelopersFromFile();

	do {
		printf("\n===== DEVELOPER MENU =====\n");
		printf("1. Add Developer\n");
		printf("2. Show Developer List\n");
		printf("3. Update Developer\n");
		printf("4. Find Developer By Name\n");
		printf("5. Delete Developer\n");
		printf("6. Sort Developer By Name\n");
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
				deleteDeveloper();
				break;

			case 6:
				sortDeveloperByName();
				break;

			case 0:
				break;

			default:
				printf("Invalid choice!\n");
		}

	} while (choice != 0);
}