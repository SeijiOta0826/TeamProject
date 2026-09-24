#pragma once

class Cursor
{
public:
    Cursor();
    ~Cursor();

    void Initialize();
    void Update();
    void Draw();
    void Finalize();

private:
    int mHandle = -1;
};