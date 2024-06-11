#ifndef _RENDERHELPERCLASS_H
#define _RENDERHELPERCLASS_H

#include "common.h"

namespace Geometry
{
	//Zadanie 2.1.1 - wierzcholki
	struct Vertex
	{
		Vertex(DirectX::XMFLOAT3 position) :Position(position){}
		DirectX::XMFLOAT3 Position;
	};

	using VertexBuffer = std::vector<Vertex>;
	using IndexBuffer = std::vector<std::uint16_t>;

	inline std::pair<VertexBuffer, IndexBuffer> CreateBoxGeometry()
	{
		std::vector<Vertex> vertices =
		{
			Vertex({ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f) }),
			Vertex({ DirectX::XMFLOAT3(-1.0f, +1.0f, -1.0f) }),
			Vertex({ DirectX::XMFLOAT3(+1.0f, +1.0f, -1.0f) }),
			Vertex({ DirectX::XMFLOAT3(+1.0f, -1.0f, -1.0f) }),
			Vertex({ DirectX::XMFLOAT3(-1.0f, -1.0f, +1.0f) }),
			Vertex({ DirectX::XMFLOAT3(-1.0f, +1.0f, +1.0f) }),
			Vertex({ DirectX::XMFLOAT3(+1.0f, +1.0f, +1.0f) }),
			Vertex({ DirectX::XMFLOAT3(+1.0f, -1.0f, +1.0f) })
		};

		std::vector<std::uint16_t> indices =
		{
			// front face
			0, 1, 2,
			0, 2, 3,

			// back face
			4, 6, 5,
			4, 7, 6,

			// left face
			4, 5, 1,
			4, 1, 0,

			// right face
			3, 2, 6,
			3, 6, 7,

			// top face
			1, 5, 6,
			1, 6, 2,

			// bottom face
			4, 0, 3,
			4, 3, 7
		};

		return { std::move(vertices), std::move(indices) };
	}

	inline DirectX::XMFLOAT4X4 Identity4x4()
	{
		static DirectX::XMFLOAT4X4 I(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);

		return I;
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

	inline UINT CalcConstantBufferByteSize(UINT byteSize)
	{
		// Constant buffers must be a multiple of the minimum hardware
		// allocation size (usually 256 bytes).  So round up to nearest
		// multiple of 256.  We do this by adding 255 and then masking off
		// the lower 2 bytes which store all bits < 256.
		// Example: Suppose byteSize = 300.
		// (300 + 255) & ~255
		// 555 & ~255
		// 0x022B & ~0x00ff
		// 0x022B & 0xff00
		// 0x0200
		// 512
		return (byteSize + 255) & ~255;
	}
};
#endif