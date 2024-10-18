#include "../../hpp/Commands.hpp"

int quit(int id, std::vector<struct pollfd> &pfd, std::vector<Client> &usr,std::string data)
{
	std::string message;

	(void)usr;
	(void)data;
	message = "BYE BYE.. :(\r\n";
	SendMessage(message, pfd[id].fd);
	close(pfd[id].fd);

	return 0;
}
