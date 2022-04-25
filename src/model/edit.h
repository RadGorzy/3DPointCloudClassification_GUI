//
// Created by radek on 26.03.19.
//

#ifndef INC_3DPOINTCLOUDCLASSIFICATION_EDIT_H
#define INC_3DPOINTCLOUDCLASSIFICATION_EDIT_H
#include <opencv2/opencv.hpp>
class EditType{
public:
    virtual void edit(std::vector<cv::Mat> &projections)=0;
};
class ProjectionEdit:public EditType{
private:
    cv::MorphShapes kernelShape=cv::MORPH_ELLIPSE;
    uint kernelWidth=3;
    uint kernelHeight=3;

public:
    ProjectionEdit(cv::MorphShapes kerShape,uint kerWidth, uint kerHeigth);
    void edit(std::vector<cv::Mat> &projections);
};

#endif //INC_3DPOINTCLOUDCLASSIFICATION_EDIT_H
