//
// Created by radek on 21.03.19.
//
#include "src/model/benchmarkAndVisualize.h"
#include "lib/helperFunctions.h"
bool PRINT_LABEL=false;

BoundingBoxType::BoundingBoxType(BBType type):bbType(type){}
pcl::PointXYZ BoundingBoxType::getMinPt(){return this->min_point;}
pcl::PointXYZ BoundingBoxType::getMaxPt(){return this->max_point;}
pcl::PointXYZ BoundingBoxType::getCenter(){return this->center;}
float BoundingBoxType::getLength(){return this->l;}
float BoundingBoxType::getWidth(){return this->w;}
float BoundingBoxType::getHeight(){return this->h;}
float BoundingBoxType::getYaw(){ return  this->yaw;}
BBType BoundingBoxType::getType(){ return this->bbType;}
Eigen::Quaternionf BoundingBoxType::getQuaternionf(){ throw std::runtime_error ("Operation not supported for this BoundingBoxType class");}
Eigen::Vector3f BoundingBoxType::getOBB_positionV3f(){throw std::runtime_error ("Operation not supported for this BoundingBoxType class");}

AxisAlignedBoudningBox::AxisAlignedBoudningBox():BoundingBoxType(type_AxisAlignedBoundingBox){}
void AxisAlignedBoudningBox::calculate(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){
    //  Na razie wszystkie w ukladzie velodyne (skanera)-pozniej prztransformujedo ukl. kamery
    pcl::PointXYZ min_pt, max_pt,center;        //->? nie wiem czy jest sens tworzyc tuaj te zmienne, czy nie lepiej od razu uzywac czlonkow klasy BBType
    pcl::getMinMax3D(*cloud, min_pt, max_pt);
    center = pcl::PointXYZ((max_pt.x + min_pt.x)/2,(max_pt.y + min_pt.y)/2,(max_pt.z + min_pt.z)/2);

    //odpowiednik w benchmarku KITTI:
    this->h=max_pt.z - min_pt.z; //dimension - height
    this->w=max_pt.y - min_pt.y; //dimension - width
    this->l=max_pt.x - min_pt.x;//dimension  - length
    this->yaw=0;        //rotation_y
    this->min_point=min_pt;
    this->max_point=max_pt;
    this->center=center;               //location
    if(PRINT_LABEL){
        std::cout<<"My label: [Class 0 0 0 0 0 0 0 h w l x y z rot_y 1]"<<std::endl;
        std::cout<<" h = "<<this->h;
        std::cout<<" w = "<<this->w;
        std::cout<<" l = "<<this->l<<std::endl;
        std::cout<<" center: "<<std::endl<<this->center<<std::endl;
        std::cout<<" yaw (rot_y) = "<<this->yaw<<std::endl;
    }
}

