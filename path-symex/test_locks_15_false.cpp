int nse_symbolic_int();
void nse_assert(bool);

int main()
{
    int p1 = nse_symbolic_int();  // condition variable
    int lk1; // lock variable

    int p2 = nse_symbolic_int();  // condition variable
    int lk2; // lock variable

    int p3 = nse_symbolic_int();  // condition variable
    int lk3; // lock variable

    int p4 = nse_symbolic_int();  // condition variable
    int lk4; // lock variable

    int p5 = nse_symbolic_int();  // condition variable
    int lk5; // lock variable

    int p6 = nse_symbolic_int();  // condition variable
    int lk6; // lock variable

    int p7 = nse_symbolic_int();  // condition variable
    int lk7; // lock variable

    int p8 = nse_symbolic_int();  // condition variable
    int lk8; // lock variable

    int p9 = nse_symbolic_int();  // condition variable
    int lk9; // lock variable

    int p10 = nse_symbolic_int();  // condition variable
    int lk10; // lock variable

    int p11 = nse_symbolic_int();  // condition variable
    int lk11; // lock variable

    int p12 = nse_symbolic_int();  // condition variable
    int lk12; // lock variable

    int p13 = nse_symbolic_int();  // condition variable
    int lk13; // lock variable

    int p14 = nse_symbolic_int();  // condition variable
    int lk14; // lock variable

    int p15 = nse_symbolic_int();  // condition variable
    int lk15; // lock variable


    int cond;

    for(int i = 0; i < 30; ++i) {
        cond = nse_symbolic_int();
        if (cond == 0) {
            goto out;
        } else {}
        lk1 = 0; // initially lock is open

        lk2 = 0; // initially lock is open

        lk3 = 0; // initially lock is open

        lk4 = 0; // initially lock is open

        lk5 = 0; // initially lock is open

        lk6 = 0; // initially lock is open

        lk7 = 0; // initially lock is open

        lk8 = 0; // initially lock is open

        lk9 = 0; // initially lock is open

        lk10 = 0; // initially lock is open

        lk11 = 0; // initially lock is open

        lk12 = 0; // initially lock is open

        lk13 = 0; // initially lock is open

        lk14 = 0; // initially lock is open

        lk15 = 0; // initially lock is open


    // lock phase
        if (p1 != 0) {
            lk1 = 1; // acquire lock
        } else {}

        if (p2 != 0) {
            lk2 = 1; // acquire lock
        } else {}

        if (p3 != 0) {
            lk3 = 1; // acquire lock
        } else {}

        if (p4 != 0) {
            lk4 = 1; // acquire lock
        } else {}

        if (p5 != 0) {
            lk5 = 1; // acquire lock
        } else {}

        if (p6 != 0) {
            lk6 = 1; // acquire lock
        } else {}

        if (p7 != 0) {
            lk7 = 1; // acquire lock
        } else {}

        if (p8 != 0) {
            lk8 = 1; // acquire lock
        } else {}

        if (p9 != 0) {
            lk9 = 1; // acquire lock
        } else {}

        if (p10 != 0) {
            lk10 = 1; // acquire lock
        } else {}

        if (p11 != 0) {
            lk11 = 1; // acquire lock
        } else {}

        if (p12 != 0) {
            lk12 = 1; // acquire lock
        } else {}

        if (p13 != 0) {
            lk13 = 1; // acquire lock
        } else {}

        if (p14 != 0) {
            lk14 = 1; // acquire lock
        } else {}

        if (p15 != 0) {
            lk15 = 1; // acquire lock
        } else {}


    // unlock phase
        if (p1 != 0) {
            nse_assert(!(lk1 != 1)); // assertion failure
            lk1 = 0;
        } else {}

        nse_assert(p2 != 0);

        if (p2 != 0) {
            nse_assert(!(lk2 != 1)); // assertion failure
            lk2 = 0;
        }

        if (p3 != 0) {
            nse_assert(!(lk3 != 1)); // assertion failure
            lk3 = 0;
        } else {}

        if (p4 != 0) {
            nse_assert(!(lk4 != 1)); // assertion failure
            lk4 = 0;
        } else {}

        if (p5 != 0) {
            nse_assert(!(lk5 != 1)); // assertion failure
            lk5 = 0;
        } else {}

        if (p6 != 0) {
            nse_assert(!(lk6 != 1)); // assertion failure
            lk6 = 0;
        } else {}

        if (p7 != 0) {
            nse_assert(!(lk7 != 1)); // assertion failure
            lk7 = 0;
        } else {}

        if (p8 != 0) {
            nse_assert(!(lk8 != 1)); // assertion failure
            lk8 = 0;
        } else {}

        if (p9 != 0) {
            nse_assert(!(lk9 != 1)); // assertion failure
            lk9 = 0;
        } else {}

        if (p10 != 0) {
            nse_assert(!(lk10 != 1)); // assertion failure
            lk10 = 0;
        } else {}

        if (p11 != 0) {
            nse_assert(!(lk11 != 1)); // assertion failure
            lk11 = 0;
        } else {}

        if (p12 != 0) {
            nse_assert(!(lk12 != 1)); // assertion failure
            lk12 = 0;
        } else {}

        if (p13 != 0) {
            nse_assert(!(lk13 != 1)); // assertion failure
            lk13 = 0;
        } else {}

        nse_assert(p14 != 0);

        if (p14 != 0) {
            nse_assert(!(lk14 != 1)); // assertion failure
            lk14 = 0;
        }

        if (p15 != 0) {
            nse_assert(!(lk15 != 1)); // assertion failure
            lk15 = 0;
        } else {}

    }
  out:
    return 0;
}

