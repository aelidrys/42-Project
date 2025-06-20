#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "../MainSrc/Servers.hpp"
using namespace std;

#ifndef METHOD_HPP
#define METHOD_HPP

class Method
{
protected:
public:
    int err;
    int end;
    string uri;
    string http_v;
    string fullUri_path;
    string respons;
    Servers serv;
    map<string, string> headers;
    virtual int process(string body, int event) = 0;
    Method();
    Method(const Method& oth);
    Method& operator=(const Method& oth);
    virtual ~Method();
};


#endif