OrientedBoundingBox::OrientedBoundingBox():BoundingBoxType(type_OrientedBoundingBox){}
void OrientedBoundingBox::calculate(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){
    //lacznie 7 wartosci. Na razie wszystkie w ukladzie velodyne (skanera)-pozniej prztransformujedo ukl. kamery
    pcl::PointXYZ min_point_OBB, max_point_OBB,position_OBB;
    pcl::PointXYZ min_point_OBB_R2, max_point_OBB_R2;
    Eigen::Quaternionf quat_init;
    Eigen::Vector3f positionV3f_init;

    pcl::MomentOfInertiaEstimation <pcl::PointXYZ> feature_extractor;
    feature_extractor.setInputCloud (cloud);
    feature_extractor.compute ();

    std::vector <float> moment_of_inertia;
    std::vector <float> eccentricity;

    Eigen::Matrix3f rotational_matrix_OBB;
    float major_value, middle_value, minor_value;
    Eigen::Vector3f major_vector, middle_vector, minor_vector;
    Eigen::Vector3f mass_center;

    feature_extractor.getMomentOfInertia (moment_of_inertia);
    feature_extractor.getEccentricity (eccentricity);
    feature_extractor.getOBB (min_point_OBB, max_point_OBB, position_OBB, rotational_matrix_OBB);
    feature_extractor.getEigenValues (major_value, middle_value, minor_value);
    feature_extractor.getEigenVectors (major_vector, middle_vector, minor_vector);
    feature_extractor.getMassCenter (mass_center);

    Eigen::Vector3f rpy_OBB = rotational_matrix_OBB.eulerAngles(2, 1, 0);  //kat eulera wzgledem osi z,y,x czyli kat obrotu wokol osi (x,y,z) -> roll,pitch,yaw->mnie interesuje yaw (czyli ea[2]) -> a nie ea[0]?
    double yaw=static_cast<double>(rpy_OBB[0]);
    double alfa=static_cast<double>(rpy_OBB[2]);//rot_x
    double beta=static_cast<double>(rpy_OBB[1]);//rot_y
    Eigen::Quaternionf quat (rotational_matrix_OBB);//wykorzystywane tylko do rysowania boundingboxa (funkcja addCube z kwaternionem)
    Eigen::Vector3f positionV3f (position_OBB.x, position_OBB.y, position_OBB.z); //wykorzystywane tylko do rysowania boundingboxa (funkcja addCube z kwaternionem)
    //std::cout<<std::endl<<"rotatinal_matrix_OBB "<<std::endl<<rotational_matrix_OBB<<std::endl;
    //std::cout<<std::endl<<"angle_axis_OBB "<<rpy_OBB<<std::endl;
    Eigen::Matrix3f R2; //macierz dwoch transforamacji - obrot wokol osi x a nastepnie wokol osi y Rx*Ry
    R2<<    cos(beta)           ,0                  ,   sin(beta),
            sin(alfa)*sin(beta) ,    cos(alfa)       ,-cos(beta)*sin(alfa),
            -cos(alfa)*sin(beta),   sin(alfa)       ,cos(alfa)*cos(beta);
    max_point_OBB_R2.getVector3fMap()=R2*max_point_OBB.getVector3fMap();
    min_point_OBB_R2.getVector3fMap()=R2*min_point_OBB.getVector3fMap();
    float height=max_point_OBB_R2.z - min_point_OBB_R2.z;  //uzywam R2, czyli wymiarow bb po transforamcji, a nie samych obiektow. Robie to po to aby zablokowac obroty wokol osi x i y -> aby byla zgodnosc z labelami w point-cloud-annotation-tool-master
    float width=max_point_OBB_R2.y - min_point_OBB_R2.y;
    float length=max_point_OBB_R2.x - min_point_OBB_R2.x;
    this->h=abs(height);//abs(length*sin(rot_y)+(width*cos(rot_x)+height*sin(rot_x))*cos(rot_y));//max_point_OBB.z - min_point_OBB.z; //height
    this->w=abs(width);//abs(width*sin(rot_x)+height*cos(rot_x));//max_point_OBB.y - min_point_OBB.y; //width
    this->l=abs(length);//abs(length*cos(rot_y)+(width*cos(rot_x)+height*sin(rot_x))*sin(rot_y));//max_point_OBB.x - min_point_OBB.x;//lenght
    this->yaw=yaw;
    this->min_point= min_point_OBB;
    this->max_point=max_point_OBB;
    this->center=position_OBB;  //->? CZY poition_OBB  NA PEWNO JEST ROWNA SRODKOWI BOUNDING BOXA ??
    //pomocnicze do rysowania bounding boxa
    this->OBB_quaternion=quat;
    this->OBB_positionV3f=positionV3f;
    if(PRINT_LABEL){
        std::cout<<"My label: [Class 0 0 0 0 0 0 0 h w l x y z rot_y 1], Using OrientedBoundingBox"<<std::endl;
        std::cout<<" h = "<<this->h<<std::endl;
        std::cout<<" w = "<<this->w<<std::endl;
        std::cout<<" l = "<<this->l<<std::endl;
        std::cout<<" max_point_OBB"<<max_point_OBB<<std::endl;
        std::cout<<" min_point_OBB"<<min_point_OBB<<std::endl;

        std::cout<<" yaw = "<<this->yaw<<std::endl;
        std::cout<<" rot_y = "<<beta<<std::endl;
        std::cout<<" rot_x = "<<alfa<<std::endl;
        std::cout<<" rotational matrix = "<<std::endl<<rotational_matrix_OBB.matrix()<<std::endl;
    }
}
Eigen::Quaternionf OrientedBoundingBox::getQuaternionf(){ return this->OBB_quaternion;}
Eigen::Vector3f OrientedBoundingBox::getOBB_positionV3f(){return this->OBB_positionV3f;}
///////////////////////////////////////////////////////////////

