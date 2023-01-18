//
// Created by abdoulayedia on 15.01.2023
//
#include "SpriteEntity.h"

#include "Application.h"
#include "ImageHandler.h"

namespace sse {

	SpriteEntity::SpriteEntity(const std::filesystem::path& path) {
		_texture         = AssetManager::GetTexture(path);
		_originalTexture = AssetManager::GetTexture(path);
	}

	SpriteEntity::SpriteEntity(sf::Sprite& sprite): _sprite(sprite) {
		const sf::Texture* spriteTex = _sprite.getTexture();
		if (spriteTex != nullptr) {
			_texture         = *spriteTex;
			_originalTexture = *spriteTex;
		}
	}

	SpriteEntity::SpriteEntity(sf::Texture& texture): _texture(texture), _originalTexture(texture) {
		_sprite.setTexture(_texture);
	}

	void SpriteEntity::OnAwake() {}

	void SpriteEntity::OnUpdate(float dt) {}

	void SpriteEntity::OnRender(sf::RenderTarget& target) {
		target.draw(_sprite);
		OnRenderFrames(target);
	}

	void SpriteEntity::OnRenderFrames(sf::RenderTarget& target) {
		if (_frames.empty()) return;

		// Draw frames
		for (auto& frame : _frames) {
			sf::RectangleShape rect;
			rect.setPosition(frame.Rect.left, frame.Rect.top);
			rect.setSize(sf::Vector2f(frame.Rect.width, frame.Rect.height));
			rect.setFillColor(sf::Color::Transparent);

			if (_currentFrame != nullptr && frame == *_currentFrame)
				rect.setOutlineColor(sf::Color::Green);
			else
				rect.setOutlineColor(sf::Color::Red);

			rect.setOutlineThickness(1.f);
			target.draw(rect);
		}

		// Draw frame connections
		for (auto& frame : _frames) {
			if (frame.NextFrame != nullptr) {
				sf::Vertex line[] = {
				    sf::Vertex(
				        sf::Vector2f(frame.Rect.left + frame.Rect.width, frame.Rect.top + frame.Rect.height / 2.f)),
				    sf::Vertex(sf::Vector2f(frame.NextFrame->Rect.left,
				                            frame.NextFrame->Rect.top + frame.NextFrame->Rect.height / 2.f))};
				target.draw(line, 2, sf::Lines);
			}
		}
	}

