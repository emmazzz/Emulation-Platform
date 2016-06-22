/*
 * CS:APP Binary Bomb (Autolab version)
 *
 * Copyright (c) 2004, R. Bryant and D. O'Hallaron, All rights reserved.
 * May not be used, modified, or copied without permission.
 */ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "phases.h"
#include "support.h"

/* Global bomb ID */
int bomb_id = 2;

/* Global userid */
char userid[1024] = "jzhong1@andrew.cmu.edu";

/* Global authkey */
char authkey[1024] = "1821904";

/* Global courseid */
char course[1024] = "15213-m16";

/* Global labid */
char lab[1024] = "bomblab";
    
/* 
 * phase1a.c - The user's input must match the specified string 
 */ 
void phase_1(char *input)
{
#if defined(PROBLEM)
    if (strings_not_equal(input, "Houses will begat jobs, jobs will begat houses.") != 0)
        explode_bomb();
#elif defined(SOLUTION)
    printf("Houses will begat jobs, jobs will begat houses.\n");
#else
    invalid_phase("1a");
#endif    
}   

/*  
 * phase2a.c - To defeat this stage the user must enter a sequence of 
 * 6 nonnegative numbers where x[i] = x[i-1] + i
 */
void phase_2(char *input)
{
#if defined(PROBLEM)
    int i;
    int numbers[6];
    
    read_six_numbers(input, numbers);
    
    if (numbers[0] < 0)
    explode_bomb();
    
    for(i = 1; i < 6; i++) {
    if (numbers[i] != numbers[i - 1] + i)
        explode_bomb();
    }
#elif defined(SOLUTION)
    printf("2 3 5 8 12 17\n");
#else
    invalid_phase("2a");
#endif
}   
/* 
 * phase3b.c - A long switch statement that the compiler should
 * implement with a jump table. The user must enter both an index 
 * into the table and the sum accumulated by falling through the rest 
 * of the table 
 */

void phase_3(char *input)
{
#if defined(PROBLEM)
    int index, sum, x = 0;
    int numScanned = 0;
    
    numScanned = sscanf(input, "%d %d", &index, &sum);
    
    if (numScanned < 2)
    explode_bomb();
    
    switch(index) {
    case 0:
    x = x + 582;
    case 1:
    x = x - 68;                                                                                                                                                                      
    case 2:
    x = x + 589;
    case 3:
    x = x - 512;
    case 4:
    x = x + 512;
    case 5:
    x = x - 512;
    case 6:
    x = x + 512;
    case 7:
    x = x - 512;
    break;
    default:
    explode_bomb();
    }
    
    if ((index > 5) || (x != sum))
    explode_bomb();
#elif defined(SOLUTION)
    printf("3 -512\n");
#else
    invalid_phase("3b");
#endif
}   
/* 
 * phase4c.c - A recursive function to sort out.  
 *
 *          0, if n=0
 * F(n,b) = b, if n=1, 
 *          b + F(n-1, b) + F(n-2, b), if n>1
 * 
 * For a randomly chosen n, student must enter matching F(n, b) and b.
 */

int func4(int n, int base) {
    if (n <= 0) {
    return 0; 
    }
    if (n == 1) {
    return base;
    }
    return base + func4(n-1, base) + func4(n-2, base);
}   
    
void phase_4(char *input) {                                                                                                                                                          
#if defined(PROBLEM)
    int n, base, val, result, numScanned;

    numScanned = sscanf(input, "%d %d", &val, &base);
    if ((numScanned != 2) || (base < 2) || (base > 4)) {
    explode_bomb();
    }

    n = 8;
    result = func4(n, base);
    
    if (result != val) {
    explode_bomb();
    }
#elif defined(SOLUTION)
    printf("%d %d %s\n", func4(8, 4), 4, SECRET_PHRASE);
#else
    invalid_phase("4c");
#endif
}

/*  
 * phase5a.c - Just to be hairy, this traverses a loop of pointers and 
 * counts its length.  The input determines where in the loop we begin. 
 * Just to make sure the user isn't guessing, we make them input the sum of
 * the pointers encountered along the path, too.
 */
void phase_5(char *input)
{
#if defined(PROBLEM)
    static int array[] = {
      10,
      2,
      14,
      7,
      8,
      12,
      15,
      11,
      0,
      4,
      1,
      13,
      3,
      9,
      6,
      5
    };
      
    int count, sum;
    int start;
    int p, result;
    int numScanned;
    
    numScanned = sscanf(input, "%d %d", &p, &result);
    
    if (numScanned < 2)
      explode_bomb();
    
    p = p & 0x0f;
    start = p; /* debug */
    
    count = 0; 
    sum = 0;
    while(p != 15) {
    count++;                                                                                                                                                                         
    p = array[p];
    sum += p;
    } 

if ((count != 15) || (sum != result))
    explode_bomb();
#elif defined(SOLUTION)
    switch (15) {
    case 1: printf("6 15"); break;
    case 2: printf("14 21"); break;
    case 3: printf("2 35"); break;
    case 4: printf("1 37"); break;
    case 5: printf("10 38"); break;
    case 6: printf("0 48"); break;
    case 7: printf("8 48"); break;
    case 8: printf("4 56"); break;
    case 9: printf("9 60"); break;
    case 10: printf("13 69"); break;
    case 11: printf("11 82"); break;
    case 12: printf("7 93"); break;
    case 13: printf("3 100"); break;
    case 14: printf("12 103"); break;
    case 15: printf("5 115"); break;
    default: 
    printf("ERROR: bad count value in phase5a\n");
    exit(8); 
    }
    printf("\n");
#else
    invalid_phase("5a");
#endif
}   

