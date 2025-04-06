/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Cao Khai(Casey Muratori's disciple) $
   $Notice: (C) Copyright 2024 by Cao Khai, Inc. All Rights Reserved. $
   ======================================================================== */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

// NOTE: Create a small tweak that make a random.map based on number of row, column
// and tile's types FLAWLESSLY DONE!

// NOTE: Should I create struct type for each tile for easy accessing or
// just need to create its position for memory benefit

typedef uint8_t uint8;
typedef uint16_t uint16;

// NOTE: Cause the map is alway a rectagle or square
// 5 is a reasonable number of wall chunks
const float WALL_RATIO = 0.35;
const uint8 WALL_CHUNK_NUMBER = 5;
const uint16 WALL_SHAPE[5] = {0x9FF9, 0x6FF6, 0x3FFC, 0xFF33, 0xCCFF};

struct Specs{
    uint8 ID = 0;
    uint8 Position = 0;
    Specs(){
        ID = 0;
        Position = 0;
    };
};

struct Tile{
    // Wall tile is clearly overlaying one
    bool isWall = false;    
    uint8 ID = 0;
    uint8 Position = 0;
    Tile(bool iswall = false, bool overlayed = false, uint8 id = 0, uint8 position = 0){
        iswall = iswall;
        ID = id;
        Position = position;
    };
};

struct WallChunk{
    // One wall struct contain number of areas, each area size
    uint8 positionn = 0;
    uint8 sizee = 0;
    // NOTE: How to decide the position of the wall without overlapping different one
    Specs* specs;
};

struct MapStructures{
    char* MapName = nullptr;
    uint8 WallIDno = 0;
    uint8 BgrIDno = 0;
    // NOTE: Don't need to make an array of ID. Directly randomize it from
    // a given number
    uint8 column = 0 ;
    uint8 row = 0 ;

    uint8 mapSize = 0 ;
    uint8 wallSize = 0;

    uint8* bgrID = nullptr;
    uint8* wallID = nullptr;

    WallChunk WallChunk[5];
};

bool IsNumber(int character){
    if (character >= 48 && character <= 57){
        return true;
    }
    return false;
}

void printMenu(){
    printf("This is a small Map maker\n");
    printf("There are few Choices: M: Make a map \n");
    printf("                       Q: Quit \n");
}

void MakeWallChunk(WallChunk* chunk){
    uint16 chosenShape = WALL_SHAPE[(rand()%4)];
    int i = 0;
    while(i < 4){
        // WORKING!! ===========================
        chosenShape
        for(int j = 0; j < 4; j++){
            if(power(2,j))
        }
        // ======================================
    };
}

void constructWall(MapStructures* map = nullptr){

    uint8 WallChunkAvgSize = map->wallSize/WALL_CHUNK_NUMBER;
    printf("Wall chunk average size is: %hhd\n", WallChunkAvgSize);
    //NOTE: ??? How to make the wall chunk looked randomly naturual
    // instead of group of equal size and the offseted last one

    uint8 countSize = 0;
    uint8 chunkDistance = map->mapSize/4;

    //NOTE: This is for deciding size of each chunks
    for (uint8 i = 0; i < WALL_CHUNK_NUMBER; i++){

        if(i < WALL_CHUNK_NUMBER - 1){            

            // NOTE: size of each chunk first
            map->WallChunk[i].sizee = (uint8)(((rand()%10)+89)*WallChunkAvgSize/100);            
            // While it created garbage value
            countSize += map->WallChunk[i].sizee;

        } else {
            map->WallChunk[i].sizee = map->wallSize - countSize;           
        }

        printf("Wall chunk %hhd size is:%hhd\n", i, map->WallChunk[i].sizee);
        map->WallChunk[i].positionn = i*chunkDistance;
        printf("Wall chunk %hhd position is:%hhd\n", i, map->WallChunk[i].positionn);        

        // if(map->WallChunk[i].specs != nullptr){
        //     delete[] map->WallChunk[i].specs;
        //     map->WallChunk[i].specs = nullptr;
        // }

        map->WallChunk[i].specs = new Specs[map->WallChunk[i].sizee];            

        // ==================================================
        // NOTE: And this is for implementing every wall of each chunk
        for(uint8 j = 0; j < map->WallChunk[i].sizee; j++){
            // NOTE: Time to create a set of fixed shape of wall chunks
            // then randomize among them
            map->WallChunk[i].specs[j].ID = map->wallID[rand()%(map->WallIDno -1)];
            map->WallChunk[i].specs[j].Position = (map->WallChunk[i].positionn*(j+1));
            printf("Wall pos %hhd ID is: %hhd\n", map->WallChunk[i].specs[j].Position, map->WallChunk[i].specs[j].ID);
            // NOTE: I Think I need to decide the each chunk range first and
            // each wall in them later            
        }        
        // 
    }
}

char* MakeContent(MapStructures* mapS){

    // NOTE: Problem arised at the content create process
    uint8 lineLength = mapS->row * 2 + mapS->row;
    uint8 charWritten = 0;

    uint8 tempBgrTile = 0;
    uint8 tempWallPosition = 0;
    uint8 wallChunkIndex = 0;
    uint8 wallIndex = 0;

    tempWallPosition = mapS->WallChunk[wallChunkIndex].specs[wallIndex].Position;
    char* Content = new char[mapS->mapSize];
    
    // NOTE: This is for securing the memory
    memset(Content, 0, sizeof(Content));
    // NOTE: 0number_ BackGround
    // First create background tile first
    for (uint8 i = 0; i < mapS->column ; i++) {
        uint8 j = 0;
        // Remake this uint8o the whole mapsize cause the linelength is not always
        // equal

        // NOTE: How to explicitly check for wall ID without nested loop
        // in designated position
        //NOTE: I think I learnt how to dynamically make advantage of loop
        // ===============================================================        

        while ( j < lineLength) {
             if ( j < lineLength - 2) {
                 if ((lineLength*i) + j == tempWallPosition){                     
                     sprintf(Content + (lineLength*i) + j ,"%d%d",0,mapS->WallChunk[wallChunkIndex].specs[wallIndex].ID);
                     wallIndex++;
                     if(wallIndex > (uint8)(mapS->WallChunk[wallChunkIndex].sizee - 1)){
                         wallChunkIndex++;
                         wallIndex = 0;
                     };

                 } else {
                     tempBgrTile = mapS->bgrID[rand()%(mapS->BgrIDno - 1)];
                     sprintf(Content + (lineLength*i) + j ,"%d",tempBgrTile);                     
                 }

                 // NOTE: Add the condition of wall check here
                 // randomize tile ID and overwrite it to the defined Pos
                 j+=2;
            // The cursor run to linelength before condition can check
                 if(j < lineLength - 2){
                     sprintf(Content + (lineLength*i) + j,"%c",' ');                 
                     j++;
                 }
             } else {
            if (i < mapS->column - 1 ){
                // NOTE: OverWrite happen when ex: i = 1; 14 = i = 0 j = lineLength

                // The loop stuck at i = lineLength - 1
                 sprintf(Content + (lineLength*i) + j,"%c",'\n');
                // Content[(lineLength*i)+j] = '\n'; // LF
                j++;
            } else {
                 sprintf(Content + (lineLength*i) + j,"%c",'\0');                
                // Content[(lineLength*i)+j] = '\0'; // LF                
                j++;
            }
            
          }
        // printf("column number %d\n", i+1);
    // NOTE: Stuck in the loop
    }
    }
    // Content[mapS->mapsize - 1] = '\0';
    printf("Content is:\n%s\n", Content);
    printf("And the number of Char written is: %d\n", charWritten);
    return Content;
    delete[]Content;
}

char MenuAndChoice(){
            printMenu();
            char option = 0;
            // NOTE: Issue solve because I hit enter every time type input
            // which is \n the " " before %c will solve this
            scanf(" %c", &option);
            if(option > 32){
                option = option - 32;
            }
            // printf("option is :%c and in uint8eger is: %d\n", option, (int)option);
    return option;
}

bool CreateAndWriteFile(const MapStructures* map, const char*Content){
    DWORD BytesWritten;
    // NOTE: Problem arised at the content create process    

    // NOTE: Bug lied here
    // printf("Content is: \n %(int)s", Content);
    // printf("Map's MapName is:%s , length is: %zu\n",FileName, strlen(FileName));
    //     if (strpbrk(FileName, "<>:\"/\\|?*") != NULL) {
    //     printf("Invalid character detected in file MapName.\n");
    //     return false;
    //     } else {
    //         printf("There is no problem with the MapName at all\n");
    //     }
    
    HANDLE hMap = CreateFileA(
        map->MapName,
        GENERIC_READ|GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL                 );
    
    if (hMap == INVALID_HANDLE_VALUE){
        printf("Failed to create or open the file. Error: %lu\n", GetLastError());
        return false;
    } else {
        if(
            !WriteFile(
                hMap,
                Content,
                strlen(Content),
                &BytesWritten,
                NULL
                      )           
           ){
            printf("Failed write the file. Error: %lu\n", GetLastError());
            return false;
        } else {
            printf("File created successfully\n");
            CloseHandle(hMap);
            return true;   
        }
    }
            // delete [] testContent;
}

int main(int argc, char* argv[]){
    uint8 MinWtileID = 0;
    uint8 MaxWtileID = 0;

    uint8 TileIDs = 0;

    srand(time(NULL));
    MapStructures* mapStructure = new MapStructures;
    mapStructure->MapName = new char [25];
    char* content = nullptr;
    bool Optionchange = false;
    // char* MapContent = nullptr;
    char Option = 0;
    uint8 j = 0;    

    while(Option != 'Q'){
        Option = MenuAndChoice();
        switch(Option){
            case 'M':                
                printf("Firstly, Number of Map's columns: \n");
                scanf(" %hhd", &mapStructure->row);
                printf("Now, Number of Map's rows: \n");
                scanf(" %hhd", &mapStructure->column);
                
                // NOTE:===================================================
                printf("Then, Number of Map's Tile's types: \n");
                scanf(" %hhd", &TileIDs);

                // ========================================================
                printf ("The wall type tile streak is");
                printf("From? : \n");
                scanf(" %hhd", &MinWtileID);

                printf("To? : \n");
                scanf(" %hhd", &MaxWtileID);
                // ========================================================
                
                if(mapStructure->wallID != nullptr){
                    delete[] mapStructure->wallID;
                    mapStructure->wallID = nullptr;
                };

                // NOTE: ?? Why this wall size is 8 while the MaxWtileID - MinWtileID + 1 is supposed to be 3

                mapStructure->WallIDno = (uint8)MaxWtileID - MinWtileID + 1;
                mapStructure->wallID = new uint8[mapStructure->WallIDno]();

                for(uint8 i = 0; i < (MaxWtileID - MinWtileID + 1); i++){
                    // NOTE: Heap overflowing happened here
                    mapStructure->wallID[i] = MinWtileID + i;
                    printf("WallID %d is :%d\n", (int)i, (int)mapStructure->wallID[i]);
                }

                if(mapStructure->bgrID != nullptr){
                    delete[] mapStructure->bgrID;
                    mapStructure->bgrID = nullptr;
                };

                mapStructure->BgrIDno = TileIDs - mapStructure->WallIDno;
                mapStructure->bgrID = new uint8[mapStructure->BgrIDno]();

                j = 0;
                for(uint8 i = 0; i < TileIDs; i++){
                    if(!(i >= MinWtileID && i <= MaxWtileID)){
                        mapStructure->bgrID[j] = i;
                        printf("BackGroundID %d is :%d\n", (int)j,(int)mapStructure->bgrID[j]);
                        j++;
                    }
                }                
                                
                
                printf("Finally, Map's MapName: \n");
                scanf(" %25s", mapStructure->MapName);
                
                mapStructure->mapSize = (((mapStructure->row*2 + mapStructure->row -1 )*mapStructure->column) + mapStructure->column) ;
                mapStructure->wallSize = mapStructure->mapSize * WALL_RATIO ;

                constructWall(mapStructure);

                content = new char;
                content =  MakeContent(mapStructure);
                CreateAndWriteFile(mapStructure, content);
                
                printf("The Map is already Made\n");
                printf("Do you want more map or not Pls type your choice\n");
                break;

            case 'Q':
                printf("Thank you for using this small tweak\n");
                printf(" Bye ^ O ^ \n");
                break;

            default:
                printf("Wrong Choices Pls type in M or Q in lowercase\n");
                break;
        }
}

    for(int i = 0; i < 5; i++){
        delete mapStructure->WallChunk[i].specs;
        mapStructure->WallChunk[i].specs = nullptr;
    }

    delete mapStructure->MapName;
    mapStructure->MapName = nullptr;

    delete mapStructure;
    mapStructure = nullptr;
    return 0;
}
