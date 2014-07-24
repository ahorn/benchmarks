typedef unsigned int uint;

int nse_symbolic_int();
void nse_assert(bool);

#define SIZE 15
int main()
{
  uint j,k;
  int array[SIZE];
  int menor;
  
  menor = nse_symbolic_int();

  for(j=0;j<SIZE;j++) {
       array[j] = nse_symbolic_int();
       
       if(array[j]<=menor)
          menor = array[j];                          
    }                       
    
    nse_assert(array[0]>menor);

  return 0;
}

