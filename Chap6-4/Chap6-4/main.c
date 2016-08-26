//
//  main.c
//  Chap6-4
//
//  Created by Anh Luong on 7/16/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD         100

typedef struct _tnode {          // the tree node
    char *word;                 // points to the text
    int count;                  // number of occurrences
    struct _tnode *left;        // left child
    struct _tnode *right;       // right child
} tnode;

tnode *addtree(tnode *, char *);
void treeprint(tnode *);
int getword(char *, int);
int isIgnoredWord(char *);
void myqsort(tnode *v, int left, int right);
void swap(tnode *t, int i, int j);
int treeToArray(tnode *root, tnode *ar, int index);
int tnodecmp(tnode a, tnode b);
int getch(void);
void myungetch(int);

#define BUFSIZE   100

char buf[BUFSIZE];    // buffer for myungetch
int bufp = 0;         // next free position in buf

char *ignoredWords[] = {
    "and",
    "the"
};

#define NIGNORED        (sizeof ignoredWords / sizeof(char *))
#define MAXKEY          1000;

/* word frequency count */
int main(int argc, const char * argv[])
{
    tnode *root;
    tnode *arrayTnode;
    char word[MAXWORD];
    int i, num;
    
    arrayTnode = (tnode *)malloc(sizeof(tnode) * 1000);
    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) && isIgnoredWord(word) != 0)
            root = addtree(root, word);
    treeprint(root);
    printf("done treeprint\n");

    // print distinct words in its input sorted into decreasing order of frequency of occurrence. This solution has the problem that the result does not print all of the words.
    num = treeToArray(root, arrayTnode, 0);
    myqsort(arrayTnode, 0, num - 1);
    for (i = 0; i < num; i++)
        printf("%4d %s\n", arrayTnode[i].count, arrayTnode[i].word);

    return 0;
}

int isIgnoredWord(char *word) {
    int i;
    for (i = 0; i < NIGNORED; i++) {
        if (strcmp(word, ignoredWords[i]) == 0)
            return 0;
    }
    return -1;
}

tnode *talloc(void);
char *mystrdup(char *);

/* addtree: add a node with w, at or below p */
tnode *addtree(tnode *p, char *w)
{
    int cond;
    
    if (p == NULL) {                            // a new wor has arrived
        p = talloc();                           // make a new node
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;                             // repeated word
    else if (cond < 0)                          // less than into left subtree
        p->left = addtree(p->left, w);
    else                                        // greater than into right subtree
        p->right = addtree(p->right, w);
    
    return p;
}

/* treeprint:   in-order print of tree p */
void treeprint(tnode *p)
{
    if (p == NULL)
        return;
    
    treeprint(p->left);
    printf("%4d %s\n", p->count, p->word);
    treeprint(p->right);
}

/* talloc:  make a tnode */
tnode *talloc(void)
{
    return (tnode *)malloc(sizeof(tnode));
}

/* strdup:  make a duplicate of s */
char *mystrdup(char *s)
{
    char *p;
    
    p = (char *) malloc(sizeof(s)+1);   // +1 for '\0'
    if (p != NULL)
        strcpy(p, s);
    return p;
}

int getch(void) // get a (possibly pushed-back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void myungetch(int c)   // push a character back on input
{
    if (bufp >= BUFSIZE)
        printf("myungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int getword(char *w, int lim)
{
    int c;
    
    while (isspace(c = getch()))
        ;
    
    if (c != EOF) {
        *w++ = c;
    }
    
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            myungetch(*w);
            break;
        }
    }
    *w = '\0';
    return w[0];
}

void myqsort(tnode *t, int left, int right)
{
    int i, last;

    if (left >= right)  // do nothing if array contains fewer than 2 elements
        return;
    
    swap(t, left, (right + left) / 2);
    last = left;
    for (i = left + 1; i <= right; i++) {
        if (tnodecmp(t[i], t[left]) > 0)
            swap(t, i, ++last);
    }
    
    swap(t, left, last);
    myqsort(t, left, last - 1);
    myqsort(t, last + 1, right);
}

int tnodecmp(tnode a, tnode b)
{
    int c;
    if ((c = (a.count - b.count)) != 0)
        return c;
    else
        return strcmp(a.word, b.word);
}

void copy(tnode *dest, tnode *src)
{
    dest->count = src->count;
    dest->left = src->left;
    dest->right = src->right;
    dest->word = src->word;
}

void swap(tnode *t, int i, int j)
{
    tnode temp;
    
    copy(&temp, (t+i));
    copy((t+i), (t+j));
    copy((t+j), &temp);
}

int treeToArray(tnode *root, tnode *array, int index)
{
    if (root == NULL)
        return index;
    
    array[index++] = *root;
    treeToArray(root->left, array, index++);
    treeToArray(root->right, array, index++);
    return index;
}