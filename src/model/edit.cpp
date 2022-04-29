//
// Created by radek on 26.03.19.
//
#include "model/edit.h"

ProjectionEdit::ProjectionEdit(cv::MorphShapes kerShape,uint kerWidth, uint kerHeigth):kernelShape(kerShape),kernelWidth(kerWidth),kernelHeight(kerHeigth){}
void ProjectionEdit::edit(std::vector<cv::Mat> &projections){
     //photo editing
     cv::Mat kernel= cv::getStructuringElement(kernelShape,cv::Size(kernelWidth,kernelHeight)); //bez upsampling stosowalem 6,6  //po upsampling 3,3
     ///Canny( vecMat, vecMat, 100, 200);
     std::vector<int> compression_params;
     compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
     compression_params.push_back(100);
     //store image in memory buffer (no need to write to file)
     std::vector<uchar> buf;
     //UWAGA - wynik klasyfikacji nieznacznie sie rozni w zaleznosci od zastosowania ponizej jedenj z 3 operacji:
     //1. Zakodowanie (z domyslnymi parametrami czyli m.in. CV_IMWRITE_JPEG_QUALITY=0.95)  orginalnej powyzszej vecMat, a nastepnie odkodowanie - czyli tak jakby odczytanie .jpg z pliku
     // w ten sposob klasyfikuje tak jakbym wczytywal zjdecie z pliku z uzyciem imread -> tak to jest robione w TestowanieModelu.py jezeli uruchomie jako main (rezultaty sa wowczas tutaj takie same jak tam)
     //2. Podanie do classify_single oryginalnej cvMat - zdaje sie, ze daje lepsze rezultaty niz sposob 1 (czedu kliku dziesieciotysiecznych na korzysc poprawnej sily odpowiedzi modelu sieci
     //3. Zakodowanie jak w sposobie 1. tylko CV_IMWRITE_JPEG_QUALITY=0.100:
     ///*

    for(int i=0; i<projections.size();++i){
        buf.clear();
        cv::morphologyEx(projections.at(i),projections.at(i),cv::MORPH_DILATE,kernel);///cv::morphologyEx(vecMat,vecMat,cv::MORPH_CLOSE,kernel);
        cv::imencode(".jpg", projections.at(i), buf,compression_params);
        projections.at(i)=cv::imdecode(buf,0);
    }






}


