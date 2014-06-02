// This file contains modified code snippets from "Algorithms in C, Third Edition,
// Parts 1-4," by Robert Sedgewick. The code is intentionally buggy!
//
// For the correct code, see https://www.cs.princeton.edu/~rs/Algs3.c1-4/code.txt

#include <iostream>
#include <nse_sequential.h>
#include <nse_report.h>

#ifndef dfs_checker
#define dfs_checker crv::backtrack_dfs_checker
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

  if (dfs_checker().branch(less(v, t)))
    h->l = insertR(h->r, item);
    //                ^ bug due to wrong variable (it should be l)
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

// It suffices to unwind N+1 times where N > 2
void crv_main() {
  STinit();

  for (crv::Internal<unsigned> i = 0; dfs_checker().branch(i < N); i = i+1) {
    STinsert(crv::any<Item>());
  }
  STsort(sorter);

  dfs_checker().add_error(!(k == N));
  for (crv::Internal<unsigned> i = 0; dfs_checker().branch(i < N - 1); i = i+1)
    dfs_checker().add_error(!(a[i] <= a[i+1]));
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

      error |= smt::sat == dfs_checker().check();
    } while (dfs_checker().find_next_path() && !error);
  }

  if (error)
    std::cout << "Found bug!" << std::endl;
  else
    std::cout << "Could not find any bugs." << std::endl;

  report_statistics(dfs_checker().solver().stats(), dfs_checker().stats(), seconds);

  return error;
}