BenchmarkType::BenchmarkType(std::shared_ptr<BoundingBoxType> bBox):boundingBox(bBox){}
void BenchmarkType::setFileName(std::string fName){this->FILENAME=fName;}
void BenchmarkType::setFilePath(std::string fPath){this->FILEPATH=fPath;}
void BenchmarkType::setClassMapping(std::vector<std::string> classList){
    if(!classList.empty()){
        this->class_mapping_set=true;
        for(int i=0; i<classList.size();++i){
            this->classList.push_back(classList[i]);
        }
    }
    else{
        std::cout<<"Empty class vector given, cannot set class mapping"<<std::endl;
        this->class_mapping_set=false;
    }
}
std::string BenchmarkType::mapClass(int i){
    if (class_mapping_set){
        if(i<classList.size()){
            return this->classList[i];
        }
        else{
            std::cout<<"Class with class_id "<<i<<" not mapped"<<std::endl;
            return "unknown";
        }

    }
    else{
        std::cout<<"Class mapping not set (set it by BenchamrkType->setClassMapping(...), instead of class name writing class_id (number)"<<std::endl;
        return std::to_string(i);
    }
}
std::vector<pcl::PointXYZ> BenchmarkType::getBoundingBox(){
    
}
void BenchmarkType::benchmark(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, const int c_id){
    this->class_id=c_id;
    calculateParameters(cloud);
    saveTxt();
}

CustomBenchmark::CustomBenchmark(std::shared_ptr<BoundingBoxType> bBox):BenchmarkType(bBox){}
void CustomBenchmark::saveTxt() {
    std::string FILESAVENAME=FILEPATH+"/"+FILENAME+".txt"; //->? USTALENIE FILESAVEPATH DAJ GDZIE INDZIEJ (BO MASZ DUPLIKACJE KODU W saveTxt() dla roznyuch podklas BenchmarkType)
    std::ofstream outfile;
    ///UWAGA ABY OZNACZENIA BYLY ZGODNE Z MOIMI OZNACZENIAMI WYKONANYMI W point-cloud-annotation-tool-master (czyli tez manual object extraction) to musi byc kolejnosc
    ///wymiarow lenght height width stad tutaj get<10>, get<8> i get<9>. Byc moze wynika to z blednego generowania wymiaorw w point-cloud-annotation-tool-master (bo z opisem labeli od KITTI wynikaloby ze jest h,w,l)
    ///JEDNAK DALEJ JEST COS NIE TAK OBB
    outfile.open(FILESAVENAME.c_str(), std::ios_base::app);//std::ios_base::app
    outfile <<mapClass(class_id)<<" "<< boundingBox->getCenter().x<<" "<<boundingBox->getCenter().y<<" "<<boundingBox->getCenter().z<<" "<<boundingBox->getLength()<<" "<<boundingBox->getWidth()
    <<" "<<boundingBox->getHeight()<<" "<<boundingBox->getYaw()<<std::endl; //nie mozna zrobic tego prosto w petli bo w get<i>(tuple), i musi byc znane w czasie compile, a nie dopiero runtime
    outfile.close();
}
void CustomBenchmark::calculateParameters(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){  //->? dla Custom i KITTI ta funkcja jest zdefiniowana tak samo, wiec mozna ja dac jako zwykla w klasie BenchmarkType
    this->boundingBox->calculate(cloud);
}

