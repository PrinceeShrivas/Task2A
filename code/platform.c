#include "platform.h"
#include "reply.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Platform *createPlatform() // Creates a Platform
{
    Platform *platform=(Platform *)malloc(sizeof(Platform));
    if (!platform)
    {
        printf("Memory allocation failed for platform \n");
        return NULL;
    }
    platform->lastviewed=NULL, platform->posts=NULL;
    return platform;
}
bool addPost(char *username,char *caption,Platform *platform) // Function to add a post
{
    Post *post=createPost(username,caption);
    if (!post) return false;
    post->next = platform->posts; 
    platform->posts = post;
    if (!platform->lastviewed) // set the new post as lastviewed if no post existed
    {
        platform->lastviewed = post;
    }
    return true;
}

bool deletePost(Platform *platform, int n) // delete nth post
{
    if (!(platform) || !(platform->posts)) return false;

    Post *curr = platform->posts;
    Post *prev = NULL;
    for (int i = 1; i < n && curr; i++)
    {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) return false;
    if (platform->lastviewed == curr) // Update the last viewedpost if required
    {
        platform->lastviewed = curr->next ? curr->next : platform->posts;
        if (platform->lastviewed == curr)
        {
            platform->lastviewed = NULL;
        }
    }
    if (prev)
    {
        prev->next = curr->next;
    }
    else
    {
        platform->posts = curr->next;
    }
    freepost(curr);
    return true;
}

Post *viewPost(Platform *platform, int n) // Function to view rhe nth recent post.
{
    if (!(platform) || !(platform->posts)) return NULL;

    Post *curr = platform->posts;

    for (int i = 1; i < n && curr; i++)     // Navigate to nth recent post (1-indexed)
    {
        curr = curr->next;
    }

    if (curr)
    {
        platform->lastviewed = curr;
    }
    return curr;
}

Post *currPost(Platform *platform)
{
    if (!platform) return NULL;

    return platform->lastviewed;
}

Post *nextPost(Platform *platform) // Next post is the one posted just before or the older post
{
    if (!(platform) || !(platform->lastviewed)) return NULL;

    if (platform->lastviewed->next)     // If not the oldest post just return the next one
    {
        platform->lastviewed = platform->lastviewed->next;
        return platform->lastviewed;
    }
    return platform->lastviewed;     // Already at oldest post, so we will just return it
}

Post *previousPost(Platform *platform) // Previous post is the post posted just after or the newer post
{
    if (!platform || !platform->lastviewed) return NULL;

    Post *curr = platform->posts;
    if (curr == platform->lastviewed) // Lastviewed post == curr => we are at the most recent post no prev exist
    {
        return platform->lastviewed;
    }
    while (curr && curr->next != platform->lastviewed) // find the prev post of lastviewed post
    {
        curr = curr->next;
    }

    if (curr && curr->next == platform->lastviewed)
    {
        platform->lastviewed = curr;
        return platform->lastviewed;
    }
    return NULL;
}

bool addComment(Platform *platform,char *username, char *content)
{
    if (!platform || !platform->lastviewed) return false;

    Comment *comment = createComment(username,content);
    if (!comment) return false;
    if (!platform->lastviewed->comments)
    {
        platform->lastviewed->comments = comment;
    }
    else
    {
        Comment *curr = platform->lastviewed->comments;
        while (curr->next)
        {
            curr = curr->next;
        }
        curr->next = comment;
    }
    return true;
}

bool deleteComment(Platform *platform, int n) 
{
    if (!platform || !(platform->lastviewed) || !(platform->lastviewed->comments)) return false;

    Comment *curr = platform->lastviewed->comments;
    int cnt = 0;
    while (curr)
    {
        cnt++;
        curr = curr->next;
    }

    int pos = cnt - n + 1;
    if (pos < 1 || pos > cnt) return false;

    curr = platform->lastviewed->comments;
    Comment *prev = NULL;

    for (int i = 1; i < pos && curr; i++)
    {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) return false;

    if (prev)
    {
        prev->next = curr->next;
    }
    else
    {
        platform->lastviewed->comments = curr->next;
    }
    freecomment(curr);
    return true;
}

Comment *viewComments(Platform *platform)
{
    if (!(platform) || !(platform->lastviewed)) return NULL;
    return platform->lastviewed->comments;
}

bool addReply(Platform *platform,char *username,char *content,int n)
{
    if (!platform || !(platform->lastviewed) || !(platform->lastviewed->comments)) return false;

    Comment *curr = platform->lastviewed->comments;
    int cnt = 0;     // Count total comments
    while (curr)
    {
        cnt++;
        curr = curr->next;
    }
    int pos = cnt-n+1; // Convert to posn from start (1 base indexing)
    if (pos<1 || pos>cnt) return false;

    curr = platform->lastviewed->comments;
    for (int i = 1; i < pos && curr; i++)
    {
        curr = curr->next;
    }

    if (!curr) return false;

    Reply *reply = createReply(username, content);
    if (!reply) return false;

    // Add the replies at the end
    if (!curr->replies) 
    {
        curr->replies = reply;
    }
    else
    {
        Reply *r = curr->replies;
        while (r->next)
        {
            r = r->next;
        }
        r->next = reply;
    }
    return true;
}

bool deleteReply(Platform *platform, int n, int m)
{
    if (!platform || !platform->lastviewed || !platform->lastviewed->comments) return false;
    Comment *curr = platform->lastviewed->comments;
    int cnt = 0;
    while (curr)
    {
        cnt++;
        curr = curr->next;
    }

    int pos = cnt-n+1;
    if (pos<1 || pos>cnt) return false;

    curr = platform->lastviewed->comments;
    for (int i = 1; i<pos &&curr;i++)
    {
        curr = curr->next;
    }

    if (!curr || !(curr->replies)) return false;

    // Count replies and find mth recent
    Reply *r = curr->replies;
    int rcnt = 0;
    while (r)
    {
        r = r->next;
        rcnt++;
    }

    int rpos = rcnt - m + 1;
    if (rpos<1||rpos>rcnt) return false;

    r = curr->replies;
    Reply *prev = NULL;
    for (int i = 1; i<rpos &&r; i++)
    {
        prev = r;
        r = r->next;
    }
    if (!r) return false;

    if (prev)
    {
        prev->next = r->next;
    }
    else
    {
        curr->replies = r->next;
    }
    freereply(r);
    return true;
}

void freeplatform(Platform *platform) // Function to free the memory allocated for the platform
{
    if (!platform) return;
    Post *curr=platform->posts;
    while (curr)                   // To delete all the posts first
    {
        Post *temp=curr;
        curr=curr->next;
        freepost(temp);
    }
    free(platform);
}