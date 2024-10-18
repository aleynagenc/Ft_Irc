#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../hpp/ircserv.hpp"
#include "../hpp/Client.hpp"
#include "../hpp/Server.hpp"
#include <string>
#include <vector>

struct Channel {
    std::string name;
    std::string password;
};

extern std::vector<Channel> channels;
void setChannelPassword(const std::string &channelName, const std::string &password);
std::string getChannelPassword(const std::string &channelName);

#endif
