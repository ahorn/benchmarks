int FAKE_INFINITY = 899;

int nse_symbolic_int();
void nse_assert(bool);

int main(){
  int nodecount = nse_symbolic_int();
  int edgecount = nse_symbolic_int();

  if (0 > nodecount || nodecount > 4 || 0 > edgecount || edgecount > 19)
    return 1;

  int source = 0;
  int Source[20] = {0,4,1,1,0,0,1,3,4,4,2,2,3,0,0,3,1,2,2,3};
  int Dest[20] = {1,3,4,1,1,4,3,4,3,0,0,0,0,2,3,0,2,1,0,4};
  int Weight[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
  int distance[5];
  int x,y;
  int i,j;
  
  for(i = 0; i < nodecount; i++){
    if(i == source){
      distance[i] = 0;
    }
    else {
      distance[i] = FAKE_INFINITY;
    }
  }

  for(i = 0; i < nodecount; i++)
    {
      for(j = 0; j < edgecount; j++)
	{
	  x = Dest[j];
	  y = Source[j];
	  if(distance[x] > distance[y] + Weight[j])
	    {
	      distance[x] = -1;
	    }
	}
    }
  for(i = 0; i < edgecount; i++)
    {
      x = Dest[i];
      y = Source[i];
      if(distance[x] > distance[y] + Weight[i])
	{
	  return 1;
	}
    }

  for(i = 0; i < nodecount; i++)
    {
      nse_assert(distance[i]>=0);
    }

  return 0;
}

