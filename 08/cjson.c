#define PY_SSIZE_T_CLEAN
#include <stdio.h>
#include <stdlib.h>

#include <Python.h>

//gcc -I/usr/include/python3.8/ -fPIC -shared -o cjson.so cjson.c

// PyObject *dict = NULL;
// if (!(dict = PyDict_New())) {
//     printf("ERROR: Failed to create Dict Object\n");
//     return NULL;
// }

// PyObject *key = NULL;
// PyObject *value = NULL;
// if (!(key = Py_BuildValue("s", "hello"))) {
//     printf("ERROR: Failed to build string value\n");
//     return NULL;
// }
// if (!(value = Py_BuildValue("i", 10))) {
//     printf("ERROR: Failed to build integer value\n");
//     return NULL;
// }
// if (PyDict_SetItem(dict, key, value) < 0) {
//     printf("ERROR: Failed to set item\n");
//     return NULL;
// }
// if (!(key = Py_BuildValue("s", "world"))) {
//     printf("ERROR: Failed to build string value\n");
//     return NULL;
// }
// if (!(value = Py_BuildValue("s", "100500"))) {
//     printf("ERROR: Failed to build string value\n");
//     return NULL;
// }
// if (PyDict_SetItem(dict, key, value) < 0) {
//     printf("ERROR: Failed to set item\n");
//     return NULL;
// }

// return dict;

static PyObject* cjson_dumps(PyObject* self, PyObject* args) {
    
    PyObject* dict;
    if (!PyArg_ParseTuple(args, "O", &dict)) 
    {
        return NULL;
    }
    if (!PyDict_Check(dict)) 
    {
        PyErr_SetString(PyExc_TypeError, "Expected dictionary");
        return NULL;
    }
    
    Py_ssize_t size = PyDict_Size(dict);
    if (size == 0) 
    {
        return PyUnicode_FromString("{}");
    }

    PyObject* jsonStr = PyUnicode_FromString("{");
    PyObject *key, *value;
    Py_ssize_t pos = 0;

    while (PyDict_Next(dict, &pos, &key, &value)) 
    {
        PyObject* jsonKey = NULL;
        if (PyUnicode_Check(key)) 
        {
            jsonKey = key;
        } 
        else if (PyBytes_Check(key)) 
        {
            jsonKey = PyUnicode_FromEncodedObject(key, "utf-8", NULL);
        } 
        else 
        {
            PyErr_SetString(PyExc_TypeError, "Dictionary keys must be strings");
            Py_DECREF(jsonStr);
            return NULL;
        }
        if (!PyUnicode_Check(value)) 
        {
            PyErr_SetString(PyExc_TypeError, "Dictionary values must be strings");
            Py_DECREF(jsonStr);
            Py_DECREF(jsonKey);
            return NULL;
        }
        
        PyObject* jsonValue = PyUnicode_FromFormat("\"%S\":\"%S\"", jsonKey, value);
        Py_DECREF(jsonKey);

        if (jsonValue == NULL) 
        {
            Py_DECREF(jsonStr);
            return NULL;
        }
        if (pos == 0) 
        {
            PyUnicode_Append(jsonStr, jsonValue);
        } 
        else 
        {
            PyUnicode_Append(jsonStr, PyUnicode_FromString(","));
            PyUnicode_Append(jsonStr, jsonValue);
        }
        Py_DECREF(jsonValue);
    }
    PyUnicode_Append(jsonStr, PyUnicode_FromString("}"));
    return jsonStr;
}



static PyObject* cjson_loads(PyObject* self, PyObject* args) {
    
    char* json_str;
    Py_ssize_t json_len;

    // Parse arguments
    if (!PyArg_ParseTuple(args, "s#", &json_str, &json_len)) {
        return NULL;
    }

    // Create a new Python dictionary object
    PyObject *py_dict = NULL;
	if (!(py_dict = PyDict_New())) {
	    printf("ERROR: Failed to create Dict Object\n");
	    return NULL;
	}

    // Parse the JSON string
    char* key = NULL;
    char* value = NULL;
    int in_key = 0;
    int in_value = 0;
    int in_quotes = 0;
    int i;

    for (i = 0; i < json_len; ++i) {
        char c = json_str[i];
        
        if (c == '{') 
        {
            continue;
        } 
        else if (c == '}') 
        {
            break;
        } 
        else if (c == ':') 
        {
            in_key = 0;
            in_value = 1;
            continue;
        } 
        else if (c == '"') 
        {
            if (in_quotes) 
            {
                in_quotes = 0;
                if (in_key) 
                {
                    key = PyUnicode_FromStringAndSize(key, strlen(key));
                    in_key = 0;
                    in_value = 1;
                } 
                else 
                {
                    value = PyUnicode_FromStringAndSize(value, strlen(value));
                    PyDict_SetItem(py_dict, key, value);
                    key = NULL;
                    value = NULL;
                    in_key = 1;
                    in_value = 0;
                }
            } 
            else 
            {
                in_quotes = 1;
            }
            continue;
        }
        if (in_key) 
        {
            if (key == NULL) 
            {
                key = malloc(sizeof(char));
                key[0] = c;
            } 
            else 
            {
                key = realloc(key, strlen(key) + 1);
                key[strlen(key)] = c;
            }
        } 
        else if (in_value) 
        {
            if (value == NULL) 
            {
                value = malloc(sizeof(char));
                value[0] = c;
            } 
            else 
            {
                value = realloc(value, strlen(value) + 1);
                value[strlen(value)] = c;
            }
        }
    }
    // Clean up memory
    if (key != NULL) free(key);
    if (value != NULL) free(value);

    // Return Python dictionary object
    return py_dict;
}



static PyMethodDef cjson_methods[] = {
    {"loads", cjson_loads, METH_VARARGS, "Load JSON string to Python dictionary."},
    {"dumps", cjson_dumps, METH_VARARGS, "Dump Python dictionary to JSON string."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef cjson_module = {
    PyModuleDef_HEAD_INIT,
    "cjson",
    "Example module that provides a function to load JSON string to Python dictionary.",
    -1,
    cjson_methods
};

PyMODINIT_FUNC PyInit_cjson(void) {
    return PyModule_Create(&cjson_module);
}


