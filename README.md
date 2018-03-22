# columns

Columns is a Tetris variant. In this game, all pieces are composed of 3 (*piece::PIECE_SIZE*) straight vertical tiles.
Each tile has a color. To eliminate tiles from the board it is necessary to gather at least 3 tiles of the same color in
a straight line in any direction (horizontal, vertical or diagonal).

The pieces don't rotate on the plane of the game, thus they always fall in vertical position. What the player can do is
rotate the colors with up and down arrow.

Try it out, it is simple and fun.

## Building

1. checkout the repository: `git clone git@bitbucket.org:mpinto70/columns.git`
1. build the system (from `columns` root): `./runbuild`
1. test the system (from `columns` root): `./runbuild test`
1. demo the system (from `columns` root): `./runbuild demo`

### Dependencies

In order to build the system, you need to install:
`sudo apt-get install -y g++ cmake libboost-all-dev cppcheck libsdl2-dev libsdl2-image-dev  libsdl2-ttf-dev`
