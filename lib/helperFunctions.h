//
// Created by radek on 17.03.19.
//

#ifndef INC_3DPOINTCLOUDCLASSIFICATION_HELPERFUNCTIONS_H
#define INC_3DPOINTCLOUDCLASSIFICATION_HELPERFUNCTIONS_H

#include <string>
#include <fstream> //->?do zapisywania do pliku .txt
#include <iostream> //->? do cerr
#include <arpa/inet.h>//->? do ntohl w funkcji get_image_dimensions
#include <vector>
#include <dirent.h>// do listowania plikow
#include <sys/stat.h>
#include <sstream>
#include <iomanip>

inline std::string get_filename(std::string path, bool remove_extension=0)
{
    // Remove directory if present.
// Do this before extension removal incase directory has a period character.
    const size_t last_slash_idx = path.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)  //check if symbol was found (else .find... returns string::npos)
    {
        path.erase(0, last_slash_idx + 1);
    }

    if (remove_extension==1)
    {
        // Remove extension if present.
        const size_t period_idx = path.rfind('.');
        if (std::string::npos != period_idx)
        {
            path.erase(period_idx);
        }
    }

    return path;
}
inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}
/**
 * \wczytuje z pliku do wektora kolejne linie w plik txt (vec[0] -> sting zawierajacy wszystko w pierwszej lini plku txt
 * @param calib_path
 * @param calib
 * @return
 */
inline bool read_txt_lines(std::string calib_path,std::vector<std::string>& calib)
{
    //open the file
    std::ifstream fid(calib_path);
    //check if objects is valid
    if(!fid)
    {
        std::cerr << "Cannot open the File : "<<calib_path<<std::endl;
        return false;
    }

    std::string str;
    // Read the next line from File untill it reaches the end.
    while (getline(fid, str))
    {
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0)
            calib.push_back(str);
    }
    //Close The File
    fid.close();
    return true;
}

inline void get_image_dimensions(std::string path, unsigned int &width,unsigned int &height )
{
    std::ifstream in(path);


    in.seekg(16);
    in.read((char *)&width, 4);
    in.read((char *)&height, 4);

    width = ntohl(width);
    height = ntohl(height);

    std::cout << path << " is " << width << " pixels wide and " << height << " pixels high.\n";
}
/**
  * Returns folders or files names (with or without extension)
  * 1=files
  * 2=folders
  */
inline void list_dir(std::vector<std::string> &results,std::string curr_directory, std::string extension,int files_or_folders=1,bool remove_extension=0){  //files_or_folders=1 - list only files, 2-list only folders
    DIR* dir_point = opendir(curr_directory.c_str());
    if(dir_point!=nullptr){
        dirent* entry = readdir(dir_point);
        struct stat sb;
        while (entry){									// if !entry then end of directory
            if (entry->d_type == DT_DIR){				// if entry is a directory
                if(files_or_folders==1)
                    std::cout<<entry->d_name<<" is directory, skipping"<<std::endl;
                else if(files_or_folders==2){
                    std::string fname = entry->d_name;
                    if (fname != "." && fname != "..")
                    {
                        results.push_back(fname);
                    }
                }

                //list_dir(entry->d_name, extension);	// search through it
            }
            else if (entry->d_type == DT_REG){		// if entry is a regular file
                if(files_or_folders==1)
                {
                    std::string fname = entry->d_name;	// filename
                    // if filename's last characters are extension
                    if (fname.find(extension, (fname.length() - extension.length())) != std::string::npos) {
                        if (remove_extension) {
                            fname = fname.substr(0, fname.length() - extension.length());
                        }
                        results.push_back(fname);        // add filename to results vector
                    } else
                        std::cout<<"File "<<fname<<" doesnt have apporpriate extension ( "<<extension<<" ) , skipping"<<std::endl;
                }
                else if(files_or_folders==2)
                    std::cout<<entry->d_name<<" is a file, skipping"<<std::endl;
            }
            else if (entry->d_type == DT_UNKNOWN){ //unkonwn probalby because of unsupported filesystem by "entry->d_type" :https://stackoverflow.com/questions/47078417/readdir-returning-dirent-with-d-type-dt-unknown-for-directories-and
                //std::cout<<"UNKNOWN ENTRY TYPE, USIN lstat()"<<std::endl;
                if(lstat((curr_directory+"/"+entry->d_name).c_str(),&sb)!=-1){
                    if(S_ISREG(sb.st_mode)!=0){ //is it a REGULAR FILE?
                        if(files_or_folders==1)
                        {
                            std::string fname = entry->d_name;	// filename
                            // if filename's last characters are extension
                            if (fname.find(extension, (fname.length() - extension.length())) != std::string::npos) {
                                if (remove_extension) {
                                    fname = fname.substr(0, fname.length() - extension.length());
                                }
                                results.push_back(fname);        // add filename to results vector
                            } else
                                std::cout<<"File "<<fname<<" doesnt have apporpriate extension ( "<<extension<<" ) , skipping"<<std::endl;
                        }
                        else if(files_or_folders==2)
                            std::cout<<entry->d_name<<" is a file, skipping"<<std::endl;
                    }else if (S_ISDIR(sb.st_mode)!=0){ //DIRECTORY?
                        if(files_or_folders==1)
                            std::cout<<entry->d_name<<" is directory, skipping"<<std::endl;
                        else if(files_or_folders==2){
                            std::string fname = entry->d_name;
                            if (fname != "." && fname != "..")
                            {
                                results.push_back(fname);
                            }
                        }
                    }
                }else{
                    std::cout<<"could not lstat() "<<curr_directory+"/"+entry->d_name<<std::endl;
                }
            }

            entry = readdir(dir_point);
        }
    }else{
        std::cout<<"Could not open "<<curr_directory<<" directory"<<std::endl;
        return;
    }


}
//Funkcja zwracajaca n unikalnych i losowych elementow z podanego np. vectora :
// https://stackoverflow.com/questions/9345087/choose-m-elements-randomly-from-a-vector-containing-n-elements
//https://ideone.com/3A3cv
template<class bidiiter>
inline bidiiter random_unique(bidiiter begin, bidiiter end, size_t num_random) {
    size_t left = std::distance(begin, end);
    while (num_random--) {
        bidiiter r = begin;
        std::advance(r, rand()%left);
        std::swap(*begin, *r);
        ++begin;
        --left;
    }
    return begin;
}

inline bool DirectoryExists( const char* pzPath )
{
    if ( pzPath == NULL) return false;

    DIR *pDir;
    bool bExists = false;

    pDir = opendir (pzPath);

    if (pDir != NULL)
    {
        bExists = true;
        (void) closedir (pDir);
    }

    return bExists;
}
inline int countTxtLines(std::string path){
    int number_of_lines = 0;
    std::string line;
    std::ifstream myfile(path);

    while (std::getline(myfile, line))
        ++number_of_lines;
    return number_of_lines;
}
template<class T>
inline std::string vectorToString(std::vector<T> vec,std::string separator,bool addBrackets=false){
    std::stringstream stream("");
    std::string result;
    if(addBrackets){stream<<"[";}

    for(auto &element:vec){
        stream<<std::fixed<<std::setprecision(5)<<element<<separator;
    }
    result=stream.str();
    if(!result.empty()){result.pop_back();}//remove last separator
    if(addBrackets){result.append("]");}
    return result;
}
#endif //INC_3DPOINTCLOUDCLASSIFICATION_HELPERFUNCTIONS_H
