#include "stdafx.h"
#include "BlockGUI.h"

#include "BlockObject.h"
#include "ItemBlockObject.h"

struct ItemTypeEnumDesc
{
	ItemType itemType;
	std::string itemTypeID;
};

BlockGUI::BlockGUI()
	: ComponentGUI(ComponentGUIType::Block)
	, blockObject(nullptr)
	, isChangeRect(false)
	, isChangeRectItemBlock(false)
	, heightCount(0)
	, texture(nullptr)
	, widthCount(0)
	, itemBlockObject(nullptr)
{
}

BlockGUI::~BlockGUI()
{
}

void BlockGUI::Update()
{
	if (blockObject == nullptr)
		return;

	ImGui::BeginChild("##Block", { 900.f, isChangeRect || isChangeRectItemBlock ? 700.f : 150.f});
	ImGui::Text("Block");

	sf::Vector2f rectSize = blockObject->GetRectSize();
	float rectSizeArr[2] = { rectSize.x, rectSize.y };
	sf::IntRect textureUVRect = blockObject->GetTextureUVRect();
	int textureUVRectArr[4] = { textureUVRect.left, textureUVRect.top, textureUVRect.width, textureUVRect.height };

	ImGui::Text("RectSize"); ImGui::SameLine();
	if (ImGui::InputFloat2("##RectSize", rectSizeArr))
	{
		rectSize.x = rectSizeArr[0];
		rectSize.y = rectSizeArr[1];
		blockObject->SetSize(rectSize);
	}

	if (ImGui::Button("ChangeUVRect", { 120.f, 20.f }))
	{
		isChangeRect = !isChangeRect;
	}

	if (itemBlockObject != nullptr)
	{
		ImGui::SameLine();
		if (ImGui::Button("ChangeRectItemBlock", { 120.f, 20.f }))
		{
			isChangeRectItemBlock = !isChangeRectItemBlock;
		}

		ItemType itemType = itemBlockObject->GetItemType();

		static const ItemTypeEnumDesc itemEnum[] =
		{
			{ ItemType::Coin , "Coin"}
			,{ ItemType::Flower , "Flower"}
			,{ ItemType::MushRoom , "MushRoom"}
			,{ ItemType::Star , "Star"}
		};

			
		int idx;
		for (idx = 0; idx < (int)ItemType::End; ++idx)
		{
			if (itemEnum[idx].itemType == (itemBlockObject->GetItemType()))
				break;
		}

		bool isSelect = false;
		if (ImGui::BeginCombo("ItemTypeCombo", itemEnum[idx].itemTypeID.c_str()))
		{
			for (int n = 0; n < (int)ItemType::End; n++)
			{
				if (ImGui::Selectable(itemEnum[n].itemTypeID.c_str(), idx == n))
				{
					itemBlockObject->SetItemType(itemEnum[n].itemType);
				}
			}

			ImGui::EndCombo();
		}
		sf::IntRect changeTextureUVRect = itemBlockObject->GetChangeTextureUvRect();
		int changeTextureUVRectArr[4] = { changeTextureUVRect.left, changeTextureUVRect.top, changeTextureUVRect.width, changeTextureUVRect.height };


		if (isChangeRectItemBlock)
		{
			ImGui::Text("ChangeRectItemBlock");

			for (int i = 0; i < heightCount; ++i)
			{
				for (int j = 0; j < widthCount; ++j)
				{
					ImGui::PushID((i * widthCount) + j);
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.f, 1.f));

					if (ImGui::ImageButton(("ItemBlockTileMap" + std::to_string((i * widthCount) + j)).c_str(), texture->getNativeHandle(), { 24.f, 24.f },
						{ tileUvSize.x * j,tileUvSize.y * i }, { tileUvSize.x * (j + 1) , tileUvSize.y * (i + 1) }, {}, { 1,1,1,1 }))
					{
						changeTextureUVRect.left = changeTextureUVRect.width * j;
						changeTextureUVRect.top = changeTextureUVRect.top * i;

						itemBlockObject->SetChangeTextureUvRect(changeTextureUVRect);
					}

					if (j != widthCount - 1)
						ImGui::SameLine();

					ImGui::PopStyleVar();
					ImGui::PopID();

				}
			}
		}
		ImGui::Text("ChangeTextureUVRect"); ImGui::SameLine();
		if (ImGui::InputInt4("##ChangeTextureUVRect", textureUVRectArr))
		{
			changeTextureUVRect.left = changeTextureUVRectArr[0];
			changeTextureUVRect.top = changeTextureUVRectArr[1];
			changeTextureUVRect.width = changeTextureUVRectArr[2];
			changeTextureUVRect.height = changeTextureUVRectArr[3];

			itemBlockObject->SetChangeTextureUvRect(changeTextureUVRect);
		}
	}

	if (isChangeRect)
	{
		ImVec4			bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		ImVec4			tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

		for (int i = 0; i < heightCount; ++i)
		{
			for (int j = 0; j < widthCount; ++j)
			{
				ImGui::PushID((i * widthCount) + j);
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.f, 1.f));

				if (ImGui::ImageButton(("BlockTileMap" + std::to_string((i * widthCount) + j)).c_str(), texture->getNativeHandle(), { 24.f, 24.f },
					{ tileUvSize.x * j,tileUvSize.y * i }, { tileUvSize.x * (j + 1) , tileUvSize.y * (i + 1) }, bg_col, tint_col))
				{
					textureUVRect.left = textureUVRect.width * j;
					textureUVRect.top = textureUVRect.top * i;

					blockObject->SetUVRect(textureUVRect);
				}

				if (j != widthCount - 1)
					ImGui::SameLine();

				ImGui::PopStyleVar();
				ImGui::PopID();

			}
		}

	}


	ImGui::Text("TextureUVRect"); ImGui::SameLine();
	if (ImGui::InputInt4("##TextureUVRect", textureUVRectArr))
	{
		textureUVRect.left = textureUVRectArr[0];
		textureUVRect.top = textureUVRectArr[1];
		textureUVRect.width = textureUVRectArr[2];
		textureUVRect.height = textureUVRectArr[3];

		blockObject->SetUVRect(textureUVRect);
	}

	ImGui::EndChild();
}

void BlockGUI::SetObject(GameObject* object)
{
	target = object;


	if (target == nullptr || (BlockObject*)target == nullptr)
	{
		blockObject = nullptr;
		return;
	}

	blockObject = (BlockObject*)target;
	itemBlockObject =  dynamic_cast<ItemBlockObject*>(target);

	texture = &ResourcesManager<sf::Texture>::GetInstance().Get(blockObject->GetTextureID());
	auto textureSize = texture->getSize();
	widthCount = textureSize.x / blockObject->GetTextureUVRect().width;
	heightCount = textureSize.y / blockObject->GetTextureUVRect().height;

	tileUvSize = { 1.f / (textureSize.x / (float)16.f), 1.f / (textureSize.y / (float)16.f) };
}

