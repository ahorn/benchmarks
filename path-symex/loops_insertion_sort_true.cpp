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
      while((i>=0)) {
         // cannot currently short-cut evaluate conjunctions
         // so we manually transformed the while condition
         if (v[i]<=key)
           break;

         v[i+1] = v[i];
         i = i - 1;
      }
      v[i+1] = key;	        
  }      
  for (k=1;k<SIZE;k++)
    nse_assert(v[k-1]<=v[k]);
   return 0;
}

