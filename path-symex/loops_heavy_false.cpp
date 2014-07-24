void nse_assert(bool);

// originally N was 1024^2
#define N 512

int main()
{
        // we use long to avoid casts in array[j] + array[k]
        // due to integral promotion of char type
	long array[N];

	int a = 1, i, j, k;

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			for (k = 0; k < N; k++)
				array[i] = array[j] + array[k];

	nse_assert(a == 0);
	return 1;
}
