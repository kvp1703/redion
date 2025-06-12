#include "tree.h"

Tree root = {
    .n = {
        .tag = (TagRoot | TagNode),
        .north = (Node *) &root,
        .west = 0,
        .east = 0,
        .path = "/"
    }
};

void clear_buffer(int8 *str, int16 size) {
    int8 *p;
    int16 i;

    for (i = 0, p=str; i < size; p++, i++)
        *p = 0;

    return;
}

Node *create_node(Node *parent, int8 *path)
{
    assert(parent);

    Node *n;
    int16 size;
    errno = NoError;

    size = sizeof(struct node_s);
    n = (Node *) malloc((int)size);
    clear_buffer((int8 *) n, size);

    parent->west = n;
    n->tag = TagNode;
    n->north = parent;
    strncpy((char *)n->path, (char *)path, 255);

    return n;
}

Leaf * find_last_leaner(Node *parent)
{
    Leaf *l;
    errno = NoError;

    assert(parent);

    if(!parent->east)
        reterr(NoError);

    for (l = parent->east; l->east; l = l->east);
    assert(l);

    return l;
}

Leaf *create_leaf(Node *parent, int8 *key, int8 *value, int16 count)
{
    Leaf *l, *new;
    int16 size;

    assert(parent);

    l = find_last(parent);

    size = sizeof(struct leaf_s);
    new = (Leaf *) malloc(size);
    assert(new);

    if (!l)
        parent->east = new;
    else
        l->east = new;

    clear_buffer((int8 *) new, size);
    new->tag = TagLeaf;
    new->west = (!l) ? (Tree *) parent : (Tree *) l;

    strncpy((char *)new->key, (char *)key, 127);
    new->value = (int8 *) malloc(count);
    assert(new->value);
    clear_buffer(new->value, count);
    strncpy((char *)new->value, (char *)value, count);
    new->size = count;

    return new;
}

int main() {
    Node *n, *n2;
    Leaf *l1, *l2;

    int8 *key, *value;
    int16 size;

    n = create_node((Node *) &root, (int8 *) "/Users");
    assert(n);
    n2 = create_node(n, (int8 *) "/Users/login");
    assert(n2);

    key = (int8 *) "Kshitij";
    value = (int8 *) "kvp1703";
    size = (int16) strlen((char *)value);
    l1 = create_leaf(n2, key, value, size);
    assert(l1);

    printf("%s\n", l1->value);

    printf("%p, %p", (void *) n, (void *) n2);
    return 0;
}