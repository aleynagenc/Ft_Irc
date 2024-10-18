#include "../../hpp/Commands.hpp"

int join(int id, std::vector<struct pollfd> &pfd, std::vector<Client> &usr, std::string data) {
    std::string channel_join;
    std::string nick;
    std::string message;
    std::string message2;
    std::vector<Client> chan_usrs;
    size_t i;

    if (usr[id - 1].getNickStat() == 0 || usr[id - 1].getNameStat() == 0) {
        message = "You have not a nick or username!\r\n";
        SendMessage(message, pfd[id].fd);
        return 0;
    }

    i = 0;
    while (data[0] == ' ')
        data.erase(data.begin());

    if (data.find('#') != 0) {
        message = "475 " + usr[id - 1].getNick() + usr[id - 1].getData() + " :Cannot join channel\r\n";
        SendMessage(message, pfd[id].fd);
        return 0;
    }

    size_t pos = data.find(' ');
    if (pos != std::string::npos) {
        channel_join = data.substr(1, pos - 1);
        std::string userPassword = data.substr(pos + 1);

        std::string correct_password = getChannelPassword(channel_join);
        if (!correct_password.empty() && userPassword != correct_password) {
            message = "Incorrect password. Please try again.\r\n";
            SendMessage(message, pfd[id].fd);
            return 0;
        }
    } else {
        channel_join = data.substr(1);
        std::string correct_password = getChannelPassword(channel_join);
        if (!correct_password.empty()) {
            message = "This channel is password protected. Please enter the password.\r\n";
            SendMessage(message, pfd[id].fd);
            return 0;
        }
    }

    for (i = 0; i < usr.size(); ++i) {
        if (usr[i].getChannel() == channel_join && usr[i].getNick() == usr[id - 1].getNick()) {
            message = "You are already on the channel.\r\n";
            SendMessage(message, pfd[id].fd);
            return 0;
        }
    }

    usr[id - 1].setChannel(channel_join);
    i = 1;
    message = usr[id - 1].getReply() + " JOIN #" + channel_join + "\r\n";
    while (i < pfd.size()) {
        if (usr[i - 1].getChannel() == channel_join) {
            SendMessage(message, pfd[i].fd);
            chan_usrs.push_back(usr[i - 1]);
        }
        ++i;
    }

    message2 = ":ircserv 331 " + usr[id - 1].getNick() + " #" + channel_join + " \r\n";
    if (!chan_usrs.empty())
        message2 += ":ircserv 353 " + usr[id - 1].getNick() + " = #" + channel_join + " :@";
    if (chan_usrs.size() == 1)
        usr[id - 1].setIsOpr(1);
    i = 0;
    while (i < chan_usrs.size()) {
        message2 += chan_usrs[i].getNick();
        if (i == chan_usrs.size() - 1)
            message2 += "\r\n";
        else
            message2 += " ";
        ++i;
    }
    message2 += ":ircserv 366 " + usr[id - 1].getNick() + " #" + channel_join + " :End of /Names list\r\n";
    SendMessage(message2, pfd[id].fd);
    return 0;
}
