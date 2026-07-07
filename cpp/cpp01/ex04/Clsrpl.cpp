#include "Clsrpl.hpp"

Clsrpl::Clsrpl(std::string f_n, std::string _s1, std::string _s2)
{
	file_name = f_n;
	s1 = _s1;
	s2 = _s2;
}

void	Clsrpl::open_infile()
{
	In_file.open(file_name.c_str(), std::ios::in);
	if (!In_file){
		std::cout<<file_name<<" : cant opening"<<"\n";
		exit(1) ;
	}
	if (!std::getline(In_file,Line)){
		std::cout<<file_name<<" : is empty"<<"\n";
		exit (1);
	}
}

void	Clsrpl::open_outfile()
{
	Out_file.open((file_name+".replace").c_str(), std::ios::out);
	if (!Out_file){
		std::cout<<file_name+".replace"<<" : cant opening"<<"\n";
		exit(1) ;
	}
}

void	Clsrpl::replace()
{
	size_t	pos;
	
	open_infile();
	open_outfile();
	while (1)
	{
		pos = Line.find(s1);
		while (pos != std::string::npos)
		{
			Line.erase(pos, s1.length());
			Line.insert(pos, s2);
			pos = Line.find(s1, pos+s2.length());
		}
		Out_file<<Line<<"\n";
		if (!std::getline(In_file,Line))
			break;
	}
	In_file.close();
	Out_file.close();
}
