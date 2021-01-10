
[[nodiscard]] 
int func(){
    return 1;
}

int func(int a, [[maybe_unused]] int b, int c) {
    int d;
    return ++a;
}

int main( int argc, char** argv ) {
    int a;
    [[maybe_unused]] int b;
    func();
    return func(argc, 1, 2);
}
