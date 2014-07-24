#define MAX 5

char nse_symbolic_char();
void nse_assert(bool);

int main()
{
  char string_A[MAX];
  char string_B[MAX];
  int i, j, nc_A, nc_B;
  bool found; 
  
  for(i=0; i<MAX; i++)
    string_A[i]=nse_symbolic_char();    
  if(string_A[MAX-1]!='\0')
    return 1;

  for(i=0; i<MAX; i++)
    string_B[i]=nse_symbolic_char();    
  if(string_B[MAX-1]!='\0')
    return 1;

  nc_A = 0;
  while(string_A[nc_A]!='\0')
  {
    nc_A++;

    if (nc_A >= MAX)
      break;
  }

  nc_B = 0;
  while(string_B[nc_B]!='\0')
  {
    nc_B++;

    if (nc_B >= MAX)
      break;
  }

  if(nc_B < nc_A)
    return 1;
  
  nse_assert(nc_A < MAX && nc_B < MAX);

  i=j=0;
  while((i<nc_A) && (j<nc_B))
  {
    if(string_A[i] == string_B[j]) 
    {
       i++;
       j++;
    }   
    else
    {
       i = i-j+1;
       j = 0;
    }   
  } 

  found = (j>nc_B-1);
  
  nse_assert(found || !found);
  return 0;
}

