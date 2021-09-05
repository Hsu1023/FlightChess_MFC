#pragma once
#include"pch.h"
#define bplane player[BLUE].plane
#define rplane player[RED].plane
#define gplane player[GREEN].plane
#define yplane player[YELLOW].plane


class CPlayer {
public:
	CBitmap plane[4];
	CBitmap temp_plane;
	int plane_pos[4][2];//四架飞机目前位置
	int plane_state[4];
	int plane_block_num[4];
	int finished_plane_num;
};
enum plane_state { AIRPORT, AIRPORT2, FLYING, FINISHED };
