#pragma once

#include "BlocksRegistry.hpp"
#include <iostream>
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <cmath>

#include <filesystem>

class ResourcesManager
{
    inline static std::unordered_map<std::string, Texture2D> texs;

	inline static RenderTexture2D blocks_atlas{};
public:
    inline static void Load(std::string fld = "res")
    {
        std::filesystem::path root = std::filesystem::path(GetApplicationDirectory()) / fld;

        if (!std::filesystem::exists(root))
        {
            root = std::filesystem::path(fld);
        }

        if (!std::filesystem::exists(root))
        {
            std::cerr << "Non valid res dir: " << root << '\n';
            return;
        }

        std::error_code ec;
        for (const auto& entry : std::filesystem::recursive_directory_iterator(root, std::filesystem::directory_options::skip_permission_denied, ec))
        {
            if (!entry.is_regular_file(ec))
            {
                continue;
            }

            const std::filesystem::path relPath = entry.path().lexically_relative(root);
            const std::string key = relPath.generic_string();
            const std::string fullPath = entry.path().string();

            if (texs.find(key) == texs.end())
            {
                texs[key] = LoadTexture(fullPath.c_str());
            }
        }
    }

	inline static void RenderBlocksAtlas()
	{
		UnloadRenderTexture(blocks_atlas);
		blocks_atlas = LoadRenderTexture(2048, 2048);

		const int atlasSize = 2048;
		const int cellSize = 32;
		size_t blockW = atlasSize / cellSize; // 64

		BeginTextureMode(blocks_atlas);
		ClearBackground(BLANK);

		for (size_t i = 0; i < BlocksRegistry::regs.size(); i++)
		{
			std::string textureP = BlocksRegistry::regs[i]->texture_path;

			if (textureP.empty()) continue;
			auto tex = GetTex(textureP);
			if (!tex) continue;

			size_t x = i % blockW;
			size_t y = std::floor(i / blockW);

			DrawTexturePro(*tex, {0, 0, (float)tex->width, (float)tex->height}, {(float)x * cellSize, (float)y * cellSize, (float)cellSize, (float)cellSize}, {0, 0}, 0.f, WHITE);
		}

		EndTextureMode();
	}

	inline static Texture2D& GetBlocksAtlas()
	{
		return blocks_atlas.texture;
	}

	inline static Rectangle GetBlockAtlasRect(uint16_t blockID)
	{
		constexpr int cellSize = 32;
		constexpr int atlasCols = 2048 / cellSize;
		constexpr int atlasSize = 2048;

		float x = static_cast<float>(blockID % atlasCols) * cellSize;
		float y = static_cast<float>(atlasSize - (blockID / atlasCols + 1) * cellSize);

		return {x, y, static_cast<float>(cellSize), -static_cast<float>(cellSize)};
	}

    inline static Texture2D* GetTex(std::string path)
    {
        std::filesystem::path resolvedPath(path);

        if (!resolvedPath.is_absolute())
        {
            resolvedPath = std::filesystem::path(GetApplicationDirectory()) / "res" / resolvedPath;
        }

        const std::string key = resolvedPath.lexically_relative(std::filesystem::path(GetApplicationDirectory()) / "res").generic_string();

        if (texs.find(key) == texs.end())
        {
            texs[key] = LoadTexture(resolvedPath.string().c_str());
        }

        return &texs.at(key);
    }

    inline static void Unload()
    {
        for (auto& t : texs)
        {
            UnloadTexture(t.second);
        }
    }
};

namespace res
{
    inline void Load(std::string fld = "res")
    {
        ResourcesManager::Load(fld);
    }

    inline Texture2D* GetTex(std::string path)
    {
        return ResourcesManager::GetTex(path);
    }

    inline void Unload()
    {
        ResourcesManager::Unload();
    }
}