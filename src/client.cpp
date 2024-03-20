#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>

struct message
{
	std::string author;
	std::string content;
};

struct client_state
{
	std::string own_name;
	std::vector<message> messages;
};

void refresh_app(client_state const& state)
{
	clear();
	wborder(stdscr, 0, 0, 0, 0, 0, 0, 0, 0);
	move(1, 1);
	addstr("Name: ");
	addstr(state.own_name.c_str());
	refresh();
}

void update_state(int input, client_state &state)
{
	if (('a' <= input && input <= 'z') || ('A' <= input && input <= 'Z') || ('0' <= input && input <= '9'))
		state.own_name.push_back(input);
	int s = state.own_name.size();
	if (s > 0 && input == 127)
	{
		state.own_name.resize(s-1);
		//std::cout << "woah" << std::endl;
	}
}

void app_loop()
{
	client_state state;
	refresh_app(state);
	while (true)
	{
		int c = getch();
		//std::cout << c << std::endl;
		if (c == '\e') break;
		update_state(c, state);
		refresh_app(state);
	}
}

int main()
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);

	app_loop();

	endwin();
}