
int main() {
    int x, y, z;
    x = 3;
    y = z = 6;
    if (x == y)
        z = 4;
    else if (x <= y)
        z = 1;
    else { z = 0; }
    print(z);
}