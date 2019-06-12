#include <mutex>
#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstdint>

extern "C" {
#include <linux/input.h>
}

struct point 
{
	int x;
	int y;
};

inline int read_event(input_event &event) {
	return std::fread(&event, sizeof(input_event), 1, stdin) == 1;
}

inline void write_event(const input_event &event) {
	if (std::fwrite(&event, sizeof(input_event), 1, stdout) != 1)
		std::exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 7)
        return std::fprintf(
                   stderr,
                   "usage: %s <x res> <y res> <output display x-offset> <output display y-offset> <x pos> <y pos>\n",
                   argv[0]),
               EXIT_FAILURE;

    std::setbuf(stdin, nullptr), std::setbuf(stdout, nullptr);

    const point mon_rect       = {std::stoi(argv[1]), std::stoi(argv[2])};
    const point display_offset = {std::stoi(argv[3]), std::stoi(argv[4])};
    point mouse_pos            = {std::stoi(argv[5]), std::stoi(argv[6])};
    input_event input;

    while (read_event(input)) {
	// input.code == 1 is y axis, 0 is x axis. type 2 is mouse movements & scrollwheel events
	if (input.type == 2) {
		if (input.code == 1) {
			int movement = mouse_pos.y + input.value;
			if (movement < mon_rect.y+display_offset.y && movement > display_offset.y) {
				write_event(input);
				mouse_pos.y += input.value;
			}
		}
		if (input.code == 0) {
			int movement = mouse_pos.x + input.value;
			if (movement < mon_rect.x+display_offset.x && movement > display_offset.x) {
				write_event(input);
				mouse_pos.x += input.value;
			}
		}
		else
			write_event(input);
	}
	else 
		write_event(input);
    }
}

