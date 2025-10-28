#include "post.h"
#include "comment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Post *createPost(char *username, char *caption)
{
    Post *post=(Post *)malloc(sizeof(Post));
    if (!post)
    {
        printf("Memory allocation failed for post \n");
        return NULL;
    }
    post->username=(char *)malloc(strlen(username)+1);
    post->caption=(char *)malloc(strlen(caption)+1);
    if (!post->username || !post->caption)
    {
        printf("Memory allocation failed for post data \n");
        free(post->username);
        free(post->caption);
        free(post);
        return NULL;
    }
    strcpy(post->username, username);
    strcpy(post->caption, caption);
    post->comments = NULL;
    post->next = NULL;
    return post;
}
void freepost(Post *post)
{
    if (!post) return;
    Comment *current = post->comments;
    while (current)                   // Because we have to free all the comments on the post also 
    {
        Comment *temp = current;
        current = current->next;
        freecomment(temp);
    }
    free(post->username);
    free(post->caption);
    free(post);
}