#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include <errno.h>

#define TagRoot     1
#define TagNode     2
#define TagLeaf     4

#define NoError     0

// typedef void* Nullptr;
// Nullptr nullptr = 0;

#define find_last(x)        find_last_leaner(x)
#define reterr(x)           errno = (x);  \
                            return nullptr

typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;
typedef unsigned char Tag;


typedef struct node_s {
    Tag tag;
    struct node_s *north;
    struct node_s *west;
    struct leaf_s *east;
    int8 path[256];
} Node;

typedef struct leaf_s {
    Tag tag;
    union tree_u *west;
    struct leaf_s *east;
    int8 key[128];
    int8 *value;
    int16 size;
} Leaf;

typedef union tree_u {
    Node n;
    Leaf l;
} Tree;

