#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
};

struct Student students[100];
int studentCount = 0;

void readStudentsFromFile() {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("Khong the mo file de doc. Mang sinh vien khoi tao rong.\n");
        return;
    }
    fread(&studentCount, sizeof(int), 1, file);
    fread(students, sizeof(struct Student), studentCount, file);
    fclose(file);
}

void writeStudentsToFile() {
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), studentCount, file);
    fclose(file);
}

void printStudents() {
    for (int i = 0; i < studentCount; i++) {
        printf("Sinh vien %d: ID: %d, Ten: %s, Tuoi: %d\n", i + 1, students[i].id, students[i].name, students[i].age);
    }
}

void addStudent() {
    if (studentCount >= 100) {
        printf("Khong the them sinh vien moi. Mang da day.\n");
        return;
    }

    struct Student newStudent;
    printf("Nhap ID: ");
    scanf("%d", &newStudent.id);
    printf("Nhap ten: ");
    scanf("%s", newStudent.name);
    printf("Nhap tuoi: ");
    scanf("%d", &newStudent.age);

    students[studentCount++] = newStudent;
    writeStudentsToFile();
    printf("Them sinh vien thanh cong!\n");
}

void editStudent() {
    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Nhap ten moi: ");
            scanf("%s", students[i].name);
            printf("Nhap tuoi moi: ");
            scanf("%d", &students[i].age);
            writeStudentsToFile();
            printf("Sua thong tin sinh vien thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID %d.\n", id);
}

void deleteStudent() {
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            writeStudentsToFile();
            printf("Xoa sinh vien thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID %d.\n", id);
}

void searchStudent() {
    char name[50];
    printf("Nhap ten sinh vien can tim: ");
    scanf("%s", name);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Sinh vien tim thay: ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ten %s.\n", name);
}

void sortStudents() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (students[i].age > students[j].age) {
                struct Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    writeStudentsToFile();
    printf("Sap xep danh sach sinh vien thanh cong!\n");
}

int main() {
    readStudentsFromFile();
    int choice;
    while (1) {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printStudents();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                editStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                return 0;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    }
}

