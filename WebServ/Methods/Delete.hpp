/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Delete.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:49:58 by abouassi          #+#    #+#             */
/*   Updated: 2024/02/01 09:26:30 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETE_HPP
#define DELETE_HPP

#include <stdio.h>
#include <dirent.h>
#include <iostream>
#include<cstring>
#include "Method.hpp"
#include "../MainSrc/ParceConf.hpp"
class Delete : public Method
{
    bool deleted;
    int  my_remove(std::string file);
    int status;
    int process(string body, int event) ;
    void RemoveAllPath(std::string path);
    Get get;
public:
    Delete();
    ~Delete();
};

#endif