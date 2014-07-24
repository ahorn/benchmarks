typedef unsigned int uint;
uint nse_symbolic_uint();
void nse_assert(bool);

uint SIZE;

bool linear_search(int *a, uint n, int q) {
  uint j=0;
  while (j<n && a[j]!=q) {
  j++;
  if (j==20) j=-1;
  }
  if (j<SIZE) return true;
  else return false;
}

int array[5];

int main() { 
  SIZE = nse_symbolic_uint();

  // may cause the array to be unbounded (no overflow
  // detection needed for assertion violation below)
  int *a = array;

  a[SIZE/2]=3;
  nse_assert(linear_search(a,SIZE,3));

  return 0;
}
