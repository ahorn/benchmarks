void nse_assert(bool);

int main(){
   int a[5];
   int len=0;
   int i;


  for(i=0; i<5; ++i) {
     
      if (len==4)
         len =0;
      
      a[len]=0;

      len++;
   }
   nse_assert(len==5);
   return 1;

   
}
