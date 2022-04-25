//USE ONLY IN Qt projects (solves problem:
//" /usr/include/python3.6m/object.h:448:23: error: expected unqualified-id before ‘;’ token 
//PyType_Slot *slots; /* terminated by slot==0. */"
//more info: https://stackoverflow.com/questions/23068700/embedding-python3-in-qt-5
//USAGE: In Qt project replace every "#include <Python.h>" with "include <Python_wrapper.h>" 
#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")
