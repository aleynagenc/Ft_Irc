#include "../../hpp/Commands.hpp"

int mode(int /*id*/, std::vector<struct pollfd> &/*pfd*/, std::vector<Client> &/*usr*/, std::string data) {
    std::string channel;
    std::string mode;
    std::string password;

    size_t pos = data.find(' ');
    if (pos == std::string::npos) {
        std::cout << "Invalid command format!\n";
        return 0;
    }
    channel = data.substr(0, pos);

    if (channel[0] != '#') {
        std::cout << "Invalid channel name: " << channel << std::endl;
        return 0;
    }

    data.erase(0, pos + 1);
    pos = data.find(' ');
    if (pos == std::string::npos) {
        std::cout << "Invalid command format! \n";
        return 0;
    }
    mode = data.substr(0, pos);
    if (mode == "-k") {
        setChannelPassword(channel.substr(1), "");
        return 0;
    }
    if (mode != "+k") {
        std::cout << "Invalid mode: " << mode << std::endl;
        return 0;
    }

    data.erase(0, pos + 1);
    password = data;
    setChannelPassword(channel.substr(1), password);

    return 1;
}
