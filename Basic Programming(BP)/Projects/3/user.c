#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.c"
#include "function.h"
void Signup(char username[], char password[], User **user_head, int flag) // for phase 1
{
    User *tmp = *user_head;
    // flag 0 means it pass normally and flag 1 means it load from file so it does not have to print anything
    if (*user_head == NULL) // there is no user in link list
    {
        *user_head = malloc(sizeof(User));
        strcpy((*user_head)->username, username);
        strcpy((*user_head)->password, password);
        (*user_head)->next = NULL;

        if (flag == 0)
            printf("User %s successfully registered!\n", username);
    }
    else if (searchUser(username, *user_head) == NULL) // there is not username match with username created already
    {                                                  
        // adding the new node to after head for efficiency and do not use loop
        
        // we are not allowed to use pointer function so we can not make one node maker and use it in all codes so there is no point to make seperate function for single use
        *user_head = malloc(sizeof(User));
        (*user_head)->next = tmp;
        strcpy((*user_head)->username, username);
        strcpy((*user_head)->password, password);
        if (flag == 0)
            printf("User %s successfully registered!\n", username);
    }
    else // otherwise it is created
        if (flag == 0)
            printf("Error: Username repeatedOne already exists\n");
}
void Login(char username[], char password[], User *user_head, System *system) // for phase 1
{
    // we check if anyone logged in already in main.c
    User *user = searchUser(username, user_head);
    if (user != NULL && strcmp(user->password, password) == 0)
    {
        (system->logged_in_user) = user;
        printf("User %s logged in successfully!\n", user->username);
    }
    else
        printf("Error: Invalid username or password.\n");
}
void Logout(System *system) // for phase 1
{
    if (system->logged_in_user == NULL)
    {
        printf("Error: No user is currently logged in.\n");
        return;
    }
    printf("User %s logged out successfully!\n", (system->logged_in_user)->username);
    system->logged_in_user = NULL;
    system->selected_chat = NULL;
}
User *searchUser(char username[], User *user_head) // for phase 1
{
    while (user_head != NULL)
    {
        if (strcmp(user_head->username, username) == 0)
            return user_head; // return the pointer of user
        user_head = user_head->next;
    }
    return NULL;
}
void free_user_memmory(User *head) // for phase 1
{
    User *tmp = head;
    while (head != NULL)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}
void loadUsers(char name_file[], User **user_head)
{
    FILE *file = fopen(name_file, "r");
    if (file == NULL)
    {
        printf("Error: Unable to open file %s.\n", name_file);
        return;
    }

    char buffer[102];
    int line = 1;
    int success = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // Remove \n char if exist
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        if (len > 1 && buffer[len - 2] == ' ')
        {
            printf("Warning: Invalid format in line %d. Skipping.\n", line);
            line++;
            continue;
        }
        if (len <= 2) // if length of line lower than 3 defenetly it is wrong format
        {
            printf("Warning: Invalid format in line %d. Skipping.\n", line);
            line++;
            continue;
        }

        char username[51];
        char password[51];

        int i_1 = 0;
        int space_count = 0;
        int tmp = 0;
        int flag = 0;

        while (buffer[i_1] != '\0')
        {
            if (buffer[i_1] == ' ')
            {
                space_count++;
                if (space_count == 1)
                {
                    strncpy(username, buffer, i_1);
                    username[i_1] = '\0'; // put null-termination
                    tmp = i_1;
                }
                else
                {
                    printf("Warning: Invalid format in line %d. Skipping.\n", line);
                    flag = 1;
                    break;
                }
            }
            i_1++;
        }

        if (flag == 1 || space_count != 1)
        {
            line++;
            continue;
        }


        if (sscanf(buffer, "%50s %50s", username, password) != 2)
        {
            printf("Warning: Invalid format in line %d. Skipping.\n", line);
            line++;
            continue;
        }
        Signup(username, password, user_head, 1);
        success++;

        line++;
    }
    if (success > 0)
        printf("Users successfully loaded from %s , %d user(s) added.\n", name_file, success);
    fclose(file);
}