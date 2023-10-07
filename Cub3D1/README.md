<div align="center">
  <h1 style="text-align: center;">Cub3D</h1>
</div>

## cub3D is a project of `42cursus`, in cub3D we work as a team of tow student

- ## how to run the program cub3D_bonus
  - first if you dont have the mlx library in your device you should install it if you are interested
  -  run this command bellow to create an executable named cub3D_bonus
  	```
  	make bonus
  	```
  - then run this command bellow you can change the file `maps/map_bonus.cub`
	by any file existing in folder `maps` like `maps/simpe_map.cub`
	```
	./cub3d_bonus maps/map_bonus.cub
	```
## PLANING
- ## Parcine

	- [x] parce first element
	- [x] parce map

- ## Ray_cast
	- [x] draw a simple map
	- [x] make player move
	- [x] put one ray
	- [x] make ray rotate
	- [x] determine the direction `<` `^` `>` and `v`
	***
	- [x] determine the coordinates `there is thre steps`
		- [x] `1` det coordinates that is represent a wall at the intersictions with __x__
		- [x] `2` det coordinates that is represent a wall at the intersictions with __y__
			- in the two steps above we should write a function that calculate the coord `(x,y)`
				and other one that check if you can  move to this coordinates
		- [x] `3` choos the coordinates that have a ray __R__ less than other
	- [x] make the ray stop if there are a wall in the next position

*** 
### relationships of trigonometric circle

		cos(o) = x/R           &&             sin(o) = y/R


		tan(o) = sin(o)/cos(o)      =>        tan(o) = y/x


		x = y/tan(o)           &&             y = tan(o)*x



***


### determine the coordonate of intersiction with y
![](img/dda_y.png)
### determine the coordonate of intersiction with x
![](img/dda_x.png)
***
- ## Draw Walls
	- [x] darwing walls
 	- calculate the hiegth of wall `H_wall = grid_size * H_window / R`
  	 you can use other method to calculate the height of wall but you should
  	 divise by R alwas
    	- then drawing the walls, for every ray there is a wall with `1 px` in the width and ther height is `H_wall px`
	- [x] draw walls with texturs

---
#### link of github repo -> [ayoub-elidryssy](https://github.com/gxxpython/cub)
### sum sources
[RAYCAST TOTURIAL](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) 




