//--------------------------------------------------------------------------------------
// File: DescriptorHeap.h
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkID=615561
//--------------------------------------------------------------------------------------

#pragma once

#ifdef _GAMING_XBOX_SCARLETT
#include <d3d12_xs.h>
#elif (defined(_XBOX_ONE) && defined(_TITLE)) || defined(_GAMING_XBOX)
#include <d3d12_x.h>
#elif defined(USING_DIRECTX_HEADERS)
#include <directx/d3d12.h>
#include <dxguids/dxguids.h>
#else
#include <d3d12.h>
#endif

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

#include <wrl/client.h>

#ifndef DIRECTX_TOOLKIT_API
#ifdef DIRECTX_TOOLKIT_EXPORT
#ifdef __GNUC__
#define DIRECTX_TOOLKIT_API __attribute__ ((dllexport))
#else
#define DIRECTX_TOOLKIT_API __declspec(dllexport)
#endif
#elif defined(DIRECTX_TOOLKIT_IMPORT)
#ifdef __GNUC__
#define DIRECTX_TOOLKIT_API __attribute__ ((dllimport))
#else
#define DIRECTX_TOOLKIT_API __declspec(dllimport)
#endif
#else
#define DIRECTX_TOOLKIT_API
#endif
#endif


namespace DirectX
{
    // A contiguous linear random-access descriptor heap
    class DescriptorHeap
    {
    public:
        DIRECTX_TOOLKIT_API DescriptorHeap(
            _In_ ID3D12DescriptorHeap* pExistingHeap) noexcept;
        DIRECTX_TOOLKIT_API DescriptorHeap(
            _In_ ID3D12Device* device,
            _In_ const D3D12_DESCRIPTOR_HEAP_DESC* pDesc) noexcept(false);
        DIRECTX_TOOLKIT_API DescriptorHeap(
            _In_ ID3D12Device* device,
            D3D12_DESCRIPTOR_HEAP_TYPE type,
            D3D12_DESCRIPTOR_HEAP_FLAGS flags,
            size_t count) noexcept(false);
        DIRECTX_TOOLKIT_API inline DescriptorHeap(
            _In_ ID3D12Device* device,
            size_t count) noexcept(false) :
            DescriptorHeap(device,
                D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
                D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, count)
        {}

        DescriptorHeap(DescriptorHeap&&) = default;
        DescriptorHeap& operator=(DescriptorHeap&&) = default;

        DescriptorHeap(const DescriptorHeap&) = delete;
        DescriptorHeap& operator=(const DescriptorHeap&) = delete;

        DIRECTX_TOOLKIT_API D3D12_GPU_DESCRIPTOR_HANDLE __cdecl WriteDescriptors(
            _In_ ID3D12Device* device,
            uint32_t offsetIntoHeap,
            uint32_t totalDescriptorCount,
            _In_reads_(descriptorRangeCount) const D3D12_CPU_DESCRIPTOR_HANDLE* pDescriptorRangeStarts,
            _In_reads_(descriptorRangeCount) const uint32_t* pDescriptorRangeSizes,
            uint32_t descriptorRangeCount);

        DIRECTX_TOOLKIT_API D3D12_GPU_DESCRIPTOR_HANDLE __cdecl WriteDescriptors(
            _In_ ID3D12Device* device,
            uint32_t offsetIntoHeap,
            _In_reads_(descriptorRangeCount) const D3D12_CPU_DESCRIPTOR_HANDLE* pDescriptorRangeStarts,
            _In_reads_(descriptorRangeCount) const uint32_t* pDescriptorRangeSizes,
            uint32_t descriptorRangeCount);

        DIRECTX_TOOLKIT_API D3D12_GPU_DESCRIPTOR_HANDLE __cdecl WriteDescriptors(
            _In_ ID3D12Device* device,
            uint32_t offsetIntoHeap,
            _In_reads_(descriptorCount) const D3D12_CPU_DESCRIPTOR_HANDLE* pDescriptors,
            uint32_t descriptorCount);

        DIRECTX_TOOLKIT_API inline D3D12_GPU_DESCRIPTOR_HANDLE GetFirstGpuHandle() const noexcept
        {
            assert(m_desc.Flags & D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);
            assert(m_pHeap != nullptr);
            return m_hGPU;
        }

        DIRECTX_TOOLKIT_API inline D3D12_CPU_DESCRIPTOR_HANDLE GetFirstCpuHandle() const noexcept
        {
            assert(m_pHeap != nullptr);
            return m_hCPU;
        }

