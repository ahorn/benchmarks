char nse_symbolic_char();
void nse_assert(bool);

#define MAX 5

int main() {
    char str1[MAX];
    char str2[MAX];
    int i, j;

    for (i=0; i<MAX; i++) {
        str1[i]=nse_symbolic_char();
    }

    str1[MAX-1]= '\0';

    j = 0;
   
    for (i = MAX - 1; i >= 0; i--) {
        str2[j] = str1[i];
        j++;
    }

    j = MAX-1;
    for (i=0; i<MAX; i++) {
      nse_assert(str1[i] == str2[j]);
      j--;
    }   

    return 0;
}

