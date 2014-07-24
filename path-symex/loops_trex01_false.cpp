int nse_symbolic_int();
void nse_assert(bool);

void f(int d) {
  int x, y, k, z = 1;
  L1:
  while (z < k) { z = 2 * z; }
  nse_assert(z>=2);
  L2:
  while (x > 0 && y > 0) {
    bool c;
    if (c) {
      P1:
      x = x - d;
      y = nse_symbolic_int();
      if (y < 0 || y > 1)
        return;
      z = z - 1;
    } else {
      y = y - d;
    }
  }
}

int main() {
  bool c;
  if (c) {
    f(1);
  } else {
    f(2);
  }
  return 0;
}


