/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Post.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onaciri <onaciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:09:48 by onaciri           #+#    #+#             */
/*   Updated: 2024/03/03 18:20:50 by onaciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_HPP
#define POST_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <map>
#include <vector>
#include <fstream>
#include <bits/stdc++.h> 
#include "Method.hpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Get.hpp"

class Post : public Method
{
    private:
        /*function*/
		void mimeType();
    private:
        /* data */
        
		int crfile;
        int error;
		int MethodType;
        int special;
        int rare;
        size_t left_over;
        int chunk_ctl;
		size_t size_len;
        size_t total_Body;
        size_t pre_total_body;
        size_t chunk_left;
        int find_sep;
        int file_hang;
        int is_first;
        int here_is;
        int first_time;
        int enter_cgi;
        std::string post_dir;
        std::string the_file;
        std::string buffer;
        std::string buff_chunk;
        std::string content_type;
		std::map<std::string, std::string> mime;
		std::fstream outFile;
        std::fstream out;
        std::string sep;
        std::string sep_end;
        std::string sep_found;
        time_t start_time; 
        int pid;
        int exit_status;
        int first_run;
        int error_time;
        std::string ran_file;
        int cgi_exe;
        std::string my_root;
        std::string name_of_script;
        int time_out;
        char **cmd;
        char **env;
        int add_i;
        std::vector<std::string> name_bound;

        
        Get get;
        
    public:
        Post();
        Post(const Post& post);
        Post& operator=(const Post& post);
        ~Post();

        std::string creat_file_name(int ret);
        char **set_cmd(std::string& ext_path);
        char **set_env();
        int process(std::string body, int event);
		void openFile(std::string body);
		void normalFile(std::string body);
        
        void chunked_file(std::string body);
        void chunk_write(std::string body);

        void    ft_boundary(std::string& body);

        void    exe_cgi();
        std::string add_new_name(std::string name, std::string mime);
        std::string find_ext();
        void script_name();

        void ft_error();
        int is_num(std::string name);



};


#endif