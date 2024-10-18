#include "../../hpp/Commands.hpp"

int help(int id, std::vector<struct pollfd> &pfd, std::vector<Client> &usr,std::string data)
{
	std::string message;

	(void)usr;
	(void)data;
	message = "[ FT_IRC COMMAND LIST ]\n"
			"NICK: Change a nickname -> NICK newNickName\n"
			"QUIT: Disconnect from server -> QUIT q\n"
			"PART: Leave a channel -> PART #chnlName\n"
			"PING: Ping the server -> PING :server\n"
			"JOIN: Join a any channel -> JOIN #channel\n"
			"PASS: Set server password -> PASS your_password\n"
			"USER: Set the user's username -> USER username\n"
			"WHO: List users matching given criteria -> WHO #channel\n"
			"MODE: Change channel modes -> MODE #channel +k password\n"
			"KICK: Kick a user in your channel -> KICK #chnlName nickname\n"
			"NOTICE:  Send a notice to a user or a channel -> NOTICE nickName #chnlName :msg\n"
			"PRIVMSG: Send message to any user or channel -> PRIVMSG nickName #chnlName :msg\n";
	SendMessage(message, pfd[id].fd);

	return 0;
}
