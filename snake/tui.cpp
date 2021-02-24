#include "tui.h"
#include <termios.h>
#include <stdio.h>
#include <sys/ioctl.h>

void tui::clear_screen() {
	printf("\e[H");
	printf("\e[J");
}

void tui::draw_hor_line(struct winsize ws) {
	for (int i = 0; i < ws.ws_col; i++) {
		printf("%c", '-');
	}
}
void tui::draw_ver_lines(struct winsize ws) {
	for (int i = 0; i < ws.ws_row; i++) {
		printf("%c", '|');
		printf("\e[%dC",ws.ws_col);
		printf("%c", '|');
		printf("\e[1E");
	}
}

tui::tui() {
	setbuf(stdout, NULL);
}

void tui::draw() {//вызываем методы clear_screen
	clear_screen();
	struct winsize ws;
	ioctl(0, TIOCGWINSZ, &ws);
	draw_hor_line(ws);
	printf("\e[1E");
	draw_ver_lines(ws);
	draw_hor_line(ws);
}




void tui::run() {//пауза, ждёт нажатия клавиши



}
