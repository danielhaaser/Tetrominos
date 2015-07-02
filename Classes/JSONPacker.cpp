//
//  JSONPacker.cpp
//  Tetrominos
//
//  Created by Daniel Haaser on 7/1/15.
//
//

#include "JSONPacker.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

using namespace cocos2d;

namespace JSONPacker
{
    TetrominoState unpackTetrominoJSON(std::string json, TetrominoType type)
    {
        rapidjson::Document document;
        document.Parse<0>(json.c_str());
        
        const char* typeStr;
        
        switch (type)
        {
            case TetrominoType::I: typeStr = "I"; break;
            case TetrominoType::O: typeStr = "O"; break;
            case TetrominoType::T: typeStr = "T"; break;
            case TetrominoType::S: typeStr = "S"; break;
            case TetrominoType::Z: typeStr = "Z"; break;
            case TetrominoType::J: typeStr = "J"; break;
            case TetrominoType::L: typeStr = "L"; break;
        }
        // ampersand or "and symbol" is &
        // reference type
        rapidjson::Value& tetrominoDoc = document[typeStr];
        
        rapidjson::Value& colorDoc = tetrominoDoc["color"];
        int r = colorDoc["r"].GetInt();
        int g = colorDoc["g"].GetInt();
        int b = colorDoc["b"].GetInt();
        Color3B color = Color3B(r, g, b);
        
        std::vector<std::vector<Coordinate>> rotations;
        
        rapidjson::Value& rotationsDoc = tetrominoDoc["rotations"];
        
        for (rapidjson::SizeType rotationIndex = 0; rotationIndex < rotationsDoc.Size(); ++rotationIndex)
        {
            std::vector<Coordinate> coordinates;
            
            rapidjson::Value& coordinatesDoc = rotationsDoc[rotationIndex];
            
            for (rapidjson::SizeType coordinatesIndex = 0; coordinatesIndex < coordinatesDoc.Size(); ++coordinatesIndex)
            {
                int x = coordinatesDoc[coordinatesIndex]["x"].GetInt();
                int y = coordinatesDoc[coordinatesIndex]["y"].GetInt();
                
                Coordinate coordinate = Coordinate(x, y);
                
                coordinates.push_back(coordinate);
            }
            
            rotations.push_back(coordinates);
        }
    
        TetrominoState tetrominoState;
        tetrominoState.color = color;
        tetrominoState.rotations = rotations;
        
        return tetrominoState;
    }
}