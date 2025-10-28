#include "reply.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Reply *createReply(char *username, char *content) // Allocates and initializes a reply with given user and text
{
    Reply *rep=(Reply *)malloc(sizeof(Reply));
    if (!rep)
    {
        printf("Memory allocation failed for reply \n");
        return NULL;
    }
    rep->username = (char *)malloc(strlen(username)+1);
    rep->content = (char *)malloc(strlen(content)+1);
    if (!(rep->username) || !(rep->content))
    {
        printf("Memory allocation failed for reply data \n");
        free(rep->username);
        free(rep->content);
        free(rep);
        return NULL;
    }
    rep->next=NULL;
    strcpy(rep->username,username);
    strcpy(rep->content,content);
    return rep;
}
void freereply(Reply *reply) //Function to free the allocated memory for a reply
{
    if (!reply) return;
    free(reply->username);
    free(reply->content);
    free(reply);
}
