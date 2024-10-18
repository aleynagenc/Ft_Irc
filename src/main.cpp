#include "../hpp/Channel.hpp"

string g_PASS;
int main( int ac, char* av[] )
{
	if (ac == 3)
	{
		try
		{
			int port = atoi(av[1]);
			string passw(av[2]);
			g_PASS = passw;
			Server serv(port, av[2]);

			if ( serv.sockStart() == -1 )
				return 1;
			if ( serv.sockScan() == -1 )
				return 1;
		}
		catch ( const std::exception &e )
		{
			cerr << RED << e.what() << endl <<
				"Port must be between : 1024 - 65535" << RESET << endl;
			exit(1);
		}
	}
	else
	{
		cerr << RED << "Missing or More Arguments!" << endl << YLW <<
			"Please Type This Format:"<< endl << CYN <<"./ircserv <port> <servPass>" << RESET << endl;
	}
	 return 0;
}
