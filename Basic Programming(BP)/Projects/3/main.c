#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "struct.c"
#include "function.h"
#define LOGIN "login"
#define SIGNUP "signup"
#define LOGOUT "logout"
#define NEWCHAT "newChat"
#define SELECTCHAT "selectChat"
#define SHOWCHAT "showChat"
#define SENDMESSAGE "sendMessage"
#define LOADUSER "loadUsers"


int main()
{
    char command[50];
    User * user_head=NULL ;
    System system ; 
    system.all_users_head=user_head ; 
    system.logged_in_user=NULL ; 
    system.selected_chat=NULL ; 
    Chat * chats_head=NULL ; 
    Message *messages_head=NULL ;


    // i prefer do not make another function to do that beacuse already we make it multi file to easy access and more readablity
    while(1)
    {
        printf("Enter Command: ");
        scanf("%s",command);
        
        
        if(strcmp(command,"exit")==0)
        {
            //free memmory
            free_user_memmory(user_head);
            free_chat_memmory(chats_head);
            free_message_memmory(messages_head);
            break;
        }
        else if(strcmp(command,SIGNUP)==0)
        {
            char buffer_1[51];
            char buffer_2[51];
            printf("Username: ");
            scanf("%s",buffer_1) ;
            printf("Password: ");
            scanf("%s",buffer_2);
            Signup(buffer_1,buffer_2,&user_head,0);
            system.all_users_head=user_head ;

        }
        else if (strcmp(command,LOGIN)==0)
        {
            if(system.logged_in_user!=NULL)
            {
                printf("Error: There is an open session, please logout first.\n") ; 
                continue;
            }
            char buffer_1[51];
            char buffer_2[51];
            printf("Username: ");
            scanf("%s",buffer_1) ;
            printf("Password: ");
            scanf("%s",buffer_2);
            Login(buffer_1,buffer_2,user_head,&system);
        }
        else if (strcmp(command,LOGOUT)==0) Logout(&system);
        else if (strcmp(command,NEWCHAT)==0)
        {
            char buffer_1[51];
            char buffer_2[51];
            printf("Enter chat name: ");
            scanf("%s",buffer_1) ;
            printf("Enter selected username: ");
            scanf("%s",buffer_2);
            newChat(buffer_1,buffer_2,&system,user_head,&chats_head);
        }
        else if (strcmp(command,SELECTCHAT)==0)
        {
            
            char buffer_1[51];
            printf("Enter chat name: ");
            scanf("%s",buffer_1) ;
            selectChat(buffer_1,&system,chats_head) ;

        }
        else if (strcmp(command,SENDMESSAGE)==0)
        {
            if(system.selected_chat==NULL)
            {
                printf("Error: No chat selected. Please select a chat first.\n");
                continue;
            }  
            
            
            User * reciver  ; 
            for (int i =0 ; i<2 ; i++)
            {
                if(system.selected_chat->users[i]!=system.logged_in_user) 
                {
                    reciver=system.selected_chat->users[i] ; 
                }
            }
            printf("Receiver: %s\n",reciver->username);
            printf("Enter message: ");
            
            getchar();// make program wait untill enter hit
            char * buffer= read_unlimited_string(stdin , 10);
            sendMessage(buffer,&system,&messages_head);
        }
        else if (strcmp(command,SHOWCHAT)==0)
        {
            showChat(&system,messages_head);
        }
        else if (strcmp(command,LOADUSER)==0)
        {
            char buffer_1[51];
            printf("Enter filename: ");
            scanf("%s",buffer_1) ;
            loadUsers(buffer_1,&user_head);
        }
        else printf("Error: Unknown command.\n");

    }
}
char * read_unlimited_string(FILE *fp , size_t start_size)
{
    char ch ; 
    char * string ; 
    string = malloc(start_size) ; 
    size_t index = 0 , size = start_size ; 
    while(1)
    {
        ch=fgetc(fp);
        if(ch==EOF ||ch=='\n') break;
        if(index == start_size)
        {
            string = realloc(string , (start_size+16)*sizeof(char)) ; 
            start_size=start_size+16;
        }
        string[index]=ch ; 
        
        index ++ ; 
    }
    string[index++]='\0';
    return realloc(string , (index+1)*sizeof(char));

}