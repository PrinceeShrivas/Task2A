#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct Node
{
    struct Node *left, *right;
    int data;

} Node;
typedef struct Queuenode
{
    Node *treeNode;
    struct Queuenode *next;
} Queuenode;
typedef struct Queue
{
    Queuenode *front;
    Queuenode *rear;
} Queue;

int phones = 0;

// Queue ADT using linked list
Queue *createqueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->rear = NULL;
    q->front = NULL;
    return q;
}

Node *newNode() //  Constructor for the New Node
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = 1;
    node->left = node->right = NULL;
    return node;
}

void enqueue(Queue *q, Node *n)
{
    Queuenode *newNode = (Queuenode *)malloc(sizeof(Queuenode));
    newNode->treeNode = n;
    newNode->next = NULL;
    if (!q->rear)
    {
        q->front = q->rear = newNode;
    }
    else
    {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

Node *dequeue(Queue *q)
{
    if (!q->front)
        return NULL;
    Queuenode *temp = q->front;
    Node *ans = temp->treeNode;
    q->front = q->front->next;
    if (!q->front)
        q->rear = NULL;
    free(temp);
    return ans;
}
int isEmpty(Queue *q)
{
    return q->front == NULL;
}
void freeQueue(Queue *q)
{
    while (!isEmpty(q))
        dequeue(q);
    free(q);
}

Node *maketree(int n, int level[])
{
    if (n == 0 || level[0] == 0) // If the array is empty or level[0] is 0 this means no root exists which implies empty tree
        return NULL;

    Queue *q = createqueue();
    Node *root = newNode();
    enqueue(q, root);
    int i = 1;
    while (i < n && !isEmpty(q)) // Process nodes level by level until queue is not empty
    {
        Node *curr = dequeue(q);
        if (i < n && level[i] == 1) // If the next element is 1 this implies that current node has a left child

        {
            curr->left = newNode();
            enqueue(q, curr->left); // Create a node and enqueue it in the queue
        }
        i++;
        if (i < n && level[i] == 1) // If the next element is 1 this implies that current node has a right child
        {
            curr->right = newNode();
            enqueue(q, curr->right); // Create a node and enqueue it in the queue
        }
        i++;
    }
    freeQueue(q);
    return root;
}

int dfs(Node *root)
{
    if (root == NULL)
        return 2;

    int left = dfs(root->left); // Recursively left and right subtree
    int right = dfs(root->right);
    if (left == 0|| right == 0) // If any any child is not covered we cover it by placing a phone there
    {
        phones++;
        return 1; // Return 1 means this node has a phone
    }
    if (left == 1 || right == 1) // If any child has a phone this implies that this node is covered

        return 2; // Return 2 means this node is covered

    return 0; // Node is not covered and has no phone
}

int minphones(Node *root)
{
    phones = 0; // declared globally
    if (dfs(root)==0)
        phones++;
    return phones;
}

void sieve(int m, int *primes) // Using Sieve of Eratosthenes to find first m primes
{
    if (m <= 0)
        return;
    int limit = 300001; // upper bound for the sieve
    int i = 0,cnt=0,j=0;
    bool *isprime = malloc((limit + 1) * sizeof(bool));
    for (i = 0; i<=limit; i++)
        isprime[i]=true; // initially assume all the numbers are prime except 0 and 1
    isprime[0] = isprime[1] = false;
    for (i = 2; i*i<=limit; i++) // mark all multiples of each prime as non-prime
    {
        if (isprime[i])
        {
            for (j = i*i; j<=limit; j += i)
                isprime[j] = false;
        }
    }
    for (i = 2;i<=limit&&cnt<m; i++) // store prime number in primes array
    {
        if (isprime[i])
            primes[cnt++] = i;
    }
    free(isprime);
}

int countpairs(int l, int r, int m, int *arr) // For counting the pairs which do not lie in our required interval
{
    int cnt,i,j;
    cnt = 0,i = 0,j = 0;
    for (i = 0; i < m; i++)
    {
        for (j = i + 1; j < m; j++)
        {
            if ((arr[i]^arr[j])>= l && (arr[i]^arr[j])<=r)
            {
                continue;
            }
            cnt++;
        }
    }
    return cnt;
}

int main()
{
    int n, i;
    i = 0;
    scanf("%d", &n);
    int *level = (int *)malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
    {
        scanf("%d", &level[i]);
    }
    int l;
    int r;
    scanf("%d %d", &l, &r);
    Node *root = maketree(n, level);
    int m = minphones(root);
    printf("%d\n", m);
    int *primes = (int *)malloc(m * sizeof(int));
    sieve(m, primes);
    int ans = countpairs(l, r, m, primes);
    printf("%d", ans);
    free(primes);
    free(level);
    return 0;
}