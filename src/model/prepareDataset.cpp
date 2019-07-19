//
// Created by radek on 26.03.19.
//
#include "src/model/prepareDataset.h"
#include "lib/helperFunctions.h"
#include <random>
PrepareDatasetFrom3D::PrepareDatasetFrom3D(uint TOTAL_PROJECTIONS, double START_DEGREE,double END_DEGREE ,double START_v,double END_v,int N_v):TOTAL_PROJECTIONS(TOTAL_PROJECTIONS),START_DEGREE(START_DEGREE),END_DEGREE(END_DEGREE),START_v(START_v),END_v(END_v),N_v(N_v){
    this->factory=std::make_shared<CloudObjectFactory>();
}
int PrepareDatasetFrom3D::calculateNumberOfProjections(uint num_of_class_obj){
    uint proj_per_obj;
    int n_horizontal; //ilosc projekcji dookola


    if(TOTAL_PROJECTIONS>0 && num_of_class_obj>=1) //user gave required total number of porjections
    {
        proj_per_obj=static_cast<uint>(ceil(static_cast<double>(TOTAL_PROJECTIONS)/ static_cast<double>(num_of_class_obj)));
        cout<<"PROJECTIONS PER OBJECT = "<<proj_per_obj<<endl;
    }
    else //TOTAL_PROJECTIONS not given by user (=-1), do default number of porjections per obnject
        proj_per_obj=default_num_of_proj_per_obj;

    //Ustalenie ilosci rzutow dookola, na podstawie wymaganej ilosci rzutow gora-dol
    if(proj_per_obj%N_v==0){ //czyli np. 36 rzutow N_v=2 czyli dla kazdej z dwoch orientacji w pionie mamy 18 rzutow dookola
        n_horizontal=proj_per_obj/N_v;
    }
    else{//Przypadek 2
        n_horizontal= static_cast<uint>(ceil(static_cast<double>(proj_per_obj)/ static_cast<double>(N_v))); //poniewaz bierzemy nadmiar, to bedzie na koncu wiecej rzutow do usuniecia (moze sie zdarzyc, ze wiecej niz jest obiektow)
    }
    return n_horizontal;
}
void PrepareDatasetFrom3D::removeSurplusProjections(std::string PROJECTIONS_PATH,int n_horizontal, int num_of_class_obj){
    uint num_to_remove=0;
    uint total_removed=0, not_removed=0, not_removed_temp=0;
    //usuwanie nadmiarowych rzutow (powyzej TOTAL_PROJECTIONS):
    if(TOTAL_PROJECTIONS>0 && num_of_class_obj>=1)
    {
        num_to_remove=(n_horizontal*N_v*num_of_class_obj)-TOTAL_PROJECTIONS;
        if(num_to_remove>0)
        {
            printf("Removing %d projections\n",num_to_remove);
            std::string removed_fname;
            std::ofstream outfile;
            //do losowania samych cyfr (niekoniecznie unikalnych) -> te co sa na koncu w nazwie rzutow (.jpg) tzn.: np. h00_p001 , h00_p031 itd.
            std::random_device rd; // obtain a random number from hardware
            std::mt19937 eng(rd()); // seed the generator
            std::uniform_int_distribution<> distr_projections(0, (n_horizontal*N_v)-1); // define the range
            //losujemy obiekty (unikalnie:
            if(num_to_remove<=fnames.size())
                random_unique(fnames.begin(), fnames.end(),num_to_remove); //teraz, fnames zawiera juz tylko num_to_remove nazw (uniklanych) : https://ideone.com/3A3cv     ,https://stackoverflow.com/questions/9345087/choose-m-elements-randomly-from-a-vector-containing-n-elements
            else //patrz Przypadek 2
                random_unique(fnames.begin(), fnames.end(),fnames.size());
            /*
            std::vector<int> a(10000);
            for(int i=0; i<10000; ++i)
                a[i] = i;
            random_unique(a.begin(), a.end(), 13);
            for(int i=0; i<13; ++i) {
                std::cout << a[i] << '\n';
            }
             */
            //usuwanie plikow
            //create folder for removed (moved) files
            if(!DirectoryExists((PROJECTIONS_PATH+"/removed").c_str()))
            {
                const int dir_err = mkdir((PROJECTIONS_PATH+"/removed").c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                if (-1 == dir_err)
                {
                    printf("Error creating %s directory!n",(PROJECTIONS_PATH+"/removed").c_str());
                    exit(1);
                }
            }

            outfile.open((PROJECTIONS_PATH+"/removed/removed.txt").c_str(), std::ios_base::app);
            outfile <<"Doing "<<(n_horizontal*N_v)<<" projections per object (horizontal= "<<n_horizontal<<" , vertical= "<<N_v<<") for "<<num_of_class_obj<<" objects. Goal is: "<<TOTAL_PROJECTIONS<<". Start degree = "<<
                    START_DEGREE<<" , end degree = "<<END_DEGREE<<" , START vertical = "<<START_v<<" , END vertical = "<<END_v<<" , required(given) vertical projections= "<<N_v<<endl;
            cout<<"Doing "<<(n_horizontal*N_v)<<" projections per object (horizontal= "<<n_horizontal<<" , vertical= "<<N_v<<") for "<<num_of_class_obj<<" objects. Goal is: "<<TOTAL_PROJECTIONS<<". Start degree = "<<
             START_DEGREE<<" , end degree = "<<END_DEGREE<<" , START vertical = "<<START_v<<" , END vertical = "<<END_v<<" , required(given) vertical projections= "<<N_v<<endl;

            int j=0;
            for (int i=0; i<num_to_remove; i++)
            {
                if(i>fnames.size()-1)  //patrz Przypadek 2
                    j=i%fnames.size();
                else
                    j=i;
                //nazwa pliku do usuniecia:
                removed_fname=fnames.at(j)+this->projection->getProjectionNameSuffix(distr_projections(eng))+".jpg"; //we remove one random projection from one object
                cout<<"removed_fname = "<<removed_fname<<endl<<endl;
                ///UWAGA, jezeli liczba rzutow do usniecia, bedzie wieksza niz liczba obiektow (a moze sie tak zdarzych dla N_v>1 - patrz Przypadek 2), to
                ///moze sie zdarzyc ze powyzej wylosujemy dwa razy taka sama nazwe (ten sam rzut). Wowczas wystapi blad, ktory zostanie wychwycony nizej, i
                ///zapisany do poliku removed.txt.
                /// Bedzie po porstu wtedy wiecej rzutow niz wymagane TOTAL_PROJECTIONS.
                ///Aby temu problemowi zaradzić, mozna jakos sprawdzac, czy dany rzut zostal juz wylosowany i jak tak to losowac kolejny i tak do skutku
                ///Ostatecznie mozna tez losowac num_to_remove (bez zadnych sprawdzen) z ostatecznej listy rzutow. Ale wowczas moze byc tak, ze wylosujemy zbyt
                ///duza liczbe rzutow dla jednego obiektu (a nawet wszystkie dla tego obiektu, co oznacza, ze usunelibysmy ze zbioru caly obiekt).
                not_removed_temp=0;
                while(std::rename((PROJECTIONS_PATH+"/"+removed_fname).c_str(), (PROJECTIONS_PATH+"/removed/"+removed_fname).c_str()) < 0){
                    cout<< "Could not move "<<(PROJECTIONS_PATH+"/"+removed_fname).c_str()<<" -> "<< strerror(errno) <<'\n';
                    ++not_removed_temp;
                    if(not_removed_temp>n_horizontal*N_v){ //we try to remove it only constrained number of times - to avoid endless loop-> it means there stilll can be a situation in which we wont remove enough projections
                        std::cout<<"Could not remove any of the projections in "<<removed_fname<<" Probaly all of the projections for this object was removed."<<std::endl;
                        ++not_removed;
                        break;
                    }
                    removed_fname=fnames.at(j)+this->projection->getProjectionNameSuffix(distr_projections(eng))+".jpg";
                }
                outfile <<removed_fname<<endl;
                ++total_removed;

            }
            outfile <<"Totall removed = "<<total_removed<<std::endl;
            outfile <<"Could not remove = "<<not_removed<<std::endl;
            outfile.close();
            std::cout<<"Total_removed = "<<total_removed<<std::endl;
            std::cout<<"Could not remove = "<<not_removed<<std::endl;

        } else{
            cout<<"Nothing to remove, total projections <= required TOTAL_PROJECTIONS (if is zero then is ok), num_to_remove = "<<num_to_remove<<endl;
        }

    }
}
//////////////////////////////////////////////////////////////////////////////////////////////
PrepareBinaryImages::PrepareBinaryImages(uint TOTAL_PROJECTIONS, double START_DEGREE, double END_DEGREE, double START_v,
                                         double END_v, int N_v):PrepareDatasetFrom3D(TOTAL_PROJECTIONS,START_DEGREE,END_DEGREE ,START_v,END_v,N_v) {}
void PrepareBinaryImages::prepare(std::string SRC_PATH, std::string PROJECTIONS_PATH){
    fnames.clear();
    uint n_horizontal;
    std::string fpath="";
    list_dir(fnames,SRC_PATH,".pcd",1,0); //file list without extension
    int num_of_class_obj=fnames.size(); //total number of objects

    n_horizontal=calculateNumberOfProjections(num_of_class_obj);
    projection=std::make_shared<BinaryProjection>(START_DEGREE,END_DEGREE , n_horizontal, START_v, END_v,N_v);//# to tez ewentualnie moze byc tworzone raz w konstruktorze, a tutaj mozna uzywac tylko funkcji projection->setParameters()
    int i=0;

    for (const auto &file:fnames)
    {
        std::cout<<i<<" ------------------------"<<endl;
        fpath=SRC_PATH+"/"+file;
        cout<<fpath<<endl;
        object=factory->create(fpath);
        //object->setProjectionType(projection);

        object->project(projection); //(0,360,36,0,0,1,PROJECTIONS_PATH,file)
        object->saveProjections(PROJECTIONS_PATH);
        ++i;
    }

    removeSurplusProjections(PROJECTIONS_PATH,n_horizontal,num_of_class_obj);
}
/////////////////////////////////////////////////////////////////////////////////////////////
PrepareRangeImages::PrepareRangeImages(uint TOTAL_PROJECTIONS, double START_DEGREE, double END_DEGREE, double START_v,
                                         double END_v, int N_v):PrepareDatasetFrom3D(TOTAL_PROJECTIONS,START_DEGREE,END_DEGREE ,START_v,END_v,N_v) {}
void PrepareRangeImages::prepare(std::string SRC_PATH, std::string PROJECTIONS_PATH){
    fnames.clear();
    uint n_horizontal;
    std::string fpath="";
    list_dir(fnames,SRC_PATH,".pcd",1,0); //file list without extension
    int num_of_class_obj=fnames.size(); //total number of objects

    n_horizontal=calculateNumberOfProjections(num_of_class_obj);
    projection=std::make_shared<RangeImageProjection>(START_DEGREE,END_DEGREE , n_horizontal, START_v, END_v,N_v);//# to tez ewentualnie moze byc tworzone raz w konstruktorze, a tutaj mozna uzywac tylko funkcji projection->setParameters()
    int i=0;

    for (const auto &file:fnames)
    {
        std::cout<<i<<" ------------------------"<<endl;
        fpath=SRC_PATH+"/"+file;
        cout<<fpath<<endl;
        object=factory->create(fpath);
        //object->setProjectionType(projection);

        object->project(projection); //(0,360,36,0,0,1,PROJECTIONS_PATH,file)
        object->saveProjections(PROJECTIONS_PATH);
        ++i;
    }

    removeSurplusProjections(PROJECTIONS_PATH,n_horizontal,num_of_class_obj);
}
