
int main() {
    int x;
    {
        int y;
        y = 3;
    }
    {
        y = 6;
    }
    print(y);
}