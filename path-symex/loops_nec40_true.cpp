int nse_symbolic_int();
void nse_assert(bool);

  // array declarations need to be on separate
  // lines for now
  char x[100];
  char y[100];

  int i,j,k;

int main() {  
  k = nse_symbolic_int();
  
  i = 0;
  while(x[i] != 0){
    y[i] = x[i];
    i++;
  }
  y[i] = 0;
  
  if(k >= 0 && k < i)
    nse_assert(y[k] == 0);

  return 0;
}