KITTIBenchmark::KITTIBenchmark(std::shared_ptr<BoundingBoxType> bBox):BenchmarkType(bBox){}
void KITTIBenchmark::saveTxt(){
    std::string FILESAVENAME=FILEPATH+"/"+FILENAME+".txt"; //->? USTALENIE FILESAVEPATH DAJ GDZIE INDZIEJ (BO MASZ DUPLIKACJE KODU W saveTxt() dla roznyuch podklas BenchmarkType)
    std::ofstream outfile;
    outfile.open(FILESAVENAME.c_str(), std::ios_base::app);//std::ios_base::app
    outfile <<mapClass(class_id)<<" "<< /*turncated*/ 0<<" "<</*occluded*/0 <<" "<</*alpha*/0 <<" "<<bb2D_Xmin<<" "<<bb2D_Ymin<<" "<<bb2D_Xmax<<" "<<bb2D_Ymax
            <<" " << boundingBox->getHeight()<<" "<<boundingBox->getWidth()<<" "<<boundingBox->getLength()<<" "<<
            boundingBox->getCenter().x<<" "<<boundingBox->getCenter().y<<" "<<boundingBox->getCenter().z<<" "<<boundingBox->getYaw()<<" "
            <<score<<std::endl; //nie mozna zrobic tego prosto w petli bo w get<i>(tuple), i musi byc znane w czasie compile, a nie dopiero runtime
    outfile.close();
}
void KITTIBenchmark::calculateParameters(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){
    this->boundingBox->calculate(cloud);
    if(CALCULATE_2D_BB){
        Eigen::VectorXd min(3);
        Eigen::VectorXd max(3);
        Eigen::VectorXd location_cam(4); //location of object (x,y,z) in camera cordinates (not image and not velodyne)
        // // // used only if add_only_if_visable_on_image=1:// // // //
         //im_width,im_heigth -wymiary zdjecia w image_2;  w,h -szerokosc i wysokosc boundig boxa 2d

        get_image_dimensions(left_image_path,im_width,im_height);

        //przypsianie wartosci do min i max:
        transformToLeftImage(boundingBox->getMinPt(),min);  //PointXYZ 3D, Eigen::Vector3d
        transformToLeftImage(boundingBox->getMaxPt(),max);  //PointXYZ 3D, Eigen::Vector3d
        //UWAGA, tu tak naprawde min moze byc max, a max min, wiec trzeba sprawdzic juz na wsp.2D co jest wieksze, a co mniejsze i odpowiednio nizej przypisac (zeby get<4> i get<5> to byly min)
        if(min.x()>max.x())
        {//swap min.x() with max.x()
            max.x()=max.x()+min.x();
            min.x()=max.x()-min.x();
            max.x()=max.x()-min.x();
        }
        if(min.y()>max.y())
        {
            max.y()=max.y()+min.y();
            min.y()=max.y()-min.y();
            max.y()=max.y()-min.y();
        }

        this->bb2D_Xmin=min.x();
        this->bb2D_Ymin=min.y();
        this->bb2D_Xmax=max.x();
        this->bb2D_Ymax=max.y();
    }
}
void KITTIBenchmark::getMatrix(Eigen::MatrixXd &mat, std::string line)
{
    //split line by whitespaces:
    std::string buf;                 // Have a buffer string
    std::stringstream ss(line);       // Insert the string into a stream

    std::vector<std::string> tokens; // Create vector to hold our words

    while (ss >> buf)
        tokens.push_back(buf);

    tokens.erase(tokens.begin());//pomijamy wyraz "P2:", Tr_velo_to_cam: itd
    //Fill the P matrix
    for (int i=0; i<tokens.size();i++)
    {
        //cout<<"w =    "<<floor(i/P.cols())<<"   k= "<<i%P.cols()<<endl;
        mat(floor(i/mat.cols()),i%mat.cols())=stod(tokens[i]);
    }

}
void KITTIBenchmark::transformToLeftImage(pcl::PointXYZ point,Eigen::VectorXd &point_transformed, bool only_to_camera_coordinates){
    //for left images P=P2
    std::vector <std::string> calib;
    if (read_txt_lines(calib_path, calib)) {

        //Eigen::Vector3d point_2D;
        Eigen::Vector4d point_3D(static_cast<double>(point.x), static_cast<double>(point.y),
                                 static_cast<double>(point.z), 1);
        Eigen::MatrixXd P(3, 4);
        Eigen::MatrixXd R0_rect(3, 3); //to trzeba rozszezyc :R0_rect contains a 3x3 matrix which you need to extend to
        //a 4x4 matrix by adding a 1 as the bottom-right element and 0's elsewhere.
        Eigen::MatrixXd Tr_velo_to_cam(3, 4); //Tr_xxx is a 3x4 matrix (R|t), which you need to extend to a 4x4 matrix
        //in the same way!
        //fill:
        getMatrix(P, calib[2]);
        getMatrix(R0_rect, calib[4]);
        getMatrix(Tr_velo_to_cam, calib[5]);

        //extand matix as descibed earlier (and in devkit_object/readme.txt)
        R0_rect.conservativeResize(4, 4);
        R0_rect.col(3).setZero();
        R0_rect.row(3).setZero();
        R0_rect(3, 3) = 1;

        Tr_velo_to_cam.conservativeResize(4, 4);
        Tr_velo_to_cam.row(3).setZero();
        Tr_velo_to_cam(3, 3) = 1;

        if(only_to_camera_coordinates==false) //czyli transformujemy do ukladu zdjecia
        {
            point_transformed = P * R0_rect * Tr_velo_to_cam * point_3D;
            point_transformed = point_transformed / point_transformed(2);

        } else{  //czyli transformujemy tylko do ukladu kamery (czyli dalej 3 wymiaruy), a nie ukladu zdjecia 2D

            point_transformed = Tr_velo_to_cam * point_3D;  //Tr_velo_to_cam to jest juz macierz translacji i rotacji z ukl. velodyne do ukl. kamery
            point_transformed = point_transformed / point_transformed(3);

        }
    }
}
void KITTIBenchmark::setCALCULATE_2D_BB(bool calculate){this->CALCULATE_2D_BB=calculate;}
void KITTIBenchmark::benchmark(const pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, const int c_id){
    this->class_id=c_id;
    calculateParameters(cloud);
    if(add_only_if_visable_on_image==1) //zapisz parametry w pliku prediction, tylko jezeli obiekt jest widoczny na (lewym) zdjeciu
    {
        if(bb2D_Xmin+/*width*/(bb2D_Xmax-bb2D_Xmin)>0 && bb2D_Xmax<im_width+(bb2D_Xmax-bb2D_Xmin) && bb2D_Ymin+/*height*/(bb2D_Ymax-bb2D_Ymin)>0 && bb2D_Ymax<im_height+(bb2D_Ymax-bb2D_Ymin)){ //&& (class_id==5 || class_id==0) //5=Pedastrian, O=Car
            saveTxt();
        }
        else{
            std::cout<<"Not adding label for this object because its not visible on 2D image"<<std::endl;
        }
    }
    else{
        saveTxt();
    }
}


