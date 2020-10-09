#include "TextureDatabase.h"
#include "Debug.h"
#include "Engine.h"
#include <iostream>
#include <fstream>
#include <string>

void TextureDatabase::ReadData(LPCWSTR filePath)
{
	std::fstream input;
	input.open(filePath, std::ios::in);
	if (input.is_open()) {
		std::string str;
		char delimiter = '|';
		while (std::getline(input, str)) {
			TextureType type;
			LPCWSTR texturePath;

			//String manipulation
			unsigned int current, previous = 0;
			current = str.find(delimiter);
			while (current != std::string::npos) {
				type = (TextureType)std::stoi(str.substr(previous, current - previous)); //Convert String -> int -> TextureType
				previous = current + 1;
				current = str.find(delimiter, previous);
			}

			//Convert std::string -> std::wstring -> LPCWSTR
			std::string temp = str.substr(previous, current - previous);
			std::wstring wideString = std::wstring(temp.begin(), temp.end());
			texturePath = wideString.c_str();
			
			LPDIRECT3DTEXTURE9 texture;
			
			//Load Texture
			D3DXIMAGE_INFO info;
			HRESULT result = D3DXGetImageInfoFromFile(texturePath, &info);
			if (result != D3D_OK)
			{
				DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", texturePath);
				return;
			}

			LPDIRECT3DDEVICE9 d3ddv = Engine::GetInstance()->GetDirect3DDevice();

			result = D3DXCreateTextureFromFileEx(
				d3ddv,								// Pointer to Direct3D device object
				texturePath,						// Path to the image to load
				info.Width,							// Texture width
				info.Height,						// Texture height
				1,
				D3DUSAGE_DYNAMIC,
				D3DFMT_UNKNOWN,
				D3DPOOL_DEFAULT,
				D3DX_DEFAULT,
				D3DX_DEFAULT,
				D3DCOLOR_XRGB(255, 255, 255),			// Transparent color
				&info,
				NULL,
				&texture);								// Created texture pointer

			if (result != D3D_OK)
			{
				DebugOut(L"[ERROR] CreateTextureFromFile failed. File: %s\n", texturePath);
				return;
			}

			mDatabase[type] = std::shared_ptr<LPDIRECT3DTEXTURE9>(&texture);

			DebugOut(L"[INFO] Texture loaded Ok: %s \n", texturePath);
		}

		input.close();
	}
	
}

std::shared_ptr<LPDIRECT3DTEXTURE9> TextureDatabase::GetTexture(TextureType type)
{
	if (mDatabase.find(type) != mDatabase.end()) {
		return mDatabase[type];
	}
	DebugOut(L"Texture Type %d not found \n", type);
	return std::shared_ptr<LPDIRECT3DTEXTURE9>();
}
