#include "../../hpp/Commands.hpp"

int part(int id, std::vector<struct pollfd> &pfd, std::vector<Client> &usr, std::string data)
{
    std::string channel;
    std::string message;
    std::string message2;
    std::vector<Client> chan_usrs;

    if (usr[id - 1].getNickStat() == 0 || usr[id - 1].getNameStat() == 0) {
        message = "You have not a nick or username!\r\n";
        SendMessage(message, pfd[id].fd);
        return 0;
    }

    if (data.find(' ') == std::string::npos) {
        message = ":ircserv 461 " + usr[id - 1].getNick() + " PART :Not enough parameters\r\n";
        SendMessage(message, pfd[id].fd);
        return 0;
    }

    size_t pos = data.find(' ');
    channel = data.substr(0, pos);
    channel.erase(channel.begin());
    data.erase(0, pos + 1);

    if (channel.empty()) {
        message = ":ircserv 403 " + usr[id - 1].getNick() + " :No such channel\r\n";
        SendMessage(message, pfd[id].fd);
        return 0;
    }
    size_t i;
    for (i = 0; i < usr.size(); ++i)
	{
        if (usr[i].getChannel() == channel)
		break;
    }

    if (i == usr.size())
	{
        message = ":ircserv 403 " + usr[id - 1].getNick() + " " + channel + " :No such channel\r\n";
        SendMessage(message, pfd[id].fd);
        return 0;
    }

	if (usr[id - 1].getChannel() != channel)
	{
		message = ":ircserv 442 " + usr[id - 1].getNick() + " " + channel + " :You are not on that channel\r\n";
		SendMessage(message, pfd[id].fd);
		return 0;
	}

    std::string partMessage = ":" + usr[id - 1].getNick() + "! PART #" + channel + "\r\n";
    chan_usrs.clear();
    bool isOpr = usr[id - 1].getIsOpr();
	for (size_t i = 0; i < usr.size(); ++i)
	{
		if (usr[i].getChannel() == channel)
		{
			if (usr[i].getNick() != usr[id - 1].getNick())
			{
				chan_usrs.push_back(usr[i]);
				if (isOpr && !usr[i].getIsOpr())
				{
					usr[i].setIsOpr(1);
					isOpr = false;
				}
			}
			SendMessage(partMessage, pfd[i + 1].fd);
		}
	}
	usr[id - 1].setChannel("");
	message2 = ":ircserv 331 " + usr[id - 1].getNick() + " #" + channel + "\r\n";
	if (!chan_usrs.empty())
		message2 += ":ircserv 353 " + usr[id - 1].getNick() + " = #" + channel + " :@";
	if (chan_usrs.size() == 1)
		usr[id - 1].setIsOpr(1);
	for (size_t i = 0; i < chan_usrs.size(); ++i)
	{
		message2 += chan_usrs[i].getNick();
		if (i == chan_usrs.size() - 1)
			message2 += "\r\n";
		else
			message2 += " ";
	}
	message2 += ":ircserv 366 " + usr[id - 1].getNick() + " #" + channel + " :End of /Names list\r\n";
	for (unsigned long j = 0; j < usr.size(); j++)
		SendMessage(message2, pfd[j+1].fd);
	return 0;
}
