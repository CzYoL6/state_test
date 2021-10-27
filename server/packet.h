#pragma once
#include "circle_buffer.hpp"
#include "message.pb.h"
class Packet {
  public:
    Packet(Update::TYPE type);
    ~Packet();

    void AddVal(char *val, int size);

    void ReadVal(char *val, int size, bool peek);

    int InsertLengthInFront();

    int GetAllLength() const;

    CircleBuffer<char> *GetCircleBuffer() const;

  private:
    CircleBuffer<char> *m_buffer{nullptr};
    Update::TYPE m_type;
};