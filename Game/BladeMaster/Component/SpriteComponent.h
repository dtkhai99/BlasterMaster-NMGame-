#pragma once
#include<d3d9.h>

/*
	Sprite component will store texture id and area where sprite's location is drawed in texture
	assumed that this texture have many sprites in it. If this texture have only 1 sprite, this
	instance must be handled when create entity

	To avoid circular inclusion, texture id will have type as integer. Anyone use this component
	must convert it to texture id

	Information about texture id, look at TextureDatabase.h
*/
struct Sprite {
	unsigned int textureID;
	//unsigned int spriteID;
	RECT area;
};