        DIRECTX_TOOLKIT_API inline D3D12_GPU_DESCRIPTOR_HANDLE GetGpuHandle(_In_ size_t index) const
        {
            assert(m_pHeap != nullptr);
            if (index >= m_desc.NumDescriptors)
            {
                throw std::out_of_range("D3DX12_GPU_DESCRIPTOR_HANDLE");
            }
            assert(m_desc.Flags & D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);

            D3D12_GPU_DESCRIPTOR_HANDLE handle;
            handle.ptr = m_hGPU.ptr + UINT64(index) * UINT64(m_increment);
            return handle;
        }

        DIRECTX_TOOLKIT_API inline D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle(_In_ size_t index) const
        {
            assert(m_pHeap != nullptr);
            if (index >= m_desc.NumDescriptors)
            {
                throw std::out_of_range("D3DX12_CPU_DESCRIPTOR_HANDLE");
            }

            D3D12_CPU_DESCRIPTOR_HANDLE handle;
            handle.ptr = static_cast<SIZE_T>(m_hCPU.ptr + UINT64(index) * UINT64(m_increment));
            return handle;
        }

        DIRECTX_TOOLKIT_API inline size_t Count() const noexcept { return m_desc.NumDescriptors; }
        DIRECTX_TOOLKIT_API inline unsigned int Flags() const noexcept { return m_desc.Flags; }
        DIRECTX_TOOLKIT_API inline D3D12_DESCRIPTOR_HEAP_TYPE Type() const noexcept { return m_desc.Type; }
        DIRECTX_TOOLKIT_API inline uint32_t Increment() const noexcept { return m_increment; }
        DIRECTX_TOOLKIT_API inline ID3D12DescriptorHeap* Heap() const noexcept { return m_pHeap.Get(); }

        DIRECTX_TOOLKIT_API static void __cdecl DefaultDesc(
            _In_ D3D12_DESCRIPTOR_HEAP_TYPE type,
            _Out_ D3D12_DESCRIPTOR_HEAP_DESC* pDesc) noexcept;

    private:
        void Create(_In_ ID3D12Device* pDevice, _In_ const D3D12_DESCRIPTOR_HEAP_DESC* pDesc);

        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>    m_pHeap;
        D3D12_DESCRIPTOR_HEAP_DESC                      m_desc;
        D3D12_CPU_DESCRIPTOR_HANDLE                     m_hCPU;
        D3D12_GPU_DESCRIPTOR_HANDLE                     m_hGPU;
        uint32_t                                        m_increment;
    };


    // Helper class for dynamically allocating descriptor indices.
    // The pile is statically sized and will throw an exception if it becomes full.
    class DescriptorPile : public DescriptorHeap
    {
    public:
        using IndexType = size_t;
        static constexpr IndexType INVALID_INDEX = size_t(-1);

        DIRECTX_TOOLKIT_API inline DescriptorPile(
            _In_ ID3D12DescriptorHeap* pExistingHeap,
            size_t reserve = 0) noexcept(false)
            : DescriptorHeap(pExistingHeap),
            m_top(reserve)
        {
            if (reserve > 0 && m_top >= Count())
            {
                throw std::out_of_range("Reserve descriptor range is too large");
            }
        }

        DIRECTX_TOOLKIT_API inline DescriptorPile(
            _In_ ID3D12Device* device,
            _In_ const D3D12_DESCRIPTOR_HEAP_DESC* pDesc,
            size_t reserve = 0) noexcept(false)
            : DescriptorHeap(device, pDesc),
            m_top(reserve)
        {
            if (reserve > 0 && m_top >= Count())
            {
                throw std::out_of_range("Reserve descriptor range is too large");
            }
        }

        DIRECTX_TOOLKIT_API inline DescriptorPile(
            _In_ ID3D12Device* device,
            D3D12_DESCRIPTOR_HEAP_TYPE type,
            D3D12_DESCRIPTOR_HEAP_FLAGS flags,
            size_t capacity,
            size_t reserve = 0) noexcept(false)
            : DescriptorHeap(device, type, flags, capacity),
            m_top(reserve)
        {
            if (reserve > 0 && m_top >= Count())
            {
                throw std::out_of_range("Reserve descriptor range is too large");
            }
        }

        DIRECTX_TOOLKIT_API inline DescriptorPile(
            _In_ ID3D12Device* device,
            size_t count,
            size_t reserve = 0) noexcept(false) :
            DescriptorPile(device,
                D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
                D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, count, reserve)
        {}

        DescriptorPile(DescriptorPile&&) = default;
        DescriptorPile& operator=(DescriptorPile&&) = default;

        DescriptorPile(const DescriptorPile&) = delete;
        DescriptorPile& operator=(const DescriptorPile&) = delete;

        DIRECTX_TOOLKIT_API inline IndexType Allocate()
        {
            IndexType start, end;
            AllocateRange(1, start, end);

            return start;
        }

        DIRECTX_TOOLKIT_API void AllocateRange(size_t numDescriptors, _Out_ IndexType& start, _Out_ IndexType& end);

    private:
        IndexType m_top;
    };
}
