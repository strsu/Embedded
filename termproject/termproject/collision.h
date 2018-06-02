/*
 * collision.h
 *
 *  Created on: 2018. 6. 1.
 *      Author: 502
 */

#ifndef COLLISION_H_
#define COLLISION_H_
#pragma once

#define NOTEHEIGHT		16
#define NOTEMAX			12
#define BARHEIGHT		32
#define KEYMAX			4

typedef struct {
	int CLIS_Y[4];
}CollisionManager;

void CollisionUpdate();
void CollisionInit();
void CollisionUrteil();	/* Bar를 터치했을때 처리 함수 */

#endif /* COLLISION_H_ */
