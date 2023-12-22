#include "irc.hpp"

bool handleSignal = false;
bool msg_const = false;

int main(int ac, char **av){

	try{
		try_args(ac, av);
		std::signal(SIGINT, handle_signal);
		server Server(atoi(av[1]), std::string(av[2]));
		Server.init_server();

		while (!handleSignal){
			Server.run_server();
		}
	}
	catch (const std::exception &e){
		std::cout << e.what() << std::endl;
	}
	return 0;
}

