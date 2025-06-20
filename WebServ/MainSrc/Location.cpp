/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:23:03 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/31 16:07:30 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

int Location::pathIsFile(std::string path)
{
    struct stat fileStat;
    if (stat(path.c_str(), &fileStat) == 0)
    {
        if (fileStat.st_mode & S_IFREG)
        {
            return 2;
        }
        else if (fileStat.st_mode & S_IFDIR)
        {
            return 3;
        }
        else
            return 4;
    }
    else
        return 0;
}

size_t Location::GetIndex(std::string dir)
{
    size_t i ;
    for (i = 0; i < vlocation.size(); i++)
    {
        if (vlocation[i][0] == dir)
        {
            return i;
        }
    }
    return (i);
}

int Location::checkDup(std::string der,int & index)
{
    int dup = 0;
    size_t i = 0;
    while ( i < vlocation.size())
    {
        if (vlocation[i][0] == der)
        {
            index = i;
            dup++;
        }
        if (dup > 1)
            throw "Error: Duplicate directive '" + der + "' detected in configuration file.\n";
        i++;
    }
    return (dup);
}
bool Location::checkPermession(string _path)
{
    struct stat stat_info;
    if(stat(_path.c_str(),&stat_info) < 0)
        return 0;
    if ((stat_info.st_mode & S_IXUSR) && (stat_info.st_mode & S_IWUSR))
        return 1;
    return 0;
}

void Location::SetAllDir(vector<string>& locpath)
{
    
    SetRoot();
    SetAllowMethods();
    SetUpload();
    SetUpload_path();
    SetReturn();
    SetPath(locpath);
    SetCgiPath();
    SetAutoindex();
    SetIndex();
}

void Location::SetIndex()
{
    int i;
    vector<string>::iterator iter;
    int num = checkDup("index", i);
    if (num == 0)
    {
        index = Servindex;
        return;
    }
    if (vlocation[i].size() < 2)
    {
        throw "Invalid number of arguments in 'index' directive \n";
    }
    iter = vlocation[i].begin();
    iter++;
    while (iter != vlocation[i].end())
    {
        index.push_back(*iter);
        iter++;
    }
}

void Location::SetIndexRoot(string root, vector<string> & index)
{
    Servindex = index;
    ServRoot = root;
}

void Location::SetRoot()
{
    int i;
    int num = checkDup("root",i);
    char resolvedPath[PATH_MAX];
    std::string arg;
    if (num == 0)
    {
        root =  ServRoot;
        return ;
    }
    if (vlocation[i].size() != 2 )
        throw "Error : Invalid number of arguments in 'root' directive \n";
    arg = vlocation[i][1];
    if (pathIsFile(arg) != 3) 
        throw("Root path :'" + arg + "' does not exist or is not a directory.\n");
    realpath(arg.c_str(),resolvedPath);
    root = resolvedPath;
    root += "/";
}


void CheckValidPathLocation(string & pathlocation)
{
    if (pathlocation[0] != '/')
        throw "Error: Invalid input path. Please provide a valid path.\n";
    if (pathlocation.size() == 1)
        return ;
    if (pathlocation[pathlocation.length() - 1] == '/')
        throw "Error: Invalid input path. Please provide a valid path.\n";
    pathlocation.push_back('/');
}
void Location::SetPath(vector<string>& locpath)
{
    int i;
    int num = checkDup("location",i);
    std::string arg;
    if (num == 0)
        return ;
    if (vlocation[i].size() != 2 )
        throw "Invalid number of arguments in 'location' directive \n";
    arg = vlocation[i][1];
    CheckValidPathLocation(arg);
    if (find(locpath.begin(),locpath.end(),arg) != locpath.end())
        throw "Error :duplicate location "+arg+" \n";
    path  = arg;
}

