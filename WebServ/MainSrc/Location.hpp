/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:23:05 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/27 09:14:01 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP


#include <algorithm> 
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <map>
#include <sys/stat.h>
#include <limits.h>

enum PERMESSION {
    GET=1,
    POST=2,
    DELETE=4,
    UPLOAD=8,
    AUTOINDEX=16,
    REDIR =32
    };
using namespace std;
class Location
{
private:
        int  checkDup(std::string der,int & index);
        int pathIsFile(std::string path);
        void CheckMethods(std::string methd);
        void SetIndex();
        void SetPath(vector<string>& locpath);
        void SetAllowMethods();
        void SetAutoindex();
        void SetUpload();
        void SetUpload_path();
        void SetCgiPath();
        void SetRoot();
        void SetReturn();
        bool get;
        bool post;
        bool dele;
        bool checkPermession(string _path);
        size_t GetIndex(std::string dir);
        string ServRoot;
        vector<string>  Servindex;
public:
        int permession;
        void SetAllDir(vector<string>& locpath);
        void SetIndexRoot(string root,vector<string> & index );
        std::string path;
        std::string  upload_path;
        std::string root;
        std::vector<std::string> index;
        std::vector<std::vector<std::string> > vlocation;
        std::map<string ,string> cgi_path;
        std::vector<string> redirect;
        Location();
        ~Location();
};
#endif