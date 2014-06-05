// This file contains modified code snippets from "Algorithms in C, Third Edition,
// Parts 1-4," by Robert Sedgewick. The code is intentionally buggy!
//
// For the correct code, see https://www.cs.princeton.edu/~rs/Algs3.c1-4/code.txt

#define N 7

typedef int Key;
typedef int Item;

void nse_make_symbolic(void*);
void nse_assert(bool);
Item nse_symbolic_item();

#define eq(A, B) (!less(A, B) && !less(B, A))
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define NULLitem 0

struct STnode;
typedef struct STnode* link;

struct STnode {
  Item item;
  link l, r;
  int n;

  // We remark that structs in C99 can be initialized with
  // designated initializers, something that is not defined
  // in C++ (at least in the year 2014). We could use C++11's
  // initializer lists feature but there arguments remain
  // unnamed. So we opt for a regular constructor which has
  // the benefit that it works with older versions of C++.
  STnode(Item _item, link _l, link _r, int _n)
  : item(_item), l(_l), r(_r), n(_n) {}
};

static link head, z;

void STinit() {
  head = (z = new STnode(NULLitem, 0, 0, 0));
}

int STcount() { return head->n; }

static link insertR(link h, Item item) {
  Key v = key(item), t = key(h->item);
  if (h == z) return new STnode(item, z, z, 1);

  if (less(v, t))
    h->l = insertR(h->r, item);
    //                ^ bug due to wrong variable (it should be l)
  else
    h->r = insertR(h->r, item);

  (h->n)++; return h;
}

void STinsert(Item item) { head = insertR(head, item); }

static void sortR(link h, void (*visit)(Item)) {
  if (h == z) return;
  sortR(h->l, visit);
  visit(h->item);
  sortR(h->r, visit);
}

void STsort(void (*visit)(Item)) { sortR(head, visit); }

static Item a[N];
static unsigned k = 0;
void sorter(Item item) {
  a[k++] = item;
}

// It suffices to unwind N+1 times where N > 2
int main() {
  STinit();
  nse_make_symbolic(a);

  for (unsigned i = 0; i < N; i++) {
    STinsert(nse_symbolic_item());
  }
  STsort(sorter);

  nse_assert(k == N);
  for (unsigned i = 0; i < N - 1; i++)
    nse_assert(a[i] <= a[i+1]);

  return 0;
}
