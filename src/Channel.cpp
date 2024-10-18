#include "../hpp/Commands.hpp"

std::vector<Channel> channels;

void setChannelPassword(const std::string &channelName, const std::string &password) {
    for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it) {
        if (it->name == channelName) {
            it->password = password;
            std::cout << "Password for channel " << channelName << " set to " << password << "\n";
            return;
        }
    }
	
    Channel newChannel;
    newChannel.name = channelName;
    newChannel.password = password;
    channels.push_back(newChannel);
    std::cout << "New channel " << channelName << " created with password " << password << "\n";
}

std::string getChannelPassword(const std::string &channelName) {
    for (std::vector<Channel>::const_iterator it = channels.begin(); it != channels.end(); ++it) {
        if (it->name == channelName) {
            return it->password;
        }
    }
    return "";
}
