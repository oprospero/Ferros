#include "Python.h"
#include "arducam.h"


// static PyObject *
// int py_arducam(PyObject *self, PyObject *args)
// {
//     PyObject *pyModel;
//     int SPI_CS1;
//     int SPI_CS2;
//     int SPI_CS3;
//     int SPI_CS4;

//     if (
//         !PyArg_ParseTuple(
//             args,
//             "Oiiii", 
//             pyModel,
//             &SPI_CS1,
//             &SPI_CS2,
//             &SPI_CS3,
//             &SPI_CS4
//         )
//         )
//         return NULL;
//     int result = arducam(
//         sensor_model_t model,
//         int SPI_CS1,
//         int SPI_CS2,
//         int SPI_CS3,
//         int SPI_CS4
//     );
// }

static PyObject *
void py_arducam_init(PyObject *self, PyObject *args)
{

    py_arducam_init();
    Py_RETURN_NONE;
}

/*
static PyObject *
void py_arducam_flush_fifo(PyObject *self, PyObject *args)
{
    int SPI_CS;
    if (!PyArg_ParseTuple(args, "i", SPI_CS))
        return NULL;
    py_arducam_flush_fifo(int SPI_CS);
    Py_RETURN_NONE;
}

static PyObject *
void py_arducam_start_capture(PyObject *self, PyObject *args)
{
    int SPI_CS;
    if (!PyArg_ParseTuple(args, "i", SPI_CS))
        return NULL;
    arducam_start_capture(int SPI_CS);
    
    Py_RETURN_NONE;
}

static PyObject *
void py_arducam_clear_fifo_flag(PyObject *self, PyObject *args)
{
    int SPI_CS;
    if (!PyArg_ParseTuple(args, "i", SPI_CS))
        return NULL;
    arducam_clear_fifo_flag(int SPI_CS);
    Py_RETURN_NONE;
}

static PyObject *
uint8_t py_arducam_read_fifo(PyObject *self, PyObject *args)
{
    int SPI_CS;
    if (!PyArg_ParseTuple(args, "i", SPI_CS))
        return NULL;
    uint8_t result = arducam_read_fifo(SPI_CS);
}

static PyObject *
uint8_t py_arducam_burst_read_fifo(PyObject *self, PyObject *args)
{
    uint8_t result = arducam_burst_read_fifo();
}

static PyObject *
void py_set_fifo_burst(PyObject *self, PyObject *args)
{
    char data;
    if (!PyArg_ParseTuple(args, "i", &char))
        return NULL;
    set_fifo_burst((uint8_t) data);
    Py_RETURN_NONE;
}

static PyObject *
void py_arducam_transfers(PyObject *self, PyObject *args)
{
    arducam_transfers(uint8_t *buf, uint32_t size);
    Py_RETURN_NONE;
}


static PyObject *
uint8_t py_arducam_read_reg(PyObject *self, PyObject *args)
{
    
    uint32_t result = arducam_read_reg(uint8_t addr, int SPI_CS);
}


static PyObject *
void py_arducam_write_reg(PyObject *self, PyObject *args)
{
    arducam_write_reg(uint8_t addr, uint8_t data, int SPI_CS);
    Py_RETURN_NONE;
}

static PyObject *
void py_arducam_transfer(PyObject *self, PyObject *args)
{
    arducam_transfer(uint8_t data);
    Py_RETURN_NONE;
}

static PyObject *
uint32_t py_read_fifo_length(PyObject *self, PyObject *args)
{
    uint32_t result = py_read_fifo_length(int SPI_CS);

}

static PyObject *
void py_arducam_set_jpeg_size(PyObject *self, PyObject *args)
{
    arducam_set_jpeg_size(jpeg_size_t size);
    Py_RETURN_NONE;
}

static PyObject *
void py_arducam_set_format(PyObject *self, PyObject *args)
{
    arducam_set_format(image_format_t fmt);
    Py_RETURN_NONE;
}

static PyObject *
void py_arducam_OV5642_set_jpeg_size(PyObject *self, PyObject *args)
{
    arducam_OV5642_set_jpeg_size(jpeg_size_t size);
    Py_RETURN_NONE;
}


static PyObject *
void py_set_bit(PyObject *self, PyObject *args)
{
    set_bit(uint8_t addr, uint8_t bit, int SPI_CS);
    Py_RETURN_NONE;
}

static PyObject *
void py_clear_bit(PyObject *self, PyObject *args)
{
    clear_bit(uint8_t addr, uint8_t bit, int SPI_CS);
    Py_RETURN_NONE;
}

*/


// Methods table
static PyMethodDef arducam_methods[] = {
    /* The cast of the function is necessary since PyCFunction values
     * only take two PyObject* parameters, and keywdarg_parrot() takes
     * three.
     */
    {"arducam_init", (PyCFunction)py_arducam_init, METH_NOARGS,
     "ArduCam Initization"},
    {NULL, NULL, 0, NULL}   /* sentinel */
};

//Module definition
static struct PyModuleDef arducammodule = {
    PyModuleDef_HEAD_INIT,
    "ArduCam",
    NULL,
    -1,
    arducam_methods
};

PyMODINIT_FUNC
PyInit_arducam(PyObject *self, PyObject *args)
{
    return PyModule_Create(&arducammodule);
}