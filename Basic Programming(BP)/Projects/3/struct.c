#include "struct.h"
//for phase 1
struct User
{
    char username[51];
    char password[51];
    Chat * chats_head ; 
    struct User * next ; 
};
struct Chat
{
    char name[51];
    User * users[2];
    //list of messages between two users
    Message * messages[2] ; 
    struct Chat * next ;
};

struct Message
{
    char *message;// make it dynamicly
    User *user ; 
    Chat *chat ; 
    struct Message * next ;
}; 
struct System
{
    User * all_users_head ; 
    User *logged_in_user ; 
    Chat *selected_chat ; 

};