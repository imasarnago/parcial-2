#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    size_t size;
    struct s_node *pq;
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
    unsigned int prioridad;
};

static struct s_node *create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);

    new_node->elem = e;
    new_node->next = NULL;
    new_node->prioridad = priority;

   
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node) {
    assert(node != NULL);
    

    node->next =NULL;
    free (node);
    node = NULL;

    return NULL;
}


static bool invrep(pqueue q) {
    bool b = true;
    struct s_node *actual = q->pq;
    while (actual != NULL && actual->next != NULL && b) {
        b = (actual->prioridad <= actual->next->prioridad);
        actual = actual->next;
    }
    return b;
}

pqueue pqueue_empty(void) {
    pqueue q = malloc (sizeof(struct s_pqueue));

    q->pq =  NULL;
    q->size = 0;
    

    assert(invrep(q));
    
    return q;
}

/* pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);


   if (q->pq == NULL) {
        q->pq = new_node;
    }
    else {
        if (q->pq->prioridad > priority) {
            new_node->next = q->pq;
            new_node->elem = e;
            new_node->prioridad = priority;
        }
        struct s_node *p = q->pq;
        while (p->next != NULL) {
        p = p->next;
        }
        p->next = new_node;
    }
    q->size++;
    assert (invrep(q) && !pqueue_is_empty(q));


    return q;
} */


pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));

    struct s_node *new_node = create_node(e, priority);

    if (q->pq == NULL || q->pq->prioridad > priority) {
        new_node->next = q->pq;
        q->pq = new_node;
    } else {
        struct s_node *p = q->pq;
        while (p->next != NULL && p->next->prioridad <= priority) {
            p = p->next;
        }
        p->next = new_node;
        new_node->next = p->next;   
    }

    q->size++;
    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}




bool pqueue_is_empty(pqueue q) {
    bool b = (q->pq == NULL);
    assert(invrep(q)); 
    return b;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(!pqueue_is_empty(q)); 
    struct s_node *p = q->pq;
    pqueue_elem elementoM = p->elem;
    assert(invrep(q));
    return elementoM;
}

unsigned int pqueue_peek_priority(pqueue q) {
    assert(!pqueue_is_empty(q)); 
    struct s_node *p = q->pq;
    unsigned int may_valor = p->prioridad; 
    assert(invrep(q));
    return may_valor;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    unsigned int size=0;
    
    size = q->size;
    assert(invrep(q));
    return size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep);

    struct s_node *matame=q->pq;
    q->pq = q->pq->next;
    matame = destroy_node(matame);
    q->size--;

    assert(invrep(q));
    return q;
}


pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *node=q->pq;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    return q;
}