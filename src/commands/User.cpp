#include "../hpp/Commands.hpp"

int username(int id, std::vector<struct pollfd> &pfd, std::vector<Client> &usr, std::string data)
{
	std::string my_data = data;
	std::string message;

	if (my_data.length() == 0 || usr[id - 1].getNickStat() == 0)
	{
		message = "Please first fill the Nickname!\r\n";
		SendMessage(message, pfd[id].fd);
		return 0;
	}
	usr[id - 1].setNameStat(1);
	usr[id - 1].setName(my_data);
	usr[id - 1].getReply() = ":" + usr[id - 1].getNick() + "!" + usr[id - 1].getName() + "@127.0.0.1";
	message = ":ircserv 001 " + usr[id - 1].getNick() + " [ Welcome To The Internet Relay Chat Server ] " + usr[id - 1].getReply() + "\r\n";
	SendMessage(message, pfd[id].fd);
	return 0;
}
