#include "Slider.h"

Slider::Slider(AssetFactory* assetFactory, Options* options, string optionPath, int min, int max, int paginations)
	: MenuEntity::MenuEntity("./png/SliderLine.png", assetFactory, options)
{
	int width, height;

	if(paginations != 0)
	{
		std::cout << "Pagination not supported yet" << std::endl;
	}

	this->dragging = false;

	this->slideRect.x = this->rect.x;
	this->slideRect.y = this->rect.y;

	this->optionPath = optionPath;
	this->controlledValue = std::stoi(options->getValue(optionPath));
	this->controlledMin = min;
	this->controlledMax = max;

	// Load the texture for the slide
	// NOTE: The texture for the line will be loaded in the Entity constructor
	if(assetFactory != NULL)
	{
		this->slideTexture = assetFactory->getAsset<SDL_Texture>("./png/Slider.png");
		SDL_QueryTexture(this->slideTexture, NULL, NULL, &width, &height);
		this->slideRect.w = width;
		this->slideRect.h = height;
	}

	this->slideValue = (float) (this->controlledValue - this->controlledMin)/(float) (this->controlledMax - this->controlledMin);
}

void Slider::handleMousePress(int mouseState, int x, int y)
{
	if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) &&
		this->rect.contains(x, y))
	{
		this->dragging = true;
	}
}

void Slider::handleMouseDrag(int mouseButton, int prevX, int prevY, int currX, int currY)
{
	if(this->dragging)
	{
		slideValue = (currX - this->rect.x - this->slideRect.w/2)/(this->rect.w - this->slideRect.w);
		if(slideValue < 0)
		{
			slideValue = 0;
		}

		if(slideValue > 1)
		{
			slideValue = 1;
		}
		
	}
}

void Slider::handleMouseRelease(int mouseState, int x, int y)
{
	if(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		this->dragging = false;
	}

	this->controlledValue = ((this->controlledMax - this->controlledMin) * slideValue) + this->controlledMin;
	options->setValue(optionPath, std::to_string(this->controlledValue));
}

void Slider::update(int frameTime)
{
	Entity::update(frameTime);

	this->slideRect.setCenter((slideValue * (this->rect.w - this->slideRect.w)) + this->rect.x + this->slideRect.w/2, this->slideRect.getCenter().y);
}

void Slider::render(SDL_Renderer* gRenderer)
{
	Entity::render(gRenderer);
	SDL_Rect renderRect = {this->slideRect.x, this->slideRect.y, this->slideRect.w, this->slideRect.h};
	SDL_RenderCopy( gRenderer, this->slideTexture, NULL, &renderRect );	
}

void Slider::setRect(Rect rect)
{
	double ratio = this->slideRect.w/this->slideRect.h;

	MenuEntity::setRect(rect);
	this->slideRect.x = this->rect.x;
	this->slideRect.y = this->rect.y;
	this->slideRect.h = this->rect.h;
	this->slideRect.w = this->rect.h*ratio;
}

char* Slider::type()
{
	return "Slider";
}