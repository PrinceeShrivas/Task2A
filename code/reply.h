#ifndef REPLY_H
#define REPLY_H
typedef struct Reply // Strucutre of a reply
{
    char *username;
    char *content;
    struct Reply *next;
} Reply;
Reply *createReply(char *username, char *content); // This function will create a new reply
void freereply(Reply *reply);                      // Function to free the allocated memory of reply
#endif