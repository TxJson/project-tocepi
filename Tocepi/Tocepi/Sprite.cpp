#include "Sprite.h"

tx::Sprite::Sprite() :
	myTextureType(TextureType::IDLE)
{
}
tx::Sprite::Sprite(Texture aTexture, tz::Vector2f& aPos, TextureType aType) :
	myPos(aPos),
	myTextureType(aType)
{
	myTextures.push_back(aTexture);
}
tx::Sprite::Sprite(std::vector<Texture> someTextures, tz::Vector2f& aPos, TextureType aType) :
	myTextures(someTextures),
	myPos(aPos),
	myTextureType(aType)
{}

tx::Sprite::Sprite(sf::Sprite& aSprite)
{
	mySprite = aSprite;
	myLoadedFlag = true;
	myTextureWidth = aSprite.getTextureRect().width;
	myTextureHeight = aSprite.getTextureRect().height;
}

tx::Sprite::~Sprite()
{
}

void tx::Sprite::LoadTexture()
{
	if (!myLoadedFlag)
	{
		sf::Texture tempTxtr;
		for (size_t i = 0; i < myTextures.size(); i++)
		{
			tempTxtr.loadFromFile(myTextures[i].GetLocation());
			myTextures[i].SetTexture(tempTxtr);
		}

		SetTexture(myTextureType);

		myLoadedFlag = true;
	}
}

void tx::Sprite::SetAnimation()
{
	mySprite.setTextureRect
	(
		sf::IntRect
		(
			myTexture.getSize().x / myRows * static_cast<int>(myCurrentFrame.X),
			myTexture.getSize().y / myColumns * static_cast<int>(myCurrentFrame.Y),
			myTexture.getSize().x / myRows,
			myTexture.getSize().y / myColumns
		)
	);
}

void tx::Sprite::UpdateAnimation(float& aDelta)
{
	if (myCurrentFrame.X * myCurrentFrame.Y >= myTextures[myTextureType].GetFrames())
	{
		myCurrentFrame = tz::Vector2i();
	}
	else
	{
		if (myCurrentFrame.X >= myRows)
		{
			myCurrentFrame.X = 0;
			if (myColumns > 1)
			{
				myCurrentFrame.Y += (myFramerate * aDelta);
			}
		}
		else if (myCurrentFrame.X < myRows)
		{
			myCurrentFrame.X += (myFramerate * aDelta);
		}
	}
	SetAnimation();
}

sf::Sprite& tx::Sprite::GetSprite()
{
	return mySprite;
}

tz::Vector2f tx::Sprite::GetOrigin()
{
	return tz::Vector2f(mySprite.getOrigin().x, mySprite.getOrigin().y);
}

tz::Vector2f tx::Sprite::GetPosition()
{
	return myPos;
}

tz::Vector2f tx::Sprite::GetScale()
{
	return myScale;
}

sf::IntRect tx::Sprite::GetFrame()
{
	if (myLoadedFlag)
	{
		return mySprite.getTextureRect();
	}
	return sf::IntRect();
}

TextureType& tx::Sprite::GetCurrentTextureType()
{
	return myTextureType;
}

void tx::Sprite::SetTexture(TextureType aType)
{
	myTextureType = aType;
	myTexture = myTextures[aType].GetTexture();
	mySprite.setTexture(myTexture);
	mySprite.setPosition(myPos.X, myPos.Y);
	mySprite.setScale(
		myTextures[aType].GetScale().X,
		myTextures[aType].GetScale().Y
	);

	myScale = myTextures[aType].GetScale();

	myRows = myTextures[aType].GetRows();
	myColumns = myTextures[aType].GetColumns();
	myFramerate = myTextures[aType].GetFramerate();

	myCurrentFrame = tz::Vector2i();
	SetAnimation();

	mySprite.setOrigin
	(
		(myTexture.getSize().x / myRows / 2.0f),
		(myTexture.getSize().y / myColumns / 2.0f)
	);

	myTextureWidth = mySprite.getTextureRect().width;
	myTextureHeight = mySprite.getTextureRect().height;
}

void tx::Sprite::Flip(FlipView aSide)
{
	if (aSide == FlipView::Left)
	{
		SetScale(-myTextures[myTextureType].GetScale().X, myTextures[myTextureType].GetScale().Y);
	}
	else
	{
		SetScale(myTextures[myTextureType].GetScale().X, myTextures[myTextureType].GetScale().Y);
	}
}

void tx::Sprite::SetScale(tz::Vector2f aScale)
{
	if (myLoadedFlag)
	{
		mySprite.setScale(sf::Vector2f(aScale.X, aScale.Y));
	}
	myScale = aScale;
}

void tx::Sprite::SetPosition(float aX, float aY)
{
	mySprite.setPosition(aX, aY);
	myPos = tz::Vector2f(aX, aY);
}

void tx::Sprite::SetScale(float x, float y)
{
	mySprite.setScale(x, y);
	myScale = tz::Vector2f(x, y);
}

void tx::Sprite::SetPosition(tz::Vector2f & aPos)
{
	mySprite.setPosition(sf::Vector2f(aPos.X, aPos.Y));
	myPos = aPos;
}

void tx::Sprite::Draw(sf::RenderWindow & aWindow)
{
	aWindow.draw(mySprite);
}
