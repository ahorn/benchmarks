// This file contains modified code snippets from "Algorithms in C,
// Third Edition, Parts 1-4," by Robert Sedgewick.
//
// See https://www.cs.princeton.edu/~rs/Algs3.c1-4/code.txt

#include <iostream>
#include <nse_sequential.h>

#include "report.h"

#ifdef FORCE_BRANCH
#define BRANCH_CALL force_branch
#else
#define BRANCH_CALL branch
#endif

typedef int Key;
typedef int Item;

#define eq(A, B) (!less(A, B) && !less(B, A))
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define NULLitem 0

struct STnode;

// Pointers are currently not instrumented on purpose
typedef struct STnode* link;

struct STnode {
  crv::Internal<Item> item;
  link l, r;
  crv::Internal<int> n;

  STnode(const crv::Internal<Item>& _item, link _l, link _r, const crv::Internal<int>& _n)
  : item(_item), l(_l), r(_r), n(_n) {}
};

static link head, z;

void STinit() {
  head = (z = new STnode(NULLitem, 0, 0, 0));
}

crv::Internal<int> STcount() { return head->n; }

static link insertR(link h, const crv::Internal<Item>& item) {
  crv::Internal<Key> v = key(item), t = key(h->item);
  if (h == z) return new STnode(item, z, z, 1);

  if (crv::sequential_dfs_checker().BRANCH_CALL(less(v, t)))
    h->l = insertR(h->l, item);
  else
    h->r = insertR(h->r, item);

  h->n = h->n + 1;
  return h;
}

void STinsert(const crv::Internal<Item>& item) { head = insertR(head, item); }

static void sortR(link h, void (*visit)(const crv::Internal<Item>&)) {
  if (h == z) return;
  sortR(h->l, visit);
  visit(h->item);
  sortR(h->r, visit);
}

void STsort(void (*visit)(const crv::Internal<Item>&)) { sortR(head, visit); }

static crv::Internal<Item[]> a;
static crv::Internal<unsigned> k;

void sorter(const crv::Internal<Item>& item) {
  a[k] = item;
  k = k+1;
}

#define N 7

// Unwind N+1 times
void crv_main() {
  STinit();

  for (crv::Internal<unsigned> i = 0; crv::sequential_dfs_checker().BRANCH_CALL(i < N); i = i+1) {
    STinsert(crv::any<Item>());
  }
  STsort(sorter);

  crv::sequential_dfs_checker().add_error(!(k == N));
  for (crv::Internal<unsigned> i = 0; crv::sequential_dfs_checker().BRANCH_CALL(i < N - 1); i = i+1)
    crv::sequential_dfs_checker().add_error(!(a[i] <= a[i+1]));
}

// leaks memory but OK for this benchmark
int main() {
  bool error = false;

  std::chrono::seconds seconds(std::chrono::seconds::zero());
  {
    smt::NonReentrantTimer<std::chrono::seconds> timer(seconds);

    do {
      k = 0;
      make_any(a);

      crv_main();

#ifndef FORCE_BRANCH
      error |= smt::sat == crv::sequential_dfs_checker().check();
#endif
    } while (crv::sequential_dfs_checker().find_next_path() && !error);
  }

  if (error)
    std::cout << "Found bug!" << std::endl;
  else
    std::cout << "Could not find any bugs." << std::endl;

  report_time(seconds);

  return error;
}
