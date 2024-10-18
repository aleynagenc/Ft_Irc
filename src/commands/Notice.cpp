#include "../../hpp/Commands.hpp"

int notice(int id, std::vector<struct pollfd> &pfd, std::vector<Client> &usr,std::string data)
{
	std::string message;
	int i = -1;
	int cliOfNbr;

	if( usr[id - 1].getNickStat() == 0 || usr[id - 1].getNameStat() == 0 )
	{
		message = "You have not a nick or username!\r\n";
		SendMessage(message, pfd[id].fd);
		return 0;
	}
	
	cliOfNbr = pfd.size();
	message = usr[id - 1].getNick() + " Send a message to everyone: " + data + "\r\n";
	while(++i <= cliOfNbr - 1)
		SendMessage(message, pfd[i].fd);
	return 0;
}
