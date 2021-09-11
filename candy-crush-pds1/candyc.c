#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

#define NUM_TYPES 4
#define N_LINHAS 9
#define N_COLS 6

#define TRIANGULO 1
#define RETANGULO 2
#define CIRCULO 3
#define ROUNDED_R 4

#define SCREEN_W 480
#define SCREEN_H 640
#define INFO_H 64
#define FPS 1
#define MARGIN 5

typedef struct Candy
{
	int type;
	int offset_lin;
	int offset_col;
	int active;
	ALLEGRO_COLOR cor;
} Candy;

Candy M[N_LINHAS][N_COLS];
ALLEGRO_COLOR colors[NUM_TYPES + 1];

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

const float CELL_W = (float)SCREEN_W / N_COLS;
const float CELL_H = (float)(SCREEN_H - INFO_H) / N_LINHAS;

int score = 0, plays = 1;
char PONTUACAOJOGADOR[100], PLAYSJOGADOR[100];

ALLEGRO_FONT *size_f;

void musicaRecorde()
{
	Beep(660, 100);
	Sleep(150); //Beep que faz a emissão do som e Sleep para esperar um tempo para o outro som ser emitido.
	Beep(660, 100);
	Sleep(200);
	Beep(660, 100);
	Sleep(200);
	Beep(510, 100);
	Sleep(50);
	Beep(660, 100);
	Sleep(200);
	Beep(770, 100);
	Sleep(400);
	Beep(380, 100);
	// Sleep(575);
	// Beep(510, 100);
	// Sleep(450);
	// Beep(380, 100);
	// Sleep(400);
	// Beep(320, 100);
	// Sleep(500);
	// Beep(440, 100);
	// Sleep(300);
	// Beep(480, 80);
	// Sleep(330);
	// Beep(450, 100);
	// Sleep(150);
	// Beep(430, 100);
	// Sleep(300);
	// Beep(380, 100);
	// Sleep(200);
	// Beep(660, 80);
	// Sleep(200);
	// Beep(760, 50);
	// Sleep(150);
	// Beep(860, 100);
	// Sleep(300);
	// Beep(700, 80);
	// Sleep(150);
	// Beep(760, 50);
	// Sleep(350);
	// Beep(660, 80);
	// Sleep(300);
	// Beep(520, 80);
	// Sleep(150);
	// Beep(580, 80);
	// Sleep(150);
	// Beep(480, 80);
	// Sleep(500);
	// Beep(510, 100);
	// Sleep(450);
	// Beep(380, 100);
	
}

int novoRecorde(int score, int *record)
{
	FILE *arq = fopen("recorde.txt", "r");
	*record = -1;
	if (arq != NULL)
	{
		fscanf(arq, "%d", record);
		fclose(arq);
	}
	if (*record < score)
	{
		musicaRecorde();
		arq = fopen("recorde.txt", "w");
		fprintf(arq, "%d", score);
		fclose(arq);
		return 1;
	}
	return 0;
}

int generateRandomCandy()
{
	return rand() % NUM_TYPES + 1;
}

void imprimeMatriz()
{
	printf("\n");
	int i, j;
	for (i = 0; i < N_LINHAS; i++)
	{
		for (j = 0; j < N_COLS; j++)
		{
			printf("%d (%d,%d) ", M[i][j].type, M[i][j].offset_lin, M[i][j].active);
		}
		printf("\n");
	}
}

void completaMatriz()
{
	int i, j;
	for (i = 0; i < N_LINHAS; i++)
	{
		for (j = 0; j < N_COLS; j++)
		{
			if (M[i][j].type == 0)
			{
				M[i][j].type = generateRandomCandy();
				M[i][j].offset_col = 0;
				M[i][j].offset_lin = 0;
				M[i][j].active = 1;
				M[i][j].cor = colors[M[i][j].type];
			}
		}
	}
}

void startGame()
{
	int i, j;
	for (i = 0; i < N_LINHAS; i++)
	{
		for (j = 0; j < N_COLS; j++)
		{
			M[i][j].type = generateRandomCandy();
			M[i][j].offset_col = 0;
			M[i][j].offset_lin = 0;
			M[i][j].active = 1;
			M[i][j].cor = colors[M[i][j].type];
			printf("%d ", M[i][j].type);
		}
		printf("\n");
	}
}

void pausa()
{
	al_stop_timer(timer);
	al_rest(3);
	al_start_timer(timer);
}

