#include <iostream>
#include <iomanip>
#include <ctime>
#include "console.h"
#include "structs.h"




// CONSTANT //
const short FRAME_RATE = 50;

const short WIDTH  = 41;
const short HEIGHT = 21;
const char WALL_SPRITE  = 4;
const int  WALL_COLOR = WHITE;
const char FRUIT_SPRITE = '?';
const short FRUIT_POINT = 10;
// -------- //


// FUNCTIONS DECLARATIONS //
void init_map(cell matrix[][WIDTH]);
void draw_map(cell matrix[][WIDTH]);
void spawn_fruit(cell matrix[][WIDTH]);

bool get_input(vect2& _new_dir);
char get_head(vect2 direction);
// ---------------------- //




int main() {
    srand(time(NULL));


    snake player = { '0', BORDEAUX, WHITE, 
        { WIDTH / 2, HEIGHT / 2 }, { WIDTH / 2, HEIGHT / 2 },
        { 0, 0 }, { WIDTH / 2, HEIGHT / 2 },
        { 0, 0 }, { 0, 0 }
    };

    cell map[HEIGHT][WIDTH]; init_map(map);
    map[HEIGHT / 2][WIDTH / 2].sprite    = player.sprite;
    map[HEIGHT / 2][WIDTH / 2].fg_color  = player.alt_color;
    map[HEIGHT / 2][WIDTH / 2].bg_color  = player.color;

    int score = 0;


    // LOGIC VARIABLES //
    bool gameover  = false;
    bool changedir = false;
    // --------------- //
    



    ///////////////
    // GAME LOOP //
    ///////////////
    spawn_fruit(map);
    setcursor(false);
    while (!gameover) {


        ////////////////////
        // UPDATE SECTION //
        ////////////////////
        changedir = get_input(player.head_dir); // input


        // HEAD UPDATE //
        if (changedir) { // if direction change, save the change in the map
            map[player.head_pos.y][player.head_pos.x].turn_point = true;
            map[player.head_pos.y][player.head_pos.x].direction = player.head_dir;
        }
        player.next_head_pos = player.head_pos + player.head_dir;  // future head position
        map[player.head_pos.y][player.head_pos.x].fg_color = player.color;
        map[player.head_pos.y][player.head_pos.x].sprite   = player.sprite;
        // ----------- //

        
        // TAIL UPDATE //
        if (map[player.tail_pos.y][player.tail_pos.x].turn_point) {
            player.tail_dir = map[player.tail_pos.y][player.tail_pos.x].direction;
            map[player.tail_pos.y][player.tail_pos.x].turn_point = false;
        }
        player.next_tail_pos = player.tail_pos + player.tail_dir;  // future tail position
        map[player.tail_pos.y][player.tail_pos.x].sprite = ' ';
        map[player.tail_pos.y][player.tail_pos.x].fg_color  = BLACK;
        map[player.tail_pos.y][player.tail_pos.x].bg_color  = BLACK;
        // ----------- //


        // SCORE & GAME OVER //
        if (map[player.next_head_pos.y][player.next_head_pos.x].sprite == FRUIT_SPRITE) {
            // change tail
            map[player.tail_pos.y][player.tail_pos.x].sprite = player.sprite;
            map[player.tail_pos.y][player.tail_pos.x].fg_color  = player.color;
            map[player.tail_pos.y][player.tail_pos.x].bg_color  = player.color;
            player.next_tail_pos = player.tail_pos;
            
            // get point & spawn fruit
            score += FRUIT_POINT;
            spawn_fruit(map);
        } else if (
            map[player.next_head_pos.y][player.next_head_pos.x].sprite == WALL_SPRITE ||
            map[player.next_head_pos.y][player.next_head_pos.x].sprite == player.sprite ) {
            gameover = true;
            break;
        }
        // ----------------- //


        // UPDATE VARIABLES //
        player.tail_pos = player.next_tail_pos;
        player.head_pos = player.next_head_pos;

        map[player.head_pos.y][player.head_pos.x].sprite = get_head(player.head_dir);
        map[player.head_pos.y][player.head_pos.x].fg_color = player.alt_color;
        map[player.head_pos.y][player.head_pos.x].bg_color = player.color;
        // ---------------- //


        //////////////////////
        // REFRESH & RENDER //
        //////////////////////
        moveto(0, 0);
        Sleep(FRAME_RATE);


        draw_map(map);
        if (player.head_dir == vect2{ 0, 0 })
             std::cout << "press wasd - arrow keys for start to play\n";   
        else std::cout << "     Y O U R   S C O R E   ::   " << std::setw(4) << score << " p   ";
    }


    // GAME OVER //
    moveto(11, HEIGHT / 2);
    setcolor(BLACK, BORDEAUX);
    std::cout << " G A M E   O V E R ";
    RESETCOLOR;
    moveto(0, HEIGHT + 2);
    // --------- //


    system("PAUSE");
    return 0;
}




// FUNCTIONS DEFINITION //
void init_map(cell matrix[][WIDTH]) {
    for (short y = 0; y < HEIGHT; y++) {
        matrix[y][0] = cell{ WALL_SPRITE, WALL_COLOR, BLACK, false, { 0, 0 } };
        matrix[y][WIDTH - 1] = cell{ WALL_SPRITE, WALL_COLOR, BLACK, false, { 0, 0 } };

        char texture = (y == 0 || y == HEIGHT - 1) ?
            WALL_SPRITE : ' ';
        for (short x = 1; x < WIDTH - 1; x++) {
            matrix[y][x] = cell{ texture, WALL_COLOR, BLACK, false, { 0, 0 } };
        }
    }
}


void draw_map(cell matrix[][WIDTH]) {
    for (short y = 0; y < HEIGHT; y++) {
        for (short x = 0; x < WIDTH; x++) {
            setcolor(matrix[y][x].fg_color, matrix[y][x].bg_color);
            std::cout << matrix[y][x].sprite;
            RESETCOLOR;
        }
        std::cout << "\n";
    }
}


void spawn_fruit(cell matrix[][WIDTH]) {
    short fruit_color = rand() % 14 + 1;
    short x, y;
    do {
        x = rand() % (WIDTH - 1)  + 1;
        y = rand() % (HEIGHT - 1) + 1;
    } while (matrix[y][x].sprite != ' ');

    matrix[y][x].sprite = FRUIT_SPRITE;
    matrix[y][x].fg_color = WHITE;
    matrix[y][x].bg_color = fruit_color;
}


bool get_input(vect2& _new_dir) {
    if (!_kbhit())
        return false;
    
    switch (_getch()) {
    case KEY_UP:
    case (int)'w':
        if (_new_dir.y == 1) return false;

        _new_dir = vect2{ 0, -1 };
        break;

    case KEY_DOWN:
    case (int)'s':
        if (_new_dir.y == -1) return false;

        _new_dir = vect2{ 0, 1 };
        break;

    case KEY_RIGHT:
    case (int)'d':
        if (_new_dir.x == -1) return false;

        _new_dir = vect2{ 1, 0 };
        break;

    case KEY_LEFT:
    case (int)'a':
        if (_new_dir.x == 1) return false;

        _new_dir = vect2{ -1, 0 };
        break;

    default:
        return false;
        break;
    }
    return true;
}


char get_head(vect2 direction) {
    if (direction == vect2{ 0, -1 }) return 24; // ↑
    if (direction == vect2{ 0, 1 })  return 25; // ↓
    if (direction == vect2{ 1, 0 })  return 26; // →
    if (direction == vect2{ -1, 0 }) return 27; // ←
}
// -------------------- //