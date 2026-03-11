#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PROJECTS 100


typedef struct {
	char projectID[20];
	char projectName[100];
	char managerID[20];
	float budget;
} Project;


Project projectList[MAX_PROJECTS];
int projectCount = 0;

void printProjectTableHeader() {
	printf("--------------------------------------------------------------------------------\n");
	printf("%-15s %-30s %-15s %-15s\n",
	       "Project ID", "Project Name", "Manager ID", "Budget");
	printf("--------------------------------------------------------------------------------\n");
}

void printProjectRow(Project p) {
	printf("%-15s %-30s %-15s %-15.2f\n",
	       p.projectID, p.projectName, p.managerID, p.budget);
}

int findProjectById(char id[]) {
	for (int i = 0; i < projectCount; i++) {
		if (strcmp(projectList[i].projectID, id) == 0) return i;
	}
	return -1;
}

void addProject() {
	if (projectCount >= MAX_PROJECTS) {
		printf("Project list is full!\n");
		return;
	}

	Project p;
	printf("Add new Project\n--------------------------\n");
	printf("Enter Project ID: ");
	scanf("%s", p.projectID);

	if (findProjectById(p.projectID) != -1) {
		printf("Error: Project ID already exists!\n");
		return;
	}

	printf("Enter Project Name: ");
	scanf(" %[^\n]", p.projectName);

	printf("Enter Manager (Developer) ID: ");
	scanf("%s", p.managerID);

	printf("Enter Budget: ");
	scanf("%f", &p.budget);

	projectList[projectCount++] = p;
	printf("\nProject added successfully!\n");
}

void printProjectList() {
	if (projectCount == 0) {
		printf("No projects available.\n");
		return;
	}
	printf("\n===== CURRENT PROJECT LIST =====\n");
	printProjectTableHeader();
	for (int i = 0; i < projectCount; i++) {
		printProjectRow(projectList[i]);
	}
}

void findProjectByManager() {
	char mID[20];
	int found = 0;
	printf("Enter Manager ID to search: ");
	scanf("%s", mID);

	printProjectTableHeader();
	for (int i = 0; i < projectCount; i++) {
		if (strcmp(projectList[i].managerID, mID) == 0) {
			printProjectRow(projectList[i]);
			found = 1;
		}
	}
	if (!found) printf("No projects found for this Manager.\n");
}

void projectMenu() {
	int choice;
	do {
		printf("\n===== PROJECT MANAGEMENT =====\n");
		printf("1. Add New Project\n");
		printf("2. Show All Projects\n");
		printf("3. Find Projects by Manager ID\n");
		printf("0. Back to Main Menu\n");
		printf("Choose: ");
		scanf("%d", &choice);

		system("cls"); 

		switch (choice) {
			case 1:
				addProject();
				break;
			case 2:
				printProjectList();
				break;
			case 3:
				findProjectByManager();
				break;
			case 0:
				break;
			default:
				printf("Invalid choice!\n");
		}
	} while (choice != 0);
}