///////////////////////////////////////////////////////////////
std::vector<uint8_t> VisualizationType::mapColor(int class_id){
    std::vector<uint8_t> rgb;   //[r,g,b]
    switch (class_id)
    {
        case 0: //car=red
        { //klamra byla po to by  moc zadeklarowac zmienna wewnatrz petli (inaczej bedzie blad "error: jump to case label [-fpermissive]") - czyli tu chyba nie jest potrzebna (tylko w visualizere)
            rgb.push_back(255);
            rgb.push_back(0);
            rgb.push_back(0);
            break;
        }
        case 1: //buillding=green
        {
            rgb.push_back(0);
            rgb.push_back(255);
            rgb.push_back(0);
            break;
        }
        case 2:  //blue=tree
        {
            rgb.push_back(0);
            rgb.push_back(0);
            rgb.push_back(255);
            break;
        }
        case 3: //purple=street_light,pole itd
        {
            rgb.push_back(139);
            rgb.push_back(0);
            rgb.push_back(139);
            break;
        }
        case 4:  //yellow=person
        {
            rgb.push_back(255);
            rgb.push_back(255);
            rgb.push_back(0);
            break;
        }
        case 5: //magenta= currently not used
        {
            rgb.push_back(255);
            rgb.push_back(0);
            rgb.push_back(144);
            break;
        }
        default: //white
        {
            rgb.push_back(255);
            rgb.push_back(255);
            rgb.push_back(255);
            break;
        }
    }
    return rgb;
}

