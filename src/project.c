#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PROJECTS 100
#define PROJECT_FILE "database/projects.txt"

typedef struct {
    char id[20];
    char name[100];
    char dev[20];
    int duration;
    char status[20];
    char startDate[20];
    char languages[100];
} Project;

Project projectList[MAX_PROJECTS];
int projectCount = 0;

// ============================
// FILE HANDLING
// ============================

void saveProjectsToFile() {
    FILE *fp = fopen(PROJECT_FILE, "w");
    if (fp == NULL) {
        printf("Cannot open file to save data!\n");
        return;
    }

    for (int i = 0; i < projectCount; i++) {
        fprintf(fp, "%s|%s|%s|%d|%s|%s|%s\n",
                projectList[i].id,
                projectList[i].name,
                projectList[i].dev,
                projectList[i].duration,
                projectList[i].status,
                projectList[i].startDate,
                projectList[i].languages);
    }

    fclose(fp);
}

void loadProjectsFromFile() {
    FILE *fp = fopen(PROJECT_FILE, "r");
    if (fp == NULL) {
        return; // chưa có file thì bỏ qua
    }

    projectCount = 0;
    while (!feof(fp)) {
        Project p;

        if (fscanf(fp, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^\n]\n",
                   p.id,
                   p.name,
                   p.dev,
                   &p.duration,
                   p.status,
                   p.startDate,
                   p.languages) == 7) {

            projectList[projectCount++] = p;
        }
    }

    fclose(fp);
}

// ============================
// Print Table
// ============================

void printProjectTableHeader() {
    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("%-10s %-20s %-10s %-10s %-12s %-15s %-20s\n",
           "ID", "Name", "Dev", "Duration", "Status", "Start Date", "Languages");
    printf("---------------------------------------------------------------------------------------------------------------\n");
}

void printProjectRow(Project p) {
    printf("%-10s %-20s %-10s %-10d %-12s %-15s %-20s\n",
           p.id, p.name, p.dev, p.duration, p.status, p.startDate, p.languages);
}

// ============================
// Find
// ============================

int findProjectById(char id[]) {
    for (int i = 0; i < projectCount; i++) {
        if (strcmp(projectList[i].id, id) == 0) return i;
    }
    return -1;
}

// ============================
// Add
// ============================

void addProject() {
    if (projectCount >= MAX_PROJECTS) {
        printf("Project list is full!\n");
        return;
    }

    Project p;
    printf("Add new Project\n--------------------------\n");

    printf("Enter ID: ");
    scanf("%s", p.id);

    if (findProjectById(p.id) != -1) {
        printf("Error: ID already exists!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);

    printf("Enter Developer ID: ");
    scanf("%s", p.dev);

    printf("Enter Duration (months): ");
    scanf("%d", &p.duration);

    printf("Enter Status: ");
    scanf("%s", p.status);

    printf("Enter Start Date: ");
    scanf("%s", p.startDate);

    printf("Enter Programming Languages: ");
    scanf(" %[^\n]", p.languages);

    projectList[projectCount++] = p;

    saveProjectsToFile();

    printf("\nProject added successfully!\n");
}

// ============================
// Show List
// ============================

void printProjectList() {
    if (projectCount == 0) {
        printf("No projects available.\n");
        return;
    }

    printf("\n===== PROJECT LIST =====\n");
    printProjectTableHeader();

    for (int i = 0; i < projectCount; i++) {
        printProjectRow(projectList[i]);
    }
}

// ============================
// Find by Developer
// ============================

void findProjectByDev() {
    char devID[20];
    int found = 0;

    printf("Enter Developer ID: ");
    scanf("%s", devID);

    printProjectTableHeader();

    for (int i = 0; i < projectCount; i++) {
        if (strcmp(projectList[i].dev, devID) == 0) {
            printProjectRow(projectList[i]);
            found = 1;
        }
    }

    if (!found) printf("No projects found.\n");
}

// ============================
// Update
// ============================

void updateProject() {
    char id[20];
    printf("Enter Project ID to update: ");
    scanf("%s", id);

    int index = findProjectById(id);

    if (index == -1) {
        printf("Project not found!\n");
        return;
    }

    Project *p = &projectList[index];

    printf("Enter New Name: ");
    scanf(" %[^\n]", p->name);

    printf("Enter New Developer ID: ");
    scanf("%s", p->dev);

    printf("Enter New Duration: ");
    scanf("%d", &p->duration);

    printf("Enter New Status: ");
    scanf("%s", p->status);

    printf("Enter New Start Date: ");
    scanf("%s", p->startDate);

    printf("Enter New Languages: ");
    scanf(" %[^\n]", p->languages);

    saveProjectsToFile();

    printf("Project updated successfully!\n");
}

// ============================
// Delete
// ============================

void deleteProject() {
    char id[20];
    printf("Enter Project ID to delete: ");
    scanf("%s", id);

    int index = findProjectById(id);

    if (index == -1) {
        printf("Project not found!\n");
        return;
    }

    for (int i = index; i < projectCount - 1; i++) {
        projectList[i] = projectList[i + 1];
    }

    projectCount--;

    saveProjectsToFile();

    printf("Project deleted successfully!\n");
}

// ============================
// Sort
// ============================

void sortProjectsByDuration() {
    for (int i = 0; i < projectCount - 1; i++) {
        for (int j = 0; j < projectCount - i - 1; j++) {
            if (projectList[j].duration < projectList[j + 1].duration) {
                Project temp = projectList[j];
                projectList[j] = projectList[j + 1];
                projectList[j + 1] = temp;
            }
        }
    }

    saveProjectsToFile();

    printf("Sorted by Duration (Descending).\n");
    printProjectList();
}

// ============================
// Menu
// ============================

void projectMenu() {
    int choice;

    loadProjectsFromFile(); // load khi vào menu

    do {
        printf("\n===== PROJECT MANAGEMENT =====\n");
        printf("1. Add Project\n");
        printf("2. Show All Projects\n");
        printf("3. Find by Developer\n");
        printf("4. Update Project\n");
        printf("5. Delete Project\n");
        printf("6. Sort by Duration\n");
        printf("0. Back\n");
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
                findProjectByDev();
                break;
            case 4:
                updateProject();
                break;
            case 5:
                deleteProject();
                break;
            case 6:
                sortProjectsByDuration();
                break;
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
}