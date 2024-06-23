#ifndef _RENDERHELPERCLASS_H
#define _RENDERHELPERCLASS_H

#include "common.h"

namespace Geometry
{
	struct Vertex
	{
		Vertex(DirectX::XMFLOAT3 position, DirectX::XMFLOAT2 uv) :Position(position), UV(uv) {}
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT2 UV;
	};
	using VertexBuffer = std::vector<Vertex>;
	using IndexBuffer = std::vector<std::uint16_t>;

	inline std::pair<VertexBuffer, IndexBuffer> CreateBoxGeometry()
	{
		std::vector<Vertex> vertices =
		{
			//Fron face																		   //Index number:
			Vertex({ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 2.0f) }), //0
			Vertex({ DirectX::XMFLOAT3(-1.0f,  1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) }), //1
			Vertex({ DirectX::XMFLOAT3(1.0f,  1.0f, -1.0f), DirectX::XMFLOAT2(2.0f, 0.0f) }), //2
			Vertex({ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(2.0f, 2.0f) }), //3

			//Right Face
			Vertex({ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) }), //4
			Vertex({ DirectX::XMFLOAT3(1.0f,  1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) }), //5
			Vertex({ DirectX::XMFLOAT3(1.0f,  1.0f,  1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) }), //6
			Vertex({ DirectX::XMFLOAT3(1.0f, -1.0f,  1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) }), //7

			//Left Face
			Vertex({ DirectX::XMFLOAT3(-1.0f, -1.0f,  1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) }), //8
			Vertex({ DirectX::XMFLOAT3(-1.0f,  1.0f,  1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) }), //9
			Vertex({ DirectX::XMFLOAT3(-1.0f,  1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) }), //10
			Vertex({ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) }), //11

			//Bottom Face
			Vertex({ DirectX::XMFLOAT3(-1.0f, -1.0f,  1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) }), //12
			Vertex({ DirectX::XMFLOAT3(-1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) }), //13
			Vertex({ DirectX::XMFLOAT3(1.0f, -1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) }), //14
			Vertex({ DirectX::XMFLOAT3(1.0f, -1.0f,  1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) }), //15

			//Bottom Face
			Vertex({ DirectX::XMFLOAT3(-1.0f,  1.0f, -1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) }), //16
			Vertex({ DirectX::XMFLOAT3(-1.0f,  1.0f,  1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) }), //17
			Vertex({ DirectX::XMFLOAT3(1.0f,  1.0f,  1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) }), //18
			Vertex({ DirectX::XMFLOAT3(1.0f,  1.0f, -1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) }), //19

			//Back Face
			Vertex({ DirectX::XMFLOAT3(1.0f, -1.0f,  1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) }), //20
			Vertex({ DirectX::XMFLOAT3(1.0f,  1.0f,  1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) }), //21
			Vertex({ DirectX::XMFLOAT3(-1.0f,  1.0f,  1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) }), //22
			Vertex({ DirectX::XMFLOAT3(-1.0f, -1.0f,  1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) })  //23
		};

		std::vector<std::uint16_t> indices =
		{
			// front face
			0, 1, 2,
			0, 2, 3,

			// right face
			4, 5, 6,
			4, 6, 7,

			// left face
			8, 9, 10,
			8, 10, 11,

			// bottom face
			12, 13, 14,
			12, 14, 15,

			// top face
			16, 17, 18,
			16, 18, 19,

			// bottom face
			20, 21, 22,
			20, 22, 23
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

	struct Camera
	{
		float Theta = 1.5f * DirectX::XM_PI;
		float Phi = DirectX::XM_PIDIV4;
		float Radius = 5.0f;
		float Width = 0.0f;
		float Height = 0.0f;

		DirectX::XMMATRIX GetViewMatrix() const
		{
			return DirectX::XMLoadFloat4x4(&m_view);
		}

		DirectX::XMMATRIX GetProjectionMatrix() const
		{
			return DirectX::XMLoadFloat4x4(&m_proj);
		}

		void UpdateViewMatrix()
		{
			float x = Radius * sinf(Phi) * cosf(Theta);
			float z = Radius * sinf(Phi) * sinf(Theta);
			float y = Radius * cosf(Phi);

			// Build the view matrix.
			DirectX::XMVECTOR pos = DirectX::XMVectorSet(x, y, z, 1.0f);
			DirectX::XMVECTOR target = DirectX::XMVectorZero();
			DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
			DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(pos, target, up);
			DirectX::XMStoreFloat4x4(&m_view, view);
		}

		void UpdateProjetionMatrix()
		{
			const auto aspectRation = Width / Height;
			DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(0.25f * static_cast<float>(M_PI), aspectRation, 1.0f, 1000.0f);
			DirectX::XMStoreFloat4x4(&m_proj, proj);
		}
	private:
		DirectX::XMFLOAT4X4 m_view = Geometry::Identity4x4();
		DirectX::XMFLOAT4X4 m_proj = Geometry::Identity4x4();
	};
};

namespace DirectXHelper
{
	Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(
		const std::wstring& filename,
		const D3D_SHADER_MACRO* defines,
		const std::string& entrypoint,
		const std::string& target) noexcept;

	Microsoft::WRL::ComPtr< IWICImagingFactory2> CreateWICFactory() noexcept;

	//Function loads a file image to memory buffer
	//Returns: A tuple containing pointer to the buffer, image width and image height
	std::tuple<std::unique_ptr<BYTE[]> /*buffer*/, UINT /*width*/, UINT /*hegiht*/> LoadTextureToBuffer(const wchar_t* path) noexcept;

	inline UINT CalcConstantBufferByteSize(UINT byteSize) noexcept
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