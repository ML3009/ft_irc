#include "irc.hpp"

int main(int ac, char **av){

	try{
		try_args(ac, av);
	}
	catch (const std::exception &e){
		std::cout << e.what() << std::endl;
	}
	return 0;
}

