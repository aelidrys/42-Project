/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:42:27 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/28 09:58:44 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERS_HPP
#define SERVERS_HPP
#include <arpa/inet.h>

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <algorithm> 
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <map>
#include <sys/stat.h>
#include "Location.hpp"
#include <stack>
#include <dirent.h>
#include <iostream>
#include<cstring>
#include <ctime>
#include <stdlib.h>
#include <limits.h>
#include <string>
#include <iomanip>
class Servers
{
private:
    int  checkDup(std::string der,int & index);
    int JoinIndexRoot(int &in);
    int pathIsFile(std::string path);
    int searchPathLocation(string uri);
    int getLocation(std::string path);
    bool check_isdigit(std::string str);
    bool MatchingWithRoot(string & rootPlusUri,string &rootPath);
    void FillValid();
    void check_Status(std::string status);
    void SetPorts (); 
    void SetServerName(vector<string> & ser_names); 
    void SetHost(); 
    void SetRoot();
    void SetError_page();  
    void SetClient_max_body_size(); 
    void SetIndex(); 
    void FillQuerys(string & uri);
    void SetDefaultError();
    void SetRederectionResp(vector<string> & redirect);
    void CheckAllowd();
    std::vector<std::string> s_erorr;
    std::vector<std::string> Vstrvalid;
    std::vector<std::string> vAlowed;
    Location FirstFill(size_t & index);
    vector<string> locationPath;
    size_t GetIndex(std::string dir);
    bool checkPermession(string _path);
    void setStatusRootPlusUri(string  _status);
    bool per;
    void deCodeUri(string _rootURi,string uri);
    string decooding_uri(string uri);
public:
    int port;
    int server_fd;
    int fillFromLocation(int &in, string &uri,string & method);
    bool  operator== (const Servers& ser);
    bool  operator== (const string & servername);
    bool Is_cgi;
    void SetUriRoot(int i,string & uri);
    void FillLocation();
    void SetAllDir(vector<string> & ser_names);
    void CreatSocketServer( std::map<int,vector<Servers> > & msockets);
    void SetIndex_Of(string _path);
    void FillData(string uri,string mehtod);
    double client_max_body_size;
    struct sockaddr_in address;
    std::vector<std::string> server_name; 
    std::string host; 
    std::string root;
    std::vector<std::string> index;
    std::vector<string> redirect;
    std::vector<std::vector<std::string> > servconf;
    std::vector<Location> locations;
    std::string rootUri;
    std::string querys;
    std::string status;
    std::map<string,string> error_page;
    Location UriLocation;
    ~Servers();
    Servers();
};


#endif