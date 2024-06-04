int sum(int a, int b) {
    for (int i = 0; i < 10; i++) {
        a += a;
    }
    for (int i = 0; i < 10; i++) {
        if (a > b) {
            a = b - 1;
        }
        if (a > b) {
            a += 1;
        }       
    }
    return a + b;
}
