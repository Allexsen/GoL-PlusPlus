#pragma once

class Pack {
public:
    Pack(int size = 0);

    int GetSize() const { return size_; }
    void AddMember() { size_++; } 
    void RemoveMember() { size_--; }

private:
    int size_;
};
