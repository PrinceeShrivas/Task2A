#ifndef COMMENT_H
#define COMMENT_H

#include <stdbool.h>

typedef struct Reply Reply;
typedef struct Comment // Structure of Comments
{
    char *username;
    char *content;
    Reply *replies;   // Linked list of replies
    struct Comment *next;
} Comment;
Comment *createComment(char *username, char *content); // Function to create a new comment
void freecomment(Comment *comment);                    // Function to free the allocated memmory a comment and all its replies
#endif