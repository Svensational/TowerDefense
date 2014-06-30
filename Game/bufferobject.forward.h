#ifndef BUFFEROBJECT_FORWARD_H
#define BUFFEROBJECT_FORWARD_H

class BufferObject;

// ARRAY_BUFFER
template <typename T> class VertexBufferObject;
template <typename T> using VBO = VertexBufferObject<T>;

// ELEMENT_ARRAY_BUFFER
template <typename T> class IndexBufferObject;
template <typename T> using IBO = IndexBufferObject<T>;
using IBOub = IndexBufferObject<unsigned char>;
using IBOus = IndexBufferObject<unsigned short>;
using IBOui = IndexBufferObject<unsigned int>;

#endif // BUFFEROBJECT_FORWARD_H
