#ifndef _RENDERWIDGETCLASS_H
#define _RENDERWIDGETCLASS_H

#include "GeometryHelper.h"

struct ObjectConstants
{
    DirectX::XMFLOAT4X4 WorldMatrix = Geometry::Identity4x4();
};

struct CameraConstants
{
    DirectX::XMFLOAT4X4 View = Geometry::Identity4x4();
    DirectX::XMFLOAT4X4 Projection = Geometry::Identity4x4();
};

class RenderWidget
{
    
public:
	explicit RenderWidget(unsigned int width, unsigned int height, HWND hWnd);
    ~RenderWidget();
    //RenderWidget class is non-copyable:
    RenderWidget(const RenderWidget&) = delete;
    RenderWidget(RenderWidget&&) = delete;
    RenderWidget& operator=(const RenderWidget&) = delete;
    RenderWidget& operator=(RenderWidget&&) = delete;

    void UpdateWorldCBuffer();
    void UpdateViewProjectionCBuffer();
    void Initialize();
    void Draw();
    void Resize(int width, int height);
    
    struct {
        float X = 0.0f, Y = 0.0f, Z = 0.0f;
    }Position;

    struct {
        float Theta = 0;
        float Phi = DirectX::XM_PIDIV4;
        float Radius = 5.0f;
        float Width = 0.0f;
        float Height = 0.0f;
    }Camera;

private:
    DirectX::XMFLOAT4X4 m_world = Geometry::Identity4x4();
    DirectX::XMFLOAT4X4 m_view = Geometry::Identity4x4();
    DirectX::XMFLOAT4X4 m_projection = Geometry::Identity4x4();
    
private:
    UINT m_rtvDescriptorSize = 0;
	//DirectX12 objects
    void CreateDXDeviceAndFactory();
    void CreateSwapChain(unsigned int width, unsigned int height);
    void ResizeSwapChain(unsigned int width, unsigned int height);
    ID3D12Resource* RenderWidget::GetCurrentBackBuffer()const;
    D3D12_CPU_DESCRIPTOR_HANDLE RenderWidget::GetCurrentBackBufferView()const;
    const static DXGI_FORMAT BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
    static const int SwapChainBufferCount = 2;
    Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
    Microsoft::WRL::ComPtr<IDXGIFactory4> m_dxgiFactory;
    Microsoft::WRL::ComPtr<ID3D12Device> m_dxDevice;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_SwapChainBuffer[SwapChainBufferCount];
    HWND m_hWnd;
    int m_width, m_height;
    unsigned int m_currBackBuffer = 0;


    //Control objects
    void CreateCommandObjects();
    void FlushCommandQueue();
    void ExecuteCommandList();
    void ResetCommandList(ID3D12PipelineState* pipelineState = nullptr);
    UINT64 m_currentFence = 0;
    Microsoft::WRL::ComPtr<ID3D12Fence> m_fence;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_directCmdListAlloc;
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> m_commandList;


    //Descriptor Heaps
    void CreateDescriptorHeaps();
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvDescriptorHeap;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_dsvDescriptorHeap;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_srvDescriptorHeap;


    // Render Target View and Depth Stencil View
    void CreateRenderTargetView();
    void CreateDepthStencilView(unsigned int width, unsigned int height);
    const static DXGI_FORMAT DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_depthStencilBuffer;


    //Constant buffers
    void CreateConstantBuffers();

    //Shaders
    void CompileShaders();
    Microsoft::WRL::ComPtr<ID3DBlob> m_vertexShaderByteCode;
    Microsoft::WRL::ComPtr<ID3DBlob> m_pixelShaderByteCode;


    //Pipeline state and Root signature
    void BuildRootSignature();
    void CreateGraphicPipeline();
    Microsoft::WRL::ComPtr<ID3D12RootSignature> m_rootSignature;
    Microsoft::WRL::ComPtr< ID3D12PipelineState> m_pipelineState;


    //Viewport
    void UpdateViewport(unsigned int width, unsigned int height);
    D3D12_VIEWPORT m_screenViewport;
    D3D12_RECT m_scissorRect;


    //Geometry, Camera, Vertex and Index buffer
    void LoadGeometry();
    void LoadVertexBuffer(const Geometry::VertexBuffer& vertices);
    void LoadIndexBuffer(const Geometry::IndexBuffer& indices);


    struct
    {
        UINT IndexCount = 0;
        UINT StartIndexLocation = 0;
        DXGI_FORMAT IndexFormat = DXGI_FORMAT_R16_UINT;
        UINT IndexBufferByteSize = 0;
        Microsoft::WRL::ComPtr<ID3D12Resource> IndexBufferGPU = nullptr;
        Microsoft::WRL::ComPtr<ID3D12Resource> IndexBufferUploader = nullptr;
        UINT BaseVertexLocation = 0;

        D3D12_INDEX_BUFFER_VIEW IndexBufferView()const
        {
            D3D12_INDEX_BUFFER_VIEW ibv;
            ibv.BufferLocation = IndexBufferGPU->GetGPUVirtualAddress();
            ibv.Format = IndexFormat;
            ibv.SizeInBytes = IndexBufferByteSize;

            return ibv;
        }
    }IndexBuffer;

    struct
    {
        Microsoft::WRL::ComPtr<ID3D12Resource> VertexBufferGPU = nullptr;
        UINT VertexByteStride = 0;
        UINT VertexBufferByteSize = 0;
        Microsoft::WRL::ComPtr<ID3D12Resource> VertexBufferUploader = nullptr;

        D3D12_VERTEX_BUFFER_VIEW VertexBufferView()const
        {
            D3D12_VERTEX_BUFFER_VIEW vbv;
            vbv.BufferLocation = VertexBufferGPU->GetGPUVirtualAddress();
            vbv.StrideInBytes = VertexByteStride;
            vbv.SizeInBytes = VertexBufferByteSize;

            return vbv;
        }
    }VertexBuffer;
};

#endif
