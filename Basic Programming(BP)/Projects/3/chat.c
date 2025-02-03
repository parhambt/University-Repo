#include "struct.c"
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "function.h"
void newChat(char chat_name[],char other_username[],System * system,User * user_head,Chat ** chats_head)
{
    User * user = searchUser(other_username,user_head) ; 
    if(system->logged_in_user==NULL) // like before we did in user
    {
        printf("Error: No user is currently logged in.\n");
        return ;
    }
    else if (user==NULL)
    {
        printf("Error: User %s not found.\n",other_username);
        return ; 
    }
    else if (user==system->logged_in_user)
    {
        printf("Error: You cannot create a chat with yourself.\n");
        return;
    }
    else if (searchChat(chat_name,system->logged_in_user  , *chats_head)!=NULL)
    {
        printf("Error: Chat with name %s already exists.\n",chat_name);
        return ;
    }
    else
    {   // adding the new node to after head for efficiency and do not use loop 
        Chat * tmp = * chats_head ; 
        *chats_head=malloc(sizeof(Chat));
        (*chats_head)->next = tmp ; 
        strcpy((*chats_head)->name,chat_name) ; 
        ((*chats_head)->users)[0]=system->logged_in_user ; 
        ((*chats_head)->users)[1]=user ; 
        printf("Chat with the name %s created between %s and %s.\n",chat_name,system->logged_in_user->username,user->username);
    }

}
Chat * searchChat(char name[],User * user_1,Chat * chats_head)
{
    while(chats_head!=NULL)
    {
        if(strcmp(chats_head->name,name)==0&&((chats_head->users)[0]==user_1 ||(chats_head->users)[1]==user_1)) return chats_head ; // return chat's pointer

        chats_head=chats_head->next ; 
    }
    return NULL ; 
}
void selectChat(char chat_name[],System * system,Chat * chats_head)
{
    Chat * chat = searchChat(chat_name,system->logged_in_user,chats_head) ; 
    if(system->logged_in_user==NULL)
    {
        printf("Error: No user is currently logged in.\n");
        return ;
    }
    else if(chat==NULL)
    {
        printf("Error: Chat %s not found for user %s.\n",chat_name,(system->logged_in_user)->username);
        return ; 
    }
    else 
    {
        system->selected_chat=chat ; // assign it to system aware from it 
        printf("Chat %s has been selected as the current chat\n",chat_name);
        return ;
    }

    
}
void sendMessage(char* message,System * system,Message ** messages_head)
{
    if(system->logged_in_user==NULL)// it was not on the pdf but it does make sense
    {
        printf("Error: No user is currently logged in.\n");
        return ;
    }
    else if(system->selected_chat==NULL)
    {
        printf("Error: No chat selected. Please select a chat first.\n");
        return ;
    }
    else // we are not allowed to use pointer function so we can not make one node maker and use it in all codes so there is no point to make seperate function for single use
    {
         //add new node at the end beacuse of order of showing chat 
        Message * tmp =*messages_head ; 

        Message *new_message = malloc(sizeof(Message));
        // strcpy(new_message->message, message);
        new_message->message = message ; 
        new_message->chat = system->selected_chat;
        new_message->user = system->logged_in_user;
        new_message->next = NULL;

        
        if (*messages_head == NULL) {
            *messages_head = new_message; 
        } else {
            Message *tmp = *messages_head;
            while (tmp->next != NULL) { 
                tmp = tmp->next;
            }
            tmp->next = new_message; 
        }
        User * reciver  ; 
        for (int i =0 ; i<2 ; i++)
        {
            if(system->selected_chat->users[i]!=system->logged_in_user) 
            {
                reciver=system->selected_chat->users[i] ; 
            }
        }
        Chat * chat=system->selected_chat ; 
        if((reciver->username)>(chat->name))
        {
            (chat->messages)[0]=*messages_head ;
        }
        else (chat->messages)[1]=*messages_head ;
        return ;

    }
}

void showChat(System* system,Message * messages_head)
{
    if(system->logged_in_user==NULL)// it was not on the pdf but it does make sense
    {
        printf("Error: No user is currently logged in.\n");
        return ;
    }
    else if (system->selected_chat==NULL)
    {
        printf("Error: No chat selected. Please select a chat first.\n");
        return ;
    }
    else 
    {
        while(messages_head!=NULL)
        {
            if(messages_head->chat==system->selected_chat)
            {
                printf("%s: %s\n",(messages_head->user)->username,messages_head->message);

            }
            messages_head=messages_head->next ; 
        }
    }
}
void free_chat_memmory(Chat* head)//for phase 1
{
    Chat * tmp = head ; 
    while(head!=NULL)
    {
       tmp= head->next ;
        free(head); 
        head=tmp  ;

    }    
}
void free_message_memmory(Message* head)//for phase 1
{
    Message * tmp = head ; 
    while(head!=NULL)
    {
        tmp= head->next ;
        free(head->message) ; 
        free(head); 
        head=tmp  ;

    }    
}