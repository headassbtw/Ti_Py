struct SDL{
    static void Present();
    static void Present(const char* message);
    static void Clear();
    static void Dot(float x, float y, const char* mark);
};