struct SDL{
    static void Present();
    static void Present(const char* message);
    static void Clear();
    static void Dot(int x, int y, const char* mark);
};