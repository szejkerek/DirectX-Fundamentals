#ifndef _RENDERHELPERCLASS_H
#define _RENDERHELPERCLASS_H

#include "common.h"

namespace Geometry
{
	struct Vertex
	{
		Vertex(DirectX::XMFLOAT3 position) :Position(position){}
		DirectX::XMFLOAT3 Position;
	};

	using VertexBuffer = std::vector<Vertex>;
	using IndexBuffer = std::vector<std::uint16_t>;

	inline std::pair<VertexBuffer, IndexBuffer> CreateTriangleGeometry()
	{
		std::vector<Vertex> vertices =
		{
			//Zadanie 2.2.1 - geometria
			//Vertex({ DirectX::XMFLOAT3(?, ?, ?) }), //index 1
			//Vertex({ DirectX::XMFLOAT3(?, ?, ?) }), //index 2
			//Vertex({ DirectX::XMFLOAT3(?, ?, ?) }), //index 3
		};

		std::vector<std::uint16_t> indices =
		{
			// triangle indices
			0, 1, 2,
		};

		return { std::move(vertices), std::move(indices) };
	}
};

namespace DirectXHelper
{
	inline Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(
		const std::wstring& filename,
		const D3D_SHADER_MACRO* defines,
		const std::string& entrypoint,
		const std::string& target)
	{
		UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
		compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		Microsoft::WRL::ComPtr<ID3DBlob> byteCode = nullptr;
		Microsoft::WRL::ComPtr<ID3DBlob> errors;
		HRESULT results = D3DCompileFromFile(filename.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			entrypoint.c_str(), target.c_str(), compileFlags, 0, &byteCode, &errors);

		if (errors != nullptr)
		{
			OutputDebugStringA((char*)errors->GetBufferPointer());
		}

		assert(SUCCEEDED(results));

		return byteCode;
	}
};
#endif