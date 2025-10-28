#ifndef PLATFORM_H
#define PLATFORM_H
#include "post.h"
#include "comment.h"
#include <stdbool.h>

typedef struct Platform
{
    Post *posts; // Linked list of posts (most recent first)
    Post *lastviewed; // Last viewed post
} Platform;

Platform *createPlatform();                                              //Function to create the platform
bool addPost(char *username,char *caption,Platform *platform);         //Function to add a post
bool deletePost(Platform *platform,int n);                              //Function to delete nth recent post
Post *viewPost(Platform *platform,int n);                               //Function to view nth recent post
Post *currPost(Platform *platform);                                      //Function to get current post
Post *nextPost(Platform *platform);                                      //Function to get next post (the older one)
Post *previousPost(Platform *platform);                                  //Function to get previous post (the newer one)
bool addComment(Platform *platform,char *username,char *content);      //Function to add comment to current post
bool deleteComment(Platform *platform,int n);                           //Function to delete nth recent comment from current post
Comment *viewComments(Platform *platform);                               //Function to view all comments of current post
bool addReply(Platform *platform,char *username,char *content, int n); //Function to add reply to nth recent comment
bool deleteReply(Platform *platform,int n,int m);                      //Function to delete mth recent reply to nth recent comment
void freeplatform(Platform *platform);                                   //Function to free the platform

#endif