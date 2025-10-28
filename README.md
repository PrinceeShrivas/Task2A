# Social Media Platform

A command-line based social media platform implemented in C that allows users to create posts, add comments, and reply to comments using linked list data structures.

## Features

- **Post Management**: Create, view, navigate, and delete posts
- **Comment System**: Add and delete comments on posts
- **Reply System**: Reply to specific comments
- **Navigation**: Browse through posts using next/previous commands
- **Memory Safe**: Proper memory allocation and deallocation for all data structures

## Project Structure

```
.
├── code/
│   ├── main.c          # Main program and command interface
│   ├── platform.c/h    # Platform management and core operations
│   ├── post.c/h        # Post data structure and operations
│   ├── comment.c/h     # Comment data structure and operations
│   └── reply.c/h       # Reply data structure and operations
├── Makefile            # Build configuration
└── README.md           # This file
```

## Data Structures

The application uses a hierarchical linked list structure:

- **Platform**: Contains a linked list of posts and tracks the last viewed post
- **Post**: Contains username, caption, and a linked list of comments
- **Comment**: Contains username, content, and a linked list of replies
- **Reply**: Contains username and content

## Building the Project

### Prerequisites

- GCC compiler
- Make utility
- Windows environment (for the clean command, or modify for Unix/Linux)

### Compilation

```bash
# Build the project
make

# Clean build artifacts
make clean

# Build and run
make run
```

The executable will be named `social_media.exe` (or `social_media` on Unix systems).

## Usage

### Starting the Application

Run the compiled executable:

```bash
./social_media
```

### Available Commands

#### Platform Management
- `create_platform` - Initialize the social media platform

#### Post Operations
- `add_post <username> <caption>` - Create a new post
- `delete_post <n>` - Delete the nth most recent post
- `view_post <n>` - View the nth most recent post
- `current_post` - Display the currently viewed post
- `next_post` - Navigate to the next (older) post
- `previous_post` - Navigate to the previous (newer) post

#### Comment Operations
- `add_comment <username> <content>` - Add a comment to the current post
- `delete_comment <n>` - Delete the nth most recent comment from the current post
- `view_comments` - Display all comments and replies on the current post

#### Reply Operations
- `add_reply <username> <content> <n>` - Add a reply to the nth most recent comment
- `delete_reply <n> <m>` - Delete the mth most recent reply from the nth most recent comment

#### Other
- `exit` - Exit the application

### Example Session

```
create_platform
Platform created

add_post prince Hello World!
Post added

add_post shubham My first post
Post added

current_post
shubham My first post

add_comment raj Great post!
Comment added

add_reply prince Thanks! 1
Reply added

view_comments
raj Great post!
prince Thanks!

next_post
prince Hello World!

previous_post
shubham My first post
```

## Indexing Convention

- **Posts**: Indexed from 1 (most recent) to n (oldest)
- **Comments**: Indexed from 1 (most recent) to n (oldest)
- **Replies**: Indexed from 1 (most recent) to n (oldest) within each comment

## Memory Management

The application handles memory allocation and deallocation automatically:

- All dynamically allocated strings are properly freed
- Deleting a post frees all its comments and replies
- Deleting a comment frees all its replies
- The platform and all its data are freed on exit

## Error Handling

The application provides feedback for:

- Invalid commands
- Memory allocation failures
- Operations on non-existent items
- Invalid index values
- Missing platform initialization

## Limitations

- Maximum input line length: 2000 characters
- Comments and replies cannot contain newline characters in input
- Usernames and content are separated by spaces in commands

## Contributing

When modifying the code:

1. Maintain the linked list structure integrity
2. Ensure proper memory management (no leaks)
3. Update this README for any new features
4. Test all navigation and deletion edge cases

## Author

Prince - 106124088
