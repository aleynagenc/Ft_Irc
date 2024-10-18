#include "../../hpp/Commands.hpp"

int nickname(int id, std::vector<struct pollfd> &pfd, std::vector<Client> &usr, std::string data)
{
    std::string my_data = data;
    std::string message;
    int i = 0;

    if (my_data.length() == 0)
	{
		message = "Please fill the Nickname!\r\n";
		SendMessage(message, pfd[id].fd);
		return 0;
	}
	while (i < id - 1)
	{
		if (usr[i].getNick() == my_data)
		{
			message = ":ircserv 433 \n[" + my_data + "]This nickname is used!\nNickname automatically assigned\r\n";
			SendMessage(message, pfd[id].fd);
			return 0;
		}
		i++;
	}
	if (usr[id - 1].getNickStat() == 0)
	{
		usr[id - 1].setNick(my_data);
		usr[id - 1].setNickStat(1);
		return 0;
	}
	if( usr[id - 1].getNickStat() == 1 )
	{
		message = "Your already have a Nickname..\r\n";
		SendMessage(message, pfd[id].fd);
		return 0;
	}
    return 0;
}
