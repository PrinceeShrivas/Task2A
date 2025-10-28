#ifndef POST_H
#define POST_H

typedef struct Comment Comment;

typedef struct Post // Structure of a Post
{
    char *username;
    char *caption;
    Comment *comments;// Using Linked List to store the comments of a post
    struct Post *next; // Pointer to the next location of the next Post
} Post;

Post *createPost(char *username, char *caption); // Function to create a new post
void freepost(Post *post);                       // Function to free allocated memory for post and comments on it

#endif