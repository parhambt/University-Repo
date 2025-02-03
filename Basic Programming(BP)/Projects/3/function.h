#include"struct.h"
void Signup(char username[],char password[],User ** user_head, int flag) ; 
User * searchUser(char username[],User * user_head);
void Login(char username[],char password[],User * user_head,System* system) ; 
void Logout(System *system);
Chat * searchChat(char name[],User * user_1,Chat * chats_head) ; 
void newChat(char chat_name[],char other_username[],System * system,User * user_head,Chat ** chats_head) ;
void selectChat(char chat_name[],System * system,Chat * chats_head) ;
void sendMessage(char *message,System * system,Message ** messages_head) ;
void showChat(System* system,Message * messages_head) ;
void free_user_memmory(User * head) ;
void free_chat_memmory(Chat* head);
void free_message_memmory(Message* head);
void loadUsers(char name_file[],User** user_head) ; 
char * read_unlimited_string(FILE *fp , size_t start_size) ;