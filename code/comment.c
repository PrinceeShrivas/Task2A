#include "comment.h"
#include "reply.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Comment *createComment(char *username,char *content) //Function to create a reply
{
    Comment *comment = (Comment *)malloc(sizeof(Comment));
    if (!comment)
    {
        printf("Memory allocation failed \n");
        return NULL;
    }
    comment->username=(char *)malloc(strlen(username)+1);// Allocate memmory for the data of a comment
    comment->content=(char *)malloc(strlen(content)+1);
    if (!comment->username||!comment->content)
    {
        printf("Memory allocation failed\n");
        free(comment->username);
        free(comment->content);
        free(comment);
        return NULL;
    }
    strcpy(comment->username,username);
    strcpy(comment->content,content);
    comment->replies=NULL;
    comment->next=NULL;
    return comment;
}
void freecomment(Comment *comment) //Function to free the allocated memory for a reply
{
    if (!comment) return;
    Reply *current = comment->replies;
    while (current)
    {
        Reply *temp =current;
        current =current->next;
        freereply(temp);
    }
    free(comment->username);
    free(comment->content);
    free(comment);
}