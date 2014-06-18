#define N 26

void nse_assert(bool);
char nse_symbolic_char();

int main()
{
  char c = nse_symbolic_char();

  if ('A' < c)
    return 1;

  for (unsigned i = 0; i < 26; ++i)
  {
    if (c < 'Z')
      ++c;
  }

  nse_assert(c <= 'Z');
  return 0;
}
