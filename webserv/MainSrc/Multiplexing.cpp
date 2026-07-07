/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiplexing.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:04:44 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/29 16:30:35 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Multiplexing.hpp"

Multiplexing::Multiplexing(std::string  configfile)
{
    server.TakeAndParce(configfile);
    if(server.msockets.empty())
    {
        throw "Error : Problem in create servers \n";
    }
    SocketTimeout = 5;
}

Multiplexing::~Multiplexing()
{
}

void Multiplexing::CloseClient(int & n)
{
    epoll_ctl(epollfd,EPOLL_CTL_DEL,events[n].data.fd,&ev);
    close(events[n].data.fd);
    mClients.erase(events[n].data.fd);
}
bool Multiplexing::CheckTimeOut(int n)
{
    clock_t CurrentTime = clock();
    string ress;
    if (mClients[events[n].data.fd].body_state)
        return 1;
    if(( double(CurrentTime - mClients[events[n].data.fd].startTime) / CLOCKS_PER_SEC  ) > SocketTimeout)
    {
        mClients[events[n].data.fd].get_timeout.serv.status = "408";
        mClients[events[n].data.fd].get_timeout.get(mClients[events[n].data.fd].get_timeout.serv.error_page["408"]);
        ress = mClients[events[n].data.fd].get_timeout.respons;
         ssize_t bytesWritten = write(events[n].data.fd ,ress.c_str(), ress.size());
        if(bytesWritten <= 0 || mClients[events[n].data.fd].get_timeout.end)
            CloseClient(n);
        return 0;
    }
    return 1;
}
void Multiplexing::Out_Events(int n)
{
     
    if(CheckTimeOut(n))
    {
        mClients[events[n].data.fd].process_req(string(""),EPOLLOUT);
        string res = mClients[events[n].data.fd].get_respons();
        if (!res.size())
            return ;
        ssize_t bytesWritten = write(events[n].data.fd , res.c_str(), res.size());

        if (bytesWritten <= 0 || mClients[events[n].data.fd].resp_done())
        {
            CloseClient(n);
        }
    }


}

void Multiplexing::In_Events(int n)
{
    char buffer[1024];
    ssize_t bytesRead = 0;

    bytesRead = recv(events[n].data.fd,buffer,1024,0);
    if (bytesRead <= 0) 
    {
        CloseClient(n);
    }
    else 
    {
        std::map<int ,Request >::iterator iter2 = mClients.find(events[n].data.fd);
        if (iter2 != mClients.end())
        {
            mClients[events[n].data.fd].process_req(string("").append(buffer, bytesRead),EPOLLIN);
        }
    }
}

void Multiplexing::Connect_And_Add(int n)
{
    int adrlen;
    std::map<int, vector<Servers> >::iterator iter = server.msockets.find(events[n].data.fd );
    if (iter != server.msockets.end()) 
    {   
        adrlen = sizeof(iter->second[0].address);
        conn_sock = accept(iter->first, (struct sockaddr *)&iter->second[0].address, (socklen_t*)&adrlen);
        if (conn_sock == -1)
        {
            perror("accept");
            return ;
        }

        Request req(iter->second);
        mClients[conn_sock] = req;    
        mClients[conn_sock].startTime = clock();
        ev.events = EPOLLIN | EPOLLOUT |  EPOLLRDHUP;
        ev.data.fd = conn_sock;

        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock,&ev) == -1)
        {
            perror("epoll_ctl : accept connection");
        }
    } 
    else 
    {
        if(events[n].events &  EPOLLRDHUP)
            CloseClient(n);
        else if (events[n].events & EPOLLIN && !(mClients[events[n].data.fd].error)) 
        {
            In_Events(n);
            mClients[events[n].data.fd].startTime = clock();
        }
        else if (events[n].events & EPOLLOUT && mClients.find(events[n].data.fd) !=  mClients.end()) 
            Out_Events(n);
    }
}


void Multiplexing::CreatMUltiplex()
{
    std::map<int,vector<Servers> >::iterator iter;
    epollfd = epoll_create(1);
    if (epollfd == -1) {
        perror("epoll_create");
        exit(EXIT_FAILURE);
    }
    for (iter = server.msockets.begin(); iter != server.msockets.end(); iter++)
    {
            ev.events = EPOLLIN;
            ev.data.fd = iter->first;
            if (epoll_ctl(epollfd, EPOLL_CTL_ADD, iter->first, &ev) == -1) 
            {
                perror("epoll_ctl: listen_sock");
            }
    }
    while (true)
    {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
        }
        for (int n = 0; n < nfds ; ++n) 
        {
            Connect_And_Add(n);
        }
       
    }
}