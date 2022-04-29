//
// Created by radek on 20.03.19.
//

#ifndef INC_3DPOINTCLOUDCLASSIFICATION_CLASSIFICATION_H
#define INC_3DPOINTCLOUDCLASSIFICATION_CLASSIFICATION_H

#include "pyboostcvconverter/pyboostcvconverter.hpp"

//For python embedding:
#if (PY_VERSION_HEX >= 0x03000000)

static void *init_ar() {
#else
    static void init_ar(){
#endif
    Py_Initialize();

    import_array();
    return NUMPY_IMPORT_ARRAY_RETVAL;
}

class ClassificationType{
public:
    virtual std::vector<float> classifyAndGetNNResponeVector(const std::vector<cv::Mat>& projection_vector, const std::string modelDirectory, int numOfClasses)=0;
};
class MultiViewClassification:public ClassificationType{
public:
   std::vector<float> listTupleToVector_Float(PyObject* incoming);
   std::vector<float> classifyAndGetNNResponeVector(const std::vector<cv::Mat>& projection_vector, const std::string modelDirectory, int numOfClasses);
   bool loadPythonModule(PyObject **module,const std::string &file,const std::string &func);
};

#endif //INC_3DPOINTCLOUDCLASSIFICATION_CLASSIFICATION_H