void Location::CheckMethods(std::string methd)
{
    std::vector<std::string> allMethds;
    std::vector<std::string>::iterator iter;
    if ((get && methd == "GET" ) ||( post && methd == "POST" )|| (dele && methd == "DELETE") )
        throw "Error :duplicate methods "+methd+" \n";
    allMethds.push_back("POST");
    allMethds.push_back("GET");
    allMethds.push_back("DELETE");
    iter = std::find(allMethds.begin(),allMethds.end(),methd);
    if (iter == allMethds.end())
        throw "Error : no method "+methd+ " exists\n";
    if (methd == "POST")
        post = 1;
    if (methd == "GET")
        get = 1;
    if (methd == "DELETE")
        dele = 1;
}

void Location::SetAllowMethods()
{
    int i;
    std::string arg;
    std::vector<std::string> vallow;
    std::vector<std::string>::iterator iter;

    int num = checkDup("allow_methods",i);
    post = 0;
    get = 0;
    dele = 0;
    if (num == 0)
        return ;
    if (vlocation[i].size() > 4 || vlocation[i].size() < 2 )
         throw "Invalid number of arguments in 'allow_methods' directive \n";
    vallow =  vlocation[i];
    iter = vallow.begin();
    iter++;
    while (iter != vallow.end())
    {
        CheckMethods(*iter);
        permession = (POST * post) | (DELETE * dele) | (GET * get);
        iter++;
    }    
}

void Location::SetAutoindex()
{
    int i;
    std::string arg;

    int num = checkDup("autoindex",i);
    if (num == 0)
        return ;
    if (vlocation[i].size() != 2 )
        throw "Invalid number of arguments in 'autoindex' directive \n";
    arg = vlocation[i][1];
    if (arg != "on" &&  arg != "off")
        throw "invalid  '" + arg + "' in auotindex  directive \n";
    if (arg == "on")
        permession += AUTOINDEX;
}

void Location::SetUpload()
{
    int i;
    std::string arg;
    int num = checkDup("upload",i);
    if (num == 0)
        return ;
    if (vlocation[i].size() != 2 )
         throw "Invalid number of arguments in 'upload' directive \n";
    arg = vlocation[i][1];
    if (arg != "on" &&  arg != "off")
       throw "invalid  '" + arg + "' in upload  directive \n";
    if (arg == "on")
        permession += UPLOAD;
}

void Location::SetCgiPath()
{
    std::string extantion;
    std::string pathcgi;
    for (size_t i = 0; i < vlocation.size(); i++)
    {
        if (vlocation[i][0] == "cgi_path")
        {
            if (path != "/cgi/")
                throw "Error : 'cgi path' directive is not allowed here \n";
            if (vlocation[i].size() != 3)
               throw "Invalid number of arguments in 'cgi_path' directive \n";
            extantion = vlocation[i][1];
            pathcgi = vlocation[i][2];
            if (!pathIsFile(pathcgi)) 
                throw ("Path '"+pathcgi+"' does not exist.\n");
            cgi_path[extantion] = pathcgi;
        }
    }
}
void Location::SetUpload_path()
{
    int i;
    std::string arg;

    int num = checkDup("upload_path",i);
    if (num == 0)
    {
        if (permession & UPLOAD)
            throw "Error : Upload in active mode  need to set upload_path \n";
        return ;
    }
    if (vlocation[i].size() != 2 )
        throw "Invalid number of arguments in 'upload_path' directive \n";
    arg = vlocation[i][1];
    if (pathIsFile(arg) != 3 || !checkPermession(arg))
        throw "Error : Path is not valid to upload or is not a directory\n";
    upload_path = arg;
}

void Location::SetReturn()
{
    int i;
    std::string arg;

    int num = checkDup("return",i);
    if (num == 0)
        return ;
    if (vlocation[i].size() != 3 )
        throw "Invalid number of arguments in 'return' directive \n";
    arg = vlocation[i][1];
    if (arg != "on" && arg != "off")
        throw "Error : argument  "+arg+" is not valid ( on or off)\n";
    if (arg == "on")
        permession += REDIR;
    redirect.push_back(arg);
    redirect.push_back(vlocation[i][2]);
    
}

Location::Location()
{
    permession = 1;
    root = "";
    index.push_back("");
    upload_path = "";
    path = "";
}

Location::~Location()
{
}