/*  
 * phase6b.c - The user has to enter the node numbers (from 1 to 6) in 
 * the order that they will occur when the list is sorted in descending order.
 */
listNode node6 = {764, 6, NULL};
listNode node5 = {98, 5, &node6};
listNode node4 = {625, 4, &node5};
listNode node3 = {349, 3, &node4};
listNode node2 = {500, 2, &node3};
listNode node1 = {997, 1, &node2};

#if defined(SOLUTION)
/* Sort list in descending order */
listNode *fun6(listNode *start)
{
    listNode *head = start;
    listNode *p, *q, *r;

    head = start;                                                                                                                                                                    
    p = start->next;
    head->next = NULL;

    while (p != NULL) {
    r = head;
q = head;
    
    while ((r != NULL) && (r->value > p->value)) {
        q = r;
        r = r->next;
    }   
        
    if (q != r)
        q->next = p;
    else
        head = p; 
    
    q = p->next;
    p->next = r;
    
    p = q;
    }
    
    return head;
}   
#endif

void phase_6(char *input)
{
#if defined(PROBLEM)
    listNode *start = &node1;
    listNode *p;
    int indices[6]; 
    listNode *pointers[6];
    int i, j;
    
    read_six_numbers(input, indices);
    
    /* Check the range of the indices and whether or not any repeat */
    for (i = 0; i < 6; i++) {
    if ((indices[i] < 1) || (indices[i] > 6))
        explode_bomb();
    
    for (j = i + 1; j < 6; j++) {
        if (indices[i] == indices[j])
        explode_bomb(); 
    }   
    }   
    
    /* Rearrange the list according to the user input */
    for (i = 0; i < 6; i++) {
    p = start;
    for (j = 1; j < indices[i]; j++)                                                                                                                                                 
        p = p -> next;
    pointers[i] = p;
    }   
    
    start = pointers[0];
    p = start;
        
    for (i = 1; i < 6; i++) {
    p->next = pointers[i];
    p = p->next;
    }
    p->next = NULL;
    
    /* Now see if the list is sorted in descending order */
    p = start;
    for (i = 0; i < 5; i++) {
    if (p->value < p->next->value)
        explode_bomb();
    
    p = p->next; 
    }   
#elif defined(SOLUTION)
    listNode *start = &node1;
    listNode *p;

    /* sort */
    start = fun6(start);

    /* emit the node indices of the sorted list */
    p = start;
    while (p) {
    printf("%d ", p->index);
    p = p->next;
    }
    printf("\n"); 
#else 
    invalid_phase("6b");
#endif
}
/* 
 * phase7.c - The infamous secret stage! 
 * The user has to find leaf value given path in a binary tree.
 */

typedef struct treeNodeStruct
{
    int value; 
    struct treeNodeStruct *left, *right;
} treeNode;
    
/* balanced binary tree containing randomly chosen values */
treeNode n48 = {1001, NULL, NULL};
treeNode n46 = {47, NULL, NULL};
treeNode n43 = {20, NULL, NULL};
treeNode n42 = {7, NULL, NULL};
treeNode n44 = {35, NULL, NULL};
treeNode n47 = {99, NULL, NULL};
treeNode n41 = {1, NULL, NULL};
treeNode n45 = {40, NULL, NULL};
treeNode n34 = {107, &n47, &n48};
treeNode n31 = {6, &n41, &n42};
treeNode n33 = {45, &n45, &n46};
treeNode n32 = {22, &n43, &n44};
treeNode n22 = {50, &n33, &n34};
treeNode n21 = {8, &n31, &n32};
treeNode n1 = {36, &n21, &n22};

/* 
 * Searches for a node in a binary tree and returns path value.
 * 0 bit denotes left branch, 1 bit denotes right branch
 * Example: the path to leaf value "35" is left, then right,
 * then right, and thus the path value is 110(base 2) = 6.
 */

int fun7(treeNode* node, int val)
{
    if (node == NULL) 
    return -1;
    
    if (val < node->value)
    return fun7(node->left, val) << 1;
    else if (val == node->value)
    return 0;
    else 
    return (fun7(node->right, val) << 1) + 1;
}   
void secret_phase()
{

#if defined(PROBLEM)
    char *input = read_line();
    int target = atoi(input);
    int path;
    
    /* Make sure target is in the right range */
    if ((target < 1) || (target > 1001))
    explode_bomb();
    
    /* Determine the path to the given target */
    path = fun7(&n1, target);
    
    /* Compare the retrieved path to a random path */
    if (path != 6)
    explode_bomb();
    
    printf("Wow! You've defused the secret stage!\n");
    
    phase_defused();
#elif defined(SOLUTION)
    int path = 6;
    treeNode *node = &n1;
    
    node = (path    & 0x1) ? node->right : node->left;
    node = (path>>1 & 0x1) ? node->right : node->left;
    node = (path>>2 & 0x1) ? node->right : node->left;
    printf("%d\n", node->value);
#else
    invalid_phase("7");
#endif
}

             