void VisualizationNoBB::visualize(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,int class_id,std::string name, pcl::visualization::PCLVisualizer::Ptr viewer){
    std::vector<uint8_t> rgb_vis;
    rgb_vis=mapColor(class_id); //get color associtated with cluster class
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, rgb_vis[0], rgb_vis[1], rgb_vis[2]);
    viewer->addPointCloud (cloud, single_color, "classified_"+name);
}

VisualizationWithBB::VisualizationWithBB(std::shared_ptr<BoundingBoxType> bBox) {
    this->boundingBox=bBox;
}
void VisualizationWithBB::visualize(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,int class_id,std::string name, pcl::visualization::PCLVisualizer::Ptr viewer){
    this->boundingBox->calculate(cloud); //we are calculationg bb box parameters for actual cloud
    //->?! moze lepiej POLICZONE RAZ PARAMETRY BB PRZECHOWYWAC W CLASIE CloudObject ?-> bedzie zajmowalo wiecej pamieci ale bedzie sie szybciej liczylo
    std::vector<uint8_t> rgb_vis;
    rgb_vis=mapColor(class_id); //get color associtated with cluster class
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, rgb_vis[0], rgb_vis[1], rgb_vis[2]);
    viewer->addPointCloud (cloud, single_color, "classified_"+name);
    if(this->boundingBox->getType()==type_OrientedBoundingBox){
        viewer->addCube (this->boundingBox->getOBB_positionV3f(), this->boundingBox->getQuaternionf(), this->boundingBox->getMaxPt().x - this->boundingBox->getMinPt().x,
                         this->boundingBox->getMaxPt().y - this->boundingBox->getMinPt().y, this->boundingBox->getMaxPt().z - this->boundingBox->getMinPt().z, "OBB_"+name);
    }
    else if (this->boundingBox->getType()==type_AxisAlignedBoundingBox){
    viewer->addCube (this->boundingBox->getMinPt().x,this->boundingBox->getMaxPt().x, this->boundingBox->getMinPt().y,this->boundingBox->getMaxPt().y,
                     this->boundingBox->getMinPt().z,this->boundingBox->getMaxPt().z
                , 1, 1, 1,"AABB_"+ name);//xmin,xmax,ymin,ymax,zmin,zmax,r,g,b,cube id
    }
    viewer->addText3D(name,this->boundingBox->getCenter(),
           /*txt size*/0.25,1,1,1,"text_"+name); //"text",PointXYZ,text_scale,r,g,b,id
//#w VTK 8.2 juz nie segfault ale mnostwo warningow //NIEWIEDZIEC CZEMU viewer->addText3D powoduje w Qt segmentaion fault
    viewer->setRepresentationToWireframeForAllActors(); //->?! tego NIE TRZEBA ROBIC ZA KAZDYM RAZEM
}
