int nse_symbolic_int();

typedef unsigned int uint;
void nse_assert(bool);

#define M 20

int main()
{
  // separate array definitions to facilitate
  // source-to-source transformation
  int A[M];
  int B[M];
  int C[M];

  uint i;
  
  for(i=0;i<M;i++)
    A[i] = nse_symbolic_int();
  
  for(i=0;i<M;i++)
    B[i] = nse_symbolic_int();

  for(i=0;i<M;i++)
     C[i]=A[i]+B[i];
  
  for(i=0;i<M;i++)
     nse_assert(C[i]==A[i]+B[i]);

  return 0;
}

