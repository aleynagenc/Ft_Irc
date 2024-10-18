#include "../../hpp/Commands.hpp"

int who(int id, std::vector<struct pollfd> &pfd, std::vector<Client> &usr, std::string data)
{
    std::string channel;
    std::string message;

    size_t pos = data.find(' ');
    if (pos != std::string::npos) {
        channel = data.substr(0, pos);
        data.erase(0, pos + 1);
    }
	else
        channel = data;

    if (channel[0] != '#') {
        message = ":ircserv 461 " + usr[id - 1].getNick() + " WHO :Not enough parameters\r\n";
        SendMessage(message, pfd[id].fd);
        return 0;
    }

    bool channelExists = false;
    for (size_t i = 0; i < usr.size(); ++i)
	{
        if (usr[i].getChannel() == channel.substr(1))
		{
            channelExists = true;
            message = ":ircserv 352 " + usr[id - 1].getNick() + " " + channel + " " + usr[i].getName() + " " + "localhost" + " ircserv " + usr[i].getNick() + " H :0 " + usr[i].getFullName() + "\r\n";
            SendMessage(message, pfd[id].fd);
        }
    }

    if (!channelExists)
	{
        message = ":ircserv 403 " + usr[id - 1].getNick() + " " + channel + " :No such channel\r\n";
        SendMessage(message, pfd[id].fd);
    }
	else
	{
        message = ":ircserv 315 " + usr[id - 1].getNick() + " " + channel + " :End of WHO list\r\n";
        SendMessage(message, pfd[id].fd);
    }

    return 0;
}
