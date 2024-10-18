#include "../../hpp/Commands.hpp"

int kick(int id, std::vector<struct pollfd> &pfd, std::vector<Client> &usr, std::string data)
{
	size_t i;
    std::string channel;
    std::string nick;
    std::string message;
	std::string message2;
	std::string partMessage;
    std::vector<Client> chan_usrs;

    if(usr[id - 1].getNickStat() == 0 || usr[id - 1].getNameStat() == 0)
	{
        message = "You have not a nick or username!\r\n";
        SendMessage(message, pfd[id].fd);
        return 0;
    }

    if (data.find(' ') == std::string::npos)
	{
        message = ":ircserv 411 " + usr[id - 1].getNick() + " :No recipient given (KICK)\r\n";
        SendMessage(message, pfd[id].fd);
        return 0;
    }

    size_t pos = data.find(' ');
    channel = data.substr(0, pos);
    channel.erase(channel.begin());

    data.erase(0, pos + 1);
    nick = data.substr(0, data.find(' '));

    if (nick.empty())
	{
        message = ":ircserv 412 " + usr[id - 1].getNick() + " :Cannot send! [no text]\r\n";
        SendMessage(message, pfd[id].fd);
        return 0;
    }

    for (i = 0; i < usr.size(); ++i)
	{
        if (usr[i].getNick() == nick)
		break;
    }

    if (i == usr.size())
	{
        message = ":ircserv 476 " + usr[id - 1].getNick() + " " + channel + " :Channel Mask is not valid!\r\n";
        SendMessage(message, pfd[id].fd);
        return 0;
    }

    if (usr[i].getChannel() != channel)
	{
        message = ":ircserv 441 " + usr[id - 1].getNick() + " " + channel + " :User not found on this channel\r\n";
        SendMessage(message, pfd[id].fd);
        return 0;
    }

    if (usr[id - 1].getChannel() != channel)
	{
        message = ":ircserv 442 " + usr[id - 1].getNick() + " " + channel + " :You are not included in this channel!\r\n";
        SendMessage(message, pfd[id].fd);
        return 0;
    }

    if (usr[id - 1].getIsOpr() == 0) {
        message = ":ircserv 482 " + usr[id - 1].getNick() + " " + channel + " :You don't have operator permissions!\r\n";
        SendMessage(message, pfd[id].fd);
        return 0;
    }
	else
	{
        partMessage = ":" + nick + "! PART #" + channel + "\r\n";
        chan_usrs.clear();
        bool isOpr = usr[id - 1].getIsOpr();
        for (size_t i = 0; i < usr.size(); ++i)
		{
            if (usr[i].getChannel() == channel)
			{
                if (usr[i].getNick() != nick)
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
        usr[i].setChannel("");
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
        {
            SendMessage(message2, pfd[j+1].fd);
		}
		return 0;
	}
}
