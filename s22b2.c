#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    char username[50];
    char password[50];
};

struct Account accounts[100];
int accountCount = 0;

void readAccountsFromFile() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        printf("Khong the mo file de doc. Mang tai khoan khoi tao rong.\n");
        return;
    }
    fread(&accountCount, sizeof(int), 1, file);
    fread(accounts, sizeof(struct Account), accountCount, file);
    fclose(file);
}

void writeAccountsToFile() {
    FILE *file = fopen("accounts.dat", "wb");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }
    fwrite(&accountCount, sizeof(int), 1, file);
    fwrite(accounts, sizeof(struct Account), accountCount, file);
    fclose(file);
}

int checkUsernameExists(char* username) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void registerAccount() {
    if (accountCount >= 100) {
        printf("Khong the dang ky tai khoan moi. Mang da day.\n");
        return;
    }

    struct Account newAccount;
    char confirmPassword[50];

    printf("Nhap ten tai khoan: ");
    scanf("%s", newAccount.username);

    if (checkUsernameExists(newAccount.username)) {
        printf("Tai khoan da ton tai. Vui long thu lai.\n");
        return;
    }

    printf("Nhap mat khau: ");
    scanf("%s", newAccount.password);
    printf("Xac nhan lai mat khau: ");
    scanf("%s", confirmPassword);

    if (strcmp(newAccount.password, confirmPassword) != 0) {
        printf("Mat khau xac nhan khong khop. Vui long thu lai.\n");
        return;
    }

    accounts[accountCount++] = newAccount;
    writeAccountsToFile();
    printf("Dang ky tai khoan thanh cong!\n");
}

void login() {
    char username[50];
    char password[50];

    printf("Nhap ten tai khoan: ");
    scanf("%s", username);
    printf("Nhap mat khau: ");
    scanf("%s", password);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            printf("Dang nhap thanh cong!\n");
            return;
        }
    }
    printf("Dang nhap that bai. Vui long thu lai.\n");
}

int main() {
    readAccountsFromFile();
    int choice;

    while (1) {
        printf("\nMENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                registerAccount();
                break;
            case 3:
                printf("Thoat chuong trinh.\n");
                return 0;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    }
}

