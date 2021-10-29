#include "packet.h"

Packet::Packet(Update::TYPE type) {
    m_type = type;
    m_buffer = new CircleBuffer<char>(1024 * 2);
    m_buffer->Write(reinterpret_cast<char *>(&type), sizeof(type));
}

Packet::~Packet() {
    if (m_buffer != nullptr) {
        delete m_buffer;
        m_buffer = nullptr;
    }
}

int Packet::InsertLengthInFront() {
    int length = m_buffer->GetLength();
    CircleBuffer<char> *newBuffer = new CircleBuffer<char>(2048);
    newBuffer->Write(reinterpret_cast<char *>(&length), sizeof(length));
    newBuffer->Write(m_buffer->GetBuffer(), m_buffer->GetLength());
    if (m_buffer != nullptr)
        delete m_buffer;
    m_buffer = newBuffer;
    return length;
}

int Packet::GetAllLength() const {
    return m_buffer->GetLength();
}

void Packet::AddVal(char *val, int size) {
    m_buffer->Write(val, size);
}

void Packet::ReadVal(char *val, int size, bool peek = false) {
    m_buffer->Read(val, size, peek);
}

CircleBuffer<char> *Packet::GetCircleBuffer() const {
    return m_buffer;
}