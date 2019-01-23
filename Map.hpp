#ifndef MAP_HPP
#define MAP_HPP


class Map
{
    public:
        
        const int cTileSize = 16;

        enum TileType
        {
            Empty,
            Block,
            OneWay,
            TotalTypes
        };

    private:
        TileType mTiles[TotalTypes];
        
};

#endif