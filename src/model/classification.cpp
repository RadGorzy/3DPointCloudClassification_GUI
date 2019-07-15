//
// Created by radek on 20.03.19.
//
//->?DO PYTHON EMBEDDING
//tu juz nie ma #define NO_IMPORT_ARRAY , bo tu (w tym pliku zrodlowym) inicjalizuje modul pythona (init_ar()) -> w kazdym pozostalym compilation unit (pliku .cpp z zalocznomymi naglowkami #include ...h) uzywajacego modulu pythona juz musze to dac
//dodatkowo kazdy plik zrodlowy .cpp uzywajacy modulu pythona musi miec: #define PY_ARRAY_UNIQUE_SYMBOL pbcvt_ARRAY_API
//Zastosowanie init_ar() i Py_Finalize() tylko raz (a nie odpowiednio przed i po klasyfikacji jazdego obiektum jak mamy tutaj) w pointCloud.h -> cloudScene->classify() nie daje zauwazalnego przyspieszenia dzialania programu.
//
#define PY_ARRAY_UNIQUE_SYMBOL pbcvt_ARRAY_API
#include "src/model/classification.h"
//# UWAGA -dziala tylko gdy uruchamiamy program w virtual environment: <w konsoli>: source ~/venv/bin/activate && cd ~/Documents/Qt5/3DPointCloudClassification_GUI/build && ./3DPointCloudClassification_GUI
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

    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;
    PyObject *vecp, *modelDir, *nOfCla;

    if (python_file.empty() || python_func.empty() ) {
        fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
        return {-1};
    }

    init_ar(); //initialization
    //dodanie do PYTHONPATH - zaradzenie problemowi no module names ... found (https://stackoverflow.com/questions/24492327/python-embedding-in-c-importerror-no-module-named-pyfunction)
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")");//czyli wymagamy aby plik pythona byl w folderze w ktorym jest .exe cpp     //PyRun_SimpleString("sys.path.append(\"<some_path>\")");
    PyRun_SimpleString("sys.path.append(\"../embedded_python\")");// embedded modules must be one folder up from executon file
    //# UWAGA-> moze podawac sciezke do embedded modules jako parametr ?
    pName = PyUnicode_FromString(python_file.c_str());
    //Error checking of pName left out //
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, python_func.c_str());
        //pFunc is a new reference
        //cv::Mat photo_cmat;
        //photo_cmat = cv::imread(path,0);
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(3);                      //ilosc zmiennych (parametrow funkcji w pythonie) //elementy musza byc przekazywane do pythona w postaciu Tuple (nawet jak jest tylko jeden)
            ///1 argument - projections///
            vecp = PyTuple_New(projection_vector.size()); //wektor bedacy parametrem w pythonie (f."classify_multiple_projections" w pythonie przyjmuje jedna zmienna bedaca wektorem )//tutaj przechowuje rzuty (projekcje) jednego obiektu -> rozmiar od 1 do ilosci rzutow
            for(int i=0; i<projection_vector.size();i++)
            {
                pValue = pbcvt::fromMatToNDArray(projection_vector[i]); //pValue = pbcvt::fromMatToNDArray(single_projection);

                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    Py_DECREF(vecp); //czy to tez trzeba ?
                    fprintf(stderr, "Cannot convert 1st argument\n");
                    return {-1};
                }

                PyTuple_SetItem(vecp, i, pValue); //przypisuje kolejne tablice na kolejne pozycje tuple o rozmiarze ilosci projekcji jednego obiektu
            }
            PyTuple_SetItem(pArgs, 0, vecp);  //przekazanie pierwszego parameru (ktorym jest wektor vecp),
            /////////////////
            ////2 argument - trained model directory///
            modelDir=PyUnicode_FromString(modelDirectory.c_str());
            if (!modelDir) {
                Py_DECREF(pArgs);
                Py_DECREF(pModule);
                fprintf(stderr, "Cannot convert 2nd argument\n");
                return {-1};
            }
            PyTuple_SetItem(pArgs,1,modelDir); //przekazanie drugiego parametru (nazwy modelu)
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
            Py_DECREF(vecp); //# nie wiem czy to jest potrzebne ?
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
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", python_file.c_str());
        return {-1};
    }
    Py_Finalize();
}
