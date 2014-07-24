typedef unsigned int uint;
uint nse_symbolic_uint();
void nse_assert(bool);

#define SIZE 8

int main() {
   int i, j, k, key;
   int v[SIZE];   
   for (j=1;j<SIZE;j++) {	  
      key = v[j];
      i = j - 1;
      while((i>=0) && (v[i]>key)) {
         if (i<2)
         v[i+1] = v[i];
         i = i - 1;
      }
      v[i+1] = key;	        
  }      
  for (k=1;k<SIZE;k++)
    nse_assert(v[k-1]<=v[k]);

   return 0;
}
