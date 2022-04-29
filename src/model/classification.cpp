//
// Created by radek on 20.03.19.
//
//we dont need #define NO_IMPORT_ARRAY ,because we initlize here python module (init_ar())
//additionaly each .cpp file using python module must have:#define PY_ARRAY_UNIQUE_SYMBOL pbcvt_ARRAY_API
//
#define PY_ARRAY_UNIQUE_SYMBOL pbcvt_ARRAY_API
#include "model/classification.h"
//#virtual environment: source ~/venv/bin/activate  && ./3DPointCloudClassification_GUI
// PyObject -> Vector
std::vector<float> MultiViewClassification::listTupleToVector_Float(PyObject* incoming) {
    std::vector<float> data;
    if (PyTuple_Check(incoming)) {
        for(Py_ssize_t i = 0; i < PyTuple_Size(incoming); i++) {
            PyObject *value = PyTuple_GetItem(incoming, i);
            data.push_back( PyFloat_AsDouble(value) );
        }
    } else {
        if (PyList_Check(incoming)) {
            for(Py_ssize_t i = 0; i < PyList_Size(incoming); i++) {
                PyObject *value = PyList_GetItem(incoming, i);
                data.push_back( PyFloat_AsDouble(value) );
            }
        } else {
            fprintf(stderr, "Passed PyObject pointer was not a list or tuple!\n");
        }
    }
    return data;
}
// Return the current Python error and backtrace as a string, or throw
// an exception if there was none.
std::string python_error_string() {
  using namespace boost::python;

  PyObject* ptype = nullptr;
  PyObject* pvalue = nullptr;
  PyObject* ptraceback = nullptr;

  // Fetch the exception information. If there was no error ptype will be set
  // to null. The other two values might set to null anyway.
  PyErr_Fetch(&ptype, &pvalue, &ptraceback);
  if (ptype == nullptr) {
      return "No error";
//    throw std::runtime_error("A Python error was detected but when we called "
//                             "PyErr_Fetch() it returned null indicating that "
//                             "there was no error.");
  }

  // Sometimes pvalue is not an instance of ptype. This converts it. It's
  // done lazily for performance reasons.
  PyErr_NormalizeException(&ptype, &pvalue, &ptraceback);
  if (ptraceback != nullptr) {
    PyException_SetTraceback(pvalue, ptraceback);
  }

  // Get Boost handles to the Python objects so we get an easier API.
  handle<> htype(ptype);
  handle<> hvalue(allow_null(pvalue));
  handle<> htraceback(allow_null(ptraceback));

  // Import the `traceback` module and use it to format the exception.
  object traceback = import("traceback");
  object format_exception = traceback.attr("format_exception");
  object formatted_list = format_exception(htype, hvalue, htraceback);
  object formatted = str("\n").join(formatted_list);
  return extract<std::string>(formatted);
}
bool MultiViewClassification::loadPythonModule(PyObject **module,const std::string &file,const std::string &func){
    

    if (file.empty() || func.empty() ) {
        fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
        return false;
    }
    //const wchar_t *argv[] = {L"python3", L"ModelTesting"};
    //PySys_SetArgv (1, (wchar_t **)argv);
    init_ar(); //initialization
    const wchar_t *argv[] = {L"python3", L"ModelTesting"};
    PySys_SetArgv (1, (wchar_t **)argv);
    //add to PYTHONPATH - solve "no module names ... found" problem (https://stackoverflow.com/questions/24492327/python-embedding-in-c-importerror-no-module-named-pyfunction)
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")");    //PyRun_SimpleString("sys.path.append(\"<some_path>\")");
    PyRun_SimpleString("sys.path.append(\"../embedded_python\")");// embedded modules must be one folder up from executon file
    //PyRun_SimpleString("sys.path.append(\'/home/radek/Projects/3DPointCloudClassification_GUI/embedded_python\')");


    //Error checking of pName left out //
    *module = PyImport_ImportModule(file.c_str());
    std::string errMsg=python_error_string();

    return (module!=NULL);
}
/**
 * @brief MultiViewClassification::classifyAndGetNNResponeVector
 * @param projection_vector
 * @param modelDirectory
 * @param numOfClasses
 * @return :vector:
 *          1st element -> class id - classification result for this object
 *          2nd - last element -> neural net response vector
 *
 */
std::vector<float> MultiViewClassification::classifyAndGetNNResponeVector(const std::vector<cv::Mat>& projection_vector, const std::string modelDirectory, int numOfClasses){
    std::string python_file="ModelTesting";
    std::string python_func="classify_multiple_projections_and_get_response_vector";//"testing";

    PyObject *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;
    PyObject *vecp, *modelDir, *nOfCla;
    if(!loadPythonModule(&pModule,python_file,python_func)){return {-1};}

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, python_func.c_str());
        //pFunc is a new reference
        //cv::Mat photo_cmat;
        //photo_cmat = cv::imread(path,0);
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(3);                      //number of python func. arguments// arguments must be passed as Tuple
            ///1 argument - projections///
            vecp = PyTuple_New(projection_vector.size()); //vector argument :we store here projections of single object: size = number of porjections
            for(int i=0; i<projection_vector.size();i++)
            {
                pValue = pbcvt::fromMatToNDArray(projection_vector[i]); //pValue = pbcvt::fromMatToNDArray(single_projection);

                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    Py_DECREF(vecp);
                    fprintf(stderr, "Cannot convert 1st argument\n");
                    return {-1};
                }

                PyTuple_SetItem(vecp, i, pValue); //assing array to tuple
            }
            PyTuple_SetItem(pArgs, 0, vecp);  //pass first argument
            /////////////////
            ////2 argument - trained model directory///
            modelDir=PyUnicode_FromString(modelDirectory.c_str());
            if (!modelDir) {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                fprintf(stderr, "Cannot convert 2nd argument\n");
                return {-1};
            }
            PyTuple_SetItem(pArgs,1,modelDir); //pass second argument
            /////////////////
            ////3 argument - number of classes (given in class mapping and on which the model was tranied///
            nOfCla = PyLong_FromLong(numOfClasses);
            if (!nOfCla) {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                fprintf(stderr, "Cannot convert 3rd argument\n");
                return {-1};
            }
            PyTuple_SetItem(pArgs,2,nOfCla);
            /////////////////

            pValue = PyObject_CallObject(pFunc, pArgs);  //returned value form function is stored here
            Py_DECREF(pArgs);
            Py_DECREF(vecp);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                return listTupleToVector_Float(pValue);
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return {-1};
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", python_func.c_str());
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        //PyErr_Print();
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);
        //pvalue contains error message
        //ptraceback contains stack snapshot and many other information
        //(see python traceback structure)

        //Get error message
        const char *pStrErrorMessage = PyUnicode_AsUTF8(PyObject_Str(pvalue));
        fprintf(stderr,"Py error = %s\n",pStrErrorMessage);
        fprintf(stderr, "Failed to load \"%s\"\n", python_file.c_str());
        return {-1};
    }
    Py_Finalize();
}
