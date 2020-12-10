#pragma once

struct vect2 {
    short x, y;
    vect2 operator + (vect2 a)
    {
        return { this->x + a.x, this->y + a.y };
    }
    bool operator == (vect2 a)
    {
        return (this->x == a.x && this->y == a.y);
    }
};

struct snake {
    char sprite;
    int color;
    int alt_color;

    vect2 head_pos, tail_pos;
    vect2 next_head_pos, next_tail_pos;
    vect2 head_dir, tail_dir;
};

struct cell {
    char sprite;
    int fg_color;
    int bg_color;

    bool turn_point;
    vect2 direction;
};
