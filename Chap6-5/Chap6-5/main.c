//
//  main.c
//  Chap6-5
//
//  Created by Anh Luong on 7/14/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>


#define HASHSIZE            101

struct nlist {              // table entry:
    struct nlist *next;     // next entry in chain
    char *name;             // defined name
    char *defn;             // replacement text
};

static struct nlist *hashtab[HASHSIZE]; // pointer table

/* word frequency count */
int main(int argc, const char * argv[]) {
    
    return 0;
}

/* hash:    form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    
    for (hashval = 0; *s != '0'; s++)
        hashval = *s + 31 * hashval;
    
    return hashval % HASHSIZE;
}

#include <string.h>

/* lookup:  look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;                  // found
    return NULL;                        // not found
}

struct nlist *lookup(char *);

#include <stdlib.h>
char *mystrdup(char *);

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    
    if ((np = lookup(name)) == NULL) {  // not found
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else
        free((void *)np->defn);         // free previous defn
    
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/* undef: remove a name in hashtab */
void undef(char *name)
{
    struct nlist *np;
    struct nlist *head;
    
    if ((np = lookup(name)) == NULL)
        return;
    
    // comes here means there's an entry for the name
    head = hashtab[hash(name)];
    
    while (head != np) {
        if (head->next == np) { // the other way is to check if (strcmp(head->name, name) == 0)
            head->next = np->next;
            free((void *)np->name);
            free((void *)np->defn);
            free((void *)np);
        }
        head = head->next;
    }
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