void draw_candy(int lin, int col)
{

	int cell_x = CELL_W * col;
	int cell_y = INFO_H + CELL_H * lin;

	if (M[lin][col].type == TRIANGULO)
	{
		al_draw_filled_triangle(cell_x + MARGIN, cell_y + CELL_H - MARGIN,
								cell_x + CELL_W - MARGIN, cell_y + CELL_H - MARGIN,
								cell_x + CELL_W / 2, cell_y + MARGIN,
								M[lin][col].cor);
	}
	else if (M[lin][col].type == RETANGULO)
	{
		al_draw_filled_rectangle(cell_x + 2 * MARGIN, cell_y + 2 * MARGIN,
								 cell_x - 2 * MARGIN + CELL_W, cell_y - 2 * MARGIN + CELL_H,
								 M[lin][col].cor);
	}
	else if (M[lin][col].type == ROUNDED_R)
	{
		al_draw_filled_rounded_rectangle(cell_x + MARGIN, cell_y + MARGIN,
										 cell_x - MARGIN + CELL_W, cell_y - MARGIN + CELL_H,
										 CELL_W / 3, CELL_H / 3, M[lin][col].cor);
	}
	else if (M[lin][col].type == CIRCULO)
	{
		al_draw_filled_ellipse(cell_x + CELL_W / 2, cell_y + CELL_H / 2,
							   CELL_W / 2 - MARGIN, CELL_H / 2 - MARGIN,
							   M[lin][col].cor);
	}
}

void draw_scenario()
{

	ALLEGRO_COLOR BKG_COLOR = al_map_rgb(0, 0, 0);
	al_set_target_bitmap(al_get_backbuffer(display));
	al_clear_to_color(BKG_COLOR);

	sprintf(PONTUACAOJOGADOR, "Pontos: %d", score);
	al_draw_text(size_f, al_map_rgb(255, 255, 255), SCREEN_W - 200, INFO_H / 4, 0, PONTUACAOJOGADOR);
	sprintf(PLAYSJOGADOR, "Jogadas: %d", plays);
	al_draw_text(size_f, al_map_rgb(255, 255, 255), 10, INFO_H / 4, 0, PLAYSJOGADOR);

	int i, j;
	for (i = 0; i < N_LINHAS; i++)
	{
		for (j = 0; j < N_COLS; j++)
		{
			draw_candy(i, j);
		}
	}
}

int clearSequence(int li, int lf, int ci, int cf)
{
	int i, j, count = 0;
	for (i = li; i <= lf; i++)
	{
		for (j = ci; j <= cf; j++)
		{
			count++;
			M[i][j].active = 0;
			M[i][j].cor = colors[0];
		}
	}
	return count;
}

int processaMatriz()
{
	int i, j, k, count = 0;
	int current, seq, ultimo;

	for (i = 0; i < N_LINHAS; i++)
	{
		current = M[i][0].type;
		seq = 1;
		for (j = 1; j < N_COLS; j++)
		{
			if (current == M[i][j].type && current > 0)
			{
				seq++;
				if (j == N_COLS - 1 && seq >= 3)
					count += clearSequence(i, i, j - seq + 1, N_COLS - 1);
			}
			else
			{
				if (seq >= 3)
				{
					count += clearSequence(i, i, j - seq, j - 1);
				}
				seq = 1;
				current = M[i][j].type;
			}
		}
	}

	for (j = 0; j < N_COLS; j++)
	{
		current = M[0][j].type;
		seq = 1;
		for (i = 1; i < N_LINHAS; i++)
		{
			if (current == M[i][j].type && current > 0)
			{
				seq++;
				if (i == N_LINHAS - 1 && seq >= 3)
					count += clearSequence(i - seq + 1, N_LINHAS - 1, j, j);
			}
			else
			{
				if (seq >= 3)
				{
					count += clearSequence(i - seq, i - 1, j, j);
				}

				seq = 1;
				current = M[i][j].type;
			}
		}
	}

	return count;
}

void atualizaOffset()
{
	imprimeMatriz();
	int i, j, offset;

	for (j = 0; j < N_COLS; j++)
	{
		offset = 0;
		for (i = N_LINHAS - 1; i >= 0; i--)
		{
			M[i][j].offset_lin = offset;
			if (M[i][j].active == 0)
			{
				M[i][j].type = 0;
				offset++;
			}
		}
	}
}