	void SpriteEntity::OnRenderProperties() {
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNode("Sprite Entity")) {
			{
				ImVec2 position(_sprite.getPosition().x, _sprite.getPosition().y);
				float  scale = _sprite.getScale().x;

				if (ImGui::SliderFloat("X", &position.x, -1000.f, 1000.f)) {
					_sprite.setPosition(position.x, _sprite.getPosition().y);
				}
				if (ImGui::SliderFloat("Y", &position.y, -1000.f, 1000.f)) {
					_sprite.setPosition(_sprite.getPosition().x, position.y);
				}

				ImGui::Separator();

				if (ImGui::SliderFloat("Scale", &scale, -1.f, 10.f)) {
					_sprite.setScale(scale, scale);
				}

				ImGui::Separator();

				if (ImGui::Button("Reset")) {
					_sprite.setPosition(0.f, 0.f);
					_sprite.setScale(1.f, 1.f);
				}

				ImGui::Separator();

				if (ImGui::Button("Add Frame")) {
					AddFrame(Frame(sf::IntRect(0, 0, _texture.getSize().x, _texture.getSize().y),
					               "Frame " + std::to_string(_frames.size() + 1)));
				}

				ImGui::Separator();

				if (ImGui::TreeNode("Frames")) {
					// Draw frames
					for (auto& frame : _frames) {
						if (ImGui::TreeNode(frame.Name.c_str())) {
							_currentFrame = &frame;
							char buffer[256];
							strcpy(buffer, frame.Name.c_str());
							if (ImGui::InputText("Name", buffer, 256)) {
								frame.Name = buffer;
							}
							ImGui::InputInt("X", &frame.Rect.left);
							ImGui::InputInt("Y", &frame.Rect.top);
							ImGui::InputInt("Width", &frame.Rect.width);
							ImGui::InputInt("Height", &frame.Rect.height);

							if (ImGui::Button("Delete")) {
								RemoveFrame(frame);
							}

							ImGui::TreePop();
						}
					}
					ImGui::TreePop();
				}

				ImGui::Separator();

				if (ImGui::TreeNode("Image")) {
					ImGui::ColorEdit4("Color To Replace", (float*)&_colorToReplace);
					ImGui::ColorEdit4("New Color", (float*)&_newColor);

					if (ImGui::Button("Replace")) {
						sf::Image img =
						    ImageHandler::ReplaceBackgroundColor(_texture,
						                                         ImageHandler::ImColorToSFColor(_colorToReplace),
						                                         ImageHandler::ImColorToSFColor(_newColor));

						_texture.loadFromImage(img);
						_sprite.setTexture(_texture);
					}
					ImGui::SameLine();
					if (ImGui::Button("Save")) {
						sf::Image img = _texture.copyToImage();
						img.saveToFile("../out/image.png");
					}

					ImGui::SameLine();
					if (ImGui::Button("Reset")) {
						_texture = _originalTexture;
						_sprite.setTexture(_texture);
					}
					ImGui::TreePop();
				}
			}
			ImGui::TreePop();
		}
	}

	sf::Sprite& SpriteEntity::GetSprite() {
		return _sprite;
	}

	void SpriteEntity::SetSprite(const sf::Sprite& sprite) {
		_sprite = sprite;

		const sf::Texture* spriteTex = sprite.getTexture();
		if (spriteTex != nullptr) {
			_texture         = *spriteTex;
			_originalTexture = *spriteTex;
		}
	}

	sf::Texture& SpriteEntity::GetTexture() {
		return _texture;
	}

	sf::Texture& SpriteEntity::GetOriginalTexture() {
		return _originalTexture;
	}

	void SpriteEntity::SetTexture(const sf::Texture& texture) {
		_texture         = texture;
		_originalTexture = texture;
		_sprite.setTexture(_texture);
	}

	std::vector<Frame>& SpriteEntity::GetFrames() {
		return _frames;
	}

	Frame& SpriteEntity::GetFrame(int pos) {
		if (pos < 0 || pos >= _frames.size())
			throw std::out_of_range("No frame were found at this pos: " + std::to_string(pos));

		return _frames[pos];
	}

	void SpriteEntity::SetFrames(const std::vector<Frame>& frames) {
		_frames = frames;
	}

	void SpriteEntity::AddFrame(const Frame& frame) {
		_frames.push_back(frame);
	}

	void SpriteEntity::AddFrame(const Frame& frame, int pos) {
		if (pos < 0 || pos >= _frames.size())
			throw std::out_of_range("Cannot add a frame at the position: " + std::to_string(pos));

		_frames.emplace(_frames.begin() + pos, frame);
	}

	void SpriteEntity::RemoveFrame(int pos) {
		if (pos < 0 || pos >= _frames.size())
			throw std::out_of_range("No frame were found at this pos: " + std::to_string(pos));

		_frames.erase(_frames.begin() + pos);
	}

	void SpriteEntity::RemoveFrame(const Frame& frame) {
		std::remove_if(_frames.begin(), _frames.end(), [&](const Frame& f) { return f == frame; });
	}

	void SpriteEntity::SwapFrames(int lhs, int rhs) {
		if ((lhs < 0 || lhs >= _frames.size()) || (rhs < 0 || rhs >= _frames.size()))
			throw std::out_of_range("Could not swap the frames because the given positions were incorrect: (" +
			                        std::to_string(lhs) + ", " + std::to_string(rhs) + ")");

		auto temp    = _frames[lhs];
		_frames[lhs] = _frames[rhs];
		_frames[rhs] = temp;
	}
} // namespace sse
