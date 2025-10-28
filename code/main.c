#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include "reply.h"
#define MAXI 2000

void printcomms()
{
    printf("\n=== Available Commands === \n");
    printf("create_platform \n");
    printf("add_post <username> <caption> \n");
    printf("delete_post <n> \n");
    printf("view_post <n> \n");
    printf("current_post\n");
    printf("next_post \n");
    printf("previous_post\n");
    printf("add_comment <username> <content> \n");
    printf("delete_comment <n> \n");
    printf("view_comments \n");
    printf("add_reply <username> <content> <n> \n");
    printf("delete_reply <n> <m> \n");
    printf("exit \n\n");
}

int main()
{
    Platform *platform=NULL;
    char line[MAXI];
    char cmd[MAXI];
    char arg1[MAXI],arg2[MAXI],arg3[MAXI];
    int n,m;
    printcomms(); // Show all available commands
    while (fgets(line, MAXI, stdin)) // our main loop which reloops which exit
    {
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')// remove newline chr from the input
        {
            line[len - 1] = '\0';
        }
        if (sscanf(line, "%s", cmd) < 1) 
        {
            continue;
        }

/*********************** Main Menu and command handling******************************/
        if (strcmp(cmd,"create_platform")==0)
        {
            if (platform)
            {
                printf("Platform already exists\n");
            }
            else
            {
                platform=createPlatform();
                if (platform)
                {
                    printf("Platform created \n");
                }
                else
                {
                    printf("Failed to create platform \n");
                }
            }
        }
        else if (strcmp(cmd,"add_post")==0) // add_post 
        {
            if (!platform)
            {
                printf("No platform exists\n");
                continue;
            }
            if (sscanf(line, "add_post %s %[^\n]", arg1, arg2) == 2)
            {
                if (addPost(arg1,arg2,platform))
                {
                    printf("Post added\n");
                }
                else
                {
                    printf("Failed to add post\n");
                }
            }
            else
            {
                printf("Invalid format. Please refer the format above\n");
            }
        }
        else if (strcmp(cmd, "delete_post") == 0) // Delete a post by index
        {
            if (!platform)
            {
                printf("No platform exists\n");
                continue;
            }
            if (sscanf(line,"delete_post %d",&n) == 1)
            {
                if (deletePost(platform,n))
                {
                    printf("Post deleted \n");
                }
                else
                {
                    printf("Post does not exist \n");
                }
            }
            else
            {
                printf("Invalid format. Please refer the format above \n");
            }
        }
        else if (strcmp(cmd,"view_post") == 0) // See a specific post by index
        {
            if (!platform)
            {
                printf("No platform exists \n");
                continue;
            }
            if (sscanf(line, "view_post %d", &n) == 1)
            {
                Post *post = viewPost(platform, n);
                if (post)
                {
                    printf("%s %s\n", post->username, post->caption);
                }
                else
                {
                    printf("Post does not exist \n");
                }
            }
            else
            {
                printf("Invalid format. Please refer the format above \n");
            }
        }
        else if (strcmp(cmd,"current_post")==0) // Show the currently viewing post
        {
            if (!platform)
            {
                printf("No platform exists\n");
                continue;
            }
            Post *post =currPost(platform);
            if (post)
            {
                printf("%s %s\n", post->username, post->caption);
            }
            else
            {
                printf("No post available\n");
            }
        }
        else if (strcmp(cmd, "next_post") == 0) // Move to next post
        {
            if (!platform)
            {
                printf("No platform exists\n");
                continue;
            }
            Post *og = platform->lastviewed;
            Post *post = nextPost(platform);
            if (post && post!=og)
            {
                printf("%s %s\n",post->username,post->caption);
            }
            else if (post==og)
            {
                printf("%s %s\n",post->username,post->caption);
            }
            else
            {
                printf("Next post does not exist\n");
            }
        }
        else if (strcmp(cmd, "previous_post") == 0) // Move to previous post
        {
            if (!platform)
            {
                printf("No platform exists\n");
                continue;
            }
            Post *og = platform->lastviewed;
            Post *post = previousPost(platform);
            if (post&&post!=og)
            {
                printf("%s %s\n",post->username,post->caption);
            }
            else if (post == og)
            {
                printf("%s %s\n",post->username,post->caption);
            }
            else
            {
                printf("Previous post does not exist\n");
            }
        }
        else if (strcmp(cmd,"add_comment")==0) // Add comment to current post
        {
            if (!platform)
            {
                printf("No platform exists\n");
                continue;
            }
            if (sscanf(line, "add_comment %s %[^\n]",arg1,arg2)==2)
            {
                if (addComment(platform, arg1, arg2))
                {
                    printf("Comment added \n");
                }
                else
                {
                    printf("Failed to add comment \n");
                }
            }
            else
            {
                printf("Invalid format. Please refer the format above \n");
            }
        }
        else if (strcmp(cmd,"delete_comment")==0) // Delete a comment
        {
            if (!platform)
            {
                printf("No platform exists \n");
                continue;
            }
            if (sscanf(line, "delete_comment %d",&n)==1)
            {
                if (deleteComment(platform, n))
                {
                    printf("Comment deleted \n");
                }
                else
                {
                    printf("Comment does not exist \n");
                }
            }
            else
            {
                printf("Invalid format. Please refer the format above\n");
            }
        }
        else if ((strcmp(cmd,"view_comments") == 0) || (strcmp(cmd, "view_all_comments") == 0)) // View all comments and their replies on current post
        {
            if (!platform)
            {
                printf("No platform exists\n");
                continue;
            }
            Comment *comments = viewComments(platform);
            if (!comments)
            {
                printf("No comments\n");
            }
            else
            {
                Comment *c = comments;
                while (c)
                {
                    printf("%s %s\n",c->username,c->content);
                    Reply *r = c->replies;
                    while (r)
                    {
                        printf("%s %s\n",r->username,r->content);
                        r = r->next;
                    }
                    c = c->next;
                }
            }
        }
        else if (strcmp(cmd,"add_reply") == 0) //Add reply to a comment
        {
            if (!platform)
            {
                printf("No platform exists\n");
                continue;
            }
            if (sscanf(line,"add_reply %s %s %d",arg1,arg2, &n) == 3)
            {
                if (addReply(platform,arg1,arg2,n))
                {
                    printf("Reply added\n");
                }
                else
                {
                    printf("Failed to add reply\n");
                }
            }
            else
            {
                printf("Invalid format. Please refer the format above\n");
            }
        }
        else if (strcmp(cmd,"delete_reply")==0) // Delete a reply
        {
            if (!platform)
            {
                printf("No platform exists \n");
                continue;
            }
            if (sscanf(line,"delete_reply %d %d",&n,&m)==2)
            {
                if (deleteReply(platform,n,m))
                {
                    printf("Reply deleted \n");
                }
                else
                {
                    printf("Reply does not exist \n");
                }
            }
            else
            {
                printf("Invalid format. Please refer the format above \n");
            }
        }
        else if (strcmp(cmd, "exit") == 0) // Exit
        {
            printf("Goodbye! \n");
            break;
        }
        else
        {
            printf("Invalid command \n");
        }
    }

    if (platform) freeplatform(platform);
    return 0;
}