void atualizaMatriz()
{
	int i, j, offset;

	for (j = 0; j < N_COLS; j++)
	{
		for (i = N_LINHAS - 1; i >= 0; i--)
		{
			offset = M[i][j].offset_lin;
			if (offset > 0)
			{
				M[i + offset][j].type = M[i][j].type;
				M[i + offset][j].active = M[i][j].active;
				M[i + offset][j].cor = M[i][j].cor;
				M[i][j].type = 0;
				M[i][j].active = 0;
				M[i][j].offset_lin = 0;
			}
		}
	}
	completaMatriz();
}

void getCell(int x, int y, int *lin, int *col)
{
	*lin = (y - INFO_H) / CELL_H;
	*col = x / CELL_W;
}

int distancia(int lin1, int col1, int lin2, int col2)
{
	return sqrt(pow(lin1 - lin2, 2) + pow(col1 - col2, 2));
}

void troca(int lin1, int col1, int lin2, int col2)
{
	Candy aux = M[lin1][col1];
	M[lin1][col1] = M[lin2][col2];
	M[lin2][col2] = aux;
	Beep(660, 100);
	Sleep(150);
	plays--;
}

int initializingRoutines() {
	if (!al_init())
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "failed to initialize primitives!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display)
	{
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	if (!al_install_mouse())
		fprintf(stderr, "failed to initialize mouse!\n");

	al_init_font_addon();
	al_init_ttf_addon();

	size_f = al_load_font("arial.ttf", 32, 1);

	event_queue = al_create_event_queue();
	if (!event_queue)
	{
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	al_install_keyboard();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_start_timer(timer);
}

int main(int argc, char **argv)
{

	initializingRoutines();

	colors[0] = al_map_rgb(0,248,0);
	colors[TRIANGULO] = al_map_rgb(151,235,219);
	colors[RETANGULO] = al_map_rgb(0,85,130);
	colors[CIRCULO] = al_map_rgb(0,194,199);
	colors[ROUNDED_R] = al_map_rgb(0,134,173);

	srand(2);
	startGame();
	int n_zeros = processaMatriz();
	while (n_zeros > 0)
	{
		do
		{
			atualizaOffset();
			// imprimeMatriz();
			atualizaMatriz();
			// imprimeMatriz();
		} while (processaMatriz());
		completaMatriz();
		n_zeros = processaMatriz();
	}

	draw_scenario();
	al_flip_display();
	int pontos, playing = 1, col_src, lin_src, col_dst, lin_dst, flag_animation = 0;
	while (playing)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				playing = 0;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && !flag_animation)
		{
			getCell(ev.mouse.x, ev.mouse.y, &lin_src, &col_src);
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && !flag_animation)
		{
			getCell(ev.mouse.x, ev.mouse.y, &lin_dst, &col_dst);
			if (distancia(lin_src, col_src, lin_dst, col_dst) == 1 && M[lin_src][col_src].type && M[lin_dst][col_dst].type)
			{
				troca(lin_src, col_src, lin_dst, col_dst);
				flag_animation = 1;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			pontos = processaMatriz();
			while (pontos > 0)
			{
				draw_scenario();
				al_flip_display();
				pausa();
				atualizaOffset();
				atualizaMatriz();
				score += pow(2, pontos);
				pontos = processaMatriz();
			}

			draw_scenario();
			al_flip_display();

			if (plays == 0)
				playing = 0;
			flag_animation = 0;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			playing = 0;
		}
	}

	al_rest(1);

	int record;
	al_clear_to_color(al_map_rgb(230, 240, 250));
	sprintf(PONTUACAOJOGADOR, "Score: %d", score);
	al_draw_text(size_f, al_map_rgb(200, 0, 30), SCREEN_W / 3, SCREEN_H / 2, 0, PONTUACAOJOGADOR);
	if (novoRecorde(score, &record))
	{
		al_draw_text(size_f, al_map_rgb(200, 20, 30), SCREEN_W / 3, 100 + SCREEN_H / 2, 0, "NOVO RECORDE!");
	}
	else
	{
		sprintf(PONTUACAOJOGADOR, "Record: %d", record);
		al_draw_text(size_f, al_map_rgb(0, 200, 30), SCREEN_W / 3, 100 + SCREEN_H / 2, 0, PONTUACAOJOGADOR);
	}
	al_flip_display();
	al_rest(2);

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}