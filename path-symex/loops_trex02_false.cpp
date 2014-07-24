int nse_symbolic_int();
void nse_assert(bool);

//x is an input variable
int x;

void foo() {
  x--;
}

int main() {
  x=nse_symbolic_int();
  while (x > 0) {
    bool c;
    if(c) foo();
    else foo();
  }
  nse_assert(x==0);
  return 0;
}

