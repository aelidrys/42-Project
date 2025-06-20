/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 09:43:27 by abouassi          #+#    #+#             */
/*   Updated: 2024/02/01 09:28:00 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Delete.hpp"
int Delete::process(string body, int event) 
{
    (void)body;
    if(event == EPOLLOUT)
    {
        if(serv.status != "200 OK")
        {
            get.serv.status = serv.status;
            get.get(serv.error_page[serv.status]);
            respons = get.respons;
            if(get.end)
                end = 1;
            return 0;
        }
        if(deleted) 
        {
            RemoveAllPath(serv.rootUri);
            deleted = 0;
        }
        if(status == 0)
        {
            respons = "HTTP/1.1 204\r\n\r\n";
            if(get.end)
                end = 1;
        }
        else if (status == 1)
        {
            get.serv.status = "403";
            get.get(serv.error_page["403"]);
            respons = get.respons;
            if(get.end)
                end = 1;
        }
        else
        {
            get.serv.status = "500";
            get.get(serv.error_page["500"]);
            respons = get.respons;
            if(get.end)
                end = 1;
        }
    }
    return 0;
}

Delete::Delete()
{
    status = 0;
    deleted = 1;
}

int  Delete::my_remove(std::string file)
{
    if (std::remove(file.c_str()) != 0) 
    {
        if(!status)
            status = 2;
        return 1;
    }
    else 
        return 0;
}

string PatentOfFile(string & fullPath)
{
    long  len = fullPath.length();
    len--;
    while (len >= 0 && fullPath[len] != '/')
    {
        len--;
    }
    char buffer[fullPath.size()];
    std::size_t length = fullPath.copy(buffer,len,0);
    buffer[length]='\0';
    return string(buffer);
    
}
void Delete::RemoveAllPath(std::string path)
{
    struct stat stat_info;
    std::string path_plus;
    if(stat(path.c_str(),&stat_info) < 0 )
    {
        status = 2;
        return ;
    }
    if (stat_info.st_mode & S_IFREG)
    {
        if(stat(PatentOfFile(path).c_str(),&stat_info) < 0) 
        {
            status = 2;
            return ;
        }
        if (((stat_info.st_mode & S_IRWXU) == S_IRWXU) && stat_info.st_mode & S_IWOTH ) 
            my_remove(path);
        else 
            status = 1;
        return ;
    }

    DIR *dir = opendir(path.c_str());
    if (dir == NULL) {
        status = 2;
        return ;
    }
    if (!(((stat_info.st_mode & S_IRWXU) == S_IRWXU) && stat_info.st_mode & S_IWOTH))
    {
        status = 1;
        return ;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_DIR)
        {
            if (std::strcmp(entry->d_name  , ".") && std::strcmp(entry->d_name ,"..") )
            {
                path_plus = path + "/"+entry->d_name;
                RemoveAllPath(path_plus);
            }
        }
        else
        {
            std::string filePath = std::string(path) + "/" + entry->d_name;
            stat(path_plus.c_str(),&stat_info);
            my_remove(filePath );

        }
    }
    closedir(dir);
    my_remove(path);
}

Delete::~Delete()
{
}