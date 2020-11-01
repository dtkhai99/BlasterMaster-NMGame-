#pragma once
#include <map>
#include <vector>
#include <d3d9.h>
/*
						|	index |  left   | top  |  right  |  bottom  |
				mapping	|	 1	  |	16		|	0  |	16	 |	16		|
	texture id-------->	|	 2	  |	32		|	0  |	16	 |	16		|
						|	 ..   | ..		|	   |		 |			|

	these left, top, right, bottom can be group as RECT struct of directX
	index can be used as index of vector
	
	Question: Should it be use for animation?
*/

class SpriteDatabase
{

private:

};

