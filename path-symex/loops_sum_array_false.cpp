int nse_symbolic_int(void);

typedef unsigned int uint;
uint nse_symbolic_uint();

void nse_assert(bool);

#define M 5

int main()
{
  // separate array declarations to facilitate
  // source-to-source transformation for now
  int A[M];
  int B[M];
  int C[M];

  uint  i;
  
  for(i=0;i<M;i++)
    A[i] = nse_symbolic_int();
  
  for(i=0;i<M;i++)
    B[i] = nse_symbolic_int();

  for(i=0;i<M;i++)
     C[i]=A[i]+B[i];
  
  for(i=0;i<M;i++)
     nse_assert(C[i]==A[i]-B[i]);

  return 0;
}

