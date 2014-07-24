#define MAX 5

typedef unsigned int uint;
char nse_symbolic_char();
void nse_assert(bool);

int main()
{
  // separate declarations to facilitate source-to-source transformation
  char input_string[MAX];
  char vogal_array[]={'a','A','e','E','i','I','o','O','u','U','\0'};

  uint  i,j,cont, tam_string, n_caracter;

  for(i=0;i<MAX;i++)
    input_string[i] = nse_symbolic_char();

  if (input_string[MAX-1]!='\0')
    return 1;
  
  n_caracter = 0;
  while(input_string[n_caracter]!='\0')
    n_caracter++;

  cont = 0;
  for(i=0;i<n_caracter;i++)
     for(j=0;j<MAX/2;j++)
        if(input_string[i] == vogal_array[j])
           cont++;
           
  i=0;
  int cont_aux = 0;
  while(input_string[i]!='\0')
  {
    for(j=0;j<MAX/2;j++)
    {
        if(input_string[i] == vogal_array[j])
           cont_aux++;
    }       
    i++;       

    if (i>=MAX) break;
  }    
  nse_assert(cont_aux==cont);
  return 0;
}

