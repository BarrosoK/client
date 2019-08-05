#include <iostream>
#include "Client.h"

int main(int ac, char **av)
{
	std::vector<std::pair<int, int>> fdp;
	fdp.push_back(std::make_pair(1, 1));
	if (ac < 3) {
		std::cerr << "Syntax : ./client <host name> <port>" << std::endl;
		return 0;
	}

	Client client(av[1], atoi(av[2]));

	return 0;
}