
int main() {
    int x;
    x = 4;
    {
        int x;
        x = 5;
    }
    print(x);
}