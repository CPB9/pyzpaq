#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include "zpaq/libzpaq.h"
#include <queue>
#include <iostream>
#include <stdexcept>

void libzpaq::error(const char* msg)
{
    std::cout << msg << std::endl;
    throw std::runtime_error(msg);
}

class In: public libzpaq::Reader
{
public:
    In(const uint8_t* data, size_t size) : _data(data), _size(size), _offset(0) {}
    int get()
    {
        if(_offset >= _size)
            return -1;
        return (int)_data[_offset++];
    }
private:
    const uint8_t* _data;
    size_t _size;
    size_t _offset;
};

class Out: public libzpaq::Writer
{
public:
    void put(int c)
    {
        _data.push_back(c);
    }
    std::vector<uint8_t> data() const { return _data; }
private:
    std::vector<uint8_t>_data;
};

static PyObject* compress(PyObject *self, PyObject *args)
{
    Py_buffer input_buffer;
    if(!PyArg_ParseTuple(args, "s*", &input_buffer))
        return NULL;
    In in((const uint8_t*)input_buffer.buf, input_buffer.len);
    Out out;
    libzpaq::compress(&in, &out, "5");
    return PyBytes_FromStringAndSize((const char*)out.data().data(), out.data().size());
}

static PyObject* decompress(PyObject *self, PyObject *args)
{
    Py_buffer input_buffer;
    if(!PyArg_ParseTuple(args, "s*", &input_buffer))
        return NULL;
    In in((const uint8_t*)input_buffer.buf, input_buffer.len);
    Out out;
    libzpaq::decompress(&in, &out);
    return PyBytes_FromStringAndSize((const char*)out.data().data(), out.data().size());
}

static PyMethodDef zpaq_methods[] = {
    {"compress", compress, METH_VARARGS, ""},
    {"decompress", decompress, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL},
};

static struct PyModuleDef zpaq_definition = {
    PyModuleDef_HEAD_INIT,
    "",
    "",
    -1,
    zpaq_methods,
};

PyMODINIT_FUNC PyInit_zpaq(void) {
  Py_Initialize();
  PyObject *m = PyModule_Create(&zpaq_definition);

  return m;
}